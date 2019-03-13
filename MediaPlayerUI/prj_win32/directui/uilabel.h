// 控件标签，文字处理，需要显示或处理文字的继承此类
#ifndef __DUI_LABEL_H__
#define __DUI_LABEL_H__

namespace DirectUICore 
{

class DIRECTUI_API CLabelUI : public CControlUI
{
public:
    CLabelUI();

	// 返回控件名
    LPCTSTR GetClass() const;
	// 得到对象指针
    LPVOID GetInterface( LPCTSTR pstrName );

	// 获取/设置 文本样式
    void SetTextStyle( UINT uStyle );
	UINT GetTextStyle() const;

	// 获取/设置 可用状态文字颜色
    void SetTextColor( DWORD dwTextColor, bool bRgb = true );
	DWORD GetTextColor() const;

	// 获取/设置 不可用状态文字颜色
    void SetDisabledTextColor( DWORD dwTextColor );
	DWORD GetDisabledTextColor() const;

	// 获取/设置 控件使用的字体, 对应在字体列表中的序号
    void SetFont( int index );
	int GetFont() const;

	// 获取/设置 文字与边框之间填充距离
    RECT GetTextPadding() const;
    void SetTextPadding( RECT rc );

	// 获取/设置 是否使用内嵌html标记格式
    bool IsShowHtml();
    void SetShowHtml( bool bShowHtml = true );

	// 预估控件大小
    SIZE EstimateSize( SIZE szAvailable );
	// 事件处理
    void DoEvent( TEventUI& event );
	// 设置属性
    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );
	// 绘制文本
    void PaintText( HDC hDC );

protected:
    DWORD m_dwTextColor;			// 可用时文字颜色
    DWORD m_dwDisabledTextColor;	// 不可用时文字颜色
    int m_iFont;					// 字体序号
    UINT m_uTextStyle;				// 样式, 默认居中
    RECT m_rcTextPadding;			// 文字与边框之间填充距离
    bool m_bShowHtml;				// 是否使用内嵌hmtl标记格式
};

}

#endif // __UILABEL_H__