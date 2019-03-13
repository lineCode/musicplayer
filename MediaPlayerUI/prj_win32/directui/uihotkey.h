#ifndef UI_HOTKEY_H
#define UI_HOTKEY_H
#include <vector>

namespace DirectUICore 
{

class CHotKeyWnd;

class DIRECTUI_API CHotKeyUI : public CLabelUI
{
    friend class CHotKeyWnd;
public:
    CHotKeyUI();
	~CHotKeyUI();

    LPCTSTR GetClass() const;					// 返回控件名
    LPVOID GetInterface(LPCTSTR pstrName);		// 得到对象指针块
    UINT GetControlFlags() const;				// 得到控件的类型标志

	void DoInit();

    void SetEnabled(bool bEnable = true);		// 设置编辑框控件是否可用
    void SetText(LPCTSTR pstrText);				// 设置文本

	void SetHotKey( WORD wVirtualKey, WORD wSysKey );
	void GetHotKey( WORD& wVirtualKey, WORD& wSysKey );

	// 获取/设置 正常状态图
    LPCTSTR GetNormalImage();
    void SetNormalImage(LPCTSTR pStrImage);

	// 获取/设置 悬浮状态图
    LPCTSTR GetHotImage();
    void SetHotImage(LPCTSTR pStrImage);

	// 获取/设置 选中状态图
    LPCTSTR GetFocusedImage();
    void SetFocusedImage(LPCTSTR pStrImage);

	// 获取/设置 不可用状态图
	LPCTSTR GetDisabledImage();
	void SetDisabledImage(LPCTSTR pStrImage);

    void SetPos(RECT rc);						// 得到编辑框位置
    void SetVisible(bool bVisible = true);		// 设置可见状态
    void SetInternVisible(bool bVisible = true);// 仅供内部调用，有些UI拥有窗口句柄，需要重写此函数
    SIZE EstimateSize(SIZE szAvailable);		// 预估控件大小
    void DoEvent(TEventUI& event);				// 处理事件
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

    void PaintStatusImage(HDC hDC);
    void PaintText(HDC hDC);

protected:
    CHotKeyWnd* m_pWindow;		// 原生编辑框窗口

    UINT m_uButtonState;		// 编辑框状态

    CStdString m_sNormalImage;	// 正常状态图
    CStdString m_sHotImage;		// 悬浮状态图
    CStdString m_sFocusedImage;	// 选中状态图
	CStdString m_sDisabledImage;// 不可用状态图
};

}

#endif // __UIEDIT_H__