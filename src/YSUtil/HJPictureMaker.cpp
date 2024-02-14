#include "HJPictureMaker.h"
#include "CListManager.h"
#include<cstdio>
#include<cstdlib>
#include<memory>
#include<iostream>

#define HJ_STANDARD_FILENAME ("HJ_STANDARD.PIC")
//#define HJ_MUJI (7)
//#define HJ_PEN (4)

void HJPictureMaker::MakePicture( 
	const std::string & cPictureFName, 
	char** pPatterns, //더블포인터 2차원배열임.
	const int iColCnt, const int iRowCnt )
{
	if( GetHeader( iColCnt, iRowCnt ) )
	{
		FILE* pFile = NULL;
		fopen_s( &pFile, cPictureFName.c_str(), "wb" );
		if( NULL != pFile )
		{
			//Header 작성
			for( int strIdx = 0; strIdx < 1024; ++strIdx )
			{
				fputc( m_buffers[strIdx], pFile );
			}
			//몸통 작성
			char iCurrContent = 0;
			int iCnt = 0;
			char iPrevPen = 0;
			int iCurrPenCnt = 0;
			for( int iRowIdx = 0; iRowIdx < iRowCnt; ++iRowIdx )
			{
				for( int iColIdx = 0; iColIdx < iColCnt; ++iColIdx )
				{
					const int iNowPen = pPatterns[iRowIdx][iColIdx];
					if( 0 == iColIdx )
					{
						iCurrPenCnt = 0;
						iPrevPen = iNowPen;
						iCurrPenCnt++;
					}
					else
					{
						if( iPrevPen == iNowPen )
						{
							iCurrPenCnt++;
						}
						else
						{
							printf( "%d %d\n", iCurrPenCnt, iPrevPen );
							fputc( iCurrPenCnt, pFile );
							fputc( iPrevPen, pFile );
							iCurrPenCnt = 0;
							iPrevPen = iNowPen;
							iCurrPenCnt++;
						}
					}
				}
				printf( "%d %d\n", iCurrPenCnt, iPrevPen );
				fputc( iCurrPenCnt, pFile );
				fputc( iPrevPen, pFile );
			}

			//마지막 종료부분
			fputc( 0, pFile );
			fputc( 0, pFile );

			fclose( pFile );
		}
		else
		{

		}
	}
	else
	{

	}
}

void HJPictureMaker::MakePicture( 
	const std::string & cPictureFName, 
	CListManager<CListManager<char>>& cPatterns, 
	const int iColCnt, const int iRowCnt )
{
	if( GetHeader( iColCnt, iRowCnt ) )
	{
		FILE* pFile = NULL;
		fopen_s( &pFile, cPictureFName.c_str(), "wb" );
		if( NULL != pFile )
		{
			//Header 작성
			for( int strIdx = 0; strIdx < 1024; ++strIdx )
			{
				fputc( m_buffers[strIdx], pFile );
			}
			//몸통 작성
			char iCurrContent = 0;
			int iCnt = 0;
			char iPrevPen = 0;
			int iCurrPenCnt = 0;
			//cPatterns.ReSize( iRowCnt );
			CListManager<char>* pRowList = cPatterns.GetPtr();
			for( int iRowIdx = 0; iRowIdx < iRowCnt; ++iRowIdx )
			{
				char* pRowData = pRowList[iRowIdx].GetPtr();
				for( int iColIdx = 0; iColIdx < iColCnt; ++iColIdx )
				{
					const int iNowPen = pRowData[iColIdx];
					if( 0 == iColIdx )
					{
						iCurrPenCnt = 0;
						iPrevPen = iNowPen;
						iCurrPenCnt++;
					}
					else
					{
						if( iPrevPen == iNowPen )
						{
							iCurrPenCnt++;
						}
						else
						{
							printf( "%d %d\n", iCurrPenCnt, iPrevPen );
							fputc( iCurrPenCnt, pFile );
							fputc( iPrevPen, pFile );
							iCurrPenCnt = 0;
							iPrevPen = iNowPen;
							iCurrPenCnt++;
						}
					}
				}
				printf( "%d %d\n", iCurrPenCnt, iPrevPen );
				fputc( iCurrPenCnt, pFile );
				fputc( iPrevPen, pFile );
			}

			//마지막 종료부분
			fputc( 0, pFile );
			fputc( 0, pFile );

			fclose( pFile );
		}
		else
		{

		}
	}
	else
	{

	}
}


