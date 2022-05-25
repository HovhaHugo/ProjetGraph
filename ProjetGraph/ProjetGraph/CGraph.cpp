#include "CParser.h"
#include "CException.h"
#include "CGraph.h"
#include <malloc.h>


/**
 * Default constructor of CGraph
 * Input: /
 * Output: /
 * Precondition : /
 * Postcondition : the object has been created in memory with uiGRASize = 0 and pNODGRANodeList = nullptr
 */
CGraph::CGraph() {
    uiGRASize = 0;
    pNODGRANodeList = (CNode*)malloc(sizeof(CNode) * uiGRASize);
    bGRAIsOriented = false;
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
    CParser* pPARParser;
    try {
        pPARParser = new CParser(pcFilePath);
    }
    catch (CException EXCError) {
        throw EXCError;
    }

    //The parser doesn't know if the graph is oriented
    bGRAIsOriented = false;

    unsigned int uiNbOfNode = pPARParser->PARGetNumber("NBSommets");
    unsigned int uiNbOfLink = pPARParser->PARGetNumber("NBArcs");

    CNode* pNODNodeList = pPARParser->PARGetNodes(uiNbOfNode,"Sommets");

    //temporary lists of link data are created in memory 
    int* piListLinkFrom = (int*)malloc(sizeof(int) * uiNbOfLink);
    if (piListLinkFrom == nullptr)
        throw CException();

    int* piListLinkTo = (int*)malloc(sizeof(int) * uiNbOfLink);
    if (piListLinkTo == nullptr) {
        free(piListLinkFrom);
        throw CException();
    }

    //Fill the previous lists
    pPARParser->PARGetLink(piListLinkFrom, piListLinkTo, uiNbOfLink, "Arcs");

    //Add link between the nodes
    try {
        for (unsigned int uiLoop = 0; uiLoop < uiNbOfLink; uiLoop++) {
            GRAAddLinkBetweenNode(*(piListLinkFrom + uiLoop), *(piListLinkTo + uiLoop));
        }
    }
    catch (CException EXCError) {
        throw EXCError;
    }
   

}


/**
 * Destructor of CGraph
 * Input: /
 * Output: /
 * Precondition : /
 * Postcondition : the object has been deleted from memory
 */
CGraph::~CGraph() {
    //Destruction des neouds à l'intérieur
    for (unsigned int uiLoopNode = 0; uiLoopNode < uiGRASize; uiLoopNode++) {
        unsigned int uiSizeNode = 0;
        CLink** ppLINLinkList = pNODGRANodeList[uiLoopNode].NODGetInputLink(&uiSizeNode);

        for (unsigned int uiLoopLink = 0; uiLoopLink < uiSizeNode; uiLoopLink++) {
            pNODGRANodeList[1].NODRemoveInputLink(*ppLINLinkList[uiLoopNode]);
        }

        delete (pNODGRANodeList+uiLoopNode);
    }
    delete pNODGRANodeList;


    bGRAIsOriented = false;
    uiGRASize = 0;
}


/**
 * Constructor by copy of CGraph
 * Input: /
 * Output: /
 * Precondition : /
 * Postcondition : the object has been created in memory with this = pGRAToCopy
 */
CGraph::CGraph(CGraph* pGRAToCopy) {
    uiGRASize = pGRAToCopy->uiGRASize;
    pNODGRANodeList = pGRAToCopy->pNODGRANodeList;
    bGRAIsOriented = pGRAToCopy->bGRAIsOriented;
}


/**
 * Function that inverte a graph (mean that each arc change their start for their beginging)
 * Input: /
 * Output: /
 * Precondition : /
 * Postcondition : the grpah has been inverted
 */
