#include "Functions.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <cstdlib>
//���� �а� �ؽ�Ʈ�� ���� ���
void Test1Func()
{
	std::string cStrFile1 = "OHL23-64.DAT";
	std::string cStrFile2 = "OHL23-64.PIC";
	printf( "���ϸ�: " );
	std::cin >> cStrFile1;
	cStrFile1 = "200X200_NO.PIC";
	cStrFile1 = "PDS_218.DAT";
	//cStrFile1 = cStrFile2;
	cStrFile1 = ".\\" + cStrFile1;
	FILE* pFP_Bef = NULL;
	FILE* pFP_Aft = NULL;

	int iCurrState = 0; //0 ���� ����
	static const int MAX_BUFF_SIZE = 2048;
	char cFileContent[MAX_BUFF_SIZE] = {};
	if( 0 == fopen_s( &pFP_Bef, cStrFile1.c_str(), "rb" ) &&
		0 == fopen_s( &pFP_Aft, "Result.txt", "w" ) )
	{
		iCurrState = CurrentState::eSuccess;
		//success
#if 0 // ���ڿ������� ī��
		while( NULL != fgets( cFileContent, MAX_BUFF_SIZE, pFP_Bef ) )
		{
			fputs( cFileContent, pFP_Aft );
		}
#else 
		int iGetC = 0;
		int iCount = 0;
		while( EOF != ( iGetC = fgetc( pFP_Bef ) ) )
		{
			iCount++;
			fprintf( pFP_Aft, "%d: ", iCount );
			for( int i = 0; i < 8; i++ )
			{
				fprintf( pFP_Aft, "%d", 1 & iGetC >> i );
				//fputc( , pFP_Aft );
			}
			fprintf( pFP_Aft, "\n" );
			if( iGetC == 0 )
			{
				//fprintf( pFP_Aft, "\n" );
			}
			//fprintf( pFP_Aft, " %c ", iGetC );
			if( iCount % 200 == 0 )
			{
				fprintf( pFP_Aft, "\n" );
			}
		}
#endif
		printf( "��(�Ѱ�: %d) \n", iCount );
		fclose( pFP_Bef );
		fclose( pFP_Aft );
	}
	else
	{
		iCurrState = CurrentState::eFail;
		std::cout << "Fail" << std::endl;
	}
}

