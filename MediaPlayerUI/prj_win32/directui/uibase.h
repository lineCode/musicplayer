#ifndef __DUI_BASE_H__
#define __DUI_BASE_H__

namespace DirectUICore {
/////////////////////////////////////////////////////////////////////////////////////
//
#ifndef ASSERT
#define ASSERT(expr)  _ASSERTE(expr)      // �жϱ��ʽ�Ƿ�ΪNULL��FALSE
#endif

#ifdef _DEBUG
#ifndef TRACE
#define TRACE __Trace
#endif
#define TRACEMSG __TraceMsg
#else
#ifndef TRACE
#define TRACE
#endif
#define TRACEMSG _T("")
#endif

void DIRECTUI_API __Trace( LPCTSTR pstrFormat, ... );
LPCTSTR DIRECTUI_API __TraceMsg( UINT uMsg );

enum DIRECTUI_API EmFileLinkErrCode
{
	emFileLinkErrInvalide = 0,      // ��Ч������
	emFileLinkErr,					// ���ļ�������Ч
	emFolderLinkErr,				// ���ļ���������Ч
	emInvalidLinkErr,				// ������Ч���޷���
};


/////////////////////////////////////////////////////////////////////////////////////
// ���ڹ�����Դ���ƻ���ԴID��

class DIRECTUI_API STRINGorID
{
public:
    STRINGorID( LPCTSTR lpString ) : m_lpstr( lpString )
    { }
    STRINGorID( UINT nID ) : m_lpstr( MAKEINTRESOURCE(nID) )
    { }
    LPCTSTR m_lpstr;
};

/////////////////////////////////////////////////////////////////////////////////////
// ��ķ�װ�֧࣬��LPARAM������

class DIRECTUI_API CDirectPoint : public tagPOINT
{
public:
    CDirectPoint();
    CDirectPoint( const POINT& src );
    CDirectPoint( int x, int y );
    CDirectPoint( LPARAM lParam );
	void Offset( int x, int y)
	{
		this->x += x;
		this->y += y;
	}

	void SetPoint(int X, int Y)
	{
		x = X;
		y = Y;
	}
	BOOL operator!=( POINT point) const
	{
		return (x != point.x || y != point.y);
	}
};


/////////////////////////////////////////////////////////////////////////////////////
// ��С��װ

class DIRECTUI_API CDirectSize : public tagSIZE
{
public:
    CDirectSize();
    CDirectSize( const SIZE& src );
    CDirectSize( const RECT rc );
    CDirectSize( int cx, int cy );
};


/////////////////////////////////////////////////////////////////////////////////////
// �����װ

class DIRECTUI_API CDirectRect : public tagRECT
{
public:
    CDirectRect();
    CDirectRect( const RECT& src );	
    CDirectRect( int iLeft, int iTop, int iRight, int iBottom );
	
	CDirectRect::CDirectRect(CDirectPoint topLeft, CDirectPoint bottomRight)
	{
		left = topLeft.x;
		top = topLeft.y;
		right = bottomRight.x;
		bottom = bottomRight.y;
	}
         
    int GetWidth() const;			// ��ȡ���
    int GetHeight() const;			// ��ȡ�߶�
    void Empty();					// ���
    bool IsNull() const;			// �Ƿ�ΪEmpty��IsEmpty
    void Join( const RECT& rc );	// ֧������ϲ�
    void ResetOffset();				// ������������ƫ��(�ƶ�)����
    void Normalize();				// ���滯(ʹ��left<right,top<bottom)
    void Offset( int cx, int cy );	// ����ƫ��(�ƶ�)����
    void Inflate( int cx, int cy );	// ��������
    void Deflate( int cx, int cy );	// ��������
    void Union( CDirectRect& rc );	// ���򲢲���
	
	void SetRectEmpty()
	{
		::SetRectEmpty(this);
	}

	void SetRect(int x1, int y1, int x2, int y2) 
	{
		::SetRect(this, x1, y1, x2, y2);
	}

	BOOL PtInRect(POINT point) const
	{
		return ::PtInRect(this, point);
	}

	void OffsetRect(int x, int y)
	{
		::OffsetRect(this, x, y);
	}

	BOOL IsRectEmpty()
	{
		return ::IsRectEmpty(this);
	}

	BOOL EqualRect(LPCRECT lpRect) const
	{
		return ::EqualRect(this, lpRect);
	}
	void CopyRect( LPCRECT lpSrcRect)
	{
		::CopyRect(this, lpSrcRect);
	}
};

/////////////////////////////////////////////////////////////////////////////////////
// ָ��������

class DIRECTUI_API CStdPtrArray
{
public:
    CStdPtrArray( int iPreallocSize = 0 );
	CStdPtrArray( const CStdPtrArray& src );
    ~CStdPtrArray();

