#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include "COperationGraph.h"
#include "CGraph.h"
#include "CException.h"


/**
 * Function that inverte a graph (mean that each link change their start for their beginging)
 * Input: /
 * Output: /
 * Precondition : /
 * Postcondition : the graph has been inverted
 */
CGraph* COperationGraph::OPEInverse(CGraph* pGRAToInverse) {
    //We create a new object
    CGraph* pGRANewGraph = new CGraph();
    pGRANewGraph->GRASetIsOriented(pGRAToInverse->GRAGetIsOriented());

    CNode* pNODNodeListToInverse = pGRAToInverse->GRAGetNodeList();

    //For each node, we recopy them all in the new graph
    for (unsigned int uiLoopNode = 0; uiLoopNode < pGRAToInverse->GRAGetSize(); uiLoopNode++) {
        pGRANewGraph->GRAAddNode(pNODNodeListToInverse[uiLoopNode].NODGetValue());
    }

    //Then we can create the links between the nodes
    for (unsigned int uiLoopNode = 0; uiLoopNode < pGRAToInverse->GRAGetSize(); uiLoopNode++) {

        //For each input on the node, we add the link reversed une our graph
        unsigned int uiSizeLinkInput = pNODNodeListToInverse[uiLoopNode].NODGetInputSize();
        CLink** ppLINInputLink = pNODNodeListToInverse[uiLoopNode].NODGetInputLink();

        for (unsigned int uiLoopLinkInput = 0; uiLoopLinkInput < uiSizeLinkInput; uiLoopLinkInput++) {
            pGRANewGraph->GRAGetNode(uiLoopNode)->NODAddOutputLink(ppLINInputLink[uiLoopLinkInput]->LINGetEnd());
        }

        //For each output on the node, we add the link reversed une our graph
        unsigned int uiSizeLinkOutput = pNODNodeListToInverse[uiLoopNode].NODGetOutputSize();
        CLink** ppLINOutputLink = pNODNodeListToInverse[uiLoopNode].NODGetOutputLink();

        for (unsigned int uiLoopLinkOutput = 0; uiLoopLinkOutput < uiSizeLinkOutput; uiLoopLinkOutput++) {
            pGRANewGraph->GRAGetNode(uiLoopNode)->NODAddInputLink(ppLINOutputLink[uiLoopLinkOutput]->LINGetEnd());
        }
    }
    return pGRANewGraph;
}



/**
 * Create a dual graph. Nodes become links and links become nodes.
 * -Create all the new nodes from every existing output links.
 * -Create links between the new nodes : each new node has a link with every other new nodes
 * created from the other links of the same node.
 * Input: toDual : CGraph&
 * Output: CGraph*
 * Precondition : /
 * Postcondition : /
 */
