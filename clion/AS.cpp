//
// Created by Maximilien Moraud on 2019-03-18.
//

#include "includes.h"


Arbre creerArbre ()  //fonction pour creer les arbres
{
    return NULL;
}

void SUPPArbre (Arbre arbre)
{
    if (arbre!=NULL)
    {
        SUPPArbre (arbre->filsDroit);
        SUPPArbre(arbre->filsGauche);
        free(arbre);
    }
}

int tailleTableau(Arg tab[])  // fonction qui retourne la taille d'un tableau
{
    int i = 0;
    if (tab == NULL) {
        return 0;
    }
    while (tab [i].type != FIN){
        i++;
    }
    return i+1; // + 1 pour type fin
}

void printTableau(Arg tab[]) // fonction affichage tableau
{
    int i;
    for (i = 0; tab[i].type != FIN; i++) {
        if (tab[i].type == OPERATEUR) {
            switch (tab[i].valeur.operateur) {
                case PLUS:
                    printf("+ ");
                    break;
                case MOINS:
                    printf("- ");
                    break;
                case DIV:
                    printf("/ ");
                    break;
                case FOIS:
                    printf("* ");
                    break;
                case PUIS:
                    printf("^ ");
                    break;
                default:
                    break;
            }
        } else if (tab[i].type == FONCTION) {
            switch (tab[i].valeur.fonction) {
                case ABS:
                    printf("abs ");
                    break;
                case SIN:
                    printf("sin ");
                    break;
                case COS:
                    printf("cos ");
                    break;
                case EXP:
                    printf("exp ");
                    break;
                case TAN:
                    printf("tan ");
                    break;
                case SQRT:
                    printf("sqrt ");
                    break;
                case LOG:
                    printf("log ");
                    break;
                case VAL_NEG:
                    printf("- ");
                    break;
                case SINC:
                    printf("sinc ");
                    break;
                case ENTIER:
                    printf("entier ");
                    break;
                default:
                    break;
            }
        } else {
            switch (tab[i].type) {
                case BAR_FERM:
                    printf("] ");
                    break;
                case BAR_OUV:
                    printf("[ ");
                    break;
                case PAR_FERM:
                    printf(") ");
                    break;
                case PAR_OUV:
                    printf("( ");
                    break;
                case ABSOLU:
                    printf("abs ");
                    break;
                case REEL:
                    printf("a ");
                    break;
                case VARIABLE:
                    printf("x ");
                    break;
                default:
                    break;
            }
        }
    }
    printf ("\n");
}

void printErreur (Arg * liste, int t)   // fonction affichage erreur
{
    printTableau (liste);
    int compt;
    for (compt=0 ; compt<t ; compt++)
    {
        if (liste[compt].type == OPERATEUR) {
            switch (liste[compt].valeur.operateur) {
                case PLUS:
                    printf("  ");
                    break;
                case FOIS:
                    printf("  ");
                    break;
                case PUIS:
                    printf("  ");
                case MOINS:
                    printf("  ");
                    break;
                case DIV:
                    printf("  ");
                    break;
                default:
                    break;
            }
        } else if (liste[compt].type== FONCTION) {
            switch (liste[compt].valeur.fonction) {
                case ABS:
                    printf("    ");
                    break;
                case SIN:
                    printf("    ");
                    break;
                case SQRT:
                    printf("     ");
                    break;
                case COS:
                    printf("    ");
                    break;
                case EXP:
                    printf("    ");
                    break;
                case TAN:
                    printf("    ");
                    break;
                case LOG:
                    printf("    ");
                    break;
                case VAL_NEG:
                    printf("  ");
                    break;
                case SINC:
                    printf("     ");
                    break;
                case ENTIER:
                    printf("      ");
                default:
                    break;
            }
        }
        else
        {
            switch (liste[compt].type) {
                case PAR_FERM:
                    printf("  ");
                    break;
                case PAR_OUV:
                    printf("  ");
                    break;
                case REEL:
                    printf("  ");
                    break;
                case VARIABLE:
                    printf("  ");
                    break;
                case ABSOLU:
                    printf("    ");
                    break;
                case BAR_FERM:
                    printf("  ");
                    break;
                case BAR_OUV:
                    printf("  ");
                    break;
                default:
                    break;
            }
        }
    }
    printf("^");
}

int erreurPAR(Arg * liste){ // fonction qui detecte les erreurs de parenthese
    int compt = 0;
    int taille = tailleTableau (liste)-1;
    int PAR = 0;
    int p1 = 0;
    int p2 = 0;

    while (compt < taille){
        if (liste[compt].type==PAR_FERM) {
            PAR--;
            p1 = compt;
        }
        if (liste[compt].type==PAR_OUV) {
            PAR++;
            p2 = compt;
        }
        compt++;
    }
    if(PAR>0){
        printf ("Erreur : parenthese ouverte non ferme\n");
        printErreur (liste, p2);
        return 1;
    }
    if(PAR<0){
        printf ("Erreur : parenthese ferme non ouverte\n");
        printErreur (liste, p1);
        return 1;
    }
    return 0;
}

int erreurFONC(Arg * liste){ // fonction qui detecte si ils manquent des parentheses apres une fonction
    int compt = 0;
    int taille = tailleTableau (liste)-1;
    int p = 0;


    while (compt < taille){
        if (liste[compt].type==FONCTION && liste[compt+1].type!=PAR_OUV) {
            p = compt;
            printf ("Erreur : parenthèse non placée sur la fonction\n");
            printErreur (liste, p);
            return 1;
        }
        compt++;
    }
    return 0;
}

