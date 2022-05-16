#include <iostream>
#include "CLink.h"

using namespace std;

/**
 * Constructor of CLink
 * Input: /
 * Output: /
 * Precondition : /
 * Postcondition : the object has been created in memory with uiNODEnd = 0;
 *	/!\ since the destination is set to 0 by default, the object is not usable/coherent
 */
CLink::CLink() {
	uiNODEnd = 0;
}


/**
 * Constructor of CLink
 * Input: uiDestination : unsigned int
 * Output: /
 * Precondition : /
 * Postcondition : the object has been created in memory with uiNODEnd = uiDestination
 */
CLink::CLink(unsigned int uiDestination) {
	uiNODEnd = uiDestination;
}


/**
 * Copy of constructor of CLink
 * Input: pLINToCopy : CLink*
 * Output: /
 * Precondition : /
 * Postcondition : uiNODEnd = pLINToCopy->uiNODEnd
 */
CLink::CLink(CLink* pLINToCopy) {
	uiNODEnd = pLINToCopy->uiNODEnd;
}


/**
 * Destructor of CLink
 * Input: /
 * Output: /
 * Precondition : /
 * Postcondition : The object has been deleted from memory
*/
CLink::~CLink() {

}


/**
 * Show a CLink
 * Input: /
 * Output: /
 * Precondition : /
 * Postcondition : The link is shown in the console
 */
void CLink::LINShow() {
	cout << "Lien vers : " << uiNODEnd << endl;

}


/**
 * Getter of uiNODEnd
 * Input: /
 * Output: unsigned int
 * Precondition : /
 * Postcondition : uiNODEnd is returned
 */
unsigned int CLink::LINGetEnd() {
	return uiNODEnd;
}

/**
 * Setter of uiNODEnd
 * Input: unsigned int : uiParam
 * Output: /
 * Precondition : /
 * Postcondition : uiNODEnd = uiParam;
 */
void CLink::LINSetEnd(unsigned int uiParam) {
	uiNODEnd = uiParam;
}