---
title: Inf::PBNI_PowerBuilderException

---

# Inf::PBNI_PowerBuilderException



 [More...](#detailed-description)


`#include <Errors.h>`

Inherits from [Inf::PBNI_Exception](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/), std::exception

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBNI_PowerBuilderException](/doxygen/Classes/class_inf_1_1_p_b_n_i___power_builder_exception/#function-pbni-powerbuilderexception)**(std::wstring method_name, PBXRESULT res) |

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

Updated on 2022-08-25 at 16:29:24 +0200