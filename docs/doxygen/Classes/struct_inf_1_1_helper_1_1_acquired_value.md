---
title: Inf::Helper::AcquiredValue

---

# Inf::Helper::AcquiredValue



 [More...](#detailed-description)


`#include <AcquiredValue.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[AcquiredValue](/doxygen/Classes/struct_inf_1_1_helper_1_1_acquired_value/#function-acquiredvalue)**(IPB_Session * session, IPB_Value * value, bool acquire =true) |
| | **[~AcquiredValue](/doxygen/Classes/struct_inf_1_1_helper_1_1_acquired_value/#function-~acquiredvalue)**() |
| void | **[Acquire](/doxygen/Classes/struct_inf_1_1_helper_1_1_acquired_value/#function-acquire)**() |
| void | **[Release](/doxygen/Classes/struct_inf_1_1_helper_1_1_acquired_value/#function-release)**() |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| IPB_Session * | **[Session](/doxygen/Classes/struct_inf_1_1_helper_1_1_acquired_value/#variable-session)**  |
| IPB_Value * | **[Value](/doxygen/Classes/struct_inf_1_1_helper_1_1_acquired_value/#variable-value)**  |
| bool | **[Acquired](/doxygen/Classes/struct_inf_1_1_helper_1_1_acquired_value/#variable-acquired)**  |

## Detailed Description

```cpp
struct Inf::Helper::AcquiredValue;
```


This struct is used to hold a PowerBuilder Value. If you dont hold Acquire the Value, the data within it will be Freed once the CallbackInfo gets freed. So if you want to keep the Value, you need to Acquire it. This is only useful with complex types, such as DateTimes, Blob, Strings, Arrays and Objects 

## Public Functions Documentation

### function AcquiredValue

```cpp
inline AcquiredValue(
    IPB_Session * session,
    IPB_Value * value,
    bool acquire =true
)
```


### function ~AcquiredValue

```cpp
inline ~AcquiredValue()
```


### function Acquire

```cpp
inline void Acquire()
```


### function Release

```cpp
inline void Release()
```


## Public Attributes Documentation

### variable Session

```cpp
IPB_Session * Session;
```


### variable Value

```cpp
IPB_Value * Value;
```


### variable Acquired

```cpp
bool Acquired;
```


-------------------------------

Updated on 2022-08-25 at 16:08:57 +0200