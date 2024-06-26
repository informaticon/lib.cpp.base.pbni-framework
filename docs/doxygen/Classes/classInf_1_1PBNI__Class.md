---
title: Inf::PBNI_Class

---

# Inf::PBNI_Class



 [More...](#detailed-description)


`#include <Framework.h>`

Inherits from IPBX_NonVisualObject

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBNI_Class](/docs/doxygen/Classes/classInf_1_1PBNI__Class.md#function-pbni-class)**(IPB_Session * session, pbobject pbobj, std::wstring pb_class_name) |
| virtual | **[~PBNI_Class](/docs/doxygen/Classes/classInf_1_1PBNI__Class.md#function-~pbni-class)**() |
| void | **[Destroy](/docs/doxygen/Classes/classInf_1_1PBNI__Class.md#function-destroy)**() override |
| PBXRESULT | **[Invoke](/docs/doxygen/Classes/classInf_1_1PBNI__Class.md#function-invoke)**(IPB_Session * session, pbobject obj, pbmethodID mid, PBCallInfo * ci) override |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| const std::wstring | **[PB_NAME](/docs/doxygen/Classes/classInf_1_1PBNI__Class.md#variable-pb-name)**  |

## Protected Attributes

|                | Name           |
| -------------- | -------------- |
| IPB_Session * | **[m_Session](/docs/doxygen/Classes/classInf_1_1PBNI__Class.md#variable-m-session)**  |
| pbobject | **[m_PBObject](/docs/doxygen/Classes/classInf_1_1PBNI__Class.md#variable-m-pbobject)**  |

## Detailed Description

```cpp
class Inf::PBNI_Class;
```


[PBNI_Class](/docs/doxygen/Classes/classInf_1_1PBNI__Class.md) is the Base Class for all Classes that you want to be used inside PowerBuilder. You just need to extend this Class and override GetPBName(). 

## Public Functions Documentation

### function PBNI_Class

```cpp
PBNI_Class(
    IPB_Session * session,
    pbobject pbobj,
    std::wstring pb_class_name
)
```


**Parameters**: 

  * **session** Current Session 
  * **pbobj** The PowerBuilder object representing this 
  * **pb_class_name** The name of the class in powerbuilder 


### function ~PBNI_Class

```cpp
inline virtual ~PBNI_Class()
```


### function Destroy

```cpp
inline void Destroy() override
```


This Method will be called by PowerBuilder once it no longer needs this Object, don't use it. Put your cleanup Code inside the Destructor. 


### function Invoke

```cpp
PBXRESULT Invoke(
    IPB_Session * session,
    pbobject obj,
    pbmethodID mid,
    PBCallInfo * ci
) override
```


**Parameters**: 

  * **session** The PowerBuilder session that is used to get Arguments and create Objects 
  * **obj** This is the PowerBuilder reference to this 
  * **mid** This is the ID of the Method that gets called, it is in the Order of the Description 
  * **ci** These are the Arguments and return Value 


**Return**: Returns PBX_SUCCESS if the Method exists, otherwise PBX_E_INVALID_METHOD_ID 

This Method will be called when PowerBuilder wants to call a Method to this specific Object.


## Public Attributes Documentation

### variable PB_NAME

```cpp
const std::wstring PB_NAME;
```


## Protected Attributes Documentation

### variable m_Session

```cpp
IPB_Session * m_Session;
```


### variable m_PBObject

```cpp
pbobject m_PBObject;
```


-------------------------------

Updated on 2022-09-16 at 11:32:54 +0200