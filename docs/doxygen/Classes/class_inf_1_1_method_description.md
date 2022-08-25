---
title: Inf::MethodDescription

---

# Inf::MethodDescription



 [More...](#detailed-description)


`#include <MethodDescription.h>`

Inherits from [Inf::IMethodDescription](/doxygen/Classes/class_inf_1_1_i_method_description/)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| template <typename... ArgNames\> <br>| **[MethodDescription](/doxygen/Classes/class_inf_1_1_method_description/#function-methoddescription)**(std::wstring pc_class_name, std::wstring pb_method_name, Ret(Cls::*)(Args...) method, ArgNames... arg_names) |
| virtual PBXRESULT | **[Invoke](/doxygen/Classes/class_inf_1_1_method_description/#function-invoke)**([PBNI_Class](/doxygen/Classes/class_inf_1_1_p_b_n_i___class/) * object, IPB_Session * session, PBCallInfo * ci) override |

## Additional inherited members

**Public Functions inherited from [Inf::IMethodDescription](/doxygen/Classes/class_inf_1_1_i_method_description/)**

|                | Name           |
| -------------- | -------------- |
| std::wstring | **[GetDescription](/doxygen/Classes/class_inf_1_1_i_method_description/#function-getdescription)**() |

**Protected Functions inherited from [Inf::IMethodDescription](/doxygen/Classes/class_inf_1_1_i_method_description/)**

|                | Name           |
| -------------- | -------------- |
| template <typename Arg \> <br>void | **[SetReference](/doxygen/Classes/class_inf_1_1_i_method_description/#function-setreference)**(IPB_Session * session, IPB_Value * value, const Arg & arg) |

**Protected Attributes inherited from [Inf::IMethodDescription](/doxygen/Classes/class_inf_1_1_i_method_description/)**

|                | Name           |
| -------------- | -------------- |
| std::wstring | **[m_Description](/doxygen/Classes/class_inf_1_1_i_method_description/#variable-m-description)**  |


## Detailed Description

```cpp
template <typename Cls ,
typename Ret ,
typename... Args>
class Inf::MethodDescription;
```


This is the derived class, it needs to be Templated to be able to store the Function Pointer. 

## Public Functions Documentation

### function MethodDescription

```cpp
template <typename... ArgNames>
inline MethodDescription(
    std::wstring pc_class_name,
    std::wstring pb_method_name,
    Ret(Cls::*)(Args...) method,
    ArgNames... arg_names
)
```


**Parameters**: 

  * **pc_class_name** The name of the already registerd Class 
  * **pb_method_name** The Name that PowerBuilder will use 
  * **method** The Function Pointer 
  * **...arg_names** The Names of the arguments 


This will craete the Description and register itself to the [ClassDescription](/doxygen/Classes/class_inf_1_1_class_description/).


### function Invoke

```cpp
inline virtual PBXRESULT Invoke(
    PBNI_Class * object,
    IPB_Session * session,
    PBCallInfo * ci
) override
```


**Parameters**: 

  * **object** Will be used as this 
  * **session** Current session 
  * **ci** Arguments for Method and returned Value 


**Exceptions**: 

  * **[Inf::PBNI_IncorrectArgumentsException](/doxygen/Classes/class_inf_1_1_p_b_n_i___incorrect_arguments_exception/)** If the wrong Arguments were provided 
  * **[Inf::PBNI_PowerBuilderException](/doxygen/Classes/class_inf_1_1_p_b_n_i___power_builder_exception/)** If a PowerBuilder function didnt return PBX_SUCCESS 


**Return**: PBX_SUCCESS, always

**Reimplements**: [Inf::IMethodDescription::Invoke](/doxygen/Classes/class_inf_1_1_i_method_description/#function-invoke)


This is the method called by [PBNI_Class::Invoke](/doxygen/Classes/class_inf_1_1_p_b_n_i___class/#function-invoke). Calls the Class Method. This will check whether the Argument Types are correct, gather the Arguments, call the Method, set References and ReturnValue


-------------------------------

Updated on 2022-08-25 at 16:29:23 +0200