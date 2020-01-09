#!/bin/sh
cd ~/PROG5/elf_linker-1.0/Examples_loader
case $1 in
  afficherData.o)
  for fichT in *.o
  do
    for i in *.o
    do
      cd ../mainProg
      touch EssaisData.txt
      touch ResultData.txt
      ./PartieAffichage -x ../Examples_loader/$i 5 > EssaisData.txt
      readelf -x5 ../Examples_loader/$i > ResultData.txt
      cat ResultData.txt | tr -cd "[:print:]\n" > ResultData.txt
      cat EssaisData.txt | tr -cd "[:print:]\n" > EssaisData.txt
      if ! diff -w "EssaisData.txt" "ResultData.txt"
      then
        echo "c'est different $i"
      fi
    done
    cd ~/PROG5/elf_linker-1.0/Examples_loader
  done;;
  afficherEntete.o)
  for fichT in *.o
  do
    for i in *.o
    do
      cd ../mainProg
      touch EssaisEntete.txt
      touch ResultEntete.txt
      ./PartieAffichage -h ../Examples_loader/$i > EssaisEntete.txt
      readelf -h ../Examples_loader/$i > ResultEntete.txt
      cat ResultEntete.txt | tr -cd "[:print:]\n" > ResultEntete.txt
      cat EssaisEntete.txt | tr -cd "[:print:]\n" > EssaisEntete.txt
      if ! diff -q -w "EssaisEntete.txt" "ResultEntete.txt"
      then
        echo "c'est different $i"
      fi
    done
    cd ~/PROG5/elf_linker-1.0/Examples_loader
  done;;
  afficher_sym.o)
  for fichT in *.o
  do
    for i in *.o
    do
      cd ../mainProg
      touch EssaisSym.txt
      touch ResultSym.txt
      ./PartieAffichage -s ../Examples_loader/$i > EssaisSym.txt
      readelf -s ../Examples_loader/$i > ResultSym.txt
      cat ResultSym.txt | tr -cd "[:print:]\n" > ResultSym.txt
      cat EssaisSym.txt | tr -cd "[:print:]\n" > EssaisSym.txt
      if ! diff -q -w "EssaisSym.txt" "ResultSym.txt"
      then
        echo "c'est different $i"
      fi
    done
    cd ~/PROG5/elf_linker-1.0/Examples_loader
  done;;
  afficherRealocation.o)
  for fichT in *.o
  do
    for i in *.o
    do
      cd ../mainProg
      touch EssaisRealocation.txt
      touch ResultRealocation.txt
      ./PartieAffichage -r ../Examples_loader/$i > EssaisRealocation.txt
      readelf../Examples_loader/$i > ResultRealocation.txt
      cat ResultRealocation.txt | tr -cd "[:print:]\n" > ResultRealocation.txt
      cat EssaisRealocation.txt | tr -cd "[:print:]\n" > EssaisRealocation.txt
      if ! diff -q -w "EssaisRealocation.txt" "ResultRealocation.txt"
      then
        echo "c'est different $i"
      fi
    done
    cd ~/PROG5/elf_linker-1.0/Examples_loader
  done;;
  afficherTableSections.o)
  for fichT in *.o
  do
    for i in *.o
    do
      cd ../mainProg
      touch EssaisSections.txt
      touch ResultSections.txt
      ./PartieAffichage -S ../Examples_loader/$i > EssaisSections.txt
      readelf -S ../Examples_loader/$i > ResultSections.txt
      if ! diff -q -w "EssaisSections.txt" "ResultEntete.txt"
      then
        echo "c'est different $i"
      fi
    done
    cd ~/PROG5/elf_linker-1.0/Examples_loader
  done;;
  *)
  echo "Mauvais argument donné, il faut donner un nom de fichier que vous voulez tester"

esac
