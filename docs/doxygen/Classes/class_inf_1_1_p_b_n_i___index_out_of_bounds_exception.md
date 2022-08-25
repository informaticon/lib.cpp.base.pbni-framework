---
title: Inf::PBNI_IndexOutOfBoundsException

---

# Inf::PBNI_IndexOutOfBoundsException



 [More...](#detailed-description)


`#include <Errors.h>`

Inherits from [Inf::PBNI_Exception](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/), std::exception

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBNI_IndexOutOfBoundsException](/doxygen/Classes/class_inf_1_1_p_b_n_i___index_out_of_bounds_exception/#function-pbni-indexoutofboundsexception)**(pblong pos, pblong size) |
| template <int N\> <br>| **[PBNI_IndexOutOfBoundsException](/doxygen/Classes/class_inf_1_1_p_b_n_i___index_out_of_bounds_exception/#function-pbni-indexoutofboundsexception)**(std::array< pblong, N > pos, std::array< std::pair< pblong, pblong >, N > bounds, pbbyte dim) |

## Additional inherited members

**Public Functions inherited from [Inf::PBNI_Exception](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/)**

|                | Name           |
| -------------- | -------------- |
| | **[PBNI_Exception](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/#function-pbni-exception)**(std::wstring err_msg) |
| | **[PBNI_Exception](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/#function-pbni-exception)**(std::map< std::wstring, std::wstring > key_values) |
| virtual const char * | **[what](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/#function-what)**() const override |
| virtual const std::map< std::wstring, std::wstring > & | **[GetKeyValues](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/#function-getkeyvalues)**() const |
| virtual void | **[Push](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/#function-push)**(std::wstring key, std::wstring value) |


## Detailed Description

```cpp
class Inf::PBNI_IndexOutOfBoundsException;
```


This Exception is thrown by [PBArray](/doxygen/Classes/class_inf_1_1_p_b_array/) when someone tried to access a value outside of the arrays bounds. 

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

Updated on 2022-08-25 at 16:29:24 +0200