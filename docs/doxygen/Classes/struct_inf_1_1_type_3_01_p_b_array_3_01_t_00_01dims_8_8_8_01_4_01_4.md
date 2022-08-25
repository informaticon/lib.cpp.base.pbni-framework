---
title: Inf::Type< PBArray< T, dims... > >

---

# Inf::Type< PBArray< T, dims... > >



 [More...](#detailed-description)


`#include <PBTypes.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| bool | **[Assert](/doxygen/Classes/struct_inf_1_1_type_3_01_p_b_array_3_01_t_00_01dims_8_8_8_01_4_01_4/#function-assert)**(IPB_Session * session, IPB_Value * pb_value) |
| std::wstring | **[GetPBName](/doxygen/Classes/struct_inf_1_1_type_3_01_p_b_array_3_01_t_00_01dims_8_8_8_01_4_01_4/#function-getpbname)**(std::wstring argument_name) |
| [PBArray](/doxygen/Classes/class_inf_1_1_p_b_array/)< T, dims... > | **[FromArgument](/doxygen/Classes/struct_inf_1_1_type_3_01_p_b_array_3_01_t_00_01dims_8_8_8_01_4_01_4/#function-fromargument)**(IPB_Session * session, IPB_Value * pb_value, bool acquire) |
| PBXRESULT | **[SetValue](/doxygen/Classes/struct_inf_1_1_type_3_01_p_b_array_3_01_t_00_01dims_8_8_8_01_4_01_4/#function-setvalue)**(IPB_Session * session, IPB_Value * pb_value, const [PBArray](/doxygen/Classes/class_inf_1_1_p_b_array/)< T, dims... > & value) |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| std::wstring | **[PBSignature](/doxygen/Classes/struct_inf_1_1_type_3_01_p_b_array_3_01_t_00_01dims_8_8_8_01_4_01_4/#variable-pbsignature)**  |

## Detailed Description

```cpp
template <typename T ,
pblong... dims>
struct Inf::Type< PBArray< T, dims... > >;
```


For Types that have their own template types (PBObject<>, PBArray<>) we cant partially specialize the static Functions. Instead we have to create our own Struct, which can be partially specialized 

## Public Functions Documentation

### function Assert

```cpp
static inline bool Assert(
    IPB_Session * session,
    IPB_Value * pb_value
)
```


### function GetPBName

```cpp
static inline std::wstring GetPBName(
    std::wstring argument_name
)
```


### function FromArgument

```cpp
static inline PBArray< T, dims... > FromArgument(
    IPB_Session * session,
    IPB_Value * pb_value,
    bool acquire
)
```


### function SetValue

```cpp
static inline PBXRESULT SetValue(
    IPB_Session * session,
    IPB_Value * pb_value,
    const PBArray< T, dims... > & value
)
```


## Public Attributes Documentation

### variable PBSignature

```cpp
static std::wstring PBSignature = std::wstring(1, Type<T>::PBSignature) + L"[]";
```


-------------------------------

Updated on 2022-08-25 at 15:54:55 +0200