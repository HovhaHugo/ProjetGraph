#include "CParser.h"
#include "CException.h"
#include "CGraph.h"
#include <malloc.h>


/**
 * Default constructor of CGraph
 * Input: /
 * Output: /
 * Precondition : /
 * Postcondition : the object has been created in memory with uiGRASize = 0 and the graph is oriented as default value
 */
CGraph::CGraph() {
    uiGRASize = 0;
    pNODGRANodeList = (CNode*)calloc(uiGRASize, sizeof(CNode));
    if (pNODGRANodeList == nullptr) {
        throw CException(EXCEPTION_MALLOC_ERROR);
    }
    bGRAIsOriented = true;
}


/**
 * Default constructor of CGraph
 * Input: /
 * Output: /
 * Precondition : /
 * Postcondition : the object has been created in memory with uiGRASize = 0 and pNODGRANodeList = nullptr
 */
CGraph::CGraph(const char* pcFilePath) {
    //Appel du parseur
    CParser* pPARParser;
    try {
        pPARParser = new CParser(pcFilePath);
    }
    catch (CException EXCError) {
        throw EXCError;
    }

    //The parser doesn't know if the graph is oriented
    bGRAIsOriented = true;

    uiGRASize = pPARParser->PARGetNumber("NBSommets");
    unsigned int uiNbOfLink = pPARParser->PARGetNumber("NBArcs");

    pNODGRANodeList = pPARParser->PARGetNodes(uiGRASize,"Sommets");

    //temporary lists of link data are created in memory 
    int* piListLinkFrom = (int*)malloc(sizeof(int) * uiNbOfLink);
    if (piListLinkFrom == nullptr)
        throw CException(EXCEPTION_MALLOC_ERROR);

    int* piListLinkTo = (int*)malloc(sizeof(int) * uiNbOfLink);
    if (piListLinkTo == nullptr) {
        free(piListLinkFrom);
        throw CException(EXCEPTION_MALLOC_ERROR);
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
 * Postcondition : the object and all his nodes has been deleted from memory
 */
CGraph::~CGraph() {

    for (unsigned int uiLoopNode = 0; uiLoopNode < uiGRASize; uiLoopNode++) {
        GRARemoveNode(pNODGRANodeList[uiLoopNode].NODGetValue());
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
    bGRAIsOriented = pGRAToCopy->bGRAIsOriented;

    pNODGRANodeList = (CNode*)calloc(uiGRASize, sizeof(CNode));
    if (pNODGRANodeList == nullptr) {
        throw CException(EXCEPTION_MALLOC_ERROR);
    }

    for (unsigned int uiLoop = 0; uiLoop < pGRAToCopy->uiGRASize; uiLoop++) {

        pNODGRANodeList[uiLoop] = CNode((unsigned int)pGRAToCopy->pNODGRANodeList[uiLoop].NODGetValue());

        unsigned int uiInputLinkSize = pGRAToCopy->pNODGRANodeList[uiLoop].NODGetInputSize();
        CLink** ppLINInputLink = pGRAToCopy->pNODGRANodeList[uiLoop].NODGetInputLink();
        if (uiInputLinkSize > 0) {
            for (unsigned int uiLoopLink1 = 0; uiLoopLink1 < uiInputLinkSize; uiLoopLink1++){
                pNODGRANodeList[uiLoop].NODAddInputLink(ppLINInputLink[uiLoopLink1]->LINGetEnd());
            }
        }

        unsigned int uiOutputLinkSize = pGRAToCopy->pNODGRANodeList[uiLoop].NODGetOutputSize();
        CLink** ppLINOutputLink = pGRAToCopy->pNODGRANodeList[uiLoop].NODGetOutputLink();
        if (uiOutputLinkSize > 0) {
            for (unsigned int uiLoopLink2 = 0; uiLoopLink2 < uiOutputLinkSize; uiLoopLink2++) {
                pNODGRANodeList[uiLoop].NODAddOutputLink(ppLINOutputLink[uiLoopLink2]->LINGetEnd());
            }
        }
    }
    

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
    pNODSource->NODAddOutputLink(pNODDestination->NODGetValue());
    pNODDestination->NODAddInputLink(pNODSource->NODGetValue());

    //If the graph is not oriented, create a new link in the other direction
    if (bGRAIsOriented==false) {
        pNODSource->NODAddInputLink(pNODDestination->NODGetValue());
        pNODDestination->NODAddOutputLink(pNODSource->NODGetValue());
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

    //The delete the 2 links
    try {
        pNODSource->NODRemoveOutputLink(pNODDestination->NODGetValue());
        pNODDestination->NODRemoveInputLink(pNODSource->NODGetValue());
    }
    catch (CException EXCError) {
        throw EXCError;
    }

    //If the graph is not oriented, we remove in the other direction
    if (bGRAIsOriented==false) {

        //The delete the 2 links
        try {
            pNODDestination->NODRemoveOutputLink(pNODSource->NODGetValue());
            pNODSource->NODRemoveInputLink(pNODDestination->NODGetValue());
        }
        catch (CException EXCError) {
            throw EXCError;
        }

    }

}


/**
 * Change a link destination
 * Input: uiValueNodeSource : unsigned int, uiVNodeOldDestination : unsigned int, uiVNodeNewDestination : unsigned int
 * Output: /
 * Precondition : /
 * Postcondition : If at least 1 of the 3 nodes is not in the graph an error is throw, same if
 *  there is not an existing link between the 2 old nodes.
 *  Else, the existing link between uiValueNodeSource and uiVNodeOldDestination are now uiValueNodeSource to uiVNodeNewDestination
 */
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
   
    try {
        //We remove this link from the input link list of the old destination
        pNODDestination->NODRemoveInputLink(pNODSource->NODGetValue());

        //And add it to the new destination
        pNODSource->NODGetLinkTowardNode(uiVNodeOldDestination)->LINSetEnd(pNODNewDestination->NODGetValue());
        pNODNewDestination->NODAddInputLink(pNODSource->NODGetValue());
    }
    catch (CException EXCError) {
        throw EXCError;
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
    
        uiGRASize++;

        CNode* pNODTemp = (CNode*)realloc(pNODGRANodeList, uiGRASize * sizeof(CNode));
        if (pNODTemp == nullptr) {
            throw CException();
        }
        pNODGRANodeList = pNODTemp;

        pNODGRANodeList[uiGRASize - 1] = CNode(uiNodeValue);;

        return (pNODGRANodeList+uiGRASize - 1);
    
    }
    else {
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
void CGraph::GRAChangeNodeValue(unsigned int uiOldValue, unsigned int uiNewValue) {

    //Check if the node exists in the graph
    CNode* pNODToModify = nullptr;
    for (unsigned int uiLoop = 0; uiLoop < uiGRASize; uiLoop++) {
        if (pNODGRANodeList[uiLoop].NODGetValue() == uiOldValue) {
            pNODToModify = (pNODGRANodeList + uiLoop);
        }
    }
    if (pNODToModify == nullptr) {
        throw CException(EXCEPTION_NODE_NOT_FOUND);
    }

    pNODToModify->NODSetValue(uiNewValue);

    unsigned int uiInputLinkSize = pNODToModify->NODGetInputSize();
    unsigned int uiOutputLinkSize = pNODToModify->NODGetOutputSize();

    CLink** ppLINInputLinks = pNODToModify->NODGetInputLink();
    CLink** ppLINOutputLinks = pNODToModify->NODGetOutputLink();

    for (unsigned int uiLoop = 0; uiLoop < uiInputLinkSize; uiLoop++) {

        try {
            CNode* pNODSource = GRAGetNode(ppLINInputLinks[uiLoop]->LINGetEnd());
            pNODSource->NODGetLinkTowardNode(uiOldValue)->LINSetEnd(uiNewValue);
        }
        catch (CException EXCError) {
            throw CException(EXCEPTION_INCOHERENCE);
        }

    }

    for (unsigned int uiLoop = 0; uiLoop < uiOutputLinkSize; uiLoop++) {

        try {
            CNode* pNODDestination = GRAGetNode(ppLINOutputLinks[uiLoop]->LINGetEnd());
            pNODDestination->NODGetLinkFromNode(uiOldValue)->LINSetEnd(uiNewValue);
        }
        catch (CException EXCError) {
            throw CException(EXCEPTION_INCOHERENCE);
        }

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
    CNode* pNODToRemove = nullptr;
    unsigned int uiIndexNode = 0;
    for (unsigned int uiLoop = 0; uiLoop < uiGRASize; uiLoop++) {
        if (pNODGRANodeList[uiLoop].NODGetValue() == uiValue) {
            pNODToRemove = (pNODGRANodeList+uiLoop);
            uiIndexNode = uiLoop;
        }
    }
    if (pNODToRemove == nullptr) {
        throw CException(EXCEPTION_NODE_NOT_FOUND);
    }

    unsigned int uiInputLinkSize = pNODToRemove->NODGetInputSize();
    unsigned int uiOutputLinkSize = pNODToRemove->NODGetOutputSize();

    CLink** ppLINInputLinks = pNODToRemove->NODGetInputLink();
    CLink** ppLINOutputLinks = pNODToRemove->NODGetOutputLink();

    for (unsigned int uiLoop = 0; uiLoop < uiInputLinkSize; uiLoop++) {

        try {
            GRARemoveLinkBetweenNode(ppLINInputLinks[uiLoop]->LINGetEnd(), pNODToRemove->NODGetValue());
        }
        catch (CException EXCError) {
            throw CException(EXCEPTION_INCOHERENCE);
        }

    }

    for (unsigned int uiLoop = 0; uiLoop < uiOutputLinkSize; uiLoop++) {

        try {
            GRARemoveLinkBetweenNode(pNODToRemove->NODGetValue(),ppLINOutputLinks[uiLoop]->LINGetEnd());
        }
        catch (CException EXCError) {
            throw CException(EXCEPTION_INCOHERENCE);
        }

    }

    //Remove the node from the list
    for (unsigned int uiLoop = uiIndexNode; uiLoop < uiGRASize - 1; uiLoop++) {

        pNODGRANodeList[uiLoop] = *(pNODGRANodeList + 1);

    }

    //all links and references to or from this node have been removed from other nodes and the graph

    uiGRASize--;
    CNode* pNODTemp = (CNode*)realloc(pNODGRANodeList, uiGRASize * sizeof(CNode));
    if (pNODTemp == nullptr && uiGRASize > 0) {
        throw CException(EXCEPTION_MALLOC_ERROR);
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
            pNODFound = (pNODGRANodeList+uiLoop);
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

/**
 * Setter of bGRAIsOriented
 * Input: bOriented : bool
 * Output: /
 * Precondition : /
 * Postcondition : bGRAIsOriented = bOriented
 */
void CGraph::GRASetIsOriented(bool bOriented) {
    bGRAIsOriented = bOriented;
}

/**
 * Getter of uiGRASize
 * Input: /
 * Output: unsigned int
 * Precondition : /
 * Postcondition : uiGRASize is returned
 */
CNode* CGraph::GRAGetNodeList() {
    return pNODGRANodeList;
}

unsigned int CGraph::GRAGetSize() {
    return uiGRASize;
}