CGraph* CGraph::GRAInverse() {
    //We create a new object
    CGraph* pGRANewGraph = new CGraph();

    pGRANewGraph->bGRAIsOriented = GRAGetIsOriented();
    unsigned int uiSize = 0;
    GRAGetNode(uiSize);

    //For each node, we recopy them all in the new graph
    for (unsigned int uiLoopNode = 0; uiLoopNode < uiSize; uiLoopNode++) {
        pGRANewGraph->GRAAddNode(GRAGetNode(uiLoopNode)->NODGetValue());

        //For each input on the node, we add the link reversed une our graph
        unsigned int uiSizeLinkInput = 0;
        CLink** ppLINInputLink = GRAGetNode(uiLoopNode)->NODGetInputLink(&uiSizeLinkInput);
        for (unsigned int uiLoopLinkInput = 0; uiLoopLinkInput < uiSizeLinkInput; uiLoopLinkInput++) {
            unsigned int uiEnd = ppLINInputLink[uiLoopLinkInput]->LINGetEnd();
            pGRANewGraph->GRAAddLinkBetweenNode(uiLoopNode, uiEnd);
        }

        //For each output on the node, we add the link reversed une our graph
        unsigned int uiSizeLinkOutput = 0;
        GRAGetNode(uiLoopNode)->NODGetOutputLink(&uiSizeLinkOutput);
        CLink** ppLINOutputLink = GRAGetNode(uiLoopNode)->NODGetInputLink(&uiSizeLinkInput);
        for (unsigned int uiLoopLinkOutput = 0; uiLoopLinkOutput < uiSizeLinkOutput; uiLoopLinkOutput++) {
            unsigned int uiEnd = ppLINOutputLink[uiLoopLinkOutput]->LINGetEnd();
            pGRANewGraph->GRAAddLinkBetweenNode(uiEnd, uiLoopNode);
        }
    }
    return pGRANewGraph;
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
    CNode* pNODSource = nullptr;
    CNode* pNODDestination = nullptr;
    try {
        pNODSource = GRAGetNode(uiValueNodeSource);
        pNODDestination = GRAGetNode(uiValueNodeDestination);
    }
    catch (CException EXCError) {
        throw EXCError;
    }

    //Creation of the new link
    CLink* LINNew = new CLink();

    LINNew->LINSetEnd(pNODDestination->NODGetValue());

    pNODSource->NODAddOutputLink(*LINNew);
    pNODDestination->NODAddInputLink(*LINNew);

    //If the graph is oriented, create a new link in the other direction
    if (bGRAIsOriented==false) {
        CLink* LINNewBack = new CLink();

        LINNewBack->LINSetEnd(pNODSource->NODGetValue());

        pNODDestination->NODAddOutputLink(*LINNew);
        pNODSource->NODAddInputLink(*LINNew);
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
    CNode* pNODSource = nullptr;
    CNode* pNODDestination = nullptr;
    try {
        pNODSource = GRAGetNode(uiValueNodeSource);
        pNODDestination = GRAGetNode(uiValueNodeDestination);
    }
    catch (CException EXCError) {
        throw CException(EXCEPTION_NODE_NOT_FOUND);
    }

    CLink* pLINLinkToRemove = nullptr;

    //We try to get the link and delete the pointer is the 2 involved nodes
    //Then we delete the link
    try {
        pLINLinkToRemove = pNODSource->NODGetLinkTowardNode(uiValueNodeDestination);
        pNODSource->NODRemoveOutputLink(*pLINLinkToRemove);
        pNODDestination->NODRemoveInputLink(*pLINLinkToRemove);
        delete pLINLinkToRemove;
    }
    catch (CException EXCError) {
        throw EXCError;
    }

    //If the graph is not oriented, we remove in the other direction
    if (bGRAIsOriented==false) {

        CLink* pLINLinkToRemoveBack = nullptr;

        //We try to get the link and delete the pointeur is the 2 concerned nodes
        //Then we delete the link
        try {
            pLINLinkToRemoveBack = pNODDestination->NODGetLinkTowardNode(uiValueNodeSource);
            pNODDestination->NODRemoveOutputLink(*pLINLinkToRemoveBack);
            pNODSource->NODRemoveInputLink(*pLINLinkToRemoveBack);
            delete pLINLinkToRemoveBack;
        }
        catch (CException EXCError) {
            throw EXCError;
        }


    }

}


void CGraph::GRAChangeLinkDestination(unsigned int uiVNodeSource, unsigned int uiVNodeOldDestination, unsigned int uiVNodeNewDestination) {

    //Check if the 3 nodes exist in the graph
    CNode* pNODSource = nullptr;
    CNode* pNODDestination = nullptr;
    CNode* pNODNewDestination = nullptr;
    try {
        pNODSource = GRAGetNode(uiVNodeSource);
        pNODDestination = GRAGetNode(uiVNodeOldDestination);
        pNODNewDestination = GRAGetNode(uiVNodeNewDestination);
    }
    catch (CException EXCError) {
        throw CException(EXCEPTION_NODE_NOT_FOUND);
    }



}



/**
 * Add a node to the graph
 * Input: uiNodeValue : unsigned int
 * Output: /
 * Precondition : /
 * Postcondition : If the value is already in the graph an error is throw, else
    a Node is created, added to the graph and uiGRASize is incremented
 */
CNode* CGraph::GRAAddNode(unsigned int uiNodeValue) {

    //We check if this value already exists in the graph
    bool bExist = true;
    try {
        CNode* pNODExist = GRAGetNode(uiNodeValue);
    }
    catch (CException EXCError) {
        bExist = false;
    }

    //If not, we can create a new node and add it
    if (bExist == false) {
    
        CNode* pNODToAdd = new CNode(uiNodeValue);
        uiGRASize++;

        CNode* pNODTemp = (CNode*)realloc(pNODGRANodeList, uiGRASize * sizeof(CNode));
        if (pNODTemp == nullptr) {
            throw CException();
        }
        pNODGRANodeList = pNODTemp;

        pNODGRANodeList[uiGRASize - 1] = pNODToAdd;

        return pNODToAdd;
    
    }
    else {
        throw CException(EXCEPTION_NODE_NOT_FOUND);
    }
    

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
    for (unsigned int uiLoop = 0; uiLoop < uiGRASize; uiLoop++) {
        if (pNODGRANodeList[uiLoop].NODGetValue() == uiValue) {
            pNODFound = (pNODGRANodeList + uiLoop);
        }
    }
    if (pNODFound == nullptr) {
        throw CException(EXCEPTION_NODE_NOT_FOUND);
    }

    /*
    if the graph is not oriented, the fastest method is to browse the entire graph and
    use the GRARemoveLinkBetweenNode method which allows you to remove all the links in 2 nodes
    */
    if (bGRAIsOriented == false) {

        for (unsigned int uiLoop = 0; uiLoop < uiGRASize; uiLoop++) {

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
        for (unsigned int uiLoop = 0; uiLoop < uiGRASize; uiLoop++) {

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
    for (unsigned int uiLoop = 0; uiLoop < uiGRASize - 1; uiLoop++) {

        if ((pNODGRANodeList + uiLoop) == pNODFound) {

            for (unsigned int uiLoopEnd = uiLoop; uiLoopEnd < uiGRASize - 1; uiLoopEnd++) {
                pNODGRANodeList[uiLoopEnd] = *(pNODGRANodeList + uiLoopEnd + 1);
            }

        }
    }

    //all links and references to or from this node have been removed from other nodes and the graph

    delete pNODFound;

    uiGRASize--;
    CNode* pNODTemp = (CNode*)realloc(pNODGRANodeList, uiGRASize * sizeof(CNode));
    if (pNODTemp == nullptr) {
        throw CException();
    }
    pNODGRANodeList = pNODTemp;

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

    for (unsigned int uiLoop = 0; uiLoop < uiGRASize; uiLoop++) {

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


