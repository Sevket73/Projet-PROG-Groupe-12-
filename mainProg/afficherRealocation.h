#ifndef __afficherRealocation_h__
#define __afficherRealocation_h__
#include <elf.h>
#include <stdio.h>

  //affiche le type
  void afficher_type(int);

  //affiche les détails si la section est de type rela
  void afficher_rela(FILE *, int, Elf32_Ehdr, Elf32_Shdr *, char *);

  //affiche les détails si la section est de type rel
  void afficher_rel (FILE *, int, Elf32_Ehdr, Elf32_Shdr *, char *);

  //affiche les détails des sections de type rel ou rela
  void afficheTableRela (FILE *, Elf32_Ehdr, Elf32_Shdr *);

  //initialise les tables rel / rela
  int initRela(FILE *);

#endif