//���� �� ���α׷� �ٸ������� ��ġ �ۼ� �� ���
void Test2Func()
{

	std::string cStrFile1 =
		//"PDS_211.DAT";
		"TEST_3.DAT";
		//"PDS_NONE.DAT";
		//"PDS_21.DAT";
		//"200X200_NO.PIC";
	//"200X100_1_1_0.PIC";
	//"200X100_2_1_1.PIC";
	std::string cStrFile2 =
		//"168x100_NO.PIC";
	//"PDS_TEST_100_NO.DAT";
	//"PDS_TEST_100_21.DAT";
	//"PDS_87.DAT";
	//"PDS_218.DAT";
		"PDS_31_22_13.DAT";
	
	
	//"200X100_2_1_1.PIC";
	FILE* pFP_1 = NULL;
	FILE* pFP_2 = NULL;

	FILE* pFileResult_1 = NULL;
	FILE* pFileResult_2 = NULL;

	int iCurrState = 0; //0 ���� ����
	static const int MAX_BUFF_SIZE = 2048;
	char cFileContent[MAX_BUFF_SIZE] = {};
	if( 0 == fopen_s( &pFP_1, cStrFile1.c_str(), "rb" ) &&
		0 == fopen_s( &pFP_2, cStrFile2.c_str(), "rb" ) )
	{
		int iTellCnt = 0;
		fseek( pFP_1, 0, SEEK_END );
		iTellCnt = ftell( pFP_1 );
		printf( "A SIZE: %d ", iTellCnt );
		fseek( pFP_1, 0, SEEK_SET );
		fseek( pFP_2, 0, SEEK_END );
		iTellCnt = ftell( pFP_2 );
		printf( "B SIZE: %d\n", iTellCnt );
		fseek( pFP_2, 0, SEEK_SET );

		iCurrState = CurrentState::eSuccess;
		int iGetC_1 = 0;
		int iCount = 0;
		int iGetC_2 = 0;
		while( 1 )
		{
			iCount++;
			bool iChk_1 = ( EOF != ( iGetC_1 = fgetc( pFP_1 ) ) );
			bool iChk_2 = ( EOF != ( iGetC_2 = fgetc( pFP_2 ) ) );
			if( false == iChk_1 && false == iChk_2 )
			{
				break;
			}
			if( iGetC_1 != iGetC_2 )
			{
				printf( "Count: %d ", iCount );
				printf( "A: (" );
				if( iChk_1 )
				{
					for( int i = 0; i < 8; i++ )
					{
						printf( "%d", 1 & iGetC_1 >> i );
						//fputc( , pFP_Aft );
					}
				}
				printf( ") " );
				printf( "B: (" );
				if( iChk_2 )
				{
					for( int i = 0; i < 8; i++ )
					{
						printf( "%d", 1 & iGetC_2 >> i );
						//fputc( , pFP_Aft );
					}
				}
				printf( ")\n" );
			}
			//if( iGetC == 0 )
			{
				//fprintf( pFP_Aft, "\n" );
			}
			//fprintf( pFP_Aft, " %c ", iGetC );
			if( iCount % 200 == 0 )
			{
				//printf( "\n" );
			}
		}
		printf( "��(�Ѱ�: %d) \n", iCount );
		fclose( pFP_1 );
		fclose( pFP_2 );
	}
	else
	{
		iCurrState = CurrentState::eFail;
		std::cout << "Fail" << std::endl;
	}
}

//���� ALL Short�� �ۼ��� �� ���� �о����
void Test3Func()
{
	std::string cStrFile1 =
		"200X200_NO.PIC";
	//"200X100_1_1_0.PIC";
	//"200X100_2_1_1.PIC";
	std::string cStrFile2 =
		"168x100_NO.PIC";
	//"200X100_2_1_1.PIC";
	FILE* pFP_1 = NULL;
	FILE* pFP_2 = NULL;

	FILE* pFileResult_1 = NULL;
	FILE* pFileResult_2 = NULL;

	int iCurrState = 0; //0 ���� ����
	static const int MAX_BUFF_SIZE = 2048;
	char cFileContent[MAX_BUFF_SIZE] = {};
	if( 0 == fopen_s( &pFP_1, cStrFile1.c_str(), "rb" ) &&
		0 == fopen_s( &pFP_2, cStrFile2.c_str(), "rb" ) )
	{
		int iTellCnt = 0;
		fseek( pFP_1, 0, SEEK_END );
		iTellCnt = ftell( pFP_1 );
		printf( "A SIZE: %d ", iTellCnt );
		fseek( pFP_1, 0, SEEK_SET );
		fseek( pFP_2, 0, SEEK_END );
		iTellCnt = ftell( pFP_2 );
		printf( "B SIZE: %d\n", iTellCnt );
		fseek( pFP_2, 0, SEEK_SET );

		iCurrState = CurrentState::eSuccess;
		int iGetC_1 = 0;
		int iCount = 0;
		int iGetC_2 = 0;
		while( 1 )
		{
			iCount++;
			bool iChk_1 = ( EOF != ( iGetC_1 = fgetc( pFP_1 ) ) );
			short iNumber = 0;
			bool iChk_2 = ( EOF != ( iGetC_2 = fgetc( pFP_2 ) ) );
			if( false == iChk_1 && false == iChk_2 )
			{
				break;
			}
			if( iGetC_1 != iGetC_2 )
			{
				printf( "Count: %d ", iCount );
				printf( "A: (" );
				if( iChk_1 )
				{
					if( 0 == iCount % 2 )
					{
						for( int i = 0; i < 8; i++ )
						{
							printf( "%d", 1 & iGetC_1 >> i );
							iNumber |= iGetC_1 >> i;
						}
					}
					else
					{
						for( int i = 0; i < 8; i++ )
						{
							iNumber |= iGetC_1 >> i;
						}
					}
				}
				printf( ") " );
				printf( "B: (" );
				if( iChk_2 )
				{
					for( int i = 0; i < 8; i++ )
					{
						printf( "%d", 1 & iGetC_2 >> i );
						//fputc( , pFP_Aft );
					}
				}
				printf( ")\n" );
			}
			//if( iGetC == 0 )
			{
				//fprintf( pFP_Aft, "\n" );
			}
			//fprintf( pFP_Aft, " %c ", iGetC );
			if( iCount % 200 == 0 )
			{
				//printf( "\n" );
			}
		}
		printf( "��(�Ѱ�: %d) \n", iCount );
		fclose( pFP_1 );
		fclose( pFP_2 );
	}
	else
	{
		iCurrState = CurrentState::eFail;
		std::cout << "Fail" << std::endl;
	}
}

