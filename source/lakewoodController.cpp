
#include "../include/lakewoodController.h"
//
namespace Carlsound 
{
	namespace Lakewood 
	{
		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodController::initialize 
		(
			FUnknown* context
		)
		{
			Steinberg::tresult result = EditController::initialize (context);
			if (result == Steinberg::kResultTrue)
			{
				//---Create Parameters------------
				parameters.addParameter //public.sdk/source/vst/vstparameters.cpp
				(
					STR16 ("Qty."), // title
					STR16("Octaves"), // units
					2, // int32 step count
					0.0, // ParamValue default normalized value
					Steinberg::Vst::ParameterInfo::kCanAutomate, // flags
					LakewoodParameters::kParamQtyOctaves // int32 tag
					// UnitID
					// const TChar* short title
				);

			}
			return Steinberg::kResultTrue;
		}

		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodController::setComponentState 
		(
			Steinberg::IBStream* state
		)
		{
			// we receive the current state of the component (processor part)
			// we read our parameters and bypass value...
			if (!state)
				return Steinberg::kResultFalse;
		
			Steinberg::IBStreamer streamer (state, kLittleEndian);
		
			float savedParameter1 = 0.f;
			if (streamer.readFloat (savedParameter1) == false)
			{
				return Steinberg::kResultFalse;
			}	
			setParamNormalized (LakewoodParameters::kParamQtyOctaves, savedParameter1);

			//
			// read the bypass
			/*
			Steinberg::int32 bypassState;
			if (streamer.readInt32(bypassState) == false)
			{
				return Steinberg::kResultFalse;
			}
			setParamNormalized (kBypassId, bypassState ? 1 : 0);
			*/
			//
			return Steinberg::kResultOk;
		}

		
		//------------------------------------------------------------------------
		Steinberg::Vst::ParamValue PLUGIN_API LakewoodController::normalizedParamToPlain
		(
			Steinberg::Vst::ParamID tag,
			Steinberg::Vst::ParamValue valueNormalized
		)
		{
			if (kParamQtyOctaves == tag)
			{
				return (valueNormalized * 2);
			}
			else
			{
				return valueNormalized;
			}
		}

		//------------------------------------------------------------------------
		void string128copy(Steinberg::Vst::TChar *str128, std::string &str)
		{
			for (int i = 0; i < str.length(); i++)
			{
				str128[i] = str[i];
			}
			str128[str.length()] = '\0';
		}

		//------------------------------------------------------------------------
		Steinberg::Vst::ParamValue PLUGIN_API LakewoodController::plainParamToNormalized
		(
			Steinberg::Vst::ParamID tag,
			Steinberg::Vst::ParamValue value
		)
		{
			if (kParamQtyOctaves == tag)
			{
				return (value / 2.0);
			}
			else
			{
				return value;
			}
		}

		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodController::getParamStringByValue
		(
			Steinberg::Vst::ParamID tag,
			Steinberg::Vst::ParamValue valueNormalized,
			Steinberg::Vst::String128 string
		)
		{
			std::string valuePlainAscii;
			//
			if (kParamQtyOctaves == tag)
			{
				float valuePlain = (valueNormalized * 2);
				//
				valuePlainAscii = std::to_string(valuePlain) + '\0';
				string128copy(string, valuePlainAscii);
			}
			return Steinberg::kResultOk;
		}
		

		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodController::getMidiControllerAssignment
		(
			Steinberg::int32 busIndex,
			Steinberg::int16 channel,
			Steinberg::Vst::CtrlNumber midiControllerNumber,
			Steinberg::Vst::ParamID& id
		)
		{
			//throw std::logic_error("The method or operation is not implemented.");
			if (busIndex == 0 && channel == 0)
			{
				id = 0;
				switch (midiControllerNumber)
				{
					//case Steinberg::Vst::ControllerNumbers::kPitchBend: id = kParamMasterTuning; break;
					//case Steinberg::Vst::ControllerNumbers::kCtrlVolume: id = kParamMasterVolume; break;
					//case Steinberg::Vst::ControllerNumbers::kCtrlFilterCutoff: id = kParamFilterFreq; break;
					//case Steinberg::Vst::ControllerNumbers::kCtrlFilterResonance: id = kParamFilterQ; break;
					//
					case Steinberg::Vst::ControllerNumbers::kCtrlGPC1:
					{
						id = kParamQtyOctaves;
						break;
					}
				}
				return id != 0 ? Steinberg::kResultTrue : Steinberg::kResultFalse;
			}
			return Steinberg::kResultFalse;
		}
		
