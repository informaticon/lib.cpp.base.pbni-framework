---
title: Inf::IClassDescription

---

# Inf::IClassDescription



 [More...](#detailed-description)


`#include <ClassDescription.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| virtual [PBNI_Class](/docs/doxygen/Classes/classInf_1_1PBNI__Class.md) * | **[Create](/docs/doxygen/Classes/classInf_1_1IClassDescription.md#function-create)**(IPB_Session * session, pbobject pbobj, std::wstring pb_class_name) const =0 |
| [IMethodDescription](/docs/doxygen/Classes/classInf_1_1IMethodDescription.md) * | **[GetMethod](/docs/doxygen/Classes/classInf_1_1IClassDescription.md#function-getmethod)**(pbmethodID method_id) const |
| std::wstring | **[GetDescription](/docs/doxygen/Classes/classInf_1_1IClassDescription.md#function-getdescription)**() const |

## Protected Functions

|                | Name           |
| -------------- | -------------- |
| void | **[AddMethod](/docs/doxygen/Classes/classInf_1_1IClassDescription.md#function-addmethod)**([IMethodDescription](/docs/doxygen/Classes/classInf_1_1IMethodDescription.md) * method_description) |

## Protected Attributes

|                | Name           |
| -------------- | -------------- |
| friend | **[PBNI_Framework](/docs/doxygen/Classes/classInf_1_1IClassDescription.md#variable-pbni-framework)**  |
| std::wstring | **[m_PBName](/docs/doxygen/Classes/classInf_1_1IClassDescription.md#variable-m-pbname)**  |
| std::vector< [IMethodDescription](/docs/doxygen/Classes/classInf_1_1IMethodDescription.md) * > | **[m_Methods](/docs/doxygen/Classes/classInf_1_1IClassDescription.md#variable-m-methods)**  |

## Detailed Description

```cpp
class Inf::IClassDescription;
```


This Class is there to be extended from, so that different ClassDescription Templates can all be put in one [Type](/docs/doxygen/Classes/structInf_1_1Type.md). 

## Public Functions Documentation

### function Create

```cpp
virtual PBNI_Class * Create(
    IPB_Session * session,
    pbobject pbobj,
    std::wstring pb_class_name
) const =0
```


**Parameters**: 

  * **session** Current session 
  * **pbobj** The PowerBuilder object representing this 
  * **pb_class_name** The name of the class used by PowerBuilder 


**Return**: Created object, cast to PBNI_Class* 

This Method creates a new Object of its [Type](/docs/doxygen/Classes/structInf_1_1Type.md) on the Heap and returns a Pointer to it.


### function GetMethod

```cpp
inline IMethodDescription * GetMethod(
    pbmethodID method_id
) const
```


**Parameters**: 

  * **method_id** The ID of the method 


**Return**: The Method 

This Method returns a Method of this Class.


### function GetDescription

```cpp
inline std::wstring GetDescription() const
```


**Return**: The Description 

This Method builds a Description out of itself and its Methods. It will always be a nonvisualobject.


## Protected Functions Documentation

### function AddMethod

```cpp
inline void AddMethod(
    IMethodDescription * method_description
)
```


**Parameters**: 

  * **method_description** The Description of the registered Method 


This gets called by [PBNI_Framework](/docs/doxygen/Classes/classInf_1_1PBNI__Framework.md) when a function registers itself to it with the name of this class.


## Protected Attributes Documentation

### variable PBNI_Framework

```cpp
friend PBNI_Framework;
```


### variable m_PBName

```cpp
std::wstring m_PBName;
```


### variable m_Methods

```cpp
std::vector< IMethodDescription * > m_Methods;
```


-------------------------------

Updated on 2022-09-15 at 20:34:45 +0200