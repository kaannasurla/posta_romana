#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int id;
    char *nume;
} cartier; /*structura pentru cartier cu campurile aferente*/

typedef struct{
    int id;
    int adresa[18];  
    int idCartier;  
    int strada;     
    int numar;       
    int prioritate;
    float masa;
    char *mesaj;
    int codificare_mesaj;
} pachet; /*structura pentru pachet cu campurile aferente*/

typedef struct{
    int id;
    int nrPachete;
    pachet *vector_pachete;
} postas; /*structura pentru postas cu campurile aferente*/

void citire_date(cartier **cartiere, pachet **pachete, int *nrC, int *nrP){  /*functia de la cerinta 1.1*/
    int x, y; /*variabilele din primul bloc al instructiunii for*/
    scanf("%d", nrC); /*citesc numarul de cartiere*/
    *cartiere = (cartier*)malloc((*nrC) * sizeof(cartier)); /*aloc spatiu atat cat e necesar pentru cartier*/
    char nume_cartier[100]; 
    for (x = 0; x < (*nrC); x++){
        (*cartiere)[x].id = x;
        scanf("%s", nume_cartier);
        (*cartiere)[x].nume = (char*)malloc(strlen(nume_cartier)*sizeof(char));
        nume_cartier[strcspn(nume_cartier, "\n")] = '\0';
        strcpy((*cartiere)[x].nume, nume_cartier); 
    }
    scanf("%d", nrP); /*citesc numarul de pachete*/
    *pachete = (pachet*)malloc((*nrP) * sizeof(pachet)); /*aloc spatiu atat cat e necesar pentru pachet*/
    for (x = 0; x < *nrP; ++x) {
    char buffer[100];
    (*pachete)[x].id = x;
    for (y = 0; y < 18; ++y) {
        if (scanf("%d", &(*pachete)[x].adresa[y]) != 1) {
            fprintf(stderr, "input invalid\n");
        }
    }
    if (scanf("%d", &(*pachete)[x].prioritate) != 1) {
        fprintf(stderr, "input invalid\n");
    }
    if (scanf("%f", &(*pachete)[x].masa) != 1) {
        fprintf(stderr, "input invalid\n");
    }
    getc(stdin); /*epuizeaza newline*/
    if (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        (*pachete)[x].mesaj = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        if ((*pachete)[x].mesaj == NULL) {
            fprintf(stderr, "eroare la alocarea memoriei\n");
        }
        strcpy((*pachete)[x].mesaj, buffer);
    } else {
        fprintf(stderr, "eroare la citire\n");
    }
}
}

void extragere_adresa(pachet **pachete, int *nrP){ /*functia de la cerinta 1.2*/
    int i, j;
    for (i = 0; i < (*nrP); i++) { /*initializez id-ul cartierului, strada si numarul cu 0.*/
        (*pachete)[i].idCartier = 0; 
        (*pachete)[i].strada = 0;
        (*pachete)[i].numar = 0;
        for (j = 0; j < 5; j++) { /*folosesc operatorii pe biti, mutand la stanga in fct de numarul de biti*/
            (*pachete)[i].idCartier=((*pachete)[i].idCartier)+((*pachete)[i].adresa[j] << (4 - j)); /*primele 5 pozitii reprezinta idCartier*/
        }
        for (j = 5; j < 10; j++) {
            (*pachete)[i].strada=((*pachete)[i].strada)+((*pachete)[i].adresa[j] << (9 - j)); /*urmatoarele 5 pozitii reprezinta strada*/
        }
        for (j = 10; j < 18; j++) {
            (*pachete)[i].numar=((*pachete)[i].numar)+((*pachete)[i].adresa[j] << (17 - j)); /*urmatoarele 8 pozitii reprezinta numarul*/
        }
    }
}

void distribuie_pachete(pachet* pachete, postas** postasi, int nrP, int nrC){ /*functia de la cerinta 1.3*/
    *postasi = malloc(sizeof(postas) * nrC); /*aloc spatiu pentru postasi, altfel segfault*/
    int i,j;
    for(i = 0; i < nrC; i++){
        postas *activ = &(*postasi)[i];
        (*activ).id = i;
        (*activ).nrPachete = 0;
        (*activ).vector_pachete = malloc(nrP * sizeof(pachet));
        for(j = 0; j < nrP; j++){
            if ((*activ).id == pachete[j].idCartier) {
                (*activ).vector_pachete[(*activ).nrPachete++] = pachete[j];
            }
        }
    }
}
void bubblesort(postas* postasi){ /*functia de la cerinta 1.4 */
    pachet aux;
    int a, b;
    int nrPachete = (*postasi).nrPachete;
    pachet* vector = (*postasi).vector_pachete;
    /* sortare dupa prioritate (descrescator) */
    for (a = 0; a < nrPachete - 1; a++) {
        for (b = 0; b < nrPachete - a - 1; b++) {
            if (vector[b].prioritate < vector[b + 1].prioritate) {
                aux = vector[b];
                vector[b] = vector[b + 1];
                vector[b + 1] = aux;
            }
        }
    }
    /* sortare dupa masa (descrescator) daca prioritatea este egala*/
    for (a = 0; a < nrPachete - 1; a++) {
        for (b = 0; b < nrPachete - a - 1; b++) {
            if (vector[b].prioritate == vector[b + 1].prioritate){
                if(vector[b].masa < vector[b + 1].masa){
                    aux = vector[b];
                    vector[b] = vector[b + 1];
                    vector[b + 1] = aux;
                }
                
            }
        }
    }
}
    /* Nu se face sortare dacă prioritatea, dar si masa sunt egale*/

