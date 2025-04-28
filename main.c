#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// definire globale
char pathIntrari[] = "/Users/bfbogdan/Library/Mobile Documents/com~apple~CloudDocs/University/First year/PP/c-project-menu-bfBogdan/c-project-menu-bfBogdan/intrari.txt";
char pathIesiri[] ="/Users/bfbogdan/Library/Mobile Documents/com~apple~CloudDocs/University/First year/PP/c-project-menu-bfBogdan/c-project-menu-bfBogdan/iesiri.txt";

typedef struct {
    char sursa[30];
    float suma;
    char data[15];
    char categorie[20];
} Venit;

typedef struct {
    char destinatar[30];
    float suma;
    char data[15];
    char categorie[20];
} Cheltuiala;

Cheltuiala cheltuieli[100];
Venit venituri[100];

void vizualizareMeniu(void) {
    printf("\n--- Sistem Contabilitate ---\n");
    printf("AdaugareVenituri - adaugarea de intrari financiare ale firmei\n");
    printf("AdaugareCheltuieli - adaugarea de iesiri financiare ale firmei\n");
    printf("VizualizareVenituri - vizualizarea tuturor veniturilor si detalilor aferente\n");
    printf("VizualizareCheltuieli - vizualizarea tuturor cheltuielilor si detalilor aferente\n");
    printf("help - Vezi lista de optiuni\n");
}

int preluareDate(char tipRequest[]){
    // citire fisier
    char linie[50];
    int primaLinie = 1, count = 0;
    // deschidere fisier
    FILE * pointerFisier;
    if (strcmp(tipRequest, "intrari") == 0){
        pointerFisier = fopen(pathIntrari, "r");
    }
    else{
        pointerFisier = fopen(pathIesiri, "r");
    }
    if (pointerFisier == NULL){
        printf("Eroare: fisierul nu poate fi accesat!");
        return -1;
    }
    else{
        while (fgets(linie, 50, pointerFisier)) {
            if (primaLinie == 1){
                primaLinie = 0;
                continue;
            }
            if(linie[0] != '\n') {
                linie[strcspn(linie, "\n")] = '\0';
                
                // stocare informatii
                if (strlen(linie) > 0) {
                    // extragem datele din linie
                    char *token = strtok(linie, ",");
                    // daca sunt venituri ...
                    if (strcmp(tipRequest, "intrari") == 0){
                        if (token != NULL) strncpy(venituri[count].sursa, token, sizeof(venituri[count].sursa) - 1);

                        token = strtok(NULL, ",");
                        if (token != NULL) venituri[count].suma = atof(token);

                        token = strtok(NULL, ",");
                        if (token != NULL) strncpy(venituri[count].data, token, sizeof(venituri[count].data) - 1);

                        token = strtok(NULL, ",");
                        if (token != NULL) strncpy(venituri[count].categorie, token, sizeof(venituri[count].categorie) - 1);
                    }
                    // daca sunt cheltuieli ...
                    else{
                        if (token != NULL) strncpy(cheltuieli[count].destinatar, token, sizeof(cheltuieli[count].destinatar) - 1);

                        token = strtok(NULL, ",");
                        if (token != NULL) cheltuieli[count].suma = atof(token);

                        token = strtok(NULL, ",");
                        if (token != NULL) strncpy(cheltuieli[count].data, token, sizeof(cheltuieli[count].data) - 1);

                        token = strtok(NULL, ",");
                        if (token != NULL) strncpy(cheltuieli[count].categorie, token, sizeof(cheltuieli[count].categorie) - 1);
                    }

                    count++;
                }
            }
        }
    }
    // inchidere fisier
    fclose(pointerFisier);
    return count;
}

