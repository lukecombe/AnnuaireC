#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jsmn.h"

typedef int bool;
#define TRUE  1
#define FALSE 0

struct Contact
{
    char name[30];
    char firstname[30];
    char phonenumber[20];
    char address[100];
};

//fonction parcourir
//permet de parcourir l'annuaire
void browse(){
    // declaration de variable
    struct Contact users[20];
    int LineCount = 0;
    int car = 0;
    int curPos = 0;
    int contactNumber = 0;
    int choice=0;
    int c;
    bool stay = TRUE;
    bool suivant = FALSE;
    bool precedent = FALSE;

    FILE* file = fopen("C:\\Users\\Luke\\Documents\\Projets\\Annuaire\\Annuaire.txt","r");
    if (file != NULL){
        do
        {
            car = fgetc(file);
            if (car == '\n')
                LineCount++;
        } while(car != EOF);
        //printf("Nombre de lignes %d : ", LineCount);

        if (LineCount == 0){
            printf("Annuaire vide \n");
            //on sort de la fonction sans oublier de fermer le fichier
            fclose(file);
            return;
        }

        // on se repositionne en début de fichier
        fseek(file, 0, SEEK_SET);

        //remplissage du tableau
        for (curPos = 0; curPos < LineCount; curPos++)
        {
            fscanf(file, "%s %s %s %s", users[curPos].name, users[curPos].firstname, users[curPos].phonenumber, users[curPos].address);
        }

        while(stay) {
            //affichage du contact courant
            printf("contact %i sur %i : %s\t%s\t%s\t%s\n", contactNumber + 1, LineCount, users[contactNumber].name,
                   users[contactNumber].firstname, users[contactNumber].phonenumber, users[contactNumber].address);

            suivant = contactNumber < LineCount -1;
            //printf("\ncontactNumber : -%i-\n", contactNumber);
            //printf("\nLineCount : -%i-\n", LineCount);
            precedent = contactNumber > 0;
            //printf("suivant = %i\n", suivant);
            //printf("precedent = %i\n", precedent);

            //s'il existe un contact suivant
            if (suivant) {
                //s'il existe un contact précédent
                if (precedent) {
                    printf("Entrez 'p' pour precedent, 's' pour suivant, 'q' pour quitter la navigation\n");
                    //s'il n'existe pas de contact précédent
                } else {
                    printf("Aucun precedent. Entrez 's' pour suivant, 'q' pour quitter la navigation\n");
                }
                //s'il n'existe pas de contact suivant
            } else {
                //s'il existe un contact précédent
                if (precedent) {
                    printf("Pas de suivant. Entrez 'p' pour precedent, 'q' pour quitter la navigation\n");
                    //s'il n'existe pas de contact précédent
                } else {
                    printf("Pas de suivant, pas de precedent. Entrez 'q' pour quitter la navigation\n");
                }
            }

            printf("> ");
            while ((c = getchar()) != '\n' && c!= EOF);
            c = getchar();
            //printf("\nwhile - le choix est : -%i-\n", c);

            //on teste la valeur du caractère ASCII
            if (c == 112) choice = 1;
            if (c == 115) choice = 2;
            if (c == 113) choice = 3;

            switch (choice) {
                case 1:
                    //printf("precedent\n");
                    if (precedent) contactNumber--;
                    break;
                case 2:
                    //printf("suivant \n");
                    if (suivant) contactNumber++;
                    break;
                case 3:
                    //printf("quitter\n");
                    stay = FALSE;
                    break;
                default:
                    printf("Mauvaise entree\n");
                    break;
                }
            fclose(file);
        }
    } else{
        printf("browse:Erreur ouverture ficher\n");
    }
}


void add_contact(){
    // declaration de variables
    char name[30];
    char firstname[30];
    char phonenumber[20];
    char address[100];

    //read input
    printf("Veuillez rentrer le nom du nouveau contact :\n");
    while( getchar() != '\n');
        scanf("%s", &name);

    printf("Veuillez rentrer le prenom du nouveau contact :\n");
    while( getchar() != '\n');
        scanf("%s", &firstname);

    printf("Veuillez rentrer le telephone du nouveau contact :\n");
    while( getchar() != '\n');
        scanf("%s", &phonenumber);

    printf("Veuillez rentrer l adresse du nouveau contact :\n");
    while( getchar() != '\n');
        scanf("%s", &address);

    //write new entry in file
    FILE* file = fopen("C:\\Users\\Luke\\Documents\\Projets\\Annuaire\\Annuaire.txt","a");
    fprintf(file, "%s %s %s %s\n",name,firstname,phonenumber,address);

    fclose(file);
}


