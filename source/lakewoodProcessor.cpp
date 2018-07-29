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

			// create Event In bus (1 bus with only 1 channel)
			addEventInput (STR16 ("EventInput"), 1);

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
			//--- Process MIDI----------------------
			//--- ----------------------------------
			// get the input event queue
			Steinberg::Vst::IEventList* inputEvents = data.inputEvents;
			if (inputEvents)
			{
				Steinberg::Event e;
				Steinberg::int32 numEvents = inputEvents->getEventCount ();

				// for each events check it..
				for (Steinberg::int32 i = 0; i < numEvents; i++)
				{
					if (inputEvents->getEvent (i, e) == kResultTrue)
					{
						switch (e.type)
						{
							//-----------------------
							case Event::kNoteOnEvent:
							{
								// here a note On, we may need to play something a keep a trace of the e.noteOn.noteId
								break;
							}
								//-----------------------
							case Event::kNoteOffEvent:
							{
								// here we have to release the voice associated to this id : e.noteOff.noteId
								// Note that kNoteExpressionValueEvent event could be send after the note is in released
								break;
							}
								//-----------------------
							case Event::kNoteExpressionValueEvent:
							{
								// here are the Note Expression interpretation

								// we check and use only tuning expression
								if (e.noteExpressionValue.typeId == kTuningTypeID)
								{
									// we have to find the voice which should be change (the note could be in released state)
									VoiceClass* voice = findVoice (e.noteExpressionValue.noteId);
									if (voice)
									{
										// we apply to it the wanted value (for a given type of note expression (detune, volume....)
										voice->setNoteExpressionValue (e.noteExpressionValue.typeId, e.noteExpressionValue.value);
									}
									// if the associated id is not anymore marked as playing voice (end of release reached) we ignore the Note Expression Event
								}
								break;
							}
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
