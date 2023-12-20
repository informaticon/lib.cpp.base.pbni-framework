# PBNI Framework - Errors
---

The PBNI Framework catches every `std::exception`, and forwards it to PowerBuilder. To be able to make descriptive Errors, the `Inf::PBNI_Exception` was created. It holds a Key-Value Store of WStrings. This Store will be passed over to PowerBuilder.

If the DLL is Built using Debug Configuration some Additional Features get used:
 - A StackTrace gets added to the `Inf::PBNI_Exception` Objects using `boost::stacktrace`
 - If the PBNI Framework fails to pass the Error to PowerBuilder (e.g. because the exf library is missing), a `pbni.log` file will be created in the Working Directory (probably `lib/`) to output the Error.

Here are a list of Exceptions that get thrown by the Framework.

 - Inf::PBNI_IndexOutOfBounds
 - Inf::PBNI_NullPointerException
 - Inf::PBNI_InvalidFieldException
 - Inf::PBNI_IncorrectArgumentsException
 - Inf::PBNI_PowerBuilderException

You can create your own by extending Inf::PBNI_Exception.

## Nesting Exceptions
If you want the Exception to have a certain PowerBuilder type you can call the NestAs function:
```cpp
    throw PBNI_Exception(L"Failed to open picture file for reading", {
        { L"GraphicsMagick Error", ConvertString<std::wstring>(err.what()) }
    }).NestAs(L"u_exf_ex_io");
```
