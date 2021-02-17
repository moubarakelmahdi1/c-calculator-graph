#include "includes.h"

int compteur_reel=0;


LISTE remplir_liste_fonction(LISTE liste_reference,char* tab_fonction,typelexem lexem,typefonction fonction) //(y)
{
    LISTE l=(LISTE)malloc(sizeof(struct fonction));
    if(liste_reference==NULL)
    {
        l->tab_fonction =(char*)malloc(sizeof(char)*(strlen(tab_fonction)+1));
        strcpy(l->tab_fonction,tab_fonction);
        l->Arg.valeur.fonction=fonction;
        l->Arg.type=lexem;
    }
    else
    {
        l->tab_fonction =(char*)malloc(sizeof(char)*(strlen(tab_fonction)+1));
        strcpy(l->tab_fonction,tab_fonction);
        l->Arg.valeur.fonction=fonction;
        l->Arg.type=lexem;
        l->suivant = liste_reference;
    }
    liste_reference = l;
    return liste_reference;
}

LISTE remplir_liste_reference(LISTE liste_reference)  //(y)
{
    char* fonction_sin="sin";
    char* fonction_cos="cos";
    char* fonction_log="log";
    char* fonction_exp="exp";
    char* fonction_sinc="sinc";
    char* fonction_sqrt="sqrt";
    char* fonction_abs="abs";
    char* fonction_val_neg="neg";
    char* fonction_entier="entier";
    char* fonction_tan="tan";

    liste_reference=remplir_liste_fonction(liste_reference,fonction_tan,FONCTION,TAN);
    liste_reference=remplir_liste_fonction(liste_reference,fonction_cos,FONCTION,COS);
    liste_reference=remplir_liste_fonction(liste_reference,fonction_log,FONCTION,LOG);
    liste_reference=remplir_liste_fonction(liste_reference,fonction_abs,FONCTION,ABS);
    liste_reference=remplir_liste_fonction(liste_reference,fonction_sin,FONCTION,SIN);
    liste_reference=remplir_liste_fonction(liste_reference,fonction_sinc,FONCTION,SINC);
    liste_reference=remplir_liste_fonction(liste_reference,fonction_sqrt,FONCTION,SQRT);
    liste_reference=remplir_liste_fonction(liste_reference,fonction_exp,FONCTION,EXP);
    liste_reference=remplir_liste_fonction(liste_reference,fonction_val_neg,FONCTION,VAL_NEG);
    liste_reference=remplir_liste_fonction(liste_reference,fonction_entier,FONCTION,ENTIER);

    return liste_reference;
}

void saisir_fonction(char* saisie_fonction)  //(y)
{
    printf ("\nSi a a a a a....tan est affiche, alors il s'agit d'une erreur de token inexistant!");
    printf("\nRentrer ici la fonction souhaitee, entre parentheses et en minuscules sans oublier les *:\n");
    scanf("%s", saisie_fonction);
}

int compteur_jsq_plus_de_lettres(char* saisie_fonction,int compteur)  //(y)
{
    int compteur_debut=compteur;
    int compteur_fin=compteur_debut;
    while((saisie_fonction[compteur_fin]>='a')&&(saisie_fonction[compteur_fin]<='z'))
    {
        compteur_fin++;
    }
    return compteur_fin-compteur_debut;
}

char* tableau_copie_pour_comp_fonction(char* saisie_fonction, int* compteur_saisie)
{
    int compteur_tmp=*compteur_saisie;
    int compteur_tmp2=compteur_tmp;
    int i=0;
    char* tableau_comparaison_fn1=(char*)malloc(sizeof(char)*(compteur_jsq_plus_de_lettres(saisie_fonction,compteur_tmp)));
    while(compteur_tmp!=compteur_tmp2+compteur_jsq_plus_de_lettres(saisie_fonction,compteur_tmp2))
    {
        tableau_comparaison_fn1[i]=saisie_fonction[(*compteur_saisie)+i];
        compteur_tmp++;
        i++;
    }
    return tableau_comparaison_fn1;
}

int compteur_jsq_plus_de_chiffres(char* saisie_fonction,int compteur, int* compteur_points)
{
    int compteur_debut=compteur;
    int compteur_fin=compteur_debut;
    *compteur_points=0;
    while(((saisie_fonction[compteur_fin]>='0')&&(saisie_fonction[compteur_fin]<='9'))||(saisie_fonction[compteur_fin]=='.'))
    {
        if(saisie_fonction[compteur_fin]=='.')
        {
            (*compteur_points)++;
        }
        compteur_fin++;
    }
    return compteur_fin-compteur_debut;
}

