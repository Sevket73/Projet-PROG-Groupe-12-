#include <stdlib.h>
#include <string.h>
#include "afficherRealocation.h"
#include "utilsP.h"

void afficher_type(int type) {
    switch (type) {
      case 2:
    		printf("  R_ARM_ABS32");
    		break;
    	case 5:
    		printf("  R_ARM_ABS16");
    		break;
    	case 8:
    		printf("  R_ARM_ABS8");
    		break;
    	case 0x1c  :
    		printf("  R_ARM_CALL");
    		break;
    	case 0x1d:
    		printf("  R_ARM_JUMP24");
    		break;
    	default :
    		printf("  INCONNU");
    }
}


void afficher_rela(FILE *f, int idx, Elf32_Ehdr ehdr, Elf32_Shdr *shdr, char *idk) {
  int nbElt = shdr[idx].sh_size / sizeof(Elf32_Rela);
  printf("La table de symboles « %s » à l'adresse de décalage 0x%x contient %d entrées :\n",idk+shdr[idx].sh_name, shdr[idx].sh_offset, nbElt);
  printf("  Décalage      Info           Type           Addenda\n");
  Elf32_Rela *relaTab = init_Table_Rela(f, ehdr, shdr, idx);
  for (int i = 0; i < nbElt; i++) {
    printf("%08x  ", relaTab[i].r_offset);
    printf("%08x  ", relaTab[i].r_info);
    afficher_type((unsigned char)relaTab[i].r_info);
    if (relaTab[i].r_addend >= 0) {
      printf(" +");
      printf("%x", relaTab[i].r_addend);
    }
    else {
      printf(" %d", relaTab[i].r_addend);
    }
    printf("\n");
  }
  printf("\n");
}

void afficher_rel (FILE *f, int idx, Elf32_Ehdr ehdr, Elf32_Shdr *shdr, char *idk) {
  int nbElt = shdr[idx].sh_size / sizeof(Elf32_Rel);
  printf("La table de symboles « %s » à l'adresse de décalage 0x%x contient %d entrées :\n",idk+shdr[idx].sh_name, shdr[idx].sh_offset, nbElt);
  printf(" Décalage   Info        Type\n");
  Elf32_Rel *relTab = init_Table_Rel(f, ehdr, shdr, idx);
  for (int i = 0; i < nbElt; i++) {
    printf(" %08x  ", relTab[i].r_offset);
    printf(" %08x  ", relTab[i].r_info);
    afficher_type((unsigned char)relTab[i].r_info);
    printf("\n");
  }
  printf("\n");
}

void afficheTableRela (FILE *f, Elf32_Ehdr ehdr, Elf32_Shdr *s) {
  char *idk = Recuperer_Table_Noms(f, ehdr, s);
  for(int i = 0; i < ehdr.e_shnum; i++) {
    if (s[i].sh_type == 4) afficher_rela(f, i, ehdr, s, idk);
    if (s[i].sh_type == 9) afficher_rel(f, i, ehdr, s, idk);
  }
  free(idk);
}


int initRela(FILE *f) {
  Elf32_Ehdr ehdr;
  Elf32_Shdr *s = initS(f, &ehdr);
  afficheTableRela(f, ehdr, s);
  free(s);
  return 0;
}