void vizualizareVenituri(char categorieFiltru[], char filtru[]) {
    // antet pagina
    printf("---- AFISARE VENITURI ----\n");
    printf("\n");
    
    // definire structura fisier
    printf("Sursa, Suma, Data, Categorie\n");
    printf("-----------------------------\n");
    
    // stocare date venituri
    int count = preluareDate("intrari");
    if (count == -1){
        printf("Eroare afisare venituri!\n");
        return;
    }
    
    // afisare date
    int afiseaza;
    for (int i = 0; i < count; i++) {
        afiseaza = 0;
        unsigned long len = strlen(venituri[i].categorie);
        venituri[i].categorie[len - 1] = '\0';
        if (strcmp(categorieFiltru, "c") == 0){
            if(strcmp(venituri[i].categorie, filtru) == 0){
                afiseaza = 1;
        }
        }
        else if (strcmp(categorieFiltru, "d") == 0 && strcmp(venituri[i].data, filtru) == 0){
            afiseaza = 1;
        }
        else if (strcmp(categorieFiltru, "-") == 0){
            afiseaza = 1;
        }
        if (afiseaza == 1){
            printf("\033[1;34m%s\033[0m, \033[0;32m%.2f\033[0m RON, %s, \033[1;33m%s\033[0m;\n",
                   venituri[i].sursa,
                   venituri[i].suma,
                   venituri[i].data,
                   venituri[i].categorie
                   );
        }
    }
    
    // subsol pagina
    printf("\n");
    printf("---- FINAL AFISARE VENITURI ----\n");
    
}

void vizualizareCheltuieli(char categorieFiltru[], char filtru[]) {
    // antet pagina
    printf("---- AFISARE CHELTUIELI ----\n");
    printf("\n");
    
    // definire structura fisier
    printf("Destinatar, Suma, Data, Categorie\n");
    printf("-----------------------------\n");
    
    // stocare date venituri
    int count = preluareDate("iesiri");
    if (count == -1){
        printf("Eroare afisare cheltuieli!\n");
        return;
    }
    
    // afisare date
    int afiseaza;
    for (int i = 0; i < count; i++) {
        afiseaza = 0;
        unsigned long len = strlen(cheltuieli[i].categorie);
        cheltuieli[i].categorie[len - 1] = '\0';
        if (strcmp(categorieFiltru, "c") == 0){
            if(strcmp(cheltuieli[i].categorie, filtru) == 0){
                afiseaza = 1;
            }
        }
        else if (strcmp(categorieFiltru, "d") == 0 && strcmp(cheltuieli[i].data, filtru) == 0){
            afiseaza = 1;
        }
        else if (strcmp(categorieFiltru, "-") == 0){
            afiseaza = 1;
        }
        if (afiseaza == 1){
            printf("\033[1;34m%s\033[0m, \033[0;32m%.2f\033[0m RON, %s, \033[1;33m%s\033[0m;\n",
                cheltuieli[i].destinatar,
                cheltuieli[i].suma,
                cheltuieli[i].data,
                cheltuieli[i].categorie
            );
        }
        
    }
    
    // subsol pagina
    printf("\n");
    printf("---- FINAL AFISARE CHELTUIELI ----\n");
    
}

