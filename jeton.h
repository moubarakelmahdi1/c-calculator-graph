#ifndef UNTITLED_JETON_H
#define UNTITLED_JETON_H


#include <stdio.h>
#include <stdlib.h>

typedef enum{
    Err_TYPE,NO_TOKEN,TROP_DE_VIRGULES
}typeerreur;

typedef enum{
    REEL,OPERATEUR,FONCTION,ERREUR,FIN,PAR_OUV,PAR_FERM,VARIABLE,BAR_OUV,BAR_FERM,ABSOLU
}typelexem;

typedef enum{
    PLUS,MOINS,FOIS,DIV,PUIS
}typeoperateur;

typedef enum{
    ABS,SIN,SQRT,LOG,COS,TAN,EXP,ENTIER,VAL_NEG,SINC
}typefonction;

typedef union{
    double reel;
    typefonction fonction;
    typeoperateur operateur;
    typeerreur erreur;
}typevaleur;


struct ArgSt {
    typelexem type;
    typevaleur valeur;
};typedef struct ArgSt  Arg;



#endif //UNTITLED_JETON_H
