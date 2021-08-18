#pragma once

#ifdef SOLVER_EXPORTS
#define SOLVERDLL_API __declspec(dllexport) 
#else
#define SOLVERDLL_API __declspec(dllimport) 
#endif

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#ifdef SOLVER_EXPORTS
#define ExportLibrary(LibraryName)

#define ExportType(Namespace, LibraryName, TypeName) \
extern "C" { \
	extern SOLVERDLL_API Namespace::TypeName* LibraryName##_##TypeName##_Create(); \
}

#define DeclareTypeFactory(Namespace, LibraryName, InterfaceName, TypeName) \
Namespace::InterfaceName* LibraryName##_##InterfaceName##_Create() \
{ \
return new Namespace::TypeName(); \
}

#else

#define ExportLibrary(LibraryName) \
	static HMODULE LibraryName##Dll = 0; \
	static int LibraryName##RefCount = 0; \
\
inline static HMODULE LibraryName##Get() \
{ \
	if (LibraryName##RefCount == 0) { \
		LibraryName##Dll = LoadLibrary(L"Solver.dll"); \
		printf("Loaded Library\r\n"); \
	} \
	LibraryName##RefCount++; \
	assert(LibraryName##Dll != nullptr); \
	return LibraryName##Dll;\
} 

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define ExportType(Namespace, LibraryName, TypeName) \
inline static Namespace::TypeName* LibraryName##_##TypeName##_Construct() { \
	HMODULE hDLL = LibraryName##Get(); \
	typedef Namespace::TypeName* (*CreateFn)(); \
	const char* funcName =  TOSTRING(LibraryName##_##TypeName##_Create); \
	printf("Loading '%s'\r\n", funcName); \
	CreateFn pfnCreate = hDLL ? CreateFn(GetProcAddress(hDLL, funcName)) : nullptr; \
	assert(pfnCreate != nullptr); \
	return pfnCreate ? pfnCreate() : nullptr; \
}

#endif

