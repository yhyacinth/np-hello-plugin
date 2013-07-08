
#include "func.h"

bool TestMethod1(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	OutputDebugString(_T("TestMethod1"));

	// Some Work


	// Return
	CString str(_T("ABCD 한글"));
	uint32_t len = str.GetLength() + 1;
	char *copy = (char*)NPN_MemAlloc(len);
	strncpy(copy, ATL::CW2A(str.GetBuffer(0)), len); // * 유니코드 리턴이 필요하면 need to convert ANSI to UTF8 

	STRINGZ_TO_NPVARIANT(copy, *result);

	return PR_TRUE;
}
