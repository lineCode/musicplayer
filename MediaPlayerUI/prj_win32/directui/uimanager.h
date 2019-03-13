#ifndef __DUI_MANAGER_H__
#define __DUI_MANAGER_H__
#include <deque>
#include <vector>

namespace DirectUICore {

class CControlUI;

/////////////////////////////////////////////////////////////////////////////////////
// Flags for CControlUI::GetControlFlags()
#define UIFLAG_TABSTOP       0x00000001
#define UIFLAG_SETCURSOR     0x00000002
#define UIFLAG_WANTRETURN    0x00000004

// Flags for FindControl()
#define UIFIND_ALL           0x00000000
#define UIFIND_VISIBLE       0x00000001
#define UIFIND_ENABLED       0x00000002
#define UIFIND_HITTEST       0x00000004
#define UIFIND_TOP_FIRST     0x00000008
#define UIFIND_ME_FIRST      0x80000000

// Flags for the CDialogLayout stretching
#define UISTRETCH_NEWGROUP   0x00000001
#define UISTRETCH_NEWLINE    0x00000002
#define UISTRETCH_MOVE_X     0x00000004
#define UISTRETCH_MOVE_Y     0x00000008
#define UISTRETCH_SIZE_X     0x00000010
#define UISTRETCH_SIZE_Y     0x00000020

// Flags used for controlling the paint
#define UISTATE_FOCUSED      0x00000001
#define UISTATE_SELECTED     0x00000002
#define UISTATE_DISABLED     0x00000004
#define UISTATE_HOT          0x00000008
#define UISTATE_PUSHED       0x00000010
#define UISTATE_READONLY     0x00000020
#define UISTATE_CAPTURED     0x00000040


/////////////////////////////////////////////////////////////////////////////////////
//

typedef struct tagTFontInfo
{
	HFONT hFont;             // ������ľ��
    CStdString sFontName;    // ��������
    int iSize;               // �ֺ�
    bool bBold;              // �Ƿ����
    bool bUnderline;         // �Ƿ����»���
    bool bItalic;            // �Ƿ�б��
    TEXTMETRIC tm;           // �������TEXTMETRIC��Ϣ
} TFontInfo;

typedef struct tagTImageInfo
{
    HBITMAP hBitmap;
    int nX;
    int nY;
    bool alphaChannel;
    CStdString sResType;
    DWORD dwMask;
	bool bGray;
} TImageInfo;

// Structure for relative position to the parent
typedef struct tagTRelativePosUI
{
	bool bRelative;
	SIZE szParent;
	int nMoveXPercent;
	int nMoveYPercent;
	int nZoomXPercent;
	int nZoomYPercent;
}TRelativePosUI;


// ��־������Ϣ�ṹ��
#if !COMMERCIAL_VERSION
typedef struct  tagNotifyUITracer
{
	time_t				m_tSendTime;		// ����ʱ��
	TNotifyUI			m_tNotifyUI;		// Notify��Ϣ
	CStdString			m_strSenderName;	// ��Ϣ���Ϳؼ�Name(��¼��Ϊ��¼��˿ؼ������ͷţ����治����ͨ����ָ��ȡֵ)
	bool				m_bAys;				// ͬ��/�첽

	HWND				m_hProcWnd;			// �ؼ��������ھ��
	CStdString			m_strProcWndClass;	// �ؼ�������������
	CStdString			m_strProcWndText;	// �ؼ��������ڱ���

	tagNotifyUITracer()
		: m_tSendTime( 0 )
		, m_strSenderName( _T("") )
		, m_bAys( false )
		, m_hProcWnd( NULL )
		, m_strProcWndClass( _T("") )
		, m_strProcWndText( _T("") )
	{
	}
}TNotifyUITracer, *PTNotifyUITracer;
#endif


/////////////////////////////////////////////////////////////////////////////////////
//
typedef CControlUI* (*LPCREATECONTROL)(LPCTSTR pstrType);


class DIRECTUI_API CPaintManagerUI
{
public:
    CPaintManagerUI();
    ~CPaintManagerUI();

