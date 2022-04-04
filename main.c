#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "libros.h"
#define MAXCHAR 1000
#define LENGHT 250

#define READ_ONLY "r"
#define WRITE_ONLY "w"

void searchBook(FILE *fp, char **);
void deleteRow(FILE *fp, FILE *fp2);  // va a agregar una columna con unos al final de cada fila para identificar que libros hemos borrado
void editBook(FILE *fp, FILE *fp2, char argv[]);
void addBook(FILE *fp, FILE *fp2, char **, char argv[], char argv2[]);

FILE * openingFile(char *filename){
    FILE *fp;
    fp = fopen(filename,"r+");  // r+ para leer y escribir en el archivo
    return fp;
}


int main(int argc, char *argv[] ) {
    char *first_row[9] = {"Titulo", "Autor", "Año", "Estante", "Sección", "Piso", "Edificio", "Sede", "\0"};
    char row[MAXCHAR];
    FILE *fp = openingFile(argv[1]);
    if (fp == NULL) {
        perror("Opening file");
        return -1;
    }

    FILE *fp2 = openingFile(argv[2]);
    if (fp2 == NULL) {
        perror("Opening file");
        return -1;
    }

    while (feof(fp) != true) {
        fgets(row, MAXCHAR, fp);
        fprintf(fp2, "%s", row);
    }


    int option;
    do
    {
        printf( "\n   1. Agregar libros\n");
        printf( "   2. Quitar libros\n");
        printf( "   3. Editar libros\n");  // cambiar sede, sección o piso
        printf( "   4. Buscar\n");
        printf( "   5. Salir.\n" );
        printf( "   Introduzca opción (1-5): \n");

        scanf("%d", &option);
        if (option == 1) {
            addBook(fp, fp2, first_row, argv[2], argv[1]);
        }
        if (option == 2) {
            deleteRow(fp,fp2);
        }
        if (option == 3) {
            editBook(fp, fp2, argv[1]);
        }
        if (option == 4) {
            searchBook(fp2, first_row);
        }


    } while ( option != 5 );

    fclose(fp);
    fclose(fp2);
    return 0;

}


void addBook(FILE *fp, FILE *fp2, char **first_row, char *argv, char *argv2) {
    char row[MAXCHAR];
    char *token;
    char add[10][100];
    for (int i = 0; i < 8; i++) {
        printf("\n%s del libro: ", first_row[i]);
        fpurge(stdin);  // para limpiar el buffer de entrada stdin
        scanf("%s", &add[i][100]);
        fpurge(stdin);
    }

    while (feof(fp) != true) {
        fgets(row, MAXCHAR, fp);
        fprintf(fp2, "%s", row);
    }
    fprintf(fp2, "%s", "\n");

    for (int j = 0; j < 8; j++) {
        fprintf(fp2, "%s", add[j]);
        if (j != 8) {

            fprintf(fp2, "%s", ",");
        }
        else {
            fprintf(fp2, "%s", "");
        }
        //printf("%s\n", add[j]);
        fclose(fp);
        fclose(fp2);

        FILE *fp = openingFile(argv);
        FILE *fp2 = openingFile(argv2);

        while (feof(fp2) != true) {
            fgets(row, MAXCHAR, fp2);
            fprintf(fp, "%s", row);
        }

    }
    fclose(fp);
    fclose(fp2);
}



