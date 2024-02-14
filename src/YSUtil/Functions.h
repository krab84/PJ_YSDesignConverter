#pragma once
namespace CurrentState
{
	enum ENUM : short
	{
		eSuccess = 0,
		eFail
	};
}


//파일 읽고 텍스트로 만들어서 출력
void Test1Func();

//파일 비교 프로그램 다른지점의 위치 작성 후 출력
void Test2Func();

//대충 ALL Short로 작성된 것 같음 읽어보겠음
void Test3Func();

//파일 읽고 바이너리에서 읽을수있게 출력하도록 변경
void Test4Func();

//헤더 구성  1024Byte에 대해
void Test5Func();
