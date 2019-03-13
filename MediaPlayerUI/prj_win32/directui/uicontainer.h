#ifndef __DUI_CONTAINER_H__
#define __DUI_CONTAINER_H__

namespace DirectUICore {
/////////////////////////////////////////////////////////////////////////////////////
//	容器虚基类

class IContainerUI
{
public:
	// 得到容器中控件项
    virtual CControlUI* GetItemAt( int iIndex ) const = 0;
	// 按容器中控件项获取序号
    virtual int GetItemIndex( CControlUI* pControl ) const  = 0;
	// 设置控件项为容器中存在的指定序号的控件项
    virtual bool SetItemIndex( CControlUI* pControl, int iIndex )  = 0;
	// 获取容器控件项数
    virtual int GetCount() const = 0;
	// 增加一个控件到容器中
    virtual bool Add( CControlUI* pControl ) = 0;
	// 插入一个控件到容器中
    virtual bool AddAt( CControlUI* pControl, int iIndex )  = 0;
	// 删除容器中控件项
    virtual bool Remove( CControlUI* pControl ) = 0;
	// 删除指定序号的容器控件项
    virtual bool RemoveAt( int iIndex )  = 0;
	// 删除所有容器中的控件
    virtual void RemoveAll() = 0;
};

class IDrawEvent
{
public:
	virtual ~IDrawEvent(void) {}
	virtual void OnDrawContainer( LPCTSTR pstrName, HDC hDC ) {}
};

class ISpecialHorinzonEvent
{
public:
	virtual HWND GetMenuHwnd(){return NULL;}
};
/////////////////////////////////////////////////////////////////////////////////////
//	容器控件
class CScrollBarUI;

class DIRECTUI_API CContainerUI : public CControlUI, public IContainerUI
{
public:
    CContainerUI();
    virtual ~CContainerUI();

public:
    LPCTSTR GetClass() const;
    LPVOID GetInterface( LPCTSTR pstrName );
	// 设置绘画事件回调
	void SetDrawEvent( IDrawEvent* pIDrawEvent ){ m_pIDrawEvent = pIDrawEvent; }

	// 以下重载父类的纯虚函数
    CControlUI* GetItemAt( int iIndex ) const;
	int GetItemIndex( CControlUI* pControl ) const;
	int GetItemIndexByName( LPCTSTR pstrName ) const;
    bool SetItemIndex( CControlUI* pControl, int iIndex );
	bool SetItemIndexByName( LPCTSTR pstrName, int iIndex );
    int GetCount() const;
	// 获取容器控件列表
	CStdPtrArray& GetItemList();
    bool Add( CControlUI* pControl );
    bool AddAt( CControlUI* pControl, int iIndex );
    bool Remove( CControlUI* pControl );
    bool RemoveAt(int iIndex);
    void RemoveAll();

	bool Activate( TEventUI& event );
    void DoEvent( TEventUI& event );
    void SetVisible( bool bVisible = true );
    void SetInternVisible( bool bVisible = true );	// 仅供内部调用，有些UI拥有窗口句柄，需要重写此函数
    void SetMouseEnabled( bool bEnable = true );	// 设置是否处理鼠标事件

	// 获取/设置内边距，相当于设置客户区
    virtual RECT GetInset() const;
    virtual void SetInset( RECT rcInset );

	// 获取/设置 控件项间距
    virtual int GetChildPadding() const;
    virtual void SetChildPadding( int iPadding );

	// 获取/设置容器内控件项是否自动摧毁
    virtual bool IsAutoDestroy() const;
    virtual void SetAutoDestroy( bool bAuto );

	// 获取/设置容器本身是否延迟摧毁
    virtual bool IsDelayedDestroy() const;
    virtual void SetDelayedDestroy( bool bDelayed );

	// ？获取/设置容器中控件是否响应鼠标事件
    virtual bool IsMouseChildEnabled() const;
    virtual void SetMouseChildEnabled( bool bEnable = true );

	// 查找容器中下一个可选项
    virtual int FindSelectable( int iIndex, bool bForward = true ) const;

    void SetPos( RECT rc );							// 设置位置
    void DoPaint( HDC hDC, const RECT& rcPaint );	// 绘制

    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );	// 设置属性

	// 设置界面管理者
    void SetManager( CPaintManagerUI* pManager, CControlUI* pParent, bool bInit = true );
    CControlUI* FindControl( FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags );

