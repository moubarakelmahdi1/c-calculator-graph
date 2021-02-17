#include "includes.h"

int main(int ac,char **av)
{
    /*Init();
    InitGraph(ac,av,"Afficharge de la fonction",1800,1000,myDraw,myKey);
    return 0;*/

    Arg* tab_Arg=(Arg*)malloc(sizeof(struct ArgSt)*20);
    tab_Arg=Tous_les_tests(tab_Arg);
    return 0;
}


