#ifndef __DUI_TEXT_H__
#define __DUI_TEXT_H__

namespace DirectUICore 
{

class DIRECTUI_API CTextUI : public CLabelUI
{
public:
    CTextUI();
    ~CTextUI();
		
    LPCTSTR GetClass() const;				// 返回控件名
    UINT GetControlFlags() const;			// 得到控件的类型标志
    LPVOID GetInterface(LPCTSTR pstrName);	// 得到对象指针

    CStdString* GetLinkContent(int iIndex);	// 得到当前控件中指定序号的超文本的内容

    void DoEvent(TEventUI& event);
    SIZE EstimateSize(SIZE szAvailable);

	SIZE EstimateTextSize(); // 根据当前设定的text控件的宽度计算文字的所需高度

    void PaintText(HDC hDC);
	// 获取/设置 是否使用内嵌html标记格式
	bool IsMultiCenter();
	void SetMultiCenter( bool bSingLine = true );

	// 设置属性
	void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );
	// 设置控件显示内容
	void SetText( LPCTSTR pstrText );

protected:
    enum { MAX_LINK = 8 };			// 超文本数量限制
    int m_nLinks;					// 超文本数量
    RECT m_rcLinks[MAX_LINK];		// 超文本区域数组
    CStdString m_sLinks[MAX_LINK];	// 超文本内容数组
    int m_nHoverLink;				// 鼠标浮动的超文本链接序号
	bool m_bMultiCenter;      //处理左起多行居中问题
};

}

#endif // __UITEXT_H__