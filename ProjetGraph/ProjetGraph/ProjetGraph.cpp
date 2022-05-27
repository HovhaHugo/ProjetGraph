// ProjetGraph.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "CGraph.h"
#include "CException.h"

using namespace std;

int main()
{
    try {

        /*const char* path = "C:\\Users\\mathi\\OneDrive\\Bureau\\test.txt";

        CGraph* test = new CGraph(path);

        test->GRAShow();*/

        
        
        CGraph* test = new CGraph();
        //CNode node2 = new CNode(2);
        test->GRAAddNode(1);
        test->GRAAddNode(2);
        test->GRAAddNode(3);
        test->GRAAddLinkBetweenNode(1, 2);

        cout << "Premier affichage, ajout d'un lien de 1 vers 2 " << endl;
        test->GRAShow();

        test->GRAAddLinkBetweenNode(2, 1);
        cout << "\nDeuxieme affichage, ajout d'un lien de 2 vers 1" << endl;
        test->GRAShow();

        test->GRARemoveLinkBetweenNode(1, 2);
        cout << "\nTroisieme affichage, apres suppression du lien 1 vers 2 " << endl;
        test->GRAShow();

        test->GRAAddLinkBetweenNode(1, 2);
        cout << "\nQuatrieme affichage, on remet un lien 1 vers 2 " << endl;
        test->GRAShow();

        test->GRAChangeNodeValue(1,4);
        cout << "\nQuatrieme 2 affichage, on change le noeud 1 a 4 " << endl;
        test->GRAShow();

        test->GRAChangeLinkDestination(4, 2, 3);
        cout << "\nCinquieme affichage, on change la destination de 4 vers 2 a 4 vers 3 " << endl;
        test->GRAShow();

        test->GRARemoveNode(3);
        cout << "\nSixieme affichage, on supprime le noeud 3 " << endl;
        test->GRAShow();

        CGraph* copy = new CGraph(test);

        cout << "\nSeptieme affichage, on affiche la copie du graphe " << endl;
        copy->GRAShow();

        CGraph* inverse = copy->GRAInverse();

        cout << "\nHuitieme affichage, on affiche le graphe inverse " << endl;
        inverse->GRAShow();

        delete test;

        cout << "\nNeuvieme affichage, on affiche la copie du graphe " << endl;
        copy->GRAShow();
        //On ne peut pas delete copy car je sais pas pourquoi mais après avoir supprime
        // test, les liens de copy sont aussi supprimes, alors qu'ils ont ete cree avec new. A voir comment ca fonctionne
        //delete copy;

        
    }
    catch (CException EXCError) {
        cout << "Error " << EXCError.EXCgetValue() << endl;
    }
    
}