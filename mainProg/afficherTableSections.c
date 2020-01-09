#include <stdlib.h>
#include <string.h>
#include "afficherTableSections.h"
#include "utilsP.h"

void Afficher_Type_Section(int type) {
  switch (type) {
    case 0 :
      printf("   NULL                 ");
      break;
    case 1 :
      printf("   PROGBITS             ");
      break;
    case 2 :
      printf("   SYMTAB               ");
      break;
    case 3 :
      printf("   STRTAB               ");
      break;
    case 4 :
      printf("   RELA                 ");
      break;
    case 5 :
      printf("   HASH                 ");
      break;
    case 6 :
      printf("   DYNAMIC              ");
      break;
    case 7 :
      printf("   NOTE                 ");
      break;
    case 8 :
      printf("   NOBITS               ");
      break;
    case 9 :
      printf("   REL                  ");
      break;
    case 10 :
      printf("   SHLIB                ");
      break;
    case 11 :
      printf("   DYNSYM               ");
      break;
    case 0x70000000 :
      printf("   LOPROC               ");
      break;
    case 0x7fffffff :
      printf("   HIPROC               ");
      break;
    case 0x80000000 :
      printf("   LOUSER               ");
      break;
    case 0xffffffff :
      printf("   HIUSER               ");
      break;
    default :
      printf("   ??                   ");
    }
}

int Afficher_Flags_Section(int value) {
  int compteur = 14;
  if (value & SHF_WRITE) printf("W");
  else compteur --;
  if (value & SHF_ALLOC) printf("A");
  else compteur --;
  if (value & SHF_EXECINSTR) printf("X");
  else compteur --;
  if (value & SHF_MERGE) printf("M");
  else compteur --;
  if (value & SHF_STRINGS) printf("S");
  else compteur --;
  if (value & SHF_INFO_LINK) printf("I");
  else compteur --;
  if (value & SHF_LINK_ORDER) printf("L");
  else compteur --;
  if (value & SHF_OS_NONCONFORMING) printf("x");
  else compteur --;
  if (value & SHF_GROUP) printf("G");
  else compteur --;
  if (value & SHF_TLS) printf("T");
  else compteur --;
  if (value & SHF_MASKOS) printf("o");
  else compteur --;
  if (value & SHF_MASKPROC) printf("p");
  else compteur --;
  if (value & SHF_ORDERED) printf("O");
  else compteur --;
  if (value & SHF_EXCLUDE) printf("E");
  else compteur --;
  return compteur;
  // Le compteur indique le nombre exact de caractère
}


void afficheTableSections (FILE *f, Elf32_Ehdr ehdr, Elf32_Shdr *s) {
  char *ANT = Recuperer_Table_Noms(f, ehdr, s);
  if (ANT == NULL){
    printf("Impossible d'afficher la table des symboles \n");
    return;
  }
  printf("Il y a %hu en-têtes de section, débutant à l'adresse de décalage 0x%x\n\n", ehdr.e_shnum, ehdr.e_shoff);
  printf("En-têtes de section :\n");
  printf("  [Nr]  Nom                 Taille               Type                 TailleEntrée         Adresse              Fanion             Lien                 Info                 Décalage             Alignement\n\n");
// On affiche toutes les sections de 0 à shnum (nb de sections)
  for (uint16_t i = 0; i < ehdr.e_shnum; i ++) {
    printf("  [%2d]  %s", i, ANT + s[i].sh_name);
    // On ajoute des espaces pour que les valeurs soient alignées
    for (int k = strlen(ANT + s[i].sh_name); k < 20; k ++) {
      printf(" ");
    }
    printf("%016x  ", s[i].sh_size);
    Afficher_Type_Section(s[i].sh_type);
    printf("%016x     ", s[i].sh_entsize);
    printf("%016x     ", s[i].sh_addr);
    int l = Afficher_Flags_Section(s[i].sh_flags);
    //On ajoute des espaces pour que les valeurs soient alignées
    mettre_espace(19 - l);
    printf("%d                   ", s[i].sh_link);
    if (s[i].sh_link < 10) printf(" ");
    printf("%d                   ", s[i].sh_info);
    if (s[i].sh_info < 10) printf(" ");
    printf("%08x             ", s[i].sh_offset);
    printf("%u\n", s[i].sh_addralign);
  }
}

int initTS(FILE *f) {
  Elf32_Ehdr ehdr;
  Elf32_Shdr *s = initS(f, &ehdr);
  afficheTableSections(f, ehdr, s);
  printf("\nClé des fanions :\n  W (écriture), A (allocation), X (exécution), M (fusion), S (chaînes), I (info), L (ordre des liens), O (traitement supplémentaire par l'OS requis), G (groupe), T (TLS), C (compressé), x (inconnu),\n  o (spécifique à l'OS), E (exclu), l (grand), p (processor specific)\n");
  fclose(f);
  return 0;
}
