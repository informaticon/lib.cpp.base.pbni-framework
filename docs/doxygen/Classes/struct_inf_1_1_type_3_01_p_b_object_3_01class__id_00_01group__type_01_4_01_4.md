---
title: Inf::Type< PBObject< class_id, group_type > >

---

# Inf::Type< PBObject< class_id, group_type > >



 [More...](#detailed-description)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| bool | **[Assert](/doxygen/Classes/struct_inf_1_1_type_3_01_p_b_object_3_01class__id_00_01group__type_01_4_01_4/#function-assert)**(IPB_Session * session, IPB_Value * pb_value) |
| std::wstring | **[GetPBName](/doxygen/Classes/struct_inf_1_1_type_3_01_p_b_object_3_01class__id_00_01group__type_01_4_01_4/#function-getpbname)**(std::wstring argument_name) |
| [PBObject](/doxygen/Classes/class_inf_1_1_p_b_object/)< class_id, group_type > | **[FromArgument](/doxygen/Classes/struct_inf_1_1_type_3_01_p_b_object_3_01class__id_00_01group__type_01_4_01_4/#function-fromargument)**(IPB_Session * session, IPB_Value * pb_value, bool acquire) |
| PBXRESULT | **[SetValue](/doxygen/Classes/struct_inf_1_1_type_3_01_p_b_object_3_01class__id_00_01group__type_01_4_01_4/#function-setvalue)**(IPB_Session * session, IPB_Value * pb_value, const [PBObject](/doxygen/Classes/class_inf_1_1_p_b_object/)< class_id, group_type > & value) |
| PBXRESULT | **[Return](/doxygen/Classes/struct_inf_1_1_type_3_01_p_b_object_3_01class__id_00_01group__type_01_4_01_4/#function-return)**(IPB_Session * session, PBCallInfo * ci, const [PBObject](/doxygen/Classes/class_inf_1_1_p_b_object/)< class_id, group_type > & value) |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| std::wstring | **[PBSignature](/doxygen/Classes/struct_inf_1_1_type_3_01_p_b_object_3_01class__id_00_01group__type_01_4_01_4/#variable-pbsignature)**  |

## Detailed Description

```cpp
template <Helper::FixedString class_id,
pbgroup_type group_type>
struct Inf::Type< PBObject< class_id, group_type > >;
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
static inline PBObject< class_id, group_type > FromArgument(
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
    const PBObject< class_id, group_type > & value
)
```


### function Return

```cpp
static inline PBXRESULT Return(
    IPB_Session * session,
    PBCallInfo * ci,
    const PBObject< class_id, group_type > & value
)
```


## Public Attributes Documentation

### variable PBSignature

```cpp
static std::wstring PBSignature = std::wstring(L"C") + PBObject<class_id, group_type>::ClassName() + L".";
```


-------------------------------

Updated on 2022-08-25 at 15:54:55 +0200