		/*
		//-----------------------------------------------------------------------------
		//------------------------------------------------------------------------
		Steinberg::int32 LakewoodController::getNoteExpressionCount
		(
			Steinberg::int32 busIndex, 
			Steinberg::int16 channel
		)
		{
			// we accept only the first bus and 1 channel
			if (busIndex == 0 && channel == 0)
				return 1;
			return 0;
		}

		//------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodController::getNoteExpressionInfo
		(
			Steinberg::int32 busIndex, 
			Steinberg::int16 channel,
			Steinberg::int32 noteExpressionIndex,
			Steinberg::Vst::NoteExpressionTypeInfo& info
		)
		{
			// we accept only the first bus and 1 channel 
			// and only 1 Note Expression (tuning)
			if (busIndex == 0 && channel == 0 && noteExpressionIndex == 0)
			{
				memset
				(
					&info, 
					0, 
					sizeof(Steinberg::Vst::NoteExpressionTypeInfo)
				);
				// set the tuning type
				info.typeId = Steinberg::Vst::kTuningTypeID;
				// set some strings
				USTRING("Tuning").copyTo(info.title, 128);
				USTRING("Tun").copyTo(info.shortTitle, 128);
				USTRING("Half Tone").copyTo(info.units, 128);
				info.unitID = -1; // no unit wanted
				info.associatedParameterID = -1; // no associated parameter wanted
				info.flags = Steinberg::Vst::NoteExpressionTypeInfo::kIsBipolar; // event is bipolar (centered)
																 // for Tuning the convert functions are : plain = 240 * (norm - 0.5); norm = plain / 240 + 0.5;
																 // we want to support only +/- one octave
				double kNormTuningOneOctave = 12.0 / 240.0;
				info.valueDesc.minimum = 0.5 - kNormTuningOneOctave;
				info.valueDesc.maximum = 0.5 + kNormTuningOneOctave;
				info.valueDesc.defaultValue = 0.5; // middle of [0, 1] => no detune (240 * (0.5 - 0.5) = 0)
				info.valueDesc.stepCount = 0; // we want continuous (no step)

				return Steinberg::kResultTrue;
			}
			return Steinberg::kResultFalse;
		}

		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodController::getNoteExpressionStringByValue
		(
			Steinberg::int32 busIndex, 
			Steinberg::int16 channel,
			Steinberg::Vst::NoteExpressionTypeID id,
			Steinberg::Vst::NoteExpressionValue valueNormalized,
			Steinberg::Vst::String128 string
		);
		{
			// here we use the id (not the index)
			if (busIndex == 0 && channel == 0 && id == kTuningTypeID)
			{
				// here we have to convert a normalized value to a Tuning string representation
				UString128 wrapper;
				valueNormalized = (240 * valueNormalized) - 120; // compute half Tones
				wrapper.printFloat(valueNormalized, 2);
				wrapper.copyTo(string, 128);

				return Steinberg::kResultTrue;
			}
			return Steinberg::kResultFalse;
		}

		//-----------------------------------------------------------------------------
		Steinberg::tresult PLUGIN_API LakewoodController::getNoteExpressionValueByString
		(
			Steinberg::int32 busIndex, 
			Steinberg::int16 channel, 
			Steinberg::Vst::NoteExpressionTypeID id,
			const Steinberg::Vst::TChar* string, 
			Steinberg::Vst::NoteExpressionValue& valueNormalized
		);
		{
			// here we use the id (not the index)
			if (busIndex == 0 && channel == 0 && id == kTuningTypeID)
			{
				// here we have to convert a given tuning string (half Tone) to a normalized value
				String wrapper((TChar*)string);
				ParamValue tmp;
				if (wrapper.scanFloat(tmp))
				{
					valueNormalized = (tmp + 120) / 240;
					return Steinberg::kResultTrue;
				}
			}
			return Steinberg::kResultFalse;
		}

		*/

		//-----------------------------------------------------------------------------

	//------------------------------------------------------------------------
	} // namespace Lakewood
} // namespace Carlsound
