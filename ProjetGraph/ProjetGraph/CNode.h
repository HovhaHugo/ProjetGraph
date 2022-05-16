#pragma once

#include "CLink.h"

#define EXCEPTION_LINK_NOT_EXIST 2
#define EXCEPTION_TRY_DELETE_USED_NODE 3

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

	//Methods
	void NODShow();
	CLink* NODGetLinkTowardNode(unsigned int uiDestination);

	void NODAddInputLink(CLink& pLINParam);
	void NODAddOutputLink(CLink& pLINParam);
	void NODRemoveInputLink(CLink& pLINParam);
	void NODRemoveOutputLink(CLink& pLINParam);


	//Getters and setters
	unsigned int NODGetValue();
	void NODSetValue(unsigned int uiValue);
	CLink** NODGetInputLink(unsigned int* uiSize);
	CLink** NODGetOutputLink(unsigned int* uiSize);

};

