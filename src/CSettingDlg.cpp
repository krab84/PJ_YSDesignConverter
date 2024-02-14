// CSettingDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication4.h"
#include "CSettingDlg.h"
#include "afxdialogex.h"


// CSettingDlg 대화 상자

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

void CSettingDlg::ReadSettingFile()
{
	FILE* pFile = NULL;
	fopen_s( &pFile, "./Setting.ini", "rb" );
	char buffers[1024] = {};
	if( NULL != pFile )
	{
		//첫번째줄은 형제 Path
		fscanf_s( pFile, "%s", buffers, 1024 );
		m_HJPath = buffers;
		//두번째줄은 부성 Path
		fscanf_s( pFile, "%s", buffers, 1024 );
		m_BSPath = buffers;
		fclose( pFile );
	}
	else
	{
		//Default SetUp C:드라이브 기본
		fopen_s( &pFile, "./Setting.ini", "wb" );
		if( nullptr != pFile )
		{
			memcpy( buffers, "C:\\", sizeof( buffers ) );
			//첫번째줄은 형제 Path
			fscanf_s( pFile, "%s", buffers, 1024 );
			m_HJPath = buffers;
			//두번째줄은 부성 Path
			fscanf_s( pFile, "%s", buffers, 1024 );
			m_BSPath = buffers;
			fclose( pFile );
		}
		else
		{
			//실패
			m_HJPath = "";
			m_BSPath = "";
		}
	}
	CString cTempStr;
	cTempStr = m_HJPath.c_str();
	SetDlgItemText( IDC_EDIT_HJ_PATH, cTempStr );
	cTempStr = m_BSPath.c_str();
	SetDlgItemText( IDC_EDIT_BS_PATH, cTempStr );
}

void CSettingDlg::SaveSettingFile()
{
	FILE* pFile = NULL;
	fopen_s( &pFile, "./Setting.ini", "wb" );
	if( NULL != pFile )
	{
		fprintf( pFile, "%s\n", m_HJPath.c_str() );
		fprintf( pFile, "%s\n", m_BSPath.c_str() );
		fclose( pFile );
	}
	else
	{
		//실패
	}
}

CSettingDlg::CSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETTING, pParent)
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_BN_CLICKED( IDOK, &CSettingDlg::OnBnClickedOk )
	ON_BN_CLICKED( IDC_BUTTON1, &CSettingDlg::OnBnClickedButton1 )
	ON_BN_CLICKED( IDC_BUTTON2, &CSettingDlg::OnBnClickedButton2 )
END_MESSAGE_MAP()


// CSettingDlg 메시지 처리기


void CSettingDlg::OnBnClickedOk()
{
	CString cTempStr;
	GetDlgItemText( IDC_EDIT_HJ_PATH, cTempStr );
	m_HJPath = std::string( CT2CA( cTempStr ) );
	GetDlgItemText( IDC_EDIT_BS_PATH, cTempStr );
	m_BSPath = std::string( CT2CA( cTempStr ) );
	SaveSettingFile();

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


INT_PTR CSettingDlg::DoModal()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	INT_PTR ret = CDialogEx::DoModal();
	if( IDOK == ret )
	{

	}
	return ret;
}


BOOL CSettingDlg::PreCreateWindow( CREATESTRUCT& cs )
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreCreateWindow( cs );
}


void CSettingDlg::PreInitDialog()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	ReadSettingFile();
	CDialogEx::PreInitDialog();
}

void CSettingDlg::WriteDefaultSetting()
{
	FILE* pFile = NULL;
	//Default SetUp C:드라이브 기본
	char buffers[1024] = {};
	fopen_s( &pFile, "./Setting.ini", "wb" );
	if( nullptr != pFile )
	{
		memcpy( buffers, "C:\\", sizeof( buffers ) );
		//첫번째줄은 형제 Path
		fscanf_s( pFile, "%s", buffers, 1024 );
		//두번째줄은 부성 Path
		fscanf_s( pFile, "%s", buffers, 1024 );
		fclose( pFile );
	}
}

std::string CSettingDlg::GetHJPath()
{
	std::string cRetPath;
	FILE* pFile = NULL;
	fopen_s( &pFile, "./Setting.ini", "rb" );
	char buffers[1024] = {};
	if( NULL != pFile )
	{
		fclose( pFile );
	}
	else
	{
		WriteDefaultSetting();
	}
	fopen_s( &pFile, "./Setting.ini", "rb" );
	if( NULL != pFile )
	{
		//첫번째줄은 형제 Path
		//for(int i=0;i< )
		fscanf_s( pFile, "%s", buffers, 1024 );
		cRetPath = buffers;
		//두번째줄은 부성 Path
		//fscanf_s( pFile, "%s", buffers, 1024 );
		//m_BSPath = buffers;
		fclose( pFile );
	}
	return cRetPath;
}

std::string CSettingDlg::GetBSPath()
{
	std::string cRetPath;
	FILE* pFile = NULL;
	fopen_s( &pFile, "./Setting.ini", "rb" );
	char buffers[1024] = {};
	if( NULL != pFile )
	{
		fclose( pFile );
	}
	else
	{
		WriteDefaultSetting();
	}
	fopen_s( &pFile, "./Setting.ini", "rb" );
	if( NULL != pFile )
	{
		//첫번째줄은 형제 Path
		fscanf_s( pFile, "%s", buffers, 1024 );
		//cRetPath = buffers;
		//두번째줄은 부성 Path
		fscanf_s( pFile, "%s", buffers, 1024 );
		cRetPath = buffers;
		fclose( pFile );
	}
	return cRetPath;
}


void CSettingDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BROWSEINFO BrInfo;
	TCHAR szBuffer[512];                                      // 경로저장 버퍼 

	::ZeroMemory( &BrInfo, sizeof( BROWSEINFO ) );
	::ZeroMemory( szBuffer, 512 );

	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.lpszTitle = _T( "파일이 저장될 폴더를 선택하세요" );
	BrInfo.ulFlags = BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_RETURNONLYFSDIRS;
	LPITEMIDLIST pItemIdList = ::SHBrowseForFolder( &BrInfo );
	::SHGetPathFromIDList( pItemIdList, szBuffer );               // 파일경로 읽어오기

	// 경로를 가져와 사용할 경우, Edit Control 에 값 저장
	CString str;
	str.Format( _T( "%s" ), szBuffer );
	SetDlgItemText( IDC_EDIT_HJ_PATH, str );
}


void CSettingDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BROWSEINFO BrInfo;
	TCHAR szBuffer[512];                                      // 경로저장 버퍼 

	::ZeroMemory( &BrInfo, sizeof( BROWSEINFO ) );
	::ZeroMemory( szBuffer, 512 );

	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.lpszTitle = _T( "파일이 저장될 폴더를 선택하세요" );
	BrInfo.ulFlags = BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_RETURNONLYFSDIRS;
	LPITEMIDLIST pItemIdList = ::SHBrowseForFolder( &BrInfo );
	::SHGetPathFromIDList( pItemIdList, szBuffer );               // 파일경로 읽어오기

	// 경로를 가져와 사용할 경우, Edit Control 에 값 저장
	CString str;
	str.Format( _T( "%s" ), szBuffer );
	SetDlgItemText( IDC_EDIT_BS_PATH, str );
}
