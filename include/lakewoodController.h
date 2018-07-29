#pragma once

#include "public.sdk/source/vst/vsteditcontroller.h"
#include "pluginterfaces/vst/ivsteditcontroller.h"

namespace Carlsound
{
	namespace Lakewood 
	{
		//-----------------------------------------------------------------------------
	class LakewoodController : public Steinberg::Vst::EditController, Steinberg::Vst::IMidiMapping
		{
		public:
		//------------------------------------------------------------------------
		// create function required for Plug-in factory,
		// it will be called to create new instances of this controller
		//------------------------------------------------------------------------
			static Steinberg::FUnknown* createInstance (void*)
			{
				return (Steinberg::Vst::IEditController*)new LakewoodController ();
			}
		
			//---from IPluginBase--------
			Steinberg::tresult PLUGIN_API initialize (FUnknown* context) SMTG_OVERRIDE;

			//---from EditController-----
			Steinberg::tresult PLUGIN_API setComponentState (Steinberg::IBStream* state) SMTG_OVERRIDE;

			//---from IVstEditController---
			Steinberg::tresult PLUGIN_API getMidiControllerAssignment
			(
					Steinberg::int32 	busIndex,
					Steinberg::int16 	channel,
					Steinberg::Vst::CtrlNumber 	midiControllerNumber,
					Steinberg::Vst::ParamID ParamID & 	id
			) SMTG_OVERRIDE;
		};

//------------------------------------------------------------------------
	} // namespace Lakewood
} // namespace Carlsound
