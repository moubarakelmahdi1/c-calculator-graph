
#include "includes.h"


//Graphique à deux dimensions., l'une pour les abscisses et l'autre pour les ordonnées
float tab[TAILLE_TABLEAU][3];
//Pas correspondant à la différence d'abscisse entre chaque point du tableau
float pas;
//Valeur maximale que peut atteindre notre courbe
float maximum;
//Valeur minimal que peut atteindre notre courbe
float minimum;
//Plus grand extremum
float base;
//Ecart entre la borne inférieur et la borne supérieur
float ecartX;
//Ecart entre la valeur maximale et la valeur minimale, nous permettra de normaliser par rapport à la plus grande valeur
float ecartY;
//Borne inférieur choisie par l'utilisateur
float borneInf;
//Borne supérieur choisie par l'utilisateur
float borneSup;

float zoomHauteur=1;
//Indice de zoom en largeur initialisé à 1, nous permettra de limité le zoom minimal 0,1
float zoomLargeur=1;
//Indice de décalage de la courbe, nous permettra de décaler les bornes à la demande de l'utilisateur
int decalage=0;
//Curseur de la courbe
int curseur=10;
//Bascule permettant d'afficher ou de masquer la grille du graphique
int bascule=0;

int* ERREUR2=new int[1];


//int* ERREUR_CURSEUR=0;

//Fonction permettant de détérminer si une chaine de caractère est un nombre ou pas
//Obligera l'utilisateur à rentrer des bornes correctes
int estUnNombre(char nombre[TAILLE_BORNES])
{
    int i=0;
    int res = 1;
    while(nombre[i]!='\0')
    {
        //On test si le caractère correspond à un nombre en ascii, à un point ou un moins en début de chaîne
        if(nombre[i]<48||nombre[i]>57)
        {
            if(nombre[i]!=46)
            {
                if(nombre[i]!=45&&i!=0)
                {
                    res = 0;
                }
            }
        }
        i=i+1;
    }
    return res;
}

void remplir_Tableau()
{
    //Fonction test permettant de remplir un tableau de valeur x et f(x)=sin(x) avec les bornes entrées par l'utilisateur
    ecartX = sqrt((borneSup-borneInf)*(borneSup-borneInf));
    pas = ecartX/TAILLE_TABLEAU;
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
    for(int i=0; i<TAILLE_TABLEAU; i++)
    {
        //x, on incrémente d'un pas entre chaque x du tableau
        tab[i][1]=(float)(borneInf+i*pas);
        //f(x)
        tab[i][2]=(float)eval(arbre,tab[i][1],ERREUR2);

        tab[i][3]=(float)*ERREUR2;

        if(i==0)
        {
            maximum=tab[i][2];
            minimum=tab[i][2];
        }
        //On cherche les minimum, maximum et écart de la fonction pour la normalisation dans l'affichage
        if(tab[i][2]>maximum)
        {
            maximum=tab[i][2];
        }
        if(tab[i][2]<minimum)
        {
            minimum=tab[i][2];
        }
    }
    if(abs(minimum)>=abs(maximum))
    {
        if(minimum<0)
        {
            base = (float)minimum *(-1);
        }
        else
        {
            base = (float)minimum;
        }
    }
    else
    {
        if(maximum<0)
        {
            base = (float)maximum *(-1);
        }
        else
        {
            base = (float)maximum;
        }
    }
    ecartY = sqrt((maximum-minimum)*(maximum-minimum));
}

