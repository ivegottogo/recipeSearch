/**
 * Fichier principal du programme
 *
 *Cree par Jonathan Labelle
*/



#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#define _GNU_SOURCE
#include <string.h>
#define _GNU_SOURCE
#include <strings.h>
#include "openFile.h"
#include "linkedlist.h"
#include "statistiques.h"

/**
 *
 * PROTOTYPES
 *
*/

void search_recipes(char recipe[], char category[]);
void search_categories(char category[]);
void begin_search(int search_type);

/**
 *
 * VARIABLES GLOBALES
 *
 */

FILE* f;
char buffer[120];
char recipy_name[120];
char category[50];
char category_search_string[50];
char recipe_search_string[50];

/**
 * Compte le nombre de categorie dans une ligne (une recette). Se sert du nombre de bracquettes ouvrantes
 * pour determiner le nombre de categorie
 * @param recipe ligne du fichier contenant la recette et les categories
 * @return retourne le nombre de categories (braquetets ouvrantes)
 */

int count_categories(char recipe[]) {
    int i = 0; int j = 0;
    char c = recipe[0];
    while (c != '\0') {
        if (c == '[') { j++; }
        i++;
        c = recipe[i];
    }
    return j;
}

/**
 * Lecture du nom de la recette. Lecture de la ligne jusqu'a la premiere braquette ouvrante
 * @param line ligne du fichier contenant la recette et les categories
 */
void read_recipe_name(char line[]) {
    int i = 0;
    char c = line[i];
    while (c != '[') {
        strncat(recipy_name, &c, 1);
        i++;
        c = line[i];
    }
}

/**
 * Lecture de une categorie. Arrete la lecture avant la premiere braquette fermante rencontree
 * @param line ligne du fichier contenant la recette et les categories
 * @param i index de la braquette ouvrante ou prendre la categorie
 */
void read_category(char line [], int i) {
    i++;
    char c = line[i];
    while (c != ']') {
        strncat(category, &c, 1);
        i++; c = line[i];
    }
}

/**
 * Cherche la position de la prochaine braquette ouvrante dans le string
 * @param line ligne du fichier contenant la recette et les categorie
 * @param i 'combientieme' braquette ouvrante il faut retrouner
 * @return position de la braquette contenant l'option
 */

int read_categories_position (char line [], int i) {
    int j = 0; int k = 0; char c = line[j];
    while (c != '\0') {
        c = line[j];
        if (c == '[' && k == i) {
            return j;
        } else if (c == '[' && k != i) {k++;}
        j++;
    }
    return j;
}

/**
 * Lecture du fichier de recette
 * @param f fichier texte fournit par l'utulisateur
 */

void read_recipes (FILE *f) {
    while (fgets(buffer, sizeof(buffer), f)) {
        memset(recipy_name, 0, strlen(recipy_name));
        read_recipe_name(buffer);
        int i = 0;
        while (i < count_categories(buffer)) {
            memset(category, 0, strlen(category));
            read_category(buffer, read_categories_position(buffer, i));
            add_category(category);
            add_recipe(recipy_name, category);
            i++;
        }
    }
}

/**
 * Fonction qui effectu la recherche de recherche. Verifie s'il s'agit d'une recherche apr categorie ou
 * d'une recherche par categorie et mot cle apres la sollicitation.
 */
void search() {
    char *exitChar = "X";
    int search_type = 0;
        while (strcasecmp(buffer, exitChar) != 0) {
        printf("\nQue voulez-vous chercher? Entrez X ou x pour quitter: ");
        search_type = 0;
        if (strcasecmp(buffer, "X") == 0) {break;}
        memset(buffer, 0, strlen(buffer));
        fgets(buffer, 120, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        char *p;
        if (strcmp(buffer, "") == 0) { printf("erreur, entree vide"); }
        else {
            char *separator = " ";
            p = strtok(buffer, separator);
            char *p2 = strtok(NULL, "");
            strcpy(category_search_string, p);
            search_type = 1;
            if (p2 != NULL) {
                strcpy(recipe_search_string, p2);
                search_type = 2;
            }
            begin_search(search_type);
        }
    }
}

/**
 * Debut de la recherche.
 * @param search_type
 */

void begin_search(int search_type) {
    if (search_type == 0) {
        printf("Entree invalide");
    }
    else if (search_type == 1) {search_categories(category_search_string);}
    else if (search_type == 2) {search_recipes(recipe_search_string, category_search_string);}
}

/**
 * Recheche par categorie avec mots cles
 * @param recipe le mot de cle
 * @param category la categorie a rechercher
 */
void search_recipes(char recipe[], char category[]) {
    int printed = 0;
    struct Category *temp = catptr->head;
    do {
        if (strcasecmp(temp->category_name, category) == 0) {
            struct Recipe *temp2 = temp->head;
                while(temp2 != NULL) {
                    if (strcasestr(temp2->recipe, recipe)) {
                        if (printed != 0) {printf(", ");}
                        printf("%s",temp2->recipe);
                        printed++;
                    }
                    temp2 = temp2->next;
                }}
            temp = temp->next;
    } while(temp->next != NULL);
}

/**
 * Recherche par categorie
 * @param category categorie
 */
void search_categories(char category[]) {
    int printed = 0;
    struct Category *temp = catptr->head;
    do {
        if (strcasecmp(temp->category_name, category) == 0) {
            struct Recipe *temp2 = temp->head;
            while(temp2 != NULL) {
                if (printed != 0) {printf(", ");}
                printf("%s",temp2->recipe);
                temp2 = temp2->next;
                printed++;
            }
        }
        temp = temp->next;
    } while(temp != NULL);
}

/**
 * Verification de l'option statistique et creation d'un fichier ecriture
 * @param argc nombre de arg
 * @param argv2 option -S
 * @param argv3 chemin fichier
 */
void check_stat_option(int argc, char argv2[], char argv3[]) {
    if (argc > 2) {
        if (strcasecmp(argv2, "-S")) {
        } if (argv3 != NULL) {
            open_write_file(argv3);
            write_file(fw, f);
        }
    }
}

int main(int argc, char *argv[]) {
    initialize_nodes();
    launch_open_file(argc, argv[1]);
    read_recipes(f);
    search();
    check_stat_option(argc, argv[2], argv[3]);
    fclose(f);
}
