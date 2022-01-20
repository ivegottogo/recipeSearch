/**
 * Librairie de statistique
 *
 *Cree par Jonathan Labelle
*/

#include "malloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include "openFile.h"

/**
 *
 * TYPEDEF ET STRUCTURES
 *
 */
typedef struct Category {
    char category_name[50];
    int nb_recipes;
    struct Category * next;
    struct Recipe * head;
} Category;

typedef struct Recipe {
    char recipe[120];
    struct Recipe * next;
} recipe;

typedef struct Category_head {
    int nb_categories;
    struct Category * head;
} Category_head;

/**
 *
 * PROTOTYPES
 *
 */
int find_index(struct Category* new_cat);
void insert_category_last(struct Category* new_cat);
void insert_category_index(struct Category* , int index);
int check_unique_cat(struct Category* new_cat);
void add_recipe(char recipe[], char cat[]);
void insert_recipe(struct Recipe* rep, struct Category* new_cat);
void insert_recipy_head (struct Recipe* rep, struct Category* cat);
int check_unique_recipe(struct Recipe* rec, struct Category* cat);
int find_index_recipe(struct Recipe* rec, struct Category* cat);
void insert_recipe_beginning (struct Recipe* rec, struct Category* cat);
void insert_recipe_last (struct Recipe* rec, struct Category* cat);
void insert_recipe_index(struct Recipe* rec, struct Category* cat, int index);

/**
 *
 * VARIABLES GLOBALES
 *
 */

Category_head category_head;
Category_head *catptr = &category_head;

/**
 * Initialisation du maillon Categorie head
 */
void initialize_nodes() {
    catptr = (struct Category_head*)malloc(sizeof(struct Category_head));
    catptr->nb_categories = 0;
    catptr->head = NULL;
}

/**
 * Ajout d'un categorie
 * @param cat string du nom de la categorie
 */

/**
 * Insertion de la premiere categorie dans la liste chainee
 * @param new_cat categorie a inserer
 */
void insert_head_category(struct Category* new_cat) {
    new_cat->next = NULL;
    catptr->head = new_cat;
    ++catptr->nb_categories;
}

void add_category(char cat[]) {
    Category *new_cat;
    new_cat = (struct Category *) malloc(sizeof(struct Category));
    new_cat->nb_recipes = 0;
    strcpy(new_cat->category_name, cat);
    if (catptr->nb_categories == 0) { insert_head_category(new_cat); }
    else {
        if (check_unique_cat(new_cat) != 0) {
            int index = find_index(new_cat);
            insert_category_index(new_cat, index);
        }
    }
}


/**
 * Parcours l'index de categorie pour trouver la position ou inserer la categorie
 * @param new_cat structure categorie a inserer
 * @return
 */
int find_index(struct Category* new_cat) {
    int i = 0;
    struct Category *temp = catptr->head;
    while (i < catptr->nb_categories) {
        if (strcmp(new_cat->category_name, temp->category_name) < 0) {
            break;//ou return i
        } else {
            i++;
            temp = temp->next;}
    }
    return i;
}

/**
 * Verificaiton si la categorie a inserer est unique
 * @param new_cat categorie a inserer
 * @return 0 si deja inseree
 */
int check_unique_cat(struct Category* new_cat) {
    struct Category *temp = catptr->head;
    while(temp != NULL) {
        if (strcmp(new_cat->category_name, temp->category_name) == 0) {
            return 0;
        }
        temp = temp->next;
    }
    return 1;
}

/**
 * insertion de la categorie a la postion du head
 * @param new_cat categorie a inserer
 */
void insert_category_beginning (struct Category* new_cat) {
    new_cat->next = catptr->head;
    catptr->head = new_cat;

}

/**
 * insertion de la categorie a inserer a un index particulier
 * @param new_cat categorie a inserer
 * @param index position a inserer dans la liste
 */
void insert_category_index(struct Category* new_cat, int index) {
    if (index == 0 ) { insert_category_beginning(new_cat);}
    else if (index == catptr->nb_categories) { insert_category_last(new_cat);}
    else {
        struct Category *temp = catptr->head;
        while(index != 1) {
            temp = temp->next;
            index--;
        }
        new_cat->next = temp->next;
        temp->next = new_cat;
    }
    ++catptr->nb_categories;
}

/**
 * insertion de la categorie a la derniere position de la liste chainee
 * @param new_cat
 */
