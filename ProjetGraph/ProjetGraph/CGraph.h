#pragma once

#include "CNode.h"

#define EXCEPTION_NODE_NOT_FOUND 1
#define EXCEPTION_INCOHERENCE 2			//Un lien n'est reference que d'un seul cote


class CGraph
{
private:
	CNode* pNODGRANodeList;
	unsigned int uiGRASize;
	bool bGRAIsOriented;

public:
	CGraph();
	CGraph(const char* pcFilePath);
	CGraph(CGraph* pGRAToCopy);
	~CGraph();

	void GRAShow();
	CGraph* GRAInverse();
	void GRAAddLinkBetweenNode(unsigned int uiValueNodeSource, unsigned int uiValueNodeDestination);
	void GRARemoveLinkBetweenNode(unsigned int uiValueNodeSource, unsigned int uiValueNodeDestination);
	void GRAChangeLinkDestination(unsigned int uiVNodeSource, unsigned int uiVNodeOldDestination, unsigned int uiVNodeNewDestination);
	CNode* GRAAddNode(unsigned int uiNodeValue);
	void GRARemoveNode(unsigned int uiValue);
	void GRAChangeNodeValue(unsigned int uiOldValue, unsigned int uiNewValue);

	CNode* GRAGetNode(unsigned int uiNumber);
	bool GRAGetIsOriented();

};

