#pragma once

#include "PBArray.h"
#include "PBAny.h"


namespace Inf
{

    /**
     * Wrapper for pbobject type. If the Group and Classnames are the same (most of the times), the ID of the Class is just the Class name.
     * If the Group and Class names are different, the ID is both combined with a dot (L"group.class"). This is only the case for nested Types.
     *
     * \tparam class_id     ID of Group and Class
     * \tparam group_type   The Group Type used by PowerBuilder (struct, userobject, ...)
     */
    template <Helper::FixedString class_id, pbgroup_type group_type = pbgroup_userobject>
    class PBObject
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
            : m_Session(session), m_Object(obj)
        {
            if (!IsNull())
                session->AddLocalRef(m_Object);
        }

        /**
         * Will create a new object of the correct Class.
         *
         * \param session   Current Session
         *
         * \throw Inf::PBNI_Exception   If the Group or Class cannot be found
         */
        PBObject(IPB_Session* session)
            : m_Session(session)
        {
            m_Object = m_Session->NewObject(PBClass(m_Session));
            // We need to add a local ref, so we can return an object returned of an invoked function
            session->AddLocalRef(m_Object);
        }

        /**
         * The ability to cast any Class to any other Class.
         *
         * \param other     Object to cast
         */
        template <Helper::FixedString other_class_id, pbgroup_type other_group_type>
        PBObject(const PBObject<other_class_id, other_group_type>& other)
            : m_Session(other.m_Session), m_Object(other.m_Object)
        { }

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
                throw Inf::PBNI_Exception(L"Not a Native Object");

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
        template <typename Ret = void, typename... Args>
            requires (!std::is_pointer_v<Ret> && !std::is_reference_v<Ret> && !Helper::is_pb_array_v<Ret> && (!std::is_pointer_v<Args> && ...))
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
        template <typename Ret = void, typename... Args>
            requires (!std::is_pointer_v<Ret> && !std::is_reference_v<Ret> && !Helper::is_pb_array_v<Ret> && (!std::is_pointer_v<Args> && ...))
        inline Ret CallSig(const std::wstring& method_name, const std::wstring& pbsig, Args... args)
        {
            return InvokeSig<Ret, Args&...>(method_name, PBRT_FUNCTION, pbsig, args...);
        }

