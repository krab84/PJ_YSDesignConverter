#pragma once


// ConverterFileSearch 대화 상자

class ConverterFileSearch : public CDialogEx
{
	DECLARE_DYNAMIC(ConverterFileSearch)

public:
	ConverterFileSearch(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ConverterFileSearch();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();

private:
	int ConvertHJ2BS( std::string& cLoadPath, std::string& cSavePath );
	int ConvertBS2HJ( std::string& cLoadPath, std::string& cSavePath );
	int ConvertHJ2HJ( std::string& cLoadPath, std::string& cSavePath );
private:
	//CEdit m_PathEdit;
};
