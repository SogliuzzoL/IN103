#ifndef __GENERIC_HASHTABLE_H__
#define __GENERIC_HASHTABLE_H__

#include <stdlib.h>
#include <stdbool.h>
#include "generic_list.h"

/** Nombre d'elements maximal dans la table de hachage */
#define MAXELEM 7919

/** Structure pour un couple (clef, valeur) qui sera stockee dans une
    liste chainee */
typedef struct {
  void* key; /**< cle */
  void* value; /**< valeur */
} generic_ht_elmt_t;

typedef struct {
  /** Nombre d'elements presents dans la table */
  int size;

  /** fonction de comparaison entre deux cles de la table de
     hachage */
  int (*compare)(const void *key1, const void *key2);

  /** fonction de construction d'un element de la liste de la table
     de hachage */
  void* (*build)(const void *data);

  /** fonction de destruction d'un element de la liste de la table de
     hachage */
  void (*destroy)(void *data);

  /** tableau utilise pour stocker les couples (clefs, valeurs) */
  generic_list_t* table[MAXELEM];

} generic_ht_t;

/** \brief Fonction de hachage des clefs qui projettent les adresses memoires
 *    vers une case du tableau.
 *
 * Algorithme simple et loin d'etre parfait: convertir l'adresse en un
 * entier long et faire un ou exclusif avec le nombre de cases du
 * tableau
 *
 * \param key adresse memoire vers l'objet qui represente la clef a
 * stocker
 *
 * \return renvoie l'indice du tableau associe a la clef
*/
int hashFunction (void* key);

/** \brief Fonction d'initialisation de la strcuture generic_ht_t
 *
 * Met a NULL tous les elements du tableau, a zero la taille.
 *
 *
 * @param ht est un pointeur vers la structure de donnees liste
 * chainee generic_ht_t
 *
 * @param compare fonction permettant la comparaison de deux clefs de
 * la table de hachage
 *
 * @param build fonction permettant la construction d'une cellule de
 * la liste associee a un element de la table de hachage
 *
 * @param destroy fonction permettant la destruction d'une valeur de
 * la liste chainee associee a un element de la table de hachage
*/

void generic_hashtable_init (generic_ht_t* ht,
			     int (*compare) (const void *data1, const void *data2),
			     void* (*build)(const void *data),
			     void (*destroy)(void *data));


/** \brief Fonction de destruction d'une table de hachage
 *
 * Desalloue tous les elements de la table de hachage
 *
 *
 * @param ht est un pointeur vers la structure de donnees liste
 * chainee generic_ht_t
*/
void generic_hashtable_destroy (generic_ht_t* ht);

/** \brief Fonction d'ajout d'un couple (clef, valeur) dans la table
 * de hachage
 *
 * Algorithme: hachage de la cle pour trouver l'indice du
 * tableau. Verifie si une liste chainee existe deja sinon la
 * cree. Puis ajoute en tete le nouveau couple (clef, valeur) apres
 * avoir construit une nouvelle cellule de la liste chainee
 *
 *
 * @param ht est un pointeur vers la structure de donnees liste
 * chainee generic_ht_t
 *
 * @param key un pointeur vers un objet memoire representant la clef
 *
 * @param value un pointeur vers un objet memoire representant la
 * valeur a stocker
 *
 * @return un entier pour dire que tout s'est bien passe (0 est ok, -1
 * probleme memoire)
*/
int generic_hashtable_insert (generic_ht_t* ht, void* key, void* value);

/** \brief Fonction de suppression d'un couple (clef, valeur) dans la
 * table de hachage
 *
 * Algorithme: hachage de la cle pour trouver l'indice du
 * tableau. Verifie si une liste chainee existe deja sinon renvoie
 * NULL. Puis cherche dans la liste l'element representant le couple
 * (clef, valeur), la dernier valeur a avoir ete ajoutee (i.e., la
 * plus proche du pointeur de tete). Il faut penser a desallouer la
 * liste si elle est vide.
 *
 * @param ht est un pointeur vers la structure de donnees liste
 * chainee generic_ht_t
 *
 * @param key un pointeur vers un objet memoire representant la clef
 *
 * @return la sturcture contenant les valeurs du couple (clef, valeur)
 * supprimer ou NULL
*/
generic_ht_elmt_t* generic_hashtable_remove (generic_ht_t* ht, void* key);

/** \brief Recherche d'une valeur associee a une clef dans la
 * table de hachage
 *
 * Algorithme: hachage de la cle pour trouver l'indice du
 * tableau. Verifie si une liste chainee existe deja sinon renvoie
 * NULL. Puis cherche dans la liste l'element representant le couple
 * (clef, valeur), la dernier valeur a avoir ete ajoutee (i.e., la
 * plus proche du pointeur de tete).
 *
 * @param ht est un pointeur vers la structure de donnees liste
 * chainee generic_ht_t
 *
 * @param key un pointeur vers un objet memoire representant la clef
 *
 * @return la sturcture contenant les valeurs du couple (clef, valeur)
 * supprimer ou NULL
*/
generic_ht_elmt_t* generic_hashtable_lookfor (generic_ht_t* ht, void* key);

/** \brief Recherche verifie qu'une clef dans la table de hachage
 *
 * Algorithme: hachage de la cle pour trouver l'indice du
 * tableau. Verifie si une liste chainee existe deja sinon renvoie
 * NULL. Puis cherche dans la liste l'element representant le couple
 * (clef, valeur), renvoie vrai si trouve faux sinon
 *
 * @param ht est un pointeur vers la structure de donnees liste
 * chainee generic_ht_t
 *
 * @param key un pointeur vers un objet memoire representant la clef
 *
 * @return une valeur booleenne indiquant si la clef est presente dans
 * la table ou non
*/
bool generic_hashtable_contains (generic_ht_t* ht, void* key);

/** \brief Fonction de mise a jour d'une valeur dans un couple (clef,
 * valeur) dans la table de hachage
 *
 * Algorithme: hachage de la cle pour trouver l'indice du
 * tableau. Cherche la clef dans la liste chainee et met a jour la
 * valeur si la clef est trouvee. Autrement insere un nouveau couple
 * (clef, valeur)
 *
 * @param ht est un pointeur vers la structure de donnees liste
 * chainee generic_ht_t
 *
 * @param key un pointeur vers un objet memoire representant la clef
 *
 * @param value un pointeur vers un objet memoire representant la
 * valeur a stocker
 *
 * @return un entier pour dire que tout s'est bien passe (0 est ok, -1
 * probleme memoire)
*/
int generic_hashtable_update (generic_ht_t* ht, void* key, void* value);

/** \brief Fonction donnant le nombre d'elements stocker dans la table
 * de hachage
 *
 * Retourne la valeur du champ size
 *
 * @param ht est un pointeur vers la structure de donnees liste
 * chainee generic_ht_t
 *
 * @return un entier donnant le nombre d'elements
*/
int generic_hashtable_size (generic_ht_t* ht);

#endif
