---
title: Inf::PBTime

---

# Inf::PBTime



 [More...](#detailed-description)


`#include <PBDateTimes.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBTime](/doxygen/Classes/class_inf_1_1_p_b_time/#function-pbtime)**(IPB_Session * session, pbtime time) |
| | **[PBTime](/doxygen/Classes/class_inf_1_1_p_b_time/#function-pbtime)**(IPB_Session * session, pbint hours, pbint minutes, pbdouble seconds) |
| std::tuple< pbint, pbint, pbdouble > | **[GetTime](/doxygen/Classes/class_inf_1_1_p_b_time/#function-gettime)**() const |
| void | **[SetTime](/doxygen/Classes/class_inf_1_1_p_b_time/#function-settime)**(pbint hours, pbint minutes, pbdouble seconds) |
| bool | **[IsNull](/doxygen/Classes/class_inf_1_1_p_b_time/#function-isnull)**() const |
| void | **[SetToNull](/doxygen/Classes/class_inf_1_1_p_b_time/#function-settonull)**() |

## Friends

|                | Name           |
| -------------- | -------------- |
| struct | **[Type](/doxygen/Classes/class_inf_1_1_p_b_time/#friend-type)**  |
| class | **[PBArray](/doxygen/Classes/class_inf_1_1_p_b_time/#friend-pbarray)**  |
| class | **[PBObject](/doxygen/Classes/class_inf_1_1_p_b_time/#friend-pbobject)**  |

## Detailed Description

```cpp
class Inf::PBTime;
```


This is a Wrapper for pbtime. 

## Public Functions Documentation

### function PBTime

```cpp
PBTime(
    IPB_Session * session,
    pbtime time
)
```


**Parameters**: 

  * **session** Current session 
  * **time** The exsiting pbtime or 0 


Creates a Wrapper to an already existing pbtime. Will be Null if time is 0.


### function PBTime

```cpp
PBTime(
    IPB_Session * session,
    pbint hours,
    pbint minutes,
    pbdouble seconds
)
```


**Parameters**: 

  * **session** Current Session 
  * **hours** The hour to set 
  * **minutes** The minute to set 
  * **seconds** The second to set 


Creates a new pbtime.


### function GetTime

```cpp
std::tuple< pbint, pbint, pbdouble > GetTime() const
```


**Exceptions**: 

  * **[Inf::PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)** If Null 
  * **[Inf::PBNI_PowerBuilderException](/doxygen/Classes/class_inf_1_1_p_b_n_i___power_builder_exception/)** If PowerBuilder function doesnt return PBX_SUCESS 


**Return**: hours, minutes, seconds

Gets the Time from PowerBuilder.


### function SetTime

```cpp
void SetTime(
    pbint hours,
    pbint minutes,
    pbdouble seconds
)
```


**Parameters**: 

  * **hours** Hours to set 
  * **minutes** Minutes to set 
  * **seconds** Seconds to set


**Exceptions**: 

  * **[Inf::PBNI_PowerBuilderException](/doxygen/Classes/class_inf_1_1_p_b_n_i___power_builder_exception/)** If PowerBuilder function doesnt return PBX_SUCESS 


Sets the Time in PowerBuilder. Creates a new Time if is Null.


### function IsNull

```cpp
bool IsNull() const
```


Checks whether the pbtime is Null 


### function SetToNull

```cpp
void SetToNull()
```


Sets the pbtime to Null. 


## Friends

### friend Type

```cpp
friend struct Type(
    Type 
);
```


### friend PBArray

```cpp
friend class PBArray(
    PBArray 
);
```


### friend PBObject

```cpp
friend class PBObject(
    PBObject 
);
```


-------------------------------

Updated on 2022-08-25 at 16:29:24 +0200