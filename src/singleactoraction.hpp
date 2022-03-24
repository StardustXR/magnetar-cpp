#pragma once

#include <stardustxr/fusion/types/input/types/handinput.hpp>
#include <stardustxr/fusion/types/input/types/pointerinput.hpp>
#include <stardustxr/fusion/types/input/inputactionhandler.hpp>

struct SingleActorAction : public StardustXRFusion::InputActionHandler::Action {
	bool actorStarted = false;
	bool actorActing  = false;
	bool actorChanged = false;
	bool actorStopped = false;

	StardustXRFusion::InputActionHandler::InputMethod *actor = nullptr;

protected:
	void update();
	std::string actorUUID;
};
