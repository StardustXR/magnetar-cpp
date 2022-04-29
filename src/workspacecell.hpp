#pragma once

#include <memory>

#include <stardustxr/fusion/values/glm.hpp>
#include <stardustxr/fusion/types/fields/cylinderfield.hpp>
#include <stardustxr/fusion/types/input/datamap.hpp>
#include <stardustxr/fusion/types/input/inputhandler.hpp>
#include <stardustxr/fusion/types/input/types/handinput.hpp>
#include <stardustxr/fusion/types/drawable/model.hpp>
#include <stardustxr/fusion/types/spatial/zone.hpp>

class WorkspaceCell : public StardustXRFusion::Spatial {
public:
	WorkspaceCell(StardustXRFusion::Spatial *parent, StardustXRFusion::Vec3 pos, float radius);

	bool capture = true;
	void recapture();

protected:
	StardustXRFusion::CylinderField field;
	StardustXRFusion::Zone zone;
	StardustXRFusion::Model cell;
	StardustXRFusion::Model divider1;
	StardustXRFusion::Model divider2;

	std::map<std::string, Spatial> spatials;
};
