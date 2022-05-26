#pragma once
class CLink
{
private:
	unsigned int uiLINEnd;

public:
	CLink();
	CLink(unsigned int uiEnd);
	CLink(CLink* pLINToCopy);
	~CLink();

	CLink* operator=(CLink* pLINToCopy);

	void LINShow();

	unsigned int LINGetEnd();
	void LINSetEnd(unsigned int uiParam);
};

