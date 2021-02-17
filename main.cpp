#include "includes.h"

int main(int ac,char **av)
{
    Init();
    InitGraph(ac,av,"Afficharge de la fonction",1800,1000,myDraw,myKey);
    return 0;
}


