---
title: Inf::PBNI_InvalidFieldException

---

# Inf::PBNI_InvalidFieldException



 [More...](#detailed-description)


`#include <Errors.h>`

Inherits from [Inf::PBNI_Exception](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md), std::exception

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBNI_InvalidFieldException](/docs/doxygen/Classes/classInf_1_1PBNI__InvalidFieldException.md#function-pbni-invalidfieldexception)**(std::wstring type, std::wstring field, std::wstring field_type) |

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
class Inf::PBNI_InvalidFieldException;
```


This Exception gets thrown if you try to access a field of an Object, that doesn't exist. 

## Public Functions Documentation

### function PBNI_InvalidFieldException

```cpp
inline PBNI_InvalidFieldException(
    std::wstring type,
    std::wstring field,
    std::wstring field_type
)
```


-------------------------------

Updated on 2022-09-16 at 11:32:54 +0200