	// 该函数是参照上面的FindControl写的，不同的是在找到控件时，调用一下SetPos函数，再者就
	// 是找到控件后不能直接return，应该将所有满足条件的控件都SetPos一下。此函数主要提供给
	// CPaintManagerUI::MessageHandler调用，以解决CPaintManagerUI::MessageHandler在处
	// 理WM_PAINT消息时的死循环问题，具体死循环原因见FindControl_SetPos的调用处说明，by zzx 2014/02/27
	// --该函数会导致少数界面显示有问题，暂不使用！！！--
	void FindControl_SetPos( FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags );

	bool SetSubControlText( LPCTSTR pstrSubControlName,LPCTSTR pstrText );
	bool SetSubControlFixedHeight( LPCTSTR pstrSubControlName,int cy );
	bool SetSubControlFixedWdith( LPCTSTR pstrSubControlName,int cx );
	bool SetSubControlUserData( LPCTSTR pstrSubControlName,LPCTSTR pstrText );
	
	CStdString GetSubControlText( LPCTSTR pstrSubControlName );
	int GetSubControlFixedHeight( LPCTSTR pstrSubControlName );
	int GetSubControlFixedWdith( LPCTSTR pstrSubControlName );
	const CStdString GetSubControlUserData( LPCTSTR pstrSubControlName );
	CControlUI* FindSubControl( LPCTSTR pstrSubControlName );

    virtual SIZE GetScrollPos() const;		// 获取滚动块位置
    virtual SIZE GetScrollRange() const;	// 获取滚动条范围
    virtual void SetScrollPos( SIZE szPos );
    virtual void LineUp();					// 向上一行（一行为默认字体高度）
    virtual void LineDown();				// 向下一行
    virtual void PageUp();					// 向上一页
    virtual void PageDown();				// 向下一页
    virtual void HomeUp();					// 最上
    virtual void EndDown();					// 最下
    virtual void LineLeft();				// 向左一行（8个像素）
    virtual void LineRight();				// 向右一行（8个像素）
    virtual void PageLeft();				// 向左一页
    virtual void PageRight();				// 向右一页
    virtual void HomeLeft();				// 最左
    virtual void EndRight();				// 最右
	// 滚动条可用
    virtual void EnableScrollBar( bool bEnableVertical = true, bool bEnableHorizontal = false );
    // 得到纵向滚动条
	virtual CScrollBarUI* GetVerticalScrollBar() const;
	// 得到横向滚动条
    virtual CScrollBarUI* GetHorizontalScrollBar() const;
	void SetEnabled( bool bEnable );
	void SetInternEnable(bool bEnable );
protected:
	// 设置悬浮位置
    virtual void SetFloatPos( int iIndex );
	// 处理滚动条
    virtual void ProcessScrollBar( RECT rc, int cxRequired, int cyRequired );

protected:
	// 同一层的控件对象或控件对象的子对象，
	// 例如canvas上放置的按钮、combox由edit和list两个子对象组成，其它还有tab等
	
	CStdPtrArray m_items;				// 容器中的空间项
    RECT m_rcInset;						// 设置内边距 客户区
    int m_iChildPadding;				// 控件项间距
    bool m_bAutoDestroy;				// 自动摧毁子控件
    bool m_bDelayedDestroy;				// 延迟摧毁子控件
    bool m_bMouseChildEnabled;			// 鼠标可用
    bool m_bScrollProcess;				// 是否处理滚动，防止SetPos循环调用

	IDrawEvent*   m_pIDrawEvent;
    CScrollBarUI* m_pVerticalScrollBar;		// 是否使用横滚动条
    CScrollBarUI* m_pHorizontalScrollBar;	// 是否使用纵滚动条
};

/////////////////////////////////////////////////////////////////////////////////////
//	纵向布局的容器控件

class DIRECTUI_API CVerticalLayoutUI : public CContainerUI
{
public:
    CVerticalLayoutUI();

    LPCTSTR GetClass() const;					// 得到控件类名
    LPVOID GetInterface( LPCTSTR pstrName );	// 得到控件指针
    UINT GetControlFlags() const;				// 得到控件的类型标志

    void SetSepHeight( int iHeight );			// 设置分割栏高度
    int GetSepHeight() const;					// 获取分割栏高度
    void SetSepImmMode( bool bImmediately );	// 设置刷新模式 立即刷新或延时刷新
    bool IsSepImmMode() const;					// 获取刷新模式
    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );// 设置属性
    void DoEvent( TEventUI& event );			// 处理事件

    void SetPos( RECT rc );
    void DoPostPaint( HDC hDC, const RECT& rcPaint );

    RECT GetThumbRect( bool bUseNew = false ) const;	// 获取欲刷新的区域

