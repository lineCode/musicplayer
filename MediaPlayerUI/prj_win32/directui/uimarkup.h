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

// ����XML
class DIRECTUI_API CMarkup
{
    friend class CMarkupNode;
public:
	CMarkup( LPCTSTR pstrXML = NULL ); // ��ʼ����Ա����������Load()
    ~CMarkup();
	// ����xml����
    bool Load( LPCTSTR pstrXML );
	// ���ڴ��м���xml����
    bool LoadFromMem( BYTE* pByte, DWORD dwSize, int encoding = XMLFILE_ENCODING_UTF8 );
	// ���ļ��м���xml����
    bool LoadFromFile( LPCTSTR pstrFilename, int encoding = XMLFILE_ENCODING_UTF8 );
	// �ͷ�xml���ݺ�Ԫ����Ϣ����
    void Release();
	// Markup�Ƿ���Ч
    bool IsValid() const;
	// �����Ƿ񱣴�հ���
    void SetPreserveWhitespace( bool bPreserve = true );
	// ���� �� �õ�������Ϣ
	// ���� ��pstrMessage - [out]������Ϣ���ݣ�cchMax - ��Ϣ����
    void GetLastErrorMessage( LPTSTR pstrMessage, SIZE_T cchMax ) const;
	// ���� �� �õ�����λ��
	// ���� �� pstrSource - ��������λ�����ݣ�cchMax - ���ݳ���
    void GetLastErrorLocation( LPTSTR pstrSource, SIZE_T cchMax ) const;
	// �õ����ڵ�
    CMarkupNode GetRoot();

private: 
    typedef struct tagXMLELEMENT	//Ԫ�ؽṹ
    {
        ULONG iStart;				//��m_pstrXML����ʼλ��
        ULONG iChild;				//�ӱ�ǩ��m_pstrXML�е�λ��
        ULONG iNext;				//ͬ����һ����ǩ��m_pstrXML�е�λ��
        ULONG iParent;				//��һ����ǩ��m_pstrXML�е�λ��
        ULONG iData;				//Ԫ��������m_pstrXML�е�λ��
    } XMLELEMENT;

    LPTSTR m_pstrXML;				//xml����
    XMLELEMENT* m_pElements;		//Ԫ���б�
    ULONG m_nElements;				//Ԫ������
    ULONG m_nReservedElements;		//�洢Ԫ�ؿռ�
    TCHAR m_szErrorMsg[100];		//������Ϣ
    TCHAR m_szErrorXML[50];			//��������
    bool m_bPreserveWhitespace;		//�Ƿ���˿հ�

private:
	// ����xml����
    bool _Parse();
    bool _Parse( LPTSTR& pstrText, ULONG iParent );
	// ���뱣��Ԫ�ؿռ�
    XMLELEMENT* _ReserveElement();
	// �����հ�
    inline void _SkipWhitespace( LPTSTR& pstr ) const;
    inline void _SkipWhitespace( LPCTSTR& pstr ) const;
	// ������ʶ��
    inline void _SkipIdentifier( LPTSTR& pstr ) const;
    inline void _SkipIdentifier( LPCTSTR& pstr ) const;
	/* ���� �� ��������
	   ���� �� pstrText - �������������ַ���
		       pstrData - ������������ַ���
		       cEnd		- ��ֹ�ַ�	*/
    bool _ParseData( LPTSTR& pstrText, LPTSTR& pstrData, char cEnd );
	// ����ת���ַ�
    void _ParseMetaChar( LPTSTR& pstrText, LPTSTR& pstrDest );
	// ��������
    bool _ParseAttributes( LPTSTR& pstrText );
	// ��¼������Ϣ���ش���
    bool _Failed( LPCTSTR pstrError, LPCTSTR pstrLocation = NULL );
};


class DIRECTUI_API CMarkupNode
{
    friend class CMarkup;
private:
    CMarkupNode();								// ����һ���սڵ�
	/*���� �� ���캯��
	  ���� �� pOwner - CMarkupָ��
			  iPos	 - ��xml�����е�λ��*/
    CMarkupNode( CMarkup* pOwner, int iPos );

public:
	// �ڵ�����Ƿ���Ч
    bool IsValid() const;
	// �õ����ڵ�
    CMarkupNode GetParent();
	// �õ��ֵܽڵ�
    CMarkupNode GetSibling();
	// �õ��ӽڵ�
    CMarkupNode GetChild();
	// �����ֵõ��ӽڵ�
    CMarkupNode GetChild( LPCTSTR pstrName );
	// �Ƿ����ֵܽڵ�
    bool HasSiblings() const;
	// �Ƿ����ӽڵ�
    bool HasChildren() const;
	// �õ��ڵ��Ӧ�ı�ǩ��
    LPCTSTR GetName() const;
	// �õ��ڵ��Ӧ�ı�ǩ����ֵ
    LPCTSTR GetValue() const;
	// �Ƿ�������
    bool HasAttributes();
	// �Ƿ�����ΪpstrName������
    bool HasAttribute( LPCTSTR pstrName );
	// �õ��ڵ����Ե�����
    int GetAttributeCount();
	// ����ŵõ���������
    LPCTSTR GetAttributeName( int iIndex );
    LPCTSTR GetAttributeValue( int iIndex );
    LPCTSTR GetAttributeValue( LPCTSTR pstrName );
	/*���� �� �õ�����
	  ���� �� iIndex	- �������
			  pstrValue - [out] ����ֵ�ַ���
			  cchMax	- ����ֵ�ַ�������*/
    bool GetAttributeValue( int iIndex, LPTSTR pstrValue, SIZE_T cchMax );
	/*���� �� �õ�����
	  ���� �� pstrName	- ������
			  pstrValue	- [out] ����ֵ�ַ���
			  cchMax	- ����ֵ�ַ�������*/
    bool GetAttributeValue( LPCTSTR pstrName, LPTSTR pstrValue, SIZE_T cchMax );

private:
	// ����xml���Խ��� ��������ֵ�ı�ӳ�䵽xml���ݵ�λ��
    void _MapAttributes();
	// ���������������
    enum { MAX_XML_ATTRIBUTES = 64 };
	// ���Խṹ
    typedef struct
    {
        ULONG iName; 
        ULONG iValue;
    } XMLATTRIBUTE;

    int m_iPos;										// �ڵ���xml�����е�λ��
    int m_nAttributes;								// ��������
    XMLATTRIBUTE m_aAttributes[MAX_XML_ATTRIBUTES];	// ����-ֵ ӳ��xmlλ�� �б�
    CMarkup* m_pOwner;								// CMarkupָ��
};

} // namespace DirectUICore

#endif // __UIMARKUP_H__
