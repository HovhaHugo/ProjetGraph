#include <stdlib.h>
#include <iostream>
#include "CNode.h"
#include "CException.h"

using namespace std;


/**
 * Default constructor of CNode
 * Input: /
 * Output: /
 * Precondition : /
 * Postcondition : the object has been created in memory with uiNODValue = 0
 */
CNode::CNode() {
	uiNODValue = 0;
	uiNODInputSize = 0;
	uiNODOutputSize = 0;
	ppLINNODInputLink = (CLink**)malloc(uiNODInputSize * sizeof(CLink*));
	ppLINNODOutputLink = (CLink**)malloc(uiNODOutputSize * sizeof(CLink*));
}

/**
 * Constructor by cipy of CNode
 * Input: pNODToCopy: CNode
 * Output: /
 * Precondition : /
 * Postcondition : the object has been created in memory with this = pNODToCopy
 */
CNode::CNode(CNode* pNODToCopy) {
	uiNODValue = pNODToCopy->NODGetValue();

	uiNODInputSize = pNODToCopy->uiNODInputSize;
	uiNODOutputSize = pNODToCopy->uiNODOutputSize;

	ppLINNODInputLink = (CLink**)malloc(uiNODInputSize * sizeof(CLink*));
	ppLINNODOutputLink = (CLink**)malloc(uiNODOutputSize * sizeof(CLink*));

	for (unsigned int uiLoop = 0; uiLoop < uiNODInputSize; uiLoop++) {
		CLink* pLINCopy = new CLink(pNODToCopy->ppLINNODInputLink[uiLoop]);
		NODAddInputLink(*pLINCopy);
	}

	for (unsigned int uiLoop = 0; uiLoop < uiNODOutputSize; uiLoop++) {
		CLink* pLINCopy = new CLink(pNODToCopy->ppLINNODOutputLink[uiLoop]);
		NODAddOutputLink(*pLINCopy);
	}
}


/**
 * Constructor of CNode
 * Input: uiParam: unsigned int
 * Output: /
 * Precondition : /
 * Postcondition : the object has been created in memory with uiNODValue = uiParam
 */
CNode::CNode(unsigned int uiParam) {
	uiNODValue = uiParam;
	uiNODInputSize = 0;
	uiNODOutputSize = 0;
	ppLINNODInputLink = (CLink**)malloc(uiNODInputSize * sizeof(CLink*));
	ppLINNODOutputLink = (CLink**)malloc(uiNODInputSize * sizeof(CLink*));
}


/**
 * Destructor of CNode
 * Input: /
 * Output: /
 * Precondition : /
 * Postcondition : the object has been deleted from memory
 */
CNode::~CNode() {
	for (unsigned int uiLoop = 0; uiLoop < uiNODInputSize; uiLoop++) {
		delete ppLINNODInputLink[uiLoop];
	}

	for (unsigned int uiLoop = 0; uiLoop < uiNODOutputSize; uiLoop++) {
		delete ppLINNODOutputLink[uiLoop];
	}
}

// ******************* END OF CONSTRUCTORS / DESTRUCTOR		************************* //

// ******************* METHODS								************************* //


/**
 * Show a CNode
 * Input: /
 * Output: /
 * Precondition : /
 * Postcondition : The node value and only output links are displayed
 */
void CNode::NODShow() {
	cout << "Node value : " << uiNODValue << endl;

	cout << "Input links :" << endl;
	for (unsigned int uiLoop = 0; uiLoop < uiNODInputSize; uiLoop++) {
		ppLINNODInputLink[uiLoop]->LINShow();
	}

	cout << "Output links :" << endl;
	for (unsigned int uiLoop = 0; uiLoop < uiNODOutputSize; uiLoop++) {
		ppLINNODOutputLink[uiLoop]->LINShow();
	}
	cout << endl;

}


/**
 * Lets you know if the node contains a link from another node
 * Input: uiDestination : unsigned int
 * Output: CLink*
 * Precondition : /
 * Postcondition : If there is a link in the current node comming from
 *	the node with uiDestination value,the returned value contains the link.
 *	Else, a error is thrown
 */
CLink* CNode::NODGetLinkFromNode(unsigned int uiFrom) {

	CLink* pLINFound = nullptr;

	//We search in all the output links
	for (unsigned int uiLoop = 0; uiLoop < uiNODInputSize; uiLoop++) {
		if (ppLINNODInputLink[uiLoop]->LINGetEnd() == uiFrom) {
			pLINFound = ppLINNODInputLink[uiLoop];
			break;
		}
	}

	if (pLINFound == nullptr) {
		throw CException(EXCEPTION_LINK_NOT_EXIST);
	}

	return pLINFound;

}


