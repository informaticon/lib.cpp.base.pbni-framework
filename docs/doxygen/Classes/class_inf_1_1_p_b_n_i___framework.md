---
title: Inf::PBNI_Framework

---

# Inf::PBNI_Framework



 [More...](#detailed-description)


`#include <Framework.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| [PBNI_Class](/doxygen/Classes/class_inf_1_1_p_b_n_i___class/) * | **[CreateClass](/doxygen/Classes/class_inf_1_1_p_b_n_i___framework/#function-createclass)**(std::wstring pb_class_name, IPB_Session * session, pbobject pbobj) |
| const std::wstring & | **[GetDescription](/doxygen/Classes/class_inf_1_1_p_b_n_i___framework/#function-getdescription)**() |
| [IMethodDescription](/doxygen/Classes/class_inf_1_1_i_method_description/) * | **[GetClassMethod](/doxygen/Classes/class_inf_1_1_p_b_n_i___framework/#function-getclassmethod)**(std::wstring pb_class_name, pbmethodID method_id) |
| | **[PBNI_Framework](/doxygen/Classes/class_inf_1_1_p_b_n_i___framework/#function-pbni-framework)**([PBNI_Framework](/doxygen/Classes/class_inf_1_1_p_b_n_i___framework/) const & ) =delete |
| void | **[operator=](/doxygen/Classes/class_inf_1_1_p_b_n_i___framework/#function-operator=)**([PBNI_Framework](/doxygen/Classes/class_inf_1_1_p_b_n_i___framework/) const & ) =delete |
| [PBNI_Framework](/doxygen/Classes/class_inf_1_1_p_b_n_i___framework/) & | **[GetInstance](/doxygen/Classes/class_inf_1_1_p_b_n_i___framework/#function-getinstance)**() |

## Friends

|                | Name           |
| -------------- | -------------- |
| class | **[ClassDescription](/doxygen/Classes/class_inf_1_1_p_b_n_i___framework/#friend-classdescription)**  |
| class | **[MethodDescription](/doxygen/Classes/class_inf_1_1_p_b_n_i___framework/#friend-methoddescription)**  |

## Detailed Description

```cpp
class Inf::PBNI_Framework;
```


This is a Singleton class, whose purpose is holding and creating/invoking all Class and Method Descriptions. 

## Public Functions Documentation

### function CreateClass

```cpp
PBNI_Class * CreateClass(
    std::wstring pb_class_name,
    IPB_Session * session,
    pbobject pbobj
)
```


**Parameters**: 

  * **pb_class_name** Name of the Class in PowerBuilder 
  * **session** Current session 
  * **pbobj** The PowerBuilder reference to the to be created Object 


**Return**: The Created Class or nullptr, if no class was found 

This method is just called from dllmain.cpp::PBX_CreateNonVisualObject. It tries to find the Class from the Class name and create a new Object.


### function GetDescription

```cpp
const std::wstring & GetDescription()
```


**Return**: The Description as Unicode 

This method is just there to be called from dllmain.cpp::PBX_GetDescription. It loops through the registered Classes and gathers all Method Descriptions, then returns the entire thing.


### function GetClassMethod

```cpp
IMethodDescription * GetClassMethod(
    std::wstring pb_class_name,
    pbmethodID method_id
)
```


**Parameters**: 

  * **pb_class_name** The Name of PowerBuilder Class 
  * **method_id** The ID of the Method, in order of registration 


**Return**: A pointer to the Method's Description 

This method is just used in [PBNI_Class::Invoke](/doxygen/Classes/class_inf_1_1_p_b_n_i___class/#function-invoke). It tries to find the invoked method.


### function PBNI_Framework

```cpp
PBNI_Framework(
    PBNI_Framework const & 
) =delete
```


### function operator=

```cpp
void operator=(
    PBNI_Framework const & 
) =delete
```


### function GetInstance

```cpp
static inline PBNI_Framework & GetInstance()
```


**Return**: 

Static function to get the singleton instance of [PBNI_Framework](/doxygen/Classes/class_inf_1_1_p_b_n_i___framework/).


## Friends

### friend ClassDescription

```cpp
friend class ClassDescription(
    ClassDescription 
);
```


### friend MethodDescription

```cpp
friend class MethodDescription(
    MethodDescription 
);
```


-------------------------------

Updated on 2022-08-25 at 16:29:24 +0200