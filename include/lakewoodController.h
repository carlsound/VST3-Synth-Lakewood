#pragma once
//
#include "base/source/fstreamer.h"
//
#include "public.sdk/source/vst/vsteditcontroller.h"
//
#include "pluginterfaces/base/ibstream.h"
#include "pluginterfaces/vst/ivsteditcontroller.h"
#include "pluginterfaces/vst/ivstmidicontrollers.h"
#include "pluginterfaces/vst/ivstnoteexpression.h"
//
#include "lakewoodParameters.h"
//
namespace Carlsound
{
	namespace Lakewood 
	{
		//-----------------------------------------------------------------------------
	class LakewoodController : public Steinberg::Vst::EditController, 
		                       //public Steinberg::Vst::INoteExpressionController
		                       public Steinberg::Vst::IMidiMapping
		{
		public:

			OBJ_METHODS(LakewoodController, EditController)
			//
			DEFINE_INTERFACES
				//DEF_INTERFACE(INoteExpressionController)
				DEF_INTERFACE(IMidiMapping)
			END_DEFINE_INTERFACES(EditController)
			//
			REFCOUNT_METHODS(EditController)

		//------------------------------------------------------------------------
		// create function required for Plug-in factory,
		// it will be called to create new instances of this controller
		//------------------------------------------------------------------------
			static Steinberg::FUnknown* createInstance
			(
				void*
			)
			{
				return (Steinberg::Vst::IEditController*)new LakewoodController ();
			}

			//---from IPluginBase--------
			Steinberg::tresult PLUGIN_API initialize 
			(
				FUnknown* context
			) SMTG_OVERRIDE;

			//---from EditController-----
			Steinberg::tresult PLUGIN_API setComponentState 
			(
				Steinberg::IBStream* state
			) SMTG_OVERRIDE;

			//---from IVstEditController---
			/*
			Steinberg::tresult PLUGIN_API getMidiControllerAssignment
			(
					Steinberg::int32 	busIndex,
					Steinberg::int16 	channel,
					Steinberg::Vst::CtrlNumber 	midiControllerNumber,
					Steinberg::Vst::ParamID ParamID & 	id
			) SMTG_OVERRIDE;
			*/

			//---from IMidiMapping---
			virtual Steinberg::tresult PLUGIN_API getMidiControllerAssignment
			(
				Steinberg::int32 busIndex, 
				Steinberg::int16 channel, 
				Steinberg::Vst::CtrlNumber midiControllerNumber, 
				Steinberg::Vst::ParamID& id
			) override;

			/*
			//---from INoteExpressionController
			Steinberg::int32 PLUGIN_API getNoteExpressionCount
			(
				Steinberg::int32 busIndex, 
				Steinberg::int16 channel
			)SMTG_OVERRIDE;

			Steinberg::tresult PLUGIN_API getNoteExpressionInfo
			(
				Steinberg::int32 busIndex, 
				Steinberg::int16 channel, 
				Steinberg::int32 noteExpressionIndex, 
				Steinberg::Vst::NoteExpressionTypeInfo& info
			)SMTG_OVERRIDE;

			Steinberg::tresult PLUGIN_API getNoteExpressionStringByValue
			(
				Steinberg::int32 busIndex, 
				Steinberg::int16 channel, 
				Steinberg::Vst::NoteExpressionTypeID id, 
				Steinberg::Vst::NoteExpressionValue valueNormalized, 
				Steinberg::Vst::String128 string
			) SMTG_OVERRIDE;

			Steinberg::tresult PLUGIN_API getNoteExpressionValueByString
			(
				Steinberg::int32 busIndex, 
				Steinberg::int16 channel, 
				Steinberg::Vst::NoteExpressionTypeID id, 
				const Steinberg::Vst::TChar* string, 
				Steinberg::Vst::NoteExpressionValue& valueNormalized
			) SMTG_OVERRIDE;
			*/
	};

//------------------------------------------------------------------------
	} // namespace Lakewood
} // namespace Carlsound