CGraph* COperationGraph::OPEToDual(CGraph* pGRAToDual) {

    //We create the blank dual graph
    CGraph* pGRADual = OPECreateBlankDual(pGRAToDual);

    CNode* pNODNodeListToDual = pGRAToDual->GRAGetNodeList();

    for (unsigned int uiLoopNode = 0; uiLoopNode < pGRAToDual->GRAGetSize(); uiLoopNode++) {

        CNode* pNODCurrent = (pNODNodeListToDual + uiLoopNode);

        int* piCurrentListLinkTo = new int[100];
        unsigned int uiCurrentOutputLinkNb = 0;

        //List of all input connections of the first node
        pNODCurrent->NODGetOutputListLink(piCurrentListLinkTo, uiCurrentOutputLinkNb);

        unsigned int uiSizeLinkOutput = pNODCurrent->NODGetOutputSize();
        CLink** ppLINOutputLink = pNODCurrent->NODGetOutputLink();

        //For each output link (== new dual node)
        for (unsigned int uiLoopLinkOutput = 0; uiLoopLinkOutput < uiSizeLinkOutput; uiLoopLinkOutput++) {

            CLink* pLINCurrentLink = ppLINOutputLink[uiLoopLinkOutput];
            CNode* pNODDestination = pGRAToDual->GRAGetNode(pLINCurrentLink->LINGetEnd());
            
            int* piOtherListLinkTo = new int[100];
            unsigned int uiOtherOutputLinkNb = 0;

            //List of all connections of the second node
            pNODDestination->NODGetOutputListLink(piOtherListLinkTo, uiOtherOutputLinkNb);

            char* pcDualNodeValue = (char*)malloc(10 * sizeof(char));
            if (pcDualNodeValue == nullptr)
                throw CException(EXCEPTION_MALLOC_ERROR);

            //Get the current dual node value
            sprintf(pcDualNodeValue, "%d%d", pNODCurrent->NODGetValue(), ppLINOutputLink[uiLoopLinkOutput]->LINGetEnd());

            char* pcEndPtrNewNode;
            int iCurrentNewNodeValue = strtod(pcDualNodeValue, &pcEndPtrNewNode);
            if (pcEndPtrNewNode == pcDualNodeValue) {
                throw CException(EXCEPTION_CONVERSION_ERROR);
            }

            //Add output links from the first old node 
            for (unsigned int uiLoopNLink = 0; uiLoopNLink < uiCurrentOutputLinkNb; uiLoopNLink++) {

                //If it's the current link, we continue to the next iteration
                if (piCurrentListLinkTo[uiLoopNLink] == pNODDestination->NODGetValue())
                    continue;

                //Create the value of the destination node
                char* pcDualDestinationNodeValue = (char*)malloc(10 * sizeof(char));
                if (pcDualDestinationNodeValue == nullptr)
                    throw CException(EXCEPTION_MALLOC_ERROR);

                //Get the destination dual node value
                sprintf(pcDualDestinationNodeValue, "%d%d", pNODCurrent->NODGetValue(), piCurrentListLinkTo[uiLoopNLink]);
                char* pcEndPtrNewNode;
                int iDestinationNodeValue = strtod(pcDualDestinationNodeValue, &pcEndPtrNewNode);
                if (pcEndPtrNewNode == pcDualNodeValue) {
                    throw CException(EXCEPTION_CONVERSION_ERROR);
                }

                pGRADual->GRAAddLinkBetweenNode(iCurrentNewNodeValue, iDestinationNodeValue);
            }//for each other output links found

            //Add output links from the second old node 
            for (unsigned int uiLoopNLink = 0; uiLoopNLink < uiOtherOutputLinkNb; uiLoopNLink++) {

                //Create the value of the destination node
                char* pcDualDestinationNodeValue = (char*)malloc(10 * sizeof(char));
                if (pcDualDestinationNodeValue == nullptr)
                    throw CException(EXCEPTION_MALLOC_ERROR);

                //Get the destination dual node value
                sprintf(pcDualDestinationNodeValue, "%d%d", pNODDestination->NODGetValue(), piOtherListLinkTo[uiLoopNLink]);
                char* pcEndPtrNewNode;
                int iDestinationNodeValue = strtod(pcDualDestinationNodeValue, &pcEndPtrNewNode);
                if (pcEndPtrNewNode == pcDualNodeValue) {
                    throw CException(EXCEPTION_CONVERSION_ERROR);
                }

                pGRADual->GRAAddLinkBetweenNode(iCurrentNewNodeValue, iDestinationNodeValue);
            }//for each other output links found

        }//for each output link

    }//for each CNode of the old graph

    return pGRADual;

}


CGraph* COperationGraph::OPECreateBlankDual(CGraph* pGRAToDual) {

    CGraph* pGRADual = new CGraph();
    pGRAToDual->GRASetIsOriented(pGRAToDual->GRAGetIsOriented());

    CNode* pNODOldNodeList = pGRAToDual->GRAGetNodeList();

    for (unsigned int uiLoopNode = 0; uiLoopNode < pGRAToDual->GRAGetSize(); uiLoopNode++) {

        CNode* pNODCurrent = (pNODOldNodeList + uiLoopNode);

        //For each output on the node, we create a new node in the dual graph
        unsigned int uiSizeLinkOutput = pNODCurrent->NODGetOutputSize();
        CLink** ppLINOutputLink = pNODCurrent->NODGetOutputLink();

        //For each other output link, we must create a new link between these 2 new nodes (old link -> new node)
        for (unsigned int uiLoopLinkOutput = 0; uiLoopLinkOutput < uiSizeLinkOutput; uiLoopLinkOutput++) {

            CLink* pLINCurrentLink = ppLINOutputLink[uiLoopLinkOutput];
            CNode* pNODDestination = pGRAToDual->GRAGetNode(pLINCurrentLink->LINGetEnd());

            char* pcNumberNode = (char*)malloc(10 * sizeof(char));
            if (pcNumberNode == nullptr)
                throw CException(EXCEPTION_MALLOC_ERROR);

            //Create the value of the new node
            sprintf(pcNumberNode, "%d%d", pNODCurrent->NODGetValue(), ppLINOutputLink[uiLoopLinkOutput]->LINGetEnd());
            char* pcEndPtrNewNode;
            int iCurrentNodeValue = strtod(pcNumberNode, &pcEndPtrNewNode);
            if (pcEndPtrNewNode == pcNumberNode) {
                throw CException(EXCEPTION_CONVERSION_ERROR);
            }

            //We create the dual node
            CNode* pNODNew = pGRADual->GRAAddNode(iCurrentNodeValue);

        }//Each Output link
    }//Each CNode

    return pGRADual;
}
