#include <stdlib.h>
#include <string.h>
#include "afficherData.h"
#include "utilsP.h"

void Etape_finale (int i, char *temp) {
  if (i%16) {
    int tmp, ip;
    ip = i;
    if (i%16<=4) tmp = 4;
    else if (i%16<=8) tmp = 3;
    else if (i%16 <= 12) tmp = 2;
    else tmp = 1;
    while (i%16) {
      printf("  ");
      i++;
    }
    mettre_espace(tmp);
    for (int j = 0; j<ip%16; j++) printf("%c",temp[j]);
  }
  else {
    printf(" ");
    for (int j = 0; j<16; j++) printf("%c",temp[j]);
  }
}

void Recup_Valeurs (int i, int indice, char *val ,char *temp, FILE *f, Elf32_Shdr *s) {
  if(!fseek(f, s[indice].sh_offset + i , SEEK_SET)) {
    if (!fread(val, 1, 1, f)) exit(0);
    *val &= 0xff;
    // Si la valeur n'est pas un caractère ascii connu on affiche un point
    //(code 46)
    if (*val >= 127 || *val < 32) temp[i%16] = 46;
    else temp[i%16] = *val;
  }
  else exit(0);
}

void test_espace (int i, char *temp) {
  // affichage d'un espace tous les 4 octets
  if (!(i%4) && i) printf(" ");
  // affichage des valeurs tous les 16 octets puis affichage de l'adresse
  if (!(i%16) && i) {
    for (int j = 0; j<16; j++) printf("%c",temp[j]);
    printf("\n  0x%08x ",i);
  }
  // On vérifie dans les deux conditions que nous ne sommes pas au début
  // (Et donc i vaut 0), il n'y a rien à afficher dans ce cas
}

void affiche_Data (FILE *f, int indice, char * ANT, Elf32_Ehdr ehdr, Elf32_Shdr *s) {
  int i;
  i = 0;
  // On vérifie que l'indice donné existe
  if (ehdr.e_shnum <= indice) {
   printf("La section '%d' n'existe pas ", indice);
   return;
  }
  int adr = s[indice].sh_offset;
  int size = s[indice].sh_size;
  char val;
  adr ++;
  // Si la taille de la section n'est pas vide
  if (size) {
    printf("Hex dump of section '%s' :\n", ANT + s[indice].sh_name);
    i = 0;
    char temp[16];
    printf("  0x%08x ",i);
    while (i < size) {
      //On vérifie et rajoute des espaces nécessaires, on gère aussi l'affichage
      //Des valeurs ascii en caractère.
      test_espace(i,temp);
      //Recuperation de la valeur ascii courante
      Recup_Valeurs(i, indice, &val, temp, f, s);
      printf("%02x", val & 0xff);
      i ++;
    }
    Etape_finale(i, temp);
    // On calcul les derniers espaces à calculer et on affiche les dernières
    //valeurs
  }
  else printf("La section '%s' est vide", ANT + s[indice].sh_name);
}

void initData (FILE *f, char *argv) {
  // Initialisation
  Elf32_Ehdr ehdr;
  Elf32_Shdr *s = initS(f, &ehdr);
  //Récupération de la table des noms
  char *ANT = Recuperer_Table_Noms(f, ehdr, s);
  if (ANT == NULL){
    printf("Impossible d'afficher la table des symboles \n");
    return;
  }
  int arg2 = Recuperer_Index_Nom(argv, ANT, ehdr, s);
  // On récupère le numéro de la section associé à l'argument donné
  if (arg2 != -1) affiche_Data(f, arg2, ANT, ehdr, s);
  // Si aucun résultat n'est donné l'argument est un entier
  // on vérifie avec atoi sans oublier le cas 0 qui serait lu comme False.
  else if (atoi(argv) || !strcmp(argv,"0")) affiche_Data(f, atoi(argv), ANT, ehdr, s);
  // Si l'argument n'a pas été trouvé dans les sections alors il existe pas
  else printf("La section '%s' n'existe pas ", argv);
  printf("\n");
  free(s);
  free(ANT);
}
