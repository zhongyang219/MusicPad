#pragma once
#include "MusicNote.h"

class CMusicSource
{
public:
	CMusicSource();
	~CMusicSource();
	const vector<Note>& GetNoteList() { return m_note_list; }

	//Ìí¼ÓÒ»¸öÒô·û
	void AddNote(int note, int octave, int type, int extend_half = 0, int signature = 0);

	void ClearList();

	void LoadFromFile(LPCTSTR file_path);
	void SaveFromFile(LPCTSTR file_path);
protected:
	vector<Note> m_note_list;
};

