#pragma once

#include "PBAny.h"
#include "PBArray.h"


namespace Inf
{
    class DynPBObject
    {
    public:
        /**
         * Creates a new Wrapper for an already existing object.
         * Will be Null if obj is 0.
         *
         * \param session       Current Session
         * \param obj           pbobject or 0
         * \param className     Name of the PowerBuilder Class, can be ""
         * \param groupType     Group type of the object
         */
        DynPBObject(IPB_Session* session, pbobject obj, pbclass cls = 0)
            : m_Session(session), m_Object(obj), m_Class(cls)
        {
            if (!IsNull())
            {
                session->AddGlobalRef(m_Object);

                pbclass obj_class = m_Session->GetClass(m_Object);
                if (m_Class)
                {
                    if (!Helper::IsPBBaseClass(m_Session, m_Class, obj_class))
                        throw PBNI_Exception(
                            L"Tried to cast an Object to a Class which is not its base",
                            {
                                { L"From", m_Session->GetClassName(obj_class) },
                                { L"To", m_Session->GetClassName(m_Class) },
                            }
                        );
                }
                else
                    m_Class = obj_class;
            }
        }

        /**
         * Creates a new Wrapper for an already existing object.
         * Will be Null if obj is 0.
         *
         * \param session   Current Session
         * \param className     Name of the PowerBuilder Class, can be ""
         * \param groupType     Group type of the object
         *
         * \throw Inf::PBNI_Exception   If the Group or Class cannot be found
         */
        DynPBObject(IPB_Session* session, pbobject obj, std::wstring className, pbgroup_type groupType)
            : DynPBObject(session, obj, FindClass(session, className, groupType))
        { }

        /**
         * Will create a new object of the correct Class.
         *
         * \param session   Current Session
         * \param className     Name of the PowerBuilder Class, can be ""
         * \param groupType     Group type of the object
         *
         * \throw Inf::PBNI_Exception   If the Group or Class cannot be found
         */
        DynPBObject(IPB_Session* session, std::wstring className, pbgroup_type groupType)
            : DynPBObject(session, FindClass(session, className, groupType))
        { }

        /**
         * Will create a new object of the correct Class.
         *
         * \param session   Current Session
         * \param className     Name of the PowerBuilder Class, can be ""
         * \param groupType     Group type of the object
         *
         * \throw Inf::PBNI_Exception   If the Group or Class cannot be found
         */
        DynPBObject(IPB_Session* session, pbclass cls)
            : DynPBObject(session, session->NewObject(cls), cls)
        { }

        DynPBObject(const DynPBObject& other)
            : DynPBObject(other.m_Session, other.m_Object, other.m_Class)
        { }

        DynPBObject& operator=(const DynPBObject& other)
        {
            if (this != &other)
            {
                if (m_Object)
                    m_Session->RemoveGlobalRef(m_Object);

                m_Object = other.m_Object;
                m_Class = other.m_Class;
                m_Session = other.m_Session;
                m_Session->AddGlobalRef(m_Object);
            }
            return *this;
        }

        virtual ~DynPBObject()
        {
            if (m_Object)
                m_Session->RemoveGlobalRef(m_Object);
        }

        /**
         * Returns the C++ pointer to the Native class of this object.
         *
         * \return Pointer to the Object extending IPBX_UserObject
         *
         * \throw Inf::PBNI_Exception   If the object is not a Native Object
         */
        IPBX_UserObject* GetNativeInterface()
        {
            if (!m_Session->IsNativeObject(m_Object))
                throw PBNI_Exception(L"Not a Native Object");

            return m_Session->GetNativeInterface(m_Object);
        }

        /**
         * Simple helper function that calls Invoke in the background, for more info read the Invoke documentation.
         *
         * \throw Inf::PBNI_InvalidFieldException           If no matching functions were found
         * \throw Inf::PBNI_IncorrectArgumentsException     If the argument types dont match up
         * \throw Inf::PBNI_NullPointerException            If pbobject is Null
         * \throw Inf::PBNI_PowerBuilderException           If the function doesnt return PBX_SUCCESS
         * \throw Inf::PBNI_Exception                       If the Group or Class cannot be found
         */
        template<typename Ret = void, typename... Args>
            requires(
                !std::is_pointer_v<Ret> && !std::is_reference_v<Ret> && !Helper::is_pb_array_v<Ret> &&
                (!std::is_pointer_v<Args> && ...)
            )
        inline Ret Call(const std::wstring& method_name, Args... args)
        {
            return Invoke<Ret, Args...>(method_name, PBRT_FUNCTION, args...);
        }

