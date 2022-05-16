
//Le prof a dit a un eleve que pour supprimer un arc c'est le graphe qui s'en occupait, qu'il possedait une liste
//d'arc. Il a dit que c'etait pas du tout logique mais que c'etait sa solution par rapport au sujet tel qui est
//propose
#include "CGraph.h"
#include "CException.h"


/**
 * Default constructor of CGraph
 * Input: /
 * Output: /
 * Precondition : /
 * Postcondition : the object has been created in memory with uiGRASize = 0 and pNODGRANodeList = nullptr
 */
CGraph::CGraph() {
    pNODGRANodeList = nullptr;
    uiGRASize = 0;
}


/**
 * Default constructor of CGraph
 * Input: /
 * Output: /
 * Precondition : /
 * Postcondition : the object has been created in memory with uiGRASize = 0 and pNODGRANodeList = nullptr
 */
CGraph::CGraph(char* pcFilePath) {
    //Appel du parseur
}


/**
 * Destructor of CGraph
 * Input: /
 * Output: /
 * Precondition : /
 * Postcondition : the object has been deleted from memory
 */
CGraph::~CGraph() {
    pNODGRANodeList = nullptr;
    uiGRASize = 0;
}


/**
 * Show a graph
 * Input: /
 * Output: /
 * Precondition : /
 * Postcondition : The graph is shown in the console
 */
void CGraph::GRAShow() {

    for (unsigned int uiLoop = 0; uiLoop < uiGRASize; uiLoop++) {
        pNODGRANodeList[uiLoop].NODShow();
    }
}


/**
 * Add a link between 2 nodes of the graph
 * Input: uiValueNodeSource : unsigned int, uiValueNodeDestination : unsigned int
 * Output: /
 * Precondition : /
 * Postcondition : If at least 1 of the 2 nodes is not in the graph an error is throw, else
    a link is created between the 2 nodes
 */
void CGraph::GRAAddLinkBetweenNode(unsigned int uiValueNodeSource, unsigned int uiValueNodeDestination) {

    //Check if the 2 nodes exist in the graph
    CNode* pcSource = nullptr;
    CNode* pcDestination = nullptr;
    try {
        pcSource = GRAGetNode(uiValueNodeSource);
        pcDestination = GRAGetNode(uiValueNodeDestination);
    }
    catch (CException EXCError) {
        throw EXCError;
    }

    //Creation of the new link
    CLink* LINNew = new CLink();

    LINNew->LINSetEnd(pcDestination->NODGetValue());

    pcSource->NODAddOutputLink(*LINNew);
    pcDestination->NODAddInputLink(*LINNew);

    //If the graph is oriented, create a new link in the other direction
    if (bGRAIsOriented) {
        CLink* LINNewBack = new CLink();

        LINNewBack->LINSetEnd(pcSource->NODGetValue());

        pcDestination->NODAddOutputLink(*LINNew);
        pcSource->NODAddInputLink(*LINNew);
    }

}


/**
 * Remove a link between 2 nodes of the graph
 * Input: uiValueNodeSource : unsigned int, uiValueNodeDestination : unsigned int
 * Output: /
 * Precondition : /
 * Postcondition : If at least 1 of the 2 nodes is not in the graph an error is throw, same if
 *  there is not an existing link between theses nodes.
 *  Else, the link is removed and deleted from memory
 */
void CGraph::GRARemoveLinkBetweenNode(unsigned int uiValueNodeSource, unsigned int uiValueNodeDestination) {

    //Check if the 2 nodes exist in the graph
    CNode* pcSource = nullptr;
    CNode* pcDestination = nullptr;
    try {
        pcSource = GRAGetNode(uiValueNodeSource);
        pcDestination = GRAGetNode(uiValueNodeDestination);
    }
    catch (CException EXCError) {
        throw CException(EXCEPTION_NODE_NOT_FOUND);
    }

    CLink* pLINLinkToRemove = nullptr;

    //We try to get the link and delete the pointer is the 2 involved nodes
    //Then we delete the link
    try {
        pLINLinkToRemove = pcSource->NODGetLinkTowardNode(uiValueNodeDestination);
        pcSource->NODRemoveOutputLink(*pLINLinkToRemove);
        pcDestination->NODRemoveInputLink(*pLINLinkToRemove);
        delete pLINLinkToRemove;
    }
    catch (CException EXCError) {
        throw EXCError;
    }

    //If the graph is oriented, we remove in the other direction
    if (bGRAIsOriented) {

        CLink* pLINLinkToRemoveBack = nullptr;

        //We try to get the link and delete the pointeur is the 2 concerned nodes
        //Then we delete the link
        try {
            pLINLinkToRemoveBack = pcDestination->NODGetLinkTowardNode(uiValueNodeSource);
            pcDestination->NODRemoveOutputLink(*pLINLinkToRemoveBack);
            pcSource->NODRemoveInputLink(*pLINLinkToRemoveBack);
            delete pLINLinkToRemove;
        }
        catch (CException EXCError) {
            throw EXCError;
        }


    }

}


