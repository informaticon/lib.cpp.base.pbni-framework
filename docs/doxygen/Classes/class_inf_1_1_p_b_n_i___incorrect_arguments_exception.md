---
title: Inf::PBNI_IncorrectArgumentsException

---

# Inf::PBNI_IncorrectArgumentsException



 [More...](#detailed-description)


`#include <Errors.h>`

Inherits from [Inf::PBNI_Exception](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/), std::exception

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBNI_IncorrectArgumentsException](/doxygen/Classes/class_inf_1_1_p_b_n_i___incorrect_arguments_exception/#function-pbni-incorrectargumentsexception)**(std::wstring class_name, std::wstring method_name) |
| | **[PBNI_IncorrectArgumentsException](/doxygen/Classes/class_inf_1_1_p_b_n_i___incorrect_arguments_exception/#function-pbni-incorrectargumentsexception)**(std::wstring class_name, std::wstring method_name, pbint argument_number) |

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

Updated on 2022-08-25 at 16:29:24 +0200