        /**
         * Simple helper function that calls InvokeSig in the background, for more info read the InvokeSig documentation.
         *
         * \throw Inf::PBNI_InvalidFieldException           If no matching functions were found
         * \throw Inf::PBNI_IncorrectArgumentsException     If the argument types dont match up
         * \throw Inf::PBNI_NullPointerException            If pbobject is Null
         * \throw Inf::PBNI_PowerBuilderException           If the function doesnt return PBX_SUCCESS
         * \throw Inf::PBNI_Exception                       If the Group or Class cannot be found
         */
        template<typename Ret = void, typename... Args>
            requires(
                !std::is_pointer_v<Ret> && !std::is_reference_v<Ret> && !Helper::is_pb_array_v<Ret> &&
                (!std::is_pointer_v<Args> && ...)
            )
        inline Ret CallSig(const std::wstring& method_name, const std::wstring& pbsig, Args... args)
        {
            return InvokeSig<Ret, Args...>(method_name, PBRT_FUNCTION, pbsig, args...);
        }

        /**
         * Simple helper function that calls InvokeMatching in the background, for more info read the InvokeMatching
         * documentation. This can't be used to invoke a non-public function.
         *
         * \throw Inf::PBNI_InvalidFieldException           If no matching functions were found
         * \throw Inf::PBNI_IncorrectArgumentsException     If the argument types dont match up
         * \throw Inf::PBNI_NullPointerException            If pbobject is Null
         * \throw Inf::PBNI_PowerBuilderException           If the function doesnt return PBX_SUCCESS
         * \throw Inf::PBNI_Exception                       If the Group or Class cannot be found
         */
        template<typename Ret = void, typename... Args>
            requires(
                !std::is_pointer_v<Ret> && !std::is_reference_v<Ret> && !Helper::is_pb_array_v<Ret> &&
                (!std::is_pointer_v<Args> && ...)
            )
        inline Ret CallMatching(const std::wstring& method_name, const std::wstring& arg_types, Args... args)
        {
            return InvokeMatching<Ret, Args...>(method_name, PBRT_FUNCTION, arg_types, args...);
        }


        /**
         * Invoke a Function of the pbobject with an unknown Signature.
         * Generates a signature out of the provided Return and Argument Types.
         *
         * \param method_name   The name of the Function to invoke
         * \param pbrt          The Type of the Function (Function or Event)
         * \param ...args       The Arguments to forward to the Function
         * \return              The acquired Value returned by the Function
         *
         * \tparam Ret  The type to be returned
         *
         * \throw Inf::PBNI_InvalidFieldException           If no matching functions were found
         * \throw Inf::PBNI_IncorrectArgumentsException     If the argument types dont match up
         * \throw Inf::PBNI_NullPointerException            If pbobject is Null
         * \throw Inf::PBNI_PowerBuilderException           If the function doesnt return PBX_SUCCESS
         * \throw Inf::PBNI_Exception                       If the Group or Class cannot be found
         */
        template<typename Ret = void, typename... Args>
            requires(
                !std::is_pointer_v<Ret> && !std::is_reference_v<Ret> && !Helper::is_pb_array_v<Ret> &&
                (!std::is_pointer_v<Args> && ...)
            )
        inline Ret Invoke(const std::wstring& method_name, PBRoutineType pbrt, Args... args)
        {
            std::wstring pbsig = std::wstring() + Type<Ret>::PBSignature;
            if constexpr (sizeof...(Args) > 0)
            {
                (
                    [&]
                    {
                        if constexpr (std::is_reference_v<Args>)
                        {
                            pbsig += std::wstring(L"R") + Type<std::remove_reference_t<Args>>::PBSignature;
                        }
                        else
                        {
                            pbsig += Type<Args>::PBSignature;
                        }
                    }(),
                    ...
                );
            }

            return InvokeSig<Ret, Args...>(method_name, pbrt, pbsig, args...);
        }

