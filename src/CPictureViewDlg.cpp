// CPictureViewDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication4.h"
#include "CPictureViewDlg.h"
#include "afxdialogex.h"
#include "YSUtil/BSPictureMaker.h"
#include "YSUtil/HJPictureMaker.h"
#include "YSUtil/CListManager.h"

// CPictureViewDlg 대화 상자

IMPLEMENT_DYNAMIC(CPictureViewDlg, CDialogEx)

void CPictureViewDlg::SetFilePath( std::string cfilePath )
{
	m_cFilePath = cfilePath;
	MakePattern();
}

void CPictureViewDlg::MakePattern()
{
	std::string  cLoadPath = m_cFilePath;
	int iDotOffset = cLoadPath.find( '.', 0 );
	int iLength = cLoadPath.length();
	if( -1 == iDotOffset )
	{
		AfxMessageBox( _T( "그림 파일의 확장자가 없습니다." ), MB_ICONSTOP );
	}
	else
	{
		std::string cFileFormat = cLoadPath.substr( iDotOffset + 1, iLength );
		std::string cSavePath;
		//형제 
		// 형제 -> 부성
		if( ( 0 == cFileFormat.compare( "PIC" ) ) || ( 0 == cFileFormat.compare( "pic" ) ) )
		{
			int iFolderOffset1 = cLoadPath.rfind( '\\' );
			int iFolderOffset2 = cLoadPath.rfind( '/' );
			if( -1 != iFolderOffset1 )
			{
				cSavePath = cLoadPath.substr( 0, iFolderOffset1 + 1 );
			}
			else if( -1 != iFolderOffset2 )
			{
				cSavePath = cLoadPath.substr( 0, iFolderOffset2 + 1 );
			}
			//현재 폴더
			else
			{
				cSavePath = "./";
			}
			int iRet = MakePattern2HJ( cLoadPath );
			if( 1 == iRet )
			{
				AfxMessageBox( _T( "잘못된 파일입니다." ), MB_ICONSTOP );
			}
			else if( 2 == iRet )
			{
				AfxMessageBox( _T( "파일을 저장하지 못했습니다." ), MB_ICONSTOP );
			}
			else
			{
				//AfxMessageBox( _T( "완료되었습니다." ) );
			}
		}
		//부성
		// 부성 -> 형제
		else if( ( 0 == cFileFormat.compare( "dat" ) ) || ( 0 == cFileFormat.compare( "DAT" ) ) )
		{
			int iFolderOffset1 = cLoadPath.rfind( '\\' );
			int iFolderOffset2 = cLoadPath.rfind( '/' );
			if( -1 != iFolderOffset1 )
			{
				cSavePath = cLoadPath.substr( 0, iFolderOffset1 + 1 );
			}
			else if( -1 != iFolderOffset2 )
			{
				cSavePath = cLoadPath.substr( 0, iFolderOffset2 + 1 );
			}
			//현재 폴더
			else
			{
				cSavePath = "./";
			}
			int iRet = MakePattern2BS( cLoadPath );
			if( 1 == iRet )
			{
				AfxMessageBox( _T( "잘못된 파일입니다." ), MB_ICONSTOP );
			}
			else if( 2 == iRet )
			{
				AfxMessageBox( _T( "파일을 저장하지 못했습니다." ), MB_ICONSTOP );
			}
			else
			{
				//AfxMessageBox( _T( "완료되었습니다." ) );
			}
		}
		else
		{
			CString cErrorContent;
			std::string cErrorMsgStr;
			cErrorMsgStr = "잘못된 파일입니다.( 확장자: " + cFileFormat + ")";
			cErrorContent = cErrorMsgStr.c_str();

			AfxMessageBox( cErrorContent, MB_ICONSTOP );
		}
	}
}

int CPictureViewDlg::MakePattern2HJ( std::string & cLoadPath )
{
	//CListManager< CListManager<char>> cPatterns;
	HJPictureMaker cHJMaker;
	int iNeedleCnt = 0;
	cHJMaker.LoadPattern( m_cPatterns, iNeedleCnt, cLoadPath );
	BSPictureMaker cBSMaker;
	m_iNeedleCnt = iNeedleCnt;
	//cBSMaker.CastingPattern4BS( cPatterns );
	return 0;
}

//부성 파일로부터 패턴가져옴

int CPictureViewDlg::MakePattern2BS( std::string & cLoadPath )
{
	//CListManager< CListManager<char>> cPatterns;
	BSPictureMaker cBSMaker;
	cBSMaker.LoadPattern( m_cPatterns, cLoadPath );
	HJPictureMaker cHJMaker;
	//cHJMaker.CastingPattern4HJ( m_cPatterns );
	m_iNeedleCnt = m_cPatterns.GetPtr()[0].GetSize();
	return 0;
}

