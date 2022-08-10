#pragma once

#include <vector>

#include "MethodDescription.h"


#define INF_REGISTER_CLASS(cls, name) typedef cls Inf_PBNI_Class; static std::wstring s_PBNI_ClassName = name; static Inf::ClassDescription<cls> class_description(name)

namespace Inf
{
	class IClassDescription
	{
	public:
		virtual PBNI_Class* Create() const = 0;

		IMethodDescription* GetMethod(pbmethodID method_id) const
		{
			return method_id < m_Methods.size() ? m_Methods[method_id] : nullptr;
		}

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

		void AddMethod(IMethodDescription* method_description)
		{
			m_Methods.push_back(method_description);
		};
	};

	template <typename Cls>
		requires (std::is_base_of_v<PBNI_Class, Cls>)
	class ClassDescription : public IClassDescription
	{
	public:
		ClassDescription(std::wstring pb_name)
		{
			m_PBName = pb_name;
			PBNI_Framework::GetInstance().RegisterPBNI_Class(pb_name, this);
		};

		PBNI_Class* Create() const override
		{
			return static_cast<PBNI_Class*>(new Cls());
		}
	};
};
