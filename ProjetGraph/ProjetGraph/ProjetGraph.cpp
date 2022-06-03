// ProjetGraph.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "CGraph.h"
#include "CException.h"

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

        cout << "---------------------------" << endl;
        cout << "\nAffichage du graphe :\n" << endl;
        CGraph* pGRAGraphTest = new CGraph(argv[1]);

        pGRAGraphTest->GRAShow();

        CGraph* inverse = pGRAGraphTest->GRAInverse();
        cout << "---------------------------" << endl;
        cout << "\nAffichage de l'inverse :\n" << endl;
        inverse->GRAShow();

        cout << "---------------------------" << endl;

    }
    catch (CException EXCError) {
        cout << "Error " << EXCError.EXCgetValue() << endl;
    }
    
}