void insert_category_last(struct Category* new_cat) {
    new_cat->next = NULL;
    struct Category *temp = catptr->head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_cat;

}

/**
 * Ajout d'une recette dans une liste chainee de recettte appartenant a une categorie
 * @param recipe string nom de la recette
 * @param cat string nom de la categorie
 */
void add_recipe(char recipe[], char cat[]) {
    struct Recipe *new_recipe;
    new_recipe = (struct Recipe *) malloc(sizeof(struct Recipe));
    strcpy(new_recipe->recipe, recipe);
    struct Category *temp = catptr->head;
    while(temp != NULL) {
        if (strcmp(temp->category_name, cat) == 0) {
            break;
        }
        temp = temp->next;
    }
    insert_recipe(new_recipe, temp);
}

/**
 * Insertion dans la liste chainee de la recette
 * @param rec structure recette a inserer
 * @param cat structure categorie ou inserer
 */
void insert_recipe(struct Recipe* rec, struct Category* cat) {
    if(cat->head == NULL) { insert_recipy_head(rec, cat);}
    else {
        if (check_unique_recipe(rec, cat) != 0) {
            int index = find_index_recipe(rec, cat);
            if (index == 0 ) { insert_recipe_beginning(rec, cat);}
            else if (index == cat->nb_recipes) { insert_recipe_last(rec, cat);}
            else {insert_recipe_index(rec, cat, index);}
            ++cat->nb_recipes;
        }
    }
}

/**
 * Insertion de recette a un index specifique
 * @param rec structure recette a inserer
 * @param cat structure categorie ou inserer
 * @param index poisiton (categorie) ou inserer la recette
 */
void insert_recipe_index(struct Recipe* rec, struct Category* cat, int index) {
    struct Recipe *temp = cat->head;
    while(index != 1) {
        temp = temp->next;
        index--;
    }
    rec->next = temp->next;
    temp->next = rec;
}

/**
 * Insertion de la recette a lorsque head est null
 * @param rec structure recette a inserer
 * @param cat categorie ou inserer
 */
void insert_recipy_head (struct Recipe* rec, struct Category* cat) {
    rec->next = NULL;
    cat->head = rec;
    ++cat->nb_recipes;
}

/**
 * insertion de la recette a la place de la recette head
 * @param rec recette a inserer
 * @param cat maillon categorie ou inserer
 */
void insert_recipe_beginning (struct Recipe* rec, struct Category* cat) {
    rec->next = cat->head;
    cat->head = rec;
}

/**
 * insertion de la recette a la fin de la liste chainee
 * @param rec structure recette a insere
 * @param cat structure categorie ou inserer
 */
void insert_recipe_last (struct Recipe* rec, struct Category* cat) {
    rec->next = NULL;
    struct Recipe *temp = cat->head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = rec;

}

/**
 * verifie si la recette n'est pas deja presente dans la liste chainee
 * @param rec structure recette a inserer
 * @param cat structure categorie ou inserer
 * @return 0 si deja present
 */
int check_unique_recipe(struct Recipe* rec, struct Category* cat) {
    struct Recipe *temp = cat->head;
    while(temp != NULL) {
        if (strcmp(temp->recipe, rec->recipe) == 0) {
            return 0;
        }
        temp = temp->next;
    }
    return 1;
}

/**
 * Parcours la liste chainee de recette pour trouver a quelle position inserer la recette
 * @param rec strucure recette a inserer
 * @param cat structure category a inserer
 * @return
 */
int find_index_recipe(struct Recipe* rec, struct Category* cat) {
    int i = 0;
    struct Recipe *temp = cat->head;
    while (i < cat->nb_recipes) {
        if (strcmp(rec->recipe, temp->recipe) < 0) {
            break;//ou return i
        } else {
            i++;
            temp = temp->next;}
    }
    return i;
}

/**
 * fontion presente pour le deboguage. Print les listes chaines dans les deux sens : Une categorie a la fois avec
 * toutes ses recettes
 */
void printcats() {
    struct Category *temp1 = catptr->head;
    struct Recipe *temp2;
    while(temp1 != NULL) {
        printf("%s --->",temp1->category_name);
        temp2 = temp1->head;
        while(temp2 != NULL) {
            printf("(%s)",temp2->recipe);
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
        printf("\n");
    }
}