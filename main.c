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
