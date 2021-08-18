
namespace Sandbox
{

	struct Vec3
	{
		double x;
		double y;
		double z;
	};

	struct ISolverNode
	{
		virtual ~ISolverNode() {}
		virtual Vec3 GetLocation() const = 0;
	};

}