        /**
         * Simple helper function that calls InvokeMatching in the background, for more info read the InvokeMatching documentation.
         * 
         * \throw Inf::PBNI_InvalidFieldException           If no matching functions were found
         * \throw Inf::PBNI_IncorrectArgumentsException     If the argument types dont match up
         * \throw Inf::PBNI_NullPointerException            If pbobject is Null
         * \throw Inf::PBNI_PowerBuilderException           If the function doesnt return PBX_SUCCESS
         * \throw Inf::PBNI_Exception                       If the Group or Class cannot be found
        */
        template <typename Ret = void, typename... Args>
            requires (!std::is_pointer_v<Ret> && !std::is_reference_v<Ret> && !Helper::is_pb_array_v<Ret> && (!std::is_pointer_v<Args> && ...))
        inline Ret CallMatching(const std::wstring& method_name, const std::wstring& arg_types, Args... args)
        {
            return InvokeMatching<Ret, Args&...>(method_name, PBRT_FUNCTION, arg_types, args...);
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
        template <typename Ret = void, typename... Args>
            requires (!std::is_pointer_v<Ret> && !std::is_reference_v<Ret> && !Helper::is_pb_array_v<Ret> && (!std::is_pointer_v<Args> && ...))
        inline Ret Invoke(const std::wstring& method_name, PBRoutineType pbrt, Args... args)
        {
            std::wstring pbsig = std::wstring() + Type<Ret>::PBSignature;
            if constexpr (sizeof...(Args) > 0)
            {
                ([&] {
                    if constexpr (std::is_reference_v<Args>)
                    {
                        pbsig += std::wstring(L"R") + Type<std::remove_reference_t<Args>>::PBSignature;
                    }
                    else
                    {
                        pbsig += Type<Args>::PBSignature;
                    }
                    }(), ...);
            }

            return InvokeSig<Ret, Args&...>(method_name, pbrt, pbsig, args...);
        }

        /**
         * Invokes a Function of a pbobject with known argument types. The return type doesn't matter.
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
        template <typename Ret = void, typename... Args>
            requires (!std::is_pointer_v<Ret> && !std::is_reference_v<Ret> && !Helper::is_pb_array_v<Ret> && (!std::is_pointer_v<Args> && ...))
        inline Ret InvokeMatching(const std::wstring& method_name, PBRoutineType pbrt, const std::wstring& arg_types, Args&&... args)
        {
            if (IsNull())
                throw PBNI_NullPointerException(class_id.data);

            pbmethodID mid = m_Session->FindMatchingFunction(PBClass(m_Session), method_name.c_str(), pbrt, arg_types.c_str());

            if (mid == kUndefinedMethodID)
                throw PBNI_InvalidFieldException(class_id.data, method_name + L"(" + arg_types + L")", L"Method");

            return InvokeFid<Ret, Args&...>(mid, args...);
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
        template <typename Ret = void, typename... Args>
            requires (!std::is_pointer_v<Ret> && !std::is_reference_v<Ret> && !Helper::is_pb_array_v<Ret> && (!std::is_pointer_v<Args> && ...))
        inline Ret InvokeSig(const std::wstring& method_name, PBRoutineType pbrt, const std::wstring& pbsig, Args&&... args)
        {
            if (IsNull())
                throw PBNI_NullPointerException(class_id.data);

            pbmethodID mid = m_Session->GetMethodID(PBClass(m_Session), method_name.c_str(), pbrt, pbsig.c_str());

            if (mid == kUndefinedMethodID)
                throw PBNI_InvalidFieldException(class_id.data, method_name + L"(" + pbsig + L")", L"Method");

            return InvokeFid<Ret, Args&...>(mid, args...);
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
        template <typename Ret = void, typename... Args>
            requires (!std::is_pointer_v<Ret> && !std::is_reference_v<Ret> && !Helper::is_pb_array_v<Ret> && (!std::is_pointer_v<Args> && ...))
        inline Ret InvokeFid(pbmethodID mid, Args&&... args)
        {
            if (IsNull())
                throw PBNI_NullPointerException(class_id.data);

            PBCallInfo ci;
            m_Session->InitCallInfo(PBClass(m_Session), mid, &ci);

            // Argument Checking
            if (ci.pArgs->GetCount() != sizeof...(Args))
                throw PBNI_IncorrectArgumentsException(class_id.data, std::to_wstring(mid));

            pbint i = 0;
            ([&] {
                Helper::PBValue value(m_Session, ci.pArgs->GetAt(i));
                if (!value.Is<std::remove_reference_t<Args>>())
                    throw PBNI_IncorrectArgumentsException(class_id.data, std::to_wstring(mid), i);
                i++;
            }(), ...);


            // Argument Gathering
            i = 0;
            (Helper::PBValue(m_Session, ci.pArgs->GetAt(i++)).Set<std::remove_reference_t<Args>>(args), ...);

            PBXRESULT res = m_Session->InvokeObjectFunction(m_Object, mid, &ci);

            if (res != PBX_OK)
            {
                m_Session->FreeCallInfo(&ci);

                throw PBNI_PowerBuilderException(L"IPB_Session::InvokeObjectFunction", res);
            }

            // Apply references
            i = 0;
            ([&] {
                if constexpr (std::is_reference_v<Args>)
                {
                    if (ci.pArgs->GetAt(i)->IsByRef())
                    {
                        // We need to acquire the value, so it doesnt get freed by FreeCallInfo.
                        args = Helper::PBValue(m_Session, ci.pArgs->GetAt(i)).Get<std::remove_reference_t<Args>>(true);
                    }
                }
                i++;
                }(), ...);

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
        template <typename Field>
        inline void SetField(const std::wstring& field_name, const Field value)
        {
            pbfieldID fid = GetFieldId(field_name);

            PBXRESULT   result = PBX_SUCCESS;

            if constexpr (Helper::is_pb_array_v<Field>)
            {
                if (!m_Session->IsFieldArray(PBClass(m_Session), fid))
                    throw PBNI_IncorrectArgumentsException(class_id.data, field_name);

                if (value.IsNull())
                {
                    m_Session->SetFieldToNull(m_Object, fid);
                }
                else
                {
                    result = m_Session->SetArrayField(m_Object, fid, value.m_Array);
                }
            }
            else if constexpr (Helper::is_pb_object_v<Field>)
            {
                if (!m_Session->IsFieldObject(PBClass(m_Session), fid))
                    throw PBNI_IncorrectArgumentsException(class_id.data, field_name);

                if (value.IsNull())
                {
                    m_Session->SetFieldToNull(m_Object, fid);
                }
                else
                {
                    result = m_Session->SetObjectField(m_Object, fid, value.m_Object);
                }
            }
            else
            {
                pbuint field_type = m_Session->GetFieldType(PBClass(m_Session), fid);
                if (field_type != Type<Field>::PBType && field_type != pbvalue_any)
                    throw PBNI_IncorrectArgumentsException(class_id.data, field_name);

                if (value.IsNull())
                {
                    m_Session->SetFieldToNull(m_Object, fid);
                }
                else
                {
                    result = SetFieldImpl(fid, value);
                }
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
        template <typename Field>
        inline Field GetField(const std::wstring& field_name) const
        {
            pbfieldID fid = GetFieldId(field_name);

            bool isarray = m_Session->IsFieldArray(PBClass(m_Session), fid);
            bool isobject = m_Session->IsFieldObject(PBClass(m_Session), fid);
            auto fieldtype = m_Session->GetFieldType(PBClass(m_Session), fid);

            if constexpr (Helper::is_pb_array_v<Field>)
                {
                if (!m_Session->IsFieldArray(PBClass(m_Session), fid))
                    throw PBNI_IncorrectArgumentsException(class_id.data, field_name);

                pbboolean is_null = false;

                pbarray pb_array = m_Session->GetArrayField(m_Object, fid, is_null);
                return { m_Session, is_null ? 0 : pb_array };
            }
            else if constexpr (Helper::is_pb_object_v<Field>)
            {
                if (!m_Session->IsFieldObject(PBClass(m_Session), fid))
                    throw PBNI_IncorrectArgumentsException(class_id.data, field_name);

                pbboolean is_null = false;

                pbobject pb_object = m_Session->GetObjectField(m_Object, fid, is_null);
                return { m_Session, is_null ? 0 : pb_object };
            }
            else
            {
                pbuint field_type = m_Session->GetFieldType(PBClass(m_Session), fid);
                if (field_type != Type<Field>::PBType)
                    throw PBNI_IncorrectArgumentsException(class_id.data, field_name);

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
         * Get the Group name extracted from the class_id.
         *
         * \return  Group name
         */
        static const std::wstring& GroupName()
        {
            static std::wstring s_GroupName = ExtractGroupName();
            return s_GroupName;
        }

        /**
         * Get the Class name extracted from the class_id.
         *
         * \return  Class name
         */
        static const std::wstring& ClassName()
        {
            static std::wstring s_ClassName = ExtractClassName();
            return s_ClassName;
        }

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
            return FindClass(session);

            //static pbclass s_Class;
            //static IPB_Session* s_LastSession = nullptr;

            //if (s_LastSession != session)
            //{
            //  s_Class = FindClass(session);
            //  s_LastSession = session;
            //}

            //return s_Class;
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
        friend struct Helper::PBValue;
        friend struct PBAny;
        template <typename T>
        friend struct Type;
        template <typename PBT, pblong... dims>
            requires (sizeof...(dims) <= 3 && !std::is_reference_v<PBT> && !std::is_pointer_v<PBT>)
        friend class PBArray;
        template <Helper::FixedString, pbgroup_type>
        friend class PBObject;


        IPB_Session* m_Session;
        pbobject m_Object;

        /**
         * Returns the ID of a Field.
         *
         * \param field_name    Name of the Field
         * \return              Field ID
         *
         * \throw Inf::PBNI_InvalidFieldException   If no matching field was found
         * \throw Inf::PBNI_NullPointerException    If pbobject is Null
         */
        pbfieldID GetFieldId(const std::wstring& field_name) const
        {
            if (IsNull())
                throw PBNI_NullPointerException(class_id.data);

            pbfieldID fid = m_Session->GetFieldID(PBClass(m_Session), field_name.c_str());

            if (fid == kUndefinedFieldID)
                throw PBNI_InvalidFieldException(class_id.data, field_name, L"Member variable");

            return fid;
        }

        /**
         * Only used in Inf::PBObject<>::GroupName() to initialize a static variable.
         *
         * \return  The Group Name extracted from class_id
         */
        static std::wstring ExtractGroupName()
        {
            std::wstring id(class_id.data);
            size_t i = id.find_first_of(L'.');

            if (i == 0 || i == std::wstring::npos)
                return id;

            if (id.find_last_of(L'.') != i)
                return L"";

            return id.substr(0, i);
        }

        /**
         * Only used in Inf::PBObject<>::ClassName() to initialize a static variable.
         *
         * \return  The Class Name extracted from class_id
         */
        static std::wstring ExtractClassName()
        {
            std::wstring id(class_id.data);
            size_t i = id.find_first_of(L'.');

            if (i == std::wstring::npos)
                return id;

            if (id.find_last_of(L'.') != i)
                return L"";

            return id.substr(i + 1);
        }

        /**
         * Only used in Inf::PBObject<>::PBClass(m_Session) to initialize a static variable.
         *
         * \return  The pbclass found using Group and Class Name
         *
         * \throw Inf::PBNI_Exception   If the Group or Class cannot be found
         */
        static pbclass FindClass(IPB_Session* session)
        {
            pbgroup group = session->FindGroup(GroupName().c_str(), group_type);
            if (!group)
            {
                throw PBNI_Exception({
                    { L"Error", L"Unable to find group" },
                    { L"Group", GroupName() },
                    { L"ID", class_id.data },
                    });
            }

            pbclass cls = session->FindClass(group, ClassName().c_str());
            if (!cls)
            {
                throw PBNI_Exception({
                    { L"Error", L"Unable to find class" },
                    { L"Group", GroupName() },
                    { L"Class", ClassName() },
                    { L"ID", class_id.data },
                    });
            }

            return cls;
        }

        // Visual studio always messes up the nice formatting here, idk if this does anything, but its my last hope
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
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBDecimal&  t) { return m_Session->SetDecField(m_Object, fid, t.m_Decimal); }
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBTime&     t) { return m_Session->SetTimeField(m_Object, fid, t.m_Time); }
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBDate&     t) { return m_Session->SetDateField(m_Object, fid, t.m_Date); }
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBDateTime& t) { return m_Session->SetDateTimeField(m_Object, fid, t.m_DateTime); }
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBString&   t) { return m_Session->SetPBStringField(m_Object, fid, t.m_String); }
        inline PBXRESULT SetFieldImpl(pbfieldID fid, const PBBlob&     t) { return m_Session->SetBlobField(m_Object, fid, t.m_Blob); }
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

    template <Helper::FixedString class_id>
    using PBStruct = PBObject<class_id, pbgroup_structure>;
    template <Helper::FixedString class_id>
    using PBWindow = PBObject<class_id, pbgroup_window>;
    template <Helper::FixedString class_id>
    using PBDataWindow = PBObject<class_id, pbgroup_datawindow>;
}
