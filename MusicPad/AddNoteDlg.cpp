// CAddNoteDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MusicPad.h"
#include "AddNoteDlg.h"
#include "afxdialogex.h"


// CAddNoteDlg 对话框

IMPLEMENT_DYNAMIC(CAddNoteDlg, CDialog)

CAddNoteDlg::CAddNoteDlg(Note note, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ADD_NOTE_DIALOG, pParent), m_note{ note }
{

}

CAddNoteDlg::~CAddNoteDlg()
{
}

void CAddNoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NOTE_NAME_EDIT, m_note_name_edit);
	DDX_Control(pDX, IDC_NOTE_OCTAVE_EDIT, m_octave_edit);
	DDX_Control(pDX, IDC_NOTE_TYPE_EDIT, m_note_type_edit);
	DDX_Control(pDX, IDC_NOTE_SIGNATURE_EDIT, m_signature_edit);
}


BEGIN_MESSAGE_MAP(CAddNoteDlg, CDialog)
END_MESSAGE_MAP()


// CAddNoteDlg 消息处理程序


BOOL CAddNoteDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//
	m_note_name_edit.SetRange(0, 7);
	m_note_name_edit.SetValue(m_note.note);
	m_note_name_edit.SetLimitText(1);

	m_octave_edit.SetRange(-4, 4);
	m_octave_edit.SetValue(m_note.octave);
	m_octave_edit.SetLimitText(2);

	m_note_type_edit.SetRange(1, 512);
	m_note_type_edit.SetValue(m_note.type);
	m_note_type_edit.SetLimitText(3);

	m_signature_edit.SetRange(-2, 2);
	m_signature_edit.SetValue(m_note.signature);
	m_signature_edit.SetLimitText(1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CAddNoteDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_note.note = m_note_name_edit.GetValue();
	m_note.octave = m_octave_edit.GetValue();
	m_note.type = m_note_type_edit.GetValue();
	m_note.extend_half = 0;
	if (((CButton*)GetDlgItem(IDC_EXTERND2_CHECK))->GetCheck() != 0)
		m_note.extend_half |= 0x0001;
	if (((CButton*)GetDlgItem(IDC_EXTERND4_CHECK))->GetCheck() != 0)
		m_note.extend_half |= 0x0002;
	if (((CButton*)GetDlgItem(IDC_EXTERND8_CHECK))->GetCheck() != 0)
		m_note.extend_half |= 0x0004;
	if (((CButton*)GetDlgItem(IDC_EXTERND16_CHECK))->GetCheck() != 0)
		m_note.extend_half |= 0x0008;
	m_note.signature = m_signature_edit.GetValue();
	CDialog::OnOK();
}
