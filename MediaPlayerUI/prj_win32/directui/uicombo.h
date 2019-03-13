// Combo控件
#ifndef __DUI_COMBO_H__
#define __DUI_COMBO_H__

namespace DirectUICore 
{

class CComboWnd;
class CEditUI;



class DIRECTUI_API CComboUI : public CContainerUI, public IListOwnerUI
{
    friend class CComboWnd;
public:
    CComboUI();
	virtual ~CComboUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);

    void DoInit();	// 初始化
	// 返回tab切换停留属性，如果选中项序号为-1，设置第0项为选中项
    UINT GetControlFlags() const;

    CStdString GetText() const;							// 得到文本内容
	void SetText( LPCTSTR pstrText );                   // 设置编辑框内容---pbl
	UINT_PTR GetTag() const;							// 在调用前请确定前面有设置
	int GetIndexByItemTag( UINT_PTR dwTag ) const;		// 在调用前请确定前面有设置
    void SetEnabled(bool bEnable = true);				// 设置是否可用
	void SetVisible(bool bVisible);						// 设置是否可见

    CStdString GetDropBoxAttributeList();				// 获取下拉框属性列表字符串
    void SetDropBoxAttributeList(LPCTSTR pstrList);		// 设置下拉框属性列表字符串
    SIZE GetDropBoxSize() const;						// 得到下拉框大小
    void SetDropBoxSize(SIZE szDropBox);				// 设置下拉框大小

    int GetCurSel() const;								// 获取当前选中项
    bool SelectItem(int iIndex, bool bTakeFocus = false);// 设置当前选中项

    bool SetItemIndex(CControlUI* pControl, int iIndex);// 按项的控件指针获取项序号
    bool Add(CControlUI* pControl);						// 加入一项
    bool AddAt(CControlUI* pControl, int iIndex);		// 加入一项到列表指定位置
    bool Remove(CControlUI* pControl);					// 按项控件的指针移除一项
    bool RemoveAt(int iIndex);							// 移除指定序号的一项
    void RemoveAll();									// 移除所有项

	// 设置控件活跃，如果处于非活跃状态，且下拉窗口未创建，则创建下拉窗口
    bool Activate();

	// 获取/设置 文本样式
	void SetTextStyle( UINT uStyle );
	UINT GetTextStyle() const;

	void LimitText( int nMaxChar = 255 );

    RECT GetTextPadding() const;						// 获取文本与控件边缘的间距
    void SetTextPadding(RECT rc);						// 设置文本与控件边缘的间距
    LPCTSTR GetNormalImage() const;						// 获取正常状态图
    void SetNormalImage(LPCTSTR pStrImage);				// 设置正常状态图
    LPCTSTR GetHotImage() const;						// 获取活跃状态图
    void SetHotImage(LPCTSTR pStrImage);				// 设置活跃状态图
    LPCTSTR GetPushedImage() const;						// 获取按下状态图
    void SetPushedImage(LPCTSTR pStrImage);				// 设置按下状态图
    LPCTSTR GetFocusedImage() const;					// 获取焦点状态图
    void SetFocusedImage(LPCTSTR pStrImage);			// 设置焦点状态图
    LPCTSTR GetDisabledImage() const;					// 获取非可用状态图
    void SetDisabledImage(LPCTSTR pStrImage);			// 设置非可用状态图