void HJPictureMaker::LoadPattern(
	CListManager<CListManager<char>>& cPatterns,
	int& iRealNeedleCnt,
	const std::string & cPictureFName )
{
	FILE* pFile = NULL;
	fopen_s( &pFile, cPictureFName.c_str(), "rb" );
	if( NULL != pFile )
	{
		fseek( pFile, 0, SEEK_SET );
		//Header 작성
		for( int strIdx = 0; strIdx < 1024; ++strIdx )
		{
			m_buffers[strIdx] = fgetc( pFile );
		}
		short iNeedleCnt = 0;
		memcpy( &iNeedleCnt, &m_buffers[2], sizeof( short ) );
		iRealNeedleCnt = GetRealNeedleCnt( iNeedleCnt );
		//const int iNeedleCnt = m_buffers[2];
		short iRowCnt = 0;
		memcpy( &iRowCnt, &m_buffers[4], sizeof( short ) );
		cPatterns.ReSize( iRowCnt );
		CListManager<char>* pRowList = cPatterns.GetPtr();
		for( int iRowIdx = 0; iRowIdx < iRowCnt; ++iRowIdx )
		{
			pRowList[iRowIdx].ReSize( iNeedleCnt );
			memset( pRowList[iRowIdx].GetPtr(), HJ_MUJI, sizeof( char )*iNeedleCnt );
		}
		int iCurrRowIdx = 0;
		int iCurrNeedleIdx = 0;
		int iCurrPenType = 0;
		while( 1 )
		{
			int iPenCnt = fgetc( pFile );
			int iPenType = fgetc( pFile );
			if( HJ_MUJI == iPenType )
			{
				//0
				iCurrPenType = 0;
			}
			else
			{
				//1
				iCurrPenType = 1;
			}

			if( 0 == iPenCnt && 0 == iPenType )
			{
				break;
			}
			//4번을 190개 넣는다.
			for( int iPenIdx = 0; iPenIdx < iPenCnt; ++iPenIdx )
			{
				pRowList[iCurrRowIdx].GetPtr()[iCurrNeedleIdx++] = iCurrPenType;
			}
			if( iNeedleCnt == iCurrNeedleIdx )
			{
				iCurrRowIdx++;
				iCurrNeedleIdx = 0;
			}
		}
		//for( int iRowIdx = 0; iRowIdx < iRowCnt; ++iRowIdx )
		//{
		//	pRowList[iRowIdx].ReSize( iRealNeedleCnt );
		//}

		fclose( pFile );
	}
}
//Picture파일을 읽고 cPatterns에 넣는다.
//return PatternList

