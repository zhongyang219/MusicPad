//音符播放类
#pragma once
#include "Common.h"

class CNotePlayer
{
public:
	CNotePlayer();
	~CNotePlayer();
	void SetMode(int mode) { m_mode = mode; }	//设置调式
	void SetFullNoteTime(int full_note_time) { m_full_note_time = full_note_time; }		//设置全音符的时间

	//播放一个音符
	void PlayNote(const Note& note);

	//播放一系列音符
	void PlayMusicSource(const vector<Note>& music_source);

private:
	//播放一个音符，index为以中央C为参考的序号，index相差1音符相差一个半音；dwDuration为播放时间
	void PlayNoteRaw(int index, DWORD dwDuration);

	int m_mode{};		//调式。0~11：C C#/Db D D#/Eb E F F#/Gb G G#/Ab A A#/Bb B
	int m_full_note_time{ 2000 };	//一个全音符的时间，单位为毫秒
};