void myDraw(void)
{
    remplir_Tableau();

    //On positionne le curseur dans le graphique
    setcolor(1.0F,1.0F,1.0F);
    if((float)(tab[curseur][2]/base)*0.8*zoomHauteur<0.8&&(float)(tab[curseur][2]/base)*0.8*zoomHauteur>-0.8)
    {
        outtextxy((float)(((2*(tab[curseur][1]-borneInf))/ecartX)-1)-0.0075,(float)(tab[curseur][2]/base)*0.8*zoomHauteur+0.008,"_");
        outtextxy((float)(((2*(tab[curseur][1]-borneInf))/ecartX)-1)-0.0035,(float)(tab[curseur][2]/base)*0.8*zoomHauteur-0.0125,"|");
    }

    //On ne veut pas que le curseur puisse aller au delas de 0.8 et au dessus de -0.8 (zone délimité du graphique)
    else if((float)(tab[curseur][2]/base)*0.8*zoomHauteur>0.8)
    {
        outtextxy((float)(((2*(tab[curseur][1]-borneInf))/ecartX)-1)-0.0075,0.8+0.008,"_");
        outtextxy((float)(((2*(tab[curseur][1]-borneInf))/ecartX)-1)-0.0035,0.8-0.0125,"|");
    }
    else
    {
        outtextxy((float)(((2*(tab[curseur][1]-borneInf))/ecartX)-1)-0.0075,-0.8+0.008,"_");
        outtextxy((float)(((2*(tab[curseur][1]-borneInf))/ecartX)-1)-0.0035,-0.8-0.0125,"|");
    }

    //On affiche les valeurs x et f(x) pointées par le curseur
    char x[TAILLE_VALEUR];
    char fx[TAILLE_VALEUR];
    sprintf(x,"%0.02f",tab[curseur][1]);
    sprintf(fx,"%0.02f",tab[curseur][2]);
    switch((int)tab[curseur][3])
        {
        case 0:
            outtextxy(0.48,-0.9,fx);
            break;
        case 1:
            outtextxy(0.48,-0.9,"ERR ARBRE");
            break;
        case 2:
            outtextxy(0.48,-0.9,"ERR LOG");
            break;
        case 3:
            outtextxy(0.48,-0.9,"ERR TYPE");
            break;
        case 4:
            outtextxy(0.48,-0.9,"ERR DIV0");
            break;
        case 5:
            outtextxy(0.48,-0.9,"ERR TAN");
            break;
        case 6:
            outtextxy(0.48,-0.9,"ERR SQRT");
            break;
        case 7:
            outtextxy(0.48,-0.9,"ERR SINC");
            break;
        }

    outtextxy(0.2,-0.9,"X = ");
    outtextxy(0.25,-0.9,x);
    outtextxy(0.4,-0.9,"F(X) = ");


    //On affiche les indices de zoom aux extremités de chaque axe du graphique
    char zoomhauteur[TAILLE_VALEUR];
    char zoomlargeur[TAILLE_VALEUR];
    sprintf(zoomhauteur,"%0.1f",zoomHauteur);
    sprintf(zoomlargeur,"%0.1f",zoomLargeur);
    outtextxy(-0.2,0.85,"Zoom Hauteur *");
    outtextxy(-0.015,0.85,zoomhauteur);
    outtextxy(0.95,-0.1,zoomlargeur);
    outtextxy(0.765,-0.1,"Zoom Largeur *");

    //On affiche les commandes pour l'utilisateur en dessous du graphique
    outtextxy(-0.9,-0.9,"Zoom Hauteur:+c/-v   Zoom Largeur:+b/-n   Translater:Droite=q Gauche=d   Curseur: +x/-w");
    outtextxy(0.7,-0.9,"Afficher/Masquer grille: a");

    //Deux chaines de caractères sont crées pour stocker les graduations des abscisses et des ordonnées
    char valeur[TAILLE_VALEUR];
    char valeur2[TAILLE_VALEUR];
    //Si la bascule est activée (bouton a) on trace la grille et on affiche graduations
    if(!bascule)
    {
        for(int j=0; j<4; j++)
        {
            line(-1,(float)j/5,1,(float)j/5);
            line(-1,(float)(-1)*j/5,1,(float)(-1)*j/5);
            if(j!=0)
            {
                sprintf(valeur,"%0.02f",(float)j*maximum/(4*zoomHauteur));
                sprintf(valeur2,"%0.02f",(float)-j*maximum/(4*zoomHauteur));
                //On fait en sorte que les graduations des ordonnées reste sur l'écran même si l'axe est décalé
                if(-0.08-(float)decalage/20>-0.975||-0.08-(float)decalage/20<0.950)
                {
                    outtextxy(-0.06-(float)decalage/20,(float)j/5+0.02,valeur);
                    outtextxy(-0.08-(float)decalage/20,(float)-j/5-0.08,valeur2);
                }
                if(-0.08-(float)decalage/20<-0.975)
                {
                    outtextxy(-0.975,(float)j/5+0.02,valeur);
                    outtextxy(-0.975,(float)-j/5-0.08,valeur2);
                }
                if(-0.08-(float)decalage/20>0.950)
                {
                    outtextxy(0.950,(float)j/5+0.02,valeur);
                    outtextxy(0.950-0.02,(float)-j/5-0.08,valeur2);
                }
            }
        }
        for(int k=0; k<5; k++)
        {
            line((float)k/5,-0.79,(float)k/5,0.79);
            line((-1)*(float)k/5,-0.79,(-1)*(float)k/5,0.79);
            sprintf(valeur,"%0.02f",tab[750+(k*750/5)][1]/zoomLargeur);
            outtextxy((float)k/5+0.02,-0.05,valeur);
            if(k!=0)
            {
                sprintf(valeur2,"%0.02f",tab[750-(k*750/5)][1]/zoomLargeur);
                outtextxy((float)-k/5-0.08,-0.05,valeur2);
            }
        }

    }

    //On trace les délimitations de notre graphique
    setcolor(1.0F,0.0F,0.0F);
    line(-1,0.8,1,0.8);
    line(-1,-0.8,1,-0.8);

    //On trace notre courbe. Pour cela, il faut tracer une droite entre chaque couple de point consécutif avec la fonction line
    for(int i=0; i<TAILLE_TABLEAU-2; i++)
    {
        //On normalise par rapport aux bornes et a au plus grand extremum que peut atteindre notre courbe
        float x0=(float)(((2*(tab[i][1]-borneInf))/ecartX)-1);
        float y0=(float)(tab[i][2]/base)*0.8*zoomHauteur;
        float x1=(float)(((2*(tab[i+1][1]-borneInf))/ecartX)-1);
        float y1=(float)(tab[i+1][2]/base)*0.8*zoomHauteur;
        //On fait toujours en sorte que la courbe ne puisse pas dépasser la zone délimité du graphique
        if(y0>0.8||y1>0.8)
        {
            y0=0.8;
            y1=0.8;
        }
        if(y0<-0.8||y1<-0.8)
        {
            y0=-0.8;
            y1=-0.8;
        }
        setcolor(1.0F,1.0F,0.0F);
        if(tab[i][3]==0)
        {
            line(x0,y0,x1,y1);
        }
    }
    //On trace les axes des abscisses et des ordonnées
    setcolor(0.0F,1.0F,0.0F);
    line((((-borneInf)/ecartX)*2)-1,0.8,(((-borneInf)/ecartX)*2)-1,-0.8);
    line(-1,(((-minimum)/ecartY)*2)-1,1,(((-minimum)/ecartY)*2)-1);
}

