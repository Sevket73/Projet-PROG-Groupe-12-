#ifndef __afficherEntete_h__
#define __afficherEntete_h__
#include <elf.h>
#include <stdio.h>

 /* Les fonctions d'affichage suivantes sont basées sur du traitement de valeurs
 Avec de simples printf ou de potentiels switch/Case */

  // Affichage des valeurs de magique
  void afficheMagique(Elf32_Ehdr);

  // Affichage des valeurs de classe
  void afficheClasse(uint16_t);

  // Affichage des valeurs de Data
  void afficheSysteme(uint16_t);

  // Affichage des valeurs de Version
  void afficheVersion1(uint16_t);

  // Affichage des valeurs de l'OS et de ASI
  void afficheOS(uint16_t);

  // Affichage des valeurs de PAD
  void affichePad(uint16_t);

  // Affichage des valeurs du Type
  void afficheType(uint16_t);

  // Affichage des valeurs de la machine utilisée
  void afficheMachine(uint16_t);

  // Affichage des valeurs de la version en hexadécimale
  void afficheVersion2(uint32_t);

  // Affichage des valeurs des entrées
  void afficheEntry(uint32_t);

  // Affichage de l'adresse du header
  void affichePhoff(uint32_t);

  // Affichage de l'adresse des sections
  void afficheShoff(uint32_t);

  // Affichage des Flags
  void afficheFlags(uint32_t);

  // Affichage de la taille du header
  void afficheEhsize(uint16_t);

  // Affichage de la taille d'une entree du header
  void affichePhentsize(uint16_t);

  // Affichage du nombre d'entrée
  void affichePhnum(uint16_t);

  // Affichage de la taille d'une section
  void afficheShentsize(uint16_t);

  // Affichage du nombre de section
  void afficheShnum(uint16_t);

  // Affichage de l'index de la section table des noms
  void afficheShstrndx(uint16_t);

  /*  Récupère les valeurs du header et les places dans une structure,
  si le fichier est en big endian alors on le transforme tout de suite
  les valeurs contenues en little endian. */
  int initEntete(FILE *);

  // Affichage des valeurs de l'entête grâce aux fonctions définies ci-dessus
  void afficheEnteteElf(FILE *, Elf32_Ehdr);

#endif
