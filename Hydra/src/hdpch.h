#ifndef HD_PCH_H
#define HD_PCH_H


#include "Hydra/Core/PlatformDetection.h"

#ifdef HD_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
		#define NOMINMAX
	#endif
#endif


#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Hydra/Core/Base.h"

#include "Hydra/Core/Log.h"

#include "Hydra/Debug/Instrumentor.h"

#ifdef HD_PLATFORM_WINDOWS
    #include <Windows.h>
#endif

#endif // HD_PCH_H