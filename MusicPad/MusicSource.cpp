#include "stdafx.h"
#include "MusicSource.h"


CMusicSource::CMusicSource()
{
}


CMusicSource::~CMusicSource()
{
}

void CMusicSource::AddNote(int note, int octave, int type, int extend_half, int signature)
{
	Note music_note;
	music_note.note = note;
	music_note.octave = octave;
	music_note.type = type;
	music_note.extend_half = extend_half;
	music_note.signature = signature;
	m_note_list.push_back(music_note);
}

void CMusicSource::ClearList()
{
	m_note_list.clear();
}

void CMusicSource::LoadFromFile(LPCTSTR file_path)
{
}

void CMusicSource::SaveFromFile(LPCTSTR file_path)
{
}
