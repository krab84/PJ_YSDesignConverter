
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication4.h"

#include "MainFrm.h"

#include "ConverterFileSearch.h"

#include "CPictureViewDlg.h"
#include "CSettingDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND( ID_32772, &CMainFrame::On32772 )
	ON_COMMAND( ID_32773, &CMainFrame::OnClickPictureOpen )
	ON_COMMAND( ID_32774, &CMainFrame::OnClickSetting )
	ON_COMMAND( ID_32775, &CMainFrame::On3277 )
	ON_COMMAND( ID_32776, &CMainFrame::OnOnclick_OpenHJ )
	ON_COMMAND( ID_32777, &CMainFrame::OnOnclick_OpenBS )
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
	: m_bIsAlivePictureDlg()
	, m_pCPictureViewDlg()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
	for( int i = 0; i < MAX_PICTUREVIEW_CNT; i++ )
	{
		m_bIsAlivePictureDlg[i] = false;
		m_pCPictureViewDlg[i] = nullptr;
	}
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기



void CMainFrame::On32772()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ConverterFileSearch dlg;
	dlg.DoModal();
}


void CMainFrame::OnClickPictureOpen()
{

}


void CMainFrame::OnClickSetting()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSettingDlg dlg;
	if( IDOK == dlg.DoModal() )
	{

	}
}

//Onclick_OpenHJ
void CMainFrame::On3277()
{

}


void CMainFrame::OnOnclick_OpenHJ()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	/*CEdit* pPathEdit = (CEdit*) GetDlgItem( IDC_EDIT1 );
pPathEdit->SetWindowTextW( _T( "" ) );*/
// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T( "형제 이미지(*.PIC)|*.PIC|" ); // 모든 파일 표시
	// _T("Excel 파일 (*.xls, *.xlsx) |*.xls; *.xlsx|"); 와 같이 확장자를 제한하여 표시할 수 있음
	CFileDialog dlg( TRUE, _T( "*.dat" ), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this );
	CString strPathName;
	CString cDefPath;
	cDefPath = CSettingDlg::GetHJPath().c_str();
	dlg.m_ofn.lpstrInitialDir = cDefPath;

	if( dlg.DoModal() == IDOK )
	{
		strPathName = dlg.GetPathName();
		// 파일 경로를 가져와 사용할 경우, Edit Control에 값 저장
		SetDlgItemText( IDC_EDIT1, strPathName );

		//항상 새창 열도록 함.
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
		bool bIsUsable = false;
		int iUsableIdx = -1;
		for( int iDlgIdx = 0; iDlgIdx < MAX_PICTUREVIEW_CNT; ++iDlgIdx )
		{
			if( false == m_bIsAlivePictureDlg[iDlgIdx] )
			{
				iUsableIdx = iDlgIdx;
				break;
			}
		}
		if( -1 != iUsableIdx )
		{
			std::string cFilePath = std::string( CT2CA( strPathName ) );

			CPictureViewDlg* pPictureVDlg = new CPictureViewDlg;
			pPictureVDlg->Create( IDD_PAINTVIEW );
			pPictureVDlg->SetFilePath( cFilePath );
			pPictureVDlg->ShowWindow( SW_SHOW );

			std::string cFileName = cFilePath.substr( cFilePath.rfind( '\\' ) + 1, cFilePath.length() );
			CString cTitle;
			cTitle = cFileName.c_str();
			pPictureVDlg->SetWindowTextW( cTitle );
			m_pCPictureViewDlg[iUsableIdx] = pPictureVDlg;
			m_bIsAlivePictureDlg[iUsableIdx] = true;
		}
		else
		{
			AfxMessageBox( _T( "생성불가능" ), MB_ICONSTOP );
		}

		//pPictureVDlg->OnInitDialog();
		//cPictureVDlg.Create();
	}
}


void CMainFrame::OnOnclick_OpenBS()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
		/*CEdit* pPathEdit = (CEdit*) GetDlgItem( IDC_EDIT1 );
	pPathEdit->SetWindowTextW( _T( "" ) );*/
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T( "부성 이미지(*.DAT)|*.DAT|" ); // 모든 파일 표시
	// _T("Excel 파일 (*.xls, *.xlsx) |*.xls; *.xlsx|"); 와 같이 확장자를 제한하여 표시할 수 있음
	CFileDialog dlg( TRUE, _T( "*.dat" ), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this );
	CString strPathName;
	CString cDefPath;
	cDefPath = CSettingDlg::GetBSPath().c_str();
	dlg.m_ofn.lpstrInitialDir = cDefPath;

	if( dlg.DoModal() == IDOK )
	{
		strPathName = dlg.GetPathName();
		// 파일 경로를 가져와 사용할 경우, Edit Control에 값 저장
		SetDlgItemText( IDC_EDIT1, strPathName );

		//항상 새창 열도록 함.
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
		bool bIsUsable = false;
		int iUsableIdx = -1;
		for( int iDlgIdx = 0; iDlgIdx < MAX_PICTUREVIEW_CNT; ++iDlgIdx )
		{
			if( false == m_bIsAlivePictureDlg[iDlgIdx] )
			{
				iUsableIdx = iDlgIdx;
				break;
			}
		}
		if( -1 != iUsableIdx )
		{
			std::string cFilePath = std::string( CT2CA( strPathName ) );

			CPictureViewDlg* pPictureVDlg = new CPictureViewDlg;
			pPictureVDlg->Create( IDD_PAINTVIEW );
			pPictureVDlg->SetFilePath( cFilePath );
			pPictureVDlg->ShowWindow( SW_SHOW );

			std::string cFileName = cFilePath.substr( cFilePath.rfind( '\\' ) + 1, cFilePath.length() );
			CString cTitle;
			cTitle = cFileName.c_str();
			pPictureVDlg->SetWindowTextW( cTitle );
			m_pCPictureViewDlg[iUsableIdx] = pPictureVDlg;
			m_bIsAlivePictureDlg[iUsableIdx] = true;
		}
		else
		{
			AfxMessageBox( _T( "생성불가능" ), MB_ICONSTOP );
		}

		//pPictureVDlg->OnInitDialog();
		//cPictureVDlg.Create();
	}
}
