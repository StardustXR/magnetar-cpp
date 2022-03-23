#include "workspaces.hpp"

#include <cmath>
#include <functional>
#include <memory>
#include <stardustxr/fusion/sk_math.hpp>
#include <stardustxr/fusion/types/input/types/handinput.hpp>
#include <string>

using namespace StardustXRFusion;
using namespace SKMath;

Workspaces::Workspaces(Spatial *parent, SKMath::vec3 pos, uint cellCount) :
	Spatial(Spatial::create(parent, pos, quat_identity, vec3_one, true, true, false, false)),
	field(this, -vec3_up * (cellCount - 1) / 2, quat_from_angles(90, 0, 0), cellCount, 1),
	input(nullptr, field, vec3_zero, quat_identity) {

	input.handHandlerMethod = std::bind(&Workspaces::handInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

	this->cellCount = cellCount;
	for(uint i=0; i<cellCount; ++i) {
		cells.emplace_back(new WorkspaceCell(this, pos + (-vec3_up * i)));
	}
}

bool Workspaces::handInput(const std::string uuid, const HandInput &hand, const Datamap &datamap) {
	if(hand.distance > 0.01f)
		return false;

	float grabStrength = datamap.getFloat("grabStrength");
	// float pinchStrength = datamap.getFloat("pinchStrength");
	// bool grabbing = grabStrength > 0.9f && pinchStrength > 0.9f;
	bool grabbing = hand.distance < 0 && grabStrength > 0.9f;
	xInteract.input(grabbing);

	if(xInteract.isActive()) {
		HandInput tempHand = hand;
		this->hand.reset(new HandInput(tempHand));
	}
	return grabbing;
}

void Workspaces::update(double delta) {
	xInteract.update();

	if(xInteract.isInteractable()){
		vec3 refPos = hand ? hand->palm.pose.position : vec3_zero;

		if(xInteract.hasActiveChanged()) {
			if(xInteract.isActive()) {
				startYPos = refPos.y - yPos;
				snapTween.t = 1;
				for(auto &cell : cells) {
					cell->capture = false;
				}
			} else {
				snapTween.start = refPos.y - startYPos;
				snapTween.end = std::round(refPos.y - startYPos);
				snapTween.t = 0;
				// setOrigin(vec3_up * snapTarget);
			}
		} else {
			if(xInteract.isActive()) {
				yPos = refPos.y - startYPos;
				setOrigin(vec3_up * yPos);
			} else {
				if(snapTween.t != snapTween.d) {
					yPos = snapTween.update(delta);
					setOrigin(vec3_up * yPos);
					if(snapTween.t + delta > snapTween.d) {
						for(auto &cell : cells) {
							cell->capture = true;
							cell->recapture();
						}
					}
				} else {

				}
			}
		}
	}
}