void HJPictureMaker::LoadPattern( 
	CListManager<CListManager<char>>& cPatterns, 
	const std::string & cPictureFName )
{
	FILE* pFile = NULL;
	fopen_s( &pFile, cPictureFName.c_str(), "rb" );
	if( NULL != pFile )
	{
		//Header 작성
		for( int strIdx = 0; strIdx < 1024; ++strIdx )
		{
			fputc( m_buffers[strIdx], pFile );
		}
		const int iNeedleCnt = m_buffers[2];
		//const int iNeedCnt = GetRealNeedleCnt( iColCnt );
		//const int iNeedleCnt = m_buffers[2];
		const int iRowCnt = m_buffers[4];
		cPatterns.ReSize( iRowCnt );
		CListManager<char>* pRowList = cPatterns.GetPtr();
		for( int iRowIdx = 0; iRowIdx < iRowCnt; ++iRowIdx )
		{
			pRowList[iRowIdx].ReSize( iNeedleCnt );
			memset( pRowList[iRowIdx].GetPtr(), HJ_MUJI, sizeof( char )*iNeedleCnt );
		}
		int iCurrRowIdx = 0;
		int iCurrNeedleIdx = 0;
		int iCurrPenType = 0;
		while( 1 )
		{
			int iPenCnt = fgetc( pFile );
			int iPenType = fgetc( pFile );
			if( HJ_MUJI == iPenType )
			{
				//0
				iCurrPenType = 0;
			}
			else
			{
				//1
				iCurrPenType = 1;
			}

			if( 0 == iPenCnt && 0 == iPenType )
			{
				break;
			}
			//4번을 190개 넣는다.
			for( int iPenIdx = 0; iPenIdx < iPenCnt; ++iPenIdx )
			{
				pRowList[iCurrRowIdx].GetPtr()[iCurrNeedleIdx++] = iCurrPenType;
			}
			if( iNeedleCnt == iCurrNeedleIdx )
			{
				iCurrRowIdx++;
				iCurrNeedleIdx = 0;
			}
		}
	}
}

//return PictureFile

void HJPictureMaker::SavePattern( CListManager<CListManager<char>>& cPatterns, const std::string & cPictureFName )
{
	int iNeedleCnt = cPatterns.GetPtr()[0].GetSize();
	int iRowCnt = cPatterns.GetSize();
	MakePicture( cPictureFName, cPatterns, iNeedleCnt, iRowCnt );
}

void HJPictureMaker::ReportFileAnalysis( const std::string & cPicturePath )
{
	FILE* pFile = NULL;
	FILE* pSaveFile = NULL;
	fopen_s( &pSaveFile, "./Report_HJ.txt", "w" );
	fopen_s( &pFile, cPicturePath.c_str(), "rb" );
	if( NULL != pFile && NULL != pSaveFile )
	{
		for( int strIdx = 0; strIdx < 1024; ++strIdx )
		{
			m_buffers[strIdx] = fgetc( pFile );
		}
		fprintf( pSaveFile, "HJ 데이터 보고서\n" );
		short iNeedleCnt = 0;
		short iRowCnt = 0;
		memcpy( &iNeedleCnt, &m_buffers[2], sizeof( short ) );
		memcpy( &iRowCnt, &m_buffers[4], sizeof( short ) );
		fprintf( pSaveFile, "침수: %d Line: %d\n", iNeedleCnt, iRowCnt );
		fprintf( pSaveFile, "DataCheck\n" );
		for( int i = 0; i < 512; ++i )
		{
			short iCheckNum = 0;
			memcpy( &iCheckNum, &m_buffers[2 * i], sizeof( short ) );
			fprintf( pSaveFile, "Data[%d]: %d\n", i, iCheckNum );
		}
		fclose( pFile );
		fclose( pSaveFile );
	}
#if 0
	else
	{
		if( 0 )
		{
			//Header 작성
			for( int strIdx = 0; strIdx < 1024; ++strIdx )
			{
				fputc( m_buffers[strIdx], pFile );
			}
			const int iNeedleCnt = m_buffers[2];
			const int iRowCnt = m_buffers[4];
			cPatterns.ReSize( iRowCnt );
			CListManager<char>* pRowList = cPatterns.GetPtr();
			for( int iRowIdx = 0; iRowIdx < iRowCnt; ++iRowIdx )
			{
				pRowList[iRowIdx].ReSize( iNeedleCnt );
				memset( pRowList[iRowIdx].GetPtr(), HJ_MUJI, sizeof( char )*iNeedleCnt );
			}
			int iCurrRowIdx = 0;
			int iCurrNeedleIdx = 0;
			int iCurrPenType = 0;
			while( 1 )
			{
				int iPenCnt = fgetc( pFile );
				int iPenType = fgetc( pFile );
				if( HJ_MUJI == iPenType )
				{
					//0
					iCurrPenType = 0;
				}
				else
				{
					//1
					iCurrPenType = 1;
				}

				if( 0 == iPenCnt && 0 == iPenType )
				{
					break;
				}
				//4번을 190개 넣는다.
				for( int iPenIdx = 0; iPenIdx < iPenCnt; ++iPenIdx )
				{
					pRowList[iCurrRowIdx].GetPtr()[iCurrNeedleIdx++] = iCurrPenType;
				}
				if( iNeedleCnt == iCurrNeedleIdx )
				{
					iCurrRowIdx++;
					iCurrNeedleIdx = 0;
				}
			}
		}
	}
#endif
}

