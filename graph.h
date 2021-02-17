#ifndef UNTITLED_GRAPH_H
#define UNTITLED_GRAPH_H

/**
* @file Graph.h
*
* @brief pr�sente quelques outils d'affichage n�cessaires dans le cadre de ce
* projet.
* Il contient la d�claration des procedures disponibles pour ouvrir une fenetre
* et y dessiner des figures. Les coordonn�es des points dans la fenetre sont
* definies sur l'intervalle [-1;1], (-1,-1) etant le coin superieur gauche de
* la fenetre et (1,1) le coin inferieur droit.
*
* Pour une d�monstration de l'utilisation de ces proc�dures, voir le fichier
* main.cpp.
*
*/

#include "string.h"
#include "stdio.h"
#include <malloc.h>
#include "glut.h"
#include <math.h>
#define PAS 100

/*typedef struct tableau_evaluateur tableau_evaluateur;
struct tableau_evaluateur{
	float x;
	float y;
};*/

/**
* InitGraph
*
* Procedure d'initialisation de la fenetre et de l'environnement OpenGL
*
* @param ac nombre de parametres
* @param av tableau contenant les parametres
* @param WinName le nom (titre) de la fenetre d'affichage
* @param w la largeur de la fenetre
* @param h la hauteur de la fenetre
* @param Draw fonction qui affiche le graphique dans la fenetre
* @param Key fonction appel�e lors de l'appui sur une touche c du clavier,
*	 c designant le code ascii de la touche
*
*/
void InitGraph(int ac,char *av[], const char *WinName,
               const int w, const int h, void (*Draw)(void),
               void (*Key)(int c));

/**
* line
*
* Cette procedure permet de tracer une ligne entre deux points (x0, y0) et
* (x1,y1)
*
* @param x0 abscisse du 1er point
* @param y0 ordonn�e du 1er point
* @param x0 abscisse du 2eme point
* @param y0 ordonn�e du 2eme point
*
*/
void line(const float x0, const float y0, const float x1, const float y1);

/**
* setcolor
*
* Cette procedure permet de definir la couleur utilis�e pour tracer les lignes.
* La couleur par les valeurs des composantes rouge, vert et bleue.
*
* @param r composante rouge
* @param v composante verte
* @param b composante bleue
*
*/
void setcolor(const float r, const float v, const float b);

/**
* beginlines
*
* Cette procedure permet de commencer le trace d'une ligne brisee composee
* de n segments de droite d�finis par (n+1) points.
*
* @param x0 l'abscisse du premier point de la ligne brisee
* @param y0 l'ordonn�e du premier point de la ligne brisee
*
*/
void beginlines(const float x0, const float y0);

/**
* lineto
*
* Cette procedure permet de d'ajouter un point a la ligne brisee en cours. Le
* dernier point defini et le nouveau point delimitent un nouveau segment de
* droite dans la ligne brisee.
*
* @param x l'abscisse du nouveau point de la ligne brisee
* @param y l'ordonnee du nouveau point de la ligne brisee
*
*/
void lineto(const float x, const float y);

/**
* finishlines
*
* Cette procedure permet de terminer le trace de la ligne brisee en cours.
*
*/
void finishlines(void);

/**
* bar
*
* Cette proc�dure permet de tracer un rectangle defini par son coin superieur
* gauche et son coin inferieur droit.
*
* @param x0 abscisse du coin superieur gauche du rectangle
* @param y0 ordonnee du coin superieur gauche du rectangle
* @param x1 abscisse du coin inferieur droit du rectangle
* @param y1 ordonnee du coin inferieur droit du rectangle
*
*/
void bar(const float x0, const float y0, const float x1, const float y1);

/**
* outtextxy
*
* Cette proc�dure permet d'ecrire une chaine de charact�re s dans une zone de
* texte d�finie par les coordonn�es x et y
*
* @param x abscisse de l'origine (coin gauche superieur) de la zone de texte
* @param y ordonn�e de l'origine (coin gauche superieur) de la zone de texte
* @param s chaine de caracteres contenant le texte a afficher
*
*/
void outtextxy(const float x, const float y, char *s);
/*void outtextxy2(const float x, const float y, float s);
char* conversion_float_char(float x);
char* arrondi(char* s);
float detection(tableau_evaluateur tab[],float x);
float inter_abscisse(float x,float x1,float x2);
float inter_ordonnee(float y, float y1, float y2);*/
/*float moyenne(tableau_evaluateur tab[]);
//void zoomer(int z);
/*void char_To_Float();
void curseur(int a);*/

#endif //UNTITLED_JETON_H

