#pragma once
#include <string>

/*
	BS Picture Maker

	Header
	1~16은 고정된것 같음
	10번은 침수
	17~32는 파일명 같음
	33 날짜
	50: 고무
	52~53: 자수시작
	54~55: 자수높이

	60 목에 작성한 값
	63~64: 바닥무늬1
	66~67: 바닥무늬2
	69~70: 바닥무늬3
	72~73: 바닥무늬4
	77~78: 전체저장 LINE수 END 두자리같음 
	79~80: 1번구간 END
	81~82: 1번 반복횟수
	83: START로부터 Offset
	85: End로부터 Offset
	87~88: 2번 반복횟수

	337~N:	반복한만큼 데이터들 그대로 적재후에
	7바이트 공석
*/

template<typename T>
class CListManager;

class BSPictureMaker
{
	static const int BS_MUJI = 0;
	static const int BS_PEN = 1;
public:
	void MakeSimplePicture(
		const std::string& cPictureFName,
		char** pPatterns,
		const int iColCnt = 200, const int iRowCnt = 100 );
	void MakeSimplePicture(
		const std::string& cPictureFName,
		CListManager<CListManager<char>>& cPatterns,
		const int iColCnt = 200, const int iRowCnt = 100 );
	void LoadPattern( CListManager<CListManager<char>>& cPatterns, const std::string & cPictureFName );
	void SavePattern( CListManager<CListManager<char>>& cPatterns, const std::string & cPictureFName );
	void SavePattern( CListManager<CListManager<char>>& cPatterns, const int iRealNeedleCnt, const std::string & cPictureFName );
	void CastingPattern4BS(
		CListManager<CListManager<char>>& cPatterns );
	void ReportFileAnalysis( const std::string & cPicturePath );
private:
	bool GetHeader( int iCol, int iRow );
	std::string GetDate();
	char m_buffers[1024] = {};
};