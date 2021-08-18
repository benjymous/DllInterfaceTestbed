#include "pch.h"
#include <Solver.h>
#include <vector>

namespace Sandbox
{

	class NodeList : public INodeList
	{
	public:
		void AddNode(ISolverNode* pNode)
		{
			_nodes.push_back(pNode);
		}
		int Count() const
		{
			return _nodes.size();
		}
		const ISolverNode* At(int idx) const
		{
			return _nodes[idx];
		}
	private:
		std::vector<ISolverNode*> _nodes;
	};

	class Solver : public ISolver
	{
	public:

		Vec3 CentrePoint(const INodeList* pNodes)
		{
			Vec3 result{ 0,0,0 };

			for (int i = 0; i < pNodes->Count(); ++i)
			{
				Vec3 pos = pNodes->At(i)->GetLocation();

				result.x += pos.x;
				result.y += pos.y;
				result.z += pos.z;
			}

			result.x /= pNodes->Count();
			result.y /= pNodes->Count();
			result.z /= pNodes->Count();

			return result;
		}
	};

}

DeclareTypeFactory(Sandbox, Solver, ISolver, Solver);
DeclareTypeFactory(Sandbox, Solver, INodeList, NodeList);