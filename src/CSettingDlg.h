#pragma once


// CSettingDlg 대화 상자

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

private:
	void ReadSettingFile();
	void SaveSettingFile();
public:
	CSettingDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSettingDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

private:
	std::string m_HJPath;
	std::string m_BSPath;
public:
	virtual INT_PTR DoModal();
	virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
	virtual void PreInitDialog();
private:
	static void WriteDefaultSetting();
public:
	static std::string GetHJPath();

	static std::string GetBSPath();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
