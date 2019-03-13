#ifndef __DUI_APPWINDOW_H__
#define __DUI_APPWINDOW_H__

#include "uishadow.h"
#include "waterroutine.h"

namespace DirectUICore {

class DIRECTUI_API CAppWindow : public CWindowWnd, public IDialogBuilderCallback
{
public:
	CAppWindow( STRINGorID strUI, unsigned int dwTransparent = 255, bool bDeleteSelf = true );
	virtual ~CAppWindow();

	// ��CWindowWnd::ShowWindow������ͬ���˴����ݴ���SW_SHOWNORMAL��SW_SHOWMINIMIZED��SW_SHOWMAXIMIZED�ȱ�ʶ
	// CWindowWnd::ShowWindow��Ҫ����DUI���ڲ�����
	void ShowWindow( int nCmdShow ); 

	// ��ʾ����Ӱ
	void ShowShadow( bool bShow /*= true*/ );
	//ǿ�Ƶ���ˢ��
//	void UpdateShadow();

	// ����ȡ��AppWindow���ڵ�WS_CLIPSIBLINGS��WS_CLIPCHILDREN���
	void SetDisableClipStyle( bool bDisableClipStyle );

public:
	virtual LPCTSTR GetWindowClassName() const;
	virtual UINT GetClassStyle() const;
	virtual void OnFinalMessage( HWND /*hWnd*/ );
	virtual CControlUI* CreateControl( LPCTSTR pstrClass );

	virtual void Init();
	virtual void Prepare();

	virtual LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam );
	
	virtual LRESULT OnCreate( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnClose( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnDestroy( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnNcActivate( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnNcCalcSize( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnNcPaint( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnNcHitTest( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnSize( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnGetMinMaxInfo( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT OnSysCommand( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );

	bool AddNotifier( CNotifyUIImpl* pNotifier );
	void RemoveNotifier( CNotifyUIImpl* pNotifier );

	virtual bool OnClose( TNotifyUI& msg );

	DECLARE_UI_MSG_MAP()

protected:
	CPaintManagerUI m_pm;
	STRINGorID	   m_strSkin;
	unsigned int   m_dwTransparent;
	bool           m_bDeleteSelf;
	CSkinShadow*   m_pSkinShadow;

	CWaterRoutine  m_myWater;
	DWORD* m_pSourceBits;
	DWORD* m_pTargetBits;

	bool m_bDisableClipStyle; // �Ƿ�ȡ��AppWindow���ڵ�WS_CLIPSIBLINGS��WS_CLIPCHILDREN���Ĭ���������������
}; 
}   // namespace DirectUICore

#endif // __APPWINDOW_H__