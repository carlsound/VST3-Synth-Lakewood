#include "../include/lakewoodProcessor.h"
#include "../include/lakewoodIDs.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/base/ibstream.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"

namespace Carlsound 
{
	namespace Lakewood
	{
		//-----------------------------------------------------------------------------
		LakewoodProcessor::LakewoodProcessor ()
		{
			// register its editor class
			setControllerClass (MyControllerUID);
		}

		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodProcessor::initialize (FUnknown* context)
		{
			//---always initialize the parent-------
					Steinberg::tresult result = AudioEffect::initialize (context);
			if (result != Steinberg::kResultTrue)
				return Steinberg::kResultFalse;

			//---create Audio In/Out buses------
			// we want a stereo Input and a Stereo Output
			addAudioInput (STR16 ("AudioInput"), Steinberg::Vst::SpeakerArr::kStereo);
			addAudioOutput (STR16 ("AudioOutput"), Steinberg::Vst::SpeakerArr::kStereo);

			return Steinberg::kResultTrue;
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodProcessor::setBusArrangements 
		(
			Steinberg::Vst::SpeakerArrangement* inputs,
			Steinberg::int32 numIns,
			Steinberg::Vst::SpeakerArrangement* outputs,
			Steinberg::int32 numOuts
		)
		{
			// we only support one in and output bus and these buses must have the same number of channels
			if (numIns == 1 && numOuts == 1 && inputs[0] == outputs[0])
			{
				return Steinberg::Vst::AudioEffect::setBusArrangements (inputs, numIns, outputs, numOuts);
			}
			return Steinberg::kResultFalse;
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodProcessor::setupProcessing (Steinberg::Vst::ProcessSetup& setup)
		{
			// here you get, with setup, information about:
			// sampleRate, processMode, maximum number of samples per audio block
			return Steinberg::Vst::AudioEffect::setupProcessing (setup);
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodProcessor::setActive (Steinberg::TBool state)
		{
			if (state) // Initialize
			{
				// Allocate Memory Here
				// Ex: algo.create ();
			}
			else // Release
			{
				// Free Memory if still allocated
				// Ex: if(algo.isCreated ()) { algo.destroy (); }
			}
			return Steinberg::Vst::AudioEffect::setActive (state);
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodProcessor::process (Steinberg::Vst::ProcessData& data)
		{
			//--- Read inputs parameter changes-----------
			if (data.inputParameterChanges)
			{
				Steinberg::int32 numParamsChanged = data.inputParameterChanges->getParameterCount ();
				for (Steinberg::int32 index = 0; index < numParamsChanged; index++)
				{
					Steinberg::Vst::IParamValueQueue* paramQueue =
						data.inputParameterChanges->getParameterData (index);
					if (paramQueue)
					{
						Steinberg::Vst::ParamValue value;
						Steinberg::int32 sampleOffset;
						Steinberg::int32 numPoints = paramQueue->getPointCount ();
						switch (paramQueue->getParameterId ())
						{
							case LakewoodParams::kParamVolId:
								if (paramQueue->getPoint (numPoints - 1, sampleOffset, value) ==
									Steinberg::kResultTrue)
									mParam1 = value;
								break;
							case LakewoodParams::kParamOnId:
								if (paramQueue->getPoint (numPoints - 1, sampleOffset, value) ==
									Steinberg::kResultTrue)
									mParam2 = value > 0 ? 1 : 0;
								break;
							case LakewoodParams::kBypassId:
								if (paramQueue->getPoint (numPoints - 1, sampleOffset, value) ==
									Steinberg::kResultTrue)
									mBypass = (value > 0.5f);
								break;
						}
					}
				}
			}

			//--- Process Audio---------------------
			//--- ----------------------------------
			if (data.numInputs == 0 || data.numOutputs == 0)
			{
				// nothing to do
				return Steinberg::kResultOk;
			}

			if (data.numSamples > 0)
			{
				// Process Algorithm
				// Ex: algo.process (data.inputs[0].channelBuffers32, data.outputs[0].channelBuffers32,
				// data.numSamples);
			}
			return Steinberg::kResultOk;
		}
		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodProcessor::setState (Steinberg::IBStream* state)
		{
			if (!state)
				return Steinberg::kResultFalse;

			// called when we load a preset or project, the model has to be reloaded
			//
			Steinberg::IBStreamer streamer (state, kLittleEndian);
			//
			float savedParam1 = 0.f;
			if (streamer.readFloat(savedParam1) == false)
			{
				return Steinberg::kResultFalse;
			}
			//
			Steinberg::int32 savedParam2 = 0;
			if (streamer.readInt32(savedParam2) == false)
			{
				return Steinberg::kResultFalse;
			}
			//
			Steinberg::int32 savedBypass = 0;
			if (streamer.readInt32(savedBypass) == false)
			{
				return Steinberg::kResultFalse;
			}
			//
			mParam1 = savedParam1;
			mParam2 = savedParam2 > 0 ? 1 : 0;
			mBypass = savedBypass > 0;
			//
			return Steinberg::kResultOk;
		}
		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodProcessor::getState (Steinberg::IBStream* state)
		{
			// here we need to save the model (preset or project)
			float toSaveParam1 = mParam1;
			Steinberg::int32 toSaveParam2 = mParam2;
			Steinberg::int32 toSaveBypass = mBypass ? 1 : 0;
			//
			Steinberg::IBStreamer streamer (state, kLittleEndian);
			streamer.writeFloat (toSaveParam1);
			streamer.writeInt32 (toSaveParam2);
			streamer.writeInt32 (toSaveBypass);
			//
			return Steinberg::kResultOk;
		}
		//------------------------------------------------------------------------
	} // namespace Lakewood
} // namespace Carlsound
