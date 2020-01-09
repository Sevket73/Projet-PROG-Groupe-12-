#ifndef afficherSym
#define afficherSym
#include <elf.h>
#include <stdio.h>

  //Renvoie le type associe à l'entier donné en argument
  char *symType(int);

  //Affiche les liens
  char *porteSym(int);

  //Affiche les Visibility
  char *recup_Visibilite(int);
  
  //Affiche le Shndx de la table des symboles
  void recup_Shndx(int);

  /*Renvoie la table des noms de symboles, son foctionnement est le même
  que celui de Recuperer_Table_Noms()*/
  char *nomTable(FILE*, Elf32_Ehdr, Elf32_Shdr *);

  //affiche la table des symboles grâce aux fonctions
  void afficheTableSymboles(FILE *, Elf32_Ehdr, Elf32_Shdr *, Elf32_Sym *);

  //initialise et affiche la table des symboles
  int initSym (FILE *);

#endif