	// ��־�����б�
#if !COMMERCIAL_VERSION	
	static std::deque<TNotifyUITracer> m_deqNotify;
#endif


public:
	// ��ͼ�������ĳ�ʼ��(m_hWndPaint,m_hDcPaint��ֵ����Ԥ������Ϣ�м��������)
    void Init( HWND hWnd );
	// ��ǰ��Ҫ���½���
    void NeedUpdate();
	// ָ��������Ч
    void Invalidate( RECT& rcItem );
	// ��ȡ��ͼ�豸DC
    HDC GetPaintDC() const;
	// ��ȡ��ͼ�Ĵ��ھ��
    HWND GetPaintWindow() const;
	// ��ȡ��ʾ���ھ��
    HWND GetTooltipWindow() const;
	// ��ȡ��ǰ���λ��
    POINT GetMousePos() const;
	// ��ȡ�ͻ�����С
    SIZE GetClientSize() const;
	// ��ȡ���ڳ�ʼ��ʱ�Ĵ�С
    SIZE GetInitSize();
	// ���ô����ʼ����С
    void SetInitSize( int cx, int cy );
	// ���ô����С
	void SetSize( int cx, int cy );
	// ��ȡ����ı߿������С
    RECT& GetSizeBox();
	// ���ô���ı߿������С
    void SetSizeBox( RECT& rcSizeBox );
	// ��ȡ���������С
    RECT& GetCaptionRect();
	// ���ñ��������С
    void SetCaptionRect( RECT& rcCaption );
	// ��ȡ�����Ľǵ�Բ�ǻ���
    SIZE GetRoundCorner() const;
	// ���ô����Ľǵ�Բ�ǻ���
    void SetRoundCorner( int cx, int cy );
	// ��ȡ������Ե���������С�Ĵ�С
    SIZE GetMinInfo() const;
	// ���ô�����Ե���������С�Ĵ�С
    void SetMinInfo( int cx, int cy );
	// ��ȡ������Ե����������Ĵ�С
    SIZE GetMaxInfo() const;
	// ���ô�����Ե����������Ĵ�С
    void SetMaxInfo( int cx, int cy );
	// ���ô���Ĳ�͸����(0��ȫ͸��-255��ȫ��͸��)
    void SetTransparent( int nOpacity );
	// ���û�ͼ�Ƿ�֧��͸������
    void SetBackgroundTransparent( bool bTrans );
	// �Ƿ���ʾ��������
    bool IsShowUpdateRect() const;
	// �����Ƿ���ʾ����
    void SetShowUpdateRect( bool show );
	// �Ƿ���Ӱ����
	bool IsShadow() const;
	// ������Ӱ����
	void SetShadow( bool shadow );
	// TABʵ�ֿؼ����л�
	void TabChange( std::vector<CControlUI*>& tabChangeControls );

	// ��ȡ��ǰ�����ʵ�����
    static HINSTANCE GetInstance();
	// ��õ�ǰ���е�ʵ����·��
    static CStdString GetInstancePath();
	// ��õ�ǰ�Ĺ���·��
    static CStdString GetCurrentPath();
	// ��ȡ��ԴDLL��ʵ�����
    static HINSTANCE GetResourceDll();
	// ��ȡ��Դ��·��(��"\"��β)
    static const CStdString& GetResourcePath();
	// ��ȡZip��Դ��·��
    static const CStdString& GetResourceZip();
	// ��ȡ��Դ�����ļ���
	static const CStdString& GetResourceIndexFileName();

	static bool IsCachedResourceZip();
    static HANDLE GetResourceZipHandle();
	// ����ʵ�����
    static void SetInstance( HINSTANCE hInst );
	// ���õ�ǰ�Ĺ���·��
    static void SetCurrentPath( LPCTSTR pStrPath );
	// ���õ�ǰ��DLL��Դ��ʵ�����
    static void SetResourceDll( HINSTANCE hInst );
	// ������Դ�����ļ���·��
    static void SetResourcePath( LPCTSTR pStrPath );
	// ����Zip��Դ��·��(����Zip�ļ���)
    static void SetResourceZip( LPVOID pVoid, unsigned int len );
    static void SetResourceZip( LPCTSTR pstrZip, bool bCachedResourceZip = false );
	static void SetResourceIndexFileName( LPCTSTR pStrIndexFileName );
	static void SetYaHei( bool bYaHei );

