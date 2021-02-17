
#ifndef UNTITLED__EV_H
#define UNTITLED__EV_H

#include <stdio.h>
#include "jeton.h"
#include "AS.h"
#include <math.h>
#include "ERREUR.h"

float OPERATION(typeoperateur O, float x, float y,int* ERREUR);

float FONCTIONS(typefonction F, float x,int* ERREUR);

float eval(Arbre A,float x,int* ERREUR);

#endif //UNTITLED__EV_H