CPictureViewDlg::CPictureViewDlg( CWnd* pParent /*=nullptr*/ )
	: CDialogEx(IDD_PAINTVIEW, pParent)
	, m_pParent( pParent )
{

}

CPictureViewDlg::~CPictureViewDlg()
{
}


//부성 파일로부터 패턴가져옴

std::string CPictureViewDlg::GetFilePath()
{
	return m_cFilePath;
}

void CPictureViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

// DDX/DDV 지원입니다.

//void CPictureViewDlg::OnPaint( CDC* pDC )    // DDX/DDV 지원입니다.
//{
//
//}

void CPictureViewDlg::OnDraw( CDC * pDC )
{
	//int cxIcon = GetSystemMetrics( SM_CXSIZE );
	//int cyIcon = GetSystemMetrics( SM_CYSIZE );

	//CRect rect;
	//GetClientRect( &rect );
	//int x = ( rect.Width() - cxIcon + 1 ) / 2;
	//int y = ( rect.Height() - cyIcon + 1 ) / 2;

	//// Draw the icon
	////dc.DrawEscape( x, y, 10 );
	//pDC->Ellipse( x - 5, y - 5, x + 5, y + 5 );
	//dc.DrawIcon( x, y, m_hIcon );
	CRect rect;
	GetClientRect( rect );
	int iRowCnt = m_cPatterns.GetSize();
	const int LINE_INTERVAL = 10;
	int iDX = rect.Width() / m_iNeedleCnt;
	int iDY = rect.Height() / iRowCnt;
	if( iDY <= 1 )
	{
		iDY = 2;
	}
	else if( iDY >= 15 )
	{
		iDY = 14;
	}
	if( iDX <= 1 )
	{
		iDX = 2;
	}
	else if( iDX >= 15 )
	{
		iDX = 14;
	}
	int iDelta = iDX;
	CListManager<char>* pRowList = m_cPatterns.GetPtr();
	for( int iRowIdx = 0; iRowIdx < iRowCnt; iRowIdx++ )
	{
		char* pRowData = pRowList[iRowIdx].GetPtr();
		for( int iNeedleIdx = 0; iNeedleIdx < m_iNeedleCnt; iNeedleIdx++ )
		{
			if( 0 != pRowData[iNeedleIdx] )
			{
				COLORREF sRGB = 0x0000ff;
				//pDC->FillSolidRect( iRowIdx*iDY, iNeedleIdx*iDY, iRowIdx*iDY + iDY, iNeedleIdx*iDY + iDY, sRGB );
				//pDC->Rectangle( iRowIdx*iDX, iNeedleIdx*iDX, iRowIdx*iDX + iDY, iNeedleIdx*iDX + iDX );
				//pDC->Rectangle( iNeedleIdx*iDX, iRowIdx*iDX, iNeedleIdx*iDX + iDX, iRowIdx*iDX + iDX );
				pDC->Rectangle( iNeedleIdx*iDelta, iRowIdx*iDelta, iNeedleIdx*iDelta + iDelta, iRowIdx*iDelta + iDelta );
				//pDC->FillSolidRect( iNeedleIdx*iDX, iRowIdx*iDX, iNeedleIdx*iDX + iDX, iRowIdx*iDX + iDY, sRGB );
			}
		}
	}
}


BEGIN_MESSAGE_MAP(CPictureViewDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CPictureViewDlg 메시지 처리기


void CPictureViewDlg::OnPaint()
{
	CPaintDC dc( this ); // device context for painting
		     // TODO: 여기에 메시지 처리기 코드를 추가합니다.
		     // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	OnDraw( &dc );
	//CDialogEx::OnPaint();

}


void CPictureViewDlg::OnSize( UINT nType, int cx, int cy )
{
	CDialogEx::OnSize( nType, cx, cy );
	Invalidate( TRUE );
	//OnPaint();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CPictureViewDlg::OnSizing( UINT fwSide, LPRECT pRect )
{
	CDialogEx::OnSizing( fwSide, pRect );
	Invalidate(TRUE);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CPictureViewDlg::OnGetMinMaxInfo( MINMAXINFO* lpMMI )
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnGetMinMaxInfo( lpMMI );
}


void CPictureViewDlg::PreInitDialog()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	int iWidth = 500;
	int iHeight = 900;
	SetWindowPos( &CWnd::wndBottom, 300, 500, iWidth, iHeight, 0 );
	
	//SetWindowPos( &CWnd::wndNoTopMost, 300, 500, iWidth, iHeight, 0 );
	CDialogEx::PreInitDialog();
}
