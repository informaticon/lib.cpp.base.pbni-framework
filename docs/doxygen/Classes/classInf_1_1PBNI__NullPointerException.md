---
title: Inf::PBNI_NullPointerException

---

# Inf::PBNI_NullPointerException



 [More...](#detailed-description)


`#include <Errors.h>`

Inherits from [Inf::PBNI_Exception](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md), std::exception

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBNI_NullPointerException](/docs/doxygen/Classes/classInf_1_1PBNI__NullPointerException.md#function-pbni-nullpointerexception)**(std::wstring type) |

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
class Inf::PBNI_NullPointerException;
```


This Exception can be thrown anywhere, because all PowerBuilder types can be null, always check using IsNull. 

## Public Functions Documentation

### function PBNI_NullPointerException

```cpp
inline PBNI_NullPointerException(
    std::wstring type
)
```


-------------------------------

Updated on 2022-09-15 at 20:34:45 +0200