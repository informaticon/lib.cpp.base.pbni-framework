---
title: Inf::PBObject

---

# Inf::PBObject



 [More...](#detailed-description)


`#include <PBObjects.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBObject](/doxygen/Classes/class_inf_1_1_p_b_object/#function-pbobject)**(IPB_Session * session, pbobject obj) |
| | **[PBObject](/doxygen/Classes/class_inf_1_1_p_b_object/#function-pbobject)**(IPB_Session * session) |
| template <Helper::FixedString other_class_id,pbgroup_type other_group_type\> <br>| **[PBObject](/doxygen/Classes/class_inf_1_1_p_b_object/#function-pbobject)**(const [PBObject](/doxygen/Classes/class_inf_1_1_p_b_object/)< other_class_id, other_group_type > & other) |
| template <typename Ret  =void,typename... Args\> <br>Ret | **[Invoke](/doxygen/Classes/class_inf_1_1_p_b_object/#function-invoke)**(const std::wstring & method_name, PBRoutineType pbrt, Args... args) |
| template <typename Ret  =void,typename... Args\> <br>Ret | **[InvokeSig](/doxygen/Classes/class_inf_1_1_p_b_object/#function-invokesig)**(const std::wstring & method_name, PBRoutineType pbrt, const std::wstring & pbsig, Args &&... args) |
| template <typename Field \> <br>void | **[SetField](/doxygen/Classes/class_inf_1_1_p_b_object/#function-setfield)**(const std::wstring & field_name, const Field value) |
| template <typename Field \> <br>Field | **[GetField](/doxygen/Classes/class_inf_1_1_p_b_object/#function-getfield)**(const std::wstring & field_name) const |
| bool | **[IsNull](/doxygen/Classes/class_inf_1_1_p_b_object/#function-isnull)**() const |
| | **[operator pbobject](/doxygen/Classes/class_inf_1_1_p_b_object/#function-operator-pbobject)**() const |
| const std::wstring & | **[GroupName](/doxygen/Classes/class_inf_1_1_p_b_object/#function-groupname)**() |
| const std::wstring & | **[ClassName](/doxygen/Classes/class_inf_1_1_p_b_object/#function-classname)**() |
| pbclass | **[PBClass](/doxygen/Classes/class_inf_1_1_p_b_object/#function-pbclass)**(IPB_Session * session) |

## Friends

|                | Name           |
| -------------- | -------------- |
| struct | **[Type](/doxygen/Classes/class_inf_1_1_p_b_object/#friend-type)**  |
| class | **[PBArray](/doxygen/Classes/class_inf_1_1_p_b_object/#friend-pbarray)**  |
| class | **[PBObject](/doxygen/Classes/class_inf_1_1_p_b_object/#friend-pbobject)**  |

## Detailed Description

```cpp
template <Helper::FixedString class_id,
pbgroup_type group_type =pbgroup_userobject>
class Inf::PBObject;
```


**Template Parameters**: 

  * **class_id** ID of Group and Class 
  * **group_type** The Group [Type](/doxygen/Classes/struct_inf_1_1_type/) used by PowerBuilder (struct, userobject, ...) 


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

  * **[Inf::PBNI_Exception](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/)** If the Group or Class cannot be found 


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


### function Invoke

```cpp
template <typename Ret  =void,
typename... Args>
inline Ret Invoke(
    const std::wstring & method_name,
    PBRoutineType pbrt,
    Args... args
)
```


**Parameters**: 

  * **method_name** The name of the Function to invoke 
  * **pbrt** The [Type](/doxygen/Classes/struct_inf_1_1_type/) of the Function (Function or Event) 
  * **...args** The Arguments to forward to the Function 


**Exceptions**: 

  * **[Inf::PBNI_InvalidFieldException](/doxygen/Classes/class_inf_1_1_p_b_n_i___invalid_field_exception/)** If no matching functions were found 
  * **[Inf::PBNI_IncorrectArgumentsException](/doxygen/Classes/class_inf_1_1_p_b_n_i___incorrect_arguments_exception/)** If the argument types dont match up 
  * **[Inf::PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)** If pbobject is Null 
  * **[Inf::PBNI_PowerBuilderException](/doxygen/Classes/class_inf_1_1_p_b_n_i___power_builder_exception/)** If the function doesnt return PBX_SUCCESS 
  * **[Inf::PBNI_Exception](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/)** If the Group or Class cannot be found 


**Template Parameters**: 

  * **Ret** The type to be returned


**Return**: The acquired Value returned by the Function

Invoke a Function of the pbobject with an unknown Signature. Generates a signature out of the provided Return and Argument Types.


### function InvokeSig

```cpp
template <typename Ret  =void,
typename... Args>
inline Ret InvokeSig(
    const std::wstring & method_name,
    PBRoutineType pbrt,
    const std::wstring & pbsig,
    Args &&... args
)
```


**Parameters**: 

  * **method_name** The name of the Function to invoke 
  * **pbrt** The [Type](/doxygen/Classes/struct_inf_1_1_type/) of the Function (Function or Event) 
  * **pbsig** The Signature of the Function (pbsig170), L"" to pick first found 
  * **...args** The Arguments to forward to the Function 


**Exceptions**: 

  * **[Inf::PBNI_InvalidFieldException](/doxygen/Classes/class_inf_1_1_p_b_n_i___invalid_field_exception/)** If no matching functions were found 
  * **[Inf::PBNI_IncorrectArgumentsException](/doxygen/Classes/class_inf_1_1_p_b_n_i___incorrect_arguments_exception/)** If the argument types dont match up 
  * **[Inf::PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)** If pbobject is Null 
  * **[Inf::PBNI_PowerBuilderException](/doxygen/Classes/class_inf_1_1_p_b_n_i___power_builder_exception/)** If the function doesnt return PBX_SUCCESS 
  * **[Inf::PBNI_Exception](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/)** If the Group or Class cannot be found 


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

  * **[Inf::PBNI_InvalidFieldException](/doxygen/Classes/class_inf_1_1_p_b_n_i___invalid_field_exception/)** If no matching field was found 
  * **[Inf::PBNI_IncorrectArgumentsException](/doxygen/Classes/class_inf_1_1_p_b_n_i___incorrect_arguments_exception/)** If the argument types dont match up 
  * **[Inf::PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)** If pbobject is Null 
  * **[Inf::PBNI_PowerBuilderException](/doxygen/Classes/class_inf_1_1_p_b_n_i___power_builder_exception/)** If SetField doesn't return PBX_SUCCESS 
  * **[Inf::PBNI_Exception](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/)** If the Group or Class cannot be found 


**Template Parameters**: 

  * **Field** The [Type](/doxygen/Classes/struct_inf_1_1_type/) of the field to be set


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

  * **[Inf::PBNI_InvalidFieldException](/doxygen/Classes/class_inf_1_1_p_b_n_i___invalid_field_exception/)** If no matching field was found 
  * **[Inf::PBNI_IncorrectArgumentsException](/doxygen/Classes/class_inf_1_1_p_b_n_i___incorrect_arguments_exception/)** If the argument types dont match up 
  * **[Inf::PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)** If pbobject is Null 
  * **[Inf::PBNI_Exception](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/)** If the Group or Class cannot be found 


**Template Parameters**: 

  * **Field** The [Type](/doxygen/Classes/struct_inf_1_1_type/) to be returned


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

  * **[Inf::PBNI_Exception](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/)** If the Group or Class cannot be found 


**Return**: pbclass

Get the pbclass extracted from the class_id.


## Friends

### friend Type

```cpp
friend struct Type(
    Type 
);
```


### friend PBArray

```cpp
friend class PBArray(
    PBArray 
);
```


### friend PBObject

```cpp
friend class PBObject(
    PBObject 
);
```


-------------------------------

Updated on 2022-08-25 at 16:29:24 +0200