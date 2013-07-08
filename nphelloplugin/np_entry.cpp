// Main plugin entry point implementation


///// AFX Header Start
#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#ifndef WINVER                          // �ʿ��� �ּ� �÷����� Windows Vista�� �����մϴ�.
#define WINVER 0x0600           // �ٸ� ������ Windows�� �µ��� ������ ������ ������ �ֽʽÿ�.
#endif

#ifndef _WIN32_WINNT            // �ʿ��� �ּ� �÷����� Windows Vista�� �����մϴ�.
#define _WIN32_WINNT 0x0600     // �ٸ� ������ Windows�� �µ��� ������ ������ ������ �ֽʽÿ�.
#endif

#ifndef _WIN32_WINDOWS          // �ʿ��� �ּ� �÷����� Windows 98�� �����մϴ�.
#define _WIN32_WINDOWS 0x0410 // Windows Me �̻� �µ��� ������ ������ ������ �ֽʽÿ�.
#endif

#ifndef _WIN32_IE                       // �ʿ��� �ּ� �÷����� Internet Explorer 7.0���� �����մϴ�.
#define _WIN32_IE 0x0700        // �ٸ� ������ IE�� �µ��� ������ ������ ������ �ֽʽÿ�.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.


#include <afxdisp.h>        // MFC �ڵ�ȭ Ŭ�����Դϴ�.

#include <winsock2.h>

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <locale.h>

#include <afxcontrolbars.h>     // MFC�� ���� �� ��Ʈ�� ���� ����
///// AFX Header End

#include "npapi.h"
#include "npfunctions.h"


#ifndef HIBYTE
#define HIBYTE(x) ((((uint32_t)(x)) & 0xff00) >> 8)
#endif


NPNetscapeFuncs NPNFuncs;

#ifdef XP_WIN

NPError OSCALL NP_GetEntryPoints(NPPluginFuncs* pFuncs)
{
	if(pFuncs == NULL)
		return NPERR_INVALID_FUNCTABLE_ERROR;

//if(pFuncs->size < sizeof(NPPluginFuncs))
//    return NPERR_INVALID_FUNCTABLE_ERROR;

	
	pFuncs->version       = (NP_VERSION_MAJOR << 8) | NP_VERSION_MINOR;
	pFuncs->newp          = NPP_New;
	pFuncs->destroy       = NPP_Destroy;
	pFuncs->setwindow     = NPP_SetWindow;
	pFuncs->newstream     = NPP_NewStream;
	pFuncs->destroystream = NPP_DestroyStream;
	pFuncs->asfile        = NPP_StreamAsFile;
	pFuncs->writeready    = NPP_WriteReady;
	pFuncs->write         = NPP_Write;
	pFuncs->print         = NPP_Print;
	pFuncs->event         = NPP_HandleEvent;
	pFuncs->urlnotify     = NPP_URLNotify;
	pFuncs->getvalue      = NPP_GetValue;
	pFuncs->setvalue      = NPP_SetValue;
	pFuncs->javaClass     = NULL;
	
	return NPERR_NO_ERROR;
}

#endif /* XP_WIN */

char *NPP_GetMIMEDescription();

const char *
NP_GetMIMEDescription()
{
	return NPP_GetMIMEDescription();
}

NPError
NP_GetValue(void* future, NPPVariable variable, void *value)
{
	return NPP_GetValue((NPP_t *)future, variable, value);
}

