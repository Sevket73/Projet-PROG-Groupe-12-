#ifndef __affichageData_h__
#define __afichageData_h__
#include <elf.h>
#include <stdio.h>

  /* Afichage des dernières valeurs du contenu d'une section elle va calculer
  le nombre d'espace à ajouter en fonction des derniers octets affichés
  les ajouter et afficher leurs valeurs ascii */
  void Etape_finale(int , char *);

  /* recupère la valeur de la section donnée à l'indice donné dans le fichier donné
  Placer cette valeur dans la chaîne de caractère donné */
  void Recup_Valeurs(int, int, char *,char *, FILE *, Elf32_Shdr *);

  /*Fonction utile pour l'affichage du contenu d'une section
  Affiche un espace en fonction du nombre d'octet affiché
  affiche les valeurs, retourne à la ligne et affiche la nouvelle adresse si on
  est positionné en fin de ligne */
  void test_espace(int, char *);

  //affichage du contenu d'une section, si elle existe, grâce aux fonctions si dessus
  //si la section n'existe pas ou est vide il affiche une erreur
  void affiche_Data (FILE *, int, char *, Elf32_Ehdr ehdr, Elf32_Shdr *s);

  /* Va initialiser les différentes tables nécessaires pour
  l'affichage du contenu d'une section, va au préalable cherche l'indice de la
  section donnée en argument, si la valeur n'est ni un nom de section ni un entier
  elle affichera une erreur */
  void initData (FILE *, char *);

#endif