void search_contact()
{
  // declaration de variables
    struct Contact users[20];
    int LineCount = 0;
    int car = 0;
    int curPos = 0;
    int contactNumber = 0;
    int c = 0;
    char name = "";
    bool keepOnSearching = TRUE;

//    printf("search_contact\n");

    //ouverture du fichier en lecture/écriture
  FILE* file = fopen("C:\\Users\\Luke\\Documents\\Projets\\Annuaire\\Annuaire.txt","r");
    if (file != NULL){
        do
        {
            car = fgetc(file);
            if (car == '\n')
                LineCount++;
        } while(car != EOF);
        printf("Nombre de lignes %d : ", LineCount);

        if (LineCount == 0){
            printf("Annuaire vide \n");
            //on sort de la fonction sans oublier de fermer le fichier
            fclose(file);
            return;
        }

        // on se repositionne en début de fichier
        fseek(file, 0, SEEK_SET);

        //remplissage du tableau
        for (curPos = 0; curPos < LineCount; curPos++)
        {
            fscanf(file, "%s %s %s %s", users[curPos].name, users[curPos].firstname, users[curPos].phonenumber, users[curPos].address);
            //printf("contact %i sur %i : %s\t%s\t%s\t%s\n", curPos + 1, LineCount, users[curPos].name,
                   //users[curPos].firstname, users[curPos].phonenumber, users[curPos].address);
        }

        // on ne recherche que par le nom
        //TO DO ajouter d'autres critères si nécessaire
        //on demande le nom
        printf("Veuillez rentrer le nom du contact a rechercher :\n");
        while( getchar() != '\n');
            scanf("%s", &name);

        //printf("recherche - name = -%s-\n", &name);

        //on parcourt le tableau pour rechercher une entree correspondante
        while ((keepOnSearching) && (contactNumber < LineCount)) {
            //printf("recherche - while - name -%s-\n", &name);
            //printf("recherche - while - users[contactNumber].name -%s-\n", users[contactNumber].name);
            if (strcmp(users[contactNumber].name, &name) == 0){
                //printf("recherche - users[contactNumber].name = -%s-", users[contactNumber].name);
                //printf("TROUVE\n");
                keepOnSearching = FALSE;
                printf("contact TROUVE %i sur %i : %s\t%s\t%s\t%s\n\n", contactNumber + 1, LineCount, users[contactNumber].name,
                       users[contactNumber].firstname, users[contactNumber].phonenumber, users[contactNumber].address);
            } else {
                contactNumber++;
            }
        }
    } else {
        printf("browse:Erreur ouverture ficher\n");
    }
  fclose(file);
  }


void deleteAllContacts() {
    //printf("deleteAllContacts\n");
    FILE* file = fopen("C:\\Users\\Luke\\Documents\\Projets\\Annuaire\\Annuaire.txt", "w+");
    fclose(file);
}


void main() {
    int choice;

//    jsmn_parser myJsmnParser;
//    jsmntok_t tokens[10];

 //   jsmn_init(&myJsmnParser);

 //   char truc[] = "{ \"name\" : \"Jack\", \"age\" : 27 }";

   // jsmn_parse(&myJsmnParser, truc, strlen(truc), tokens, 10);

   bool stay = TRUE;

   while(stay) {
       printf("Entrez le numero correspondant a l option que vous souhaitez effectuer :\n");
       printf("1 parcourir l annuaire\n");
       printf("2 ajouter un nouveau contact\n");
       printf("3 rechercher un contact\n");
       printf("4 supprimer l integralite des contacts presents dans l annuaire\n");
       printf("5 quitter l application\n");
       printf("> ");

       scanf("%i", &choice);
       //printf("le choix est : %i", choice);

       switch (choice) {
           case 1:
               //printf("parcourir\n");
               browse();
               break;
           case 2:
               //printf("ajouter \n");
               add_contact();
               break;
           case 3:
               //printf("rechercher\n");
               search_contact();
               break;
           case 4:
               //printf("supprimer\n");
               deleteAllContacts();
               break;
           case 5:
               //printf("quitter\n");
               stay = FALSE;
               break;
           default:
               printf("Mauvaise entree\n");
               break;

       }
   }
}
