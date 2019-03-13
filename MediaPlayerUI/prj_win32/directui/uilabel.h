// �ؼ���ǩ�����ִ�����Ҫ��ʾ�������ֵļ̳д���
#ifndef __DUI_LABEL_H__
#define __DUI_LABEL_H__

namespace DirectUICore 
{

class DIRECTUI_API CLabelUI : public CControlUI
{
public:
    CLabelUI();

	// ���ؿؼ���
    LPCTSTR GetClass() const;
	// �õ�����ָ��
    LPVOID GetInterface( LPCTSTR pstrName );

	// ��ȡ/���� �ı���ʽ
    void SetTextStyle( UINT uStyle );
	UINT GetTextStyle() const;

	// ��ȡ/���� ����״̬������ɫ
    void SetTextColor( DWORD dwTextColor, bool bRgb = true );
	DWORD GetTextColor() const;

	// ��ȡ/���� ������״̬������ɫ
    void SetDisabledTextColor( DWORD dwTextColor );
	DWORD GetDisabledTextColor() const;

	// ��ȡ/���� �ؼ�ʹ�õ�����, ��Ӧ�������б��е����
    void SetFont( int index );
	int GetFont() const;

	// ��ȡ/���� ������߿�֮��������
    RECT GetTextPadding() const;
    void SetTextPadding( RECT rc );

	// ��ȡ/���� �Ƿ�ʹ����Ƕhtml��Ǹ�ʽ
    bool IsShowHtml();
    void SetShowHtml( bool bShowHtml = true );

	// Ԥ���ؼ���С
    SIZE EstimateSize( SIZE szAvailable );
	// �¼�����
    void DoEvent( TEventUI& event );
	// ��������
    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );
	// �����ı�
    void PaintText( HDC hDC );

protected:
    DWORD m_dwTextColor;			// ����ʱ������ɫ
    DWORD m_dwDisabledTextColor;	// ������ʱ������ɫ
    int m_iFont;					// �������
    UINT m_uTextStyle;				// ��ʽ, Ĭ�Ͼ���
    RECT m_rcTextPadding;			// ������߿�֮��������
    bool m_bShowHtml;				// �Ƿ�ʹ����Ƕhmtl��Ǹ�ʽ
};

}

#endif // __UILABEL_H__