#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilsP.h"
#include "fusionPart1.h"

int main (int argc, char *argv[]) {
  if(argc <= 3){
    printf("Veuillez entrer les deux fichiers à fusionner et le fichier résultat\n");
    exit(0);
  }
  FILE *f1, *f2, *res;
  f1 = fopen(argv[1], "rb");
  f2 = fopen(argv[2], "rb");
  res = fopen(argv[3], "wb");
  if ((f1 == NULL) || (f2 == NULL)) {
    printf("Erreur lors de l'ouverture des fichiers\n");
    exit(0);
  }
  e1 = initEhdr(f1, e1);
  e2 = initEhdr(f2, e2);
  s1 = initShdr(f1, e1, s1);
  s2 = initShdr(f2, e2, s2);
  init(res, f1, f2);
  affiche_Databis (f1, f2, res);
  init46(res, f1, f2);
  TableSymbolesFus (f1, f2);
  Ecrire_Ehdr(res);
  fclose(f1);
  fclose(f2);
  fclose(res);
}