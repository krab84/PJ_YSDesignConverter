#pragma once
#include<cstdio>
#include<iostream>
//클래스 할당은 주의 필요
template<typename T>
class CListManager
{
public:
	T* GetPtr();
	int GetSize()const;
	bool ReSize( const int iReSize );
	explicit CListManager()
		: m_List( nullptr )
		, m_Size( 0 )
	{
	}

	CListManager( CListManager & charm ) = default;
	~CListManager()
	{
		if( nullptr != m_List )
		{
			delete[] m_List;
			m_List = nullptr;
		}
	}
private:
	T* m_List;
	int m_Size;
};


template<typename T>
T * CListManager<T>::GetPtr()
{
	return m_List;
}

template<typename T>
inline int CListManager<T>::GetSize() const
{
	return m_Size;
}

template<typename T>
bool CListManager<T>::ReSize( const int iReSize )
{
	bool bIsSuccess = true;
	if( iReSize > 0 )
	{
		if( 1 )
		//if( iReSize > GetSize() )
		{
			T* pTmp = new T[iReSize];
			if( 0 == GetSize() )
			{
				// 복사할 것 없음.
			}
			else
			{
				for( int i = 0; i < iReSize; ++i )
				{
					pTmp[i] = m_List[i];
				}
				delete[] m_List;
			}
			m_List = pTmp;
			m_Size = iReSize;
		}
		else
		{
			//교체 안함. 그냥 그대로 둠 
		}
	}
	else
	{
		bIsSuccess = false;
	}
	return bIsSuccess;
}
