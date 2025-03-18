#ifndef __INTEGER_STREE_H__
#define __INTEGER_STREE_H__

typedef struct integer_stree_t {
  int size; /**< nombre d'elements dans le tableau initial  */
  int max_size; /**< nombre d'elements dans l'arbre */
  int *tree; /**< tableau representant l'arbre de segment */
} integer_stree_t;

/*! \brief initialisation de la structure arbres de segments
 *
 * Met a zero les champs de la structure
 *
 * @param stree pointeur vers une structure de type integer_stree_t
 */
void integer_stree_init (integer_stree_t* stree);

/*! \brief destruction de la structure arbres de segments
 *
 * Met a zero les champs de la structure et desalloue la m\'emoire
 * associe au champ tree
 *
 * @param stree pointeur vers une structure de type integer_stree_t
 */
void integer_stree_destroy (integer_stree_t* stree);


/*! \brief construction d'un arbre de segements a partir d'un tableau
 *
 * Calcule le nombre maximal d'elements pouvant etre contenus dans
 * l'arbre puis effectue un parcours dichotomique du tableau en meme
 * temps que le parcours d'arbre pour positionner les elements du
 * tableau dans l'arbre. Durant le parcours un calcul de la somme des
 * segments est effectue et stocker dans l'arbre.
 *
 * @param stree pointeur vers une structure de type integer_stree_t
 *
 * @param datas tableaux contenant les valeurs a stocker dans l'arbre
 *
 * @param n la taille de datas
 *
 * @return une valeur entiere indiquant si tout s'est bien passe (0 si
 * ok, -1 sinon)
 */
int integer_stree_build (integer_stree_t* stree, int* datas, int n);

/*! \brief accesseur donnant le nombre d'elements issus du tableau
 *  ayant servi a creer l'arbre de segments
 *
 * @param stree pointeur vers une structure de type integer_stree_t
 *
 * @return le nombre d'elements du tableau initial
 */
int integer_stree_size (integer_stree_t* stree);

/*! \brief accesseur donnant le nombre d'elements pouvant etre stockes
 *  dans l'arbre
 *
 * @param stree pointeur vers une structure de type integer_stree_t
 *
 * @return le nombre d'elements pouvant etre contenus dans l'arbre
 */
int integer_stree_max_size (integer_stree_t* stree);

/*! \brief recuperation de la somme des valeurs du tableau associe a
 * un intervalle d'indice
 *
 * Parcours de l'arbre pour calculer la somme des valeurs de
 * l'intervalle.
 *
 * @param stree pointeur vers une structure de type integer_stree_t
 *
 * @param qe indice de debut d'intervalle
 *
 * @param qs indice de fin d'intervalle
 *
 * @param result valeur de somme des elements associes  a l'interval [qe, qs]
 *
 * @return valeur entiere indiquant si tout s'est bien passse (0 si
 * ok, -1 sinon)
 */
int integer_stree_query (integer_stree_t* stree, int qs, int qe, int *result);

/*! \brief Mise a jour d'une valeur du tableau
 *
 * Parcours l'arbre pour trouver la position associee a l'indice index
 * et mise a jour de sommes partielles
 *
 * @param stree pointeur vers une structure de type integer_stree_t
 *
 * @param index indice de l'element du tableau où changer la valeur
 *
 * @param value nouvelle valeur a stocker
 *
 * @return valeur entiere indiquant si tout s'est bien passee (0 si
 * ok, -1 sinon)
 */
int integer_stree_update (integer_stree_t* stree, int index, int value);

#endif
