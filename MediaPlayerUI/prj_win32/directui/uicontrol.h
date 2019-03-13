#ifndef __DUI_CONTROL_H__
#define __DUI_CONTROL_H__
#include <deque> 
#include <time.h>

namespace DirectUICore {

/////////////////////////////////////////////////////////////////////////////////////
// ���ඨ�������пؼ��Ŀ��ܾ��еĻ�������
//////////////////////////////////////////////////////////////////////////
class CControlUI;
typedef CControlUI* (CALLBACK* FINDCONTROLPROC)(CControlUI*, LPVOID);

#if COMMERCIAL_VERSION
#else
typedef struct tagCtrlCrashTracer
{
	time_t  m_tDesTime;				// �ؼ���ȡʱ��
	void*	m_pCtrlPointer;			// �ؼ�ָ��
	CStdString m_strCtrlName;		// �ؼ�Name
	HWND	m_hOwnWnd;				// �ؼ��������ھ��
	CStdString m_strOwnWndClass;	// �ؼ�������������
	CStdString m_strOwnWndCaption;	// �ؼ��������ڱ���

	tagCtrlCrashTracer()
		: m_pCtrlPointer( NULL )
		, m_tDesTime( 0 )
		, m_strCtrlName( _T("") )
		, m_hOwnWnd( NULL )
		, m_strOwnWndClass( _T("") )
		, m_strOwnWndCaption( _T("") )
	{			
	}
}TCtrlCrashTracer, *PTCtrlCrashTracer;
#endif


class DIRECTUI_API CControlUI
{
public:
    CControlUI();
    virtual ~CControlUI();

#if COMMERCIAL_VERSION
#else
	static std::deque<TCtrlCrashTracer> m_deqTracer;
#endif

public:
	// �õ��ؼ����� ����Ϊ�ؼ���ΨһID
    virtual CStdString GetName() const;
	// ���ÿؼ�����
    virtual void SetName( LPCTSTR pstrName );
	// �õ��ؼ�����
    virtual LPCTSTR GetClass() const;
	// �õ��ؼ�ָ��
    virtual LPVOID GetInterface( LPCTSTR pstrName );
	// �õ��ؼ����ͱ�־
    virtual UINT GetControlFlags() const;
	// �ؼ��Ƿ��Ծ (�ǲ�����״̬���ǲ��ɼ�״̬)
    virtual bool Activate();
	// �õ����ƹ�����
    virtual CPaintManagerUI* GetManager() const;
	// ���ÿؼ��Ļ��ƹ����ߣ���ʼ����
    virtual void SetManager( CPaintManagerUI* pManager, CControlUI* pParent, bool bInit = true );
    // �õ����ؼ�
	virtual CControlUI* GetParent() const;

    // �õ��ؼ���ʾ����
    virtual CStdString GetText() const;
	// ���ÿؼ���ʾ����
    virtual void SetText( LPCTSTR pstrText );

	// * ����ɫ1,2,3���ڽ���ɫ ��ɫ�������Ϊ1->2->3
    // �õ�����ɫ
    DWORD GetBkColor() const;
	// ���ñ���ɫ
    void SetBkColor( DWORD dwBackColor) ;
	// �õ�����ɫ 2
    DWORD GetBkColor2() const;
	// ���ñ���ɫ 2
    void SetBkColor2( DWORD dwBackColor );
	// �õ�����ɫ 3
    DWORD GetBkColor3() const;
	// ���ñ���ɫ 3
    void SetBkColor3( DWORD dwBackColor );

	// �õ�����ͼƬ
    LPCTSTR GetBkImage();
	// ���ñ���ͼƬ
    void SetBkImage( LPCTSTR pStrImage );
	// �õ��ߵ���ɫ
    DWORD GetBorderColor() const;
	// ���ñߵ���ɫ
    void SetBorderColor( DWORD dwBorderColor );
	// ��ȡ��ý���ʱ�ߵ���ɫ
	DWORD GetFocusBorderColor() const;
	// ���û�ý���ʱ�ߵ���ɫ
	void SetFocusBorderColor( DWORD dwBorderColor );
    bool IsColorHSL() const;
    void SetColorHSL( bool bColorHSL );

