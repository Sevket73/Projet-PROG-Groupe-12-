#include <stdlib.h>
#include <string.h>
#include "utilsP.h"
#include "afficherEntete.h"
#include "afficherTableSections.h"
#include "afficherRealocation.h"
#include "afficher_sym.h"
#include "afficherData.h"

Elf32_Ehdr e1;
Elf32_Ehdr e2;
Elf32_Ehdr eR;
Elf32_Shdr *s1;
Elf32_Shdr *s2;
Elf32_Shdr *shR;
char *ANTR;
char *ANT1;
char *ANT2;


//      PARTIE 2

char *nomTable2 (FILE* f, Elf32_Ehdr e, Elf32_Shdr *s) {
  char *idk = Recuperer_Table_Noms(f, e, s);
  int index = Recuperer_Index_Nom(".strtab", idk, e, s);
  char *n=malloc(s[index].sh_size);
  if (fseek(f, s[index].sh_offset, SEEK_SET)) return NULL;
  if (!fread(n,1, s[index].sh_size, f)) return NULL;
  return n;
}

void TableSymbolesFus (FILE *f1, FILE *f2) {
  char *idk1 = nomTable2(f1, e1, s1);
  if (idk1 == NULL) {
    printf("Impossible d'afficher la table des symbole \n");
    return;
  }
  char *idk2 = nomTable2(f2, e2, s2)
  if (idk2 == NULL) {
    printf("Impossible d'afficher la table des symbole \n");
    return;
  }
  int i1 = recup_IndexSym(e1, s1);
  int nbElt1 = s1[i1].sh_size / sizeof(Elf32_Sym);
  Elf32_Sym *symTab1 = Init_Sym_Tab(f1, nbElt1, e1, s1);
  int i2 = recup_IndexSym(e2, s2);
  int nbElt2 = s2[i2].sh_size / sizeof(Elf32_Sym);
  Elf32_Sym *symTab2 = Init_Sym_Tab(f2, nbElt2, e2, s2);
  int iR = recup_IndexSym(eR, shR);
  Elf32_Sym *symTabR = malloc(shR[iR].sh_size);
  int index1 = Recuperer_Index_Nom(".strtab", idk1, e1, s1);
  int index2 = Recuperer_Index_Nom(".strtab", idk2, e2, s2);
  char *idkR = malloc(s1[index1].sh_size + s2[index2].sh_size);
  idkR = idk1;
  int nbEltR = nbElt1;
  int j;
  symTabR = symTab1;
  for (int i = 0; i < nbElt2; i++) {
    j = 0;
    while ((j < nbElt1) && ((strcmp(idk1 + symTab1[j].st_name,idk2 + symTab2[i].st_name))))
      j++;
    if (j < nbElt1 && (symTab2[i].st_info >> 4) && !(symTab1[j].st_info & 0xf) && !(symTab2[i].st_info & 0xf)) {
      // défini dans aucune mais présent dans les deux, on peut ne rien faire
    }
    else if (j < nbElt1 && (symTab2[i].st_info >> 4) && (symTab1[j].st_info & 0xf) && (symTab2[i].st_info & 0xf)) {
      //A mettre un message d'erreur
      exit(0);
    }
    else if (j < nbElt1 && (symTab2[i].st_info >> 4) && (symTab1[j].st_info & 0xf)) {
      //défini dans la table 1 mais pas dans la table 2 (présent dans les deux), rien à faire+
    }
    else if (j < nbElt1 && (symTab2[i].st_info >> 4) && (symTab2[i].st_info & 0xf)) {
      //défini dans la table 2 mais pas dans la table 1 (présent dans les deux)
      symTabR[j] = symTab2[i];
      symTabR[j].st_name = symTab1[j].st_name;
      symTabR[j].st_value = symTab1[j].st_value;
    }
    else {
      //present dans la table 2
      symTabR[nbEltR] = symTab2[i];
      nbEltR ++;
    }
  }
}


//    PARTIE 1
void Recup_Valeurs1 (int i, int indice, char *val, FILE *f) {
  if(!fseek(f, s1[indice].sh_offset + i , SEEK_SET)) {
    if (!fread(val, 1, 1, f)) exit(0);
    *val &= 0xff;
  }
  else exit(0);
}

void Recup_Valeurs2 (int i, int indice, char *val, FILE *f) {
  if(!fseek(f, s2[indice].sh_offset + i , SEEK_SET)) {
    if (!fread(val, 1, 1, f)) exit(0);
    *val &= 0xff;
  }
  else exit(0);
}