NPError OSCALL
NP_Initialize(NPNetscapeFuncs* pFuncs
#ifdef XP_UNIX
              , NPPluginFuncs* pluginFuncs
#endif
)
{
	if(pFuncs == NULL)
	    return NPERR_INVALID_FUNCTABLE_ERROR;

	if(HIBYTE(pFuncs->version) > NP_VERSION_MAJOR)
		return NPERR_INCOMPATIBLE_VERSION_ERROR;

	if(pFuncs->size < sizeof(NPNetscapeFuncs))
	{
		//CUtilGlobal::ZsTRACE(_T("%u; %u"), pFuncs->size, sizeof(NPNetscapeFuncs));
		return NPERR_INVALID_FUNCTABLE_ERROR;
	}

	
	NPNFuncs.size                    = pFuncs->size;
	NPNFuncs.version                 = pFuncs->version;
	NPNFuncs.geturlnotify            = pFuncs->geturlnotify;
	NPNFuncs.geturl                  = pFuncs->geturl;
	NPNFuncs.posturlnotify           = pFuncs->posturlnotify;
	NPNFuncs.posturl                 = pFuncs->posturl;
	NPNFuncs.requestread             = pFuncs->requestread;
	NPNFuncs.newstream               = pFuncs->newstream;
	NPNFuncs.write                   = pFuncs->write;
	NPNFuncs.destroystream           = pFuncs->destroystream;
	NPNFuncs.status                  = pFuncs->status;
	NPNFuncs.uagent                  = pFuncs->uagent;
	NPNFuncs.memalloc                = pFuncs->memalloc;
	NPNFuncs.memfree                 = pFuncs->memfree;
	NPNFuncs.memflush                = pFuncs->memflush;
	NPNFuncs.reloadplugins           = pFuncs->reloadplugins;
	//NPNFuncs.getJavaEnv              = pFuncs->getJavaEnv;
	//NPNFuncs.getJavaPeer             = pFuncs->getJavaPeer;
	NPNFuncs.getvalue                = pFuncs->getvalue;
	NPNFuncs.setvalue                = pFuncs->setvalue;
	NPNFuncs.invalidaterect          = pFuncs->invalidaterect;
	NPNFuncs.invalidateregion        = pFuncs->invalidateregion;
	NPNFuncs.forceredraw             = pFuncs->forceredraw;
	NPNFuncs.getstringidentifier     = pFuncs->getstringidentifier;
	NPNFuncs.getstringidentifiers    = pFuncs->getstringidentifiers;
	NPNFuncs.getintidentifier        = pFuncs->getintidentifier;
	NPNFuncs.identifierisstring      = pFuncs->identifierisstring;
	NPNFuncs.utf8fromidentifier      = pFuncs->utf8fromidentifier;
	NPNFuncs.intfromidentifier       = pFuncs->intfromidentifier;
	NPNFuncs.createobject            = pFuncs->createobject;
	NPNFuncs.retainobject            = pFuncs->retainobject;
	NPNFuncs.releaseobject           = pFuncs->releaseobject;
	NPNFuncs.invoke                  = pFuncs->invoke;
	NPNFuncs.invokeDefault           = pFuncs->invokeDefault;
	NPNFuncs.evaluate                = pFuncs->evaluate;
	NPNFuncs.getproperty             = pFuncs->getproperty;
	NPNFuncs.setproperty             = pFuncs->setproperty;
	NPNFuncs.removeproperty          = pFuncs->removeproperty;
	NPNFuncs.hasproperty             = pFuncs->hasproperty;
	NPNFuncs.hasmethod               = pFuncs->hasmethod;
	NPNFuncs.releasevariantvalue     = pFuncs->releasevariantvalue;
	NPNFuncs.setexception            = pFuncs->setexception;

#ifdef XP_UNIX
	/*
	* Set up the plugin function table that Netscape will use to
	* call us.  Netscape needs to know about our version and size
	* and have a UniversalProcPointer for every function we
	* implement.
	*/
	pluginFuncs->version    = (NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR;
	pluginFuncs->size       = sizeof(NPPluginFuncs);
	pluginFuncs->newp       = NewNPP_NewProc(NPP_New);
	pluginFuncs->destroy    = NewNPP_DestroyProc(NPP_Destroy);
	pluginFuncs->setwindow  = NewNPP_SetWindowProc(NPP_SetWindow);
	pluginFuncs->newstream  = NewNPP_NewStreamProc(NPP_NewStream);
	pluginFuncs->destroystream = NewNPP_DestroyStreamProc(NPP_DestroyStream);
	pluginFuncs->asfile     = NewNPP_StreamAsFileProc(NPP_StreamAsFile);
	pluginFuncs->writeready = NewNPP_WriteReadyProc(NPP_WriteReady);
	pluginFuncs->write      = NewNPP_WriteProc(NPP_Write);
	pluginFuncs->print      = NewNPP_PrintProc(NPP_Print);
	pluginFuncs->urlnotify  = NewNPP_URLNotifyProc(NPP_URLNotify);
	pluginFuncs->event      = NULL;
	pluginFuncs->getvalue   = NewNPP_GetValueProc(NPP_GetValue);
#ifdef OJI
	pluginFuncs->javaClass  = NPP_GetJavaClass();
#endif

	NPP_Initialize();
#endif

	return NPERR_NO_ERROR;
}

NPError OSCALL NP_Shutdown()
{
	return NPERR_NO_ERROR;
}
