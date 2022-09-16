---
title: Inf::PBNI_PowerBuilderException

---

# Inf::PBNI_PowerBuilderException



 [More...](#detailed-description)


`#include <Errors.h>`

Inherits from [Inf::PBNI_Exception](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md), std::exception

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBNI_PowerBuilderException](/docs/doxygen/Classes/classInf_1_1PBNI__PowerBuilderException.md#function-pbni-powerbuilderexception)**(std::wstring method_name, PBXRESULT res) |

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
class Inf::PBNI_PowerBuilderException;
```


This exception gets thrown if any PBNI Function that gets called doesn't return PBX_SUCCESS. 

## Public Functions Documentation

### function PBNI_PowerBuilderException

```cpp
inline PBNI_PowerBuilderException(
    std::wstring method_name,
    PBXRESULT res
)
```


-------------------------------

Updated on 2022-09-16 at 11:32:54 +0200