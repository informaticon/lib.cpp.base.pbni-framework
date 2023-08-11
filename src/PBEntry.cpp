#include "Framework.h"


/**
 * This Function will be called by PowerBuilder when you create a new Object of a Class that is defined in C++.
 * It will create a new Object on the Heap and return the Pointer to it.
 * 
 * \param pbSession     Current PowerBuilder Session
 * \param pbobj         The PowerBuilder reference to this
 * \param xtraName      The name of the Class
 * \param obj           The returned Object
 * \return              PBX_SUCESS if Object created, otherwise PBX_E_NO_SUCH_CLASS
 */
extern "C" PBXEXPORT PBXRESULT PBXCALL PBX_CreateNonVisualObject(IPB_Session* pbsession, pbobject pbobj, LPCTSTR xtraName, IPBX_NonVisualObject** obj)
{
    *obj = Inf::PBNI_Framework::GetInstance().CreateClass(xtraName, pbsession, pbobj);

    return *obj ? PBX_SUCCESS : PBX_E_NO_SUCH_CLASS;
};

/**
 * This is the function that gets called by PBNI to get the Class and Method Descriptions.
 * Each class will be put into a seperate User Object when you import it.
 * 
 * \return Unicode string describing the the registered Classes and their Methods.
 */
extern "C" PBXEXPORT LPCTSTR PBXCALL PBX_GetDescription()
{
    return Inf::PBNI_Framework::GetInstance().GetDescription().c_str();
}
