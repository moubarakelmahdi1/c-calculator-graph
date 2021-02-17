#ifndef AL_H
#define AL_H


#include <stdio.h>
#include <stdlib.h>
#define TAILLE_ARG 20

extern int compteur_reel;

struct fonction
{
    char* tab_fonction;
    Arg Arg;
    struct fonction *suivant;
};typedef struct fonction * LISTE;

LISTE remplir_liste_fonction(LISTE liste_reference,char* tab_fonction,typelexem lexem,typefonction fonction);

LISTE remplir_liste_reference(LISTE liste_reference);

void saisir_fonction(char* saisie_fonction);

int compteur_jsq_plus_de_lettres(char* saisie_fonction,int compteur);

char* tableau_copie_pour_comp_fonction(char* saisie_fonction, int* compteur_saisie);

int compteur_jsq_plus_de_chiffres(char* saisie_fonction,int compteur, int* compteur_points);

char* tableau_copie_pour_reel(char* saisie_fonction, int* compteur_saisie,int* compteur_points);

void test_reel(char* saisie_fonction,int* compteur_saisie,Arg* tab, int* compteur_Arg,int* compteur_points);

void test_operateur_caracteres_speciaux(char* saisie_fonction,int*compteur_saisie,Arg* tab,int* compteur_Arg);

void test_fonction(char* saisie_fonction,int* compteur_saisie,LISTE liste_fonction,Arg* tab, int* compteur_Arg);

Arg* Tous_les_tests(Arg* tab_Arg);

extern Arg* tab_Arg;

int compte_virgule(char saisie_fonction[TAILLE_ARG]);

int compte_reel(Arg tab[TAILLE_ARG]);




#endif //AL_H
