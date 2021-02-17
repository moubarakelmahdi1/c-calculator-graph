#ifndef UNTITLED_AFFICHAGE_H
#define UNTITLED_AFFICHAGE_H

#include "stdlib.h"
#include <stdio.h>
#include "math.h"
#include "graph.h"

#define TAILLE_BORNES 50
#define TAILLE_TABLEAU 1500
#define TAILLE_VALEUR 20

//Graphique � deux dimensions., l'une pour les abscisses et l'autre pour les ordonn�es
extern float tab[TAILLE_TABLEAU][3];
//Pas correspondant � la diff�rence d'abscisse entre chaque point du tableau
extern float pas;
//Valeur maximale que peut atteindre notre courbe
extern float maximum;
//Valeur minimal que peut atteindre notre courbe
extern float minimum;
//Plus grand extremum
extern float base;
//Ecart entre la borne inf�rieur et la borne sup�rieur
extern float ecartX;
//Ecart entre la valeur maximale et la valeur minimale, nous permettra de normaliser par rapport � la plus grande valeur
extern float ecartY;
//Borne inf�rieur choisie par l'utilisateur
extern float borneInf;
//Borne sup�rieur choisie par l'utilisateur
extern float borneSup;
//Indice de zoom en hauteur initialis� � 1
extern float zoomHauteur;
//Indice de zoom en largeur initialis� � 1, nous permettra de limit� le zoom minimal 0,1
extern float zoomLargeur;
//Indice de d�calage de la courbe, nous permettra de d�caler les bornes � la demande de l'utilisateur
extern int decalage;
//Curseur de la courbe
extern int curseur;
//Bascule permettant d'afficher ou de masquer la grille du graphique
extern int bascule;


extern char fonction[TAILLE_BORNES];

int estUnNombre(char nombre[TAILLE_BORNES]);

void remplir_Tableau();

void myDraw(void);

void myKey(int c);

void Init();

#endif // UNTITLED_AFFICHAGE_H
