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
	ppLINNODOutputLink = (CLink**)malloc(uiNODInputSize * sizeof(CLink*));
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

	if (uiNODInputSize > 0 || uiNODOutputSize > 0) {
		throw CException(EXCEPTION_TRY_DELETE_USED_NODE);
	}

	//faire les free

}

// ******************* END OF CONSTRUCTORS / DESTRUCTOR		************************* //

// ******************* METHODS								************************* //


/**
 * Show a CNode
 * Input: /
 * Output: /
 * Precondition : /
 * Postcondition : The node is shown in the console
 */
void CNode::NODShow() {
	cout << "Noeud de valeur : " << uiNODValue << endl;

	cout << "Lien(s) d'entrée :" << endl;
	for (unsigned int uiLoop = 0; uiLoop < uiNODInputSize; uiLoop++) {
		ppLINNODInputLink[uiLoop]->LINShow();
	}

	cout << "Lien(s) de sortie :" << endl;
	for (unsigned int uiLoop = 0; uiLoop < uiNODOutputSize; uiLoop++) {
		ppLINNODOutputLink[uiLoop]->LINShow();
	}

}


/**
 * Lets you know if the node contains a link to another node in particular
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


// ******************* INPUTLINK / OUTPUTLINK MANAGEMENT		********************* //

/**
 * Add an input link to the node
 * Input: pLinParam : CLink&
 * Output: /
 * Precondition : /
 * Postcondition : pLINParam has been added to the inputs links list, and uiNODInputSize has been incremented
 */
void CNode::NODAddInputLink(CLink& pLINParam) {

	CLink** ppLINTemp = nullptr;

	uiNODInputSize++;
	ppLINTemp = (CLink**)realloc(ppLINNODInputLink, uiNODInputSize * sizeof(CLink*));

	if (ppLINTemp != nullptr) {
		ppLINNODInputLink = ppLINTemp;
		ppLINNODInputLink[uiNODInputSize - 1] = &pLINParam;	//JE SUIS PAS DU TOUT SUR
	}
	else
		throw CException();

}


/**
 * Add an output link to the node
 * Input: pLinParam : CLink&
 * Output: /
 * Precondition : /
 * Postcondition : pLINParam has been added to the outputs links list, and uiNODOuputSize has been incremented
 */
void CNode::NODAddOutputLink(CLink& pLINParam) {

	CLink** ppLINTemp = nullptr;

	uiNODInputSize++;
	ppLINTemp = (CLink**)realloc(ppLINNODOutputLink, uiNODInputSize * sizeof(CLink*));

	if (ppLINTemp != nullptr) {
		ppLINNODOutputLink = ppLINTemp;
		ppLINNODOutputLink[uiNODInputSize - 1] = &pLINParam;	//JE SUIS PAS DU TOUT SUR
	}
	else
		throw CException();

}


/**
 * Remove an input link to the node
 * Input: pLinParam : CLink&
 * Output: /
 * Precondition : /
 * Postcondition : If pLINParam isn't in the list an error is throw, else
	pLINParam has been removed to the inputs links list, and uiNODInputSize has been decremented
 */
void CNode::NODRemoveInputLink(CLink& pLINParam) {

	unsigned int indexFound = 0;

	bool bFound = false;
	for (int uiLoop = 0; uiLoop < uiNODInputSize; uiLoop++) {
		if (ppLINNODInputLink[uiLoop] == &pLINParam) {
			indexFound = uiLoop;
			bFound = true;
		}
	}
	if (bFound == false) {
		//lancer une erreur, ou avoir une valeur de retour en bool
	}

	for (int uiLoop = indexFound; uiLoop < uiNODInputSize - 1; uiLoop++) {
		ppLINNODInputLink[uiLoop] = ppLINNODInputLink[uiLoop + 1];
	}

	CLink** ppLINTemp = nullptr;

	uiNODInputSize--;
	ppLINTemp = (CLink**)realloc(ppLINNODInputLink, uiNODInputSize * sizeof(CLink*));

	if (ppLINTemp != nullptr) {
		ppLINNODInputLink = ppLINTemp;
	}
	else
		throw CException();

}


/**
 * Remove an output link to the node
 * Input: pLinParam : CLink&
 * Output: /
 * Precondition : /
 * Postcondition : If pLINParam isn't in the list an error is throw, else
	pLINParam has been removed to the outputs links list, and uiNODInputSize has been decremented
 */
void CNode::NODRemoveOutputLink(CLink& pLINParam) {

	unsigned int indexFound = 0;

	bool bFound = false;
	for (int uiLoop = 0; uiLoop < uiNODOutputSize; uiLoop++) {
		if (ppLINNODOutputLink[uiLoop] == &pLINParam) {
			indexFound = uiLoop;
			bFound = true;
		}
	}
	if (bFound == false) {
		//lancer une erreur, ou avoir une valeur de retour en bool
	}

	for (int uiLoop = indexFound; uiLoop < uiNODOutputSize - 1; uiLoop++) {
		ppLINNODOutputLink[uiLoop] = ppLINNODInputLink[uiLoop + 1];
	}

	CLink** ppLINTemp = nullptr;

	uiNODOutputSize--;
	ppLINTemp = (CLink**)realloc(ppLINNODOutputLink, uiNODOutputSize * sizeof(CLink*));

	if (ppLINTemp != nullptr) {
		ppLINNODOutputLink = ppLINTemp;
	}
	else
		throw CException();

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
 * Setter of uiNODValue
 * Input: uiValue: unsigned int
 * Output: /
 * Precondition : /
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
CLink** CNode::NODGetInputLink(unsigned int* uiSize) {
	*uiSize = uiNODInputSize;
	return ppLINNODInputLink;
}

/**
 * Getter of ppLINNODOutputLink
 * Input: /
 * Output: *uiSize, CLink**
 * Precondition : /
 * Postcondition : uiNODValue is returned and uiSize = uiNODOutputSize
 */
CLink** CNode::NODGetOutputLink(unsigned int* uiSize) {
	*uiSize = uiNODOutputSize;
	return ppLINNODInputLink;
}