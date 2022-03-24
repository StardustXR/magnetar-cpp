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
	Spatial(Spatial::create(parent, pos, quat_identity, vec3_one, true, true, false, false)),
	field(this, -vec3_up * (cellCount - 1) / 2, quat_from_angles(90, 0, 0), cellCount, radius),
	input(parent, field, vec3_zero, quat_identity),
	radius(radius),
	yPos(pos.y) {

	this->cellCount = cellCount;
	for(uint i=0; i<cellCount; ++i) {
		cells.emplace_back(new WorkspaceCell(this, pos + (-vec3_up * i), radius));
	}

	grabAction.captureOnTrigger = true;
	grabAction.handActiveCondition = std::bind(&Workspaces::handInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	input.actions.push_back(&grabAction);
}

bool Workspaces::handInput(const std::string uuid, const HandInput &hand, const Datamap &datamap) {
	float grabStrength = datamap.getFloat("grabStrength");
	if(grabStrength < 0.9f)
		return false;

	if(hand.distance >= 0)
		return false;

//	vec3 handPos = hand.palm.pose.position;
//	float handHeight = std::abs(handPos.y - yPos - 0.5f);
//	if(handHeight > 0 || handHeight < -cellCount)
//		return false;
//	handPos.y = 0;
//	if(vec3_magnitude_sq(handPos) > std::pow(radius, 2))
//		return false;

	return true;
}

void Workspaces::update(double delta) {
	input.update();
	if(grabAction.actorActing) {
		float inputY = oldInputY;
		if(grabAction.actor->hand.get()) {
			inputY = grabAction.actor->hand->palm.pose.position.y;
		}
		if(grabAction.actorStarted || grabAction.actorChanged) {
			oldInputY = inputY;
			return;
		}
		yPos += inputY - oldInputY;
	setOrigin(vec3_up * yPos);
		oldInputY = inputY;

		if(grabAction.actorStarted) {
			for(auto &cell : cells) {
				cell->capture = false;
			}
		};
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
