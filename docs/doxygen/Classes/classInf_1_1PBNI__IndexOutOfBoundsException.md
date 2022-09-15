---
title: Inf::PBNI_IndexOutOfBoundsException

---

# Inf::PBNI_IndexOutOfBoundsException



 [More...](#detailed-description)


`#include <Errors.h>`

Inherits from [Inf::PBNI_Exception](/docs/doxygen/Classes/classInf_1_1PBNI__Exception.md), std::exception

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBNI_IndexOutOfBoundsException](/docs/doxygen/Classes/classInf_1_1PBNI__IndexOutOfBoundsException.md#function-pbni-indexoutofboundsexception)**(pblong pos, pblong size) |
| template <int N\> <br>| **[PBNI_IndexOutOfBoundsException](/docs/doxygen/Classes/classInf_1_1PBNI__IndexOutOfBoundsException.md#function-pbni-indexoutofboundsexception)**(std::array< pblong, N > pos, std::array< std::pair< pblong, pblong >, N > bounds, pbbyte dim) |

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
class Inf::PBNI_IndexOutOfBoundsException;
```


This Exception is thrown by PBArray when someone tried to access a value outside of the arrays bounds. 

## Public Functions Documentation

### function PBNI_IndexOutOfBoundsException

```cpp
inline PBNI_IndexOutOfBoundsException(
    pblong pos,
    pblong size
)
```


### function PBNI_IndexOutOfBoundsException

```cpp
template <int N>
inline PBNI_IndexOutOfBoundsException(
    std::array< pblong, N > pos,
    std::array< std::pair< pblong, pblong >, N > bounds,
    pbbyte dim
)
```


-------------------------------

Updated on 2022-09-15 at 20:34:45 +0200