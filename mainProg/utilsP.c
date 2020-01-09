#include <stdlib.h>
#include <string.h>
#include "big_endian.h"
#include "utilsP.h"

Elf32_Ehdr ehdrBig(Elf32_Ehdr ehdr) {
  ehdr.e_type = Traduire_uint16(ehdr.e_type);
  ehdr.e_machine = Traduire_uint16(ehdr.e_machine);
  ehdr.e_entry = Traduire_uint32(ehdr.e_entry);
  ehdr.e_phoff = Traduire_uint16(ehdr.e_phoff);
  ehdr.e_shoff = Traduire_uint32(ehdr.e_shoff);
  ehdr.e_flags = Traduire_uint32(ehdr.e_flags);
  ehdr.e_ehsize = Traduire_uint16(ehdr.e_ehsize);
  ehdr.e_phentsize = Traduire_uint16(ehdr.e_phentsize);
  ehdr.e_phnum = Traduire_uint16(ehdr.e_phnum);
  ehdr.e_shentsize = Traduire_uint16(ehdr.e_shentsize);
  ehdr.e_shnum = Traduire_uint16(ehdr.e_shnum);
  ehdr.e_shstrndx = Traduire_uint16(ehdr.e_shstrndx);
  return ehdr;
}

Elf32_Shdr *shdrBig(Elf32_Shdr *s, Elf32_Ehdr ehdr) {
  for(int i = 0; i < ehdr.e_shnum; i++) {
    s[i].sh_name = Traduire_uint32(s[i].sh_name);
    s[i].sh_type = Traduire_uint32(s[i].sh_type);
    s[i].sh_flags = Traduire_uint32(s[i].sh_flags);
    s[i].sh_addr = Traduire_uint32(s[i].sh_addr);
    s[i].sh_offset = Traduire_uint32(s[i].sh_offset);
    s[i].sh_size = Traduire_uint32(s[i].sh_size);
    s[i].sh_link = Traduire_uint32(s[i].sh_link);
    s[i].sh_info = Traduire_uint32(s[i].sh_info);
    s[i].sh_addralign = Traduire_uint32(s[i].sh_addralign);
    s[i].sh_entsize = Traduire_uint32(s[i].sh_entsize);

  }
  return s;
}

Elf32_Ehdr initEhdr(FILE *f) {
  Elf32_Ehdr ehdr;
  fread(&ehdr, 1, sizeof(ehdr), f);
  //Si le fichier est en big endian on traduit les valeurs en little endian
  if (ehdr.e_ident[EI_DATA] == 2) ehdr = ehdrBig(ehdr);
  return ehdr;
}

Elf32_Shdr *initShdr(FILE *f, Elf32_Ehdr ehdr) {
  Elf32_Shdr *s = malloc(ehdr.e_shnum * ehdr.e_shentsize);
  if (s == NULL){
    printf("Pas assez de place mémoire pour réserver la section\n");
    exit(0);
  }
  if (fseek(f, ehdr.e_shoff, SEEK_SET)){
    printf("Valeur de l'offset de l'entête trop grande\n");
    exit(0);
  }
  if (!fread(s, 1, ehdr.e_shnum * ehdr.e_shentsize, f)){
    printf("Taille et nombre de cette section trop grands pour ce fichier, impossible de lire les valeurs\n");
    exit(0);
  }
  //Si le fichier est en big endian on traduit les valeurs en little endian
  if (ehdr.e_ident[EI_DATA] == 2) s = shdrBig(s, ehdr);
  return s;
}

int recup_IndexSym (Elf32_Ehdr ehdr, Elf32_Shdr *shdr) {
  int index = -1;
  for(int i=0; i < ehdr.e_shnum; i++ )
    if(shdr[i].sh_type == 2)
      index = i;
  return index;
}

Elf32_Sym *Init_Sym_Tab(FILE *f,int nbElt, Elf32_Ehdr ehdr, Elf32_Shdr *shdr) {
  int index = recup_IndexSym(ehdr, shdr);
  Elf32_Sym * symTab;
  symTab = malloc(shdr[index].sh_size);
  if (symTab == NULL){
    printf("Pas assez de place mémoire pour réserver la section\n");
    exit(0);
  }
  if (fseek(f, shdr[index].sh_offset, SEEK_SET)){
    printf("Valeur de l'offset de cette section trop grande\n");
    exit(0);
  }
  if (!fread(symTab, 1, shdr[index].sh_size, f)){
    printf("Taille de cette section trop grande pour ce fichier, impossible de lire les valeurs\n");
    exit(0);
  }
  if (ehdr.e_ident[EI_DATA] == 2) symTabBig(index,  nbElt, symTab);
  return symTab;
}