void myKey(int c)
{
    switch(c)
    {
    case 'a':
        bascule^=1; /* La bascule passe alternativement de 0 a 1, nous permettra d'afficher ou masquer la grille et les graduations du graphique */
        break;
    case 'c': //le bouton c permet de zoomer en hauteur
        zoomHauteur = zoomHauteur + 0.1;
        remplir_Tableau();
        break;
    case 'q': //le bouton q permet de décaler la courbe vers la droite, pour cela on élargie les bornes de notre graphique
        borneInf = borneInf - 0.5;
        borneSup = borneSup - 0.5;
        decalage = decalage - 1;
        remplir_Tableau();
        break;
    case 'v': //Le bouton v permet de dézoomer en hauteur
        if(zoomHauteur>0.1)
        {
            zoomHauteur = zoomHauteur - 0.1;
            remplir_Tableau();
        }
        break;
    case 'd': //Le bouton d permet de décaler la courbe vers la gauche, pour cela on retrécie les bornes de notre graphique
        borneInf = borneInf + 0.5;
        borneSup = borneSup + 0.5;
        decalage = decalage + 1;
        remplir_Tableau();
        break;
    case 'b': //Le bouton b permet de zoomer en largeur, pour cela on modifie les bornes du graphique
        zoomLargeur = zoomLargeur + 0.1;
        borneInf= 0.9*borneInf;
        borneSup= 0.9*borneSup;
        remplir_Tableau();
        break;
    case 'n': //le bouton n permet de dézoomer en largeur avec une limite à 0.1, pour cela on modifie les bornes du graphiques
        if(zoomLargeur>0.1)
        {
            zoomLargeur = zoomLargeur - 0.1;
            borneInf = borneInf * 1.1;
            borneSup = borneSup * 1.1;
            remplir_Tableau();
        }
        break;
    case 'w': //le bouton w permet de déplacer le cuseur vers la gauche
        if(curseur<1500)
        {
            curseur = curseur - 10;
            if(curseur<10)
            {
                curseur = 1480;
            }
        }
        else
        {
            curseur = 10;
        }
        break;
    case 'x': //Le bouton x permet de déplacer le curseur vers la droite. Si on attend l'extreme droit du graphique, le curseur est ramené à gauche
        if(curseur>0)
        {
            curseur = curseur + 10;
            if(curseur>1480)
            {
                curseur = 10;
            }
        }
        else
        {
            curseur = 1480;
        }
        break;
    }
}

void Init()
{
    // Lecture des bornes
    printf("Fonction test: f(x)=sin(x)\n");
    char inf[TAILLE_BORNES];
    char sup[TAILLE_BORNES];
    printf("\nEntrez la borne inferieur:\n");
    scanf("%s",&inf);
    printf("\nEntrez la borne superieur:\n");
    scanf("%s",&sup);

    //On vérifie si les bornes entrées par l'utilisateur sont correctes
    while(estUnNombre(inf)==0||estUnNombre(sup)==0||atoi(inf)>=atoi(sup))
    {
        system("cls");
        printf("Fonction test: f(x)=sin(x)\n");
        printf("\nEntrez des bornes correctes!!\n");
        printf("\nEntrez la borne inferieur:\n");
        scanf("%s",&inf);
        printf("\nEntrez la borne superieur:\n");
        scanf("%s",&sup);
    }

    //On convertie bornes string en float, puis on remplie notre tableau
    borneInf=atof(inf);
    borneSup=atof(sup);
    remplir_Tableau();
    //On initialise le graphqiue
}




