#ifndef __fusionPart1_h__
#define __fusionPart1_h__
#include <elf.h>
#include <stdio.h>

  char *nomTable2 (FILE *, Elf32_Ehdr, Elf32_Shdr *);
  
  void TableSymbolesFus (FILE *, FILE *);
  
  void Recup_Valeurs1 (int, int, char *, FILE *);
  
  void Recup_Valeurs2 (int, int, char *, FILE *);
 
  void affiche_Databis (FILE *, FILE *, FILE *);
  
  int copie_table(char *, int);
  
  uint32_t max_off();
  
  void shdr_nbtaille(FILE *, FILE *);
  
  void init(FILE *, FILE *, FILE *);
  
  void Ecrire_Ehdr(FILE *);

#endif