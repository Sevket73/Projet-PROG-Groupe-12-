#include "utilsP.h"
#include "afficherEntete.h"

void afficheMagique(Elf32_Ehdr ehdr) {
  for (int i = 0; i <= 15; i++) {
    printf("%02hhx ", ehdr.e_ident[i]);
  }
  printf("\n");
}

void afficheClasse (uint16_t class) {
  switch (class) {
    case 0:
      printf("Invalid class\n");
      break;
    case 1:
      printf("ELF32\n");
      break;
    case 2:
      printf("ELF64\n");
      break;
    default:
      printf("\n");
  }
}

void afficheSysteme (uint16_t data) {
  switch (data) {
    case 0:
      printf("Invalid data encoding\n");
      break;
    case 1:
      printf("Complément à 2, système à octets de poids\n faible d'abord (little endian)\n");
      break;
    case 2:
      printf("Complément à 2, système à octets de poids\n fort d'abord (big endian)\n");
      break;
    default:
      printf("\n");
  }
}

void afficheVersion1 (uint16_t version) {
  switch (version) {
    case 0:
      printf("%hx (invalid)\n", version);
      break;
    case 1:
      printf("%hx (current)\n", version);
      break;
    default:
      printf("\n");
  }
}

void afficheOS (uint16_t osabi) {
  switch (osabi) {
    case 0:
      printf("UNIX - System V\n");
      break;
    default: //Faire tous les cas
      printf("inconnu\n");
      break;
  }
}

void affichePad (uint16_t pad) {
  printf("%u\n", pad);
}

void afficheType (uint16_t type) {
  switch (type) {
    case 0:
      printf("NONE (No file type)\n");
      break;
    case 1:
      printf("REL (Relocatable file)\n");
      break;
    case 2:
      printf("EXEC (Executable file)\n");
      break;
    case 3:
      printf("DYN (Shared object file)\n");
      break;
    case 4:
      printf("CORE (Core file)\n");
      break;
    case 0xff00:
      printf("LOPROC (Processor-specific)\n");
      break;
    case 0xffff:
      printf("HIPROC (Processor-specific)\n");
      break;
    default:
      printf("Type non reconnu\n");
  }
}

void afficheMachine (uint16_t machine) {
  switch (machine) {
    case 0:
      printf("Pas de Machine\n");
      break;
    case 1:
      printf("AT&T WE 64100\n");
      break;
    case 2:
      printf("SPARC\n");
      break;
    case 3:
      printf("Intel Architecture\n");
      break;
    case 4:
      printf("Motorola 68000\n");
      break;
    case 5:
      printf("Motorola 88000\n");
      break;
    case 7:
      printf("Intel 80860\n");
      break;
    case 8:
      printf("MIPS RS3000 Big-Endian\n");
      break;
    case 10:
      printf("MIPS RS4000 Big-Endian\n");
      break;
    case 11:
      printf("Reserver pour plus tard\n");
      break;
    case 12:
      printf("Reserver pour plus tard\n");
      break;
    case 13:
      printf("Reserver pour plus tard\n");
      break;
    case 14:
      printf("Reserver pour plus tard\n");
      break;
    case 15:
      printf("Reserver pour plus tard\n");
      break;
    case 16:
      printf("Reserver pour plus tard\n");
      break;
    case 40:
      printf("ARM\n");
      break;
    case 62:
      printf("AMD x86-64\n");
      break;
    default:
        printf("%hu\n", machine); //Bizarre ça me met 62 pour machine pour scanner.o
  }
}

void afficheVersion2 (uint32_t version) {
  printf("0x%u\n", version);
}

void afficheEntry (uint32_t entry) {
  printf("0x%x\n", entry);
}

void affichePhoff (uint32_t phoff) {
  printf("%u (octets dans le fichier)\n", phoff);
}

void afficheShoff (uint32_t shoff) {
  printf("%u (octets dans le fichier)\n", shoff);
}

void afficheFlags (uint32_t flags) {
  printf("0x%x\n", flags);
}

void afficheEhsize (uint16_t ehsize) {
  printf("%u (octets)\n", ehsize);
}

void affichePhentsize (uint16_t phentsize) {
  printf("%u (octets)\n", phentsize);
}

void affichePhnum (uint16_t phnum) {
  printf("%u\n", phnum);
}

void afficheShentsize (uint16_t shentsize) {
  printf("%u (octets)\n", shentsize);
}

void afficheShnum (uint16_t shnum) {
  printf("%u\n", shnum);
}

void afficheShstrndx (uint16_t shstrndx) {
  printf("%u\n", shstrndx);
}

void afficheEnteteElf (FILE *f, Elf32_Ehdr ehdr) {
  printf("En-tête ELF:\n");
  printf("  Magique:  ");
  afficheMagique(ehdr);
  printf("  Classe:                             ");
  afficheClasse(ehdr.e_ident[EI_CLASS]);
  printf("  Données:                            ");
  afficheSysteme(ehdr.e_ident[EI_DATA]);
  printf("  Version:                            ");
  afficheVersion1(ehdr.e_ident[EI_VERSION]);
  printf("  OS/ABI:                             ");
  afficheOS(ehdr.e_ident[EI_OSABI]);
  printf("  Version ABI:                        ");
  affichePad(ehdr.e_ident[EI_PAD]);
  printf("  Type:                               ");
  afficheType(ehdr.e_type);
  printf("  Machine:                            ");
  afficheMachine(ehdr.e_machine);
  printf("  Version:                            ");
  afficheVersion2(ehdr.e_ident[EI_VERSION]);
  printf("  Adresse du point d'entrée:          ");
  afficheEntry(ehdr.e_entry);
  printf("  Début des en-têtes de programme:    ");
  affichePhoff(ehdr.e_phoff);
  printf("  Début des en-têtes de section:      ");
  afficheShoff(ehdr.e_shoff);
  printf("  Fanions:                            ");
  afficheFlags(ehdr.e_flags);
  printf("  Taille de cet en-tête:              ");
  afficheEhsize(ehdr.e_ehsize);
  printf("  Taille de l'en-tête du programme:   ");
  affichePhentsize(ehdr.e_phentsize);
  printf("  Nombre d'en-tête du programme:      ");
  affichePhnum(ehdr.e_phnum);
  printf("  Taille des en-têtes de section:     ");
  afficheShentsize(ehdr.e_shentsize);
  printf("  Nombre d'en-têtes de section:       ");
  afficheShnum(ehdr.e_shnum);
  printf("  Table d'indexes des chaînes d'en-tête de section:     ");
  afficheShstrndx(ehdr.e_shstrndx);
}

int initEntete(FILE *f) {
  Elf32_Ehdr ehdr = initEhdr(f);
  afficheEnteteElf(f, ehdr);
  return 0;
}
