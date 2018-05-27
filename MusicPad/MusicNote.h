//音符播放类
#pragma once

//音符结构体
struct Note
{
	int note;		//音符。1~7分别为简谱中的1~7，0：休止符
	int octave;		//升降8度。例如 0：中央C所在的8度，1:升8度，2:升两个8度，-1:降8度
	int type;		//音符类型：1：全音符，2：2分音符，4：4分音符，依此类推
	int extend_half;	//音符时值延长一半（如果为2，则延长1/2 + 1/4，为3则延长 1/2 + 1/4 + 1/8，依此类推）
	int signature;		//升降记号：0：无变化，-1：降半音，1：升半音
};

class CMusicNote
{
public:
	CMusicNote();
	~CMusicNote();
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

