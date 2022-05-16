#pragma once
class CLink
{
private:
	unsigned int uiNODEnd;

public:
	CLink();
	CLink(unsigned int uiDestination);
	CLink(CLink* pLINToCopy);
	~CLink();

	void LINShow();

	unsigned int LINGetEnd();
	void LINSetEnd(unsigned int uiParam);
};

