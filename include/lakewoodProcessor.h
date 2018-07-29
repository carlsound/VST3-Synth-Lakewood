#pragma once
//
#include "maximilian.h"
//
#include "public.sdk/source/vst/vstaudioeffect.h"
#include "pluginterfaces/vst/ivstevents.h"
#include "public.sdk/samples/vst/note_expression_synth/source/note_expression_synth_voice.h"
#include "public.sdk/samples/vst/common/voiceprocessor.h"
//
namespace Carlsound 
{
	namespace Lakewood 
	{
	//-----------------------------------------------------------------------------
	class LakewoodProcessor : public Steinberg::Vst::AudioEffect
	{
	public:
		LakewoodProcessor ();
	
		Steinberg::tresult PLUGIN_API initialize
		(
				FUnknown* context
				) SMTG_OVERRIDE;
		Steinberg::tresult PLUGIN_API setBusArrangements
		(
				Steinberg::Vst::SpeakerArrangement* inputs,
				Steinberg::int32 numIns,
				Steinberg::Vst::SpeakerArrangement* outputs,
				Steinberg::int32 numOuts
				) SMTG_OVERRIDE;

		Steinberg::tresult PLUGIN_API setupProcessing
		(
				Steinberg::Vst::ProcessSetup& setup
				) SMTG_OVERRIDE;
		Steinberg::tresult PLUGIN_API setActive
		(
				Steinberg::TBool state
				) SMTG_OVERRIDE;
		Steinberg::tresult PLUGIN_API process
		(
				Steinberg::Vst::ProcessData& data
				) SMTG_OVERRIDE;
	
		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API setState
		(
				Steinberg::IBStream* state
				) SMTG_OVERRIDE;
		Steinberg::tresult PLUGIN_API getState
		(
				Steinberg::IBStream* state
				) SMTG_OVERRIDE;

		static FUnknown* createInstance
		(
				void*
				)
		{
			return (Steinberg::Vst::IAudioProcessor*)new LakewoodProcessor ();
		}
	
		protected:
			Steinberg::Vst::ParamValue mParam1 = 0;
			Steinberg::int16 mParam2 = 0;
			bool mBypass = false;

			Steinberg::Vst::VoiceProcessor* voiceProcessor;
		};
		
	//------------------------------------------------------------------------
	} // namespace Lakewood
} // namespace Carlsound
