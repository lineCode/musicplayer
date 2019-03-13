#ifndef UI_CONTROL_WND_H
#define UI_CONTROL_WND_H

namespace DirectUICore {

class DIRECTUI_API CControlWndUI : public CWindowWnd, public CControlUI
{
public:
	CControlWndUI();
	virtual ~CControlWndUI();

	virtual LPCTSTR GetClass() const;
	virtual LPVOID GetInterface( LPCTSTR pstrName );
	virtual LPCTSTR GetWindowClassName() const;	
	virtual void SetManager( CPaintManagerUI* pManager, CControlUI* pParent, bool bInit = true );
	virtual void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );

	virtual void DoInit();

	virtual void SetVisible( bool bVisible = true );
	virtual void SetInternVisible( bool bVisible = true ); 

	virtual void SetEnabled( bool bEnable = true );
	virtual void SetInternEnable( bool bEnable = true );   

	virtual void SetPos( RECT rc );
	virtual void Invalidate();

	virtual bool Notify( TNotifyUI& msg );
	LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam );
	LRESULT OnCreate( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	LRESULT OnPaint( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	void SetSkinXml( STRINGorID strSkin );
	void SetWndColor( DWORD dwWndColor);	// ÉèÖÃ´°¿Ú±³¾°É«


protected:
	CPaintManagerUI m_pm;
	STRINGorID m_strSkin;
	DWORD m_dwWndColor;
	bool m_bFirstLayout;	
	bool m_bSkinXml;
	bool m_bCreate;	
};

} // namespace DirectUICore

#endif 
