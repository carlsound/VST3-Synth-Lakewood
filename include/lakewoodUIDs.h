#pragma once

#include "public.sdk/samples/vst/mda-vst3/source/mdaParameter.h"

namespace Carlsound
{
	namespace Lakewood 
	{

		// HERE are defined the parameter Ids which are exported to the host
		/*
		enum LakewoodParams : Steinberg::Vst::ParamID
		{
			kBypassId = 100,
			//
			kParamVolId = 102,
			kParamOnId = 1000
		};
		 */
		
		// HERE you have to define new unique class ids: for processor and for controller
		// you can use GUID creator tools like https://www.guidgenerator.com/
		static const Steinberg::FUID LakewoodProcessorUID 
		(
			0x8059AB5E,
			0x21BE45F6,
			0xAA8A964C,
			0xB9C159C3
		);
		//
		static const Steinberg::FUID LakewoodControllerUID 
		(
			0x0A1E04AC,
			0x69DA417D,
			0x81990A5B,
			0x451DFD0B
		);
		
		//------------------------------------------------------------------------
	} // namespace Lakewood
} // namespace Carlsound