void editBook(FILE *fp, FILE *fp2, char *argv) {
    char title[LENGHT];
    char parameter[LENGHT];
    char *token;

    printf("\nIngresa el título del libro que quieres editar: ");
    fpurge(stdin);  // para limpiar el buffer de entrada stdin
    fgets(title, LENGHT, stdin);
    strtok(title, "\n");

    printf("Que parámetro quieres cambiar (ejemplo: sección): ");
    fpurge(stdin);
    fgets(parameter, LENGHT, stdin);
    strtok(parameter, "\n");

    bool gate_title = false;
    bool gate_par = false;
    bool once = true;
    int position;

    while (feof(fp) != true) {


        while (once) {
            char *row = malloc(sizeof(char) * MAXCHAR);
            fgets(row, MAXCHAR, fp);
            //fprintf(fp2, "%s", row);
            for (int i = 0; i < 8; i++) {
                token = strtok(row, ",");
                row = strtok(NULL, "\n");
                if (strcmp(token, parameter) == 0) {
                    position = i;
                    gate_par = true;
                }
            }
            if (gate_par == false) {
                perror("No se encontró el parámetro que quieres cambiar");
            }
            once = false;
        }

        if (gate_par) {
            char *row = malloc(sizeof(char) * MAXCHAR);
            fgets(row, MAXCHAR, fp);
            token = strtok(row, ",");

            for (int j = 0; j < 7; ++j) {
                if (j == 0) {
                    if (strcmp(row, title) == 0) {
                        gate_title = true;
                    }
                }
            }
            free(row);
        }

        if (gate_par == true && gate_title == true) {
            fclose(fp);
            FILE *fp = openingFile(argv);

            while (feof(fp) != true) {
                char *row = malloc(sizeof(char) * MAXCHAR);
                fgets(row, MAXCHAR, fp);
                fprintf(fp2, "%s", row);

                for (int j = 0; j < 8; ++j) {
                    token = strtok(row, ",");
                    if (j == 0) {
                        if (strcmp(row, title) == 0) {
                            for (int k = 0; k <= position; k++) {
                                row = strtok(NULL, "\n");
                                token = strtok(row, ",");

                                if (k == position-1) {
                                    fprintf(fp2, "%s", token);
                                    char value[LENGHT];
                                    printf("Por cual valor lo quieres cambiar: ");
                                    fpurge(stdin);
                                    fgets(value, LENGHT, stdin);
                                    strtok(value, "\n");

                                    fprintf(fp2  , "%s", value);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (gate_title == false) {
        perror("No se ha encontrado el título");
    }
}

void deleteRow(FILE *fp, FILE *fp2) {
    char title[LENGHT];
    char *row = malloc(sizeof(char) * MAXCHAR);
    char *token;
    char *rest;
    bool gate = false;

    printf("\nIngresa el título del libro que quieres eliminar: ");
    fpurge(stdin);  // para limpiar el buffer de entrada stdin
    fgets(title, LENGHT, stdin);
    strtok(title, "\n");

    while (feof(fp) != true) {
        //obtiene la linea siguiente
        fgets(row, MAXCHAR, fp);
        token = strtok(row, ",");
        rest = strtok(NULL, "\n");

        if (strcmp(token, title) != 0) {
            fprintf(fp2, "%s,%s", token, rest);
        }
        else gate = true;
    }
    free(row);
    if (gate == false) printf("No hemos encontrado el libro que quiere eliminar :(\n");
    else printf("Hemos encontrado y eliminado correctamente el libro!!\n");
}


void searchBook(FILE *fp, char **first_row) {
    char row[MAXCHAR];
    char *token;
    char title[LENGHT];
    int j = 0;
    int i;

    printf("\nIngresa el título del libro que quieres buscar:");
    fpurge(stdin);  // para limpiar el buffer de entrada stdin
    fgets(title, LENGHT, stdin);
    strtok(title, "\n");

    bool found = false;
    while (feof(fp) != true) {

        bool found2 = false;
        //obtiene la linea siguiente
        fgets(row, MAXCHAR, fp);
        token = strtok(row, ",");

        for (i = 0; i < 7; ++i) {
            if (i == 0) {
                if (strcmp(row, title) == 0) {
                    printf("Encontramos el libro!\n");
                    found = true;
                    found2 = true;
                }
            }
            if (found2 == true) {
                while (strcmp(first_row[j], "\0") != 0) {
                    printf("%s: %s\n", first_row[j], token);
                    token = strtok(NULL, ",");
                    j++;
                }
            }
        }
    }
    if (found == false) {
        printf("Lo sentimos, su libro no se ha encontrado.\n");
    }
}

