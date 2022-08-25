---
title: Inf::PBArray

---

# Inf::PBArray



 [More...](#detailed-description)


`#include <PBArray.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PBArray](/doxygen/Classes/class_inf_1_1_p_b_array/#function-pbarray)**(IPB_Session * session, pbarray arr) |
| | **[PBArray](/doxygen/Classes/class_inf_1_1_p_b_array/#function-pbarray)**(IPB_Session * session) |
| void | **[Set](/doxygen/Classes/class_inf_1_1_p_b_array/#function-set)**(pblong pos, const Item t) |
| Item | **[Get](/doxygen/Classes/class_inf_1_1_p_b_array/#function-get)**(pblong pos) |
| void | **[SetItemToNull](/doxygen/Classes/class_inf_1_1_p_b_array/#function-setitemtonull)**(pblong pos) |
| bool | **[IsItemNull](/doxygen/Classes/class_inf_1_1_p_b_array/#function-isitemnull)**(pblong pos) |
| void | **[Set](/doxygen/Classes/class_inf_1_1_p_b_array/#function-set)**(std::array< pblong, sizeof...(dims)> pos, const Item t) |
| Item | **[Get](/doxygen/Classes/class_inf_1_1_p_b_array/#function-get)**(std::array< pblong, sizeof...(dims)> pos) |
| void | **[SetItemToNull](/doxygen/Classes/class_inf_1_1_p_b_array/#function-setitemtonull)**(std::array< pblong, sizeof...(dims)> pos) |
| bool | **[IsItemNull](/doxygen/Classes/class_inf_1_1_p_b_array/#function-isitemnull)**(std::array< pblong, sizeof...(dims)> pos) |
| std::array< std::pair< pblong, pblong >, sizeof...(dims)> | **[Bounds](/doxygen/Classes/class_inf_1_1_p_b_array/#function-bounds)**() const |
| pblong | **[Size](/doxygen/Classes/class_inf_1_1_p_b_array/#function-size)**() |
| bool | **[IsNull](/doxygen/Classes/class_inf_1_1_p_b_array/#function-isnull)**() const |
| void | **[SetToNull](/doxygen/Classes/class_inf_1_1_p_b_array/#function-settonull)**() |
| | **[operator pbarray](/doxygen/Classes/class_inf_1_1_p_b_array/#function-operator-pbarray)**() const |

## Detailed Description

```cpp
template <typename Item ,
pblong... dims>
class Inf::PBArray;
```


**Template Parameters**: 

  * **Item** [Type](/doxygen/Classes/struct_inf_1_1_type/) of the Array Items 
  * **...dims** The Bounds of the Bounded Array, Unbounded Array if empty 


Wrapper for simple Arrays.

## Public Functions Documentation

### function PBArray

```cpp
inline PBArray(
    IPB_Session * session,
    pbarray arr
)
```


**Parameters**: 

  * **session** Current session 
  * **arr** pbarray or 0 


Creates a Wrapper to an existing pbarray. Null if arr is 0


### function PBArray

```cpp
inline PBArray(
    IPB_Session * session
)
```


**Parameters**: 

  * **session** Current Session 


Creates a new Bounded or Unbounded Array.


### function Set

```cpp
inline void Set(
    pblong pos,
    const Item t
)
```


**Parameters**: 

  * **pos** The Position 
  * **t** The Value to set from


**Exceptions**: 

  * **[Inf::PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)** If is Null 
  * **[Inf::PBNI_IndexOutOfBoundsException](/doxygen/Classes/class_inf_1_1_p_b_n_i___index_out_of_bounds_exception/)** If out of bounds 
  * **[Inf::PBNI_PowerBuilderException](/doxygen/Classes/class_inf_1_1_p_b_n_i___power_builder_exception/)** If PowerBuilder function doesnt return PBX_SUCESS 


Sets an Item in an Unbounded Array. Copies if Item is string or blob.


### function Get

```cpp
inline Item Get(
    pblong pos
)
```


**Parameters**: 

  * **pos** The Position 


**Exceptions**: 

  * **[Inf::PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)** If is Null 
  * **[Inf::PBNI_IndexOutOfBoundsException](/doxygen/Classes/class_inf_1_1_p_b_n_i___index_out_of_bounds_exception/)** If out of bounds 


**Return**: The Value

Retrieves an Item in an Unbounded Array. If Item is complex, it will return a reference.


### function SetItemToNull

```cpp
inline void SetItemToNull(
    pblong pos
)
```


**Parameters**: 

  * **pos** The Position


**Exceptions**: 

  * **[Inf::PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)** If is Null 
  * **[Inf::PBNI_IndexOutOfBoundsException](/doxygen/Classes/class_inf_1_1_p_b_n_i___index_out_of_bounds_exception/)** If out of bounds 
  * **[Inf::PBNI_PowerBuilderException](/doxygen/Classes/class_inf_1_1_p_b_n_i___power_builder_exception/)** If PowerBuilder function doesnt return PBX_SUCESS 


Sets an Item in an Unbounded Array To Null.


### function IsItemNull

```cpp
inline bool IsItemNull(
    pblong pos
)
```


**Parameters**: 

  * **pos** The Position 


**Exceptions**: 

  * **[Inf::PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)** If is Null 
  * **[Inf::PBNI_IndexOutOfBoundsException](/doxygen/Classes/class_inf_1_1_p_b_n_i___index_out_of_bounds_exception/)** If out of bounds 


**Return**: Is Null

Checks wheter an Item in an Unbounded Array is Null.


### function Set

```cpp
inline void Set(
    std::array< pblong, sizeof...(dims)> pos,
    const Item t
)
```


**Parameters**: 

  * **pos** Array of Positions 
  * **t** The Value to set from


**Exceptions**: 

  * **[Inf::PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)** If is Null 
  * **[Inf::PBNI_IndexOutOfBoundsException](/doxygen/Classes/class_inf_1_1_p_b_n_i___index_out_of_bounds_exception/)** If out of bounds 
  * **[Inf::PBNI_PowerBuilderException](/doxygen/Classes/class_inf_1_1_p_b_n_i___power_builder_exception/)** If PowerBuilder function doesnt return PBX_SUCESS 


Sets an Item in a Bounded Array. Copies if Item is string or blob.


### function Get

```cpp
inline Item Get(
    std::array< pblong, sizeof...(dims)> pos
)
```


**Parameters**: 

  * **pos** Array of Positions 


**Exceptions**: 

  * **[Inf::PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)** If is Null 
  * **[Inf::PBNI_IndexOutOfBoundsException](/doxygen/Classes/class_inf_1_1_p_b_n_i___index_out_of_bounds_exception/)** If out of bounds 


**Return**: The Value

Retrieves an Item in a Bounded Array. If Item is complex, it will return a reference.


### function SetItemToNull

```cpp
inline void SetItemToNull(
    std::array< pblong, sizeof...(dims)> pos
)
```


**Parameters**: 

  * **pos** Array of Positions


**Exceptions**: 

  * **[Inf::PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)** If is Null 
  * **[Inf::PBNI_IndexOutOfBoundsException](/doxygen/Classes/class_inf_1_1_p_b_n_i___index_out_of_bounds_exception/)** If out of bounds 
  * **[Inf::PBNI_PowerBuilderException](/doxygen/Classes/class_inf_1_1_p_b_n_i___power_builder_exception/)** If PowerBuilder function doesnt return PBX_SUCESS 


Sets an Item in a Bounded Array To Null.


### function IsItemNull

```cpp
inline bool IsItemNull(
    std::array< pblong, sizeof...(dims)> pos
)
```


**Parameters**: 

  * **pos** Array of Positions 


**Exceptions**: 

  * **[Inf::PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)** If is Null 
  * **[Inf::PBNI_IndexOutOfBoundsException](/doxygen/Classes/class_inf_1_1_p_b_n_i___index_out_of_bounds_exception/)** If out of bounds 


**Return**: Is Null

Checks wheter an Item in a Bounded Array is Null.


### function Bounds

```cpp
inline std::array< std::pair< pblong, pblong >, sizeof...(dims)> Bounds() const
```


**Return**: An Array of Bounds 

Gets the Bounds of a Bounded Array From PowerBuilder.


### function Size

```cpp
inline pblong Size()
```


**Exceptions**: 

  * **[Inf::PBNI_NullPointerException](/doxygen/Classes/class_inf_1_1_p_b_n_i___null_pointer_exception/)** If is Null 


**Return**: The Size

Retrieves the Length of the Array from PowerBuilder.


### function IsNull

```cpp
inline bool IsNull() const
```


**Return**: Is Null 

Check wether the pbarray is null.


### function SetToNull

```cpp
inline void SetToNull()
```


Sets the pbarray to Null. 


### function operator pbarray

```cpp
inline operator pbarray() const
```


**Return**: The pbarray used for PowerBuilder functions 

This conversion operator is currently the only way of getting the pbarray.


-------------------------------

Updated on 2022-08-25 at 16:29:23 +0200