#ifndef UNTITLED_AS_H
#define UNTITLED_AS_H
#include "jeton.h"

struct Arbres {
    Arg arg;
    struct Arbres * filsDroit;
    struct Arbres * filsGauche;
};typedef struct Arbres * Arbre;

Arbre creerArbre ();  //fonction pour creer les arbres

void SUPPArbre (Arbre arbre);

int tailleTableau(Arg tab[]);  // fonction qui retourne la taille d'un tableau

void printTableau(Arg tab[]); // fonction affichage tableau

void printErreur (Arg * liste, int t);   // fonction affichage erreur

int erreurPAR(Arg * liste); // fonction qui detecte les erreurs de parenthese

int erreurFONC(Arg * liste);

Arbre creationArbre(Arbre arbre, Arg tab[]);

Arg *reduireTAB (Arg tab[], int debut, int fin); //fonction qui decoupe un tableau entre 2 valeurs de position

//___________________________________________________FONCTION DE TESTS__________________________________________________

void testPARandFONC();

void testCREEARBRE();

#endif //UNTITLED_AS_H

