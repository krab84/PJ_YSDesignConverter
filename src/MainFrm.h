
// MainFrm.h: CMainFrame 클래스의 인터페이스
//

#pragma once

class CPictureViewDlg;

class CMainFrame : public CFrameWnd
{
	static const int MAX_PICTUREVIEW_CNT = 10;

protected: // serialization에서만 만들어집니다.
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void On32772();
	afx_msg void OnClickPictureOpen();

private:
	//최대 10개
	CPictureViewDlg* m_pCPictureViewDlg[MAX_PICTUREVIEW_CNT];
	bool		m_bIsAlivePictureDlg[MAX_PICTUREVIEW_CNT];
public:
	afx_msg void OnClickSetting();
	afx_msg void On3277();
	afx_msg void OnOnclick_OpenHJ();
	afx_msg void OnOnclick_OpenBS();
};


