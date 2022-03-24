#include "workspacecell.hpp"
#include <stardustxr/fusion/sk_math.hpp>

using namespace StardustXRFusion;
using namespace SKMath;

WorkspaceCell::WorkspaceCell(Spatial *parent, SKMath::vec3 pos, float radius) :
	Spatial(Spatial::create(parent, pos, quat_identity, vec3_one, true, true, false, false)),
	field(this, vec3_zero, quat_from_angles(90, 0, 0), 1, radius),
	zone(this, field),
	cell(this, "../res/cell.glb", vec3_zero, quat_identity, {radius, 1, radius}),
	divider1(this, "../res/divider.glb",  vec3_up*0.5f, quat_identity, vec3_one * radius),
	divider2(this, "../res/divider.glb", -vec3_up*0.5f,  quat_identity, vec3_one * radius) {
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
	for(auto spatialPair : spatials) {
		zone.capture(spatialPair.second);
	}
}
