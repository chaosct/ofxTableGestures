#pragma once

//Define ONLY_SIMULATOR to build a simulator-only view, with custom settings

#ifdef ONLY_SIMULATOR

#ifndef ONLY_SIMULATOR_NOBJECTS
	#define ONLY_SIMULATOR_NOBJECTS 3
#endif
#ifndef ONLY_SIMULATOR_ENABLE_ANGLE
	#define ONLY_SIMULATOR_ENABLE_ANGLE false
#endif

#endif
