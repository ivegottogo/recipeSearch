/**
 * Librairie de statistique
 *
 *Cree par Jonathan Labelle
*/

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include "openFile.h"
#include "linkedlist.h"

/**
 *
 * VARIABLES GLOBALES
 *
 */

char* get_recipe (char buf[]);
char buffer[120];

/**
 * Compte le nombre de lignes d'un fichier
 * @param f fichier
 * @return nombre de ligne
 */
int count_lines(FILE* f) {
    rewind(f);
    int i = 0;
    while (fgets(buffer, sizeof(buffer), f)) {
        i++;
    }
    return i;
}

/**
 * Calcul le nombre de total de recette implante
 * @return nombre de recette
 */

int number_of_recipes () {
    struct Category *temp = catptr->head;
    int i = temp->nb_recipes;
    while(temp->next != NULL){
        temp = temp->next;
        i = i + temp->nb_recipes;
    }
    return i;
}

/**
 * Compte le nombre total de categorie unique implantee
 * @return nomrbe de categorie
 */
int number_of_categories () {
    return catptr->nb_categories;
}

/**
 * Calcule la categorie avec le plus de recette associee
 * @return stirng de la categorie
 */
char* popular_category() {
    struct Category *temp = catptr->head;
    struct Category *temp2 = catptr->head;
    int i = temp->nb_recipes;
    while(temp->next != NULL){
        temp = temp->next;
        if (temp->nb_recipes > i) {
            temp2 = temp;
        }
    }
    return temp2->category_name;
}

/**
 * Compte le nombre de mont dans les le fichier
 * @param f fichier
 * @return nombre de mot
 */
int count_words (FILE *f) {
    rewind(f);
    char *word;
    int i = 0;
    while (fgets(buffer, sizeof(buffer), f)) {
        word = strtok(buffer, " ,.-");
        while (word != NULL) {
            i++;
            word = strtok(NULL, " ,.-");
        }
    }
    return i;
}

/**
 * Prend toutes les statistiques et les ecrit dans un fichier
 * @param fw fichier d'ecriture
 * @param f fichier de lecture
 */
void write_file(FILE *fw, FILE *f) {
    fprintf(fw, "Nombre de ligne: %d\n", count_lines(f));
    fprintf(fw, "Nombre de mots: %d\n", count_words(f));
    fprintf(fw, "Nombre de categorie: %d\n", number_of_categories());
    fprintf(fw, "Nombre de recette: %d\n", number_of_recipes());
    fprintf(fw, "Categorie la plus populaire: %s\n", popular_category());
    fprintf(fw, "Categorie avec le plus de recette: %s\n", popular_category());
    fclose(fw);
}