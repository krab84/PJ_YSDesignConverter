// ConverterFileSearch.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication4.h"
#include "ConverterFileSearch.h"
#include "afxdialogex.h"
#include "YSUtil/BSPictureMaker.h"
#include "YSUtil/HJPictureMaker.h"
#include "YSUtil/CListManager.h"

// ConverterFileSearch 대화 상자

IMPLEMENT_DYNAMIC(ConverterFileSearch, CDialogEx)

ConverterFileSearch::ConverterFileSearch(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

ConverterFileSearch::~ConverterFileSearch()
{
}

void ConverterFileSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ConverterFileSearch, CDialogEx)
	ON_BN_CLICKED( IDC_BUTTON1, &ConverterFileSearch::OnBnClickedButton1 )
	ON_BN_CLICKED( IDC_BUTTON3, &ConverterFileSearch::OnBnClickedButton3 )
END_MESSAGE_MAP()


// ConverterFileSearch 메시지 처리기


void ConverterFileSearch::OnBnClickedButton1()
{
	/*CEdit* pPathEdit = (CEdit*) GetDlgItem( IDC_EDIT1 );
	pPathEdit->SetWindowTextW( _T( "" ) );*/
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T( "All files(*.*)|*.*|" ); // 모든 파일 표시
	// _T("Excel 파일 (*.xls, *.xlsx) |*.xls; *.xlsx|"); 와 같이 확장자를 제한하여 표시할 수 있음
	CFileDialog dlg( TRUE, _T( "*.dat" ), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this );

	if( dlg.DoModal() == IDOK )
	{
		CString strPathName = dlg.GetPathName();
		// 파일 경로를 가져와 사용할 경우, Edit Control에 값 저장
		SetDlgItemText( IDC_EDIT1, strPathName );
	}
}

// Convert 버튼 이벤트 처리
void ConverterFileSearch::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString cTempStr;
	GetDlgItemText( IDC_EDIT1, cTempStr );
	//명칭 가져왔고.
	std::string cLoadPath = std::string( CT2CA( cTempStr ) );
	GetDlgItemText( IDC_EDIT2, cTempStr );
	std::string cSaveFile = std::string( CT2CA( cTempStr ) );
	bool iCheckPath = 0 != cLoadPath.length();
	bool iCheckSaveFileName = 0 != cSaveFile.length();
	if( iCheckPath &&iCheckSaveFileName )
	{
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
					cSavePath = cLoadPath.substr( 0, iFolderOffset1+1 );
				}
				else if( -1 != iFolderOffset2 )
				{
					cSavePath = cLoadPath.substr( 0, iFolderOffset2 +1);
				}
				//현재 폴더
				else
				{
					cSavePath = "./";
				}
				cSavePath += cSaveFile + ".DAT";
				int iRet = ConvertHJ2BS( cLoadPath, cSavePath );
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
					AfxMessageBox( _T( "완료되었습니다." ) );
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
					cSavePath = cLoadPath.substr( 0, iFolderOffset1 +1);
				}
				else if( -1 != iFolderOffset2 )
				{
					cSavePath = cLoadPath.substr( 0, iFolderOffset2 +1);
				}
				//현재 폴더
				else
				{
					cSavePath = "./";
				}
				cSavePath += cSaveFile + ".PIC";
				int iRet = ConvertBS2HJ( cLoadPath, cSavePath );
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
					AfxMessageBox( _T( "완료되었습니다." ) );
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
	else if( iCheckPath )
	{
		AfxMessageBox( _T( "그림 파일의 경로가 설정되지 않았습니다." ), MB_ICONSTOP );
	}
	else if( iCheckSaveFileName )
	{
		AfxMessageBox( _T( "저장할 파일명을 설정해주세요" ), MB_ICONSTOP );
	}
	else
	{
		//AfxMessageBox( _T( "알림" ) );
		AfxMessageBox( _T( "그림 파일의 경로가 설정되지 않았습니다. \n저장할 파일명을 설정해주세요" ), MB_ICONSTOP );
		/*
		if( AfxMessageBox( _T( "Yes or No" ), MB_YESNO | MB_ICONQUESTION ) == IDYES )
		{
			// Yes
		}
		*/
	}
}

int ConverterFileSearch::ConvertHJ2BS( std::string& cLoadPath, std::string& cSavePath )
{
	CListManager< CListManager<char>> cPatterns;
	HJPictureMaker cHJMaker;
	int iNeedleCnt = 0;
	cHJMaker.LoadPattern( cPatterns, iNeedleCnt, cLoadPath );
	BSPictureMaker cBSMaker;
	//cBSMaker.CastingPattern4BS( cPatterns );
	cBSMaker.SavePattern( cPatterns, iNeedleCnt, cSavePath );
	cBSMaker.ReportFileAnalysis( cSavePath );
	return 0;
}

int ConverterFileSearch::ConvertBS2HJ( std::string& cLoadPath, std::string& cSavePath )
{
	CListManager< CListManager<char>> cPatterns;
	BSPictureMaker cBSMaker;
	cBSMaker.LoadPattern( cPatterns, cLoadPath);
	HJPictureMaker cHJMaker;
	cHJMaker.CastingPattern4HJ( cPatterns );
	cHJMaker.SavePattern( cPatterns, cSavePath );
	cHJMaker.ReportFileAnalysis( cSavePath );
	return 0;
}

int ConverterFileSearch::ConvertHJ2HJ( std::string & cLoadPath, std::string & cSavePath )
{
	CListManager< CListManager<char>> cPatterns;
	HJPictureMaker cHJMaker;
	int iNeedleCnt = 0;
	cHJMaker.LoadPattern( cPatterns, iNeedleCnt, cLoadPath );
	HJPictureMaker cHJMaker2;
	//cHJMaker2.CastingPattern4( cPatterns );
	cHJMaker2.SavePattern( cPatterns, cSavePath );
	return 0;
}
