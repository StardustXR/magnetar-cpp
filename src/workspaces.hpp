 #pragma once

#include <memory>

#include <stardustxr/fusion/sk_math.hpp>
#include <stardustxr/fusion/types/drawable/model.hpp>
#include <stardustxr/fusion/types/fields/cylinderfield.hpp>
#include <stardustxr/fusion/types/input/datamap.hpp>
#include <stardustxr/fusion/types/input/inputhandler.hpp>
#include <stardustxr/fusion/types/input/types/handinput.hpp>

#include <stardustxr/fusion/util/tween.hpp>

#include <vector>

#include "workspacecell.hpp"
#include "xinteract.hpp"

class Workspaces : public StardustXRFusion::Spatial {
public:
	Workspaces(StardustXRFusion::Spatial *parent, SKMath::vec3 pos, uint cellCount);

	void update(double delta);

protected:
	StardustXRFusion::CylinderField field;
	StardustXRFusion::InputHandler input;
	std::vector<std::unique_ptr<WorkspaceCell>> cells;
	uint cellCount;

	bool handInput(const std::string uuid, const StardustXRFusion::HandInput &hand, const StardustXRFusion::Datamap &datamap);
	// bool pointerInput(const StardustXRFusion::PointerInput &hand, const StardustXRFusion::Datamap &datamap);

	float yPos;
	float snapStart;
	float snapTarget;
	StardustXRFusion::Tween<float> snapTween = {0.25f, 0.25f, 0, 0, StardustXRFusion::TweenEaseOutCirc};

	XInteract xInteract;
	std::unique_ptr<StardustXRFusion::HandInput> hand = nullptr;
	float startYPos = 0;
};
