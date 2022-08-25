---
title: Inf

---

# Inf



## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[Inf::ClassDescription](/doxygen/Classes/class_inf_1_1_class_description/)**  |
| class | **[Inf::IClassDescription](/doxygen/Classes/class_inf_1_1_i_class_description/)**  |
| class | **[Inf::IMethodDescription](/doxygen/Classes/class_inf_1_1_i_method_description/)**  |
| class | **[Inf::MethodDescription](/doxygen/Classes/class_inf_1_1_method_description/)**  |
| class | **[Inf::PBArray](/doxygen/Classes/class_inf_1_1_p_b_array/)**  |
| class | **[Inf::PBBlob](/doxygen/Classes/class_inf_1_1_p_b_blob/)**  |
| class | **[Inf::PBDate](/doxygen/Classes/class_inf_1_1_p_b_date/)**  |
| class | **[Inf::PBDateTime](/doxygen/Classes/class_inf_1_1_p_b_date_time/)**  |
| class | **[Inf::PBDecimal](/doxygen/Classes/class_inf_1_1_p_b_decimal/)**  |
| class | **[Inf::PBNI_Class](/doxygen/Classes/class_inf_1_1_p_b_n_i___class/)**  |
| class | **[Inf::PBNI_Exception](/doxygen/Classes/class_inf_1_1_p_b_n_i___exception/)**  |
| class | **[Inf::PBNI_Framework](/doxygen/Classes/class_inf_1_1_p_b_n_i___framework/)**  |
| class | **[Inf::PBNI_IncorrectArgumentsException](/doxygen/Classes/class_inf_1_1_p_b_n_i___incorrect_arguments_exception/)**  |
| class | **[Inf::PBNI_IndexOutOfBoundsException](/doxygen/Classes/class_inf_1_1_p_b_n_i___index_out_of_bounds_exception/)**  |
| class | **[Inf::PBNI_InvalidFieldException](/doxygen/Classes/class_inf_1_1_p_b_n_i___invalid_field_exception/)**  |
| class | **[Inf::PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)**  |
| class | **[Inf::PBNI_PowerBuilderException](/doxygen/Classes/class_inf_1_1_p_b_n_i___power_builder_exception/)**  |
| class | **[Inf::PBObject](/doxygen/Classes/class_inf_1_1_p_b_object/)**  |
| class | **[Inf::PBString](/doxygen/Classes/class_inf_1_1_p_b_string/)**  |
| class | **[Inf::PBTime](/doxygen/Classes/class_inf_1_1_p_b_time/)**  |
| struct | **[Inf::Type](/doxygen/Classes/struct_inf_1_1_type/)**  |

## Types

|                | Name           |
| -------------- | -------------- |
| using PBReal | **[PBFloat](/doxygen/Namespaces/namespace_inf/#using-pbfloat)**  |
| template <Helper::FixedString class_id\> <br>using [PBObject](/doxygen/Classes/class_inf_1_1_p_b_object/)< class_id, pbgroup_structure > | **[PBStruct](/doxygen/Namespaces/namespace_inf/#using-pbstruct)**  |
| template <Helper::FixedString class_id\> <br>using [PBObject](/doxygen/Classes/class_inf_1_1_p_b_object/)< class_id, pbgroup_window > | **[PBWindow](/doxygen/Namespaces/namespace_inf/#using-pbwindow)**  |
| template <Helper::FixedString class_id\> <br>using [PBObject](/doxygen/Classes/class_inf_1_1_p_b_object/)< class_id, pbgroup_datawindow > | **[PBDataWindow](/doxygen/Namespaces/namespace_inf/#using-pbdatawindow)**  |

## Functions

|                | Name           |
| -------------- | -------------- |
| template <typename ToStr ,typename... FromStr\> <br>ToStr | **[ConvertString](/doxygen/Namespaces/namespace_inf/#function-convertstring)**(FromStr... str) =delete |
| std::wstring | **[ConvertString](/doxygen/Namespaces/namespace_inf/#function-convertstring)**(const char * str, size_t size) |
| std::wstring | **[ConvertString](/doxygen/Namespaces/namespace_inf/#function-convertstring)**(const char * str) |
| std::wstring | **[ConvertString](/doxygen/Namespaces/namespace_inf/#function-convertstring)**(const std::string str) |
| std::string | **[ConvertString](/doxygen/Namespaces/namespace_inf/#function-convertstring)**(const wchar_t * wstr, size_t size) |
| std::string | **[ConvertString](/doxygen/Namespaces/namespace_inf/#function-convertstring)**(const wchar_t * wstr) |
| std::string | **[ConvertString](/doxygen/Namespaces/namespace_inf/#function-convertstring)**(const std::wstring wstr) |

## Types Documentation

### using PBFloat

```cpp
using Inf::PBFloat = typedef PBReal;
```


### using PBStruct

```cpp
template <Helper::FixedString class_id>
using Inf::PBStruct = typedef PBObject<class_id, pbgroup_structure>;
```


### using PBWindow

```cpp
template <Helper::FixedString class_id>
using Inf::PBWindow = typedef PBObject<class_id, pbgroup_window>;
```


### using PBDataWindow

```cpp
template <Helper::FixedString class_id>
using Inf::PBDataWindow = typedef PBObject<class_id, pbgroup_datawindow>;
```



## Functions Documentation

### function ConvertString

```cpp
template <typename ToStr ,
typename... FromStr>
ToStr ConvertString(
    FromStr... str
) =delete
```


**Template Parameters**: 

  * **ToStr** The [Type](/doxygen/Classes/struct_inf_1_1_type/) to be converted to 


These functions convert a String from Ansi to Unicode or back. They use Window's MultiByteToWideChar and WideCharToMultiByte functions (stringapiset.h)


### function ConvertString

```cpp
std::wstring ConvertString(
    const char * str,
    size_t size
)
```


### function ConvertString

```cpp
std::wstring ConvertString(
    const char * str
)
```


### function ConvertString

```cpp
std::wstring ConvertString(
    const std::string str
)
```


### function ConvertString

```cpp
std::string ConvertString(
    const wchar_t * wstr,
    size_t size
)
```


### function ConvertString

```cpp
std::string ConvertString(
    const wchar_t * wstr
)
```


### function ConvertString

```cpp
std::string ConvertString(
    const std::wstring wstr
)
```






-------------------------------

Updated on 2022-08-25 at 16:29:23 +0200