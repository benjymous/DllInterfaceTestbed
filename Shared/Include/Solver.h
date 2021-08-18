#pragma once

#include "ISolverNode.h"

#ifdef SOLVER_EXPORTS
#define SOLVERDLL_API __declspec(dllexport) 
#else
#define SOLVERDLL_API __declspec(dllimport) 
#endif

namespace Sandbox
{
	struct INodeList
	{
		virtual ~INodeList() {}
		virtual void AddNode(ISolverNode* pNode) = 0;
		virtual int Count() const = 0;
		virtual const ISolverNode* At(int idx) const = 0;
	};

	struct ISolver
	{
		virtual ~ISolver() {}
		virtual Vec3 CentrePoint(const INodeList* pNodes) = 0;

		virtual INodeList* CreateNodeList() = 0;
	};

#ifndef SOLVER_EXPORTS
inline static ISolver* InitSolverDll()
{
	HMODULE hDLL = LoadLibrary(L"Solver.dll");
	typedef ISolver* (*CreateSolverFn)();
	CreateSolverFn pfnCreateSolver = hDLL ? CreateSolverFn(GetProcAddress(hDLL, "CreateSolver")) : nullptr;
	return pfnCreateSolver ? pfnCreateSolver() : nullptr;
}
#endif
}

#ifdef SOLVER_EXPORTS
	extern "C" /*Important for avoiding Name decoration*/
	{
		extern SOLVERDLL_API Sandbox::ISolver* CreateSolver();
	} 
#endif