    TListInfoUI* GetListInfo();							// 获取列表信息
    void SetItemFont(int index);						// 设置项字体
    void SetItemTextStyle(UINT uStyle);					// 设置项字体大小
	RECT GetItemTextPadding() const;					// 得到项文本间距
    void SetItemTextPadding(RECT rc);					// 设置项文本间距
	DWORD GetItemTextColor() const;						// 获取项文本颜色
    void SetItemTextColor(DWORD dwTextColor);			// 设置项文本颜色
	DWORD GetItemBkColor() const;						// 获取项背景色
    void SetItemBkColor(DWORD dwBkColor);				// 设置项背景色
	LPCTSTR GetItemBkImage() const;						// 获取项背景图
    void SetItemBkImage(LPCTSTR pStrImage);				// 设置项背景图
    bool IsAlternateBk() const;
    void SetAlternateBk(bool bAlternateBk);
	DWORD GetSelectedItemTextColor() const;				// 获取选中状态项文本颜色
    void SetSelectedItemTextColor(DWORD dwTextColor);	// 设置选中状态项文本颜色
	DWORD GetSelectedItemBkColor() const;				// 得到选中项背景色
    void SetSelectedItemBkColor(DWORD dwBkColor);		// 设置选中项背景色
	LPCTSTR GetSelectedItemImage() const;				// 获取选中项背景图
    void SetSelectedItemImage(LPCTSTR pStrImage);		// 设置选中项背景图
	DWORD GetHotItemTextColor() const;					// 获取项活跃状态文本色
    void SetHotItemTextColor(DWORD dwTextColor);		// 设置项活跃状态文本色
	DWORD GetHotItemBkColor() const;					// 获取项活跃状态背景色
    void SetHotItemBkColor(DWORD dwBkColor);			// 设置项活跃状态背景色
	LPCTSTR GetHotItemImage() const;					// 获取项活跃状态图
    void SetHotItemImage(LPCTSTR pStrImage);			// 设置项活跃状态图
	DWORD GetDisabledItemTextColor() const;				// 得到项非可用状态文本色
    void SetDisabledItemTextColor(DWORD dwTextColor);	// 设置项非可用状态文本色
	DWORD GetDisabledItemBkColor() const;				// 获取项非可用状态背景色
    void SetDisabledItemBkColor(DWORD dwBkColor);		// 设置项非可用状态背景色
	LPCTSTR GetDisabledItemImage() const;				// 获取项非可用状态图
    void SetDisabledItemImage(LPCTSTR pStrImage);		// 设置项非可用状态图
	DWORD GetItemLineColor() const;						// 获取项边框色
    void SetItemLineColor(DWORD dwLineColor);			// 设置项边框色
    bool IsItemShowHtml();								// 项是否使用内嵌html标识语言
    void SetItemShowHtml(bool bShowHtml = true);		// 置项是否使用内嵌html标识语言
	void SetReadOnly(bool bReadOnly);			// 设置只读模式
	bool IsReadOnly() const;					// 获取只读模式

	void SetDropDown(bool bDropDown);

    SIZE EstimateSize(SIZE szAvailable);				// 计算控件大小
    void SetPos(RECT rc);								// 设置控件位置
    void DoEvent(TEventUI& event);						// 事件处理
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
    
    void DoPaint(HDC hDC, const RECT& rcPaint);
    void PaintText(HDC hDC);
    void PaintStatusImage(HDC hDC);

	int FindString(int nStartAfter, LPCTSTR lpszString);
	bool IsMultiSelectItem()const{return false;}
	void EnableScrollWheel( bool bEnable );
	bool IsEnableScrollWheel() const;

	//设置下拉框样式
	void SetWndLayoutInset( RECT rcInset );				// 设置缩进
	RECT GetWndLayoutInset() const;
	void SetWndLayoutBkColor(DWORD dwBackColor);			// 设置背景色
	DWORD GetWndLayoutBkColor() const;
	void SetWndLayoutBorderColor(DWORD dwBorderColor);	// 设置边框色
	DWORD GetWndLayoutBorderColor() const;
	void SetWndLayoutBorderSize(int nSize);		// 设置边框粗细
	int GetWndLayoutBorderSize() const;

protected:
    CComboWnd* m_pWindow;			// 下拉框窗口
	CEditUI* m_pEdit;

    bool m_bReadOnly;				// 只读方式
    int m_iCurSel;					// 当前选中项
	UINT m_uTextStyle;				// 样式, 默认居中
    RECT m_rcTextPadding;			// 文本与控件边缘间距
    CStdString m_sDropBoxAttributes;// 下拉框属性
    SIZE m_szDropBox;				// 下拉框窗体大小
    UINT m_uButtonState;			// 控件状态
	bool m_bDropDown;				// 是否是带Edit的DropDown
	bool m_bEnableScrollWheel;		// 是否启用combo滚轮

