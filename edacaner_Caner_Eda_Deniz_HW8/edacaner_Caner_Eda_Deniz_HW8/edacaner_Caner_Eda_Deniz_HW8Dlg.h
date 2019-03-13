
// edacaner_Caner_Eda_Deniz_HW8Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// Cedacaner_Caner_Eda_Deniz_HW8Dlg dialog
class Cedacaner_Caner_Eda_Deniz_HW8Dlg : public CDialogEx
{
// Construction
public:
	Cedacaner_Caner_Eda_Deniz_HW8Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_EDACANER_CANER_EDA_DENIZ_HW8_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	CEdit textInput;
	CEdit keyInput;
	CComboBox rotateInput;
	CListBox outputResult;
	afx_msg void OnBnClickedButton1();
	int option;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
};
