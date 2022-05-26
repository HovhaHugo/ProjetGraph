#pragma once

#include "CLink.h"

#define EXCEPTION_LINK_NOT_EXIST 2
#define EXCEPTION_TRY_DELETE_USED_NODE 3
#define EXCEPTION_MallocError 6			//Memory allocation error


class CNode
{
private:
	unsigned int uiNODValue;
	unsigned int uiNODInputSize;
	unsigned int uiNODOutputSize;
	CLink** ppLINNODInputLink;
	CLink** ppLINNODOutputLink;

public:
	CNode();
	CNode(unsigned int uiParam);
	CNode(CNode* pNODToCopy);
	~CNode();

	CNode* operator=(CNode* pNODToCopy);

	//Methods
	void NODShow();
	CLink* NODGetLinkTowardNode(unsigned int uiDestination);

	void NODAddInputLink(CLink &LINToAdd);
	void NODAddOutputLink(CLink& LINToAdd);
	void NODAddInputLink(unsigned int uiDestination);
	void NODAddOutputLink(unsigned int uiDestination);
	void NODRemoveInputLink(unsigned int uiDestinationNode);
	void NODRemoveOutputLink(unsigned int uiDestinationNode);


	//Getters and setters
	unsigned int NODGetValue();
	void NODSetValue(unsigned int uiValue);
	CLink** NODGetInputLink(unsigned int* uiSize);
	CLink** NODGetOutputLink(unsigned int* uiSize);

};