    static void GetHSL( short* H, short* S, short* L );
    static void SetHSL( bool bUseHSL, short H, short S, short L ); // H:0~360, S:0~200, L:0~200 
    static void ReloadSkin();
	static bool LoadPlugin( LPCTSTR pstrModuleName );
    static CStdPtrArray* GetPlugins();

	// ����ʹ���ϼ���Դ�Ļ�ͼ������
    bool UseParentResource( CPaintManagerUI* pm );
	//  ����ϼ���Դ��ͼ������
    CPaintManagerUI* GetParentResource() const;
	// ��ȡ����״̬��Ĭ����ɫ
    DWORD GetDefaultDisabledColor() const;
	// ���ý���״̬��Ĭ����ɫ
    void SetDefaultDisabledColor( DWORD dwColor );
	// ��ȡ����Ĭ����ɫ
    DWORD GetDefaultFontColor() const;
	// ��������Ĭ����ɫ
    void SetDefaultFontColor( DWORD dwColor );
	// ��ȡ�������ֵ�Ĭ��������ɫ   
    DWORD GetDefaultLinkFontColor() const;
	// �����������ֵ�Ĭ��������ɫ   
    void SetDefaultLinkFontColor( DWORD dwColor );
	// ��ȡ�����ͣ�ڳ����ϵ�Ĭ��������ɫ
    DWORD GetDefaultLinkHoverFontColor() const;
	// ���������ͣ�ڳ����ϵ�Ĭ��������ɫ
    void SetDefaultLinkHoverFontColor( DWORD dwColor );
	// ��ȡѡ��״���Ĭ�ϱ�����ɫ
    DWORD GetDefaultSelectedBkColor() const;
	// ����ѡ��״���Ĭ�ϱ�����ɫ
    void SetDefaultSelectedBkColor( DWORD dwColor );
	// ��ȡĬ��ʹ�õ�������Ϣ
    TFontInfo* GetDefaultFontInfo();
	// ����Ĭ��ʹ�õ�������Ϣ
    void SetDefaultFont( LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic );
	//  ��ȡ�û��Զ������������(һ���Ӧxml��Font������)
	DWORD GetCustomFontCount() const;
	// �����������б��в���������Դ
	HFONT AddFont( LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic );
	// �����������б��в���������Դ
	HFONT AddFontAt( int index, LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic );
	// ��ȡ������ָ���±�����������
	HFONT GetFont( int index );
	// �������鼯�����Ƿ����ָ�����õ��������
    HFONT GetFont( LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic );
	// �������鼯�����Ƿ�����������
	bool FindFont( HFONT hFont );
	// �������鼯�����Ƿ����ָ�����õ��������
	bool FindFont( LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic );
	// ���������������
	int GetFontIndex( HFONT hFont );
	// ����ָ����������Ϣ��ѯ��������
	int GetFontIndex( LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic );
	// �����������б����Ƴ��������
	bool RemoveFont( HFONT hFont );
	// �����������б����Ƴ�ָ��λ�õ�������Ϣ
    bool RemoveFontAt( int index );
	// ������������б�
    void RemoveAllFonts();
	// ͨ������������������������Ϣ
    TFontInfo* GetFontInfo( int index );
	// ͨ�������������ȡ������Ϣ
    TFontInfo* GetFontInfo( HFONT hFont );

