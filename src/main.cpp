#include <stardustxr/fusion/values/glm.hpp>
#include <stardustxr/fusion/fusion.hpp>
#include <stardustxr/fusion/types/spatial/spatial.hpp>

#include "workspaces.hpp"

using namespace StardustXRFusion;

double elapsedTime = 0;

int main(int, char *[]) {
	StardustXRFusion::Setup();

	Workspaces workspaces(Root(), Vec3::Zero, 3, 1);

	OnLogicStep([&](double delta, double) {
		elapsedTime += delta;
		workspaces.update(delta);
	});
	StardustXRFusion::RunEventLoop();
}