	// �õ��ߵĿ��
    int GetBorderSize() const;
	// ���ñߵĿ��
    void SetBorderSize( int nSize );
	// �õ�Բ��
    SIZE GetBorderRound() const;
	// ����Բ��
    void SetBorderRound( SIZE cxyRound );
	// ����ͼƬ
    bool DrawImage( HDC hDC, LPCTSTR pStrImage, LPCTSTR pStrModify = NULL );
	BOOL DrawButtonImage( HDC hDC, LPCTSTR pStrImage, int nCurState, int nStateCount, BOOL bPicSize = FALSE );
	bool DrawRectImage( HDC hDC, LPCTSTR pStrImage, RECT rc,  LPCTSTR pStrModify = NULL );

    // �õ��ؼ�λ��
    virtual const RECT& GetPos() const;
	// ���ÿؼ�λ�ò��ػ�
    virtual void SetPos( RECT rc );
	// �õ��ؼ����
    virtual int GetWidth() const;
	// �õ��ؼ��߶�
    virtual int GetHeight() const;
	// �õ��ؼ�������λ��(���ϵ������)
    virtual int GetX() const;
	// �õ��ؼ�������λ��(���ϵ�������)
    virtual int GetY() const;
	// ��ȡ��߾�
    virtual RECT GetPadding() const;
	// ������߾࣬���ϲ㴰�ڻ���(����Χ�ؼ�����Զ������(��ֵ�������ܻ���˳��Ӱ�죬�Ƚ�����)
    virtual void SetPadding( RECT rcPadding );
	// ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
    virtual SIZE GetFixedXY() const;   
	// ��floatΪtrueʱ��Ч
    virtual void SetFixedXY( SIZE szXY );
	// ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
    virtual int GetFixedWidth() const; 
	// Ԥ��Ĳο�ֵ
    virtual void SetFixedWidth( int cx ); 
	// ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
    virtual int GetFixedHeight() const;        
    // Ԥ��Ĳο�ֵ
	virtual void SetFixedHeight( int cy ); 
	// Ԥ��Ĳο�ֵ
	virtual void SetBkImageWidth( int cx ); 
	virtual int GetBkImageWidth() const; 
	// Ԥ��Ĳο�ֵ
	virtual void SetBkImageHeight( int cy ); 
	virtual int GetBkImageHeight() const; 

	// ���ô�С������ֵ
	virtual int GetMinWidth() const;
    virtual void SetMinWidth( int cx );
    virtual int GetMaxWidth() const;
    virtual void SetMaxWidth( int cx );
    virtual int GetMinHeight() const;
    virtual void SetMinHeight( int cy );
    virtual int GetMaxHeight() const;
    virtual void SetMaxHeight( int cy );

	// �������λ�ñ���
    virtual void SetRelativePos( SIZE szMove, SIZE szZoom );
	// ���ø��ؼ���С
    virtual void SetRelativeParentSize( SIZE sz );
	// �õ����λ�ñ���
    virtual TRelativePosUI GetRelativePos() const;
	// �Ƿ�ʹ�����λ��
    virtual bool IsRelativePos() const;

    // ��ȡ/���� ��ʾ��Ϣ
    virtual CStdString GetToolTip() const;
    virtual void SetToolTip( LPCTSTR pstrText );

	virtual int GetMaxTipWidth() const;
	virtual void SetMaxTipWidth( int nWidth );

	// ��ʾ�Ƿ��ö���ʾ������ʹ��
	virtual bool IsToolTipTop() const{ return m_bToolTipTopMost; }
	virtual void SetToolTipTop( bool bTopMost ){ m_bToolTipTopMost = bTopMost; }

