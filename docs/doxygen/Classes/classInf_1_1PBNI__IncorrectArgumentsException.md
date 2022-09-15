---
title: Inf::PBNI_IncorrectArgumentsException

---

# Inf::PBNI_IncorrectArgumentsException



 [More...](#detailed-description)


`#include <Errors.h>`

Inherits from [Inf::PBNI_Exception](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md), std::exception

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBNI_IncorrectArgumentsException](/docs/doxygen/Classes/classInf_1_1PBNI__IncorrectArgumentsException.md#function-pbni-incorrectargumentsexception)**(std::wstring class_name, std::wstring method_name) |
| | **[PBNI_IncorrectArgumentsException](/docs/doxygen/Classes/classInf_1_1PBNI__IncorrectArgumentsException.md#function-pbni-incorrectargumentsexception)**(std::wstring class_name, std::wstring method_name, pbint argument_number) |

## Additional inherited members

**Public Functions inherited from [Inf::PBNI_Exception](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md)**

|                | Name           |
| -------------- | -------------- |
| | **[PBNI_Exception](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md#function-pbni-exception)**(std::wstring err_msg) |
| | **[PBNI_Exception](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md#function-pbni-exception)**(std::map< std::wstring, std::wstring > key_values) |
| virtual const char * | **[what](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md#function-what)**() const override |
| virtual const std::map< std::wstring, std::wstring > & | **[GetKeyValues](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md#function-getkeyvalues)**() const |
| virtual void | **[Push](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md#function-push)**(std::wstring key, std::wstring value) |


## Detailed Description

```cpp
class Inf::PBNI_IncorrectArgumentsException;
```


This exception gets thrown, when PowerBuilder invokes a function inside the Framework, but it doesnt give the right Arguments. Or when you try to Invoke a PowerBuilder function and dont give the right Arguments. 

## Public Functions Documentation

### function PBNI_IncorrectArgumentsException

```cpp
inline PBNI_IncorrectArgumentsException(
    std::wstring class_name,
    std::wstring method_name
)
```


### function PBNI_IncorrectArgumentsException

```cpp
inline PBNI_IncorrectArgumentsException(
    std::wstring class_name,
    std::wstring method_name,
    pbint argument_number
)
```


-------------------------------

Updated on 2022-09-15 at 20:34:45 +0200