void affiche_Databis (FILE *f1, FILE *f2, FILE *res) {
  int i, i1, i2;
  for (int k = 0; k < eR.e_shnum; k ++) {
    int size = shR[k].sh_size;
    char val;
    i = 0;
    while (i < size) {
      fseek(res, shR[k].sh_offset + i , SEEK_SET);
      i1 = 0;
      while ((i1 < e1.e_shnum) && (strcmp(ANT1 + s1[i1].sh_name,ANTR + shR[k].sh_name))) i1++;
      i2 = 0;
      while ((i2 < e2.e_shnum) && (strcmp(ANT2 + s2[i2].sh_name,ANTR + shR[k].sh_name))) i2++;
      //rajouter une condition, il faut pas marquer la section des symboles car on l'a refaite, faut la faire plus tard quand on écrit dans le fichier
      //rajouter une autre, il faut pas marquer la table des noms !!
      if (i1 < e1.e_shnum && i != eR.e_shstrndx) Recup_Valeurs1(i, i1, &val, f1);
      if (i2 < e2.e_shnum && i != eR.e_shstrndx) Recup_Valeurs2(i, i2, &val, f2);
      fwrite(&val, sizeof(val), 1, res);
      i ++;
    }
  }
}

int copie_table(char *ANT, int taille) {
  int k = 0;
  for(int i = 0; i < taille; i++){
    while (ANT[k] != '\0') {
      ANTR[k] = ANT[k];
      k++;
    }
    ANTR[k] = ANT[k];
    k++;
  }
  return k;
}

uint32_t max_off(){
  int max = 0;
  for(int i = 0; i < eR.e_shnum; i++) {
    if (shR[max].sh_offset < shR[i].sh_offset) max = i;
  }
  return shR[max].sh_offset + shR[max].sh_size;
}

void shdr_nbtaille(FILE *f1, FILE *f2){
  int j, k, temp, comp;
  int Tab[e2.e_shnum];
  ANT1 = Recuperer_Table_Noms(f1, e1, s1);
  ANT2 = Recuperer_Table_Noms(f2, e2, s2);
  ANTR = malloc(s1[e1.e_shstrndx].sh_size + s2[e2.e_shstrndx].sh_size);
  temp = copie_table(ANT1, e1.e_shnum);
  //ANTR = ANT1;
  comp = 0;
  for(int i = 0; i<e2.e_shnum; i++){
    j = 0;
    while ((j < e1.e_shnum) && (strcmp(ANT1 + s1[j].sh_name,ANT2 + s2[i].sh_name)))
      j++;
    if (j >= e1.e_shnum){
      shR = realloc(shR, sizeof(Elf32_Shdr) + 1);
      Tab[comp] = i;
      shR[eR.e_shnum].sh_type = s2[i].sh_type;
      shR[eR.e_shnum].sh_addr = s2[i].sh_addr;
      shR[eR.e_shnum].sh_size = s2[i].sh_size;
      shR[eR.e_shnum].sh_link = s2[i].sh_link;
      shR[eR.e_shnum].sh_info = s2[i].sh_info;
      shR[eR.e_shnum].sh_addralign = s2[i].sh_addralign;
      shR[eR.e_shnum].sh_offset = s2[i].sh_offset;
      shR[eR.e_shnum].sh_entsize = s2[i].sh_entsize;
      shR[eR.e_shnum].sh_name = temp;
      //Les flags font tout planter quand on les defini
      k = 0;
      while (*(ANT2 + s2[i].sh_name + k) != '\0') {
        ANTR[shR[eR.e_shnum].sh_name + k] = ANT2[s2[i].sh_name + k];
        k++;
      }
      ANTR[shR[eR.e_shnum].sh_name + k] = '\0';
      temp += k + 1;
      eR.e_shnum ++;
      comp++;
    }
    else  shR[j].sh_size += s2[i].sh_size;
    printf("%d\n", shR[i].sh_link);
  }
  int max = max_off();
  for(int i = 0; i < comp; i++){
    s2[Tab[i]].sh_offset = max;
    max += s2[Tab[i]].sh_size;
  }
}

void init(FILE *res, FILE *f1, FILE *f2) {
  eR = e1;
  shR = malloc(e1.e_shnum * e1.e_shentsize);
  shR = s1;
  eR.e_ident[EI_DATA] = 1;
  eR.e_phentsize += e2.e_phentsize;
  eR.e_phnum += e2.e_phnum;
  shdr_nbtaille(f1,f2);
}

void Ecrire_Ehdr (FILE *res) {
  Elf32_Shdr tableName = shR[eR.e_shstrndx];
  int temp;
  fwrite(&eR, sizeof(Elf32_Ehdr), 1, res);
  fseek(res, eR.e_shoff, SEEK_SET);
  //Modifier les sections pour la table des symboles et la table des noms
  fwrite(shR, eR.e_shnum * eR.e_shentsize, 1, res);
  fseek(res, tableName.sh_offset, SEEK_SET);
  //ecrire la table des symboles ici
  for(int I = 0; I<eR.e_shnum; I++){
    temp = 0;
    while (*(ANTR + shR[I].sh_name + temp) != '\0') {
      fwrite(ANTR + shR[I].sh_name + temp, sizeof(char), 1, res);
      temp ++;
    }
    fwrite(ANTR + shR[I].sh_name + temp, sizeof(char), 1, res);
  }
  //ECRIRE LA TABLE DES SYMBOLES
}
