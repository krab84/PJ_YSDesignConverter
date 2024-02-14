#pragma once
#include <string>

/*
	BS Picture Maker

	Header
	1~16�� �����Ȱ� ����
	10���� ħ��
	17~32�� ���ϸ� ����
	33 ��¥
	50: ��
	52~53: �ڼ�����
	54~55: �ڼ�����

	60 �� �ۼ��� ��
	63~64: �ٴڹ���1
	66~67: �ٴڹ���2
	69~70: �ٴڹ���3
	72~73: �ٴڹ���4
	77~78: ��ü���� LINE�� END ���ڸ����� 
	79~80: 1������ END
	81~82: 1�� �ݺ�Ƚ��
	83: START�κ��� Offset
	85: End�κ��� Offset
	87~88: 2�� �ݺ�Ƚ��

	337~N:	�ݺ��Ѹ�ŭ �����͵� �״�� �����Ŀ�
	7����Ʈ ����
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