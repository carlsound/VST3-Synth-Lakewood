#pragma once
//
#include "pluginterfaces/base/fstrdefs.h"
#include "pluginterfaces/base/ftypes.h"
//
// http://www.glassarmonica.com/science/frequency_midi.php
//
struct midiData
{
	//Steinberg::Vst::ParamID noteValue;
	const Steinberg::Vst::TChar *noteName;
	Steinberg::Vst::ParamValue noteFrequency;
};
//
class midiFrequencies
{
public:
	midiFrequencies()
	{
		for (int i = 0; i < 128; i++)
		{
			//mMidiNoteList[i].noteValue = (Steinberg::Vst::ParamID) i;
			//mMidiNoteList[i].noteFrequency = (Steinberg::Vst::ParamValue) (27.5 * 2 ^ ((i - 21) / 12));
			mMidiNoteList[i].noteName = STR16("note");
			mMidiNoteList[i].noteFrequency = 0.0;
		}
		//
		mMidiNoteList[21].noteName = STR16("A0");
		mMidiNoteList[21].noteFrequency = 27.5;
		mMidiNoteList[22].noteName = STR16("A#0");
		mMidiNoteList[22].noteFrequency = 29.1;
		mMidiNoteList[23].noteName = STR16("B0");
		mMidiNoteList[23].noteFrequency = 30.9;
		//
		mMidiNoteList[24].noteName = STR16("C1");
		mMidiNoteList[24].noteFrequency = 32.7;
		mMidiNoteList[25].noteName = STR16("C#1");
		mMidiNoteList[25].noteFrequency = 34.6;
		mMidiNoteList[26].noteName = STR16("D1");
		mMidiNoteList[26].noteFrequency = 36.7;
		mMidiNoteList[27].noteName = STR16("D#1");
		mMidiNoteList[27].noteFrequency = 38.9;
		mMidiNoteList[28].noteName = STR16("E1");
		mMidiNoteList[28].noteFrequency = 41.2;
		mMidiNoteList[29].noteName = STR16("F1");
		mMidiNoteList[29].noteFrequency = 43.7;
		mMidiNoteList[30].noteName = STR16("F#1");
		mMidiNoteList[30].noteFrequency = 46.2;
		mMidiNoteList[31].noteName = STR16("G1");
		mMidiNoteList[31].noteFrequency = 49.0;
		mMidiNoteList[32].noteName = STR16("G#1");
		mMidiNoteList[32].noteFrequency = 51.9;
		mMidiNoteList[33].noteName = STR16("A1");
		mMidiNoteList[33].noteFrequency = 55.0;
		mMidiNoteList[34].noteName = STR16("A#1");
		mMidiNoteList[34].noteFrequency = 58.3;
		mMidiNoteList[35].noteName = STR16("B1");
		mMidiNoteList[35].noteFrequency = 61.7;
		//
		mMidiNoteList[36].noteName = STR16("C2");
		mMidiNoteList[36].noteFrequency = 65.4;
		mMidiNoteList[37].noteName = STR16("C#2");
		mMidiNoteList[37].noteFrequency = 69.3;
		mMidiNoteList[38].noteName = STR16("D2");
		mMidiNoteList[38].noteFrequency = 73.4;
		mMidiNoteList[39].noteName = STR16("D#2");
		mMidiNoteList[39].noteFrequency = 77.8;
		mMidiNoteList[40].noteName = STR16("E2");
		mMidiNoteList[40].noteFrequency = 82.4;
		mMidiNoteList[41].noteName = STR16("F2");
		mMidiNoteList[41].noteFrequency = 87.3;
		mMidiNoteList[42].noteName = STR16("F#2");
		mMidiNoteList[42].noteFrequency = 92.5;
		mMidiNoteList[43].noteName = STR16("G2");
		mMidiNoteList[43].noteFrequency = 98.0;
		mMidiNoteList[44].noteName = STR16("G#2");
		mMidiNoteList[44].noteFrequency = 103.8;
		mMidiNoteList[45].noteName = STR16("A2");
		mMidiNoteList[45].noteFrequency = 110.0;
		mMidiNoteList[46].noteName = STR16("A#2");
		mMidiNoteList[46].noteFrequency = 116.5;
		mMidiNoteList[47].noteName = STR16("B2");
		mMidiNoteList[47].noteFrequency = 123.5;
		//
		mMidiNoteList[48].noteName = STR16("C3");
		mMidiNoteList[48].noteFrequency = 130.8;
		mMidiNoteList[49].noteName = STR16("C#3");
		mMidiNoteList[49].noteFrequency = 138.6;
		mMidiNoteList[50].noteName = STR16("D3");
		mMidiNoteList[50].noteFrequency = 146.8;
		mMidiNoteList[51].noteName = STR16("D#3");
		mMidiNoteList[51].noteFrequency = 155.6;
		mMidiNoteList[52].noteName = STR16("E3");
		mMidiNoteList[52].noteFrequency = 164.8;
		mMidiNoteList[53].noteName = STR16("F3");
		mMidiNoteList[53].noteFrequency = 174.6;
		mMidiNoteList[54].noteName = STR16("F#3");
		mMidiNoteList[54].noteFrequency = 185.0;
		mMidiNoteList[55].noteName = STR16("G3");
		mMidiNoteList[55].noteFrequency = 196.0;
		mMidiNoteList[56].noteName = STR16("G#3");
		mMidiNoteList[56].noteFrequency = 207.7;
		mMidiNoteList[57].noteName = STR16("A3");
		mMidiNoteList[57].noteFrequency = 220.0;
		mMidiNoteList[58].noteName = STR16("A#3");
		mMidiNoteList[58].noteFrequency = 233.1;
		mMidiNoteList[59].noteName = STR16("B3");
		mMidiNoteList[59].noteFrequency = 246.9;
		//
		mMidiNoteList[60].noteName = STR16("C4"); // middle C
		mMidiNoteList[60].noteFrequency = 261.6;
		mMidiNoteList[61].noteName = STR16("C#4");
		mMidiNoteList[61].noteFrequency = 277.2;
		mMidiNoteList[62].noteName = STR16("D4");
		mMidiNoteList[62].noteFrequency = 293.7;
		mMidiNoteList[63].noteName = STR16("D#4");
		mMidiNoteList[63].noteFrequency = 311.1;
		mMidiNoteList[64].noteName = STR16("E4");
		mMidiNoteList[64].noteFrequency = 329.6;
		mMidiNoteList[65].noteName = STR16("F4");
		mMidiNoteList[65].noteFrequency = 349.2;
		mMidiNoteList[66].noteName = STR16("F#4");
		mMidiNoteList[66].noteFrequency = 370.0;
		mMidiNoteList[67].noteName = STR16("G4");
		mMidiNoteList[67].noteFrequency = 392.0;
		mMidiNoteList[68].noteName = STR16("G#4");
		mMidiNoteList[68].noteFrequency = 415.3;
		mMidiNoteList[69].noteName = STR16("A4");
		mMidiNoteList[69].noteFrequency = 440.0;
		mMidiNoteList[70].noteName = STR16("A#4");
		mMidiNoteList[70].noteFrequency = 466.2;
		mMidiNoteList[71].noteName = STR16("B4");
		mMidiNoteList[71].noteFrequency = 493.9;
		//
		mMidiNoteList[72].noteName = STR16("C5");
		mMidiNoteList[72].noteFrequency = 523.3;
		mMidiNoteList[73].noteName = STR16("C#5");
		mMidiNoteList[73].noteFrequency = 554.4;
		mMidiNoteList[74].noteName = STR16("D5");
		mMidiNoteList[74].noteFrequency = 587.3;
		mMidiNoteList[75].noteName = STR16("D#5");
		mMidiNoteList[75].noteFrequency = 622.3;
		mMidiNoteList[76].noteName = STR16("E5");
		mMidiNoteList[76].noteFrequency = 659.3;
		mMidiNoteList[77].noteName = STR16("F5");
		mMidiNoteList[77].noteFrequency = 698.5;
		mMidiNoteList[78].noteName = STR16("F#5");
		mMidiNoteList[78].noteFrequency = 740.0;
		mMidiNoteList[79].noteName = STR16("G5");
		mMidiNoteList[79].noteFrequency = 784.0;
		mMidiNoteList[80].noteName = STR16("G#5");
		mMidiNoteList[80].noteFrequency = 830.6;
		mMidiNoteList[81].noteName = STR16("A5");
		mMidiNoteList[81].noteFrequency = 880.0;
		mMidiNoteList[82].noteName = STR16("A#5");
		mMidiNoteList[82].noteFrequency = 932.3;
		mMidiNoteList[83].noteName = STR16("B5");
		mMidiNoteList[83].noteFrequency = 987.8;
		//
		mMidiNoteList[84].noteName = STR16("C6");
		mMidiNoteList[84].noteFrequency = 1046.5;
		mMidiNoteList[85].noteName = STR16("C#6");
		mMidiNoteList[85].noteFrequency = 1108.7;
		mMidiNoteList[86].noteName = STR16("D6");
		mMidiNoteList[86].noteFrequency = 1174.7;
		mMidiNoteList[87].noteName = STR16("D#6");
		mMidiNoteList[87].noteFrequency = 1244.5;
		mMidiNoteList[88].noteName = STR16("E6");
		mMidiNoteList[88].noteFrequency = 1318.5;
		mMidiNoteList[89].noteName = STR16("F6");
		mMidiNoteList[89].noteFrequency = 1396.9;
		mMidiNoteList[90].noteName = STR16("F#6");
		mMidiNoteList[90].noteFrequency = 1480.0;
		mMidiNoteList[91].noteName = STR16("G6");
		mMidiNoteList[91].noteFrequency = 1568.0;
		mMidiNoteList[92].noteName = STR16("G#6");
		mMidiNoteList[92].noteFrequency = 1661.2;
		mMidiNoteList[93].noteName = STR16("A6");
		mMidiNoteList[93].noteFrequency = 1760.0;
		mMidiNoteList[94].noteName = STR16("A#6");
		mMidiNoteList[94].noteFrequency = 1864.7;
		mMidiNoteList[95].noteName = STR16("B6");
		mMidiNoteList[95].noteFrequency = 1975.5;
		//
		mMidiNoteList[96].noteName = STR16("C7");
		mMidiNoteList[96].noteFrequency = 2093.0;
		mMidiNoteList[97].noteName = STR16("C#7");
		mMidiNoteList[97].noteFrequency = 2217.5;
		mMidiNoteList[98].noteName = STR16("D7");
		mMidiNoteList[98].noteFrequency = 2349.3;
		mMidiNoteList[99].noteName = STR16("D#7");
		mMidiNoteList[99].noteFrequency = 2489.0;
		mMidiNoteList[100].noteName = STR16("E7");
		mMidiNoteList[100].noteFrequency = 2637.0;
		mMidiNoteList[101].noteName = STR16("F7");
		mMidiNoteList[101].noteFrequency = 2793.8;
		mMidiNoteList[102].noteName = STR16("F#7");
		mMidiNoteList[102].noteFrequency = 2960.0;
		mMidiNoteList[103].noteName = STR16("G7");
		mMidiNoteList[103].noteFrequency = 3136.0;
		mMidiNoteList[104].noteName = STR16("G#7");
		mMidiNoteList[104].noteFrequency = 3322.4;
		mMidiNoteList[105].noteName = STR16("A7");
		mMidiNoteList[105].noteFrequency = 3520.0;
		mMidiNoteList[106].noteName = STR16("A#7");
		mMidiNoteList[106].noteFrequency = 3729.3;
		mMidiNoteList[107].noteName = STR16("B7");
		mMidiNoteList[107].noteFrequency = 3951.1;
		//
		mMidiNoteList[108].noteName = STR16("C8");
		mMidiNoteList[108].noteFrequency = 4186.0;
	}
	//
	Steinberg::Vst::ParamValue getNoteFrequency(Steinberg::Vst::ParamID note)
	{
		return mMidiNoteList[note].noteFrequency;
	}
protected:
	midiData mMidiNoteList[128];
};