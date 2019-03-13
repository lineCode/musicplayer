#ifndef __DUI_WINDOW_H__
#define __DUI_WINDOW_H__

namespace DirectUICore 
{

	// ������ʽ��
#define UI_WNDSTYLE_CONTAINER  (0)																							// ������ʽ�����κ���ʽ  
#define UI_WNDSTYLE_FRAME      (WS_OVERLAPPEDWINDOW)															// UI��׼��ܴ�����ʽ(���������߿�ͼ�ꡢ���⡢�����С��ť���رհ�ť)
#define UI_WNDSTYLE_CHILD      (WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)									// UI�����ӿؼ���ʽ
#define UI_WNDSTYLE_DIALOG     (WS_POPUPWINDOW | WS_CAPTION | WS_DLGFRAME | WS_CLIPSIBLINGS | WS_CLIPCHILDREN) // UI�Ի�������ʽ
#define UI_WNDSTYLE_BOX        (WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME )
	// ��չ������ʽ��
#define UI_WNDSTYLE_EX_FRAME    (WS_EX_WINDOWEDGE)							// ����ͻ���������ʽ
#define UI_WNDSTYLE_EX_DIALOG   (WS_EX_TOOLWINDOW | WS_EX_DLGMODALFRAME)	// ������������ʽ+ģʽ�Ի�����ʽ

	// ����ʽ��
#define UI_CLASSSTYLE_CONTAINER  (0)													// ��������ʽ
#define UI_CLASSSTYLE_FRAME      (CS_VREDRAW | CS_HREDRAW)								// ˮƽ����ֱ��С�ı�ʱ����
#define UI_CLASSSTYLE_CHILD      (CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)	// ˮƽ����ֱ��С�ı�ʱ���ơ�֧��˫���¼������洰��λͼ
#define UI_CLASSSTYLE_DIALOG     (CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)	// ˮƽ����ֱ��С�ı�ʱ���ơ�֧��˫���¼������洰��λͼ

/////////////////////////////////////////////////////////////////////////////////////
// ������
/////////////////////////////////////////////////////////////////////////////////////
class DIRECTUI_API CWindowWnd : public CNotifyUIImpl
{
public:
	CWindowWnd();
	// ��ȡ���ھ��
	HWND GetHWND() const;
	operator HWND() const;
	HWND m_hWnd;			// ����������ʼ��ΪNULL

	BOOL IsWindowVisible() const;
	BOOL IsIconic() const;
	BOOL GetWindowRect(LPRECT lpRect) const;
	BOOL GetClientRect(LPRECT lpRect) const;
	void SetActiveWindow();
	BOOL SetForegroundWindow();
	BOOL FlashWindow(BOOL bInvert);
	void UpdateWindow();
	void Invalidate(BOOL bErase = TRUE);
	void MoveWindow(LPCRECT lpRect, BOOL bRepaint = TRUE);

	bool IsMaxShow(){ return m_bMaxShow; }

	/************************************************************************/
	/*	ע�ᴰ�ڹ���														*/
	/*	1.����GetClassStyle��ȡ��ʽ��Ϣ										*/
	/*	2.���û�ͼ�������ľ�̬������ȡʵ��CPaintManagerUI::GetInstance()	*/
	/*	3.����GetWindowClassName()��ȡҪע���������                        */
	/************************************************************************/
	bool RegisterWindowClass();
	// ͨ���Ѵ��ڵĴ�����Ϊ����ע�ᴰ����
	bool RegisterSuperclass();
	// ���ڴ���
	HWND Create( HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu = NULL );
	/************************************************************************/
	/* 	��������															*/
	/*	1.������ڸ�����������ע�Ḹ��������								*/
	/*	2.�����ڸ����������������Ĵ���ע��									*/
	/*	3.����ע��ɹ��󣬴�������                                          */
	/************************************************************************/
	HWND Create( HWND hwndParent, LPCTSTR pstrName
			  , DWORD dwStyle, DWORD dwExStyle
			  , int x = CW_USEDEFAULT, int y = CW_USEDEFAULT
			  , int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT
			  , HMENU hMenu = NULL );
	// �������໯
	HWND Subclass( HWND hWnd );
	// ж�ش������໯
	void Unsubclass();
	// ��ʾ����
	void ShowWindow( bool bShow = true, bool bTakeFocus = false );
	// ��ʾģʽ����
	UINT ShowModal();
	// �رմ���
	void Close( UINT nRet = IDOK );
	// ���ھ��У����Ϊ�Ӵ��ڣ�����ڸ����ڵ�����
	void CenterWindow();
	// ͨ����ԴID������ͼ��
	void SetIcon( UINT nRes );
	// ����UIͬ����Ϣ
	LRESULT SendMessage( UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L );
	// Ͷ��UI�첽��Ϣ
	LRESULT PostMessage( UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L );
	// �����ͻ�����С
	void ResizeClient( int cx = -1, int cy = -1 );

	DECLARE_UI_MSG_MAP()

protected:
	// ��ȡ���������ƣ��������ʵ�ָô��麯��
	virtual LPCTSTR GetWindowClassName() const = 0;	
	// ��ȡ�������ƣ��������໯
	virtual LPCTSTR GetSuperClassName() const;		
	// �������ʽ
	virtual UINT GetClassStyle() const;						
	// ��Ϣ������
	virtual LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam );	
	// ��������ǰ���Ĵ�����
	virtual void OnFinalMessage( HWND hWnd );									
	//  ���ڹ��̻ص�����
	static LRESULT CALLBACK __WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	// �ؼ����̻ص�����
	static LRESULT CALLBACK __ControlProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	// add by zlg 2014/02/24
	void DestroyWindow();

protected:
	WNDPROC m_OldWndProc;	// Win32���ڹ��̣�Ĭ��ΪDefWindowProc
	HWND m_hWndParent;
	bool m_bSubclassed;		// �Ƿ����໯��Ĭ��Ϊfalse
	bool m_bMaxShow;
};
} // namespace DirectUICore

#endif // __UIWINDOW_H__