#ifndef __DUI_TEXT_H__
#define __DUI_TEXT_H__

namespace DirectUICore 
{

class DIRECTUI_API CTextUI : public CLabelUI
{
public:
    CTextUI();
    ~CTextUI();
		
    LPCTSTR GetClass() const;				// ���ؿؼ���
    UINT GetControlFlags() const;			// �õ��ؼ������ͱ�־
    LPVOID GetInterface(LPCTSTR pstrName);	// �õ�����ָ��

    CStdString* GetLinkContent(int iIndex);	// �õ���ǰ�ؼ���ָ����ŵĳ��ı�������

    void DoEvent(TEventUI& event);
    SIZE EstimateSize(SIZE szAvailable);

	SIZE EstimateTextSize(); // ���ݵ�ǰ�趨��text�ؼ��Ŀ�ȼ������ֵ�����߶�

    void PaintText(HDC hDC);
	// ��ȡ/���� �Ƿ�ʹ����Ƕhtml��Ǹ�ʽ
	bool IsMultiCenter();
	void SetMultiCenter( bool bSingLine = true );

	// ��������
	void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );
	// ���ÿؼ���ʾ����
	void SetText( LPCTSTR pstrText );

protected:
    enum { MAX_LINK = 8 };			// ���ı���������
    int m_nLinks;					// ���ı�����
    RECT m_rcLinks[MAX_LINK];		// ���ı���������
    CStdString m_sLinks[MAX_LINK];	// ���ı���������
    int m_nHoverLink;				// ��긡���ĳ��ı��������
	bool m_bMultiCenter;      //����������о�������
};

}

#endif // __UITEXT_H__