        /**
         * Invokes a Function of a pbobject with known argument types. The return type doesn't matter.
         * This can't be used to invoke a non-public function.
         *
         * \param method_name   The name of the Function to invoke
         * \param pbrt          The Type of the Function (Function or Event)
         * \param arg_types     Comma seperated names of the argument types (L"int, double")
         * \param ...args       The Arguments to forward to the Function
         * \return              The acquired Value returned by the Function
         *
         * \tparam Ret  The type to be returned
         *
         * \throw Inf::PBNI_InvalidFieldException           If no matching functions were found
         * \throw Inf::PBNI_IncorrectArgumentsException     If the argument types dont match up
         * \throw Inf::PBNI_NullPointerException            If pbobject is Null
         * \throw Inf::PBNI_PowerBuilderException           If the function doesnt return PBX_SUCCESS
         * \throw Inf::PBNI_Exception                       If the Group or Class cannot be found
         */
        template<typename Ret = void, typename... Args>
            requires(
                !std::is_pointer_v<Ret> && !std::is_reference_v<Ret> && !Helper::is_pb_array_v<Ret> &&
                (!std::is_pointer_v<Args> && ...)
            )
        inline Ret
        InvokeMatching(const std::wstring& method_name, PBRoutineType pbrt, const std::wstring& arg_types, Args&&... args)
        {
            if (IsNull())
                throw PBNI_NullPointerException(GetClassName());

            pbmethodID mid = m_Session->FindMatchingFunction(m_Class, method_name.c_str(), pbrt, arg_types.c_str());

            if (mid == kUndefinedMethodID)
                throw PBNI_InvalidFieldException(GetClassName(), method_name + L"(" + arg_types + L")", L"Method");

            return InvokeFid<Ret, Args...>(mid, args...);
        }

        /**
         * Invokes a Function of a pbobject with a known Signature.
         *
         * \param method_name   The name of the Function to invoke
         * \param pbrt          The Type of the Function (Function or Event)
         * \param pbsig         The Signature of the Function (pbsig170), L"" to pick first found
         * \param ...args       The Arguments to forward to the Function
         * \return              The acquired Value returned by the Function
         *
         * \tparam Ret  The type to be returned
         *
         * \throw Inf::PBNI_InvalidFieldException           If no matching functions were found
         * \throw Inf::PBNI_IncorrectArgumentsException     If the argument types dont match up
         * \throw Inf::PBNI_NullPointerException            If pbobject is Null
         * \throw Inf::PBNI_PowerBuilderException           If the function doesnt return PBX_SUCCESS
         * \throw Inf::PBNI_Exception                       If the Group or Class cannot be found
         */
        template<typename Ret = void, typename... Args>
            requires(
                !std::is_pointer_v<Ret> && !std::is_reference_v<Ret> && !Helper::is_pb_array_v<Ret> &&
                (!std::is_pointer_v<Args> && ...)
            )
        inline Ret InvokeSig(const std::wstring& method_name, PBRoutineType pbrt, const std::wstring& pbsig, Args... args)
        {
            if (IsNull())
                throw PBNI_NullPointerException(GetClassName());

            pbmethodID mid = m_Session->GetMethodID(m_Class, method_name.c_str(), pbrt, pbsig.c_str(), false);

            if (mid == kUndefinedMethodID)
                throw PBNI_InvalidFieldException(GetClassName(), method_name + L"(" + pbsig + L")", L"Method");

            return InvokeFid<Ret, Args...>(mid, args...);
        }

