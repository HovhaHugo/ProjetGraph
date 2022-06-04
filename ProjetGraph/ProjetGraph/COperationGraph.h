#pragma once

#pragma warning(disable: 4996)

#include <string.h>

#include "CNode.h";
#include "CGraph.h";

#include <iostream>



#define EXCEPTION_CONVERSION_ERROR 3

class COperationGraph
{

private:
	CGraph* OPECreateBlankDual(CGraph* pGRAToDual);
public:
	CGraph* OPEToDual(CGraph* pGRAToDual);
	CGraph* OPEInverse(CGraph* pGRAToInverse);
	

};
