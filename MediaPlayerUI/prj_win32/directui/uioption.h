// 选项控件(如CheckBox RadioBox等)
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
	// 设置绘制管理者, 父控件
    void SetManager( CPaintManagerUI* pManager, CControlUI* pParent, bool bInit = true );

    bool Activate( TEventUI& event );
    void SetEnabled( bool bEnable = true );
	void DoEvent( TEventUI& event );

	// 获取/设置 选中状态背景图片
    LPCTSTR GetSelectedImage();
    void SetSelectedImage( LPCTSTR pStrImage );
	
	// 获取/设置 选中状态字体颜色
	void SetSelectedTextColor( DWORD dwTextColor );
	DWORD GetSelectedTextColor();
		
	// 获取/设置 前景图片
	LPCTSTR GetForeImage();
	void SetForeImage( LPCTSTR pStrImage );

	// 获取/设置 选项所属组
    LPCTSTR GetGroup() const;
    void SetGroup( LPCTSTR pStrGroupName = NULL );
	
	// 获取/设置 选项是否处于选中状态
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