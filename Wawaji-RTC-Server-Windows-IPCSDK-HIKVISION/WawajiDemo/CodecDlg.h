#pragma once
#include "AGButton.h"
#include "AGComboBox.h"

// CCodecDlg �Ի���

class CCodecDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCodecDlg)

public:
	CCodecDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCodecDlg();

// �Ի�������
	enum { IDD = IDD_CODEC_DIALOG };

	int GetCodecType();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtnconfirmSetup();

	DECLARE_MESSAGE_MAP()

protected:
	void InitCtrls();
	void DrawClient(CDC *lpDC);

private:
	CAGButton		m_btnConfirm;
	CAGComboBox		m_cbxCodec;

	CFont			m_ftHead;		// title
	CFont			m_ftDes;		// text in ctrl
	CFont			m_ftBtn;		// button
public:
	afx_msg void OnPaint();
};