/**
 * Lets you know if the node contains a link to another node
 * Input: uiDestination : unsigned int
 * Output: CLink*
 * Precondition : /
 * Postcondition : If there is a link starting from the current node toward
 *	the node with uiDestination value,the returned value contains the link.
 *	Else, a error is thrown
 */
CLink* CNode::NODGetLinkTowardNode(unsigned int uiDestination) {

	CLink* pLINFound = nullptr;

	//We search in all the output links
	for (unsigned int uiLoop = 0; uiLoop < uiNODOutputSize; uiLoop++) {
		if (ppLINNODOutputLink[uiLoop]->LINGetEnd() == uiDestination) {
			pLINFound = ppLINNODOutputLink[uiLoop];
			break;
		}
	}

	if (pLINFound == nullptr) {
		throw CException(EXCEPTION_LINK_NOT_EXIST);
	}

	return pLINFound;

}

// ******************* END OF METHODS						************************* //

// ******************* OVERLOADED OPERATOR					************************* //

/**
 * Overloaded = operator
 * Input: pNODToCopy : CNode*
 * Output: CNode*
 * Precondition : /
 * Postcondition : The copy constructor is called
 */
CNode* CNode::operator=(CNode* pNODToCopy) {

	CNode* pNODNewNode = new CNode(pNODToCopy);

	return pNODNewNode;
}

// ******************* END OF OVERLOADED OPERATOR			************************* //


// ******************* INPUTLINK / OUTPUTLINK MANAGEMENT		********************* //

/**
 * Add an input link to the node
 * Input: LINToAdd : CLink&
 * Output: /
 * Precondition : /
 * Postcondition : LINToAdd has been added to the inputs links list, and uiNODInputSize has been incremented
 */
void CNode::NODAddInputLink(CLink &LINToAdd) {

	CLink** ppLINTemp = nullptr;

	uiNODInputSize++;
	ppLINTemp = (CLink**)realloc(ppLINNODInputLink, uiNODInputSize * sizeof(CLink*));

	if (ppLINTemp != nullptr) {
		ppLINNODInputLink = ppLINTemp;
		ppLINNODInputLink[uiNODInputSize - 1] = &LINToAdd;
	}
	else
		throw CException(EXCEPTION_MALLOC_ERROR);

}


/**
 * Add an output link to the node
 * Input: LINToAdd : CLink&
 * Output: /
 * Precondition : /
 * Postcondition : pLINParam has been added to the outputs links list, and uiNODOuputSize has been incremented
 */
void CNode::NODAddOutputLink(CLink& LINToAdd) {

	CLink** ppLINTemp = nullptr;

	uiNODOutputSize++;
	ppLINTemp = (CLink**)realloc(ppLINNODOutputLink, uiNODOutputSize * sizeof(CLink*));

	if (ppLINTemp != nullptr) {
		ppLINNODOutputLink = ppLINTemp;
		ppLINNODOutputLink[uiNODOutputSize - 1] = &LINToAdd;
	}
	else
		throw CException(EXCEPTION_MALLOC_ERROR);

}

/**
 * Add an input link to the node
 * Input: uiDestination : unsigned int
 * Output: /
 * Precondition : uiDestination is a existing node value
 * Postcondition : pLINParam has been added to the inputs links list, and uiNODInputSize has been incremented
 */
void CNode::NODAddInputLink(unsigned int uiDestination) {

	CLink** ppLINTemp = nullptr;

	uiNODInputSize++;
	ppLINTemp = (CLink**)realloc(ppLINNODInputLink, uiNODInputSize * sizeof(CLink*));

	if (ppLINTemp != nullptr) {
		ppLINNODInputLink = ppLINTemp;
		ppLINNODInputLink[uiNODInputSize - 1] = new CLink(uiDestination);
	}
	else
		throw CException(EXCEPTION_MALLOC_ERROR);

}


/**
 * Add an output link to the node
 * Input: uiDestination : unsigned int
 * Output: /
 * Precondition : uiDestination is a existing node value
 * Postcondition : pLINParam has been added to the outputs links list, and uiNODOuputSize has been incremented
 */
void CNode::NODAddOutputLink(unsigned int uiDestination) {

	CLink** ppLINTemp = nullptr;

	uiNODOutputSize++;
	ppLINTemp = (CLink**)realloc(ppLINNODOutputLink, uiNODOutputSize * sizeof(CLink*));

	if (ppLINTemp != nullptr) {
		ppLINNODOutputLink = ppLINTemp;
		ppLINNODOutputLink[uiNODOutputSize - 1] = new CLink(uiDestination);
	}
	else
		throw CException(EXCEPTION_MALLOC_ERROR);

}


/**
 * Remove an input link to the node
 * Input: uiDestination : unsigned int
 * Output: /
 * Precondition : /
 * Postcondition : If uiDestination isn't found in the list an error is throw, else
	the link has been removed to the inputs links list, and uiNODInputSize has been decremented
 */
