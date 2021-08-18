#pragma once
#include "DllHelper.h"
#include "ISolverNode.h"

ExportLibrary(Solver);

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
	};
}

ExportType(Sandbox, Solver, INodeList)
ExportType(Sandbox, Solver, ISolver)

