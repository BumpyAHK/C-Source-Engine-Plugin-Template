// yoinked from https://woz.blue/articles/non-cpp-plugin.html 
// and https://github.com/shroomwastaken/portal_plugin_template

#include <stdbool.h> 
#include <string.h>
#ifdef _WIN32
#define DLL_EXPORT __attribute__((dllexport))
#define VCALLCONV __fastcall
#define VCALLTHIS void* this, void* _edx_ignore
// ignore edx
#else
#define VCALLCONV
#define VCALLTHIS void* this
#endif

typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);

typedef int QueryCvarCookie_t;

typedef enum
{
	EQueryCvarValueStatus_ValueIntact=0,
	EQueryCvarValueStatus_CvarNotFound=1,
	EQueryCvarValueStatus_NotACvar=2,
	EQueryCvarValueStatus_CvarProtected=3
}EQueryCvarValueStatus;

//typedef void* (*edict_t);

bool VCALLCONV Load(VCALLTHIS,
                    CreateInterfaceFn ifacefactory,
                    CreateInterfaceFn gameserverfactory) {
    return true; // returns true when the plugin has loaded successfully
};

void VCALLCONV Unload(VCALLTHIS){	
};

void VCALLCONV Pause(VCALLTHIS){
};

void VCALLCONV UnPause(VCALLTHIS){
};

char VCALLCONV *GetPluginDescription(VCALLTHIS) {
    return "Example plugin";
};

void VCALLCONV LevelInit(VCALLTHIS, char const *pMapName){
};

void VCALLCONV ServerActivate(VCALLTHIS, void* pEdictList, 
	int edictCount, 
	int clientMax){
};

void VCALLCONV GameFrame(VCALLTHIS, bool simulating){
};

void VCALLCONV LevelShutdown(VCALLTHIS){
};

void VCALLCONV ClientActive(VCALLTHIS, void* pEntity){
};

void VCALLCONV ClientDisconnect(VCALLTHIS, void* pEntity){
};

void VCALLCONV ClientPutInServer(VCALLTHIS, void* pEntity,
	char const *playername){
};

void VCALLCONV SetCommandClient(VCALLTHIS, int index){
};

void VCALLCONV ClientSettingsChanged(VCALLTHIS, void* pEdict){
};

int VCALLCONV ClientConnect(VCALLTHIS, bool *bAllowConnect, void* pEntity,
	const char *pszName, const char *pszAddress, char *reject,
	int maxrejectlen){
	
	return 0;
};

int VCALLCONV ClientCommand(VCALLTHIS, void* pEntity, const void* args){
	return 0;
};

int VCALLCONV NetworkIDValidated(VCALLTHIS, const char *pszUserName,
	const char *pszNetworkID){

	return 0;
}

void VCALLCONV OnQueryCvarValueFinished(VCALLTHIS,
	QueryCvarCookie_t iCookie,
	void* pPlayerEntity, EQueryCvarValueStatus eStatus,
	const char *pCvarName, const char *pCvarValue){
};

void VCALLCONV OnEdictAllocated(VCALLTHIS, void* edict){
};

void VCALLCONV OnEdictFreed(VCALLTHIS, const void* edict){
};

struct CMyExamplePlugin {
    void *const *const vtable;
};

static const void *vtable[] = {
    (void*)&Load,
    (void*)&Unload,
	(void*)&Pause,
	(void*)&UnPause,
	(void*)&GetPluginDescription,
	(void*)&LevelInit,
	(void*)&ServerActivate,
	(void*)&GameFrame,
	(void*)&LevelShutdown,
	(void*)&ClientActive,
	(void*)&ClientDisconnect,
	(void*)&ClientPutInServer,
	(void*)&SetCommandClient,
	(void*)&ClientSettingsChanged,
	(void*)&ClientConnect, //PLUGIN_RESULT should return 0
	(void*)&ClientCommand, // ^ ^ ^
	(void*)&NetworkIDValidated, // ^ ^ ^
	(void*)&OnQueryCvarValueFinished, // added in interface v2
	(void*)&OnEdictAllocated, // interface v3
	(void*)&OnEdictFreed, // ^ ^ ^
};

struct CMyExamplePlugin plugin_object = { vtable };

DLL_EXPORT void *CreateInterface(const char *name, int *ret) {
    if (!strcmp(name, "ISERVERPLUGINCALLBACKS003")) {
        if (ret) *ret = 0;
        return &plugin_object;
    }
    if (ret) *ret = 1;
    return 0;
};