    // ��ȡ/���� ��ݼ�
    virtual TCHAR GetShortcut() const;
    virtual void SetShortcut( TCHAR ch );

    // ��ȡ/���� �����Ĳ˵��Ƿ�ʹ��
    virtual bool IsContextMenuUsed() const;
    virtual void SetContextMenuUsed( bool bMenuUsed );

    // ��ȡ/���� �û�����(�ַ���)
    virtual const CStdString& GetUserData();       // �������������û�ʹ��
    virtual void SetUserData( LPCTSTR pstrText );   // �������������û�ʹ��
	
	// ��ȡ/���� �û�ָ��
	virtual UINT_PTR GetTag() const;               // �������������û�ʹ��
    virtual void SetTag( UINT_PTR pTag );           // �������������û�ʹ��

    // ��ȡ/���� �ؼ��Ƿ�ɼ�
    virtual bool IsVisible() const;
    virtual void SetVisible( bool bVisible = true );
	// �����ڲ����ã���ЩUIӵ�д��ھ������Ҫ��д�˺���
	// �д��ھ����UI�����ò��ɼ�ʱ����Ҫ��ʧȥ����
    virtual void SetInternVisible( bool bVisible = true );
    
	// ��ȡ/���� �ؼ��Ƿ����
	virtual bool IsEnabled() const;
    virtual void SetEnabled( bool bEnable = true );
	// �����ڲ����ã���ЩUIӵ�д��ھ������Ҫ��д�˺���
	virtual void SetInternEnable( bool bEnable = true ); 

	// ��ȡ/���� �Ƿ�������¼�
    virtual bool IsMouseEnabled() const;
    virtual void SetMouseEnabled( bool bEnable = true );

	virtual bool IsKeyboardEnabled() const;
    virtual void SetKeyboardEnabled( bool bEnable = true );

	// �ؼ��Ƿ��ý���
    virtual bool IsFocused() const;
	// ���ÿؼ���ý���
    virtual void SetFocus();

	// �ؼ��Ƿ�����
    virtual bool IsFloat() const;
	// ���ÿؼ�Ϊ����
    virtual void SetFloat( bool bFloat = true );

	// ǿ��Floatʱ�Ƿ���ʾ������
	virtual bool IsFloatScroll() const;
	virtual void SetFloatScroll( bool bScroll = true );

	// ���ҿؼ�
    virtual CControlUI* FindControl( FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags );

	// ���� - ������Ч,����ˢ��
	// ʵ�� - ѭ��������ؼ�Ϊֹ, ���㵱ǰ��Ч�����븸�ؼ�����������Ϊ����Ч����
    virtual void Invalidate();

	// ��ȡ/���� �����״̬
    bool IsUpdateNeeded() const;
	void NeedUpdate( bool bNeed = true ); // ����bNeed��2014/02/27�¼ӵģ�������������õ��ò�������������ʹ��Ĭ�ϲ���true
	void NeedParentUpdate();

    DWORD GetAdjustColor( DWORD dwColor );

	// ��ʼ���ؼ��¼���Ӧ, ��SetManager()�б�����
    virtual void Init();
	// ����ʼ��������, ��Init()����
    virtual void DoInit();

	// �¼���Ӧ����
    virtual void Event( TEventUI& event );
    virtual void DoEvent( TEventUI& event );

	// ��������, ���ݽ���������ƶ������ĵ���������״̬��Ա������ֵ
    virtual void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );
	// ������ǩ�������ַ���, ����SetAttribute()
    CControlUI* ApplyAttributeList( LPCTSTR pstrList );

	// Ԥ���ؼ���С
    virtual SIZE EstimateSize( SIZE szAvailable );