        /**
         * Invokes a Function of a pbobject with a Method ID
         *
         * \param method_id     The powerbuilder ID of the Method
         * \param ...args       The Arguments to forward to the Function
         * \return              The acquired Value returned by the Function
         *
         * \tparam Ret  The type to be returned
         *
         * \throw Inf::PBNI_InvalidFieldException           If no matching functions were found
         * \throw Inf::PBNI_IncorrectArgumentsException     If the argument types dont match up
         * \throw Inf::PBNI_NullPointerException            If pbobject is Null
         * \throw Inf::PBNI_PowerBuilderException           If the function doesnt return PBX_SUCCESS
         * \throw Inf::PBNI_Exception                       If the Group or Class cannot be found
         */
        template<typename Ret = void, typename... Args>
            requires(
                !std::is_pointer_v<Ret> && !std::is_reference_v<Ret> && !Helper::is_pb_array_v<Ret> &&
                (!std::is_pointer_v<Args> && ...)
            )
        inline Ret InvokeFid(pbmethodID mid, Args... args)
        {
            if (IsNull())
                throw PBNI_NullPointerException(GetClassName());

            PBCallInfo ci;
            m_Session->InitCallInfo(m_Class, mid, &ci);

            // Argument Checking
            if (ci.pArgs->GetCount() != sizeof...(Args))
            {
                m_Session->FreeCallInfo(&ci);
                throw PBNI_IncorrectArgumentsException(GetClassName(), std::to_wstring(mid));
            }

            pbint i = 0;
            (
                [&]
                {
                    Helper::PBValue value(m_Session, ci.pArgs->GetAt(i));
                    if (!value.Is<std::remove_reference_t<Args>>())
                    {
                        m_Session->FreeCallInfo(&ci);
                        throw PBNI_IncorrectArgumentsException(GetClassName(), std::to_wstring(mid), i);
                    }
                    i++;
                }(),
                ...
            );


            // Argument Gathering
            i = 0;
            (Helper::PBValue(m_Session, ci.pArgs->GetAt(i++)).Set<std::remove_reference_t<Args>>(args), ...);

            // TODO TriggerEvent?
            PBXRESULT res = m_Session->InvokeObjectFunction(m_Object, mid, &ci);

            if (res != PBX_OK)
            {
                m_Session->FreeCallInfo(&ci);

                throw PBNI_PowerBuilderException(L"IPB_Session::InvokeObjectFunction", res);
            }
            if (m_Session->HasExceptionThrown())
            {
                m_Session->FreeCallInfo(&ci);

                throw PBNI_ExceptionThrown();
            }

            // Apply references
            i = 0;
            (
                [&]
                {
                    if constexpr (std::is_reference_v<Args>)
                    {
                        if (ci.pArgs->GetAt(i)->IsByRef())
                        {
                            // We need to acquire the value, so it doesnt get freed by FreeCallInfo.
                            args = Helper::PBValue(m_Session, ci.pArgs->GetAt(i)).Get<std::remove_reference_t<Args>>(true);
                        }
                    }
                    i++;
                }(),
                ...
            );

            if constexpr (std::is_void_v<Ret>)
            {
                m_Session->FreeCallInfo(&ci);
            }
            else
            {
                // We need to acquire the value, so it doesnt get freed by FreeCallInfo.
                Ret ret = Helper::PBValue(m_Session, ci.returnValue).Get<Ret>(true);

                m_Session->FreeCallInfo(&ci);
                return ret;
            }
        }


        /**
         * Returns the ID of a Field.
         *
         * \param field_name    Name of the Field
         * \return              Field ID
         *
         * \throw Inf::PBNI_InvalidFieldException   If no matching field was found
         * \throw Inf::PBNI_NullPointerException    If class is Null
         */
        pbfieldID GetFieldId(const std::wstring& field_name) const
        {
            if (!m_Class)
                throw PBNI_NullPointerException(GetClassName());

            pbfieldID fid = m_Session->GetFieldID(m_Class, field_name.c_str());

            if (fid == kUndefinedFieldID)
                throw PBNI_InvalidFieldException(GetClassName(), field_name, L"Member variable");

            return fid;
        }

        /**
         * Returns whether a field is null
         *
         * \param field_name    Name of the field
         * \return              Is null
         *
         * \throw Inf::PBNI_InvalidFieldException   If no matching field was found
         * \throw Inf::PBNI_NullPointerException    If pbobject is Null
         */
        pbboolean IsFieldNull(const std::wstring& field_name) const
        {
            if (IsNull())
                throw PBNI_NullPointerException(GetClassName());

            pbfieldID fid = m_Session->GetFieldID(m_Class, field_name.c_str());

            return m_Session->IsFieldNull(m_Object, fid);
        }

        /**
         * Returns whether a field is an Object
         *
         * \param field_name    Name of the field
         * \return              Is Object
         *
         * \throw Inf::PBNI_InvalidFieldException   If no matching field was found
         * \throw Inf::PBNI_NullPointerException    If class is Null
         */
        pbboolean IsFieldObject(const std::wstring& field_name) const
        {
            if (!m_Class)
                throw PBNI_NullPointerException(GetClassName());

            pbfieldID fid = m_Session->GetFieldID(m_Class, field_name.c_str());

            return m_Session->IsFieldObject(m_Class, fid);
        }

