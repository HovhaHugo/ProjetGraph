#pragma once

#include "CNode.h"
#include <fstream>

#pragma warning(disable: 4996)

#define EXCEPTION_ConversionError 2		//Conversion error, a letter was read instead of a number
#define EXCEPTION_MissingFile 4			//The file was not found
#define EXCEPTION_ErrorDataFile 4		//Error from data in the file
#define EXCEPTION_Parser_not_init 5
#define EXCEPTION_MallocError 6			//Memory allocation error
#define EXCEPTION_invalide_number 7

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
	CNode** PARGetNodes(unsigned int uiNodeListSize, const char* pcIdentifier);
	void PARGetLink(int* piFrom, int* piTo, unsigned int iSize, const char* pcIdentifier);


};

