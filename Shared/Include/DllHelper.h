#pragma once

#include <memory>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#ifdef SOLVER_EXPORTS
#define SOLVERDLL_API __declspec(dllexport) 

#define ExportLibrary(LibraryName)

#define ExportType(Namespace, LibraryName, TypeName) \
extern "C" { \
	extern SOLVERDLL_API Namespace::TypeName* LibraryName##_##TypeName##_Create(); \
	extern SOLVERDLL_API void LibraryName##_##TypeName##_Destroy(Namespace::TypeName* obj); \
}

#define DeclareTypeFactory(Namespace, LibraryName, InterfaceName, TypeName) \
Namespace::InterfaceName* LibraryName##_##InterfaceName##_Create() \
{ \
printf("Created a %s\r\n", TOSTRING(TypeName)); \
return new Namespace::TypeName(); \
} \
void LibraryName##_##InterfaceName##_Destroy(Namespace::InterfaceName* obj) \
{ \
delete obj; \
printf("Deleted a %s\r\n", TOSTRING(TypeName)); \
}

#else

#define ExportLibrary(LibraryName) \
	static HMODULE LibraryName##Dll = 0; \
	static int LibraryName##RefCount = 0; \
\
inline static HMODULE LibraryName##Get() \
{ \
	if (LibraryName##RefCount == 0) { \
		const char* dllName = TOSTRING(LibraryName)".dll"; \
		LibraryName##Dll = LoadLibraryA(dllName); \
		printf("Loaded Library '%s'\r\n", dllName); \
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
	printf("Loading dll fn '%s'\r\n", funcName); \
	CreateFn pfnCreate = hDLL ? CreateFn(GetProcAddress(hDLL, funcName)) : nullptr; \
	assert(pfnCreate != nullptr); \
	return pfnCreate ? pfnCreate() : nullptr; \
} \
inline static void LibraryName##_##TypeName##_Delete(Namespace::TypeName* obj) { \
	HMODULE hDLL = LibraryName##Get(); \
	typedef void (*DestroyFn)(Namespace::TypeName*); \
	const char* funcName =  TOSTRING(LibraryName##_##TypeName##_Destroy); \
	printf("Loading dll fn '%s'\r\n", funcName); \
	DestroyFn pfnDestroy = hDLL ? DestroyFn(GetProcAddress(hDLL, funcName)) : nullptr; \
	assert(pfnDestroy != nullptr); \
	if (pfnDestroy) pfnDestroy(obj); \
} \
namespace Namespace { \
typedef std::shared_ptr<TypeName> TypeName##Ptr;  \
TypeName##Ptr Make##TypeName() { return TypeName##Ptr( LibraryName##_##TypeName##_Construct(), LibraryName##_##TypeName##_Delete ); } \
}

#endif