	// ����ͼ��·������ͼ����Ϣ
    const TImageInfo* GetImage( LPCTSTR bitmap );
	// ��������,���ͣ�����ɫ ��ѯ ͼ����Ϣ
    const TImageInfo* GetImageEx( LPCTSTR bitmap, LPCTSTR type = NULL, DWORD mask = 0, bool bGrey = false );
    // ���ͼ��
	const TImageInfo* AddImage( LPCTSTR bitmap, LPCTSTR type = NULL, DWORD mask = 0, bool bGray = false  );
    const TImageInfo* AddImage( LPCTSTR bitmap, HBITMAP hBitmap, int iWidth, int iHeight, bool bAlpha );
	// ����ͼ�������Ƴ�ͼ��
	bool RemoveImage( LPCTSTR bitmap );
	// �Ƴ�����ͼ��
    void RemoveAllImages();
	// ���¼�������ͼ��
    void ReloadAllImages();

	// ��ӿؼ���Ĭ��������Ϣ(��button)
    void AddDefaultAttributeList( LPCTSTR pStrControlName, LPCTSTR pStrControlAttrList );
	// ���ݿؼ����Ʋ�ѯ����ؼ���Ĭ������
    LPCTSTR GetDefaultAttributeList( LPCTSTR pStrControlName ) const;
	// �Ƴ�ָ���ؼ��������Ƶ�Ĭ������
    bool RemoveDefaultAttributeList( LPCTSTR pStrControlName );
	// ��ȡĬ��������Ϣ�б�
    const CStdStringPtrMap& GetDefaultAttribultes() const;
	// ���Ĭ��������Ϣ�б�
    void RemoveAllDefaultAttributeList();

	// ���Ի���ؼ����ӵ���ǰ�Ĺ�������
    bool AttachDialog( CControlUI* pControl );
	// �ؼ���ʼ��
    bool InitControls( CControlUI* pControl, CControlUI* pParent = NULL );
	// �ؼ�����
    void ReapObjects( CControlUI* pControl );

	// ��ӿؼ���ָ����ѡ����
    bool AddOptionGroup( LPCTSTR pStrGroupName, CControlUI* pControl );
	// ��ѯָ��ѡ���������е�ȫ��ѡ��
    CStdPtrArray* GetOptionGroup( LPCTSTR pStrGroupName );
	// ��ָ���ؼ����Ƴ�ָ��ѡ�������Ƶ�ѡ����
    void RemoveOptionGroup( LPCTSTR pStrGroupName, CControlUI* pControl );
	// ���ȫ��ѡ�����б�
    void RemoveAllOptionGroups();

	// ��ȡ����״̬�Ŀؼ�
    CControlUI* GetFocus() const;
	// ���ÿؼ�Ϊ��ý���״̬
    void SetFocus( CControlUI* pControl );
	// ���ÿؼ�Ϊ��Ҫ���ƽ���
    void SetFocusNeeded( CControlUI* pControl );
	void SetFocusNeeded( bool bFocusNeeded );

	// ������һ�����Tab�����ý���Ŀؼ���Tab�Ƿ����������
    bool SetNextTabControl( bool bForward = true );

	// Ϊָ���ؼ��Լ����ӿؼ����ö�ʱ��
    bool SetTimer( CControlUI* pControl, UINT nTimerID, UINT uElapse );
	// �Ƴ�ָ���ؼ��ϵ�ָ����ŵĶ�ʱ��
    bool KillTimer( CControlUI* pControl, UINT nTimerID );
    void KillTimer( CControlUI* pControl );
	// ������еĶ�ʱ��
    void RemoveAllTimers();

	// ���ô����������¼�
    void SetCapture();
	// �ͷŴ��岶������¼�
    void ReleaseCapture();
	//  �жϴ����Ƿ��������¼�
    bool IsCaptured();

	// ��ӿؼ���֪ͨ������
    bool AddNotifier( INotifyUI* pControl );
	// ���ؼ���֪ͨ�������Ƴ�
    bool RemoveNotifier( INotifyUI* pControl );   
	// ����ͬ��/�첽֪ͨ
    void SendNotify( TNotifyUI& Msg, bool bAsync = false );
	// ����ͬ�����첽֪ͨ������
    void SendNotify( CControlUI* pControl, LPCTSTR pstrMessage, WPARAM wParam = 0, LPARAM lParam = 0, bool bAsync = false );

