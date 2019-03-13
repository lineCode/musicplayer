#ifndef __DUI_BUTTON_H__
#define __DUI_BUTTON_H__

namespace DirectUICore 
{
class DIRECTUI_API CButtonUI : public CLabelUI
{
public:
    CButtonUI();								// ���캯��, �ı���ʽΪ���о���

    LPCTSTR GetClass() const;					// ���ؿؼ���
    LPVOID GetInterface( LPCTSTR pstrName );	// �õ�����ָ��
    UINT GetControlFlags() const;				// �õ��ؼ������ͱ�־

	// ���ÿؼ�λ�ò��ػ�
	virtual void SetPos( RECT rc );
	// ���ť�ؼ����ж��Ƿ��Ծ�����Ծ����֪ͨ 
    bool Activate( TEventUI& event );	
	// ���ð�ť�ؼ��Ƿ���ã����û�������, �粻��������հ�ť״̬
    void SetEnabled( bool bEnable = true );
	// �¼�����������¼���������CLabelUI����, ����¼��ɴ˺�������
    void DoEvent( TEventUI& event );

	// ��ȡ/���� ����״̬�°�ť����ͼƬ
    LPCTSTR GetNormalImage();
    void SetNormalImage( LPCTSTR pStrImage );

	// ���� �����ʱ�ı�������
	void SetHotTextFont( int iFont );

	// ���� ��ť����ʱ�ı�����
	void SetPushedTextFont( int iFont );

	// ���� ��ť��ý���ʱ�ı�����
	void SetFocusedTextFont( int iFont );

	// ���� ��ť������ʱ�ı�����
	void SetDisabledTextFont( int iFont );

	// ����/��ȡ �����ʱ�ı�����ɫ
    void SetHotTextColor( DWORD dwColor );
	DWORD GetHotTextColor() const;

	// ����/��ȡ ��ť����ʱ�ı���ɫ
    void SetPushedTextColor( DWORD dwColor );
	DWORD GetPushedTextColor() const;

	// ����/��ȡ ��ť��ý���ʱ�ı���ɫ
	void SetFocusedTextColor( DWORD dwColor );
	DWORD GetFocusedTextColor() const;

	// Ԥ����С
    SIZE EstimateSize( SIZE szAvailable );
	// ��������, ���ݽ���������ƶ������ĵ���������״̬��Ա������ֵ
    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );
	// ���ð�ťtooltip
	void SetToolTip( LPCTSTR pstrText );
	// �����Ӱ�ťtooltip
	void SetChildBtnToolTip( LPCTSTR pstrText );
	// �����ı�
	void PaintText( HDC hDC );
	// ����״̬����ͼƬ
    void PaintStatusImage( HDC hDC );

	// �����Ӱ�ť����
	void SetChildBtnArea( int offset );
	// �����Ӱ�ť����(�Զ�������)
	void SetChildBtnArea( int x, int y, int nWidth, int nHeight );
	void SetChildBtn( bool bChildBtn );  // �����Ƿ��Ǻ��Ӱ�ť�İ�ť
	void EnableChildClick( bool bEnable ){ m_bEnableChildClick = bEnable; }
	void SetNeedMoveMsg( bool bNeedMoveMsg ){ m_bNeedMoveMsg = bNeedMoveMsg; }
	void SetAsync( bool bAsync ){ m_bAsync = bAsync; }

	bool IsMultiCenter();
	void SetMultiCenter( bool bSingLine = true );

protected:
    UINT m_uButtonState;

	bool m_bDownChild;
	bool m_bHoveringChild;
	bool m_bDrawDot;
	bool m_bChildBtn;
	bool m_bEnableChildClick; // �Ƿ���Ӧ�Ӱ�ť������Ϣ
	bool m_bNeedMoveMsg;      // �Ƿ���Ҫ�ڰ�ťû�а���ʱ����move��Ϣ
	bool m_bAsync;            // �Ƿ��첽��Ӧ����Ҫ��Ϊ�˹�ܵ�ģ̬�����

	RECT m_rcChild;
	int m_nStateCount;
	int m_nChildOffset;
	RECT m_rcChildOffset;		// ��¼ƫ�Ƶ����ң�����

	int m_iHotTextFont;
	int m_iPushedTextFont;
	int m_iFocusedTextFont;
	int m_iDisabledTextFont;

	DWORD m_dwHotTextColor;
	DWORD m_dwPushedTextColor;
	DWORD m_dwFocusedTextColor;

    CStdString m_sNormalImage;
	CStdString m_sToolTip;				// ��������ť��Tip��Ϣ
	CStdString m_sChildBtnToolTip;				// �����Ӱ�ť��Tip��Ϣ
	bool m_bMultiCenter;      //����������о�������
};

}

#endif // __UIBUTTON_H__