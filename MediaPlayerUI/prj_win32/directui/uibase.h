#ifndef __DUI_BASE_H__
#define __DUI_BASE_H__

namespace DirectUICore {
/////////////////////////////////////////////////////////////////////////////////////
//
#ifndef ASSERT
#define ASSERT(expr)  _ASSERTE(expr)      // 判断表达式是否为NULL或FALSE
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
	emFileLinkErrInvalide = 0,      // 无效错误码
	emFileLinkErr,					// 打开文件链接无效
	emFolderLinkErr,				// 打开文件夹链接无效
	emInvalidLinkErr,				// 链接无效，无法打开
};


/////////////////////////////////////////////////////////////////////////////////////
// 用于构建资源名称或资源ID号

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
// 点的封装类，支持LPARAM构建点

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
// 大小封装

class DIRECTUI_API CDirectSize : public tagSIZE
{
public:
    CDirectSize();
    CDirectSize( const SIZE& src );
    CDirectSize( const RECT rc );
    CDirectSize( int cx, int cy );
};


/////////////////////////////////////////////////////////////////////////////////////
// 区域封装

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
         
    int GetWidth() const;			// 获取宽度
    int GetHeight() const;			// 获取高度
    void Empty();					// 清空
    bool IsNull() const;			// 是否为Empty，IsEmpty
    void Join( const RECT& rc );	// 支持区域合并
    void ResetOffset();				// 重新设置区域偏移(移动)操作
    void Normalize();				// 正规化(使得left<right,top<bottom)
    void Offset( int cx, int cy );	// 区域偏移(移动)操作
    void Inflate( int cx, int cy );	// 区域膨胀
    void Deflate( int cx, int cy );	// 区域收缩
    void Union( CDirectRect& rc );	// 区域并操作
	
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
// 指针数组类

class DIRECTUI_API CStdPtrArray
{
public:
    CStdPtrArray( int iPreallocSize = 0 );
	CStdPtrArray( const CStdPtrArray& src );
    ~CStdPtrArray();

    void Empty();								// 清空记录
	void Resize( int iSize );					// 重新分配内存大小(注意:之前的记录丢失)
    bool IsEmpty() const;						// 是否为空数组
	int Find( LPVOID iIndex ) const;			// 查询指定元素的索引号
	bool Add( LPVOID pData );					// 在指针集合中添加新数据
	bool SetAt( int iIndex, LPVOID pData );		// 设置指定索引号处的新数据
	bool InsertAt( int iIndex, LPVOID pData );	// 在指定的索引号处插入数据
	bool InsertAt( int iIndex, CStdPtrArray& src ); // 在指定的索引号处插入数组
	bool Remove( int iIndex );					// 移除指定索引号的数据
	bool Remove( int iStartIndex, int iEndIndex ); // 移除指定索引号间的数据
	int GetSize() const;						// 获取指针数量
	LPVOID* GetData();							// 获取全部的数据
	LPVOID GetAt( int iIndex ) const;			// 查询索引号所对应的元素
	LPVOID operator[] ( int nIndex ) const;     // 支持[]查找元素

protected:
	// realloc返回的类型是void*，而CStdPtrArray中存放的是void*元素，
	// 所以该成员变量设置成void**类型，所以将realloc返回的值强转了一下
    LPVOID* m_ppVoid;	// 数据指针
    int m_nCount;		// 指针数量
    int m_nAllocated;	// 内存已分配大小
};


/////////////////////////////////////////////////////////////////////////////////////
// 自定义数据长度数组类

class DIRECTUI_API CStdValArray
{
public:
    CStdValArray( int iElementSize, int iPreallocSize = 0 ); // 指定元素大小，预分配数量
    ~CStdValArray();

	void Empty();							// 清空数据
	bool IsEmpty() const;					// 是否为空数组
    bool Add( LPCVOID pData );				// 追加数据
	bool Remove( int iIndex );				// 移除指定索引号得数据
	int GetSize() const;					// 获取当前保存元素的个数
	LPVOID GetData();						// 获取数据
	LPVOID GetAt( int iIndex ) const;		// 获取指定索引号处的数据
	LPVOID operator[] ( int nIndex ) const;	// 支持[]查找元素

protected:
    LPBYTE m_pVoid;		// 指针数据
    int m_iElementSize;	// 元素大小
    int m_nCount;		// 元素数量
    int m_nAllocated;	// 当前分配的可用容量
};


/////////////////////////////////////////////////////////////////////////////////////
// 字符串类

class DIRECTUI_API CStdString
{
public:
    enum { MAX_LOCAL_STRING_LEN = 16 };

