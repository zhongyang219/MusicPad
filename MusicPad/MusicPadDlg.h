
// MusicPadDlg.h: 头文件
//

#pragma once
#include "MusicSource.h"
#include "Common.h"


// CMusicPadDlg 对话框
class CMusicPadDlg : public CDialog
{
// 构造
public:
	CMusicPadDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MUSICPAD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	//控件变量
	CListCtrl m_note_list_ctrl;

	//
	CMusicSource m_music_source;
	CMusicNote m_music_note;

	void ShowNoteList();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPlayButton();
};
