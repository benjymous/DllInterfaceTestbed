#include "pch.h"
#include <Solver.h>
#include <vector>

class NodeList : public Sandbox::INodeList
{
public:
	void AddNode(Sandbox::ISolverNode* pNode)
	{
		_nodes.push_back(pNode);
	}
	int Count() const
	{
		return _nodes.size();
	}
	const Sandbox::ISolverNode* At(int idx) const
	{
		return _nodes[idx];
	}
private:
	std::vector<Sandbox::ISolverNode*> _nodes;
};

class Solver : public Sandbox::ISolver
{
public:

	Sandbox::Vec3 CentrePoint(const Sandbox::INodeList* pNodes)
	{
		Sandbox::Vec3 result{ 0,0,0 };

		for (int i = 0; i < pNodes->Count(); ++i)
		{
			Sandbox::Vec3 pos = pNodes->At(i)->GetLocation();

			result.x += pos.x;
			result.y += pos.y;
			result.z += pos.z;
		}

		result.x /= pNodes->Count();
		result.y /= pNodes->Count();
		result.z /= pNodes->Count();

		return result;
	}

	virtual Sandbox::INodeList* CreateNodeList()
	{
		return new NodeList();
	}

};

Sandbox::ISolver* CreateSolver()
{
	return new Solver();
}

