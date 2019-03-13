#ifndef __DUI_BUTTON_H__
#define __DUI_BUTTON_H__

namespace DirectUICore 
{
class DIRECTUI_API CButtonUI : public CLabelUI
{
public:
    CButtonUI();								// 构造函数, 文本样式为单行居中

    LPCTSTR GetClass() const;					// 返回控件名
    LPVOID GetInterface( LPCTSTR pstrName );	// 得到对象指针
    UINT GetControlFlags() const;				// 得到控件的类型标志

	// 设置控件位置并重绘
	virtual void SetPos( RECT rc );
	// 激活按钮控件，判断是否活跃，如活跃发送通知 
    bool Activate( TEventUI& event );	
	// 设置按钮控件是否可用，调用基类设置, 如不可用则清空按钮状态
    void SetEnabled( bool bEnable = true );
	// 事件处理，非鼠标事件交给基类CLabelUI处理, 鼠标事件由此函数处理
    void DoEvent( TEventUI& event );

	// 获取/设置 正常状态下按钮背景图片
    LPCTSTR GetNormalImage();
    void SetNormalImage( LPCTSTR pStrImage );

	// 设置 鼠标悬时文本的字体
	void SetHotTextFont( int iFont );

	// 设置 按钮按下时文本字体
	void SetPushedTextFont( int iFont );

	// 设置 按钮获得焦点时文本字体
	void SetFocusedTextFont( int iFont );

	// 设置 按钮不可用时文本字体
	void SetDisabledTextFont( int iFont );

	// 设置/获取 鼠标悬时文本的颜色
    void SetHotTextColor( DWORD dwColor );
	DWORD GetHotTextColor() const;

	// 设置/获取 按钮按下时文本颜色
    void SetPushedTextColor( DWORD dwColor );
	DWORD GetPushedTextColor() const;

	// 设置/获取 按钮获得焦点时文本颜色
	void SetFocusedTextColor( DWORD dwColor );
	DWORD GetFocusedTextColor() const;

	// 预估大小
    SIZE EstimateSize( SIZE szAvailable );
	// 设置属性, 根据解析后的名称对所关心的属性设置状态成员变量的值
    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );
	// 设置按钮tooltip
	void SetToolTip( LPCTSTR pstrText );
	// 设置子按钮tooltip
	void SetChildBtnToolTip( LPCTSTR pstrText );
	// 绘制文本
	void PaintText( HDC hDC );
	// 绘制状态背景图片
    void PaintStatusImage( HDC hDC );

	// 设置子按钮区域
	void SetChildBtnArea( int offset );
	// 设置子按钮区域(自定义区域)
	void SetChildBtnArea( int x, int y, int nWidth, int nHeight );
	void SetChildBtn( bool bChildBtn );  // 设置是否是含子按钮的按钮
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
	bool m_bEnableChildClick; // 是否响应子按钮按下消息
	bool m_bNeedMoveMsg;      // 是否需要在按钮没有按下时发送move消息
	bool m_bAsync;            // 是否异步响应，主要是为了规避弹模态框崩溃

	RECT m_rcChild;
	int m_nStateCount;
	int m_nChildOffset;
	RECT m_rcChildOffset;		// 记录偏移的左，右，宽，高

	int m_iHotTextFont;
	int m_iPushedTextFont;
	int m_iFocusedTextFont;
	int m_iDisabledTextFont;

	DWORD m_dwHotTextColor;
	DWORD m_dwPushedTextColor;
	DWORD m_dwFocusedTextColor;

    CStdString m_sNormalImage;
	CStdString m_sToolTip;				// 控制主按钮的Tip信息
	CStdString m_sChildBtnToolTip;				// 控制子按钮的Tip信息
	bool m_bMultiCenter;      //处理左起多行居中问题
};

}

#endif // __UIBUTTON_H__