        /**
         * Returns whether a field is an Array
         *
         * \param field_name    Name of the field
         * \return              Is Array
         *
         * \throw Inf::PBNI_InvalidFieldException   If no matching field was found
         * \throw Inf::PBNI_NullPointerException    If class is Null
         */
        pbboolean IsFieldArray(const std::wstring& field_name) const
        {
            if (!m_Class)
                throw PBNI_NullPointerException(GetClassName());

            pbfieldID fid = m_Session->GetFieldID(m_Class, field_name.c_str());

            return m_Session->IsFieldArray(m_Class, fid);
        }

        /**
         * Returns the type of a field
         *
         * \param field_name    Name of the field
         * \return              Type of the field
         *
         * \throw Inf::PBNI_InvalidFieldException   If no matching field was found
         * \throw Inf::PBNI_NullPointerException    If class is Null
         */
        pbuint GetFieldType(const std::wstring& field_name) const
        {
            if (!m_Class)
                throw PBNI_NullPointerException(GetClassName());

            pbfieldID fid = m_Session->GetFieldID(m_Class, field_name.c_str());

            return m_Session->GetFieldType(m_Class, fid);
        }

        /**
         * Sets a Field of the pbobjec to a Value.
         *
         * \param field_name    The name of the PowerBuilder Field
         * \param t             The Value to set it to
         *
         * \tparam Field    The Type of the field to be set
         *
         * \throw Inf::PBNI_InvalidFieldException           If no matching field was found
         * \throw Inf::PBNI_IncorrectArgumentsException     If the argument types dont match up
         * \throw Inf::PBNI_NullPointerException            If pbobject is Null
         * \throw Inf::PBNI_PowerBuilderException           If SetField doesn't return PBX_SUCCESS
         * \throw Inf::PBNI_Exception                       If the Group or Class cannot be found
         */
        template<typename Field>
        inline void SetField(const std::wstring& field_name, const Field value)
        {
            if (IsNull())
                throw PBNI_NullPointerException(GetClassName());

            pbfieldID fid = GetFieldId(field_name);

            PBXRESULT result = PBX_SUCCESS;

            if constexpr (Helper::is_pb_array_v<Field>)
            {
                if (!m_Session->IsFieldArray(m_Class, fid))
                    throw PBNI_IncorrectArgumentsException(GetClassName(), field_name);

                if (value.IsNull())
                    m_Session->SetFieldToNull(m_Object, fid);
                else
                    result = m_Session->SetArrayField(m_Object, fid, value.m_Array);
            }
            else if constexpr (std::is_base_of_v<DynPBObject, Field>)
            {
                if (!m_Session->IsFieldObject(m_Class, fid))
                    throw PBNI_IncorrectArgumentsException(GetClassName(), field_name);

                if (value.IsNull())
                    m_Session->SetFieldToNull(m_Object, fid);
                else
                    result = m_Session->SetObjectField(m_Object, fid, (pbobject) value);
            }
            else
            {
                pbuint field_type = m_Session->GetFieldType(m_Class, fid);
                if (field_type != Type<Field>::PBType && field_type != pbvalue_any)
                    throw PBNI_IncorrectArgumentsException(GetClassName(), field_name);

                if (value.IsNull())
                    m_Session->SetFieldToNull(m_Object, fid);
                else
                    result = SetFieldImpl(fid, value);
            }

            if (result != PBX_SUCCESS)
                throw PBNI_PowerBuilderException(L"IPB_Session::SetArrayField", result);
        }


