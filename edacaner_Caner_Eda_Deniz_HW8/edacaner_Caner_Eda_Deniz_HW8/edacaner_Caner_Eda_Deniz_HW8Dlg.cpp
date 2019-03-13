
// edacaner_Caner_Eda_Deniz_HW8Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "edacaner_Caner_Eda_Deniz_HW8.h"
#include "edacaner_Caner_Eda_Deniz_HW8Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cedacaner_Caner_Eda_Deniz_HW8Dlg dialog



Cedacaner_Caner_Eda_Deniz_HW8Dlg::Cedacaner_Caner_Eda_Deniz_HW8Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cedacaner_Caner_Eda_Deniz_HW8Dlg::IDD, pParent)
	, option(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cedacaner_Caner_Eda_Deniz_HW8Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, textInput);
	DDX_Control(pDX, IDC_EDIT2, keyInput);
	DDX_Control(pDX, IDC_COMBO1, rotateInput);
	DDX_Control(pDX, IDC_LIST1, outputResult);
	DDX_Radio(pDX, IDC_RADIO1, option);
}

BEGIN_MESSAGE_MAP(Cedacaner_Caner_Eda_Deniz_HW8Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &Cedacaner_Caner_Eda_Deniz_HW8Dlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &Cedacaner_Caner_Eda_Deniz_HW8Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO1, &Cedacaner_Caner_Eda_Deniz_HW8Dlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &Cedacaner_Caner_Eda_Deniz_HW8Dlg::OnBnClickedRadio2)
END_MESSAGE_MAP()


// Cedacaner_Caner_Eda_Deniz_HW8Dlg message handlers

BOOL Cedacaner_Caner_Eda_Deniz_HW8Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Cedacaner_Caner_Eda_Deniz_HW8Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Cedacaner_Caner_Eda_Deniz_HW8Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Cedacaner_Caner_Eda_Deniz_HW8Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cedacaner_Caner_Eda_Deniz_HW8Dlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	//#1015

	// TODO:  Add your control notification handler code here
}

int maxSize = 0;
bool control = true;

bool check(CString & cText,CString & cKey)
{
	for (int i=0; i < cText.GetLength(); i++)
	{
		if (cText[i] < '0' || cText[i] > '9' )
		{
			return false;
		}
	}

	for (int i=0; i < cKey.GetLength(); i++)
	{
		if (cKey[i] < '0' || cKey[i] > '9' )
		{
			return false;
		}
	}
	return true;
}

void Cedacaner_Caner_Eda_Deniz_HW8Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CString cText, cKey, cRotate, cResult;
	unsigned int textUnsigned, keyUnsigned, result ;

	//get a DC
	CDC *pDC = GetDC();
	//select the listbox font into the dc
	CSize cz;

	textInput.GetWindowTextW(cText);
	keyInput.GetWindowTextW(cKey);
	rotateInput.GetWindowTextW(cRotate);

	textUnsigned = _tcstoul(cText,nullptr,10);
	keyUnsigned =  _tcstoul(cKey,nullptr,10);

	if(check(cText, cKey))
	{

		if(cRotate == "No Rotation" )
		{
			result = keyUnsigned ^ textUnsigned;
			cResult.Format(_T("%u"), result);

			if(control == true)
			{
				cResult= cText+" encrypted with "+cKey+" using "+cRotate+": "+ cResult;
			}
			else
			{
				cResult= cText+" decrypted with "+cKey+" using "+cRotate+": "+ cResult;
			}
		}
		else if(cRotate == "Rotate Left 1")
		{
			keyUnsigned = keyUnsigned << 1;
			result = keyUnsigned ^ textUnsigned;
			cResult.Format(_T("%u"), result);

			if(control == true)
			{
				cResult= cText+" encrypted with "+cKey+" using "+cRotate+": "+ cResult;
			}
			else 
			{
				cResult= cText+" decrypted with "+cKey+" using "+cRotate+": "+ cResult;
			}
		}
		else if(cRotate == "Rotate Right 1")
		{
			keyUnsigned = keyUnsigned >> 1;
			result = keyUnsigned ^ textUnsigned;
			cResult.Format(_T("%u"), result);

			if(control == true)
			{
				cResult= cText+" encrypted with "+cKey+" using "+cRotate+": "+ cResult;
			}
			else
			{
				cResult= cText+" decrypted with "+cKey+" using "+cRotate+": "+ cResult;
			}
		}
		else
		{
			outputResult.AddString(_T("Wrong input. Try again."));
			result = 0;
		}
	}
	else
	{
		outputResult.AddString(_T("Wrong input. Try again."));
	}

	outputResult.AddString(cResult);

	cz = pDC->GetTextExtent(cResult);// Returns the size of the string to cz object
	if(cz.cx > maxSize)// cz.cx keeps the horizontal length of the string. We compare
		maxSize = cz.cx; // it with maxSize and update the maxSize if the condition
	// is satisfied

	keyInput.SetWindowTextW(_T(""));
	textInput.SetWindowTextW(_T(""));
	outputResult.SetHorizontalExtent(maxSize);
}


void Cedacaner_Caner_Eda_Deniz_HW8Dlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	control = true;
}


void Cedacaner_Caner_Eda_Deniz_HW8Dlg::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	control = false;
}
