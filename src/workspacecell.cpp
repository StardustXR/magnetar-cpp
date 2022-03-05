#include "workspacecell.hpp"
#include <stardustxr/fusion/sk_math.hpp>

using namespace StardustXRFusion;
using namespace SKMath;

WorkspaceCell::WorkspaceCell(Spatial *parent, SKMath::vec3 pos) :
	Spatial(Spatial::create(parent, pos, quat_identity, vec3_one, true, true, false, false)),
	field(this, vec3_zero, quat_from_angles(90, 0, 0), 1, 1),
	zone(this, field),
	cell(this, "../res/cell.glb"),
	divider1(this, "../res/divider.glb"),
	divider2(this, "../res/divider.glb", -vec3_up) {
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