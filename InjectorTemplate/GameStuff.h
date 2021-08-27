#pragma once
#include "stdafx.h"
#include "injector/injector.hpp"
#include "injector/assembly.hpp"

enum gameVersion
{
	//not implemented for this game yet
	VERSION_PLATINUM,
	VERSION_COMPLETE,
	VERSION_UNKNOWN
};
extern gameVersion version;
