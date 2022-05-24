
#ifndef DEF_CEXCEPTION
#define DEF_CEXCEPTION


class CException
{
private:
	unsigned int uiEXCValue;
	char* pcEXCFunction;

public:
	//Constructors/destructor
	CException();
	CException(unsigned int uiValueParam);
	CException(unsigned int uiValueParam, char* pcFunctionParam);
	~CException();

	//Getters/setters
	void EXCsetFunction(char* pcFunctionParam);
	void EXCsetValue(unsigned int uiValueParam);
	char* EXCgetFunction();
	unsigned int EXCgetValue();
};


#endif
