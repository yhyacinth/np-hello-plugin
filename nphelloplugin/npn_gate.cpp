
// Implementation of Netscape entry points (NPN_*)

#include "npapi.h"
#include "npfunctions.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>

#ifndef HIBYTE
#define HIBYTE(x) ((((uint32_t)(x)) & 0xff00) >> 8)
#endif

#ifndef LOBYTE
#define LOBYTE(W) ((W) & 0xFF)
#endif

extern NPNetscapeFuncs NPNFuncs;

void NPN_Version(int* plugin_major, int* plugin_minor, int* netscape_major, int* netscape_minor)
{
	*plugin_major   = NP_VERSION_MAJOR;
	*plugin_minor   = NP_VERSION_MINOR;
	*netscape_major = HIBYTE(NPNFuncs.version);
	*netscape_minor = LOBYTE(NPNFuncs.version);
}

NPError NPN_GetURLNotify(NPP instance, const char *url, const char *target, void* notifyData)
{
	int navMinorVers = NPNFuncs.version & 0xFF;
	NPError rv = NPERR_NO_ERROR;

	if( navMinorVers >= NPVERS_HAS_NOTIFICATION )
		rv = NPNFuncs.geturlnotify(instance, url, target, notifyData);
	else
		rv = NPERR_INCOMPATIBLE_VERSION_ERROR;

	return rv;
}

NPError NPN_GetURL(NPP instance, const char *url, const char *target)
{
	NPError rv = NPNFuncs.geturl(instance, url, target);
	return rv;
}

NPError NPN_PostURLNotify(NPP instance, const char* url, const char* window, uint32_t len, const char* buf, NPBool file, void* notifyData)
{
	int navMinorVers = NPNFuncs.version & 0xFF;
	NPError rv = NPERR_NO_ERROR;

	if( navMinorVers >= NPVERS_HAS_NOTIFICATION )
		rv = NPNFuncs.posturlnotify(instance, url, window, len, buf, file, notifyData);
	else
		rv = NPERR_INCOMPATIBLE_VERSION_ERROR;

	return rv;
}

NPError NPN_PostURL(NPP instance, const char* url, const char* window, uint32_t len, const char* buf, NPBool file)
{
	NPError rv = NPNFuncs.posturl(instance, url, window, len, buf, file);
	return rv;
} 

NPError NPN_RequestRead(NPStream* stream, NPByteRange* rangeList)
{
	NPError rv = NPNFuncs.requestread(stream, rangeList);
	return rv;
}

NPError NPN_NewStream(NPP instance, NPMIMEType type, const char* target, NPStream** stream)
{
	int navMinorVersion = NPNFuncs.version & 0xFF;

	NPError rv = NPERR_NO_ERROR;

	if( navMinorVersion >= NPVERS_HAS_STREAMOUTPUT )
		rv = NPNFuncs.newstream(instance, type, target, stream);
	else
		rv = NPERR_INCOMPATIBLE_VERSION_ERROR;

	return rv;
}

int32_t NPN_Write(NPP instance, NPStream *stream, int32_t len, void *buffer)
{
	int navMinorVersion = NPNFuncs.version & 0xFF;
	int32_t rv = 0;

	if( navMinorVersion >= NPVERS_HAS_STREAMOUTPUT )
		rv = NPNFuncs.write(instance, stream, len, buffer);
	else
		rv = -1;

	return rv;
}

NPError NPN_DestroyStream(NPP instance, NPStream* stream, NPError reason)
{
	int navMinorVersion = NPNFuncs.version & 0xFF;
	NPError rv = NPERR_NO_ERROR;

	if( navMinorVersion >= NPVERS_HAS_STREAMOUTPUT )
		rv = NPNFuncs.destroystream(instance, stream, reason);
	else
		rv = NPERR_INCOMPATIBLE_VERSION_ERROR;

	return rv;
}

void NPN_Status(NPP instance, const char *message)
{
	NPNFuncs.status(instance, message);
}

const char* NPN_UserAgent(NPP instance)
{
	const char * rv = NULL;
	rv = NPNFuncs.uagent(instance);
	return rv;
}

void* NPN_MemAlloc(uint32_t size)
{
	void * rv = NULL;
	rv = NPNFuncs.memalloc(size);
	return rv;
}

void NPN_MemFree(void* ptr)
{
	NPNFuncs.memfree(ptr);
}

uint32_t NPN_MemFlush(uint32_t size)
{
	uint32_t rv = NPNFuncs.memflush(size);
	return rv;
}

void NPN_ReloadPlugins(NPBool reloadPages)
{
	NPNFuncs.reloadplugins(reloadPages);
}

#if 0
JRIEnv* NPN_GetJavaEnv(void)
{
	JRIEnv * rv = NULL;
	rv = NPNFuncs.getJavaEnv();
	return rv;
}

