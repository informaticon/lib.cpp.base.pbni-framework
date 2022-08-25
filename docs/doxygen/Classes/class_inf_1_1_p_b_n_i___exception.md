---
title: Inf::PBNI_Exception

---

# Inf::PBNI_Exception



 [More...](#detailed-description)


`#include <Errors.h>`

Inherits from std::exception

Inherited by [Inf::PBNI_IncorrectArgumentsException](/doxygen/Classes/class_inf_1_1_p_b_n_i___incorrect_arguments_exception/), [Inf::PBNI_IndexOutOfBoundsException](/doxygen/Classes/class_inf_1_1_p_b_n_i___index_out_of_bounds_exception/), [Inf::PBNI_InvalidFieldException](/doxygen/Classes/class_inf_1_1_p_b_n_i___invalid_field_exception/), [Inf::PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/), [Inf::PBNI_PowerBuilderException](/doxygen/Classes/class_inf_1_1_p_b_n_i___power_builder_exception/)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBNI_Exception](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/#function-pbni-exception)**(std::wstring err_msg) |
| | **[PBNI_Exception](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/#function-pbni-exception)**(std::map< std::wstring, std::wstring > key_values) |
| virtual const char * | **[what](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/#function-what)**() const override |
| virtual const std::map< std::wstring, std::wstring > & | **[GetKeyValues](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/#function-getkeyvalues)**() const |
| virtual void | **[Push](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/#function-push)**(std::wstring key, std::wstring value) |

## Detailed Description

```cpp
class Inf::PBNI_Exception;
```


Use this class to throw Verbose Exceptions that can be handled by PowerBuilder. This class automatically generates a StackTrace. 

## Public Functions Documentation

### function PBNI_Exception

```cpp
inline PBNI_Exception(
    std::wstring err_msg
)
```


### function PBNI_Exception

```cpp
inline PBNI_Exception(
    std::map< std::wstring, std::wstring > key_values
)
```


### function what

```cpp
inline virtual const char * what() const override
```


**Return**: The First error 

This method is just there so the exception is compatible with std::exception.


### function GetKeyValues

```cpp
inline virtual const std::map< std::wstring, std::wstring > & GetKeyValues() const
```


**Return**: KeyValues 

Method to retrieve the pushed KeyValues.


### function Push

```cpp
inline virtual void Push(
    std::wstring key,
    std::wstring value
)
```


**Parameters**: 

  * **key** Key To add 
  * **value** Value to add as key 


Push a KeyValue to an already existing error.


-------------------------------

Updated on 2022-08-25 at 16:29:24 +0200