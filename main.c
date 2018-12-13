#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jsmn.h"

typedef int bool;
#define TRUE  1
#define FALSE 0

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
    FILE* file = fopen("C:\\Users\\Luke\\Documents\\Projets\\Annuaire\\Annuaire.csv","a");
    fprintf(file, "\n%s;%s;%s;%s",name,firstname,phonenumber,address);
  //  char c;
   // do{
    //    c = fgetc(file);
    //    printf("%c", c);
   // }
  //  while (c != EOF);

    fclose(file);
   // return 0 ;

}

//void parcourir() {

  //  FILE* file = fopen("C:\\Users\\Luke\\Documents\\Projets\\Annuaire\\Annuaire.csv", "r+");
  void search_contact()
  {
      // declaration de variables
      char name[30];
      int TAILLE_MAX=25 ;
      char chaine[TAILLE_MAX];
      int offset = 0;

      //ouverture du fichier en lecture seule
      FILE* file = fopen("C:\\Users\\Luke\\Documents\\Projets\\Annuaire\\Annuaire.csv","r");
      // on ne recherche que par le nom
      //TO DO ajouter d'autres critères si nécessaire
      //on demande le nom
      printf("Veuillez rentrer le nom du nouveau contact :\n");
      while( getchar() != '\n');
        scanf("%s", &name);

        rewind(file);
        if(fgets(chaine,TAILLE_MAX,file)!=NULL)
        {
          strlwr(chaine);
          strlwr(name);
          if(strstr(chaine,name)!=NULL)
          {
              printf("Donnee non trouve\n");
          }
          else
          {
              offset = fseek(file,1,SEEK_SET);
              printf("Le decalage est de %i\n", offset);
          }
        }
      fclose(file);
      }





//}

void supprimer() {

    FILE* file = fopen("C:\\Users\\Luke\\Documents\\Projets\\Annuaire\\Annuaire.csv", "w+");
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
               printf("parcourir\n");
               break;
           case 2:
               printf("ajouter \n");
               add_contact();
               break;
           case 3:
               printf("rechercher\n");
               search_contact();
               break;
           case 4:
               printf("supprimer\n");
               supprimer();
               break;
           case 5:
               printf("quitter\n");
               stay = FALSE;
               break;
           default:
               printf("Mauvaise entree\n");
               break;

       }
   }
}