    void Empty();								// ��ռ�¼
	void Resize( int iSize );					// ���·����ڴ��С(ע��:֮ǰ�ļ�¼��ʧ)
    bool IsEmpty() const;						// �Ƿ�Ϊ������
	int Find( LPVOID iIndex ) const;			// ��ѯָ��Ԫ�ص�������
	bool Add( LPVOID pData );					// ��ָ�뼯�������������
	bool SetAt( int iIndex, LPVOID pData );		// ����ָ�������Ŵ���������
	bool InsertAt( int iIndex, LPVOID pData );	// ��ָ���������Ŵ���������
	bool InsertAt( int iIndex, CStdPtrArray& src ); // ��ָ���������Ŵ���������
	bool Remove( int iIndex );					// �Ƴ�ָ�������ŵ�����
	bool Remove( int iStartIndex, int iEndIndex ); // �Ƴ�ָ�������ż������
	int GetSize() const;						// ��ȡָ������
	LPVOID* GetData();							// ��ȡȫ��������
	LPVOID GetAt( int iIndex ) const;			// ��ѯ����������Ӧ��Ԫ��
	LPVOID operator[] ( int nIndex ) const;     // ֧��[]����Ԫ��

protected:
	// realloc���ص�������void*����CStdPtrArray�д�ŵ���void*Ԫ�أ�
	// ���Ըó�Ա�������ó�void**���ͣ����Խ�realloc���ص�ֵǿת��һ��
    LPVOID* m_ppVoid;	// ����ָ��
    int m_nCount;		// ָ������
    int m_nAllocated;	// �ڴ��ѷ����С
};


/////////////////////////////////////////////////////////////////////////////////////
// �Զ������ݳ���������

class DIRECTUI_API CStdValArray
{
public:
    CStdValArray( int iElementSize, int iPreallocSize = 0 ); // ָ��Ԫ�ش�С��Ԥ��������
    ~CStdValArray();

	void Empty();							// �������
	bool IsEmpty() const;					// �Ƿ�Ϊ������
    bool Add( LPCVOID pData );				// ׷������
	bool Remove( int iIndex );				// �Ƴ�ָ�������ŵ�����
	int GetSize() const;					// ��ȡ��ǰ����Ԫ�صĸ���
	LPVOID GetData();						// ��ȡ����
	LPVOID GetAt( int iIndex ) const;		// ��ȡָ�������Ŵ�������
	LPVOID operator[] ( int nIndex ) const;	// ֧��[]����Ԫ��

protected:
    LPBYTE m_pVoid;		// ָ������
    int m_iElementSize;	// Ԫ�ش�С
    int m_nCount;		// Ԫ������
    int m_nAllocated;	// ��ǰ����Ŀ�������
};


/////////////////////////////////////////////////////////////////////////////////////
// �ַ�����

class DIRECTUI_API CStdString
{
public:
    enum { MAX_LOCAL_STRING_LEN = 16 };

    CStdString();									// ��ʼ���ַ�����
    CStdString( const TCHAR ch );

// 	//����������캯����֧��խ�ֽںͿ��ֽڵ��Զ�ת����add by zzx 2013/09/06
#ifdef _UNICODE
	CStdString( const LPCSTR lpStr );
#else
	CStdString( const LPCWSTR lpwStr );
#endif

	CStdString( const CStdString& src );
	CStdString( LPCTSTR lpsz, int nLen = -1 );		// ����Ϊ-1�ɳ����Լ��жϳ���
    ~CStdString();

	void Empty();									// ����ַ���
	int GetLength() const;							// ��ȡ�ַ�������
	bool IsEmpty() const;							// �ַ����Ƿ�Ϊ�մ�
	TCHAR GetAt( int nIndex ) const;				// ��ȡָ��λ�ô����ַ�
	void Append( LPCTSTR pstr );					// �ַ���׷�Ӳ���
	void Assign( LPCTSTR pstr, int nLength = -1 );	// �����ڴ渳ֵ
	LPCTSTR GetData();								// ��ȡ�ַ���ָ��
	void SetAt( int nIndex, TCHAR ch );				// ��ָ�������������ַ�
    operator LPCTSTR() const;

    TCHAR operator[] ( int nIndex ) const;
    const CStdString& operator=( const CStdString& src );
    const CStdString& operator=( const TCHAR ch );
    const CStdString& operator=( LPCTSTR pstr );
#ifdef _UNICODE
    const CStdString& CStdString::operator=( LPCSTR lpStr );
    const CStdString& CStdString::operator+=( LPCSTR lpStr );
#else
    const CStdString& CStdString::operator=( LPCWSTR lpwStr );
    const CStdString& CStdString::operator+=( LPCWSTR lpwStr );
#endif
    CStdString operator+( const CStdString& src ) const;
    CStdString operator+( LPCTSTR pstr ) const;
    const CStdString& operator+=( const CStdString& src );
    const CStdString& operator+=( LPCTSTR pstr );
    const CStdString& operator+=( const TCHAR ch );

