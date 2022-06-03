#pragma once

#include "CNode.h"
#include <fstream>

#pragma warning(disable: 4996)

#define EXCEPTION_CONVERSION_ERROR 3		//Conversion error, a letter was read instead of a number
#define EXCEPTION_MISSING_FILE 4			//The file was not found
#define EXCEPTION_ERROR_DATA_FILE 5		//Error from data in the file
#define EXCEPTION_MALLOC_ERROR 6			//Memory allocation error
#define EXCEPTION_INVALID_NUMBER 7

#define LINE_LENGTH 255

using namespace std;

class CParser
{

private:
	const char* pcPARFilePath;
	const char cPARSeparator = '=';
	void PARToUpper(char* pcOutput, const char* pcOrigin);
	char* PARJumpToIdentifier(ifstream *ifFile, const char* pcIdentifier);

public:
	CParser(const char* pcFilePathParam);
	unsigned int PARGetNumber(const char* pcIdentifier);
	CNode* PARGetNodes(unsigned int uiNodeListSize, const char* pcIdentifier);
	void PARGetLink(int* piFrom, int* piTo, unsigned int uiSize, const char* pcIdentifier);


};

