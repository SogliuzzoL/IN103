#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "bitree.h"
#include "bitreealg.h"
#include "generic_queue.h"

#include "utilio.h"
#include "utilstr.h"

double entropy(int nbY, int nbN, int total)
{
  double py = ((double)nbY) / total;
  double pn = ((double)nbN) / total;
  double result = 0.0;

  if (py > 0)
  {
    result -= py * log2(py);
  }
  if (pn > 0)
  {
    result -= pn * log2(pn);
  }

  return result;
}

/* IG(S, Fever) = Entropy(S) - (|Sʏᴇꜱ| / |S|) * Entropy(Sʏᴇꜱ) -  */
/* (|Sɴᴏ| / |S|) * Entropy(Sɴᴏ) */
double information_gain(double entropy_target, double entropy_feature_yes, double entropy_feature_no,
                        int nb_feature_yes, int nb_feature_no, int length_target)
{

  double result = entropy_target - (((double)nb_feature_yes) / length_target) * entropy_feature_yes - (((double)nb_feature_no) / length_target) * entropy_feature_no;

  return result;
}

double information_gain_feature(char *filename, int feature, int class_index, int length_dataset, int class_yes, int class_no)
{

  char *prefix_cmd_yes;
  asprintf(&prefix_cmd_yes, "cut -d ';' -f%d,%d %s | grep '^Y' ", feature, class_index, filename);
  char *cmd;
  asprintf(&cmd, "%s | %s", prefix_cmd_yes, "wc -l");
  int feature_nb_yes = command_to_int(cmd);
  asprintf(&cmd, "%s | %s", prefix_cmd_yes, "grep 'Y$' | wc -l");
  int feature_nb_yes_yes = command_to_int(cmd);
  asprintf(&cmd, "%s | %s", prefix_cmd_yes, "grep 'N$' | wc -l");
  int feature_nb_yes_no = command_to_int(cmd);

  char *prefix_cmd_no;
  asprintf(&prefix_cmd_no, "cut -d ';' -f%d,%d %s | grep '^N' ", feature, class_index, filename);
  asprintf(&cmd, "%s | %s", prefix_cmd_no, "wc -l");
  int feature_nb_no = command_to_int(cmd);
  asprintf(&cmd, "%s | %s", prefix_cmd_no, "grep 'Y$' | wc -l");
  int feature_nb_no_yes = command_to_int(cmd);
  asprintf(&cmd, "%s | %s", prefix_cmd_no, "grep 'N$' | wc -l");
  int feature_nb_no_no = command_to_int(cmd);

  double result = information_gain(entropy(class_yes, class_no, length_dataset),
                                   entropy(feature_nb_yes_yes, feature_nb_yes_no, feature_nb_yes),
                                   entropy(feature_nb_no_yes, feature_nb_no_no, feature_nb_no),
                                   feature_nb_yes, feature_nb_no, length_dataset);

  return result;
}

int findMaxIndex(double *tab, int size)
{
  double max = tab[0];
  int index = 0;

  for (int i = 1; i < size; i++)
  {
    if (max < tab[i])
    {
      max = tab[i];
      index = i;
    }
  }

  return index;
}

