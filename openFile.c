/**
 * Librairie d'ouverture de fichier
 *
 *Cree par Jonathan Labelle
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include "openFile.h"

/**
 *
 * VARIABLES GLOBALES
 *
 */

FILE *f;
FILE *fw;
char output_stats[80];

/**
 * Execute l'ouverture du fichier founit en arg
 * @param argc nombre d'argument fournit
 * @param filePath chemin du fichier intrant
 */
void launch_open_file (int argc, char filePath[]) {

    check_argc(argc);
    open_file(filePath);
    check_file(f);
    rewind(f);

}

void open_write_file(char path[]) {
    fw = fopen(path, "w");
    if (f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier!\n");
        exit(errno);
    }
}

/**
 * Verificaiton si au moins un argument fournit par l'utilisateur
 * @param argc nombre d'argument
 */
void check_argc(int argc) {

    if (argc < 2) {
        errno = 1;
        printf("Erreur arguments invalides\n");
        exit(errno);
    }
}

/**
 * Ouverture du fichier
 * @param file chemin du fichier
 */
void open_file(char file[]) {

    f = fopen(file, "r");
    if (f == NULL) {
        errno = 2;
        printf("Erreur fichier introuvable\n");
        exit(errno);
    }
}

/**
 * Verificaitond de l'integrite du fichier
 * @param file fichier
 */
void check_file(FILE *file) {

    int isValid = 1;
    while (fgets(line, sizeof(line), file) && isValid ) {
        isValid = check_characters(line);
        if (isValid) {
            isValid = check_brackets(line);
        }
    }
    if (!(isValid)) {printf("%s", line);}
}

/**
 * Vericcation si autant de braquette ouvrante que fermante
 * @param lineToCheck ligne a verifier
 */

int check_brackets(char lineToCheck[]) {
    int left = 0, right = 0;
    int i = 0;
    char c = lineToCheck[0];
    while (c != '\0') {
        if (c == '[') {left++;}
        else if (c == ']') {right++;}
        i++;
        c = lineToCheck[i];
    }
    return (left == right);
}
/**
 * Verificaiton si tout les caracteres sont des caractere accepte
 * @param lineToCheck ligne a verifier
 */
int check_characters(char lineToCheck[]) {
    int isValid = 1;
    int i = 0;
    char c = lineToCheck[0];
    while (c != '\0') {
        if (!(isalnum(c) || c == '[' || c == ']' || c == 13 || c == 32 || c == 10 )) {
            printf("%d", c);
            isValid = 0;
        }
        i++;
        c = lineToCheck[i];
    }
    return isValid;
}