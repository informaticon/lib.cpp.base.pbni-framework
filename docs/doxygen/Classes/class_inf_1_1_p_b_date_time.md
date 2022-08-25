---
title: Inf::PBDateTime

---

# Inf::PBDateTime



 [More...](#detailed-description)


`#include <PBDateTimes.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBDateTime](/doxygen/Classes/class_inf_1_1_p_b_date_time/#function-pbdatetime)**(IPB_Session * session, pbdatetime datetime) |
| | **[PBDateTime](/doxygen/Classes/class_inf_1_1_p_b_date_time/#function-pbdatetime)**(IPB_Session * session, pbint years, pbint months, pbint days, pbint hours, pbint minutes, pbdouble seconds) |
| std::tuple< pbint, pbint, pbint, pbint, pbint, pbdouble > | **[GetDateTime](/doxygen/Classes/class_inf_1_1_p_b_date_time/#function-getdatetime)**() const |
| void | **[SetDateTime](/doxygen/Classes/class_inf_1_1_p_b_date_time/#function-setdatetime)**(pbint years, pbint months, pbint days, pbint hours, pbint minutes, pbdouble seconds) |
| bool | **[IsNull](/doxygen/Classes/class_inf_1_1_p_b_date_time/#function-isnull)**() const |
| void | **[SetToNull](/doxygen/Classes/class_inf_1_1_p_b_date_time/#function-settonull)**() |

## Friends

|                | Name           |
| -------------- | -------------- |
| struct | **[Type](/doxygen/Classes/class_inf_1_1_p_b_date_time/#friend-type)**  |
| class | **[PBArray](/doxygen/Classes/class_inf_1_1_p_b_date_time/#friend-pbarray)**  |
| class | **[PBObject](/doxygen/Classes/class_inf_1_1_p_b_date_time/#friend-pbobject)**  |

## Detailed Description

```cpp
class Inf::PBDateTime;
```


This is a Wrapper for pbdatetime. 

## Public Functions Documentation

### function PBDateTime

```cpp
PBDateTime(
    IPB_Session * session,
    pbdatetime datetime
)
```


**Parameters**: 

  * **session** Current session 
  * **datetime** The exsiting pbdatetime or 0 


Creates a Wrapper to an already existing pbdatetime. Will be Null if datetime is 0.


### function PBDateTime

```cpp
PBDateTime(
    IPB_Session * session,
    pbint years,
    pbint months,
    pbint days,
    pbint hours,
    pbint minutes,
    pbdouble seconds
)
```


**Parameters**: 

  * **session** Current Session 
  * **years** The years to set 
  * **months** The months to set 
  * **days** The days to set 
  * **hours** The hour to set 
  * **minutes** The minute to set 
  * **seconds** The second to set 


Creates a new pbdatetime.


### function GetDateTime

```cpp
std::tuple< pbint, pbint, pbint, pbint, pbint, pbdouble > GetDateTime() const
```


**Exceptions**: 

  * **[Inf::PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)** If Null 
  * **[Inf::PBNI_PowerBuilderException](/doxygen/Classes/class_inf_1_1_p_b_n_i___power_builder_exception/)** If PowerBuilder function doesnt return PBX_SUCESS 


**Return**: years, months, days, hours, minutes, seconds

Gets the DateTime from PowerBuilder.


### function SetDateTime

```cpp
void SetDateTime(
    pbint years,
    pbint months,
    pbint days,
    pbint hours,
    pbint minutes,
    pbdouble seconds
)
```


**Parameters**: 

  * **years** Years to set 
  * **months** Months to set 
  * **days** Days to set 
  * **hours** Hours to set 
  * **minutes** Minutes to set 
  * **seconds** Seconds to set


**Exceptions**: 

  * **[Inf::PBNI_PowerBuilderException](/doxygen/Classes/class_inf_1_1_p_b_n_i___power_builder_exception/)** If PowerBuilder function doesnt return PBX_SUCESS 


Sets the DateTime in PowerBuilder. Creates a new DateTime if is Null.


### function IsNull

```cpp
bool IsNull() const
```


Checks whether the pbdatetime is Null 


### function SetToNull

```cpp
void SetToNull()
```


Sets the pbdatetime to Null. 


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