jref NPN_GetJavaPeer(NPP instance)
{
	jref rv;
	rv = NPNFuncs.getJavaPeer(instance);
	return rv;
}
#endif

NPError NPN_GetValue(NPP instance, NPNVariable variable, void *value)
{
	NPError rv = NPNFuncs.getvalue(instance, variable, value);
	return rv;
}

NPError NPN_SetValue(NPP instance, NPPVariable variable, void *value)
{
	NPError rv = NPNFuncs.setvalue(instance, variable, value);
	return rv;
}

void NPN_InvalidateRect(NPP instance, NPRect *invalidRect)
{
	NPNFuncs.invalidaterect(instance, invalidRect);
}

void NPN_InvalidateRegion(NPP instance, NPRegion invalidRegion)
{
	NPNFuncs.invalidateregion(instance, invalidRegion);
}

void NPN_ForceRedraw(NPP instance)
{
	NPNFuncs.forceredraw(instance);
}

NPIdentifier NPN_GetStringIdentifier(const NPUTF8 *name)
{
	return NPNFuncs.getstringidentifier(name);
}

void NPN_GetStringIdentifiers(const NPUTF8 **names, uint32_t nameCount,
							  NPIdentifier *identifiers)
{
	NPNFuncs.getstringidentifiers(names, nameCount, identifiers);
}

NPIdentifier NPN_GetStringIdentifier(int32_t intid)
{
	return NPNFuncs.getintidentifier(intid);
}

bool NPN_IdentifierIsString(NPIdentifier identifier)
{
	return NPNFuncs.identifierisstring(identifier);
}

NPUTF8 *NPN_UTF8FromIdentifier(NPIdentifier identifier)
{
	return NPNFuncs.utf8fromidentifier(identifier);
}

int32_t NPN_IntFromIdentifier(NPIdentifier identifier)
{
	return NPNFuncs.intfromidentifier(identifier);
}

NPObject *NPN_CreateObject(NPP npp, NPClass *aClass)
{
	return NPNFuncs.createobject(npp, aClass);
}

NPObject *NPN_RetainObject(NPObject *obj)
{
	return NPNFuncs.retainobject(obj);
}

void NPN_ReleaseObject(NPObject *obj)
{
	NPNFuncs.releaseobject(obj);
}

bool NPN_Invoke(NPP npp, NPObject* obj, NPIdentifier methodName,
				const NPVariant *args, uint32_t argCount, NPVariant *result)
{
	return NPNFuncs.invoke(npp, obj, methodName, args, argCount, result);
}

bool NPN_InvokeDefault(NPP npp, NPObject* obj, const NPVariant *args,
					   uint32_t argCount, NPVariant *result)
{
	OutputDebugString(L"AAAA NPN_InvokeDefault Start");
	bool bRet= NPNFuncs.invokeDefault(npp, obj, args, argCount, result);
	OutputDebugString(L"AAAA NPN_InvokeDefault End");
	return bRet;
}

bool NPN_Evaluate(NPP npp, NPObject* obj, NPString *script,
				  NPVariant *result)
{
	return NPNFuncs.evaluate(npp, obj, script, result);
}

bool NPN_GetProperty(NPP npp, NPObject* obj, NPIdentifier propertyName,
					 NPVariant *result)
{
	return NPNFuncs.getproperty(npp, obj, propertyName, result);
}

bool NPN_SetProperty(NPP npp, NPObject* obj, NPIdentifier propertyName,
					 const NPVariant *value)
{
	return NPNFuncs.setproperty(npp, obj, propertyName, value);
}

bool NPN_RemoveProperty(NPP npp, NPObject* obj, NPIdentifier propertyName)
{
	return NPNFuncs.removeproperty(npp, obj, propertyName);
}

bool NPN_Enumerate(NPP npp, NPObject *obj, NPIdentifier **identifier,
				   uint32_t *count)
{
	return NPNFuncs.enumerate(npp, obj, identifier, count);
}

bool NPN_Construct(NPP npp, NPObject *obj, const NPVariant *args,
				   uint32_t argCount, NPVariant *result)
{
	return NPNFuncs.construct(npp, obj, args, argCount, result);
}

bool NPN_HasProperty(NPP npp, NPObject* obj, NPIdentifier propertyName)
{
	return NPNFuncs.hasproperty(npp, obj, propertyName);
}

bool NPN_HasMethod(NPP npp, NPObject* obj, NPIdentifier methodName)
{
	return NPNFuncs.hasmethod(npp, obj, methodName);
}

void NPN_ReleaseVariantValue(NPVariant *variant)
{
	NPNFuncs.releasevariantvalue(variant);
}

void NPN_SetException(NPObject* obj, const NPUTF8 *message)
{
	NPNFuncs.setexception(obj, message);
}
