# PBNI Framework
*lib.cpp.base.pbni-framework*

---

This is a framework to easily create extensions for PowerBuilder.
All you need to do is add a CMake target and register your Classes and its Methods.

Under the hood, the Framework gathers the Argument and Return Types of the Methods at compile time. Then creates UserObject Descriptions of the Classes when the DLL is attached. The Framework will instantiate new Objects if told to. Whenever PowerBuilder calls a function of the dll, the Framework will parse all arguments and forward it to your Method. Once your Method returns it will parse the return Value and reference Arguments back to PowerBuilder.

### Dependencies
 - PowerBuilder PBNI
 - Boost (vcpkg)

### Documentation
  - [Quickstart](quick-start.md)
  - [PowerBuilder](powerbuilder.md)
  - [PowerBuilder DataTypes](variables.md)
  - [Exception Handling](errors.md)
  - [External Libraries](libraries.md)
  - [Doxygen Documentation](https://github.com/informaticon/lib.cpp.base.pbni-framework/tree/main/docs/doxygen)

### Examples
 - [Usage Example](https://github.com/informaticon/div.cpp.base.pbni-framework-usage-example)
 - [TSE Library](https://github.com/informaticon/lib.pbni.base.tse)
