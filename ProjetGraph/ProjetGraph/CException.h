
#ifndef DEF_CEXCEPTION
#define DEF_CEXCEPTION


class CException
{
private:
	unsigned int uiEXCValue;

public:
	//Constructors/destructor
	CException();
	CException(unsigned int uiValueParam);
	~CException();

	//Getters/setters
	void EXCsetValue(unsigned int uiValueParam);
	unsigned int EXCgetValue();
};


#endif