char* tableau_copie_pour_reel(char* saisie_fonction, int* compteur_saisie,int* compteur_points)
{
    int compteur_tmp=*compteur_saisie;
    int compteur_tmp2=compteur_tmp;
    int i=0;
    char* tableau_comparaison_fn1=(char*)malloc(sizeof(char)*(compteur_jsq_plus_de_chiffres(saisie_fonction,compteur_tmp,compteur_points)));
    while(compteur_tmp!=compteur_tmp2+compteur_jsq_plus_de_chiffres(saisie_fonction,compteur_tmp2,compteur_points))
    {
        tableau_comparaison_fn1[i]=saisie_fonction[(*compteur_saisie)+i];
        compteur_tmp++;
        i++;
    }
    return tableau_comparaison_fn1;
}

void test_reel(char* saisie_fonction,int* compteur_saisie,Arg* tab, int* compteur_Arg,int* compteur_points)
{
    if((saisie_fonction[*compteur_saisie]>='0')&&(saisie_fonction[*compteur_saisie]<='9'))
    {
        compteur_jsq_plus_de_chiffres(saisie_fonction,*compteur_saisie,compteur_points);

        switch(*compteur_points)
        {
        case 0:
            tab[*compteur_Arg].type=REEL;
            tab[*compteur_Arg].valeur.reel=atof(tableau_copie_pour_reel(saisie_fonction,compteur_saisie,compteur_points));
            *compteur_saisie=*compteur_saisie+compteur_jsq_plus_de_chiffres(saisie_fonction,*compteur_saisie,compteur_points);
            (*compteur_Arg)++;
            break;
        case 1:

            compteur_reel=compteur_reel+1;
            tab[*compteur_Arg].type=REEL;
            tab[*compteur_Arg].valeur.reel=atof(tableau_copie_pour_reel(saisie_fonction,compteur_saisie,compteur_points));
            *compteur_saisie=*compteur_saisie+compteur_jsq_plus_de_chiffres(saisie_fonction,*compteur_saisie,compteur_points);
            (*compteur_Arg)++;
            break;
        default:
            tab[*compteur_Arg].type=ERREUR;
            tab[*compteur_Arg].valeur.erreur=TROP_DE_VIRGULES;
            *compteur_saisie=*compteur_saisie+compteur_jsq_plus_de_chiffres(saisie_fonction,*compteur_saisie,compteur_points);
            (*compteur_Arg)++;
            break;
        }
    }
}

void test_operateur_caracteres_speciaux(char* saisie_fonction,int*compteur_saisie,Arg* tab,int* compteur_Arg)
{
    switch(saisie_fonction[*compteur_saisie])
    {
    case '+':
        tab[*compteur_Arg].type=OPERATEUR;
        tab[*compteur_Arg].valeur.operateur=PLUS;
        (*compteur_saisie)++;
        (*compteur_Arg)++;
        break;
    case '-':
        tab[*compteur_Arg].type=OPERATEUR;
        tab[*compteur_Arg].valeur.operateur=MOINS;
        (*compteur_saisie)++;
        (*compteur_Arg)++;
        break;
    case '/':
        tab[*compteur_Arg].type=OPERATEUR;
        tab[*compteur_Arg].valeur.operateur=DIV;
        (*compteur_saisie)++;
        (*compteur_Arg)++;
        break;
    case '*':
        tab[*compteur_Arg].type=OPERATEUR;
        tab[*compteur_Arg].valeur.operateur=FOIS;
        (*compteur_saisie)++;
        (*compteur_Arg)++;
        break;
    case '^':
        tab[*compteur_Arg].type=OPERATEUR;
        tab[*compteur_Arg].valeur.operateur=PUIS;
        (*compteur_saisie)++;
        (*compteur_Arg)++;
        break;
    case '(':
        tab[*compteur_Arg].type=PAR_OUV;
        (*compteur_saisie)++;
        (*compteur_Arg)++;
        break;
    case ')':
        tab[*compteur_Arg].type=PAR_FERM;
        (*compteur_saisie)++;
        (*compteur_Arg)++;
        break;
    case '[':
        tab[*compteur_Arg].type=BAR_OUV;
        (*compteur_saisie)++;
        (*compteur_Arg)++;
        break;
    case ']':
        tab[*compteur_Arg].type=BAR_FERM;
        (*compteur_saisie)++;
        (*compteur_Arg)++;
        break;
    case '|':
        tab[*compteur_Arg].type=ABSOLU;
        (*compteur_saisie)++;
        (*compteur_Arg)++;
        break;
    case 'x':
        tab[*compteur_Arg].type=VARIABLE;
        (*compteur_saisie)++;
        (*compteur_Arg)++;
        break;
    case '\0':
        tab[*compteur_Arg].type=FIN;
        (*compteur_saisie)++;
        (*compteur_Arg)++;
        break;
    case 'p':
        tab[*compteur_Arg].type=OPERATEUR;
        tab[*compteur_Arg].valeur.operateur=PUIS;
        (*compteur_saisie)++;
        (*compteur_Arg)++;
        break;
    }
}

