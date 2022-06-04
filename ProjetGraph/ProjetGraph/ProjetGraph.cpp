// ProjetGraph.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "CGraph.h"
#include "CException.h"
#include "COperationGraph.h"

using namespace std;

int main(int argc, char* argv[])
{
    
    unsigned int uiGraphNbRead = argc - 1;
    if (uiGraphNbRead == 0) {
        cerr << "ERREUR : Pas d'arguments passes en parametre" << endl;
        return -1;
    }

    if (uiGraphNbRead > 1) {
        cerr << "ERREUR : Trop d'arguments passes en parametre" << endl;
        return -1;
    }

    cout << "Debut du test : " << endl;
    try {
        CGraph* pGRAGraphTest = new CGraph(argv[1]);
        /*CGraph* pGRAGraphTest = new CGraph();
        pGRAGraphTest->GRASetIsOriented(false);
        pGRAGraphTest->GRAAddNode(1);
        pGRAGraphTest->GRAAddNode(2);
        pGRAGraphTest->GRAAddNode(3);
        pGRAGraphTest->GRAAddNode(4);
        pGRAGraphTest->GRAAddNode(5);

        pGRAGraphTest->GRAAddLinkBetweenNode(1, 5);
        pGRAGraphTest->GRAAddLinkBetweenNode(1, 3);
        pGRAGraphTest->GRAAddLinkBetweenNode(1, 4);
        pGRAGraphTest->GRAAddLinkBetweenNode(5, 3);
        pGRAGraphTest->GRAAddLinkBetweenNode(5, 2);
        pGRAGraphTest->GRAAddLinkBetweenNode(4, 2);
        pGRAGraphTest->GRAAddLinkBetweenNode(4, 3);*/


        COperationGraph* pOPEToolBox = new COperationGraph();

        cout << "---------------------------" << endl;
        cout << "\nAffichage du graphe :\n" << endl;

        pGRAGraphTest->GRAShow();

        CGraph* pGRADual = pOPEToolBox->OPEToDual(pGRAGraphTest);
        cout << "---------------------------" << endl;
        cout << "\nAffichage du graphe dual :\n" << endl;
        pGRADual->GRAShow();

        cout << "---------------------------" << endl;

    }
    catch (CException EXCError) {
        cout << "Error " << EXCError.EXCgetValue() << endl;
    }
    
}