#pragma once

#include "DllHelper.h"
#include "ISolverNode.h"
#include <memory>

ExportLibrary(SolverDll);

namespace Sandbox
{
	struct INodeList
	{
		virtual ~INodeList() {}

		virtual void AddNode(ISolverNode* pNode) = 0;
		virtual size_t Count() const = 0;
		virtual const ISolverNode* At(int idx) const = 0;
	};

	struct ISolver
	{
		virtual ~ISolver() {}

		virtual Vec3 CentrePoint(const INodeList* pNodes) = 0;
	};
}

ExportType(Sandbox, SolverDll, INodeList)
ExportType(Sandbox, SolverDll, ISolver)
