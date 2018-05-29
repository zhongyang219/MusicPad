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

void CMusicSource::AddNote(const Note & note)
{
	m_note_list.push_back(note);
}

void CMusicSource::ClearList()
{
	m_note_list.clear();
}

void CMusicSource::LoadFromFile(LPCTSTR file_path)
{
	// 打开文件
	CFile file;
	BOOL bRet = file.Open(file_path, CFile::modeRead);
	if (!bRet) return;
	// 构造CArchive对象
	CArchive ar(&file, CArchive::load);
	// 读数据
	m_note_list.clear();
	size_t size{};
	Note note;
	CString temp;
	int no_use;
	try
	{
		ar >> temp;
		ar >> m_mode;
		ar >> m_full_note_time;
		ar >> size;		//读取映射容器的长度
		for (size_t i{}; i < size; i++)
		{
			ar >> note.note;
			ar >> note.octave;
			ar >> note.type;
			ar >> note.extend_half;
			ar >> note.signature;
			ar >> no_use;
			ar >> no_use;
			m_note_list.push_back(note);
		}
	}
	catch (CArchiveException* exception)
	{
		CString info;
		info.Format(_T("载入文件时发生了序列化异常，异常类型：CArchiveException，m_cause = %d。"), exception->m_cause);
		AfxMessageBox(info, MB_ICONWARNING | MB_OK);
	}
	// 关闭对象
	ar.Close();
	// 关闭文件
	file.Close();
}

bool CMusicSource::SaveToFile(LPCTSTR file_path)
{
	// 打开或者新建文件
	CFile file;
	BOOL bRet = file.Open(file_path, CFile::modeCreate | CFile::modeWrite);
	if (!bRet)		//打开文件失败
	{
		return false;
	}
	// 构造CArchive对象
	CArchive ar(&file, CArchive::store);
	// 写数据
	ar << CString("MPDSC");				//文件开关写入固定的字符
	ar << m_mode;
	ar << m_full_note_time;
	ar << m_note_list.size();		//写入映射容器的大小
	for (auto& note : m_note_list)
	{
		ar << note.note
			<< note.octave
			<< note.type
			<< note.extend_half
			<< note.signature
			<< 0		//预留
			<< 0;		//预留
	}
	// 关闭CArchive对象
	ar.Close();
	// 关闭文件
	file.Close();
	return true;
}
