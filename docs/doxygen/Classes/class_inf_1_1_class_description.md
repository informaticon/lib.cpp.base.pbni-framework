---
title: Inf::ClassDescription

---

# Inf::ClassDescription



 [More...](#detailed-description)


`#include <ClassDescription.h>`

Inherits from [Inf::IClassDescription](/doxygen/Classes/class_inf_1_1_i_class_description/)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[ClassDescription](/doxygen/Classes/class_inf_1_1_class_description/#function-classdescription)**(std::wstring pb_name) |
| virtual [PBNI_Class](/doxygen/Classes/class_inf_1_1_p_b_n_i___class/) * | **[Create](/doxygen/Classes/class_inf_1_1_class_description/#function-create)**(IPB_Session * session, pbobject pbobj, std::wstring pb_class_name) const override |

## Additional inherited members

**Public Functions inherited from [Inf::IClassDescription](/doxygen/Classes/class_inf_1_1_i_class_description/)**

|                | Name           |
| -------------- | -------------- |
| [IMethodDescription](/doxygen/Classes/class_inf_1_1_i_method_description/) * | **[GetMethod](/doxygen/Classes/class_inf_1_1_i_class_description/#function-getmethod)**(pbmethodID method_id) const |
| std::wstring | **[GetDescription](/doxygen/Classes/class_inf_1_1_i_class_description/#function-getdescription)**() const |

**Protected Functions inherited from [Inf::IClassDescription](/doxygen/Classes/class_inf_1_1_i_class_description/)**

|                | Name           |
| -------------- | -------------- |
| void | **[AddMethod](/doxygen/Classes/class_inf_1_1_i_class_description/#function-addmethod)**([IMethodDescription](/doxygen/Classes/class_inf_1_1_i_method_description/) * method_description) |

**Protected Attributes inherited from [Inf::IClassDescription](/doxygen/Classes/class_inf_1_1_i_class_description/)**

|                | Name           |
| -------------- | -------------- |
| friend | **[PBNI_Framework](/doxygen/Classes/class_inf_1_1_i_class_description/#variable-pbni-framework)**  |
| std::wstring | **[m_PBName](/doxygen/Classes/class_inf_1_1_i_class_description/#variable-m-pbname)**  |
| std::vector< [IMethodDescription](/doxygen/Classes/class_inf_1_1_i_method_description/) * > | **[m_Methods](/doxygen/Classes/class_inf_1_1_i_class_description/#variable-m-methods)**  |


## Detailed Description

```cpp
template <typename Cls >
class Inf::ClassDescription;
```


This is the derived class, this only needs to be a Template to store the [Type](/doxygen/Classes/struct_inf_1_1_type/) of the Class and be able to create a new Object. 

## Public Functions Documentation

### function ClassDescription

```cpp
inline ClassDescription(
    std::wstring pb_name
)
```


**Parameters**: 

  * **pb_name** 


This Constructor automatically registers to [PBNI_Framework](/doxygen/Classes/class_inf_1_1_p_b_n_i___framework/).


### function Create

```cpp
inline virtual PBNI_Class * Create(
    IPB_Session * session,
    pbobject pbobj,
    std::wstring pb_class_name
) const override
```


**Parameters**: 

  * **session** Current session 
  * **pbobj** The PowerBuilder object representing this 
  * **pb_class_name** The name of the class used by PowerBuilder 


**Return**: Created object, cast to PBNI_Class* 

**Reimplements**: [Inf::IClassDescription::Create](/doxygen/Classes/class_inf_1_1_i_class_description/#function-create)


This Method creates a new Object of its [Type](/doxygen/Classes/struct_inf_1_1_type/) on the Heap and returns a Pointer to it.


-------------------------------

Updated on 2022-08-25 at 16:29:23 +0200