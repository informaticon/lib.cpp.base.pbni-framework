---
title: Inf::PBNI_NullPointerException

---

# Inf::PBNI_NullPointerException



 [More...](#detailed-description)


`#include <Errors.h>`

Inherits from [Inf::PBNI_Exception](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/), std::exception

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/#function-pbni-nullpointerexception)**(std::wstring type) |

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

Updated on 2022-08-25 at 16:29:24 +0200