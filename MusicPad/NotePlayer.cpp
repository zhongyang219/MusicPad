#include "stdafx.h"
#include "NotePlayer.h"


CNotePlayer::CNotePlayer()
{
}


CNotePlayer::~CNotePlayer()
{
}

void CNotePlayer::PlayNote(const Note& note)
{
	int index;		//音符以中央C为参考的序号（以半音为单位）
	int index_in_octave{};	//音符在一个八度中的序号（以半音为单位）
	switch (note.note)
	{
	case 1: index_in_octave = 0; break;
	case 2: index_in_octave = 2; break;
	case 3: index_in_octave = 4; break;
	case 4: index_in_octave = 5; break;
	case 5: index_in_octave = 7; break;
	case 6: index_in_octave = 9; break;
	case 7: index_in_octave = 11; break;
	case 0: break;
	default: return;
	}
	index_in_octave += note.signature;	//根据升降记号升降指定数量的半音
	index = m_mode + index_in_octave + note.octave * 12;
	DWORD time;		//音符的持续时间
	time = m_full_note_time / note.type;
	//音符时值延长
	for (int i = 0; i <= 31; i++)
	{
		if ((note.extend_half >> i) % 2 != 0)
			time += (m_full_note_time / note.type * (1 / std::pow(2, i + 1)));
	}
	if (note.note == 0)	//为休止符时
		Sleep(time);
	else
		PlayNoteRaw(index, time);
}

void CNotePlayer::PlayMusicSource(const vector<Note>& music_source)
{
	for (const auto& note : music_source)
	{
		PlayNote(note);
	}
}

void CNotePlayer::PlayNoteRaw(int index, DWORD dwDuration)
{
	double freq;
	freq = 261.626 * std::pow(2, (static_cast<double>(index) / 12));	//中央C的频率是261.626Hz，音符每相差一个半音，频率相差2的1/12次方倍
	Beep(static_cast<int>(freq), dwDuration);
}
