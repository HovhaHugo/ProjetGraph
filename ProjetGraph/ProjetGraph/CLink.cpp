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
	uiLINEnd = 0;
}


/**
 * Constructor of CLink
 * Input: uiDestination : unsigned int
 * Output: /
 * Precondition : /
 * Postcondition : the object has been created in memory with uiNODEnd = uiDestination
 */
CLink::CLink(unsigned int uiDestination) {
	uiLINEnd = uiDestination;
}


/**
 * Copy of constructor of CLink
 * Input: pLINToCopy : CLink*
 * Output: /
 * Precondition : /
 * Postcondition : uiNODEnd = pLINToCopy->uiNODEnd
 */
CLink::CLink(CLink* pLINToCopy) {
	uiLINEnd = pLINToCopy->uiLINEnd;
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
	cout << "Link to Node #" << uiLINEnd << endl;

}


/**
 * Getter of uiNODEnd
 * Input: /
 * Output: unsigned int
 * Precondition : /
 * Postcondition : uiNODEnd is returned
 */
unsigned int CLink::LINGetEnd() {
	return uiLINEnd;
}

/**
 * Setter of uiNODEnd
 * Input: unsigned int : uiParam
 * Output: /
 * Precondition : /
 * Postcondition : uiNODEnd = uiParam;
 */
void CLink::LINSetEnd(unsigned int uiParam) {
	uiLINEnd = uiParam;
}