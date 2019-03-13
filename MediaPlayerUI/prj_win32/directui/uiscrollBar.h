#ifndef __DUI_SCROLLBAR_H__
#define __DUI_SCROLLBAR_H__

namespace DirectUICore 
{

class DIRECTUI_API CScrollBarUI : public CControlUI
{
public:
    CScrollBarUI();

    LPCTSTR GetClass() const;					// 返回控件名
    LPVOID GetInterface( LPCTSTR pstrName );	// 得到对象指针

    CContainerUI* GetOwner() const;				// 得到滚动条拥有者
    void SetOwner( CContainerUI* pOwner );		// 设置滚动条拥有者

    void SetVisible( bool bVisible = true );	// 设置滚动条是否可见
    void SetEnabled( bool bEnable = true );		// 设置滚动条是否可用
    void SetFocus();							// 设置焦点

	// 获取/设置 滚动条横竖方向
    bool IsHorizontal();
    void SetHorizontal( bool bHorizontal = true );

	// 得到/设置 滚动条范围
    int GetScrollRange() const;
    void SetScrollRange( int nRange );

	// 得到/设置 滚动块位置
    int GetScrollPos() const;
    void SetScrollPos( int nPos );

	// 得到/设置 步长大小
    int GetLineSize() const;
    void SetLineSize( int nSize );

	// 获取/设置 上或左位置的按钮 显示状态
    bool GetShowButton1();
    void SetShowButton1(bool bShow);

	// 获取/设置 上或左位置的按钮 正常状态图
    LPCTSTR GetButton1NormalImage();
    void SetButton1NormalImage(LPCTSTR pStrImage);

	// 获取/设置 上或左位置的按钮 悬浮状态图
    LPCTSTR GetButton1HotImage();
    void SetButton1HotImage(LPCTSTR pStrImage);

	// 获取/设置 上或左位置的按钮 按下状态图
    LPCTSTR GetButton1PushedImage();
    void SetButton1PushedImage(LPCTSTR pStrImage);

	// 获取/设置 上或左位置的按钮 非可用状态图
    LPCTSTR GetButton1DisabledImage();
    void SetButton1DisabledImage(LPCTSTR pStrImage);

	// 获取/设置 下或右位置的按钮 显示状态
    bool GetShowButton2();
    void SetShowButton2(bool bShow);

	// 获取/设置 下或右位置的按钮 正常状态图
    LPCTSTR GetButton2NormalImage();
    void SetButton2NormalImage(LPCTSTR pStrImage);

	// 获取/设置 下或右位置的按钮 悬浮状态图
    LPCTSTR GetButton2HotImage();
    void SetButton2HotImage(LPCTSTR pStrImage);

	// 获取/设置 下或右位置的按钮 按下状态图
    LPCTSTR GetButton2PushedImage();
    void SetButton2PushedImage(LPCTSTR pStrImage);

	// 获取/设置 下或右位置的按钮 非可用状态图
    LPCTSTR GetButton2DisabledImage();
    void SetButton2DisabledImage(LPCTSTR pStrImage);

	// 获取/设置 滚动块 正常状态图
    LPCTSTR GetThumbNormalImage();
    void SetThumbNormalImage(LPCTSTR pStrImage);

	// 获取/设置 滚动块 悬浮状态图
    LPCTSTR GetThumbHotImage();
    void SetThumbHotImage(LPCTSTR pStrImage);

	// 获取/设置 滚动块 按下状态图
    LPCTSTR GetThumbPushedImage();
    void SetThumbPushedImage(LPCTSTR pStrImage);

	// 获取/设置 滚动块 非可用状态图
    LPCTSTR GetThumbDisabledImage();
    void SetThumbDisabledImage(LPCTSTR pStrImage);

	// 获取/设置 滚动轨迹 正常状态图
    LPCTSTR GetRailNormalImage();
    void SetRailNormalImage(LPCTSTR pStrImage);

	// 获取/设置 滚动轨迹 悬浮状态图
    LPCTSTR GetRailHotImage();
    void SetRailHotImage(LPCTSTR pStrImage);

	// 获取/设置 滚动轨迹 按下状态图
    LPCTSTR GetRailPushedImage();
    void SetRailPushedImage(LPCTSTR pStrImage);

	// 获取/设置 滚动轨迹 非可用状态图
    LPCTSTR GetRailDisabledImage();
    void SetRailDisabledImage(LPCTSTR pStrImage);

	// 获取/设置 背景图 正常状态图
    LPCTSTR GetBkNormalImage();
    void SetBkNormalImage(LPCTSTR pStrImage);

	// 获取/设置 背景图 悬浮状态图
    LPCTSTR GetBkHotImage();
    void SetBkHotImage(LPCTSTR pStrImage);

	// 获取/设置 背景图 按下状态图
    LPCTSTR GetBkPushedImage();
    void SetBkPushedImage(LPCTSTR pStrImage);

	// 获取/设置 背景图 非可用状态图
    LPCTSTR GetBkDisabledImage();
    void SetBkDisabledImage(LPCTSTR pStrImage);

    void SetPos(RECT rc);			// 设置滚动条
    void DoEvent(TEventUI& event);	// 事件处理
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

    void DoPaint(HDC hDC, const RECT& rcPaint);	// 绘制

    void PaintBk(HDC hDC);			// 绘制背景
    void PaintButton1(HDC hDC);		// 绘制上或左向的按钮
    void PaintButton2(HDC hDC);		// 绘制下或右位置的按钮
    void PaintThumb(HDC hDC);		// 绘制滚动块
    void PaintRail(HDC hDC);		// 绘制滚动轨迹

protected:

    enum { 
        DEFAULT_SCROLLBAR_SIZE = 16,// 滚动条默认大小
        DEFAULT_TIMERID = 10,		// 默认计时器id
    };

    bool m_bHorizontal;				// 滚动条横纵方向
    int m_nRange;					// 范围
    int m_nScrollPos;				// 滚动块位置
    int m_nLineSize;				// 步长
    CContainerUI* m_pOwner;			// 滚动条拥有者
    POINT ptLastMouse;				// 鼠标位置
    int m_nLastScrollPos;			// 滚动块位置
    int m_nLastScrollOffset;		// 滚动块偏移量 未使用
    int m_nScrollRepeatDelay;		// 未使用

    CStdString m_sBkNormalImage;
    CStdString m_sBkHotImage;
    CStdString m_sBkPushedImage;
    CStdString m_sBkDisabledImage;

    bool m_bShowButton1;
    RECT m_rcButton1;
    UINT m_uButton1State;
    CStdString m_sButton1NormalImage;
    CStdString m_sButton1HotImage;
    CStdString m_sButton1PushedImage;
    CStdString m_sButton1DisabledImage;

    bool m_bShowButton2;
    RECT m_rcButton2;
    UINT m_uButton2State;
    CStdString m_sButton2NormalImage;
    CStdString m_sButton2HotImage;
    CStdString m_sButton2PushedImage;
    CStdString m_sButton2DisabledImage;

    RECT m_rcThumb;
    UINT m_uThumbState;
    CStdString m_sThumbNormalImage;
    CStdString m_sThumbHotImage;
    CStdString m_sThumbPushedImage;
    CStdString m_sThumbDisabledImage;

    CStdString m_sRailNormalImage;
    CStdString m_sRailHotImage;
    CStdString m_sRailPushedImage;
    CStdString m_sRailDisabledImage;

    CStdString m_sImageModify;
};

}

#endif // __UISCROLLBAR_H__