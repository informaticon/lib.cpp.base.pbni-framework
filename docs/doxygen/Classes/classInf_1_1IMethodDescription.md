---
title: Inf::IMethodDescription

---

# Inf::IMethodDescription



 [More...](#detailed-description)


`#include <MethodDescription.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| virtual PBXRESULT | **[Invoke](/docs/doxygen/Classes/classInf_1_1IMethodDescription.md#function-invoke)**([PBNI_Class](/docs/doxygen/Classes/classInf_1_1PBNI__Class.md) * object, IPB_Session * session, PBCallInfo * ci) =0 |
| std::wstring | **[GetDescription](/docs/doxygen/Classes/classInf_1_1IMethodDescription.md#function-getdescription)**() |

## Protected Functions

|                | Name           |
| -------------- | -------------- |
| template <typename Arg \> <br>void | **[SetReference](/docs/doxygen/Classes/classInf_1_1IMethodDescription.md#function-setreference)**(IPB_Session * session, IPB_Value * value, const Arg & arg) |

## Protected Attributes

|                | Name           |
| -------------- | -------------- |
| std::wstring | **[m_Description](/docs/doxygen/Classes/classInf_1_1IMethodDescription.md#variable-m-description)**  |

## Detailed Description

```cpp
class Inf::IMethodDescription;
```


This Class is there to be extended from, so that different MethodDescription Templates can all be put in one [Type](/docs/doxygen/Classes/structInf_1_1Type.md). 

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

  * **[Inf::PBNI_IncorrectArgumentsException](/docs/doxygen/Classes/classInf_1_1PBNI__IncorrectArgumentsException.md)** If the wrong Arguments were provided 
  * **[Inf::PBNI_PowerBuilderException](/docs/doxygen/Classes/classInf_1_1PBNI__PowerBuilderException.md)** If a PowerBuilder function didnt return PBX_SUCCESS 


**Return**: PBX_SUCCESS, always

This is the method called by [PBNI_Class::Invoke](/docs/doxygen/Classes/classInf_1_1PBNI__Class.md#function-invoke). Calls the Class Method. This will check whether the Argument Types are correct, gather the Arguments, call the Method, set References and ReturnValue


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

Updated on 2022-09-16 at 11:32:55 +0200