int main(int argc, char *argv[])
{

  /* argv[1] = dataset_header */
  /* argv[2] = dataset_feature */
  /* argv[3] = dataset */

  if (argc != 4)
  {
    printf("Not enough arguemts\n");
    printf("\tUsage: %s header.csv features.csv dataset.csv\n", argv[0]);
    return EXIT_FAILURE;
  }

  char *cmd;
  asprintf(&cmd, "head -1 %s", argv[1]);
  char *header_dataset = command_to_string(cmd);
  asprintf(&cmd, "head -1 %s | grep -o ';' | wc -l", argv[1]);
  int nb_seperators_dataset = command_to_int(cmd);
  int nb_fields_dataset = nb_seperators_dataset + 1;
  int class_index = nb_fields_dataset;
  char **fields_dataset = csv_to_array(header_dataset, nb_fields_dataset);
  printf("header dataset: %s", header_dataset);
  asprintf(&cmd, "head -1 %s", argv[2]);
  char *header_features = command_to_string(cmd);
  asprintf(&cmd, "head -1 %s | grep -o ';' | wc -l", argv[2]);
  int nb_seperators_features = command_to_int(cmd);
  int nb_fields_features = nb_seperators_features + 1;
  char **fields_features = csv_to_array(header_features, nb_fields_features);
  printf("header features: %s", header_features);

  bool *considered_features = malloc(sizeof(bool) * nb_fields_dataset);
  if (considered_features == NULL)
  {
    perror("Erreur allocation memoire\n");
    return EXIT_FAILURE;
  }
  for (int i = 0; i < nb_fields_dataset; i++)
  {
    considered_features[i] = false;
  }

  for (int i = 0; i < nb_fields_features; i++)
  {
    for (int j = 0; j < nb_fields_dataset; j++)
    {
      if (strcmp(fields_features[i], fields_dataset[j]) == 0)
      {
        considered_features[j] = true;
        break;
      }
    }
  }

  integer_bitree_t tree;
  integer_bitree_init(&tree);

  generic_queue_t queue_nodes;
  generic_queue_init(&queue_nodes, NULL, NULL, NULL);
  generic_queue_t queue_filenames;
  generic_queue_init(&queue_filenames, NULL, build_str, free);

  generic_queue_enqueue(&queue_filenames, argv[3]);

  int code = 0;
  int cpt = 0;
  integer_bitreenode_t *current_node = NULL;

  double *current_ig = malloc(nb_fields_dataset * sizeof(double));
  if (current_ig == NULL)
  {
    fprintf(stderr, "Error: memory allocation\n");
    return EXIT_FAILURE;
  }

  /* ********************* */
  /* * Tree construction * */
  /* ********************* */
  do
  {
    printf("################## ITERATION %d\n", cpt);

    void *data_str = NULL;
    generic_queue_dequeue(&queue_filenames, &data_str);
    printf("%s \n", (char *)data_str);
    char *dataset = (char *)data_str;

    /* Computation of the entropy of the targeted class in the current dataset */
    char *cmd;
    asprintf(&cmd, "cat %s | wc -l", dataset);
    int length_dataset = command_to_int(cmd);
    printf("Length of dataset: %d\n", length_dataset);

    //    memset (cmd, 0, 50);
    asprintf(&cmd, "cut -d ';' -f %d %s | grep -c 'Y'", class_index, dataset);
    int target_nb_yes = command_to_int(cmd);
    //    memset (cmd, 0, 50);
    asprintf(&cmd, "cut -d ';' -f %d %s | grep -c 'N'", class_index, dataset);
    int target_nb_no = command_to_int(cmd);
    printf("Target Y=%d, N=%d => entropy=%f\n", target_nb_yes, target_nb_no, entropy(target_nb_yes, target_nb_no, length_dataset));

    /* Reset IG memory */
    for (int i = 0; i < nb_fields_dataset; i++)
    {
      current_ig[i] = 0.0;
    }

    for (int i = 0; i < nb_fields_dataset; i++)
    {
      if (considered_features[i] != true)
      {
        continue;
      }

      /* Note : cut counts from 1 while in C counts from 0 so i+1 */
      printf("Compute information gain for feature:%d\n", i);
      current_ig[i] = information_gain_feature(dataset, i + 1, class_index, length_dataset, target_nb_yes, target_nb_no);
    }

    int maxIndex = findMaxIndex(current_ig, nb_fields_dataset);
    considered_features[maxIndex] = false; /* Do not consider this feature in the next iterations */

    printf("current node considers feature %d\n", maxIndex);

    if (current_node == NULL)
    {
      /* We are at the first iteration */
      code = integer_bitree_ins_left(&tree, NULL, maxIndex); /* Put value at root level */
      if (code != 0)
      {
        fprintf(stderr, "Error\n");
        integer_bitree_destroy(&tree);
        generic_queue_destroy(&queue_nodes);
        return EXIT_FAILURE;
      }
      integer_bitreenode_t *root = integer_bitree_root(&tree);
      code = generic_queue_enqueue(&queue_nodes, root); /* For next iteration on left son */
      if (code != 0)
      {
        printf("Error enqueue is not working %d\n", code);
      }
      code = generic_queue_enqueue(&queue_nodes, root); /* For right son in two iterations */
      if (code != 0)
      {
        printf("Error enqueue is not working %d\n", code);
      }
    }
    else
    {
      /* Other iterations */
      if (cpt % 2 == 1)
      {
        code = integer_bitree_ins_left(&tree, current_node, maxIndex);
        integer_bitreenode_t *temp = integer_bitree_left(current_node);
        generic_queue_enqueue(&queue_nodes, (void *)temp);
      }
      else
      {
        code = integer_bitree_ins_right(&tree, current_node, maxIndex);
        integer_bitreenode_t *temp = integer_bitree_right(current_node);
        generic_queue_enqueue(&queue_nodes, (void *)temp);
      }
    }
    /* ********************************* */
    /* Preparation of the next iteration */
    /* ********************************* */

    /* Generate new files following latest decision made  */
    asprintf(&cmd, "awk -F';' '$%d==\"Y\"' %s > /tmp/feature%d-yes.csv; echo $?", maxIndex + 1, dataset, maxIndex);
    /* printf ("cmd = %s\n", cmd); */
    command_to_int(cmd);
    asprintf(&cmd, "awk -F';' '$%d==\"N\"' %s > /tmp/feature%d-no.csv; echo $?", maxIndex + 1, dataset, maxIndex);
    /* printf ("cmd = %s\n", cmd); */
    command_to_int(cmd);
    char *filename_yes;
    asprintf(&filename_yes, "/tmp/feature%d-yes.csv", maxIndex);
    code = generic_queue_enqueue(&queue_filenames, filename_yes);
    char *filename_no;
    asprintf(&filename_no, "/tmp/feature%d-no.csv", maxIndex);
    code = generic_queue_enqueue(&queue_filenames, filename_no);

    cpt++; /* Count the number of features already used */
    if (cpt >= nb_fields_features)
    {
      /* To avoid removing latest elements added in queue_nodes to
   allow adding last leafs in the tree */
      break;
    }

    /* Choose the next node where to insert in the tree */
    void *data;
    code = generic_queue_dequeue(&queue_nodes, &data);
    if (code != 0)
    {
      printf("ERROR\n");
    }
    current_node = (integer_bitreenode_t *)data;

  } while (cpt < nb_fields_features);
  printf("################## ADDING LEAFS !!\n\n");

  while (generic_queue_size(&queue_nodes) > 0 && generic_queue_size(&queue_filenames) > 0)
  {
    void *data = NULL;
    generic_queue_dequeue(&queue_nodes, &data);
    integer_bitreenode_t *new_node = (integer_bitreenode_t *)data;

    /* left son */
    {
      generic_queue_dequeue(&queue_filenames, &data);
      char *filename = (char *)data;

      char *cmd;
      asprintf(&cmd, "cut -d ';' -f %d %s | grep -c 'Y'", class_index, filename);
      int target_nb_yes = command_to_int(cmd);
      // memset (cmd, 0, 50);
      asprintf(&cmd, "cut -d ';' -f %d %s | grep -c 'N'", class_index, filename);
      int target_nb_no = command_to_int(cmd);

      if (target_nb_yes > target_nb_no)
      {
        code = integer_bitree_ins_left(&tree, new_node, nb_fields_dataset);
      }
      else
      {
        code = integer_bitree_ins_left(&tree, new_node, -nb_fields_dataset);
      }
    }

    /* right son */
    {
      generic_queue_dequeue(&queue_filenames, &data);
      char *filename = (char *)data;

      char *cmd;
      asprintf(&cmd, "cut -d ';' -f %d %s | grep -c 'Y'", class_index, filename);
      int target_nb_yes = command_to_int(cmd);
      // memset (cmd, 0, 50);
      asprintf(&cmd, "cut -d ';' -f %d %s | grep -c 'N'", class_index, filename);
      int target_nb_no = command_to_int(cmd);

      if (target_nb_yes > target_nb_no)
      {
        code = integer_bitree_ins_right(&tree, new_node, nb_fields_dataset);
      }
      else
      {
        code = integer_bitree_ins_right(&tree, new_node, -nb_fields_dataset);
      }
    }
  }

  integer_list_t t_inorder;
  integer_list_init(&t_inorder);

  integer_bitreenode_t *root = integer_bitree_root(&tree);
  integer_inorder(root, &t_inorder);

  integer_list_elmt_t *elt = integer_list_head(&t_inorder);
  printf("List (inorder): ");
  for (; elt != NULL; elt = integer_list_next(elt))
  {
    printf("%d, ", elt->data);
  }
  printf("\n");

  /* *********** */
  /* * Inference */
  /* *********** */

  /* *********** */
  /* * Nettoyage */
  /* *********** */

  integer_bitree_destroy(&tree);
  generic_queue_destroy(&queue_nodes);
  generic_queue_destroy(&queue_filenames);

  return EXIT_SUCCESS;
}
