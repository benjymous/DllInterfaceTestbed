#include "pch.h"
#include <Solver.h>
#include <vector>
#include <memory>

namespace Sandbox
{
	class NodeList : public INodeList
	{
	public:
		void AddNode(ISolverNode* pNode)
		{
			_nodes.push_back(std::shared_ptr<ISolverNode>(pNode));
		}
		size_t Count() const
		{
			return _nodes.size();
		}
		const ISolverNode* At(int idx) const
		{
			return _nodes[idx].get();
		}
	private:
		std::vector<std::shared_ptr<ISolverNode>> _nodes;
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

DeclareTypeFactory(Sandbox, SolverDll, ISolver, Solver);
DeclareTypeFactory(Sandbox, SolverDll, INodeList, NodeList);

// namespace Sandbox
// {
// 	INodeList* SolverDll_INodeList_Construct() { return new NodeList; }
// 	void SolverDll_INodeList_Delete(INodeList* obj) { delete obj; }
// }