/*in cadrul cerintei 1.5 voi implementa doua functii*/
void functia_prim(char *text) { 
    /*Functie care reorganizeaza cuvintele în ordine inversa si elimina punctuaia*/
    text[strlen(text)] = '\0';
    char tmp[100][100];
    char *token;
    int contor = 0;
    /*Separare cuvinte folosind delimitatori*/
    for (token = strtok(text, " ,.;:?"); token!= NULL; token = strtok(NULL, " ,.;:?!")) {
        strncpy(tmp[contor], token, sizeof(tmp[contor]) - 1);
        contor++;
    }
    /*Reconstruire text în ordine invers*/ 
    text[0] = '\0'; 
    while (contor-- > 0) {
        strcat(text, tmp[contor]);
    }
}

void cod_mesaj(pachet *pachete) { 
    /* Funcție pentru calcularea codului mesajului */
    int contor = 0; 
    (*pachete).codificare_mesaj = 0; /* Inițializare cu zero */
    while ((*pachete).mesaj[contor]!= '\0') { 
        (*pachete).codificare_mesaj += (int)((*pachete).mesaj[contor]) * contor; 
        contor++; 
    } 
    int factor = (((*pachete).strada) * ((*pachete).numar)) + 1; 
    if (factor != 0) { 
        (*pachete).codificare_mesaj = (*pachete).codificare_mesaj % factor; 
    }
}
/*in cadrul cerintei 1.6 voi implementa doua functii*/
int modelare_cod(int identif, int cod_initial) {
    int iter, vector_factori[33] = {0}; /*initializez vectorul direct cu 0*/
    if (identif == 0 || identif == 1) {
        return cod_initial ^ (1 << identif); /*aplic XOR pentru cazurile speciale*/
    }
    for (iter = 2; iter <= identif; iter++){
        while (identif % iter == 0) {
            identif = identif / iter;
            vector_factori[iter] = 1; // Marchez pozitiile corespondente factorilor primi
        }
    }
    for (iter = 2; iter < 33; iter++) {
        if (vector_factori[iter]) {
            cod_initial = cod_initial ^ (1 << iter); // Realizez operatia XOR pe pozitiile factorilor
        }
    }
    return cod_initial;
}
void operatie_cod(postas* postasi) {
    int id = (*postasi).id;
    int i;
    int aux;
    int cifra1 = id % 10;
    int cifra2 = id / 10;

    for (i = 0; i < (*postasi).nrPachete; i++) {
        aux = (*postasi).vector_pachete[i].codificare_mesaj;

        while (aux) {
            int cifra_curenta = aux % 10;

            if ((id <= 9 && cifra_curenta == id) || 
                (id > 9 && (cifra_curenta == cifra1 || cifra_curenta == cifra2))) {

                (*postasi).vector_pachete[i].codificare_mesaj = modelare_cod((*postasi).id, (*postasi).vector_pachete[i].codificare_mesaj);
                break;
            }

            aux = aux / 10;
        }
    }
}
float punctaj_postas(int* initial, postas* postasi, int nrPachete){ /*functia de la cerinta 2.2*/
    float punctaj = 0;
    int i;
    for (i = 0; i < nrPachete; ++i) {
        if (initial[i] == (*postasi).vector_pachete[i].codificare_mesaj) {
            punctaj += 1.0f / nrPachete;
        } else {
            punctaj += 0.0f;
        }
    }
    return punctaj;
}

