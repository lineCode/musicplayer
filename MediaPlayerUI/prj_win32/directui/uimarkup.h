#ifndef __DUI_MARKUP_H__
#define __DUI_MARKUP_H__

namespace DirectUICore {

enum
{
    XMLFILE_ENCODING_UTF8 = 0,
    XMLFILE_ENCODING_UNICODE = 1,
    XMLFILE_ENCODING_ASNI = 2,
};

class CMarkup;
class CMarkupNode;

// 解析XML
class DIRECTUI_API CMarkup
{
    friend class CMarkupNode;
public:
	CMarkup( LPCTSTR pstrXML = NULL ); // 初始化成员变量，调用Load()
    ~CMarkup();
	// 加载xml数据
    bool Load( LPCTSTR pstrXML );
	// 从内存中加载xml数据
    bool LoadFromMem( BYTE* pByte, DWORD dwSize, int encoding = XMLFILE_ENCODING_UTF8 );
	// 从文件中加载xml数据
    bool LoadFromFile( LPCTSTR pstrFilename, int encoding = XMLFILE_ENCODING_UTF8 );
	// 释放xml数据和元素信息数据
    void Release();
	// Markup是否有效
    bool IsValid() const;
	// 设置是否保存空白行
    void SetPreserveWhitespace( bool bPreserve = true );
	// 功能 ： 得到错误信息
	// 参数 ：pstrMessage - [out]错误信息内容；cchMax - 信息长度
    void GetLastErrorMessage( LPTSTR pstrMessage, SIZE_T cchMax ) const;
	// 功能 ： 得到出错位置
	// 参数 ： pstrSource - 错误所在位置内容；cchMax - 内容长度
    void GetLastErrorLocation( LPTSTR pstrSource, SIZE_T cchMax ) const;
	// 得到根节点
    CMarkupNode GetRoot();

private: 
    typedef struct tagXMLELEMENT	//元素结构
    {
        ULONG iStart;				//在m_pstrXML中起始位置
        ULONG iChild;				//子标签在m_pstrXML中的位置
        ULONG iNext;				//同级下一个标签在m_pstrXML中的位置
        ULONG iParent;				//上一级标签在m_pstrXML中的位置
        ULONG iData;				//元素数据在m_pstrXML中的位置
    } XMLELEMENT;

    LPTSTR m_pstrXML;				//xml数据
    XMLELEMENT* m_pElements;		//元素列表
    ULONG m_nElements;				//元素数量
    ULONG m_nReservedElements;		//存储元素空间
    TCHAR m_szErrorMsg[100];		//错误消息
    TCHAR m_szErrorXML[50];			//错误内容
    bool m_bPreserveWhitespace;		//是否过滤空白

private:
	// 解析xml数据
    bool _Parse();
    bool _Parse( LPTSTR& pstrText, ULONG iParent );
	// 申请保存元素空间
    XMLELEMENT* _ReserveElement();
	// 跳过空白
    inline void _SkipWhitespace( LPTSTR& pstr ) const;
    inline void _SkipWhitespace( LPCTSTR& pstr ) const;
	// 跳过标识符
    inline void _SkipIdentifier( LPTSTR& pstr ) const;
    inline void _SkipIdentifier( LPCTSTR& pstr ) const;
	/* 功能 ： 解析数据
	   参数 ： pstrText - 被解析的数据字符串
		       pstrData - 解析后的数据字符串
		       cEnd		- 终止字符	*/
    bool _ParseData( LPTSTR& pstrText, LPTSTR& pstrData, char cEnd );
	// 解析转义字符
    void _ParseMetaChar( LPTSTR& pstrText, LPTSTR& pstrDest );
	// 解析属性
    bool _ParseAttributes( LPTSTR& pstrText );
	// 记录错误信息返回错误
    bool _Failed( LPCTSTR pstrError, LPCTSTR pstrLocation = NULL );
};


class DIRECTUI_API CMarkupNode
{
    friend class CMarkup;
private:
    CMarkupNode();								// 构造一个空节点
	/*功能 ： 构造函数
	  参数 ： pOwner - CMarkup指针
			  iPos	 - 在xml数据中的位置*/
    CMarkupNode( CMarkup* pOwner, int iPos );

public:
	// 节点对象是否有效
    bool IsValid() const;
	// 得到父节点
    CMarkupNode GetParent();
	// 得到兄弟节点
    CMarkupNode GetSibling();
	// 得到子节点
    CMarkupNode GetChild();
	// 按名字得到子节点
    CMarkupNode GetChild( LPCTSTR pstrName );
	// 是否有兄弟节点
    bool HasSiblings() const;
	// 是否有子节点
    bool HasChildren() const;
	// 得到节点对应的标签名
    LPCTSTR GetName() const;
	// 得到节点对应的标签数据值
    LPCTSTR GetValue() const;
	// 是否有属性
    bool HasAttributes();
	// 是否有名为pstrName的属性
    bool HasAttribute( LPCTSTR pstrName );
	// 得到节点属性的数量
    int GetAttributeCount();
	// 按序号得到属性名称
    LPCTSTR GetAttributeName( int iIndex );
    LPCTSTR GetAttributeValue( int iIndex );
    LPCTSTR GetAttributeValue( LPCTSTR pstrName );
	/*功能 ： 得到属性
	  参数 ： iIndex	- 属性序号
			  pstrValue - [out] 属性值字符串
			  cchMax	- 属性值字符串长度*/
    bool GetAttributeValue( int iIndex, LPTSTR pstrValue, SIZE_T cchMax );
	/*功能 ： 得到属性
	  参数 ： pstrName	- 属性名
			  pstrValue	- [out] 属性值字符串
			  cchMax	- 属性值字符串长度*/
    bool GetAttributeValue( LPCTSTR pstrName, LPTSTR pstrValue, SIZE_T cchMax );

private:
	// 解析xml属性建立 属性名和值的表映射到xml数据的位置
    void _MapAttributes();
	// 属性最大数量限制
    enum { MAX_XML_ATTRIBUTES = 64 };
	// 属性结构
    typedef struct
    {
        ULONG iName; 
        ULONG iValue;
    } XMLATTRIBUTE;

    int m_iPos;										// 节点在xml数据中的位置
    int m_nAttributes;								// 属性数量
    XMLATTRIBUTE m_aAttributes[MAX_XML_ATTRIBUTES];	// 属性-值 映射xml位置 列表
    CMarkup* m_pOwner;								// CMarkup指针
};

} // namespace DirectUICore

#endif // __UIMARKUP_H__
