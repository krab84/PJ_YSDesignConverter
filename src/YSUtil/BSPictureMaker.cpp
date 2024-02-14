#include "BSPictureMaker.h"
#include<cstdio>
#include<cstdlib>
#include<memory>
#include<iostream>
#include<ctime>
#include<typeinfo>
#include "CListManager.h"
#define BS_DEFAULT_MOCK_VALUE (0)
#define BS_DEFAULT_GOMU_VALUE (0)
#define BS_STANDARD_FILENAME ("BS_STANDARD.DAT")
void BSPictureMaker::MakeSimplePicture( 
	const std::string & cPictureFName, 
	char ** pPatterns, 
	const int iColCnt, const int iRowCnt )
{
	if( GetHeader( iColCnt, iRowCnt ) )
	{
		FILE* pFile = NULL;
		fopen_s( &pFile, cPictureFName.c_str(), "wb" );
		if( NULL != pFile )
		{
			for( int strIdx = 0; strIdx < 336; ++strIdx )
			{
				fputc( m_buffers[strIdx], pFile );
			}
			fclose( pFile );
		}
	}
}

void BSPictureMaker::MakeSimplePicture( 
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
			for( int strIdx = 0; strIdx < 336; ++strIdx )
			{
				fputc( m_buffers[strIdx], pFile );
			}

			CListManager<char>* pRowList = cPatterns.GetPtr();
			//몸통 작성
			int bitCnt = 0;
			char cPutData = 0;
			//한라인에 256임
			char tmpRow[32] = {};
			for( int iRowIdx = 0; iRowIdx < iRowCnt; ++iRowIdx )
			{
				int tmpIdx = 0;
				memset( tmpRow, 0, sizeof( tmpRow ) );
				char* pCurrRow = pRowList[iRowIdx].GetPtr();
				for( int iColIdx = 0; iColIdx < iColCnt; ++iColIdx )
				{
					cPutData |= ( pCurrRow[iColIdx] << (7 - bitCnt) );
					bitCnt++;
					if( 8 == bitCnt )
					{
						//fputc( cPutData, pFile );
						tmpRow[tmpIdx++] = cPutData;
						bitCnt = 0;
						cPutData = 0;
					}
				}
				for( int iStoreIdx = 0; iStoreIdx < 32; ++iStoreIdx )
				{
					fputc( tmpRow[iStoreIdx], pFile );
				}
			}
			//if( 8 == bitCnt )
			//{
			//	fputc( cPutData, pFile );
			//	bitCnt = 0;
			//}
			char cEndPutData = {};
			for(int i=0;i<7;++i )
				fputc( cEndPutData, pFile );
			fclose( pFile );
		}
	}
}
void BSPictureMaker::LoadPattern( 
	CListManager<CListManager<char>>& cPatterns, 
	const std::string & cPictureFName )
{
	//337~N데이터 그대로 가져와서 메이킹하는 작업
	FILE* pFile = NULL;
	fopen_s( &pFile, cPictureFName.c_str(), "rb" );
	if( NULL != pFile )
	{
		fseek( pFile, 0, SEEK_END );
		int iFileSize = ftell( pFile );
		fseek( pFile, 0, SEEK_SET );
		memset( m_buffers, 0, sizeof( m_buffers ) );
		for( int strIdx = 0; strIdx < 336; ++strIdx )
		{
			m_buffers[strIdx] = fgetc( pFile );
		}
		//침수
		short iNeedleCnt = 0;
		memcpy( &iNeedleCnt, &m_buffers[9], sizeof( iNeedleCnt ) );
		//고무 Default
		//short iGomuCnt = BS_DEFAULT_GOMU_VALUE;
		//memcpy( &m_buffers[49], &iGomuCnt, sizeof( iGomuCnt ) );
		//short iMockCnt = BS_DEFAULT_MOCK_VALUE;
		//memcpy( &m_buffers[59], &iMockCnt, sizeof( iMockCnt ) );
		//라인수는 거진 쓸모없음 걍 첨부터끝까지 카피할 생각임.
		short iSaveRowsCnt = 0;
		memcpy( &iSaveRowsCnt, &m_buffers[76], sizeof( iSaveRowsCnt ) );

		int iPatternSize = iFileSize  - 336  ;
		int iRealRowCnt = iPatternSize / 32; //한줄에 256
		cPatterns.ReSize( iRealRowCnt );
		CListManager<char>* pRowList = cPatterns.GetPtr();
		for( int iRowIdx = 0; iRowIdx < iRealRowCnt; ++iRowIdx )
		{
			pRowList[iRowIdx].ReSize( iNeedleCnt );
			char* pCurrRow = pRowList[iRowIdx].GetPtr();
			memset( pCurrRow, 0, sizeof( char )*iNeedleCnt );
		}
		char cGetData = 0;
		int iCurrNeedleCnt = 0;
		int iCurrRowCnt = 0;
		bool bRowComplete = false;
		//for( int iBuffIdx = 0; iBuffIdx < iSaveRowsCnt; ++iBuffIdx )
		for( int iBuffIdx = 0; iBuffIdx < iPatternSize; ++iBuffIdx )
		{
			cGetData = fgetc( pFile );
			if( true == bRowComplete )
			{
				if( 0 == iBuffIdx % 32 )
				{
					bRowComplete = false;
				}
			}
			if( false == bRowComplete )
			{
				if( iSaveRowsCnt == iCurrRowCnt )
				{
					break;
				}
				char* pCurrRow = pRowList[iCurrRowCnt].GetPtr();
				for( int i = 0; i < 8; i++ )
				{
					pCurrRow[iCurrNeedleCnt++] = ( 1 & ( cGetData >> (7 - i) ) );
					//200개 채워졌으면 탈출하고
					if( iNeedleCnt == iCurrNeedleCnt )
					{
						break;
					}
				}
				//초기화 시켜준다.
				if( iNeedleCnt == iCurrNeedleCnt )
				{
					bRowComplete = true;
					iCurrNeedleCnt = 0;
					iCurrRowCnt++;
				}
			}
		}
		fclose( pFile );
	}
}
void BSPictureMaker::SavePattern( CListManager<CListManager<char>>& cPatterns, const std::string & cPictureFName )
{
	int iNeedleCnt = cPatterns.GetPtr()[0].GetSize();
	int iRowCnt = cPatterns.GetSize();
	MakeSimplePicture( cPictureFName, cPatterns, iNeedleCnt, iRowCnt );
}
void BSPictureMaker::SavePattern( CListManager<CListManager<char>>& cPatterns, const int iRealNeedleCnt, const std::string & cPictureFName )
{
	int iNeedleCnt = iRealNeedleCnt;
	int iRowCnt = cPatterns.GetSize();
	MakeSimplePicture( cPictureFName, cPatterns, iNeedleCnt, iRowCnt );
}
void BSPictureMaker::CastingPattern4BS( CListManager<CListManager<char>>& cPatterns )
{
	const int iRowCnt = cPatterns.GetSize();
	CListManager<char>* pRowList = cPatterns.GetPtr();
	const int iNeedleCnt = pRowList[0].GetSize();
	for( int iRowIdx = 0; iRowIdx < iRowCnt; ++iRowIdx )
	{
		char* pRowData = pRowList[iRowIdx].GetPtr();
		for( int iNeedleIdx = 0; iNeedleIdx < iNeedleCnt; ++iNeedleIdx )
		{
			if( 7 == pRowData[iNeedleIdx] )
			{
				pRowData[iNeedleIdx] = BS_MUJI;
			}
			else
			{
				pRowData[iNeedleIdx] = BS_PEN;
			}
		}
	}
}
void BSPictureMaker::ReportFileAnalysis( const std::string & cPicturePath )
{
	FILE* pFile = NULL;
	FILE* pSaveFile = NULL;
	fopen_s( &pSaveFile, "./Report_BS.txt", "w" );
	fopen_s( &pFile, cPicturePath.c_str(), "rb" );
	if( NULL != pFile && NULL != pSaveFile )
	{
		for( int strIdx = 0; strIdx < 336; ++strIdx )
		{
			m_buffers[strIdx] = fgetc( pFile );
		}
		fprintf( pSaveFile, "BS 데이터 보고서\n" );
		short iNeedleCnt = 0;
		short iRowCnt = 0;
		memcpy( &iNeedleCnt, &m_buffers[9], sizeof( short ) );
		memcpy( &iRowCnt, &m_buffers[76], sizeof( short ) );
		short iSection1End = 0;
		memcpy( &iSection1End, &m_buffers[78], sizeof( short ) );
		short iSection1Cycle = 0;
		memcpy( &iSection1Cycle, &m_buffers[80], sizeof( short ) );
		fprintf( pSaveFile, "침수: %d Line: %d\n", iNeedleCnt, iRowCnt );
		fprintf( pSaveFile, "1번구간 끝: %d 반복횟수: %d\n", iSection1End, iSection1Cycle );
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
}
bool BSPictureMaker::GetHeader( int iCol, int iRow )
{
	bool bIsSuccess = true;
	FILE* pFile = NULL;
	//원래 형제기계 PICTURE그대로 들고옴
	memset( m_buffers, 0, sizeof( m_buffers ) );
	fopen_s( &pFile, BS_STANDARD_FILENAME, "rb" );
	if( pFile )
	{
		for( int strIdx = 0; strIdx < 336; ++strIdx )
		{
			m_buffers[strIdx] = fgetc( pFile );
		}
		//m_buffers[2] = iCol;
		//m_buffers[4] = iRow;
		fclose( pFile );

		int iDate = 32;
		memset( &m_buffers[iDate], 0, 10 );
		//날짜 작성
		std::string cDate = GetDate();
		for( auto iter = cDate.begin(); iter != cDate.end(); ++iter )
		{
			m_buffers[iDate++] = *iter;
		}
		//침수
		short iNeedleCnt = iCol;
		memcpy( &m_buffers[9], &iNeedleCnt, sizeof( iNeedleCnt ) );
		//고무 Default 50
		short iGomuCnt = BS_DEFAULT_GOMU_VALUE;
		memcpy( &m_buffers[49], &iGomuCnt, sizeof( iGomuCnt ) );
		short iMockCnt = BS_DEFAULT_MOCK_VALUE;
		memcpy( &m_buffers[59], &iMockCnt, sizeof( iMockCnt ) );
		short iSaveRowsCnt = iRow;
		memcpy( &m_buffers[76], &iSaveRowsCnt, sizeof( iSaveRowsCnt ) );
		memcpy( &m_buffers[78], &iSaveRowsCnt, sizeof( iSaveRowsCnt ) );
		//1번 구간 지정
		short iSection1Start = 0;
		short iSection1End = iSaveRowsCnt - 1;
		memcpy( &m_buffers[82], &iSection1Start, sizeof( iSection1Start ) );
		//1번 구간 지정
		memcpy( &m_buffers[84], &iSection1End, sizeof( iSection1End ) );
	}
	else
	{
		bIsSuccess = false;
		std::cout << "기본 파일이 없습니다." << BS_STANDARD_FILENAME << std::endl;
	}
	return bIsSuccess;
}

std::string BSPictureMaker::GetDate()
{
	std::string cDate;
	tm curr_tm = {};
	time_t curr_time = time( nullptr );

	localtime_s( &curr_tm, &curr_time );

	int curr_year = curr_tm.tm_year + 1900;
	int curr_month = curr_tm.tm_mon + 1;
	int curr_day = curr_tm.tm_mday;
	char tmpStr[256] = {};
	sprintf_s( tmpStr, sizeof( tmpStr ), "%04d.%02d.%02d", curr_year, curr_month, curr_day );
	cDate = tmpStr;
	std::cout << cDate << std::endl;
	return cDate;
}