int main(){ /*functia main o utilizez pentru apelul functiilor din cerinte si afisarile conform outputului dorit*/
    int i, j, task;
    scanf("%d", &task);
    int nrC, nrP;
    pachet *pachete;
    cartier *cartiere;
    postas *postasi;
    citire_date(&cartiere, &pachete, &nrC, &nrP);
    /*obs:alternativa la if(cerinta) ar fi switch*/
    if(task == 1){ /*afisare conform cerintei 1*/
        for(i = 0; i < nrC; i++){
            printf("%d %s\n", cartiere[i].id, cartiere[i].nume);
        }
        for(i = 0; i < nrP; i++){
            printf("%d\n", pachete[i].id);
            for(j = 0; j < 17; j++){
                printf("%d ", pachete[i].adresa[j]); 
            }
            printf("%d\n", pachete[i].adresa[17]); /*important:am adaugat aceasta afisare pentru a nu aparea spatiu dupa ultimul element*/
            printf("%d %.3f\n", pachete[i].prioritate, pachete[i].masa);
            printf("%s\n", pachete[i].mesaj); /*string*/
        }
    }
    extragere_adresa(&pachete, &nrP);
    if(task == 2){
        int i;
        for(i=0;i<nrP;i++){
            printf("%d\n", pachete[i].id);
            printf("%d %d %d\n",pachete[i].idCartier, pachete[i].strada, pachete[i].numar);
        }
    }
    distribuie_pachete(pachete, &postasi, nrP, nrC);

if (task == 3) {
    distribuie_pachete(pachete, &postasi, nrP, nrC);
    int indexPostas;
    int idxPachet;
    for (indexPostas = 0; indexPostas < nrC; ++indexPostas) {
        printf("%d %d\n", postasi[indexPostas].id, postasi[indexPostas].nrPachete);

        if (postasi[indexPostas].nrPachete > 0) {
            for (idxPachet = 0; idxPachet < postasi[indexPostas].nrPachete; ++idxPachet) {
                printf("%d", postasi[indexPostas].vector_pachete[idxPachet].id);

                // Evităm spațiu suplimentar la final
                if (idxPachet < postasi[indexPostas].nrPachete - 1) {
                    printf(" ");
                }
            }
            printf("\n");
        }
    }
}
    for (i = 0; i < nrC; i++) {
        bubblesort(&postasi[i]);
    }
    if (task == 4) { /*afisare conform task 4*/
    int idx = 0;
    while (idx < nrC) {
        printf("%d %d\n", postasi[idx].id, postasi[idx].nrPachete);
        if (postasi[idx].nrPachete != 0) {
            int pachet_idx = 0;
            while (pachet_idx < postasi[idx].nrPachete - 1) {
                printf("%d ", postasi[idx].vector_pachete[pachet_idx].id);
                pachet_idx++;
            }
            printf("%d", postasi[idx].vector_pachete[postasi[idx].nrPachete - 1].id);
            printf("\n");
        }
        idx++;
    }
}
int j_idx = 0;
while (j_idx < nrC) {
    int i_idx = 0;
    while (i_idx < postasi[j_idx].nrPachete) {
        functia_prim(postasi[j_idx].vector_pachete[i_idx].mesaj);
        cod_mesaj(&postasi[j_idx].vector_pachete[i_idx]);
        i_idx++;
    }
    j_idx++;
}
if (task == 5) { // Afisare conform task 5
    int idx = 0;
    while (idx < nrC) {
        printf("%d %d\n", postasi[idx].id, postasi[idx].nrPachete);
        int pachet_idx = 0;
        while (pachet_idx < postasi[idx].nrPachete) {
            if (postasi[idx].nrPachete != 0) {
                printf("%d %d\n", postasi[idx].vector_pachete[pachet_idx].id, postasi[idx].vector_pachete[pachet_idx].codificare_mesaj);
            }
            pachet_idx++;
        }
        idx++;
    }
}
int var = 0;
int cod_initial[100][100]; // matrice pentru a stoca codurile initiale ale pachetelor
int idx_postas = 0;
while (idx_postas < nrC) {
    int numar_pachete = postasi[idx_postas].nrPachete;
    int idx_pachet = 0;
    while (idx_pachet < numar_pachete) {
        cod_initial[idx_postas][idx_pachet] = postasi[idx_postas].vector_pachete[idx_pachet].codificare_mesaj;
        var++;
        idx_pachet++;
    }
    idx_postas++;
}
int postas_idx = 0;
while (postas_idx < nrC) {
    operatie_cod(&postasi[postas_idx]);
    postas_idx++;
}
if (task == 6) { /*afisare conform task 6*/
    int idx_postas = 0;
    while (idx_postas < nrC) {
        printf("%d %d\n", postasi[idx_postas].id, postasi[idx_postas].nrPachete);

        if (postasi[idx_postas].nrPachete > 0) {
            int pachet_idx = 0;
            while (pachet_idx < postasi[idx_postas].nrPachete) {
                printf("%d %d\n", postasi[idx_postas].vector_pachete[pachet_idx].id, postasi[idx_postas].vector_pachete[pachet_idx].codificare_mesaj);
                pachet_idx++;
            }
        }
        idx_postas++;
    }
}
if (task == 7) { /*afisare conform task 7*/
    int postas_idx = 0;
    while (postas_idx < nrC) {
        float scor_calculat = punctaj_postas(cod_initial[postas_idx], &postasi[postas_idx], postasi[postas_idx].nrPachete);
        printf("%d %.3f\n", postasi[postas_idx].id, scor_calculat);
        postas_idx++;
    }
}
return 0;
}