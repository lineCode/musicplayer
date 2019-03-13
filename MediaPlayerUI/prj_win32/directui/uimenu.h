#ifndef __DUI_MENU_H__
#define __DUI_MENU_H__
#include "observer_impl_base.h"
#include "uishadow.h"

namespace DirectUICore 
{

/////////////////////////////////////////////////////////////////////////////////////
//
struct ContextMenuParam
{
	// 1: remove all
	// 2: remove the sub menu
	WPARAM wParam;
	HWND hWnd;
};

enum MenuAlignment
{
	eMenuAlignment_Left = 1 << 1,
	eMenuAlignment_Top = 1 << 2,
	eMenuAlignment_Right = 1 << 3,
	eMenuAlignment_Bottom = 1 << 4,
};

typedef class ObserverImpl<BOOL, ContextMenuParam> ContextMenuObserver;
typedef class ReceiverImpl<BOOL, ContextMenuParam> ContextMenuReceiver;
extern ContextMenuObserver s_context_menu_observer;

class DIRECTUI_API CMenuUI : public CListUI
{
public:
	CMenuUI();
	~CMenuUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface( LPCTSTR pstrName );

	virtual void DoEvent( TEventUI& event );

    virtual bool Add( CControlUI* pControl );
    virtual bool AddAt( CControlUI* pControl, int iIndex );
    virtual bool Remove( CControlUI* pControl );
	virtual int GetItemIndex( CControlUI* pControl ) const;
	virtual bool SetItemIndex( CControlUI* pControl, int iIndex );

	SIZE EstimateSize( SIZE szAvailable );
	void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );
};

/////////////////////////////////////////////////////////////////////////////////////
//

class CMenuElementUI;
class DIRECTUI_API CMenuWnd : public CWindowWnd, public ContextMenuReceiver
{
public:
	CMenuWnd( STRINGorID xml, LPCTSTR pSkinType, CPaintManagerUI* pParentManager );
	CMenuWnd( CMenuElementUI* pOwner, CPaintManagerUI* pParentManager );
	virtual ~CMenuWnd();

    LPCTSTR GetWindowClassName() const;
    void OnFinalMessage( HWND hWnd );

	virtual LRESULT OnCreate( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnClose( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnKillFocus( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
    LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual bool Notify( TNotifyUI& msg );

	BOOL Receive( ContextMenuParam param );

	void TrackPopupMenu( DWORD dwAlignment, POINT point, HWND hParentWnd );

	void SetItemTextPadding( RECT rc );
	bool AddMenuItem( CControlUI* pControl );
	void DeleteMenuItem( LPCTSTR pstrName );
	void CheckMenuItem( LPCTSTR pstrName, bool bCheck );
	void EnableMenuItem( LPCTSTR pstrName, bool bEnable );
	void ModifyMenu( LPCTSTR pstrName, LPCTSTR pstrText );
	CMenuUI* GetMenuRoot();
	void SetMaxHeight(int nHeight );
	int GetMaxHeight();
	void SetMinWidth( int nWidth );
	int GetMinWidth();

private:
	void CreateWndByOwner();
	void CreateWndByXml();

public:
	HWND m_hParentWnd;    // 菜单消息通知窗口句柄
	CPaintManagerUI* m_pParentManager;
	CPaintManagerUI m_pm;
	POINT m_BasedPoint;
	STRINGorID m_xml;
	CStdString m_sType;
    CMenuElementUI* m_pOwner;
	CMenuUI* m_pLayout;
	CMenuUI* m_pRoot;
	DWORD m_dwAlignMent;      // 菜单的对齐方式
	CSkinShadow* m_pSkinShadow;
	int m_nHeight;
	int m_nMinWidth;
	bool m_bDestroyWindow;
};

class DIRECTUI_API CMenuElementUI : public CListContainerElementUI
{
	friend CMenuWnd;
public:
    CMenuElementUI();
	~CMenuElementUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface( LPCTSTR pstrName );

    void DoPaint( HDC hDC, const RECT& rcPaint );

	void DrawItemText( HDC hDC, const RECT& rcItem );
	SIZE EstimateSize( SIZE szAvailable );

	bool Activate();
	void DoEvent( TEventUI& event );

	CMenuWnd* GetMenuWnd();
	void CreateMenuWnd();

	void CheckMenu( bool bCheck,bool bLeft = true );
	void SetCheckPos( RECT rc );
	bool SetSelect(bool bSelect);

	/*static */void SetDefaultCheckImage( LPCTSTR pstrImage );
	/*static */void SetDefaultSelCheckImage( LPCTSTR pstrImage );

protected:
	CMenuWnd* m_pWindow;
	CControlUI* m_pCheck;
	/*static */CStdString m_ckImage;
	/*static */CStdString m_ckSelImage;
};

} // namespace DirectUICore

#endif // __DUI_MENU_H__
