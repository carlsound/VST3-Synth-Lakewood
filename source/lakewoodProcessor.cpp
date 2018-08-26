#include "../include/lakewoodProcessor.h"
//
namespace Carlsound 
{
	namespace Lakewood
	{
		//-----------------------------------------------------------------------------
		LakewoodProcessor::LakewoodProcessor ()
		{
			// register its editor class
			setControllerClass (LakewoodControllerUID);
			//
			mFrequencies = std::make_shared<midiFrequencies>();
			//
			mOscillatorSettings = std::make_shared<maxiSettings>();
			mOscillator = std::make_shared<maxiOsc>();
		}

		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodProcessor::initialize (FUnknown* context)
		{
			//---always initialize the parent-------
					Steinberg::tresult result = AudioEffect::initialize (context);
			if (result != Steinberg::kResultTrue)
				return Steinberg::kResultFalse;

			//---create Audio In/Out buses------
			// we want a Stereo Output
			
			addAudioOutput 
			(
				STR16 ("AudioOutput"), 
				Steinberg::Vst::SpeakerArr::kStereo
			);

			// create Event In bus (1 bus with only 1 channel)
			addEventInput 
			(
				STR16 ("EventInput"), 
				1
			);

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
			// we only support one output bus and these buses must have the same number of channels
			if (1 == numOuts)
			{
				return Steinberg::Vst::AudioEffect::setBusArrangements 
				(
					inputs, 
					numIns, 
					outputs, 
					numOuts
				);
			}
			return Steinberg::kResultFalse;
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodProcessor::setupProcessing 
		(
			Steinberg::Vst::ProcessSetup& setup
		)
		{
			// here you get, with setup, information about:
			// sampleRate, processMode, maximum number of samples per audio block
			return Steinberg::Vst::AudioEffect::setupProcessing (setup);
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodProcessor::setActive 
		(
			Steinberg::TBool state
		)
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
		template <class T>
		inline void LakewoodProcessor::outputBufferAmplitude
		(
			T outBuffer,
			const int sampleLocation,
			const double amplitudeValue
		)
		{
			outBuffer = outBuffer + sampleLocation; // pointer arithmetic
			//
			*outBuffer = amplitudeValue;
		}
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodProcessor::processInputParameterChanges
		(
			Steinberg::Vst::ProcessData& data
		)
		{
			//--- Read inputs parameter changes-----------
			if (data.inputParameterChanges)
			{
				Steinberg::int32 numParamsChanged = data.inputParameterChanges->getParameterCount();
				for (Steinberg::int32 index = 0; index < numParamsChanged; index++)
				{
					Steinberg::Vst::IParamValueQueue* paramQueue =
						data.inputParameterChanges->getParameterData(index);
					if (paramQueue)
					{
						Steinberg::Vst::ParamValue value;
						Steinberg::int32 sampleOffset;
						Steinberg::int32 numPoints = paramQueue->getPointCount();
						switch (paramQueue->getParameterId())
						{
						case LakewoodParameters::kParamQtyOctaves:
							if
								(
									paramQueue->getPoint(numPoints - 1, sampleOffset, value)
									==
									Steinberg::kResultTrue
									)
								mParam1 = value;
							break;
						}
					}
				}
			}
			return Steinberg::kResultTrue;
		}

		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodProcessor::processMidiEvents
		(
			Steinberg::Vst::ProcessData& data
		)
		{
			// get the input event queue
			Steinberg::Vst::IEventList* inputEvents = data.inputEvents;
			if (inputEvents)
			{
				Steinberg::Vst::Event event;
				Steinberg::int32 numEvents = inputEvents->getEventCount();

				// for each events check it..
				for (Steinberg::int32 i = 0; i < numEvents; i++)
				{
					if (inputEvents->getEvent(i, event) == Steinberg::kResultTrue)
					{
						switch (event.type)
						{
							//-----------------------
						case Steinberg::Vst::Event::kNoteOnEvent:
						{
							// here a note On, we may need to play something a keep a trace of the e.noteOn.noteId
							mNoteActivated = event.noteOn.pitch;
							break;
						}
						//-----------------------
						case Steinberg::Vst::Event::kNoteOffEvent:
						{
							// here we have to release the voice associated to this id : e.noteOff.noteId
							// Note that kNoteExpressionValueEvent event could be send after the note is in released
							mNoteDeactivated = event.noteOff.pitch;
							//
							if (mNoteDeactivated == mNoteActivated)
							{
								mNoteActivated = 0;
							}
							break;
						}
						//-----------------------
						case Steinberg::Vst::Event::kNoteExpressionValueEvent:
						{
							// here are the Note Expression interpretation

							// we check and use only tuning expression
							/*
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
							*/
						}
						}
					}
				}
			}
			return Steinberg::kResultTrue;
		}

		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodProcessor::processAudio
		(
			Steinberg::Vst::ProcessData& data
		)
		{
			if (0 == data.numOutputs)
			{
				// nothing to do
				return Steinberg::kResultOk;
			}

			if (data.numSamples > 0)
			{
				// Process Algorithm
				// Ex: algo.process (data.inputs[0].channelBuffers32, data.outputs[0].channelBuffers32,
				// data.numSamples);
				Steinberg::int32 numChannels = data.outputs[0].numChannels;
				//
				//---get audio buffers----------------
				Steinberg::uint32 sampleFramesSize = Steinberg::Vst::getSampleFramesSizeInBytes
				(
					processSetup,
					data.numSamples
				);
				void** out = getChannelBuffersPointer
				(
					processSetup,
					data.outputs[0]
				);
				//
				if (0 < mNoteActivated)
				{
					// mark our outputs has not silent
					data.outputs[0].silenceFlags = 0;
					//
					for (int sample = 0; sample < data.numSamples; sample++)
					{

						mAmplitude = mOscillator->sinewave(mFrequencies->getNoteFrequency(mNoteActivated));
						//
						for (int channel = 0; channel < data.outputs->numChannels; channel++)
						{
							if (data.symbolicSampleSize == Steinberg::Vst::kSample32) //32-Bit
							{
								outputBufferAmplitude
								(
									static_cast<Steinberg::Vst::Sample32*>(out[channel]),
									sample,
									mAmplitude
								);
							}
							else // 64-Bit
							{
								outputBufferAmplitude
								(
									static_cast<Steinberg::Vst::Sample64*>(out[channel]),
									sample,
									mAmplitude
								);
							}
						}
					}
				}
				else
				{
					// mark our outputs has not silent
					data.outputs[0].silenceFlags = 1;
				}
				
			}
			return Steinberg::kResultTrue;
		}

		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodProcessor::processOutputParameterChanges
		(
			Steinberg::Vst::ProcessData& data
		)
		{
			// Write outputs parameter changes-----------
			Steinberg::Vst::IParameterChanges* outParamChanges = data.outputParameterChanges;
			//
			return Steinberg::kResultTrue;
		}

		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodProcessor::process 
		(
			Steinberg::Vst::ProcessData& data
		)
		{
			processInputParameterChanges(data);
			processMidiEvents(data);
			processAudio(data);
			processOutputParameterChanges(data);
			//
			return Steinberg::kResultOk;
		}
		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodProcessor::setState 
		(
			Steinberg::IBStream* state
		)
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
			mParam1 = savedParam1;
			//
			return Steinberg::kResultOk;
		}

		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodProcessor::getState 
		(
			Steinberg::IBStream* state
		)
		{
			// here we need to save the model (preset or project)
			float toSaveParam1 = mParam1;
			//
			Steinberg::IBStreamer streamer (state, kLittleEndian);
			streamer.writeFloat (toSaveParam1);
			//
			return Steinberg::kResultOk;
		}
		//------------------------------------------------------------------------
	} // namespace Lakewood
} // namespace Carlsound
