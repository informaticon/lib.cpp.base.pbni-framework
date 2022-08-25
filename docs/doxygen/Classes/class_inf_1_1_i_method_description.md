---
title: Inf::IMethodDescription

---

# Inf::IMethodDescription



 [More...](#detailed-description)


`#include <MethodDescription.h>`

Inherited by [Inf::MethodDescription< Cls, Ret, Args >](/doxygen/Classes/class_inf_1_1_method_description/)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| virtual PBXRESULT | **[Invoke](/doxygen/Classes/class_inf_1_1_i_method_description/#function-invoke)**([PBNI_Class](/doxygen/Classes/class_inf_1_1_p_b_n_i___class/) * object, IPB_Session * session, PBCallInfo * ci) =0 |
| std::wstring | **[GetDescription](/doxygen/Classes/class_inf_1_1_i_method_description/#function-getdescription)**() |

## Protected Functions

|                | Name           |
| -------------- | -------------- |
| template <typename Arg \> <br>void | **[SetReference](/doxygen/Classes/class_inf_1_1_i_method_description/#function-setreference)**(IPB_Session * session, IPB_Value * value, const Arg & arg) |

## Protected Attributes

|                | Name           |
| -------------- | -------------- |
| std::wstring | **[m_Description](/doxygen/Classes/class_inf_1_1_i_method_description/#variable-m-description)**  |

## Detailed Description

```cpp
class Inf::IMethodDescription;
```


This Class is there to be extended from, so that different [MethodDescription](/doxygen/Classes/class_inf_1_1_method_description/) Templates can all be put in one [Type](/doxygen/Classes/struct_inf_1_1_type/). 

## Public Functions Documentation

### function Invoke

```cpp
virtual PBXRESULT Invoke(
    PBNI_Class * object,
    IPB_Session * session,
    PBCallInfo * ci
) =0
```


**Parameters**: 

  * **object** Will be used as this 
  * **session** Current session 
  * **ci** Arguments for Method and returned Value 


**Exceptions**: 

  * **[Inf::PBNI_IncorrectArgumentsException](/doxygen/Classes/class_inf_1_1_p_b_n_i___incorrect_arguments_exception/)** If the wrong Arguments were provided 
  * **[Inf::PBNI_PowerBuilderException](/doxygen/Classes/class_inf_1_1_p_b_n_i___power_builder_exception/)** If a PowerBuilder function didnt return PBX_SUCCESS 


**Return**: PBX_SUCCESS, always

**Reimplemented by**: [Inf::MethodDescription::Invoke](/doxygen/Classes/class_inf_1_1_method_description/#function-invoke)


This is the method called by [PBNI_Class::Invoke](/doxygen/Classes/class_inf_1_1_p_b_n_i___class/#function-invoke). Calls the Class Method. This will check whether the Argument Types are correct, gather the Arguments, call the Method, set References and ReturnValue


### function GetDescription

```cpp
inline std::wstring GetDescription()
```


**Return**: Description 

Returns the definition, that was built during constructing.


## Protected Functions Documentation

### function SetReference

```cpp
template <typename Arg >
static inline void SetReference(
    IPB_Session * session,
    IPB_Value * value,
    const Arg & arg
)
```


**Parameters**: 

  * **session** Current Session 
  * **value** The Value to set the reference of 
  * **arg** The [reference] argument


**Template Parameters**: 

  * **The** type of the [ref] argument 


This Function is there so parameter unpacking can be done with a tuple, it just calls SetValue if Arg is a reference.


## Protected Attributes Documentation

### variable m_Description

```cpp
std::wstring m_Description;
```


-------------------------------

Updated on 2022-08-25 at 16:29:23 +0200