#pragma once

#include <vector>

#include "MethodDescription.h"

/**
 * This Macro is just there for convenienve.
 * Use it to register a Class to the PBNI Franework.
 * Make sure that every function you register to this class is in the same File.
 * Don't use this inside a header File.
 *
 * \param cls	The Class Type to use
 * \param name	A WString containing the Name to be used by PowerBuilder (Must be the same as GetPBName)
 */
#define INF_REGISTER_CLASS(cls, name) typedef cls Inf_PBNI_Class; static std::wstring s_PBNI_ClassName = name; static Inf::ClassDescription<cls> class_description(name)

namespace Inf
{
	/**
	 * This Class is there to be extended from, so that different ClassDescription Templates can all be put in one Type.
	 */
	class IClassDescription
	{
	public:
		/**
		 * This Method creates a new Object of its Type on the Heap and returns a Pointer to it.
		 * 
		 * \param session			Current session
		 * \param pbobj				The PowerBuilder object representing this
		 * \param pb_class_name		The name of the class used by PowerBuilder
		 * \return					Created object, cast to PBNI_Class*
		 */
		virtual PBNI_Class* Create(IPB_Session* session, pbobject pbobj, std::wstring pb_class_name) const = 0;

		/**
		 * This Method returns a Method of this Class.
		 * 
		 * \param method_id		The ID of the method
		 * \return				The Method
		 */
		IMethodDescription* GetMethod(pbmethodID method_id) const
		{
			return method_id < m_Methods.size() ? m_Methods[method_id] : nullptr;
		}

		/**
		 * This Method builds a Description out of itself and its Methods.
		 * It will always be a nonvisualobject.
		 * 
		 * \return	The Description
		 */
		std::wstring GetDescription() const
		{
			std::wstring builder = L"class " + m_PBName + L" from nonvisualobject\n";
			for (IMethodDescription* method : m_Methods)
			{
				builder += method->GetDescription() + L"\n";
			}
			builder += L"end class\n";

			return builder;
		}


	protected:
		friend PBNI_Framework;

		std::wstring m_PBName;
		std::vector<IMethodDescription*> m_Methods;

		/**
		 * This gets called by PBNI_Framework when a function registers itself to it with the name of this class.
		 * 
		 * \param method_description	The Description of the registered Method
		 */
		void AddMethod(IMethodDescription* method_description)
		{
			m_Methods.push_back(method_description);
		};
	};

	/**
	 * This is the derived class, this only needs to be a Template to store the Type of the Class and be able to create a new Object.
	 */
	template <typename Cls>
		requires (std::is_base_of_v<PBNI_Class, Cls>)
	class ClassDescription : public IClassDescription
	{
	public:
		/**
		 * This Constructor automatically registers to PBNI_Framework.
		 * 
		 * \param pb_name
		 */
		ClassDescription(std::wstring pb_name)
		{
			m_PBName = pb_name;
			PBNI_Framework::GetInstance().RegisterPBClass(pb_name, this);
		};

		PBNI_Class* Create(IPB_Session* session, pbobject pbobj, std::wstring pb_class_name) const override
		{
			if constexpr (std::is_constructible_v<Cls, IPB_Session*, pbobject, std::wstring>)
			{
				return static_cast<PBNI_Class*>(new Cls(session, pbobj, pb_class_name));
			}
			else
			{
				PBNI_Class* cls = static_cast<PBNI_Class*>(new Cls());
				cls->m_PBObject = pbobj;
				cls->m_Session = session;
				cls->m_PBName = pb_class_name;
				return cls;
			}
		}
	};
};