    bool operator == ( LPCTSTR str ) const;
    bool operator != ( LPCTSTR str ) const;
    bool operator <= ( LPCTSTR str ) const;
    bool operator <  ( LPCTSTR str ) const;
    bool operator >= ( LPCTSTR str ) const;
    bool operator >  ( LPCTSTR str ) const;

    int Compare( LPCTSTR pstr ) const;					// �ַ����Ƚ�
	int CompareNoCase( LPCTSTR pstr ) const;			// �ַ������Դ�Сд�Ƚ�

	void MakeUpper();									// �ַ���ת��Ϊ��д
	void MakeLower();									// �ַ���ת��ΪСд

	CStdString Left( int nLength ) const;				// ����߽�ȡָ�����ȵ��Ӵ�
	CStdString Mid( int iPos, int nLength = -1 ) const;	// ��ȡ�м��ַ���
	CStdString Right( int nLength ) const;				// ���ҿ�ʼ��ȡָ�����ȵ��ַ���

	CStdString SpanIncluding( LPCTSTR lpStrFilter ) const;
	CStdString SpanExcluding( LPCTSTR lpStrFilter ) const;

	CStdString GetAllSpanIncluding( LPCTSTR lpStrFilter );
	CStdString GetAllSpanExcluding( LPCTSTR lpStrFilter );

	void CopySpanIncluding( LPWSTR dest, LPWSTR src, LPCTSTR lpStrFilter );
	void CopySpanExcluding( LPWSTR dest, LPWSTR src, LPCTSTR lpStrFilter );

	int Find( TCHAR ch, int iPos = 0 ) const;			// ��ָ��λ�ÿ�ʼѰ��ƥ���ַ���λ��
	int Find( LPCTSTR pstr, int iPos = 0 ) const;		// ��ָ��λ�ÿ�ʼѰ��ƥ���ַ�����λ��
	int ReverseFind( TCHAR ch ) const;					// �����ѯ�ַ�λ��
	int Replace( LPCTSTR pstrFrom, LPCTSTR pstrTo );	// ��ƥ����ַ��Ӵ���ָ���ַ����滻
	int Delete( int iIndex, int nCount = 1 );
	void TrimLeft();
	void TrimRight();
	void Trim();
	
	int __cdecl Format( LPCTSTR pstrFormat, ... );		// һ�θ�ʽ��1024���ȵ��ַ�����ʽ��
	int __cdecl SmallFormat( LPCTSTR pstrFormat, ... );	// �63λ���ַ�����ʽ��

protected:
    LPTSTR m_pstr;								// �ַ�ָ��
	TCHAR m_szBuffer[MAX_LOCAL_STRING_LEN];	    // �ַ�������
};

/////////////////////////////////////////////////////////////////////////////////////
//
// TITEM�ṹ
struct TITEM
{
    CStdString Key;			// ��
    LPVOID Data;			// ֵ
	struct TITEM* pNext;	// ��һ��TITEM�ṹ��ָ��
};

class DIRECTUI_API CStdStringPtrMap
{
public:
	CStdStringPtrMap( int nSize = 83 );			// �����ַ���Map����
    ~CStdStringPtrMap();

	void Resize( int nSize = 83 );				// ���·��伯�ϴ�С
	LPVOID Find( LPCTSTR key ) const;			// ���߼���ѯ�ַ���ָ��
	bool Insert( LPCTSTR key, LPVOID pData );	// ��������
	LPVOID Set( LPCTSTR key, LPVOID pData );	// ����ָ����������
	bool Remove( LPCTSTR key );					// ͨ�����Ƴ�����
	int GetSize() const;						// ��ȡ��С
	LPCTSTR GetAt( int iIndex ) const;			// ��ȡָ�����������ַ���
	LPCTSTR operator[] ( int nIndex ) const;	// ͨ���±��ȡ�ַ���

protected:
	TITEM** m_aT;	// TITEM˫ָ��
    int m_nBuckets; // ��������
};

///////////////////////////////////////////////////////////////////////
// �ȴ����

class DIRECTUI_API CWaitCursor
{
public:
	CWaitCursor();			// ���óɵȴ����
	~CWaitCursor();			// ��ԭΪ֮ǰ�Ĺ��

protected:
	HCURSOR m_hOrigCursor;	// �滻ǰ���
};


class CVariant : public VARIANT
{
public:
	CVariant() 
	{ 
		VariantInit(this); 
	}
	CVariant(int i)
	{
		VariantInit(this);
		this->vt = VT_I4;
		this->intVal = i;
	}
	CVariant(float f)
	{
		VariantInit(this);
		this->vt = VT_R4;
		this->fltVal = f;
	}
	CVariant(LPOLESTR s)
	{
		VariantInit(this);
		this->vt = VT_BSTR;
		this->bstrVal = s;
	}
	CVariant(IDispatch *disp)
	{
		VariantInit(this);
		this->vt = VT_DISPATCH;
		this->pdispVal = disp;
	}

	~CVariant() 
	{ 
		VariantClear(this); 
	}
};
} // namespace DirectUICore

#endif // __UIBASE_H__
