#ifndef __affichage_h__
#define __affichage_h__
#include <elf.h>
#include <stdio.h>

  //Transforme un header en format big endian en little endian
  Elf32_Ehdr ehdrBig(Elf32_Ehdr);

  //Transforme les section en format big endian en little endian
  Elf32_Shdr *shdrBig(Elf32_Shdr *, Elf32_Ehdr);

  //Initialise la table des header
  Elf32_Ehdr initEhdr(FILE *);

  //Initialise la table des sections
  Elf32_Shdr *initShdr(FILE *, Elf32_Ehdr);

  //initialise la table des symboles
  Elf32_Sym *Init_Sym_Tab(FILE *, int, Elf32_Ehdr, Elf32_Shdr *);

  //Remplissage de la table Rel
  Elf32_Rel *init_Table_Rel(FILE *,  Elf32_Ehdr, Elf32_Shdr *, int);

  //Remplissage de la table Rela
  Elf32_Rela *init_Table_Rela(FILE *, Elf32_Ehdr, Elf32_Shdr *, int);

  /*Récupération de la table des noms, elle contient une liste de chaîne de
  caractères separés par des \0, pour cela on recupère son index donnée par le
  header e_shstrndx, on réserve en mémoire une chaîne de caractères de la taille
  de cette section sh_size et on lit dans le fichier les valeurs de la table */
  char *Recuperer_Table_Noms(FILE *, Elf32_Ehdr , Elf32_Shdr *);

  //Renvoie l'index de la table des symboles
  int recup_IndexSym(Elf32_Ehdr, Elf32_Shdr *);

  /* Parcours les sections jusqu'à trouver celle qui a le nom donné en argument
  renvoie -1 si elle n'a pas été trouvée */
  int Recuperer_Index_Nom (char *, char *, Elf32_Ehdr, Elf32_Shdr *);

  //Change les valeurs de la table des symboles en big ou little endian
  Elf32_Sym *symTabBig(int, int, Elf32_Sym *);

  //Change les valeurs de la rel en big ou little endian
  Elf32_Rela *relaBig(Elf32_Shdr *, Elf32_Rela *, int);

  //Change les valeurs de la rela en big ou little endian
  Elf32_Rel * relBig(Elf32_Shdr *, Elf32_Rel *, int);

  void mettre_espace(int);
  
  Elf32_Sym *initSymTab (FILE *, Elf32_Ehdr, Elf32_Shdr *);
  
  //Récupération de la table de section dans le fichier
  Elf32_Shdr *initS(FILE *, Elf32_Ehdr *);
  
#endif
