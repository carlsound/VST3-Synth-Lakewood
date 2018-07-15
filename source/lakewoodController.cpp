
#include "../include/lakewoodController.h"
#include "../include/lakewoodIDs.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/base/ibstream.h"

namespace Carlsound 
{
	namespace Lakewood 
	{
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodController::initialize (FUnknown* context)
		{
			Steinberg::tresult result = EditController::initialize (context);
			if (result == Steinberg::kResultTrue)
			{
				//---Create Parameters------------
				parameters.addParameter
				(
					STR16 ("Bypass"), 
					0, 
					1, 
					0,
					Steinberg::Vst::ParameterInfo::kCanAutomate | Steinberg::Vst::ParameterInfo::kIsBypass,
					LakewoodParams::kBypassId
				);

				parameters.addParameter 
				(
					STR16 ("Parameter 1"), STR16 ("dB"), 
					0, 
					.5,
					Steinberg::Vst::ParameterInfo::kCanAutomate,
					LakewoodParams::kParamVolId, 
					0,
					STR16 ("Param1")
				);
				parameters.addParameter 
				(
					STR16 ("Parameter 2"), 
					STR16 ("On/Off"), 
					1, 
					1.,
					Steinberg::Vst::ParameterInfo::kCanAutomate,
					LakewoodParams::kParamOnId, 
					0,			
					STR16 ("Param2")
				);
			}
			return Steinberg::kResultTrue;
		}

		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodController::setComponentState (Steinberg::IBStream* state)
		{
			// we receive the current state of the component (processor part)
			// we read our parameters and bypass value...
			if (!state)
				return Steinberg::kResultFalse;
		
			Steinberg::IBStreamer streamer (state, kLittleEndian);
		
			float savedParam1 = 0.f;
			if (streamer.readFloat (savedParam1) == false)
			{
				return Steinberg::kResultFalse;
			}	
			setParamNormalized (LakewoodParams::kParamVolId, savedParam1);
			//
			Steinberg::int8 savedParam2 = 0;
			if (streamer.readInt8(savedParam2) == false)
			{
				return Steinberg::kResultFalse;
			}
			setParamNormalized (LakewoodParams::kParamOnId, savedParam2);
		
			// read the bypass
			Steinberg::int32 bypassState;
			if (streamer.readInt32(bypassState) == false)
			{
				return Steinberg::kResultFalse;
			}
			setParamNormalized (kBypassId, bypassState ? 1 : 0);
			//
			return Steinberg::kResultOk;
		}
		
	//------------------------------------------------------------------------
	} // namespace Lakewood
} // namespace Carlsound
