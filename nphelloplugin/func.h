
///// AFX Header Start
#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#ifndef WINVER                          // 필요한 최소 플랫폼을 Windows Vista로 지정합니다.
#define WINVER 0x0600           // 다른 버전의 Windows에 맞도록 적합한 값으로 변경해 주십시오.
#endif

#ifndef _WIN32_WINNT            // 필요한 최소 플랫폼을 Windows Vista로 지정합니다.
#define _WIN32_WINNT 0x0600     // 다른 버전의 Windows에 맞도록 적합한 값으로 변경해 주십시오.
#endif

#ifndef _WIN32_WINDOWS          // 필요한 최소 플랫폼을 Windows 98로 지정합니다.
#define _WIN32_WINDOWS 0x0410 // Windows Me 이상에 맞도록 적합한 값으로 변경해 주십시오.
#endif

#ifndef _WIN32_IE                       // 필요한 최소 플랫폼을 Internet Explorer 7.0으로 지정합니다.
#define _WIN32_IE 0x0700        // 다른 버전의 IE에 맞도록 적합한 값으로 변경해 주십시오.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.


#include <afxdisp.h>        // MFC 자동화 클래스입니다.

#include <winsock2.h>

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <locale.h>

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원
///// AFX Header End

#include "plugin.h"
#include "npfunctions.h"

#ifdef XP_WIN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#endif

#ifdef XP_MAC
#include <TextEdit.h>
#endif

#ifdef XP_UNIX
#include <string.h>
#endif


#define PR_TRUE true
#define PR_FALSE false

bool TestMethod1(const NPVariant *args, uint32_t argCount, NPVariant *result);