protected:
    int m_iSepHeight;		// 分隔栏高度
    UINT m_uButtonState;	// 容器控件状态
    POINT ptLastMouse;		// 鼠标位置
    RECT m_rcNewPos;		// 刷新区域
    bool m_bImmMode;		// 立即刷新模式
};



/////////////////////////////////////////////////////////////////////////////////////
//	横向布局的容器控件

class DIRECTUI_API CHorizontalLayoutUI : public CContainerUI
{
public:
    CHorizontalLayoutUI();

	LPCTSTR GetClass() const;					// 得到控件类名
	LPVOID GetInterface( LPCTSTR pstrName );	// 得到控件指针
	UINT GetControlFlags() const;				// 得到控件的类型标志
    
    void SetSepWidth( int iWidth );		    // 设置分割栏宽度
	int GetSepWidth() const;					// 获取分割栏宽度
	void SetSepImmMode( bool bImmediately );	// 设置刷新模式 立即刷新或延时刷新
	bool IsSepImmMode() const;					// 获取刷新模式
	void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );// 设置属性
	void DoEvent( TEventUI& event );			// 处理事件

	void SetPos( RECT rc );
	void DoPostPaint( HDC hDC, const RECT& rcPaint );

	RECT GetThumbRect( bool bUseNew = false ) const;	// 获取欲刷新的区域

protected:
	int m_iSepWidth;		// 分隔栏宽度
	UINT m_uButtonState;	// 容器控件状态
	POINT ptLastMouse;		// 鼠标位置
	RECT m_rcNewPos;		// 刷新区域
	bool m_bImmMode;		// 立即刷新模式
};

/////////////////////////////////////////////////////////////////////////////////////
//	特殊水平布局

class DIRECTUI_API CSpecialHorizontal : public CHorizontalLayoutUI
{
public:
	CSpecialHorizontal():m_pSpecialHorinzonEvent( NULL ){}
	virtual ~CSpecialHorizontal(){}
	virtual LPCTSTR GetClass() const;
	virtual LPVOID GetInterface( LPCTSTR pstrName );
	void DoEvent( TEventUI& event );
	void SetSpecialHorinzonEvent( ISpecialHorinzonEvent* pSpecialHorinzonEvent );
	enum{ SHOW_TIMERID = 0,
		  HIDE_TIMERID = 1,
	      HIDE_MENU_TIMERID = 2};
private:
	ISpecialHorinzonEvent* m_pSpecialHorinzonEvent;
};

/////////////////////////////////////////////////////////////////////////////////////
//	平铺布局

class DIRECTUI_API CTileLayoutUI : public CContainerUI
{
public:
    CTileLayoutUI();

    LPCTSTR GetClass() const;				// 得到控件类名
    LPVOID GetInterface( LPCTSTR pstrName );// 得到控件的类型标志

    void SetPos( RECT rc );					// 设置容器及其容器内控件项位置

    SIZE GetItemSize() const;				// 获取控件项大小
    void SetItemSize(SIZE szItem);			// 设置控件项大小
    int GetColumns() const;					// 获取布局列数
    void SetColumns( int nCols );			// 设置布局列数

    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );

protected:
    SIZE m_szItem;		// 控件项大小
    int m_nColumns;		// 布局列数
};


/////////////////////////////////////////////////////////////////////////////////////
//	标签页容器

class DIRECTUI_API CTabLayoutUI : public CContainerUI
{
public:
    CTabLayoutUI();

    LPCTSTR GetClass() const;				// 得到控件类名
    LPVOID GetInterface( LPCTSTR pstrName );// 得到控件指针

	// 向容器中添加控件，如果不是选中项则设置为非可见
    bool Add( CControlUI* pControl );
	// 将控件添加到容器控件列表的指定位置，不为选中项为非可见
    bool AddAt( CControlUI* pControl, int iIndex );
	// 移除控件
    bool Remove( CControlUI* pControl );
	// 移除所有控件
    void RemoveAll();
	// 得到当前选中的控件项（可见控件）
    int GetCurSel() const;
	// 设置控件项为选中项（设置为可见控件）
    bool SelectItem( int iIndex );

	// 设置容器及其控件位置
    void SetPos( RECT rc );
	// 设置属性
    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );

protected:
    int m_iCurSel;	// 当前选中控件（可见）
};

} // namespace DirectUICore

#endif // __UICONTAINER_H__
