# Dll Interface Testbed

This is a little example showing a cross platform library solution

On Windows the "Solver" library is built to a Dll, and is lazy loaded automatically when required

On Linux (and other posix platforms) the library is built as a static lib

The majority of platform specific library handling logic is wrapped up in Shared\Include\DllHelper.h

This defines a number of macros, depending on build target and platform

## ExportLibrary(LibraryName)

Declares a library - generates the boilerplate dll loading code when built in the library project

## ExportType(Namespace, LibraryName, InterfaceName)

Declares an exported type

## DeclareTypeFactory(Namespace, LibraryName, InterfaceName, TypeName)

Instantiates the factory functions to create and delete objects of a given type

# Usage

The macros create some convenience functions that wrap up all the dll usage so

```
auto pSolver = Sandbox::MakeISolver();
```

will handle loading the dll (if necessary) and will return a `std::shared_ptr<ISolver>` - this object will auto destruct safely (using the factory functions defined in the library) as per a usual std::shared_ptr