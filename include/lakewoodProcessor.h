#pragma once
//
#include "maximilian.h"
//
#include "base/source/fstreamer.h"
#include "pluginterfaces/base/ibstream.h"
#include "pluginterfaces/vst/ivstevents.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "public.sdk/source/vst/vstaudioeffect.h"
#include "public.sdk/source/vst/vstaudioprocessoralgo.h"
//
#include "lakewoodParameters.h"
#include "../include/lakewoodUIDs.h"
#include "midiFrequencies.h"
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
	
		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API initialize 
		(
			FUnknown* context
		) SMTG_OVERRIDE;

		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API setBusArrangements 
		(
			Steinberg::Vst::SpeakerArrangement* inputs, 
			Steinberg::int32 numIns,
			Steinberg::Vst::SpeakerArrangement* outputs, 
			Steinberg::int32 numOuts
		
		) SMTG_OVERRIDE;

		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API setupProcessing 
		(
			Steinberg::Vst::ProcessSetup& setup
		) SMTG_OVERRIDE;
		
		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API setActive 
		(
			Steinberg::TBool state
		) SMTG_OVERRIDE;
		
		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API process 
		(
			Steinberg::Vst::ProcessData& data
		) SMTG_OVERRIDE;

		Steinberg::tresult PLUGIN_API processInputParameterChanges
		(
			Steinberg::Vst::ProcessData& data
		);

		Steinberg::tresult PLUGIN_API processMidiEvents
		(
			Steinberg::Vst::ProcessData& data
		);

		Steinberg::tresult PLUGIN_API processAudio
		(
			Steinberg::Vst::ProcessData& data
		);

		Steinberg::tresult PLUGIN_API processOutputParameterChanges
		(
			Steinberg::Vst::ProcessData& data
		);
	
		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API setState 
		(
			Steinberg::IBStream* state
		) SMTG_OVERRIDE;
		
		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API getState 
		(
			Steinberg::IBStream* state
		) SMTG_OVERRIDE;

		//------------------------------------------------------------------------
		static FUnknown* createInstance (void*)
		{
			return (Steinberg::Vst::IAudioProcessor*)new LakewoodProcessor ();
		}
	
		//------------------------------------------------------------------------
		template <class T>
		void outputBufferAmplitude
		(
			T outBuffer,
			const int sampleLocation,
			const double amplitudeValue
		);
		//------------------------------------------------------------------------
		//------------------------------------------------------------------------
		//------------------------------------------------------------------------
		protected:
			Steinberg::Vst::ParamValue mParamQtyOctavesNormalized = 0;
			Steinberg::int32 mParamQtyOctavesPlain = 0;
			//Steinberg::int16 mParam2 = 0;
			//bool mBypass = false;
			Steinberg::int32 mNoteActivated = 0;
			Steinberg::int32 mNoteDeactivated = 0;
			//
			std::shared_ptr<midiFrequencies> mFrequencies;
			//
			std::shared_ptr<maxiSettings> mOscillatorSettings[3];
			std::shared_ptr<maxiOsc> mOscillator[3];
			//
			double mAmplitude;
		};
		
	//------------------------------------------------------------------------
	} // namespace Lakewood
} // namespace Carlsound
