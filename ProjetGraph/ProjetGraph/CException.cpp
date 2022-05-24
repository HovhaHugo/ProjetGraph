
#include "CException.h"
#include <stdio.h>
#include<string.h>


/***
* Default constructor of CException
* Input: /
* Output: /
* Precondition: /
* Postcondition: uiEXCValue = 0 and pcEXCFunction = "Undefined function"
***/
CException::CException() {
	uiEXCValue = 0;
	pcEXCFunction = new char[25];

	const char* s = "Undefined function";

	sprintf_s(pcEXCFunction, 20, s);

}

/***
* Constructor of CException
* Input: unsigned int: uiValueParam
* Output: /
* Precondition: /
* Postcondition: uiEXCValue = uiValueParam and pcEXCFunction = "Undefined function"
***/
CException::CException(unsigned int uiValueParam) {
	uiEXCValue = uiValueParam;
	pcEXCFunction = new char[25];

	const char* s = "Undefined function";

	sprintf_s(pcEXCFunction, 20, s);
}

/***
* Constructor of CException
* Input: unsigned int: uiValueParam, char*: pcFunctionParam
* Output: /
* Precondition: /
* Postcondition: uiEXCValue = uiValueParam and pcEXCFunction = pcFunctionParam
***/
CException::CException(unsigned int uiValueParam, char* pcFunctionParam) {
	uiEXCValue = uiValueParam;

	size_t ulLength = strlen(pcFunctionParam);

	pcEXCFunction = new char[ulLength];

	sprintf_s(pcEXCFunction, ulLength, pcFunctionParam);

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
* Set the function of the Exception
* Input: char* :pcFunctionParam
* Output: /
* Precondition: /
* Postcondition: pcEXCfunction = pcFunctionParam
***/
void CException::EXCsetFunction(char* pcFunctionParam) {

	size_t ulLength = strlen(pcFunctionParam);

	if (pcEXCFunction != nullptr)
		delete pcEXCFunction;

	pcEXCFunction = new char[ulLength];

	sprintf_s(pcEXCFunction, ulLength, pcFunctionParam);

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
* Return the function of the the Exception
* Input: /
* Output: char *:uiEXCValue
* Precondition: /
* Postcondition: /
***/
char* CException::EXCgetFunction() {
	return pcEXCFunction;
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
