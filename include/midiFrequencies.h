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
	midiData midiNoteList[128];
	//
public:
	midiFrequencies()
	{
		for (int i = 0; i < 128; i++)
		{
			//midiNoteList[i].noteValue = (Steinberg::Vst::ParamID) i;
			//midiNoteList[i].noteFrequency = (Steinberg::Vst::ParamValue) (27.5 * 2 ^ ((i - 21) / 12));
		}
		//
		midiNoteList[21].noteName = STR16("A0");
		midiNoteList[21].noteFrequency = 27.5;
		midiNoteList[22].noteName = STR16("A#0");
		midiNoteList[22].noteFrequency = 29.1;
		midiNoteList[23].noteName = STR16("B0");
		midiNoteList[23].noteFrequency = 30.9;
		//
		midiNoteList[24].noteName = STR16("C1");
		midiNoteList[24].noteFrequency = 32.7;
		midiNoteList[25].noteName = STR16("C#1");
		midiNoteList[25].noteFrequency = 34.6;
		midiNoteList[26].noteName = STR16("D1");
		midiNoteList[26].noteFrequency = 36.7;
		midiNoteList[27].noteName = STR16("D#1");
		midiNoteList[27].noteFrequency = 38.9;
		midiNoteList[28].noteName = STR16("E1");
		midiNoteList[28].noteFrequency = 41.2;
		midiNoteList[29].noteName = STR16("F1");
		midiNoteList[29].noteFrequency = 43.7;
		midiNoteList[30].noteName = STR16("F#1");
		midiNoteList[30].noteFrequency = 46.2;
		midiNoteList[31].noteName = STR16("G1");
		midiNoteList[31].noteFrequency = 49.0;
		midiNoteList[32].noteName = STR16("G#1");
		midiNoteList[32].noteFrequency = 51.9;
		midiNoteList[33].noteName = STR16("A1");
		midiNoteList[33].noteFrequency = 55.0;
		midiNoteList[34].noteName = STR16("A#1");
		midiNoteList[34].noteFrequency = 58.3;
		midiNoteList[35].noteName = STR16("B1");
		midiNoteList[35].noteFrequency = 61.7;
		//
		midiNoteList[36].noteName = STR16("C2");
		midiNoteList[36].noteFrequency = 65.4;
		midiNoteList[37].noteName = STR16("C#2");
		midiNoteList[37].noteFrequency = 69.3;
		midiNoteList[38].noteName = STR16("D2");
		midiNoteList[38].noteFrequency = 73.4;
		midiNoteList[39].noteName = STR16("D#2");
		midiNoteList[39].noteFrequency = 77.8;
		midiNoteList[40].noteName = STR16("E2");
		midiNoteList[40].noteFrequency = 82.4;
		midiNoteList[41].noteName = STR16("F2");
		midiNoteList[41].noteFrequency = 87.3;
		midiNoteList[42].noteName = STR16("F#2");
		midiNoteList[42].noteFrequency = 92.5;
		midiNoteList[43].noteName = STR16("G2");
		midiNoteList[43].noteFrequency = 98.0;
		midiNoteList[44].noteName = STR16("G#2");
		midiNoteList[44].noteFrequency = 103.8;
		midiNoteList[45].noteName = STR16("A2");
		midiNoteList[45].noteFrequency = 110.0;
		midiNoteList[46].noteName = STR16("A#2");
		midiNoteList[46].noteFrequency = 116.5;
		midiNoteList[47].noteName = STR16("B2");
		midiNoteList[47].noteFrequency = 123.5;
		//
		midiNoteList[48].noteName = STR16("C3");
		midiNoteList[48].noteFrequency = 130.8;
		midiNoteList[49].noteName = STR16("C#3");
		midiNoteList[49].noteFrequency = 138.6;
		midiNoteList[50].noteName = STR16("D3");
		midiNoteList[50].noteFrequency = 146.8;
		midiNoteList[51].noteName = STR16("D#3");
		midiNoteList[51].noteFrequency = 155.6;
		midiNoteList[52].noteName = STR16("E3");
		midiNoteList[52].noteFrequency = 164.8;
		midiNoteList[53].noteName = STR16("F3");
		midiNoteList[53].noteFrequency = 174.6;
		midiNoteList[54].noteName = STR16("F#3");
		midiNoteList[54].noteFrequency = 185.0;
		midiNoteList[55].noteName = STR16("G3");
		midiNoteList[55].noteFrequency = 196.0;
		midiNoteList[56].noteName = STR16("G#3");
		midiNoteList[56].noteFrequency = 207.7;
		midiNoteList[57].noteName = STR16("A3");
		midiNoteList[57].noteFrequency = 220.0;
		midiNoteList[58].noteName = STR16("A#3");
		midiNoteList[58].noteFrequency = 233.1;
		midiNoteList[59].noteName = STR16("B3");
		midiNoteList[59].noteFrequency = 246.9;
		//
		midiNoteList[60].noteName = STR16("C4"); // middle C
		midiNoteList[60].noteFrequency = 261.6;
		midiNoteList[61].noteName = STR16("C#4");
		midiNoteList[61].noteFrequency = 277.2;
		midiNoteList[62].noteName = STR16("D4");
		midiNoteList[62].noteFrequency = 293.7;
		midiNoteList[63].noteName = STR16("D#4");
		midiNoteList[63].noteFrequency = 311.1;
		midiNoteList[64].noteName = STR16("E4");
		midiNoteList[64].noteFrequency = 329.6;
		midiNoteList[65].noteName = STR16("F4");
		midiNoteList[65].noteFrequency = 349.2;
		midiNoteList[66].noteName = STR16("F#4");
		midiNoteList[66].noteFrequency = 370.0;
		midiNoteList[67].noteName = STR16("G4");
		midiNoteList[67].noteFrequency = 392.0;
		midiNoteList[68].noteName = STR16("G#4");
		midiNoteList[68].noteFrequency = 415.3;
		midiNoteList[69].noteName = STR16("A4");
		midiNoteList[69].noteFrequency = 440.0;
		midiNoteList[70].noteName = STR16("A#4");
		midiNoteList[70].noteFrequency = 466.2;
		midiNoteList[71].noteName = STR16("B4");
		midiNoteList[71].noteFrequency = 493.9;
		//
		midiNoteList[72].noteName = STR16("C5");
		midiNoteList[72].noteFrequency = 523.3;
		midiNoteList[73].noteName = STR16("C#5");
		midiNoteList[73].noteFrequency = 554.4;
		midiNoteList[74].noteName = STR16("D5");
		midiNoteList[74].noteFrequency = 587.3;
		midiNoteList[75].noteName = STR16("D#5");
		midiNoteList[75].noteFrequency = 622.3;
		midiNoteList[76].noteName = STR16("E5");
		midiNoteList[76].noteFrequency = 659.3;
		midiNoteList[77].noteName = STR16("F5");
		midiNoteList[77].noteFrequency = 698.5;
		midiNoteList[78].noteName = STR16("F#5");
		midiNoteList[78].noteFrequency = 740.0;
		midiNoteList[79].noteName = STR16("G5");
		midiNoteList[79].noteFrequency = 784.0;
		midiNoteList[80].noteName = STR16("G#5");
		midiNoteList[80].noteFrequency = 830.6;
		midiNoteList[81].noteName = STR16("A5");
		midiNoteList[81].noteFrequency = 880.0;
		midiNoteList[82].noteName = STR16("A#5");
		midiNoteList[82].noteFrequency = 932.3;
		midiNoteList[83].noteName = STR16("B5");
		midiNoteList[83].noteFrequency = 987.8;
		//
		midiNoteList[84].noteName = STR16("C6");
		midiNoteList[84].noteFrequency = 1046.5;
		midiNoteList[85].noteName = STR16("C#6");
		midiNoteList[85].noteFrequency = 1108.7;
		midiNoteList[86].noteName = STR16("D6");
		midiNoteList[86].noteFrequency = 1174.7;
		midiNoteList[87].noteName = STR16("D#6");
		midiNoteList[87].noteFrequency = 1244.5;
		midiNoteList[88].noteName = STR16("E6");
		midiNoteList[88].noteFrequency = 1318.5;
		midiNoteList[89].noteName = STR16("F6");
		midiNoteList[89].noteFrequency = 1396.9;
		midiNoteList[90].noteName = STR16("F#6");
		midiNoteList[90].noteFrequency = 1480.0;
		midiNoteList[91].noteName = STR16("G6");
		midiNoteList[91].noteFrequency = 1568.0;
		midiNoteList[92].noteName = STR16("G#6");
		midiNoteList[92].noteFrequency = 1661.2;
		midiNoteList[93].noteName = STR16("A6");
		midiNoteList[93].noteFrequency = 1760.0;
		midiNoteList[94].noteName = STR16("A#6");
		midiNoteList[94].noteFrequency = 1864.7;
		midiNoteList[95].noteName = STR16("B6");
		midiNoteList[95].noteFrequency = 1975.5;
		//
		midiNoteList[96].noteName = STR16("C7");
		midiNoteList[96].noteFrequency = 2093.0;
		midiNoteList[97].noteName = STR16("C#7");
		midiNoteList[97].noteFrequency = 2217.5;
		midiNoteList[98].noteName = STR16("D7");
		midiNoteList[98].noteFrequency = 2349.3;
		midiNoteList[99].noteName = STR16("D#7");
		midiNoteList[99].noteFrequency = 2489.0;
		midiNoteList[100].noteName = STR16("E7");
		midiNoteList[100].noteFrequency = 2637.0;
		midiNoteList[101].noteName = STR16("F7");
		midiNoteList[101].noteFrequency = 2793.8;
		midiNoteList[102].noteName = STR16("F#7");
		midiNoteList[102].noteFrequency = 2960.0;
		midiNoteList[103].noteName = STR16("G7");
		midiNoteList[103].noteFrequency = 3136.0;
		midiNoteList[104].noteName = STR16("G#7");
		midiNoteList[104].noteFrequency = 3322.4;
		midiNoteList[105].noteName = STR16("A7");
		midiNoteList[105].noteFrequency = 3520.0;
		midiNoteList[106].noteName = STR16("A#7");
		midiNoteList[106].noteFrequency = 3729.3;
		midiNoteList[107].noteName = STR16("B7");
		midiNoteList[107].noteFrequency = 3951.1;
		//
		midiNoteList[108].noteName = STR16("C8");
		midiNoteList[108].noteFrequency = 4186.0;
	}
	//
	Steinberg::Vst::ParamValue getNoteFrequency(Steinberg::Vst::ParamID note)
	{
		return midiNoteList[note].noteFrequency;
	}
};