#include "workspacecell.hpp"

using namespace StardustXRFusion;

WorkspaceCell::WorkspaceCell(Spatial *parent, StardustXRFusion::Vec3 pos, float radius) :
	Spatial(parent, pos, Quat::Identity, Vec3::One, true, true, false, false),
	field(this, Vec3::Zero, glm::quat(glm::radians(glm::vec3(90, 0, 0))), 1, radius),
	zone(this, field),
	cell(this, "res/cell.glb", Vec3::Zero, Quat::Identity, Vec3{radius, 1, radius}),
	divider1(this, "res/divider.glb",  Vec3::Up*0.5f, Quat::Identity, Vec3::One * radius),
	divider2(this, "res/divider.glb", -Vec3::Up*0.5f,  Quat::Identity, Vec3::One * radius) {
	zone.onSpatialEnter = [&](Spatial &spatial) {
		if(capture)
			zone.capture(spatial);
		spatials.emplace(spatial.getNodeName(), spatial);
	};
	zone.onSpatialLeave = [&](std::string uuid) {
		spatials.erase(uuid);
	};
}

void WorkspaceCell::recapture() {
	for(auto spatialPair : spatials)
		zone.capture(spatialPair.second);
}
