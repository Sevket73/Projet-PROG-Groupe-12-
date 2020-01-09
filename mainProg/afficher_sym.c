#include <stdlib.h>
#include <string.h>
#include "afficher_sym.h"
#include "utilsP.h"

char *symType (int val) {
    switch (val & 0xf) {
        case(0):
            return "NOTYPE";
            break;

        case(1):
            return "OBJECT";
            break;

        case(2):
            return "FUNC";
            break;

        case(3):
            return "SECTION";
            break;

        case(4):
            return "FILE";
            break;

        case(13):
            return "LOPROC";
            break;

        case(15):
            return "HIPROC";
            break;

        default:
            exit(1);
    }
}



char *porteSym(int val) {
    switch (val >> 4) {
        case(0):
            return "LOCAL";
            break;

        case(1):
            return "GLOBAL";
            break;

        case(2):
            return "WEAK";
            break;

        case(13):
            return "LOPROC";
            break;

        case(15):
            return "HIPROC";
            break;

        default:
            return("UNKNOWN");
    }
}



char *recup_Visibilite (int val) {
    switch(val) {
      	case STV_DEFAULT:
          return "DEFAULT";
          break;

      	case STV_INTERNAL:
          return "INTERNAL";
          break;

      	case STV_HIDDEN:
          return "HIDDEN";
          break;

      	case STV_PROTECTED:
          return "PROTECTED";
          break;

      	default:
          return "UNKNOWN";
      }
}

void recup_Shndx (int val) {
    switch(val) {
      	case 0:
          printf("UND ");
          break;

      	case 0xff00:
          printf(" LO ");
          break;

      	case 0xff1f:
          printf("HIP ");
          break;

      	case 0xfff1:
          printf("ABS ");
          break;

        case 0xfff2:
          printf("COM ");
          break;

        case 0xffff:
          printf("HIR ");
          break;

      	default:
          printf("%3d ", val);
      }
}

char *nomTable (FILE* f, Elf32_Ehdr ehdr, Elf32_Shdr *shdr) {
  char *idk = Recuperer_Table_Noms(f, ehdr, shdr);
  int index = Recuperer_Index_Nom(".strtab", idk, ehdr, shdr);
  char *n=malloc(shdr[index].sh_size);
  if (fseek(f, shdr[index].sh_offset, SEEK_SET)) return NULL;
  if (!fread(n,1, shdr[index].sh_size, f)) return NULL;
  return n;
}

void afficheTableSymboles (FILE *f, Elf32_Ehdr ehdr, Elf32_Shdr *s, Elf32_Sym *symTab) {
  int i = recup_IndexSym(ehdr, s);
  int nbElt = s[i].sh_size / sizeof(Elf32_Sym);
  printf("La table de symboles « .symtab » contient %d entrées :\n",nbElt);
  printf("   Num: Valeur     Tail Type    Lien   Vis     Ndx Nom\n");
  char *idk = nomTable(f, ehdr, s);
  if (idk == NULL) return;
  for(int i = 0; i < nbElt; i++) {
    printf("   %3d: ", i);
    printf("%08x ", symTab[i].st_value);
    printf("%4u ", symTab[i].st_size);
    printf("%s", symType(symTab[i].st_info));
    for (int j = strlen(symType(symTab[i].st_info)); j < 8; j ++) printf(" ");
    printf("%s", porteSym(symTab[i].st_info));
    for (int k = strlen(porteSym(symTab[i].st_info)); k < 7; k ++) printf(" ");
    printf("%s", recup_Visibilite(symTab[i].st_other));
    for (int l = strlen(porteSym(symTab[i].st_other)); l < 6; l ++) printf(" ");
    recup_Shndx(symTab[i].st_shndx);
    printf("%s", idk + symTab[i].st_name);
    printf("\n");
  }
}

int initSym (FILE *f) {
  Elf32_Ehdr ehdr;
  Elf32_Shdr *s = initS(f, &ehdr);
  Elf32_Sym *symTab = initSymTab (f, ehdr, s);
  afficheTableSymboles(f, ehdr, s, symTab);
  return 0;
}
