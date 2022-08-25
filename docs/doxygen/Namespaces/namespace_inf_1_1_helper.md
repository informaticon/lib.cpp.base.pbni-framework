---
title: Inf::Helper

---

# Inf::Helper



## Classes

|                | Name           |
| -------------- | -------------- |
| struct | **[Inf::Helper::AcquiredValue](/doxygen/Classes/struct_inf_1_1_helper_1_1_acquired_value/)**  |
| struct | **[Inf::Helper::FixedString](/doxygen/Classes/struct_inf_1_1_helper_1_1_fixed_string/)**  |
| struct | **[Inf::Helper::is_pb_array](/doxygen/Classes/struct_inf_1_1_helper_1_1is__pb__array/)**  |
| struct | **[Inf::Helper::is_pb_array< PBArray< Item, dims... > >](/doxygen/Classes/struct_inf_1_1_helper_1_1is__pb__array_3_01_p_b_array_3_01_item_00_01dims_8_8_8_01_4_01_4/)**  |
| struct | **[Inf::Helper::is_pb_object](/doxygen/Classes/struct_inf_1_1_helper_1_1is__pb__object/)**  |
| struct | **[Inf::Helper::is_pb_object< PBObject< class_id, group_type > >](/doxygen/Classes/struct_inf_1_1_helper_1_1is__pb__object_3_01_p_b_object_3_01class__id_00_01group__type_01_4_01_4/)**  |

## Types

|                | Name           |
| -------------- | -------------- |
| using boost::multiprecision::number< boost::multiprecision::cpp_dec_float< 8 > > | **[PBDecimalImpl](/doxygen/Namespaces/namespace_inf_1_1_helper/#using-pbdecimalimpl)**  |

## Attributes

|                | Name           |
| -------------- | -------------- |
| constexpr bool | **[is_pb_object_v](/doxygen/Namespaces/namespace_inf_1_1_helper/#variable-is-pb-object-v)**  |
| constexpr bool | **[is_pb_array_v](/doxygen/Namespaces/namespace_inf_1_1_helper/#variable-is-pb-array-v)**  |

## Types Documentation

### using PBDecimalImpl

```cpp
using Inf::Helper::PBDecimalImpl = typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<8> >;
```


Since decimals arent natively supported, we use boost. PowerBuilder decimals are 30 Digits max (excluding - and .) cpp_dec_float<8> has a precission of 32 digits. If the Number gets too big, it will set to 0. 




## Attributes Documentation

### variable is_pb_object_v

```cpp
constexpr bool is_pb_object_v = is_pb_object<T>::value;
```


### variable is_pb_array_v

```cpp
constexpr bool is_pb_array_v = is_pb_array<T>::value;
```





-------------------------------

Updated on 2022-08-25 at 16:08:57 +0200