int HJPictureMaker::GetRealNeedleCnt( const int iColCnt )
{
	int iNeedleCnt = 0;
	bool bIs108Machine =
		( 0 == iColCnt % 108 ) ||
		( 20 == iColCnt % 108 ) ||
		( 23 == iColCnt % 108 );
	bool bIs120Machine =
		( 0 == iColCnt % 120 ) ||
		( 20 == iColCnt % 120 ) ||
		( 23 == iColCnt % 120 );
	bool bIs144Machine =
		( 0 == iColCnt % 144 ) ||
		( 20 == iColCnt % 144 ) ||
		( 23 == iColCnt % 144 );
	bool bIs168Machine =
		( 0 == iColCnt % 168 ) ||
		( 20 == iColCnt % 168 ) ||
		( 23 == iColCnt % 168 );
	bool bIs200Machine =
		( 0 == iColCnt % 200 ) ||
		( 20 == iColCnt % 200 ) ||
		( 23 == iColCnt % 200 );
	if( bIs200Machine )
	{
		iNeedleCnt = 200;
	}
	else if( bIs168Machine )
	{
		iNeedleCnt = 168;
	}
	else if( bIs144Machine )
	{
		iNeedleCnt = 144;
	}
	else if( bIs120Machine )
	{
		iNeedleCnt = 120;
	}
	else if( bIs108Machine )
	{
		iNeedleCnt = 108;
	}
	return iNeedleCnt;
}

void HJPictureMaker::CastingPattern4HJ( CListManager<CListManager<char>>& cPatterns )
{
	const int iRowCnt = cPatterns.GetSize();
	CListManager<char>* pRowList = cPatterns.GetPtr();
	const int iNeedleCnt = pRowList[0].GetSize();
	for( int iRowIdx = 0; iRowIdx < iRowCnt; ++iRowIdx )
	{
		char* pRowData = pRowList[iRowIdx].GetPtr();
		for( int iNeedleIdx = 0; iNeedleIdx < iNeedleCnt; ++iNeedleIdx )
		{
			if( 0 == pRowData[iNeedleIdx] )
			{
				pRowData[iNeedleIdx] = HJ_MUJI;
			}
			else
			{
				pRowData[iNeedleIdx] = HJ_PEN;
			}
		}
	}
}

bool HJPictureMaker::GetHeader( int iCol, int iRow )
{
	bool bIsSuccess = true;
	FILE* pFile = NULL;
	//원래 HJ PICTURE그대로 들고옴
	memset( m_buffers, 0, sizeof( m_buffers ) );
	fopen_s( &pFile, HJ_STANDARD_FILENAME, "rb" );
	if( pFile )
	{
		for( int strIdx = 0; strIdx < 1024; ++strIdx )
		{
			m_buffers[strIdx] = fgetc( pFile );
		}
		const short iNeedleCnt = iCol;
		const short iRowCnt= iRow;
		memcpy( &m_buffers[2], &iNeedleCnt, sizeof( short ) );
		memcpy( &m_buffers[4], &iRowCnt, sizeof( short ) );
		fclose( pFile );
	}
	else
	{
		bIsSuccess = false;
		std::cout << "기본 파일이 없습니다." << HJ_STANDARD_FILENAME << std::endl;
	}
	return bIsSuccess;
}