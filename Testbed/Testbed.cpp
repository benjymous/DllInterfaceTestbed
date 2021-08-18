#include "pch.h"

#include <iostream>
#include <vector>
#include <assert.h>
#include "Solver.h"

class UnitTestNode : public Sandbox::ISolverNode
{
public: 
    UnitTestNode(double x, double y, double z)
    {
        _location = { x,y,z };
        printf("Created node %f,%f,%f\r\n", x, y, z);
    }

    ~UnitTestNode()
    {
        printf("Deleted node \r\n");
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
    auto pSolver = Sandbox::MakeISolver();
    assert(pSolver != nullptr);

    // This NodeList class lives entirely in the solver - the testbed only has an interface pointer
    auto pNodeList = Sandbox::MakeINodeList();

    // these TestbedNodes live entirely in the testbed - the nodelist only gets interface pointers 
    pNodeList->AddNode(new UnitTestNode( 1,2,3 ));
    pNodeList->AddNode(new UnitTestNode( 2,3,4 ));
    pNodeList->AddNode(new UnitTestNode( 3,4,5 ));

    Sandbox::Vec3 centre = pSolver->CentrePoint(pNodeList.get());

    Sandbox::Vec3 expected{ 2,3,4 };

    assert(centre == expected);
}