	// ���� - �ؼ�����
	// ʵ�� - ����ѭ�򣺱�����ɫ->����ͼ->״̬ͼ->�ı�->�߿�
    virtual void DoPaint( HDC hDC, const RECT& rcPaint );
	// ���Ʊ���ɫ
    virtual void PaintBkColor( HDC hDC );
	// ���Ʊ���ͼƬ
    virtual void PaintBkImage( HDC hDC );
	// ����״̬���Ʊ���ͼƬ
    virtual void PaintStatusImage( HDC hDC );
	// ��������
    virtual void PaintText( HDC hDC );
	// ���Ʊ߿�
    virtual void PaintBorder( HDC hDC );

    virtual void DoPostPaint( HDC hDC, const RECT& rcPaint );

	// ���ÿؼ��Ƿ���Խ����϶�����
	virtual bool IsDropAvailable();
	virtual void SetDropAvailable( bool bAvailable = true );

	// ��Control�ؼ��еĵ���ͼƬ������ʾ��������Ҫ��ͼƬ���п�ߵĵȱ�������
	virtual void SetCenterImage( bool bCenterImage = true );
	virtual RECT CalcCenterImageRect( RECT& rc );

public:
	// �¼�Դ - ����ͨ��ί�е����ģʽΪ��ʼ�������٣��¼���������м������Ĵ������
    CEventSource OnInit;	// ��ʼ���¼�Դ
    CEventSource OnDestroy;	// �����¼�Դ
    CEventSource OnSize;
    CEventSource OnEvent;	// �¼���Ӧ�¼�Դ
    CEventSource OnNotify;

protected:
	CPaintManagerUI* m_pManager;	// ���ڻ�ؼ���ͼ����Ϣ������ 
    CControlUI* m_pParent;			// �߼��ϵĸ�����(�ؼ�)����ָ��
    CStdString m_sName;				// �ؼ���ʶ
    bool m_bUpdateNeeded;
    bool m_bMenuUsed;
    RECT m_rcItem;
    RECT m_rcPadding;
    SIZE m_cXY;                     // ��pos����ֵ�õ�������ڸ����������Ͻǵ�����
    SIZE m_cxyFixed;                // ��pos����ֵ�õ��ĵ�ǰ�ؼ��Ŀ�Ⱥ͸߶�
    SIZE m_cxyMin;
    SIZE m_cxyMax;
	SIZE m_cxyBkImage;
    bool m_bVisible;
    bool m_bInternVisible;
	bool m_bInternEnabled;
    bool m_bEnabled;
    bool m_bMouseEnabled;
	bool m_bKeyboardEnabled;
	bool m_bDropAvailable;
	bool m_bCenterImage;                // ��Control�ؼ��еĵ���ͼƬ������ʾ��������Ҫ��ͼƬ���п�ߵĵȱ�������
    bool m_bFocused;
    bool m_bFloat;
	bool m_bFloatScroll;
    bool m_bSetPos;						// ��ֹSetPosѭ������
    TRelativePosUI m_tRelativePos;

    CStdString m_sText;					// �ؼ���ʾ�������ʾ�ű��ַ���
	CStdString m_sToolTip;				// ���Ƶ�Tip��Ϣ
	DWORD	m_dwToolTipMaxWidth;		// ToolTip�����(���ڶ�����ʾ)
	bool m_bToolTipTopMost;
    TCHAR m_chShortcut;
    CStdString m_sUserData;
    UINT_PTR m_pTag;

    DWORD m_dwBackColor;
    DWORD m_dwBackColor2;
    DWORD m_dwBackColor3;
    CStdString m_sBkImage;
    DWORD m_dwBorderColor;
	DWORD m_dwFocusBorderColor;
    bool m_bColorHSL;
    int m_nBorderSize;
    SIZE m_cxyBorderRound;
    RECT m_rcPaint;
};



// ��־���ٴ�ӡ��
class DIRECTUI_API CCrachTracer
{
public:
	void PrintControlDestructMap();
	void PrintNotifyMessage();
};

} // namespace DirectUICore

#endif // __UICONTROL_H__