void test_fonction(char* saisie_fonction,int* compteur_saisie,LISTE liste_fonction,Arg* tab, int* compteur_Arg)
{
    char* test = tableau_copie_pour_comp_fonction(saisie_fonction,compteur_saisie);
    int a = strcmp(test,liste_fonction->tab_fonction);
    if(liste_fonction->suivant->suivant!=NULL)
    {
        if(a==0)
        {
            tab[*compteur_Arg].type=liste_fonction->Arg.type;
            tab[*compteur_Arg].valeur.fonction=liste_fonction->Arg.valeur.fonction;
            *compteur_saisie=*compteur_saisie+compteur_jsq_plus_de_lettres(saisie_fonction,*compteur_saisie);
            (*compteur_Arg)++;
        }
        else
        {
            if(liste_fonction->suivant!=NULL)
            {
                test_fonction(saisie_fonction,compteur_saisie,liste_fonction->suivant,tab,compteur_Arg);
            }
            tab[*compteur_Arg].type=ERREUR;
            tab[*compteur_Arg].valeur.erreur=NO_TOKEN;
        }
    }
}

Arg* Tous_les_tests(Arg* tab_Arg)
{
    compteur_reel=0;
    int* compteur_saisie=(int*)malloc(sizeof(int));
    *compteur_saisie=0;
    int* compteur_Arg=(int*)malloc(sizeof(int));
    *compteur_Arg=0;
    int* compteur_points=(int*)malloc(sizeof(int));
    *compteur_points=0;
    LISTE liste_reference;
    liste_reference=(LISTE)malloc(sizeof(struct fonction));
    liste_reference=remplir_liste_reference(liste_reference);
    int i=0;
    char saisie_fonction[20];
    saisir_fonction(saisie_fonction);
    for(i=0; i<20; i++)
    {
        test_reel(saisie_fonction,compteur_saisie,tab_Arg,compteur_Arg,compteur_points);
        test_fonction(saisie_fonction,compteur_saisie,liste_reference,tab_Arg,compteur_Arg);
        test_operateur_caracteres_speciaux(saisie_fonction,compteur_saisie,tab_Arg,compteur_Arg);
    }
    if(compte_virgule(saisie_fonction)>compteur_reel)
    {
        free(saisie_fonction);
        free(compteur_Arg);
        free(compteur_points);
        free(compteur_saisie);
        free(liste_reference);
        printf("ERREUR-TROP DE VIRGULES\n");
        Tous_les_tests(tab_Arg);
    }
    if(erreurOPP(tab_Arg)==1)
    {
        free(saisie_fonction);
        free(compteur_Arg);
        free(compteur_points);
        free(compteur_saisie);
        free(liste_reference);
        Tous_les_tests(tab_Arg);
    }
    if(erreurPAR(tab_Arg)==1)
    {
        free(saisie_fonction);
        free(compteur_Arg);
        free(compteur_points);
        free(compteur_saisie);
        free(liste_reference);
        Tous_les_tests(tab_Arg);
    }
    if(erreurFONC(tab_Arg)==1)
    {
        free(saisie_fonction);
        free(compteur_Arg);
        free(compteur_points);
        free(compteur_saisie);
        free(liste_reference);
        Tous_les_tests(tab_Arg);
    }
    free(compteur_Arg);
    free(compteur_points);
    free(compteur_saisie);
    free(liste_reference);
    return tab_Arg;
}

int compte_virgule(char saisie_fonction[TAILLE_ARG])
{
    int virgule;
    int i=0;
    int j=0;
    while(i<TAILLE_ARG&&saisie_fonction[i]!='\0')
    {
        if(saisie_fonction[i]=='.')
        {
            j=j+1;
        }
        i=i+1;
    }
    return j;
}

