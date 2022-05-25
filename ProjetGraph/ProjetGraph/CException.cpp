
#include "CException.h"
#include <stdio.h>
#include<string.h>


/***
* Default constructor of CException
* Input: /
* Output: /
* Precondition: /
* Postcondition: uiEXCValue = 0
***/
CException::CException() {
	uiEXCValue = 0;

}

/***
* Constructor of CException
* Input: unsigned int: uiValueParam
* Output: /
* Precondition: /
* Postcondition: uiEXCValue = uiValueParam
***/
CException::CException(unsigned int uiValueParam) {
	uiEXCValue = uiValueParam;
}


/***
* Delete a CException object
* Input: /
* Output: /
* Precondition: The object has been initialised in memory
* Postcondition: The object has been deleted from memory
***/
CException::~CException() {
}

/***
* Set the value of the Exception
* Input: unsigned int:uiValueParam
* Output: /
* Precondition: /
* Postcondition: uiEXCValue = uiValueParam
***/
void CException::EXCsetValue(unsigned int uiValueParam) {
	uiEXCValue = uiValueParam;
}

/***
* Return the value of the Exception
* Input: /
* Output: unsigned int:uiEXCValue
* Precondition: /
* Postcondition: /
***/
unsigned int CException::EXCgetValue() {
	return uiEXCValue;
}