void adaugareVenituri(void) {
    char sursa[100], data[20], categoria[100], buffer[20], raspuns[5];
    float suma;
    
    // antet pagina
    printf("\n");
    printf("---- ADAUGARE VENIT ----\n");

    // input sursa venitului
    printf("Sursa venitului: ");
    fgets(sursa, sizeof(sursa), stdin);
    sursa[strcspn(sursa, "\n")] = '\0';

    // input suma + validare input
    printf("Suma (suma sa fie pozitiva): ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%f", &suma);
    if (suma < 0) {
        printf("Suma trebuie sa fie pozitiva.\n");
        return;
    }

    // input data
    printf("Data [DD-MM-YYYY]: ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = '\0';

    // input categoria venitului
    printf("Categoria: ");
    fgets(categoria, sizeof(categoria), stdin);
    categoria[strcspn(categoria, "\n")] = '\0';

    // descidere + scriere fisier
    FILE * pointerFisier = fopen(pathIntrari, "a");
    if (pointerFisier == NULL) {
        printf("Fisierul nu poate fi accesat.");
    } else {
        fprintf(pointerFisier, "%s,%.2f,%s,%s;\n", sursa, suma, data, categoria);
        fclose(pointerFisier);
        printf("\n---- VENIT ADAUGAT CU SUCCES ----\n");
        printf("Mai doriti sa adaugati un venit? (y/n): ");
        fgets(raspuns, sizeof(raspuns), stdin);
        raspuns[strcspn(raspuns, "\n")] = '\0';
        if (strcmp(raspuns, "y") == 0){
            adaugareVenituri();
        }
    }
}

void adaugareCheltuieli(void) {
    char sursa[100], data[20], categoria[100], buffer[20], raspuns[5];
    float suma;
    
    // antet pagina
    printf("\n");
    printf("---- ADAUGARE CHELTUIALA ----\n");

    // input sursa venitului
    printf("Destinatar: ");
    fgets(sursa, sizeof(sursa), stdin);
    sursa[strcspn(sursa, "\n")] = '\0';

    // input suma + validare input
    printf("Suma (suma sa fie pozitiva): ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%f", &suma);
    if (suma < 0) {
        printf("Suma trebuie sa fie pozitiva.\n");
        return;
    }

    // input data
    printf("Data [DD-MM-YYYY]: ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = '\0';

    // input categoria venitului
    printf("Categoria: ");
    fgets(categoria, sizeof(categoria), stdin);
    categoria[strcspn(categoria, "\n")] = '\0';

    // descidere + scriere fisier
    FILE * pointerFisier = fopen(pathIesiri, "a");
    if (pointerFisier == NULL) {
        printf("Fisierul nu poate fi accesat.");
    } else {
        fprintf(pointerFisier, "%s,%.2f,%s,%s;\n", sursa, suma, data, categoria);
        fclose(pointerFisier);
        printf("\n---- CHELTUIALA ADAUGATA CU SUCCES ----\n");
        printf("Mai doriti sa adaugati o cheltuiala? (y/n): ");
        fgets(raspuns, sizeof(raspuns), stdin);
        raspuns[strcspn(raspuns, "\n")] = '\0';
        if (strcmp(raspuns, "y") == 0){
            adaugareCheltuieli();
        }
    }
}

void cautare(void){
    char tipCautare[5], selectie[5], filtru[30];
    
    // antet pagina
    printf("\n");
    printf("---- CAUTARE ----\n");
    
    printf("Doriti sa cautati dupa intrare(in) sau iesire(ie)? (in/ie): ");
    fgets(tipCautare, sizeof(tipCautare), stdin);
    tipCautare[strcspn(tipCautare, "\n")] = '\0';
    
    printf("Doriti sa cautati dupa categorie(c) sau dupa data(d)? (c/d): ");
    fgets(selectie, sizeof(selectie), stdin);
    selectie[strcspn(selectie, "\n")] = '\0';
    
    if (strcmp(tipCautare, "in") == 0){
        if (strcmp(selectie, "c") == 0){
            printf("Introduceti categoria: ");
            fgets(filtru, sizeof(filtru), stdin);
            filtru[strcspn(filtru, "\n")] = '\0';
        }
        else if (strcmp(selectie, "d") == 0){
            printf("Introduceti data [DD-MM-YYYY]: ");
            fgets(filtru, sizeof(filtru), stdin);
            filtru[strcspn(filtru, "\n")] = '\0';
        }
        vizualizareVenituri(selectie, filtru);
    }
    else if (strcmp(tipCautare, "ie") == 0){
        if (strcmp(selectie, "c") == 0){
            printf("Introduceti categoria: ");
            fgets(filtru, sizeof(filtru), stdin);
            filtru[strcspn(filtru, "\n")] = '\0';
        }
        else if (strcmp(selectie, "d") == 0){
            printf("Introduceti data [DD-MM-YYYY]: ");
            fgets(filtru, sizeof(filtru), stdin);
            filtru[strcspn(filtru, "\n")] = '\0';
        }
        vizualizareCheltuieli(selectie, filtru);
    }
    else{
        printf("Optiune invalida! Va rugam selectati una dintre optiunile disponibile! (in/ie/c/d)");
    }
}

void prelucrareOptiuni(const char *option) {
    if (strcmp(option, "AdaugareVenituri") == 0) {
        adaugareVenituri();
    }
    else if (strcmp(option, "AdaugareCheltuieli") == 0) {
        adaugareCheltuieli();
    }
    else if (strcmp(option, "VizualizareVenituri") == 0) {
        vizualizareVenituri("-", "-");
    }
    else if (strcmp(option, "VizualizareCheltuieli") == 0) {
        vizualizareCheltuieli("-", "-");
    }
    else if (strcmp(option, "Cautare") == 0) {
        cautare();
    }
    else if (strcmp(option, "help") == 0) {
        vizualizareMeniu();
    }
    else {
        printf("Optiune lipsa! Pentru a vedea o lista cu toate comenzile accesibile folositi optiunea help!\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        vizualizareMeniu();
        return 1;
    }
    
    prelucrareOptiuni(argv[1]);
    return 0;
}