	int m_nDropIconWidth;           // DropDown点击图标的宽度

    CStdString m_sNormalImage;		// 正常状态图
    CStdString m_sHotImage;			// 活跃状态图
    CStdString m_sPushedImage;		// 按下状态图
    CStdString m_sFocusedImage;		// 获得焦点状态图
    CStdString m_sDisabledImage;	// 非可用状态图

	RECT m_rcWndLayoutInset;						// 设置下来框内边距
	int m_nWndLayoutBorderSize;                  //设置下拉边框粗细
	DWORD m_dwWndLayoutBackColor;        //设置下来框背景
	DWORD m_dwWndLayoutBorderColor;      //设置下来框边框颜色

    TListInfoUI m_ListInfo;			// 下拉框项的列表
};

class DIRECTUI_API CComboWnd : public CWindowWnd
{
public:
	CComboWnd():m_pOwner(nullptr),m_pLayout(nullptr),m_iOldSel(-1),m_iCurHover(-1),m_bUnSelect(false),m_bDisappear(false){}
	// 初始化Combo窗口，计算窗口创建位置，创建窗口
    void Init(CComboUI* pOwner);
    LPCTSTR GetWindowClassName() const;
	// 窗口被销毁时，最后消息处理函数
    void OnFinalMessage(HWND hWnd);

	/************************************************************************/
	/*	消息处理
		WM_CREATE:创建一个纵向排列容器控件，把项加入容器中
		WM_CLOSE:CComboUI::SetManager() CComboUI::SetPos9) CComboUI::SetFocus()
		WM_LBUTTONUP:查找当鼠标位置，如果当前位置有控件并且不是滚动条控件则向自身发送失去焦点消息
		WM_KEYDOWN:空格键 恢复原来选项 回车键向自身发送失去焦点消息其他键交由CComboUI::DoEvent()处理
		WM_MOUSEWHEEL:由CComboUI::DoEvent
		WM_KILLFOCUS:向自身发送WM_CLOSE									    */
	/************************************************************************/
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	// 计算位置，Scroll 
    void EnsureVisible(int iIndex);
	// 设置纵向滚动条位置
    void Scroll(int dx, int dy);
	// 为了响应删除按钮
	void SetManager( CPaintManagerUI* pManager ){m_pManager = pManager;}
	virtual bool Notify( TNotifyUI& msg );

#if(_WIN32_WINNT >= 0x0501)
	virtual UINT GetClassStyle() const;
#endif

public:
    CPaintManagerUI m_pm;			// 绘制管理者
	CPaintManagerUI* m_pManager;    // 登录窗口manager，通过它给登录窗口发送帐号删除按钮点击通知消息
    CComboUI* m_pOwner;				// ComboUI控件
    CVerticalLayoutUI* m_pLayout;	// 纵向容器
    int m_iOldSel;					// 上一次选中项
	int m_iCurHover;
	bool m_bUnSelect;               // 标志位
	bool m_bSelectOld;              // 标志位
	bool m_bDisappear;              // 是否需要下拉框消失
         
};

class DIRECTUI_API CComboBoxUI : public CComboUI
{
public:
	CComboBoxUI();
	~CComboBoxUI();
	LPCTSTR GetClass() const;

	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	// 获取/设置 可用状态文字颜色
	void SetTextColor( DWORD dwTextColor, bool bRgb = true );
	DWORD GetTextColor() const;
	void SetFrontImage( LPCTSTR pstrText );            // 设置编辑框背景图---pbl

	void PaintText(HDC hDC);
	void PaintStatusImage(HDC hDC);

protected:
	DWORD m_dwTextColor;			// 可用时文字颜色
	CStdString m_sArrowImage;
	int        m_nArrowWidth;
	CStdString m_sFrontImage;
};

} // namespace DirectUICore

#endif // __UICOMBO_H__
