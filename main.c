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