//���� �а� ���̳ʸ����� �������ְ� ����ϵ��� ����
void Test4Func()
{
	std::string cStrFile1 = "OHL23-64.DAT";
	std::string cStrFile2 = "OHL23-64.PIC";
	printf( "���ϸ�: " );
	//std::cin >> cStrFile1;
	//cStrFile1 = "168X100_NO.PIC";
	cStrFile1 = "200X100_11_21.PIC";
	//cStrFile1 = cStrFile2;
	cStrFile1 = ".\\" + cStrFile1;
	FILE* pFP_Bef = NULL;
	FILE* pFP_Aft = NULL;

	int iCurrState = 0; //0 ���� ����
	static const int MAX_BUFF_SIZE = 2048;
	char cFileContent[MAX_BUFF_SIZE] = {};
	if( 0 == fopen_s( &pFP_Bef, cStrFile1.c_str(), "rb" ) &&
		0 == fopen_s( &pFP_Aft, "Result.txt", "w" ) )
	{
		iCurrState = CurrentState::eSuccess;
		//success
#if 0 // ���ڿ������� ī��
		while( NULL != fgets( cFileContent, MAX_BUFF_SIZE, pFP_Bef ) )
		{
			fputs( cFileContent, pFP_Aft );
		}
#else 
		int iGetC = 0;
		int iCount = 0;
		while( EOF != ( iGetC = fgetc( pFP_Bef ) ) )
		{
			iCount++;
			fprintf( pFP_Aft, "%d: ", iCount );
#if 0
			for( int i = 0; i < 8; i++ )
			{
				fprintf( pFP_Aft, "%d", 1 & iGetC >> i );
				//fputc( , pFP_Aft );
			}
#else
			fprintf( pFP_Aft, "%d", iGetC );
#endif
			fprintf( pFP_Aft, "\n" );
			if( iGetC == 0 )
			{
				//fprintf( pFP_Aft, "\n" );
			}
			//fprintf( pFP_Aft, " %c ", iGetC );
			if( iCount % 200 == 0 )
			{
				fprintf( pFP_Aft, "\n" );
			}
		}
#endif
		printf( "��(�Ѱ�: %d) \n", iCount );
		fclose( pFP_Bef );
		fclose( pFP_Aft );
	}
	else
	{
		iCurrState = CurrentState::eFail;
		std::cout << "Fail" << std::endl;
	}
}

//��� ����  1024Byte�� ����
void Test5Func()
{
	unsigned char strHeader[1024] = {};
	strHeader[0] = 78;
	strHeader[1] = 66;
	strHeader[2] = 200;		//200ħ
	strHeader[3] = 0;		//����
	strHeader[4] = 200;		//����
	strHeader[5] = 0;		//����
							//������ �⺻ ���Ͽ��� �״�ε����� 1024����
}
