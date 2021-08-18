#include "pch.h"
#include <iostream>
#include "catch.hpp"
#include "Solver.h"


class UnitTestNode : public Sandbox::ISolverNode
{
public: 
    UnitTestNode(double x, double y, double z)
    {
        _x = x;
        _y = y;
        _z = z;
    }

    virtual Sandbox::Vec3 GetLocation() const
    {
        return Sandbox::Vec3{_x,_y,_z};
    }
private:
    double _x;
    double _y;
    double _z;
};

bool operator==(const Sandbox::Vec3& left, const Sandbox::Vec3& right)
{
    return  left.x == right.x &&
            left.y == right.y &&
            left.z == right.z;
}


SCENARIO("Solver tests") {

    GIVEN("No manual setup") {
        auto pSolver = Sandbox::MakeISolver();
        THEN("Solver should instantiate automatically") {
            CHECK(pSolver != nullptr);
        }
    }

    GIVEN("No manual setup") {
        auto pNodeList = Sandbox::MakeINodeList();
        THEN("NodeList should instantiate automatically") {
            CHECK(pNodeList != nullptr);
        }
    }

	GIVEN("A solver and a bunch of coordinates") {
	
        auto pSolver = Sandbox::MakeISolver();
        auto pNodeList = Sandbox::MakeINodeList();

        pNodeList->AddNode(new UnitTestNode( 1,2,3 ));
        pNodeList->AddNode(new UnitTestNode( 2,3,4 ));
        pNodeList->AddNode(new UnitTestNode( 3,4,5 ));

        Sandbox::Vec3 centre = pSolver->CentrePoint(pNodeList.get());

        Sandbox::Vec3 expected{ 2,3,4 };

		THEN("The centre point should be as expected") {
			CHECK((centre == expected));
		}
	}
}