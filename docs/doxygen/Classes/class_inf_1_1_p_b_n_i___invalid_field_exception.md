---
title: Inf::PBNI_InvalidFieldException

---

# Inf::PBNI_InvalidFieldException



 [More...](#detailed-description)


`#include <Errors.h>`

Inherits from [Inf::PBNI_Exception](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/), std::exception

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBNI_InvalidFieldException](/doxygen/Classes/class_inf_1_1_p_b_n_i___invalid_field_exception/#function-pbni-invalidfieldexception)**(std::wstring type, std::wstring field, std::wstring field_type) |

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

Updated on 2022-08-25 at 16:29:24 +0200