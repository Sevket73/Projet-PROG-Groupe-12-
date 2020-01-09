# Makefile de notre programme
CC=gcc
CFLAGS=-Wall -Werror
COMPILE=$(CC) $(CFLAGS) -o $@ -c $<
main: PartieAffichage

Fusion: mainFusion.o FusionPart1.o afficherRealocation.o afficher_sym.o afficherData.o afficherEntete.o afficherTableSections.o big_endian.o utilsP.o
	$(CC) -o $@ $^

PartieAffichage: mainProg.o afficherRealocation.o afficher_sym.o afficherData.o afficherEntete.o afficherTableSections.o big_endian.o utilsP.o
	$(CC) -o $@ $^

mainFusion.o : mainFusion.c utilsP.h fusionPart1.h
	$(COMPILE)

mainProg.o: mainProg.c utilsP.h afficherEntete.h afficherTableSections.h afficherData.h afficher_sym.h afficherRealocation.h
	$(COMPILE)

FusionPart1.o: fusionPart1.c fusionPart1.h utilsP.h afficherEntete.h afficherTableSections.h afficherData.h afficher_sym.h afficherRealocation.h
	$(COMPILE)

afficherEntete.o: afficherEntete.c utilsP.h afficherEntete.h
	$(COMPILE)

afficherTableSections.o: afficherTableSections.c utilsP.h afficherTableSections.h
	$(COMPILE)

afficherData.o: afficherData.c utilsP.h afficherData.h
	$(COMPILE)

afficher_sym.o: afficher_sym.c utilsP.h afficher_sym.h
	$(COMPILE)

afficherRealocation.o: afficherRealocation.c utilsP.h afficherRealocation.h
	$(COMPILE)

utilsP.o: utilsP.c utilsP.h big_endian.h
	$(COMPILE)

big_endian.o: big_endian.c big_endian.h
	$(COMPILE)