Elf32_Rel *init_Table_Rel(FILE *f,  Elf32_Ehdr ehdr,Elf32_Shdr *shdr, int idx) {
  Elf32_Rel *relTab = malloc(shdr[idx].sh_size);
  if (relTab == NULL) {
    printf("Pas assez de place mémoire pour réserver la table de réimplentation\n");
    exit(0);
  }
  if (fseek(f, shdr[idx].sh_offset, SEEK_SET)){
    printf("Valeur de l'offset de cette section trop grande\n");
    exit(0);
  }
  if (!fread(relTab, 1, shdr[idx].sh_size, f)){
    printf("Taille de cette section trop grande pour ce fichier, impossible de lire les valeurs\n");
    exit(0);
  }
  if (ehdr.e_ident[EI_DATA] == 2) relBig(shdr, relTab, idx);
  return relTab;
}

Elf32_Rela *init_Table_Rela(FILE *f, Elf32_Ehdr ehdr, Elf32_Shdr *shdr, int idx) {
  Elf32_Rela *relaTab = malloc(shdr[idx].sh_size);
  if (relaTab == NULL) {
    printf("Pas assez de place mémoire pour réserver la table de réimplentation\n");
    exit(0);
  }
  if (fseek(f, shdr[idx].sh_offset, SEEK_SET)){
    printf("Valeur de l'offset de cette section trop grande\n");
    exit(0);
  }
  if (!fread(relaTab, 1, shdr[idx].sh_size, f)){
    printf("Taille de cette section trop grande pour ce fichier, impossible de lire les valeurs\n");
    exit(0);
  }
  if (ehdr.e_ident[EI_DATA] == 2) relaBig(shdr, relaTab, idx);
  return relaTab;
}

char *Recuperer_Table_Noms (FILE *f, Elf32_Ehdr ehdr, Elf32_Shdr *s) {
  Elf32_Shdr tableName = s[ehdr.e_shstrndx];
  char *ANT = malloc(tableName.sh_size);
  if (ANT == NULL){
    printf("Impossible d'afficher la table des symboles \n");
    exit(0);
  }
  if(fseek(f, tableName.sh_offset, SEEK_SET)){
    printf("Valeur de l'offset de cette section trop grande\n");
    exit(0);
  }
  if (!fread(ANT, 1, tableName.sh_size, f)){
    printf("Taille de cette section trop grande pour ce fichier, impossible de lire les valeurs\n");
    exit(0);
  }
  return ANT;
}

int Recuperer_Index_Nom (char * c, char * ANT, Elf32_Ehdr ehdr, Elf32_Shdr *s) {
  int i = 0;
  while  ((i < ehdr.e_shnum) && (strcmp(c,ANT + s[i].sh_name))) {
    i ++;
  }
  if (i < ehdr.e_shnum) return i;
  return -1;
}


Elf32_Sym *symTabBig(int index,  int nbElt, Elf32_Sym *symTab) {
  for(int i = 0; i < nbElt; i++) {
    symTab[i].st_value = Traduire_uint32(symTab[i].st_value);
    symTab[i].st_size = Traduire_uint32(symTab[i].st_size);
    symTab[i].st_shndx = Traduire_uint16(symTab[i].st_shndx);
    symTab[i].st_name = Traduire_uint32(symTab[i].st_name);
  }
  return symTab;
}

Elf32_Rel *relBig(Elf32_Shdr *shdr, Elf32_Rel *relTab, int idx) {
  int nbElt = shdr[idx].sh_size / sizeof(Elf32_Rel);
  for (int i = 0; i < nbElt; i++) {
    relTab[i].r_offset = Traduire_uint32(relTab[i].r_offset);
    relTab[i].r_info = Traduire_uint32(relTab[i].r_info);
  }
  return relTab;
}

Elf32_Rela *relaBig(Elf32_Shdr *shdr, Elf32_Rela *relaTab, int idx) {
  int nbElt = shdr[idx].sh_size / sizeof(Elf32_Rela);
  for (int i = 0; i < nbElt; i++) {
    relaTab[i].r_offset = Traduire_uint32(relaTab[i].r_offset);
    relaTab[i].r_info = Traduire_uint32(relaTab[i].r_info);
    relaTab[i].r_addend = Traduire_uint32(relaTab[i].r_addend);
  }
  return relaTab;
}

void mettre_espace(int i) {
    while (i--) printf(" ");
}

Elf32_Sym *initSymTab (FILE *f, Elf32_Ehdr ehdr, Elf32_Shdr *shdr) {
  int i = recup_IndexSym(ehdr, shdr);
  int nbElt = shdr[i].sh_size / sizeof(Elf32_Sym);
  Elf32_Sym *symTab = Init_Sym_Tab(f, nbElt, ehdr, shdr);
  return symTab;
}

Elf32_Shdr *initS(FILE *f, Elf32_Ehdr *ehdr) {
  *ehdr = initEhdr(f);
  Elf32_Shdr *s = initShdr(f, *ehdr);
  return s;
}

