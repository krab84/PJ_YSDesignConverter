#pragma once

#include<vector>
#include<string>

template<typename T>
class CListManager;

/*
HU Picture Maker

Header
1024 Byte�� �⺻Ʋ
Pattern
����*Pen��ȣ ������ �ۼ��Ǿ�����
eg 1) 200ħ ����
	200 7 200 7 200 7 200 7 200 7 200 7 200 7 200 7 200 7 200 7 200 7 200 7 200 7
eg 2) 200ħ 1��1
	1 4 1 7 1 4 1 7 1 4 1 7 1 4 1 7 1 4 1 7 1 4 1 7 1 4 1 7 1 4 1 7 1 4 1 7 1 4 1 7 1 4 1 7 1 4 1 7
End
0,0 ���� ���� 
*/

class HJPictureMaker
{
	static const int HJ_MUJI = 7;
	static const int HJ_PEN = 4;
public:
	void MakePicture( const std::string& cPictureFName,
					  char** pPatterns,
					  const int iColCnt = 200, const int iRowCnt = 100 );

	void MakePicture( const std::string& cPictureFName,
					  CListManager<CListManager<char>>& cPatterns,
					  const int iColCnt = 200, const int iRowCnt = 100 );

	//Picture������ �а� cPatterns�� �ִ´�.
	//return PatternList
	void LoadPattern(
		CListManager<CListManager<char>>& cPatterns,
		const std::string & cPictureFName );

	void LoadPattern(
		CListManager<CListManager<char>>& cPatterns,
		int& iRealNeedleCnt,
		const std::string & cPictureFName );

	//return PictureFile
	void SavePattern( 
		CListManager<CListManager<char>>& cPatterns, 
		const std::string & cPictureFName );

	void CastingPattern4HJ(
		CListManager<CListManager<char>>& cPatterns );
	
	void ReportFileAnalysis( const std::string & cPicturePath );
	//member Function private

	int GetRealNeedleCnt( const int iColCnt );
private:

	bool GetHeader( int iCol, int iRow );
	//member variance
private:
	char m_buffers[1024] = {};
};
