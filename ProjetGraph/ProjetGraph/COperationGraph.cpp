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

        unsigned int uiCurrentSizeLinkOutput = pNODCurrent->NODGetOutputSize();
        CLink** ppLINCurrentOutputLink = pNODCurrent->NODGetOutputLink();

        //For each output link (== new dual node)
        for (unsigned int uiLoopLinkOutput = 0; uiLoopLinkOutput < uiCurrentSizeLinkOutput; uiLoopLinkOutput++) {

            CLink* pLINCurrentLink = ppLINCurrentOutputLink[uiLoopLinkOutput];
            CNode* pNODDestination = pGRAToDual->GRAGetNode(pLINCurrentLink->LINGetEnd());

            if (pNODCurrent->NODGetValue() > pNODDestination->NODGetValue() && pGRAToDual->GRAGetIsOriented() ==false)
                continue;
            
            //All output of the other node
            CLink** ppLINOtherListLinkTo = pNODDestination->NODGetOutputLink();
            unsigned int uiOtherOutputLinkNb = pNODDestination->NODGetOutputSize();

            char* pcDualNodeValue = (char*)malloc(10 * sizeof(char));
            if (pcDualNodeValue == nullptr)
                throw CException(EXCEPTION_MALLOC_ERROR);

            //Get the current dual node value
            sprintf(pcDualNodeValue, "%d%d", pNODCurrent->NODGetValue(), pNODDestination->NODGetValue());

            char* pcEndPtrNewNode;
            int iCurrentNewNodeValue = strtod(pcDualNodeValue, &pcEndPtrNewNode);
            if (pcEndPtrNewNode == pcDualNodeValue) {
                throw CException(EXCEPTION_CONVERSION_ERROR);
            }

            //Add output links from the first old node 
            for (unsigned int uiLoopNLink = 0; uiLoopNLink < uiCurrentSizeLinkOutput; uiLoopNLink++) {

                //If it's the current link, we continue to the next iteration
                if (ppLINCurrentOutputLink[uiLoopNLink]->LINGetEnd() == pNODDestination->NODGetValue())
                    continue;

                //Create the value of the destination node
                char* pcDualDestinationNodeValue = (char*)malloc(10 * sizeof(char));
                if (pcDualDestinationNodeValue == nullptr)
                    throw CException(EXCEPTION_MALLOC_ERROR);

                int temp1 = pNODCurrent->NODGetValue();
                int temp2 = ppLINCurrentOutputLink[uiLoopNLink]->LINGetEnd();


                if (temp1 > temp2 && pGRAToDual->GRAGetIsOriented() == false) {
                    int t = temp1;
                    temp1 = temp2;
                    temp2 = t;
                }

                //Get the destination dual node value
                sprintf(pcDualDestinationNodeValue, "%d%d", temp1, temp2);
                char* pcEndPtrNewNode;
                int iDestinationNodeValue = strtod(pcDualDestinationNodeValue, &pcEndPtrNewNode);
                if (pcEndPtrNewNode == pcDualNodeValue) {
                    throw CException(EXCEPTION_CONVERSION_ERROR);
                }

                pGRADual->GRAAddLinkBetweenNode(iCurrentNewNodeValue, iDestinationNodeValue);
            }//for each other output links found

            //Add output links from the second old node 
            for (unsigned int uiLoopNLink = 0; uiLoopNLink < uiOtherOutputLinkNb; uiLoopNLink++) {

                //If it's the current link, we continue to the next iteration
                if (ppLINOtherListLinkTo[uiLoopNLink]->LINGetEnd() == pNODCurrent->NODGetValue())
                    continue;

                //Create the value of the destination node
                char* pcDualDestinationNodeValue = (char*)malloc(10 * sizeof(char));
                if (pcDualDestinationNodeValue == nullptr)
                    throw CException(EXCEPTION_MALLOC_ERROR);

                int temp1 = pNODDestination->NODGetValue();
                int temp2 = ppLINOtherListLinkTo[uiLoopNLink]->LINGetEnd();

                if (temp1 > temp2 && pGRAToDual->GRAGetIsOriented() == false) {
                    int t = temp1;
                    temp1 = temp2;
                    temp2 = t;
                }

                //Get the destination dual node value
                sprintf(pcDualDestinationNodeValue, "%d%d", temp1, temp2);
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

            if (pNODCurrent->NODGetValue() > pNODDestination->NODGetValue() && pGRAToDual->GRAGetIsOriented() ==false)
                continue;

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
