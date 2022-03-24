#include "singleactoraction.hpp"

using namespace StardustXRFusion;

void SingleActorAction::update() {
	InputActionHandler::Action::update();

	if(startedActing.size() > 0) {
		if(actorActing)
			actorChanged = true;
		else
			actorStarted = true;
		actorActing = true;
		actor = (startedActing.end()-1).base();
		actorUUID = actor->uuid;
		return;
	}

	if(!actorActing && actor)
		actor = nullptr;
	auto stoppedActor = std::find(stoppedActing.begin(), stoppedActing.end(), actorUUID);
	if(actorActing && stoppedActor != stoppedActing.end()) {
		actor = stoppedActor.base();
		actorUUID = "";
		actorActing = false;
		actorStopped = true;
		return;
	}

	actorChanged = false;
	actorStarted = false;
	actorStopped = false;

	if(actorActing)
		actor = std::find(activelyActing.begin(), activelyActing.end(), actorUUID).base();
}
