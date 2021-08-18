#pragma once

#ifdef _WIN32

#include <memory>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#ifdef SOLVER_EXPORTS
	#define SOLVERDLL_API __declspec(dllexport) 

	#define ExportLibrary(LibraryName)

	#define ExportType(Namespace, LibraryName, InterfaceName) \
	extern "C" { \
		extern SOLVERDLL_API Namespace::InterfaceName* LibraryName##_##InterfaceName##_Create(); \
		extern SOLVERDLL_API void LibraryName##_##InterfaceName##_Destroy(Namespace::InterfaceName* obj); \
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

	#define ExportType(Namespace, LibraryName, InterfaceName) \
	inline static Namespace::InterfaceName* LibraryName##_##InterfaceName##_Construct() { \
		HMODULE hDLL = LibraryName##Get(); \
		typedef Namespace::InterfaceName* (*CreateFn)(); \
		const char* funcName =  TOSTRING(LibraryName##_##InterfaceName##_Create); \
		printf("Loading dll fn '%s'\r\n", funcName); \
		CreateFn pfnCreate = hDLL ? CreateFn(GetProcAddress(hDLL, funcName)) : nullptr; \
		assert(pfnCreate != nullptr); \
		return pfnCreate ? pfnCreate() : nullptr; \
	} \
	inline static void LibraryName##_##InterfaceName##_Delete(Namespace::InterfaceName* obj) { \
		HMODULE hDLL = LibraryName##Get(); \
		typedef void (*DestroyFn)(Namespace::InterfaceName*); \
		const char* funcName =  TOSTRING(LibraryName##_##InterfaceName##_Destroy); \
		printf("Loading dll fn '%s'\r\n", funcName); \
		DestroyFn pfnDestroy = hDLL ? DestroyFn(GetProcAddress(hDLL, funcName)) : nullptr; \
		assert(pfnDestroy != nullptr); \
		if (pfnDestroy) pfnDestroy(obj); \
	} \
	namespace Namespace { \
		typedef std::shared_ptr<InterfaceName> InterfaceName##Ptr;  \
		InterfaceName##Ptr Make##InterfaceName() { return InterfaceName##Ptr( LibraryName##_##InterfaceName##_Construct(), LibraryName##_##InterfaceName##_Delete ); } \
	}

#endif

#else
	// Linux uses a static lib, so don't need to worry about most of this

	#define ExportLibrary(x)

#ifdef SOLVER_EXPORTS
	#define ExportType(Namespace, LibraryName, InterfaceName)
#else
	#define ExportType(Namespace, LibraryName, InterfaceName) \
	namespace Namespace { \
		typedef std::shared_ptr<InterfaceName> InterfaceName##Ptr;  \
		InterfaceName* LibraryName##_##InterfaceName##_Construct(); \
		void LibraryName##_##InterfaceName##_Delete(InterfaceName* obj); \
		InterfaceName##Ptr Make##InterfaceName() { return InterfaceName##Ptr( LibraryName##_##InterfaceName##_Construct(), LibraryName##_##InterfaceName##_Delete ); } \
	}
#endif

	#define DeclareTypeFactory(Namespace, LibraryName, InterfaceName, TypeName) \
	namespace Namespace { \
		InterfaceName* LibraryName##_##InterfaceName##_Construct() { return new TypeName(); } \
		void LibraryName##_##InterfaceName##_Delete(InterfaceName* obj) { delete obj; } \
	}
#endif