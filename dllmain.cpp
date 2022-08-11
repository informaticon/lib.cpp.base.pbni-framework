#include "Framework.h"


/**
 * Entrypoint for the dll.
 */
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


/**
 * .This is the function that gets called to get an instance of TSE_Wrapper
 */
PBXEXPORT PBXRESULT PBXCALL PBX_CreateNonVisualObject(IPB_Session* pbSession, pbobject pbobj, LPCTSTR xtraName, IPBX_NonVisualObject** obj)
{
    *obj = Inf::PBNI_Framework::GetInstance().CreateClass(xtraName, pbSession);

    return *obj ? PBX_SUCCESS : PBX_E_NO_SUCH_CLASS;
};

/**
 * This is the function that gets called by the PBVM to get the class and method descriptions, it will be put into a User Object called u_tse_pbni.
 * 
 * \return Unicode string describing the u_tse_pbni class and its methods.
 */
PBXEXPORT LPCTSTR PBXCALL PBX_GetDescription()
{
    return Inf::PBNI_Framework::GetInstance().GetDescription().c_str();
}