    CStdString();									// 初始化字符串类
    CStdString( const TCHAR ch );

// 	//添加两个构造函数，支持窄字节和宽字节的自动转换，add by zzx 2013/09/06
#ifdef _UNICODE
	CStdString( const LPCSTR lpStr );
#else
	CStdString( const LPCWSTR lpwStr );
#endif

	CStdString( const CStdString& src );
	CStdString( LPCTSTR lpsz, int nLen = -1 );		// 长度为-1由程序自己判断长度
    ~CStdString();

	void Empty();									// 清空字符串
	int GetLength() const;							// 获取字符串长度
	bool IsEmpty() const;							// 字符串是否为空串
	TCHAR GetAt( int nIndex ) const;				// 获取指定位置处的字符
	void Append( LPCTSTR pstr );					// 字符串追加操作
	void Assign( LPCTSTR pstr, int nLength = -1 );	// 分配内存赋值
	LPCTSTR GetData();								// 获取字符串指针
	void SetAt( int nIndex, TCHAR ch );				// 在指定索引处设置字符
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

    int Compare( LPCTSTR pstr ) const;					// 字符串比较
	int CompareNoCase( LPCTSTR pstr ) const;			// 字符串忽略大小写比较

	void MakeUpper();									// 字符串转换为大写
	void MakeLower();									// 字符串转换为小写

	CStdString Left( int nLength ) const;				// 从左边截取指定长度的子串
	CStdString Mid( int iPos, int nLength = -1 ) const;	// 截取中间字符串
	CStdString Right( int nLength ) const;				// 从右开始截取指定长度的字符串

	CStdString SpanIncluding( LPCTSTR lpStrFilter ) const;
	CStdString SpanExcluding( LPCTSTR lpStrFilter ) const;

	CStdString GetAllSpanIncluding( LPCTSTR lpStrFilter );
	CStdString GetAllSpanExcluding( LPCTSTR lpStrFilter );

	void CopySpanIncluding( LPWSTR dest, LPWSTR src, LPCTSTR lpStrFilter );
	void CopySpanExcluding( LPWSTR dest, LPWSTR src, LPCTSTR lpStrFilter );

	int Find( TCHAR ch, int iPos = 0 ) const;			// 从指定位置开始寻找匹配字符的位置
	int Find( LPCTSTR pstr, int iPos = 0 ) const;		// 重指定位置开始寻找匹配字符串的位置
	int ReverseFind( TCHAR ch ) const;					// 反向查询字符位置
	int Replace( LPCTSTR pstrFrom, LPCTSTR pstrTo );	// 将匹配的字符子串用指定字符串替换
	int Delete( int iIndex, int nCount = 1 );
	void TrimLeft();
	void TrimRight();
	void Trim();
	
	int __cdecl Format( LPCTSTR pstrFormat, ... );		// 一次格式化1024长度的字符串格式化
	int __cdecl SmallFormat( LPCTSTR pstrFormat, ... );	// 最长63位的字符串格式化

protected:
    LPTSTR m_pstr;								// 字符指针
	TCHAR m_szBuffer[MAX_LOCAL_STRING_LEN];	    // 字符缓冲区
};

/////////////////////////////////////////////////////////////////////////////////////
//
// TITEM结构
struct TITEM
{
    CStdString Key;			// 键
    LPVOID Data;			// 值
	struct TITEM* pNext;	// 下一个TITEM结构体指针
};

class DIRECTUI_API CStdStringPtrMap
{
public:
	CStdStringPtrMap( int nSize = 83 );			// 构建字符串Map集合
    ~CStdStringPtrMap();

	void Resize( int nSize = 83 );				// 重新分配集合大小
	LPVOID Find( LPCTSTR key ) const;			// 更具键查询字符串指针
	bool Insert( LPCTSTR key, LPVOID pData );	// 插入数据
	LPVOID Set( LPCTSTR key, LPVOID pData );	// 设置指定键的数据
	bool Remove( LPCTSTR key );					// 通过键移除数据
	int GetSize() const;						// 获取大小
	LPCTSTR GetAt( int iIndex ) const;			// 获取指定索引处得字符串
	LPCTSTR operator[] ( int nIndex ) const;	// 通过下标获取字符串

protected:
	TITEM** m_aT;	// TITEM双指针
    int m_nBuckets; // 容器容量
};

///////////////////////////////////////////////////////////////////////
// 等待光标

class DIRECTUI_API CWaitCursor
{
public:
	CWaitCursor();			// 设置成等待光标
	~CWaitCursor();			// 还原为之前的光标

protected:
	HCURSOR m_hOrigCursor;	// 替换前光标
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
