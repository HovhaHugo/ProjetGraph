// ProjetGraph.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "CGraph.h"
#include "CException.h"

using namespace std;

int main()
{
    try {
        CGraph* test = new CGraph();
        CNode node1 = new CNode(1);
        //CNode node2 = new CNode(2);
        test->GRAAddNode(1);
        test->GRAAddNode(2);
        test->GRAAddNode(3);
        test->GRAAddLinkBetweenNode(1, 2);

        cout << "Premier affichage " << endl;
        test->GRAShow();

        test->GRAAddLinkBetweenNode(2, 1);
        cout << "\nDeuxieme affichage " << endl;
        test->GRAShow();

        test->GRARemoveLinkBetweenNode(1, 2);
        cout << "\nTroisieme affichage, apres suppression du lien 1 vers 2 " << endl;
        test->GRAShow();

        test->GRAAddLinkBetweenNode(1, 2);
        cout << "\nQuatrieme affichage, on remet un lien 1 vers 2 " << endl;
        test->GRAShow();

        test->GRAChangeLinkDestination(1, 2, 3);
        cout << "\nCinquieme affichage, on change la destination de 1 vers 2 a 1 vers 3 " << endl;
        test->GRAShow();

        test->GRARemoveNode(3);
        cout << "\nSixieme affichage, on supprime le noeud 3 " << endl;
        test->GRAShow();

    }
    catch (CException EXCError) {
        cout << "Error " << EXCError.EXCgetValue() << endl;
    }
    
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
