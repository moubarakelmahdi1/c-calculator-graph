//
// Created by heishim on 19/03/2019.
//

#include "includes.h"



float OPERATION(typeoperateur O, float x, float y, int* ERREUR){
    float res;
    switch(O)
    {
        case PLUS:
            res = x+y;
            break;
        case MOINS:
            res= x-y;
            break;
        case FOIS:
            res = x*y;
            break;
        case DIV:
            if(y!=0){
                res=x/y;
            }else{
                *ERREUR = DivisionPar0 ;
                return 0;
            }
            break;
        case PUIS:
            res=pow(x,y);
            if((int)(1/y)%2==0)
            {
                *ERREUR = ErreurRacineCarre;
            }
            break;
    }
    return res;
}

float FONCTIONS(typefonction F, float x, int* ERREUR){
    float res,j;
    switch(F){
        case ABS:
            res = fabs(x) ;
            break;

        case SIN:
            res = sin(x);
            break;

        case SQRT:

            if(x<0){
                *ERREUR = ErreurRacineCarre;
                res=0;
            }else if(x>=0){
                res =sqrt(x) ;
            }
            break;

        case LOG:
            if(x>=0){
                res = log10(x);
            }
            else{
                *ERREUR = ErreurLOG;
                res =0;
            }
            break;

        case COS:
            res = cos(x);
            break;

        case TAN:
            if (cos(x) != 0) {
                res= sin(x) / cos(x);
            }
            else {
                *ERREUR = ErreurTAN;
                res= 0;
            }
            break;

        case EXP:
            res = exp(x);
            break;

        case ENTIER:
            j=(int)x;
            res =j;
            break;

        case VAL_NEG:
            if(x<=0){
                res=x;
            }else if(x>0){
                res=-x;
            }
            break;

        case SINC:
            if(x!=0){
                res=sin(x)/x;
            }else{
                *ERREUR = ErreurSINC;
                return 0;
            }
            break;
    }
    return res;
}

float eval(Arbre A, float x,int* ERREUR){
    *ERREUR=0;
    float res;
    if(A==NULL){
        return 0;
    }
    if((*ERREUR)==0){
        if (A->arg.type == FONCTION) {
            float a = eval(A->filsGauche, x,ERREUR);

            res= FONCTIONS(A->arg.valeur.fonction, a,ERREUR);
        }
        if (A->arg.type == OPERATEUR) {
            float a = eval(A->filsGauche, x,ERREUR);
            float b = eval(A->filsDroit, x,ERREUR);
            res= OPERATION(A->arg.valeur.operateur, a, b,ERREUR);
        }
        if (A->arg.type == REEL){
            res= A->arg.valeur.reel;}
        if (A->arg.type == VARIABLE){
            res= x;}
    }else if((*ERREUR)!=0){
        res=0;
    }
    return res;
}
