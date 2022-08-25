---
title: Inf::Helper::FixedString

---

# Inf::Helper::FixedString



 [More...](#detailed-description)


`#include <PBString.h>`

## Public Functions

|                | Name           |
| -------------- | -------------- |
| constexpr | **[FixedString](/doxygen/Classes/struct_inf_1_1_helper_1_1_fixed_string/#function-fixedstring)**(wchar_t const (&) s[N]) |
| constexpr std::strong_ordering | **[operator<=>](/doxygen/Classes/struct_inf_1_1_helper_1_1_fixed_string/#function-operator<=>)**([FixedString](/doxygen/Classes/struct_inf_1_1_helper_1_1_fixed_string/) const & ) const =default |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| wchar_t | **[data](/doxygen/Classes/struct_inf_1_1_helper_1_1_fixed_string/#variable-data)**  |

## Detailed Description

```cpp
template <size_t N>
struct Inf::Helper::FixedString;
```


We need this to be able to pass strings as Template parameters. There will probably be a more supported way in C++23. See [https://www.quora.com/How-do-you-pass-a-string-literal-as-a-parameter-to-a-C-template-class](https://www.quora.com/How-do-you-pass-a-string-literal-as-a-parameter-to-a-C-template-class). 

## Public Functions Documentation

### function FixedString

```cpp
inline constexpr FixedString(
    wchar_t const (&) s[N]
)
```


### function operator<=>

```cpp
constexpr std::strong_ordering operator<=>(
    FixedString const & 
) const =default
```


## Public Attributes Documentation

### variable data

```cpp
wchar_t data;
```


-------------------------------

Updated on 2022-08-25 at 16:08:57 +0200