        /**
         * Gets a Field of the pbobject.
         *
         * \param field_name    The name of the PowerBuilder Field
         *
         * \tparam Field    The Type to be returned
         *
         * \throw Inf::PBNI_InvalidFieldException           If no matching field was found
         * \throw Inf::PBNI_IncorrectArgumentsException     If the argument types dont match up
         * \throw Inf::PBNI_NullPointerException            If pbobject is Null
         * \throw Inf::PBNI_Exception                       If the Group or Class cannot be found
         */
        template<typename Field>
        inline Field GetField(const std::wstring& field_name) const
        {
            if (IsNull())
                throw PBNI_NullPointerException(GetClassName());

            pbfieldID fid = GetFieldId(field_name);

            if constexpr (Helper::is_pb_array_v<Field>)
            {
                if (!m_Session->IsFieldArray(m_Class, fid))
                    throw PBNI_IncorrectArgumentsException(GetClassName(), field_name);

                pbboolean is_null = false;

                pbarray pb_array = m_Session->GetArrayField(m_Object, fid, is_null);
                return { m_Session, is_null ? 0 : pb_array };
            }
            else if constexpr (Helper::is_pb_object_v<Field>)
            {
                if (!m_Session->IsFieldObject(m_Class, fid))
                    throw PBNI_IncorrectArgumentsException(GetClassName(), field_name);

                pbboolean is_null = false;

                pbobject pb_object = m_Session->GetObjectField(m_Object, fid, is_null);

                if (!is_null && !Helper::IsPBBaseClass(m_Session, Field::PBClass(m_Session), m_Session->GetClass(pb_object)))
                    throw PBNI_IncorrectArgumentsException(GetClassName(), field_name);

                return { m_Session, is_null ? 0 : pb_object };
            }
            else if constexpr (std::is_same_v<DynPBObject, Field>)
            {
                if (!m_Session->IsFieldObject(m_Class, fid))
                    throw PBNI_IncorrectArgumentsException(GetClassName(), field_name);

                pbboolean is_null = false;

                pbobject pb_object = m_Session->GetObjectField(m_Object, fid, is_null);
                return { m_Session, is_null ? 0 : pb_object };
            }
            else
            {
                pbuint field_type = m_Session->GetFieldType(m_Class, fid);
                if (field_type != Type<Field>::PBType)
                    throw PBNI_IncorrectArgumentsException(GetClassName(), field_name);


                return GetFieldImpl(Type<Field>(), fid);
            }
        };


        /**
         * Wheteher the pbobject is Null.
         *
         * \return Is Null
         */
        bool IsNull() const
        {
            return !m_Object;
        }

        /**
         * Get the Class Name of this objects class
         *
         * \return  Class name
         */
        std::wstring GetClassName() const
        {
            if (!m_Class)
                return L"NULL!";

            LPCTSTR name = m_Session->GetClassName(m_Class);
            std::wstring className(name);

            m_Session->ReleaseString(name);
            return className;
        }

        /**
         * \return  The Group Name extracted from class_id
         */
        static std::wstring ExtractGroupName(const std::wstring& className)
        {
            size_t i = className.find_first_of(L'.');

            if (i == 0 || i == std::wstring::npos)
                return className;

            if (className.find_last_of(L'.') != i)
                return L"";

            return className.substr(0, i);
        }

        /**
         * \return  The Class Name extracted from class_id
         */
        static std::wstring ExtractClassName(const std::wstring& className)
        {
            size_t i = className.find_first_of(L'.');

            if (i == std::wstring::npos)
                return className;

            if (className.find_last_of(L'.') != i)
                return L"";

            return className.substr(i + 1);
        }

        /**
         * Finds a Class using a className in the form of group.class or just class
         *
         * \return  The pbclass found using Group and Class Name
         *
         * \throw Inf::PBNI_Exception   If the Group or Class cannot be found
         */
        static pbclass FindClass(IPB_Session* session, const std::wstring& className, pbgroup_type groupType)
        {
            std::wstring groupName = ExtractGroupName(className);
            pbgroup group = session->FindGroup(groupName.c_str(), groupType);
            if (!group)
            {
                if (groupName != className)
                    throw PBNI_Exception(
                        L"Unable to find group",
                        {
                            { L"Group", ExtractGroupName(className) },
                            { L"ID", className },
                        }
                    );

                group = session->GetSystemGroup();
            }

            pbclass cls = session->FindClass(group, ExtractClassName(className).c_str());
            if (!cls)
            {
                throw PBNI_Exception(
                    L"Unable to find class",
                    {
                        { L"Group", ExtractGroupName(className) },
                        { L"Class", ExtractClassName(className) },
                        { L"ID", className },
                    }
                );
            }

            return cls;
        }

        /**
         * This conversion operator is currently the only way of getting the pbobject out.
         *
         * \return  The pbobject used for PowerBuilder functions
         */
        operator pbobject() const
        {
            return m_Object;
        }

    private:
        template<Helper::FixedString class_id, pbgroup_type group_type>
        friend class PBObject;

        IPB_Session* m_Session;
        pbobject m_Object = 0;
        pbclass m_Class = 0;

