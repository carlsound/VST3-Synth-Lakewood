#pragma once

#include "pluginterfaces/vst/vsttypes.h"

namespace Carlsound
{
	namespace Lakewood
	{
		//-----------------------------------------------------------------------------
		// Global Parameters
		//-----------------------------------------------------------------------------
		// HERE are defined the parameter Ids which are exported to the host
		enum LakewoodParameters : Steinberg::Vst::ParamID
		{
			kParamQtyOctaves,
			//
			kNumGlobalParameters
		};
	} // namespace Lakewood
} // namespace Carlsound