Arbre ajoutNoeud (Arbre arbre, typelexem  type, typevaleur valeur){ // fonction qui ajoute une valeur à un fils de l'arbre
    arbre = (Arbre)malloc(sizeof(struct Arbres));
    arbre->filsDroit = NULL;
    arbre->filsGauche = NULL;
    arbre->arg.type = type;
    switch(arbre->arg.type){
        case OPERATEUR:
            arbre->arg.valeur.operateur=valeur.operateur;
            break;
        case FONCTION:
            arbre->arg.valeur.fonction=valeur.fonction;
            break;
        case REEL:
            arbre->arg.valeur.reel=valeur.reel;
            break;
        case VARIABLE:
            arbre->arg.valeur.reel=0;
            break;
        default:
            arbre->arg.valeur.erreur=Err_TYPE;
            arbre->arg.type=ERREUR;
            break;
    }
    return arbre;

}

Arg *reduireTAB (Arg tab[], int debut, int fin){ //fonction qui decoupe un tableau entre 2 valeurs de position
    int ecart = fin-debut;
    Arg *tab2 = (Arg*)malloc((ecart+2)*sizeof(Arg));
    for (int i = debut; i <= fin; i ++)
    {
        tab2[i-debut] = tab[i];
    }
    tab2[ecart+1].type=FIN;
    return tab2;
}


Arg *SuppPAR (Arg tab[]){ //fonction qui supprime les parrethese ext si elles existent
    int taille = tailleTableau (tab);
    if (taille > 2){
        while (tab[0].type==PAR_OUV && tab[taille-2].type==PAR_FERM){
            int ecart = taille - 3;
            Arg *tab2 = (Arg*)malloc((ecart+2)*sizeof(Arg));
            for (int i = 1; i <= ecart; i ++)
            {
                tab2[i-1] = tab[i];
            }
            tab2[ecart].type=FIN;
            tab = tab2;
            taille = tailleTableau(tab);
        }

    }

    return tab;
}

int Operateur(Arg tab[]){ //cherche l'existance d'un operateur
    int i, a = 0, PAR = 0, taille = tailleTableau(tab);
    for(i=0; i < taille-1; i++){
        if (tab[i].type == PAR_FERM) PAR++;
        if (tab[i].type == PAR_OUV) PAR--;
        if (tab[i].type == OPERATEUR && PAR == 0){
            a--;
        }
    }
    return a;
}


Arbre creationArbre(Arbre arbre, Arg tab[]) //on créé un arbre etage par etage en commencant pour les derniere operations à effectuer
{
    tab = SuppPAR(tab);
    int i, taille = tailleTableau(tab), PAR = 0;
    if (Operateur(tab) == 0) {
        for (i=0; i < taille; i++) {
            if (tab[i].type == PAR_OUV) {
                PAR++;
            }
            if (tab[i].type == PAR_FERM) {
                PAR--;
            }
            if (tab[i].type == FONCTION && PAR == 0) {
                arbre = ajoutNoeud(arbre, tab[i].type, tab[i].valeur);
                arbre->filsGauche = creationArbre(arbre->filsGauche, reduireTAB(tab, i + 1, taille-1));
            }
            if ((tab[i].type == REEL || tab[i].type == VARIABLE) && PAR == 0){
                arbre = ajoutNoeud(arbre, tab[i].type, tab[i].valeur);
            }
        }
    }
    if (Operateur(tab) != 0) {
        for (i=0; i < taille; i++) {
            if (tab[i].type == PAR_OUV) {
                PAR++;
            }
            if (tab[i].type == PAR_FERM) {
                PAR--;
            }
            if (tab[i].type == OPERATEUR && PAR == 0) {
                arbre = ajoutNoeud(arbre, tab[i].type, tab[i].valeur);
                if (i != 0) {
                    arbre->filsGauche = creationArbre(arbre->filsGauche, reduireTAB(tab, 0, i - 1));
                    arbre->filsDroit = creationArbre(arbre->filsDroit, reduireTAB(tab, i + 1, taille-1));}
            }
        }
    }
    return arbre;
}

//___________________________________________________FONCTION DE TESTS__________________________________________________

void testPARandFONC(){
    Arg test[16];

    test[0].type = PAR_OUV;

    test[1].type = FONCTION;
    test[1].valeur.fonction = COS;

    test[2].type = PAR_OUV;

    test[3].type = REEL;
    test[3].valeur.reel = 3;

    test[4].type = OPERATEUR;
    test[4].valeur.operateur = FOIS;

    test[5].type = VARIABLE;

    test[6].type = PAR_FERM;

    test[7].type = OPERATEUR;
    test[7].valeur.operateur = MOINS;

    test[8].type = VARIABLE;

    test[9].type = OPERATEUR;
    test[9].valeur.operateur = FOIS;

    test[10].type = FONCTION;
    test[10].valeur.fonction = SQRT;

    test[11].type = PAR_OUV;

    test[12].type = REEL;
    test[12].valeur.reel = 34;

    test[13].type = PAR_FERM;

    test[14].type = PAR_FERM;


    test[15].type = FIN;


    erreurPAR(test);
    erreurFONC(test);
}

void testCREEARBRE(){
    Arg test[5];
    test[0].type = FONCTION;
    test[0].valeur.fonction = COS;
    test[1].type = PAR_OUV;
    test[2].type = VARIABLE;
    test[3].type = PAR_FERM;
    test[4].type = FIN;
    Arbre arbre = NULL;
    arbre = creerArbre();
    arbre = creationArbre(arbre, test);
}
