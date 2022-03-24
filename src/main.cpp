#include <stardustxr/fusion/sk_math.hpp>
#include <stardustxr/fusion/fusion.hpp>
#include <stardustxr/fusion/types/spatial/spatial.hpp>

#include "workspaces.hpp"

using namespace StardustXRFusion;
using namespace SKMath;

double elapsedTime = 0;

int main(int, char *[]) {
	StardustXRFusion::Setup();

	Workspaces workspaces(Root(), vec3_zero, 3, 1);

	OnLogicStep([&](double delta, double) {
		elapsedTime += delta;
		workspaces.update(delta);
	});
	StardustXRFusion::StallMainThread();
}