/**
 * Add a node to the graph
 * Input: NODParam : CNode&
 * Output: /
 * Precondition : /
 * Postcondition : If the node are already in the graph an error is throw, else
    the NODParam is added to the graph and uiGRASize is incremented
 */
void CGraph::GRAAddNode(CNode& NODParam) {

    uiGRASize++;
    pNODGRANodeList = realloc(pNODGRANodeList, uiGRASize * sizeof(CNode));
    pNODGRANodeList[uiGRASize - 1] = NODParam;

}


/**
 * Remove a node from the graph
 * Input: NODParam : CNode&
 * Output: /
 * Precondition : /
 * Postcondition : If the node are not in the graph an error is throw, else
    the NODParam is removed from the graph and uiGRASize is decremented
 */
void CGraph::GRARemoveNode(unsigned int uiValue) {

    //Check if the node exists in the graph
    CNode* pNODFound = nullptr;
    for (int uiLoop = 0; uiLoop < uiGRASize; uiLoop++) {
        if (pNODGRANodeList[uiLoop].NODGetValue() == uiValue) {
            pNODFound = (pNODGRANodeList + uiLoop);
        }
    }
    if (pNODFound == false) {
        throw CException(EXCEPTION_NODE_NOT_FOUND);
    }

    /*
    if the graph is oriented, the fastest method is to browse the entire graph and
    use the GRARemoveLinkBetweenNode method which allows you to remove all the links in 2 nodes
    */
    if (bGRAIsOriented) {

        for (int uiLoop = 0; uiLoop < uiGRASize; uiLoop++) {

            try {
                GRARemoveLinkBetweenNode(uiValue, pNODGRANodeList[uiLoop].NODGetValue());
            }
            catch (CException EXCError) {
                //Ignored : there is just no link
            }

        }

    }
    else {  //If the graph is not oriented, it needs to be removed more methodically

        //We remove all the links in destination of this node
        for (int uiLoop = 0; uiLoop < uiGRASize; uiLoop++) {

            CLink* pLINFound = pNODGRANodeList[uiLoop].NODGetLinkTowardNode(uiValue);
            if (pLINFound != nullptr) {
                pNODFound->NODRemoveInputLink(*pLINFound);
                pNODGRANodeList[uiLoop].NODRemoveOutputLink(*pLINFound);
                delete(pLINFound);
            }

        }

        //We remove all the links starting on this node
        //Note: We could also have used the same principe as before but this time we will take advantage of the getters

        //we get all the outputs of the node that we want to delete
        unsigned int uiSize = 0;
        CLink** ppLINOutputLinkFromNode = pNODFound->NODGetOutputLink(&uiSize);

        for (unsigned int uiLoop = 0; uiLoop < uiSize; uiLoop++) {

            CLink* pLINFound = pNODFound->NODGetLinkTowardNode(pNODGRANodeList[uiLoop].NODGetValue());
            if (pLINFound != nullptr) {
                pNODFound->NODRemoveInputLink(*pLINFound);
                pNODGRANodeList[uiLoop].NODRemoveInputLink(*pLINFound);
                delete(pLINFound);
            }

        }

    }//else 

    //Remove the node from the list
    for (int uiLoop = 0; uiLoop < uiGRASize - 1; uiLoop++) {

        if ((pNODGRANodeList + uiLoop) == pNODFound) {

            for (int uiLoopEnd = uiLoop; uiLoopEnd < uiGRASize - 1; uiLoopEnd++) {
                pNODGRANodeList[uiLoopEnd] = *(pNODGRANodeList + uiLoopEnd + 1);
            }

        }
    }

    //all links and references to or from this node have been removed from other nodes and the graph

    delete pNODFound;

    uiGRASize--;
    pNODGRANodeList = realloc(pNODGRANodeList, uiGRASize * sizeof(CNode));

}


/**
 * Get a node from the graph
 * Input: uiNumber : unsigned int
 * Output: CNode*
 * Precondition : /
 * Postcondition : If the node are not in the graph an error is throw, else
    the CNode is returned
 */
CNode* CGraph::GRAGetNode(unsigned int uiNumber) {

    CNode* pNODFound = nullptr;

    for (int uiLoop = 0; uiLoop < uiGRASize; uiLoop++) {

        if (pNODGRANodeList[uiLoop].NODGetValue() == uiNumber)
            pNODFound = (pNODGRANodeList + uiLoop);
    }

    //If the node wasn't found
    if (pNODFound == nullptr) {
        throw CException(EXCEPTION_NODE_NOT_FOUND);
    }

    return pNODFound;

}


/**
 * Getter of bGRAIsOriented
 * Input: /
 * Output: bool
 * Precondition : /
 * Postcondition : bGRAIsOriented is returned
 */
bool CGraph::GRAGetIsOriented() {
    return bGRAIsOriented;
}

