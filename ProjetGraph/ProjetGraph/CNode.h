#pragma once

#include "CLink.h"

#define EXCEPTION_MALLOC_ERROR 6			//Memory allocation error
#define EXCEPTION_LINK_NOT_EXIST 8


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
	CLink* NODGetLinkFromNode(unsigned int uiFrom);

	void NODAddInputLink(CLink &LINToAdd);
	void NODAddOutputLink(CLink& LINToAdd);
	void NODAddInputLink(unsigned int uiDestination);
	void NODAddOutputLink(unsigned int uiDestination);
	void NODRemoveInputLink(unsigned int uiDestinationNode);
	void NODRemoveOutputLink(unsigned int uiDestinationNode);


	//Getters and setters

	unsigned int NODGetValue();
	unsigned int NODGetInputSize();
	unsigned int NODGetOutputSize();
	void NODSetValue(unsigned int uiValue);
	CLink** NODGetInputLink();
	CLink** NODGetOutputLink();

};

