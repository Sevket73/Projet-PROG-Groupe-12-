#ifndef __afficherTableSections_h__
#define __afficherTableSections_h__
#include <elf.h>
#include <stdio.h>

  // affiche le type de section correspondant à l'index donnée
  void Afficher_Type_Section(int);

  /* affiche les flags de la section correspondant à l'index donnée
  Renvoie une valeur entière correspondant aux nombres de caractères affichés
  afin de faciliter l'alignement */
  int Afficher_Flags_Section(int);

  //Affichage de la table de section grâce aux valeurs au dessus
  void afficheTableSections(FILE *, Elf32_Ehdr, Elf32_Shdr *);

  //Initialisation de l'affichage de la table de section
  int initTS (FILE *);

#endif