        // clang-format off
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBByte&     t) { return m_Session->SetByteField(m_Object, fid, t); }
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBBoolean&  t) { return m_Session->SetCharField(m_Object, fid, t); }
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBChar&     t) { return m_Session->SetCharField(m_Object, fid, t); }
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBInt&      t) { return m_Session->SetIntField(m_Object, fid, t); }
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBUint&     t) { return m_Session->SetUintField(m_Object, fid, t); }
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBLong&     t) { return m_Session->SetLongField(m_Object, fid, t); }
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBUlong&    t) { return m_Session->SetUlongField(m_Object, fid, t); }
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBLongLong& t) { return m_Session->SetLongLongField(m_Object, fid, t); }
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBReal&     t) { return m_Session->SetRealField(m_Object, fid, t); }
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBDouble&   t) { return m_Session->SetDoubleField(m_Object, fid, t); }
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBDecimal&  t) { return m_Session->SetDecField(m_Object, fid, t); }
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBTime&     t) { return m_Session->SetTimeField(m_Object, fid, t); }
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBDate&     t) { return m_Session->SetDateField(m_Object, fid, t); }
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBDateTime& t) { return m_Session->SetDateTimeField(m_Object, fid, t); }
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBString&   t) { return m_Session->SetPBStringField(m_Object, fid, t); }
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBBlob&     t) { return m_Session->SetBlobField(m_Object, fid, t); }
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBAny&      t) { pbboolean is_null; return t.ToValue(m_Session->GetPBAnyField(m_Object, fid, is_null)); }

        inline PBByte       GetFieldImpl(Type<PBByte>,     pbfieldID fid) const { pbboolean is_null = false; pbbyte pb_byte         = m_Session->GetByteField(m_Object, fid, is_null);     return is_null ? PBByte()       : PBByte(pb_byte); }
        inline PBBoolean    GetFieldImpl(Type<PBBoolean>,  pbfieldID fid) const { pbboolean is_null = false; pbboolean pb_boolean   = m_Session->GetCharField(m_Object, fid, is_null);     return is_null ? PBBoolean()    : PBBoolean(pb_boolean); }
        inline PBChar       GetFieldImpl(Type<PBChar>,     pbfieldID fid) const { pbboolean is_null = false; pbchar pb_char         = m_Session->GetCharField(m_Object, fid, is_null);     return is_null ? PBChar()       : PBChar(pb_char); }
        inline PBInt        GetFieldImpl(Type<PBInt>,      pbfieldID fid) const { pbboolean is_null = false; pbint pb_int           = m_Session->GetIntField(m_Object, fid, is_null);      return is_null ? PBInt()        : PBInt(pb_int); }
        inline PBUint       GetFieldImpl(Type<PBUint>,     pbfieldID fid) const { pbboolean is_null = false; pbuint pb_uint         = m_Session->GetUintField(m_Object, fid, is_null);     return is_null ? PBUint()       : PBUint(pb_uint); }
        inline PBLong       GetFieldImpl(Type<PBLong>,     pbfieldID fid) const { pbboolean is_null = false; pblong pb_long         = m_Session->GetLongField(m_Object, fid, is_null);     return is_null ? PBLong()       : PBLong(pb_long); }
        inline PBUlong      GetFieldImpl(Type<PBUlong>,    pbfieldID fid) const { pbboolean is_null = false; pbulong pb_ulong       = m_Session->GetUlongField(m_Object, fid, is_null);    return is_null ? PBUlong()      : PBUlong(pb_ulong); }
        inline PBLongLong   GetFieldImpl(Type<PBLongLong>, pbfieldID fid) const { pbboolean is_null = false; pblonglong pb_longlong = m_Session->GetLongLongField(m_Object, fid, is_null); return is_null ? PBLongLong()   : PBLongLong(pb_longlong); }
        inline PBReal       GetFieldImpl(Type<PBReal>,     pbfieldID fid) const { pbboolean is_null = false; pbreal pb_real         = m_Session->GetRealField(m_Object, fid, is_null);     return is_null ? PBReal()       : PBReal(pb_real); }
        inline PBDouble     GetFieldImpl(Type<PBDouble>,   pbfieldID fid) const { pbboolean is_null = false; pbdouble pb_double     = m_Session->GetDoubleField(m_Object, fid, is_null);   return is_null ? PBDouble()     : PBDouble(pb_double); }
        inline PBDecimal    GetFieldImpl(Type<PBDecimal>,  pbfieldID fid) const { pbboolean is_null = false; pbdec pb_dec           = m_Session->GetDecField(m_Object, fid, is_null);      return { m_Session, is_null ? 0 : pb_dec }; }
        inline PBTime       GetFieldImpl(Type<PBTime>,     pbfieldID fid) const { pbboolean is_null = false; pbtime pb_time         = m_Session->GetTimeField(m_Object, fid, is_null);     return { m_Session, is_null ? 0 : pb_time }; }
        inline PBDate       GetFieldImpl(Type<PBDate>,     pbfieldID fid) const { pbboolean is_null = false; pbdate pb_date         = m_Session->GetDateField(m_Object, fid, is_null);     return { m_Session, is_null ? 0 : pb_date }; }
        inline PBDateTime   GetFieldImpl(Type<PBDateTime>, pbfieldID fid) const { pbboolean is_null = false; pbdatetime pb_datetime = m_Session->GetDateTimeField(m_Object, fid, is_null); return { m_Session, is_null ? 0 : pb_datetime }; }
        inline PBString     GetFieldImpl(Type<PBString>,   pbfieldID fid) const { pbboolean is_null = false; pbstring pb_string     = m_Session->GetStringField(m_Object, fid, is_null);   return { m_Session, is_null ? 0 : pb_string }; }
        inline PBBlob       GetFieldImpl(Type<PBBlob>,     pbfieldID fid) const { pbboolean is_null = false; pbblob pb_blob         = m_Session->GetBlobField(m_Object, fid, is_null);     return { m_Session, is_null ? 0 : pb_blob }; }
        inline PBAny        GetFieldImpl(Type<PBAny>,      pbfieldID fid) const { pbboolean is_null = false; IPB_Value* pb_any      = m_Session->GetPBAnyField(m_Object, fid, is_null);    return { m_Session, is_null ? 0 : pb_any, false }; }
        // clang-format on
    };

    /**
     * Wrapper for pbobject type. If the Group and Classnames are the same (most of the times), the ID of the Class is just
     * the Class name. If the Group and Class names are different, the ID is both combined with a dot (L"group.class"). This
     * is only the case for nested Types.
     *
     * \tparam class_id     ID of Group and Class
     * \tparam group_type   The Group Type used by PowerBuilder (struct, userobject, ...)
     */
    template<Helper::FixedString class_id, pbgroup_type group_type = pbgroup_userobject>
    class PBObject : public DynPBObject
    {
    public:
        static constexpr Helper::FixedString _class_id = class_id;
        static constexpr pbgroup_type _group_type = group_type;

        /**
         * Creates a new Wrapper for an already existing object.
         * Will be Null if obj is 0.
         *
         * \param session   Current Session
         * \param obj       pbobject or 0
         */
        PBObject(IPB_Session* session, pbobject obj)
            : DynPBObject(session, obj, class_id.data, group_type)
        { }

        /**
         * Will create a new object of the correct Class.
         *
         * \param session   Current Session
         *
         * \throw Inf::PBNI_Exception   If the Group or Class cannot be found
         */
        PBObject(IPB_Session* session)
            : DynPBObject(session, class_id.data, group_type)
        { }

        /**
         * Copy constructor
         */
        PBObject(const DynPBObject& other)
            : PBObject(other.m_Session, other.m_Object)
        { }

        /**
         * Get the pbclass extracted from the class_id.
         *
         * \return  pbclass
         *
         * \throw Inf::PBNI_Exception   If the Group or Class cannot be found
         */
        static pbclass PBClass(IPB_Session* session)
        {
            // No caching because it kept randomly erroring.
            return FindClass(session, class_id.data, group_type);

            // static pbclass s_Class;
            // static IPB_Session* s_LastSession = nullptr;

            // if (s_LastSession != session)
            //{
            //   s_Class = FindClass(session);
            //   s_LastSession = session;
            // }

            // return s_Class;
        }
    };

    template<Helper::FixedString class_id>
    using PBStruct = PBObject<class_id, pbgroup_structure>;
    template<Helper::FixedString class_id>
    using PBWindow = PBObject<class_id, pbgroup_window>;
    template<Helper::FixedString class_id>
    using PBDataWindow = PBObject<class_id, pbgroup_datawindow>;
    template<Helper::FixedString class_id>
    using PBFunction = PBObject<class_id, pbgroup_function>;
}  // namespace Inf
