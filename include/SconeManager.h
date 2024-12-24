#pragma once
#include "Scone.h"
#include <iostream>
#include <vector>
#include <memory>
class SconeManager
{
public:
	void addScone(std::unique_ptr<Scone> i_pScone);

private:
	std::vector<std::shared_ptr<Scone>> Scones;

};

