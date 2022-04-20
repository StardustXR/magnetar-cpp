#include "workspaces.hpp"

#include <cmath>
#include <functional>
#include <memory>
#include <stardustxr/fusion/fusion.hpp>
#include <stardustxr/fusion/sk_math.hpp>
#include <stardustxr/fusion/types/input/types/handinput.hpp>
#include <string>

using namespace StardustXRFusion;
using namespace SKMath;

Workspaces::Workspaces(Spatial *parent, SKMath::vec3 pos, uint cellCount, float radius) :
	Spatial(parent, pos, quat_identity, vec3_one, true, true, false, false),
	field(this, -vec3_up * (cellCount - 1) / 2, quat_from_angles(90, 0, 0), cellCount, radius),
	input(parent, field, vec3_zero, quat_identity),
	inRangeAction(false, true),
	grabAction(true, true, &inRangeAction),
	radius(radius),
	yPos(pos.y),
	snapTween(0.25f, 0, 0, TweenEaseOutCirc) {

	this->cellCount = cellCount;
	for(uint i=0; i<cellCount; ++i) {
		cells.emplace_back(new WorkspaceCell(this, pos + (-vec3_up * i), radius));
	}

	inRangeAction.handActiveCondition = [](const std::string uuid, const HandInput &hand, const Datamap &datamap)          { return hand.distance < 0; };
	inRangeAction.pointerActiveCondition = [](const std::string uuid, const PointerInput &pointer, const Datamap &datamap) { return pointer.distance < 0; };
	input.actions.push_back(&inRangeAction);

	grabAction.handActiveCondition = [](const std::string uuid, const HandInput &hand, const Datamap &datamap) {
		float grabStrength = datamap.getFloat("grabStrength");
		return grabStrength > 0.9f;
	};
	input.actions.push_back(&grabAction);
}

//bool Workspaces::handInput(const std::string uuid, const HandInput &hand, const Datamap &datamap) {
//	float grabStrength = datamap.getFloat("grabStrength");
//	if(grabStrength < 0.9f)
//		return false;

//	if(hand.distance >= 0)
//		return false;

//	vec3 handPos = hand.palm.pose.position;
//	float handHeight = std::abs(handPos.y - yPos - 0.5f);
//	if(handHeight > 0 || handHeight < -cellCount)
//		return false;
//	handPos.y = 0;
//	if(vec3_magnitude_sq(handPos) > std::pow(radius, 2))
//		return false;

//	return true;
//}

void Workspaces::update(double delta) {
	input.update();
	if(grabAction.actorActing) {
		float inputY = oldInputY;
		if(grabAction.actor->hand.get())
			inputY = grabAction.actor->hand->palm.pose.position.y;
		if(grabAction.actorStarted || grabAction.actorChanged) {
			oldInputY = inputY;
			for(auto &cell : cells)
				cell->capture = false;
			return;
		}
		yPos += inputY - oldInputY;
		setOrigin(vec3_up * yPos);
		oldInputY = inputY;
	} else {
		if(grabAction.actorStopped) {
			snapTween.start = yPos;
			snapTween.end = std::round(yPos);
			snapTween.t = 0;
		}

		if(snapTween.t != snapTween.d) {
			yPos = snapTween.update(delta);
			setOrigin(vec3_up * yPos);
			if(snapTween.t + delta > snapTween.d) {
				for(auto &cell : cells) {
					cell->capture = true;
					cell->recapture();
				}
			}
		}
	}
}
