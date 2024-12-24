#pragma once
#include "SconeManager.h"
#include <memory>
class Scone : public SconeManager
{

public:
	Scone(std::shared_ptr<SconeManager> i_pSconeManager);

private:
	std::shared_ptr<SconeManager> m_pSconeManager;
};