void CNode::NODRemoveInputLink(unsigned int uiDestination) {

	//Check if the link exist
	unsigned int indexFound = 0;
	bool bFound = false;
	for (unsigned int uiLoop = 0; uiLoop < uiNODInputSize; uiLoop++) {
		if (ppLINNODInputLink[uiLoop]->LINGetEnd() == uiDestination) {
			indexFound = uiLoop;
			bFound = true;
			delete ppLINNODInputLink[uiLoop];
		}
	}
	if (bFound == false) {
		throw CException(EXCEPTION_LINK_NOT_EXIST);
	}

	//shifts the remaining pointers
	for (unsigned int uiLoop = indexFound; uiLoop < uiNODInputSize - 1; uiLoop++) {
		ppLINNODInputLink[uiLoop] = ppLINNODInputLink[uiLoop + 1];
	}

	CLink** ppLINTemp = nullptr;

	uiNODInputSize--;
	ppLINTemp = (CLink**)realloc(ppLINNODInputLink, uiNODInputSize * sizeof(CLink*));

	if (ppLINTemp != nullptr || uiNODInputSize == 0) {
		ppLINNODInputLink = ppLINTemp;
	}
	else
		throw CException(EXCEPTION_MALLOC_ERROR);

}


/**
 * Remove an output link to the node
 * Input: uiDestination : unsigned int
 * Output: /
 * Precondition : /
 * Postcondition : If uiDestination isn't found in the list an error is throw, else
	the link has been removed to the outputs links list, and uiNODInputSize has been decremented
 */
void CNode::NODRemoveOutputLink(unsigned int uiDestination) {

	//Check if the link exist
	unsigned int indexFound = 0;
	bool bFound = false;

	for (unsigned int uiLoop = 0; uiLoop < uiNODOutputSize; uiLoop++) {
		if (ppLINNODOutputLink[uiLoop]->LINGetEnd() == uiDestination) {
			indexFound = uiLoop;
			bFound = true;
			delete ppLINNODOutputLink[uiLoop];
		}
	}
	if (bFound == false) {
		throw CException(EXCEPTION_LINK_NOT_EXIST);
	}

	//shifts the remaining pointers
	for (unsigned int uiLoop = indexFound; uiLoop < uiNODOutputSize - 1; uiLoop++) {
		ppLINNODOutputLink[uiLoop] = ppLINNODOutputLink[uiLoop + 1];
	}

	CLink** ppLINTemp = nullptr;

	uiNODOutputSize--;
	ppLINTemp = (CLink**)realloc(ppLINNODOutputLink, uiNODOutputSize * sizeof(CLink*));

	if (ppLINTemp != nullptr || uiNODOutputSize == 0) {
		ppLINNODOutputLink = ppLINTemp;
	}
	else
		throw CException(EXCEPTION_MALLOC_ERROR);

}

// ******************* END OF INPUTLINK / OUTPUTLINK MANAGEMENT	********************* //

// ******************* GETTERS AND SETTERS					************************* //

/**
 * Getter of uiNODValue
 * Input: /
 * Output: unsigned int
 * Precondition : /
 * Postcondition : uiNODValue is returned
 */
unsigned int CNode::NODGetValue() {
	return uiNODValue;
}

/**
 * Getter of uiNODInputSize
 * Input: /
 * Output: unsigned int
 * Precondition : /
 * Postcondition : uiNODInputSize is returned
 */
unsigned int CNode::NODGetInputSize() {
	return uiNODInputSize;
}

/**
 * Getter of uiNODOutputSize
 * Input: /
 * Output: unsigned int
 * Precondition : /
 * Postcondition : uiNODOutputSize is returned
 */
unsigned int CNode::NODGetOutputSize() {
	return uiNODOutputSize;
}


/**
 * Setter of uiNODValue
 * Input: uiValue: unsigned int
 * Output: /
 * Precondition : 
 * To keep the integrity of the graph, all the links in the other nodes referring
	to this one must have been modified. This method must be called via the GRAChangeNodeValue method
 * Postcondition : uiNODValue = uiValue
 */
void CNode::NODSetValue(unsigned int uiValue) {
	uiNODValue = uiValue;
}


/**
 * Getter of ppLINNODInputLink
 * Input: *uiSize : unsigned int
 * Output: *uiSize, CLink**
 * Precondition : /
 * Postcondition : uiNODValue is returned and uiSize = uiNODInputSize
 */
CLink** CNode::NODGetInputLink() {
	return ppLINNODInputLink;
}

/**
 * Getter of ppLINNODOutputLink
 * Input: /
 * Output: *uiSize, CLink**
 * Precondition : /
 * Postcondition : uiNODValue is returned and uiSize = uiNODOutputSize
 */
CLink** CNode::NODGetOutputLink() {
	return ppLINNODOutputLink;
}