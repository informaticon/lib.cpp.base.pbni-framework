---
title: Inf::PBObject

---

# Inf::PBObject



 [More...](#detailed-description)


`#include <PBObjects.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBObject](/docs/doxygen/Classes/classInf_1_1PBObject.md#function-pbobject)**(IPB_Session * session, pbobject obj) |
| | **[PBObject](/docs/doxygen/Classes/classInf_1_1PBObject.md#function-pbobject)**(IPB_Session * session) |
| template <Helper::FixedString other_class_id,pbgroup_type other_group_type\> <br>| **[PBObject](/docs/doxygen/Classes/classInf_1_1PBObject.md#function-pbobject)**(const [PBObject](/docs/doxygen/Classes/classInf_1_1PBObject.md)< other_class_id, other_group_type > & other) |
| template <typename Ret  =void,typename... Args\> <br>| **[requires](/docs/doxygen/Classes/classInf_1_1PBObject.md#function-requires)**(!std::is_pointer_v< Ret > &&!std::is_reference_v< Ret > && !std::is_pointer_v< Args > &&...) const |
| template <typename Ret  =void,typename... Args\> <br>| **[requires](/docs/doxygen/Classes/classInf_1_1PBObject.md#function-requires)**(!std::is_pointer_v< Ret > &&!std::is_reference_v< Ret > && !std::is_pointer_v< Args > &&...) const |
| template <typename Field \> <br>void | **[SetField](/docs/doxygen/Classes/classInf_1_1PBObject.md#function-setfield)**(const std::wstring & field_name, const Field value) |
| template <typename Field \> <br>Field | **[GetField](/docs/doxygen/Classes/classInf_1_1PBObject.md#function-getfield)**(const std::wstring & field_name) const |
| bool | **[IsNull](/docs/doxygen/Classes/classInf_1_1PBObject.md#function-isnull)**() const |
| | **[operator pbobject](/docs/doxygen/Classes/classInf_1_1PBObject.md#function-operator-pbobject)**() const |
| const std::wstring & | **[GroupName](/docs/doxygen/Classes/classInf_1_1PBObject.md#function-groupname)**() |
| const std::wstring & | **[ClassName](/docs/doxygen/Classes/classInf_1_1PBObject.md#function-classname)**() |
| pbclass | **[PBClass](/docs/doxygen/Classes/classInf_1_1PBObject.md#function-pbclass)**(IPB_Session * session) |

## Friends

|                | Name           |
| -------------- | -------------- |
| struct | **[Type](/docs/doxygen/Classes/classInf_1_1PBObject.md#friend-type)**  |
| class | **[PBObject](/docs/doxygen/Classes/classInf_1_1PBObject.md#friend-pbobject)**  |

## Detailed Description

```cpp
template <Helper::FixedString class_id,
pbgroup_type group_type =pbgroup_userobject>
class Inf::PBObject;
```


**Template Parameters**: 

  * **class_id** ID of Group and Class 
  * **group_type** The Group [Type](/docs/doxygen/Classes/structInf_1_1Type.md) used by PowerBuilder (struct, userobject, ...) 


Wrapper for pbobject type. If the Group and Classnames are the same (most of the times), the ID of the Class is just the Class name. If the Group and Class names are different, the ID is both combined with a dot (L"group.class"). This is only the case for nested Types.

## Public Functions Documentation

### function PBObject

```cpp
inline PBObject(
    IPB_Session * session,
    pbobject obj
)
```


**Parameters**: 

  * **session** Current Session 
  * **obj** pbobject or 0 


Creates a new Wrapper for an already existing object. Will be Null if obj is 0.


### function PBObject

```cpp
inline PBObject(
    IPB_Session * session
)
```


**Parameters**: 

  * **session** Current Session


**Exceptions**: 

  * **[Inf::PBNI_Exception](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md)** If the Group or Class cannot be found 


Will create a new object of the correct Class.


### function PBObject

```cpp
template <Helper::FixedString other_class_id,
pbgroup_type other_group_type>
inline PBObject(
    const PBObject< other_class_id, other_group_type > & other
)
```


**Parameters**: 

  * **other** Object to cast 


The ability to cast any Class to any other Class.


### function requires

```cpp
template <typename Ret  =void,
typename... Args>
inline requires(
    !std::is_pointer_v< Ret > &&!std::is_reference_v< Ret > && !std::is_pointer_v< Args > &&...
) const
```


**Parameters**: 

  * **method_name** The name of the Function to invoke 
  * **pbrt** The [Type](/docs/doxygen/Classes/structInf_1_1Type.md) of the Function (Function or Event) 
  * **...args** The Arguments to forward to the Function 


**Exceptions**: 

  * **[Inf::PBNI_InvalidFieldException](/docs/doxygen/Classes/classInf_1_1PBNI__InvalidFieldException.md)** If no matching functions were found 
  * **[Inf::PBNI_IncorrectArgumentsException](/docs/doxygen/Classes/classInf_1_1PBNI__IncorrectArgumentsException.md)** If the argument types dont match up 
  * **[Inf::PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)** If pbobject is Null 
  * **[Inf::PBNI_PowerBuilderException](/docs/doxygen/Classes/classInf_1_1PBNI__PowerBuilderException.md)** If the function doesnt return PBX_SUCCESS 
  * **[Inf::PBNI_Exception](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md)** If the Group or Class cannot be found 


**Template Parameters**: 

  * **Ret** The type to be returned


**Return**: The acquired Value returned by the Function

Invoke a Function of the pbobject with an unknown Signature. Generates a signature out of the provided Return and Argument Types.


### function requires

```cpp
template <typename Ret  =void,
typename... Args>
inline requires(
    !std::is_pointer_v< Ret > &&!std::is_reference_v< Ret > && !std::is_pointer_v< Args > &&...
) const
```


**Parameters**: 

  * **method_name** The name of the Function to invoke 
  * **pbrt** The [Type](/docs/doxygen/Classes/structInf_1_1Type.md) of the Function (Function or Event) 
  * **pbsig** The Signature of the Function (pbsig170), L"" to pick first found 
  * **...args** The Arguments to forward to the Function 


**Exceptions**: 

  * **[Inf::PBNI_InvalidFieldException](/docs/doxygen/Classes/classInf_1_1PBNI__InvalidFieldException.md)** If no matching functions were found 
  * **[Inf::PBNI_IncorrectArgumentsException](/docs/doxygen/Classes/classInf_1_1PBNI__IncorrectArgumentsException.md)** If the argument types dont match up 
  * **[Inf::PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)** If pbobject is Null 
  * **[Inf::PBNI_PowerBuilderException](/docs/doxygen/Classes/classInf_1_1PBNI__PowerBuilderException.md)** If the function doesnt return PBX_SUCCESS 
  * **[Inf::PBNI_Exception](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md)** If the Group or Class cannot be found 


**Template Parameters**: 

  * **Ret** The type to be returned


**Return**: The acquired Value returned by the Function

Invokes a Function of a pbobject with a known Signature.


### function SetField

```cpp
template <typename Field >
inline void SetField(
    const std::wstring & field_name,
    const Field value
)
```


**Parameters**: 

  * **field_name** The name of the PowerBuilder Field 
  * **t** The Value to set it to


**Exceptions**: 

  * **[Inf::PBNI_InvalidFieldException](/docs/doxygen/Classes/classInf_1_1PBNI__InvalidFieldException.md)** If no matching field was found 
  * **[Inf::PBNI_IncorrectArgumentsException](/docs/doxygen/Classes/classInf_1_1PBNI__IncorrectArgumentsException.md)** If the argument types dont match up 
  * **[Inf::PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)** If pbobject is Null 
  * **[Inf::PBNI_PowerBuilderException](/docs/doxygen/Classes/classInf_1_1PBNI__PowerBuilderException.md)** If SetField doesn't return PBX_SUCCESS 
  * **[Inf::PBNI_Exception](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md)** If the Group or Class cannot be found 


**Template Parameters**: 

  * **Field** The [Type](/docs/doxygen/Classes/structInf_1_1Type.md) of the field to be set


Sets a Field of the pbobjec to a Value.


### function GetField

```cpp
template <typename Field >
inline Field GetField(
    const std::wstring & field_name
) const
```


**Parameters**: 

  * **field_name** The name of the PowerBuilder Field


**Exceptions**: 

  * **[Inf::PBNI_InvalidFieldException](/docs/doxygen/Classes/classInf_1_1PBNI__InvalidFieldException.md)** If no matching field was found 
  * **[Inf::PBNI_IncorrectArgumentsException](/docs/doxygen/Classes/classInf_1_1PBNI__IncorrectArgumentsException.md)** If the argument types dont match up 
  * **[Inf::PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md)** If pbobject is Null 
  * **[Inf::PBNI_Exception](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md)** If the Group or Class cannot be found 


**Template Parameters**: 

  * **Field** The [Type](/docs/doxygen/Classes/structInf_1_1Type.md) to be returned


Gets a Field of the pbobject.


### function IsNull

```cpp
inline bool IsNull() const
```


**Return**: Is Null 

Wheteher the pbobject is Null.


### function operator pbobject

```cpp
inline operator pbobject() const
```


**Return**: The pbobject used for PowerBuilder functions 

This conversion operator is currently the only way of getting the pbobject out.


### function GroupName

```cpp
static inline const std::wstring & GroupName()
```


**Return**: Group name 

Get the Group name extracted from the class_id.


### function ClassName

```cpp
static inline const std::wstring & ClassName()
```


**Return**: Class name 

Get the Class name extracted from the class_id.


### function PBClass

```cpp
static inline pbclass PBClass(
    IPB_Session * session
)
```


**Exceptions**: 

  * **[Inf::PBNI_Exception](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md)** If the Group or Class cannot be found 


**Return**: pbclass

Get the pbclass extracted from the class_id.


## Friends

### friend Type

```cpp
friend struct Type(
    Type 
);
```


### friend PBObject

```cpp
friend class PBObject(
    PBObject 
);
```


-------------------------------

Updated on 2022-09-16 at 11:32:55 +0200