---
title: Inf::PBNI_Exception

---

# Inf::PBNI_Exception



 [More...](#detailed-description)


`#include <Errors.h>`

Inherits from std::exception

Inherited by [Inf::PBNI_IncorrectArgumentsException](/docs/doxygen/Classes/classInf_1_1PBNI__IncorrectArgumentsException.md), [Inf::PBNI_IndexOutOfBoundsException](/docs/doxygen/Classes/classInf_1_1PBNI__IndexOutOfBoundsException.md), [Inf::PBNI_InvalidFieldException](/docs/doxygen/Classes/classInf_1_1PBNI__InvalidFieldException.md), [Inf::PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md), [Inf::PBNI_PowerBuilderException](/docs/doxygen/Classes/classInf_1_1PBNI__PowerBuilderException.md)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBNI_Exception](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md#function-pbni-exception)**(std::wstring err_msg) |
| | **[PBNI_Exception](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md#function-pbni-exception)**(std::map< std::wstring, std::wstring > key_values) |
| virtual const char * | **[what](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md#function-what)**() const override |
| virtual const std::map< std::wstring, std::wstring > & | **[GetKeyValues](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md#function-getkeyvalues)**() const |
| virtual void | **[Push](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md#function-push)**(std::wstring key, std::wstring value) |

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

Updated on 2022-09-15 at 20:34:45 +0200