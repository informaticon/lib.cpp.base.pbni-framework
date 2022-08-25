---
title: Inf::Type< PBArray< PBObject< class_id, group_type >, dims... > >

---

# Inf::Type< PBArray< PBObject< class_id, group_type >, dims... > >



 [More...](#detailed-description)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| bool | **[Assert](/doxygen/Classes/struct_inf_1_1_type_3_01_p_b_array_3_01_p_b_object_3_01class__id_00_01group__type_01_4_00_01dims_8_8_8_01_4_01_4/#function-assert)**(IPB_Session * session, IPB_Value * pb_value) |
| std::wstring | **[GetPBName](/doxygen/Classes/struct_inf_1_1_type_3_01_p_b_array_3_01_p_b_object_3_01class__id_00_01group__type_01_4_00_01dims_8_8_8_01_4_01_4/#function-getpbname)**(std::wstring argument_name) |
| [PBArray](/doxygen/Classes/class_inf_1_1_p_b_array/)< [PBObject](/doxygen/Classes/class_inf_1_1_p_b_object/)< class_id, group_type >, dims... > | **[FromArgument](/doxygen/Classes/struct_inf_1_1_type_3_01_p_b_array_3_01_p_b_object_3_01class__id_00_01group__type_01_4_00_01dims_8_8_8_01_4_01_4/#function-fromargument)**(IPB_Session * session, IPB_Value * pb_value, bool acquire) |
| PBXRESULT | **[SetValue](/doxygen/Classes/struct_inf_1_1_type_3_01_p_b_array_3_01_p_b_object_3_01class__id_00_01group__type_01_4_00_01dims_8_8_8_01_4_01_4/#function-setvalue)**(IPB_Session * session, IPB_Value * pb_value, const [PBArray](/doxygen/Classes/class_inf_1_1_p_b_array/)< [PBObject](/doxygen/Classes/class_inf_1_1_p_b_object/)< class_id, group_type >, dims... > & value) |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| std::wstring | **[PBSignature](/doxygen/Classes/struct_inf_1_1_type_3_01_p_b_array_3_01_p_b_object_3_01class__id_00_01group__type_01_4_00_01dims_8_8_8_01_4_01_4/#variable-pbsignature)**  |

## Detailed Description

```cpp
template <Helper::FixedString class_id,
pbgroup_type group_type,
pblong... dims>
struct Inf::Type< PBArray< PBObject< class_id, group_type >, dims... > >;
```

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
static inline PBArray< PBObject< class_id, group_type >, dims... > FromArgument(
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
    const PBArray< PBObject< class_id, group_type >, dims... > & value
)
```


## Public Attributes Documentation

### variable PBSignature

```cpp
static std::wstring PBSignature = Type<PBObject<class_id, group_type>>::PBSignature + L"[]";
```


-------------------------------

Updated on 2022-08-25 at 15:54:55 +0200