	// ��Ԥ������Ϣ���������������Ϣ������
    bool AddPreMessageFilter( IMessageFilterUI* pFilter );
	// ��Ԥ������Ϣ�������������Ƴ�ָ������Ϣ������
    bool RemovePreMessageFilter( IMessageFilterUI* pFilter );

	// ����Ϣ���������������Ϣ������
    bool AddMessageFilter( IMessageFilterUI* pFilter );
	// ����Ϣ�����������Ƴ���Ϣ������
    bool RemoveMessageFilter( IMessageFilterUI* pFilter );

	bool AddAnimJob( const CAnimJobUI& job );

	//  ��ȡ������Ҫ���ƵĿؼ�������
    int GetPostPaintCount() const;
	// ��������󼯺������Ҫ���ƵĿؼ�
    bool AddPostPaint( CControlUI* pControl );
	// �ӻ������󼯺����Ƴ�ָ���Ŀؼ�
    bool RemovePostPaint( CControlUI* pControl );
	// ����������ؼ����뵽�������󼯺ϵ�ָ��λ��
    bool SetPostPaintIndex( CControlUI* pControl, int iIndex );
	// ���ӳ��������������Ҫ�ӳ�����Ķ���
    void AddDelayedCleanup( CControlUI* pControl );

	// ��ȡ���ڵ�ؼ�
    CControlUI* GetRoot() const;
	// �Ӹ��ڵ㿪ʼ����ָ�������ڵĿؼ�
    CControlUI* FindControl( POINT pt ) const;
	// �Ӹ��ڵ㿪ʼ������ָ�����ƵĿؼ�
    CControlUI* FindControl( LPCTSTR pstrName ) const;
    CControlUI* FindSubControlByPoint( CControlUI* pParent, POINT pt ) const;
    CControlUI* FindSubControlByName( CControlUI* pParent, LPCTSTR pstrName ) const;
    CControlUI* FindSubControlByClass( CControlUI* pParent, LPCTSTR pstrClass, int iIndex = 0 );
    CStdPtrArray* FindSubControlsByClass( CControlUI* pParent, LPCTSTR pstrClass );
    CStdPtrArray* GetSubControlsByClass();

	bool AddTranslateAccelerator(ITranslateAccelerator *pTranslateAccelerator);
	bool RemoveTranslateAccelerator(ITranslateAccelerator *pTranslateAccelerator);
	bool TranslateAccelerator(LPMSG pMsg);
	void CPaintManagerUI::UsedVirtualWnd(bool bUsed);
	// ��Ϣѭ��������Ϸ�����Ϣ�ã��޷���������Ϣ�Ŀ���ʱ�� 
    static void MessageLoop();
	// ��Ϣ���룬��Win32ԭ�е���Ϣת�������ϣ�����Ҫ�Լ��������Ϣת������ϢԤ������
    static bool TranslateMessage( const LPMSG pMsg );
	static void Term();

    bool MessageHandler( UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes );

	/************************************************************************/
	/*	��ϢԤ������														*/
	/*	1.��ϢԤ�������(��ϢԤ������������϶���Ϣ���й��˴���)			*/
	/*	2.����Ƿ���Tab����������һ����ý���Ŀؼ�						*/
	/*	3.����Alt+Shortcut Key���º�Ŀؼ���ý���ͼ��������				*/
	/*	4.����Ƿ���ϵͳ����Ϣ�������ͻ�ý���Ŀؼ����¼�                */
	/************************************************************************/
    bool PreMessageHandler( UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes );
	bool IsDropAvailable( POINT pt, CControlUI* pParent = NULL );

