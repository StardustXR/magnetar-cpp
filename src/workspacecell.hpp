#pragma once

#include <memory>

#include <stardustxr/fusion/sk_math.hpp>
#include <stardustxr/fusion/types/fields/cylinderfield.hpp>
#include <stardustxr/fusion/types/input/datamap.hpp>
#include <stardustxr/fusion/types/input/inputhandler.hpp>
#include <stardustxr/fusion/types/input/types/handinput.hpp>
#include <stardustxr/fusion/types/drawable/model.hpp>
#include <stardustxr/fusion/types/spatial/zone.hpp>

#include "tween.hpp"
#include "xinteract.hpp"

class WorkspaceCell : public StardustXRFusion::Spatial {
public:
	WorkspaceCell(StardustXRFusion::Spatial *parent, SKMath::vec3 pos);

	bool capture = true;
	void recapture();

protected:
	StardustXRFusion::CylinderField field;
	StardustXRFusion::Zone zone;
	StardustXRFusion::Model cell;
	StardustXRFusion::Model divider1;
	StardustXRFusion::Model divider2;

	bool handInput(const StardustXRFusion::HandInput &hand, const StardustXRFusion::Datamap &datamap);
	// bool pointerInput(const StardustXRFusion::PointerInput &hand, const StardustXRFusion::Datamap &datamap);

	std::map<std::string, Spatial> spatials;
};
