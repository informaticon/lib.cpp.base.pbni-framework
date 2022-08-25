---
title: Inf::IClassDescription

---

# Inf::IClassDescription



 [More...](#detailed-description)


`#include <ClassDescription.h>`

Inherited by [Inf::ClassDescription< Cls >](/doxygen/Classes/class_inf_1_1_class_description/)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| virtual [PBNI_Class](/doxygen/Classes/class_inf_1_1_p_b_n_i___class/) * | **[Create](/doxygen/Classes/class_inf_1_1_i_class_description/#function-create)**(IPB_Session * session, pbobject pbobj, std::wstring pb_class_name) const =0 |
| [IMethodDescription](/doxygen/Classes/class_inf_1_1_i_method_description/) * | **[GetMethod](/doxygen/Classes/class_inf_1_1_i_class_description/#function-getmethod)**(pbmethodID method_id) const |
| std::wstring | **[GetDescription](/doxygen/Classes/class_inf_1_1_i_class_description/#function-getdescription)**() const |

## Protected Functions

|                | Name           |
| -------------- | -------------- |
| void | **[AddMethod](/doxygen/Classes/class_inf_1_1_i_class_description/#function-addmethod)**([IMethodDescription](/doxygen/Classes/class_inf_1_1_i_method_description/) * method_description) |

## Protected Attributes

|                | Name           |
| -------------- | -------------- |
| friend | **[PBNI_Framework](/doxygen/Classes/class_inf_1_1_i_class_description/#variable-pbni-framework)**  |
| std::wstring | **[m_PBName](/doxygen/Classes/class_inf_1_1_i_class_description/#variable-m-pbname)**  |
| std::vector< [IMethodDescription](/doxygen/Classes/class_inf_1_1_i_method_description/) * > | **[m_Methods](/doxygen/Classes/class_inf_1_1_i_class_description/#variable-m-methods)**  |

## Detailed Description

```cpp
class Inf::IClassDescription;
```


This Class is there to be extended from, so that different [ClassDescription](/doxygen/Classes/class_inf_1_1_class_description/) Templates can all be put in one [Type](/doxygen/Classes/struct_inf_1_1_type/). 

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

**Reimplemented by**: [Inf::ClassDescription::Create](/doxygen/Classes/class_inf_1_1_class_description/#function-create)


This Method creates a new Object of its [Type](/doxygen/Classes/struct_inf_1_1_type/) on the Heap and returns a Pointer to it.


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


This gets called by [PBNI_Framework](/doxygen/Classes/class_inf_1_1_p_b_n_i___framework/) when a function registers itself to it with the name of this class.


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

Updated on 2022-08-25 at 16:29:23 +0200