	void UsedWaterRoutine( bool bUsed ){ m_bUsedWaterRoutine = bUsed; }
	bool IsUsedWaterRoutine(){ return m_bUsedWaterRoutine; }
	HDC GetSourceDC(){ return m_hDcOffscreen; }
	HDC GetTargetDC(){ return m_hDcWaterRoutine; }
	HBITMAP GetSourceBitmap(){ return m_hbmpOffscreen; }
	HBITMAP GetTargetBitmap(){ return m_hBmpWaterRoutine; }

private:
	// �����еĿؼ���ӵ�m_mNameHash��ϣ����
    static CControlUI* CALLBACK __FindControlFromNameHash( CControlUI* pThis, LPVOID pData );
	// ����ؼ�����
	static CControlUI* CALLBACK __FindControlFromCount( CControlUI* pThis, LPVOID pData );
	// ���ݵ��Ƿ��������У���ѯ�ؼ�
	static CControlUI* CALLBACK __FindControlFromPoint( CControlUI* pThis, LPVOID pData );
	// ͨ��Tab��Ϣ��ѯ�ؼ�
	static CControlUI* CALLBACK __FindControlFromTab( CControlUI* pThis, LPVOID pData );
    // �ӿ����в�ѯ�ؼ�
	static CControlUI* CALLBACK __FindControlFromShortcut( CControlUI* pThis, LPVOID pData );
    // ��ѯ��Ҫ���µĿؼ�
	static CControlUI* CALLBACK __FindControlFromUpdate( CControlUI* pThis, LPVOID pData );
    // ͨ�����ƱȽϲ�ѯ�ؼ�
	static CControlUI* CALLBACK __FindControlFromName( CControlUI* pThis, LPVOID pData );
    // ͨ�������Ƚϲ�ѯ�ؼ�
	static CControlUI* CALLBACK __FindControlFromClass( CControlUI* pThis, LPVOID pData );
    static CControlUI* CALLBACK __FindControlsFromClass( CControlUI* pThis, LPVOID pData );

private:
	// ������
    HWND m_hWndPaint;					// �ؼ����ִ��ھ�� 
	HWND m_hwndTooltip;					// ��ʾ���ھ��

	// ��ͼ�豸
	HDC m_hDcPaint;						// �ؼ����ִ����豸DC 
	HDC m_hDcOffscreen;					// �����ڴ�DC, �ڴ滺������ͼDC
	HDC m_hDcBackground;				// �����ڴ�DC, (֧��AlphaBackgroundʱʹ��)

	// λͼ
    HBITMAP m_hbmpOffscreen;			// �����ڴ�DC�����HBITMAP 
	HBITMAP m_hbmpBackground;			// �����ڴ�DC�����HBITMAP 

	// �ؼ���Ϣ
    CControlUI* m_pRoot;				// ����ؼ��ǵ��ӵ��������²�Ŀؼ�����,�����ŵ�һ�������Ŀؼ�����
    CControlUI* m_pFocus;				// ��Ż�ý���Ŀؼ�����ָ�� 
	CControlUI* m_pEventHover;			// ��ŵ�ǰ������ƽ��Ƴ��¼��Ŀؼ�����ָ�� 
    CControlUI* m_pEventClick;			// ��ŵ�ǰ�е���¼��Ŀؼ�����ָ��
    CControlUI* m_pEventKey;			// ��ŵ�ǰ�а����¼��Ŀؼ�����ָ��
	
	// λ�ü�¼��Ϣ
	POINT m_ptLastMousePos;				// ������µ�λ��
	SIZE m_szMinWindow;					// ���ô�����Ե���������С��С
	SIZE m_szMaxWindow;					// ������Ե�����������С
	SIZE m_szInitWindowSize;			// �����ʼ��ʱ�Ĵ�С
	RECT m_rcSizeBox;					// ������߿�����Ĵ�С
	SIZE m_szRoundCorner;				// �����Ľǵ�Բ�ǻ���
	RECT m_rcCaption;					// ��������������С
	UINT m_uTimerID;					// ��ǰ��ʱ��ID

