#pragma once


// CPictureViewDlg 대화 상자
template<typename T>
class CListManager;

class CPictureViewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPictureViewDlg)
private:
	void MakePattern();
	int MakePattern2HJ( std::string& cLoadPath );
	//부성 파일로부터 패턴가져옴
	int MakePattern2BS( std::string& cLoadPath );
public:
	void SetFilePath( std::string cfilePath );
	std::string GetFilePath();
public:
	CPictureViewDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CPictureViewDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAINTVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	//virtual void OnPaint( CDC* pDC );
	virtual void OnDraw( CDC* pDC );

	DECLARE_MESSAGE_MAP()
private:
	std::string m_cFilePath;
	CListManager< CListManager<char>> m_cPatterns;
	int m_iNeedleCnt;
	CWnd* m_pParent;
public:
	afx_msg void OnPaint();
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnSizing( UINT fwSide, LPRECT pRect );
	afx_msg void OnGetMinMaxInfo( MINMAXINFO* lpMMI );
	virtual void PreInitDialog();
};
