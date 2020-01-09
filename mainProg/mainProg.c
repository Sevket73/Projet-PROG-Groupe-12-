#include <stdlib.h>
#include <string.h>
#include "utilsP.h"
#include "afficherEntete.h"
#include "afficherTableSections.h"
#include "afficherRealocation.h"
#include "afficher_sym.h"
#include "afficherData.h"

int main (int argc, char *argv[]) {
  if (argc == 1) {
    printf("Veuillez saisir un argument et un fichier, entrer -H pour la liste des arguments\n");
    return 0;
  }
  // Trouver moyen d'éviter les répétitions
  if (argv[1][0] =='H' || (argv[1][0] == '-' && argv[1][1] =='H')) {
    printf("Saisir -H pour la liste des commandes\nSaisir -a pour tout afficher \nSaisir -h pour afficher l'entête\nSaisir -S pour afficher la table des sections\nSaisir -x pour afficher le contenu d'une section (Préciser le numéro ou le nom de la section après le fichier)\nSaisir -s pour la table des symboles\nSaisir -r pour la table de réimplantation \n");
    return 0;
  }
  // Trouver moyen d'eviter les repetitions
  else if (argc <= 2) {
    printf("Veuillez saisir un argument et un fichier, entrer -H pour la liste des arguments\n");
    return 0;
  }
  // Faire Gestion erreur en cas de mauvais ficher
  FILE *f;
  f = fopen(argv[2], "rb");
  if (f == NULL) {
    printf("Impossible d'ouvrir le fichier\n");
    return 0;
  }
  char var = argv[1][0];
  if (argv[1][0] == '-' ) var = argv[1][1];
  switch (var) {

    case 'a':
      initEntete(f);
      f = fopen(argv[2], "rb");
      initTS(f);
      f = fopen(argv[2], "rb");
      if (argc <= 3) printf("Nombre d'argument insuffisant");
      else initData(f,argv[3]);
      f = fopen(argv[2], "rb");
      initSym(f);
      f = fopen(argv[2], "rb");
      initRela(f);
      break;
    case 'h':
      initEntete(f);
      break;
    case 'S':
      initTS(f);
      break;
    case 'x':
      if (argc <= 3) printf("Nombre d'argument insuffisant");
      else initData(f,argv[3]);
      break;
    case 's':
      initSym(f);
      break;
    case 'r':
      initRela(f);
      break;
    default:
      printf("%c n'est pas un caractère reconnu \nSaisir -H pour la liste des commandes\nSaisir -h pour afficher l'entête\nSaisir -S pour afficher la table des sections\nSaisir -x pour afficher le contenu d'une section (Préciser le numéro ou le nom de la section après le fichier)\nSaisir -s pour la table des symboles\nSaisir -r pour la table de réimplantation \n", argv[1][1]);
  }
  printf("\n" );
}