	// ��ʶ����Ϣ 
	bool m_bShowUpdateRect;				// �Ƿ���ʾ��������
    bool m_bFirstLayout;				// �Ƿ����׸�����
	bool m_bUpdateNeeded;				// �Ƿ���Ҫ���½���
	bool m_bFocusNeeded;				// �Ƿ���Ҫ����
	bool m_bOffscreenPaint;				// �Ƿ���Ҫ��˫�����ͼ
	bool m_bAlphaBackground;			// ���屳���Ƿ���Ҫ֧��Alphaͨ��(��pngͼƬ�İ�͸��Ч��)
	bool m_bMouseTracking;				// �Ƿ���Ҫ֧�����׷��
	bool m_bMouseCapture;				// �Ƿ���Ҫ֧����겶��
	bool m_bShadow;				        // �Ƿ�֧����Ӱ����

	// ��������Ϣ
    CStdPtrArray m_aNotifiers;					// ��¼������Ҫ�¼�֪ͨ�Ĵ���,���ݴ������Ƶ�����Ӧ����Ϣ������
	CStdPtrArray m_aTimers;						// ��ʱ������
	CStdPtrArray m_aPreMessageFilters;			// Ԥ������Ϣ����
	CStdPtrArray m_aMessageFilters;				// ������Ҫ������Ϣ���˵Ŀؼ�����(�綯����) 
	CStdPtrArray m_aPostPaintControls;			// ���ͻ�������Ŀؼ�����
	CStdPtrArray m_aDelayedCleanup;				// �ӳ�����Ķ��󼯺�
	CStdPtrArray m_aAsyncNotify;				// �첽֪ͨ��Ϣ����
    CStdPtrArray m_aFoundControls;
	CStdStringPtrMap m_mNameHash;				// ����ؼ�����ָ��hash��(�ÿؼ���������hashֵ) 
	CStdStringPtrMap m_mOptionGroup;			// ѡ����Map
    
	// xml��Ӧ��Դ
	CPaintManagerUI* m_pParentResourcePM;		// �ϼ�(����)��Դ��PaintManagerUI��ͼ������
	DWORD m_dwDefaultDisabledColor;				// Ĭ��ʧЧ״̬��ɫ
	DWORD m_dwDefaultFontColor;					// Ĭ��������ɫ
	DWORD m_dwDefaultLinkFontColor;				//  Ĭ�ϳ�����������ɫ
	DWORD m_dwDefaultLinkHoverFontColor;		// Ĭ�ϳ����������ͣ״̬��������ɫ
	DWORD m_dwDefaultSelectedBkColor;			// Ĭ��ѡ��״̬����ɫ
	TFontInfo m_DefaultFontInfo;				// Ĭ��������Ϣ
    CStdPtrArray m_aCustomFonts;				// �Զ���������Դ����
    CStdStringPtrMap m_mImageHash;				// ͼƬ��Դ��HashMap
    CStdStringPtrMap m_DefaultAttrHash;			// DefaultAttr��ԴHashMap
    
	//
	static HINSTANCE m_hInstance;				// ��ǰ�����Instanceʵ��
	static HINSTANCE m_hResourceInstance;		// ��ǰ�������ԴDLL Instanceʵ��
	static CStdString m_pStrResourcePath;		// ��ǰʹ�õ���Դ·��
	static CStdString m_pStrResourceZip;		// ��ǰʹ�õ���Դѹ�����ļ�ȫ��
	static CStdString m_pStrResIndexFileName;   // ��ǰʹ�õ���Դ�����ļ�
	static bool m_bCachedResourceZip;
	static bool m_bYaHei;                       // �Ƿ���΢���ź�
    static HANDLE m_hResourceZip;
    static short m_H;
    static short m_S;
    static short m_L;
    static CStdPtrArray m_aPreMessages;			// Ԥ������Ϣ 
    static CStdPtrArray m_aPlugins;
	TOOLINFO m_ToolTip;

	bool m_bUsedVirtualWnd;
	CStdPtrArray m_aTranslateAccelerator;

	// ˮ��Ч�����
	bool    m_bUsedWaterRoutine;
	HDC     m_hDcWaterRoutine;
	HBITMAP m_hBmpWaterRoutine;
};

} // namespace DirectUICore

#endif // __UIMANAGER_H__
