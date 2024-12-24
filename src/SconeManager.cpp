#include "SconeManager.h"

void SconeManager::addScone(std::unique_ptr<Scone> i_pScone)
{
	Scones.push_back(std::move(i_pScone));
}
