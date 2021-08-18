#include "pch.h"

#include <iostream>
#include <vector>
#include <assert.h>
#include "Solver.h"

class TestbedNode : public Sandbox::ISolverNode
{
public: 
    TestbedNode(double x, double y, double z)
    {
        _location = { x,y,z };
    }

    virtual Sandbox::Vec3 GetLocation() const
    {
        return _location;
    }
private:
    Sandbox::Vec3 _location;
};

bool operator==(Sandbox::Vec3& left, Sandbox::Vec3& right)
{
    return  left.x == right.x &&
            left.y == right.y &&
            left.z == right.z;
}

int main()
{
    // This Dll is lazy loaded at runtime - we don't link the .lib into the project
    // The only shared resource are the interface headers
    Sandbox::ISolver* pSolver = Solver_ISolver_Construct();
    assert(pSolver != nullptr);

    // This NodeList class lives entirely in the solver - the testbed only has an interface pointer
    Sandbox::INodeList* pNodeList = Solver_INodeList_Construct();

    // these TestbedNodes live entirely in the testbed - the nodelist only gets interface pointers 
    pNodeList->AddNode(new TestbedNode( 1,2,3 ));
    pNodeList->AddNode(new TestbedNode( 2,3,4 ));
    pNodeList->AddNode(new TestbedNode( 3,4,5 ));

    Sandbox::Vec3 centre = pSolver->CentrePoint(pNodeList);

    Solver_INodeList_Delete(pNodeList);

    Sandbox::Vec3 expected{ 2,3,4 };

    assert(centre == expected);

    Solver_ISolver_Delete(pSolver);
}
