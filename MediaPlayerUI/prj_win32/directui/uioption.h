// ѡ��ؼ�(��CheckBox RadioBox��)
#ifndef __DUI_OPTION_H__
#define __DUI_OPTION_H__

namespace DirectUICore 
{

class DIRECTUI_API COptionUI : public CButtonUI
{
public:
    COptionUI();
    ~COptionUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface( LPCTSTR pstrName );
	// ���û��ƹ�����, ���ؼ�
    void SetManager( CPaintManagerUI* pManager, CControlUI* pParent, bool bInit = true );

    bool Activate( TEventUI& event );
    void SetEnabled( bool bEnable = true );
	void DoEvent( TEventUI& event );

	// ��ȡ/���� ѡ��״̬����ͼƬ
    LPCTSTR GetSelectedImage();
    void SetSelectedImage( LPCTSTR pStrImage );
	
	// ��ȡ/���� ѡ��״̬������ɫ
	void SetSelectedTextColor( DWORD dwTextColor );
	DWORD GetSelectedTextColor();
		
	// ��ȡ/���� ǰ��ͼƬ
	LPCTSTR GetForeImage();
	void SetForeImage( LPCTSTR pStrImage );

	// ��ȡ/���� ѡ��������
    LPCTSTR GetGroup() const;
    void SetGroup( LPCTSTR pStrGroupName = NULL );
	
	// ��ȡ/���� ѡ���Ƿ���ѡ��״̬
    bool IsSelected() const;
    void Selected( bool bSelected );

    SIZE EstimateSize( SIZE szAvailable );
    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );

    void PaintStatusImage( HDC hDC );
	void PaintText( HDC hDC );

protected:
    bool m_bSelected;
    CStdString m_sGroupName;

	DWORD m_dwSelectedTextColor;

    CStdString m_sSelectedImage;
	CStdString m_sForeImage;
	BOOL  m_bDrawDot;
	CStdString m_sDotImage;
};

class DIRECTUI_API CCheckBoxUI : public COptionUI
{
public:
	LPCTSTR GetClass() const;

	void SetCheck(bool bCheck);
	bool GetCheck() const;

	void PaintStatusImage( HDC hDC );

};

}

#endif // __UIOPTION_H__