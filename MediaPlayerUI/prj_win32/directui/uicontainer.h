#ifndef __DUI_CONTAINER_H__
#define __DUI_CONTAINER_H__

namespace DirectUICore {
/////////////////////////////////////////////////////////////////////////////////////
//	���������

class IContainerUI
{
public:
	// �õ������пؼ���
    virtual CControlUI* GetItemAt( int iIndex ) const = 0;
	// �������пؼ����ȡ���
    virtual int GetItemIndex( CControlUI* pControl ) const  = 0;
	// ���ÿؼ���Ϊ�����д��ڵ�ָ����ŵĿؼ���
    virtual bool SetItemIndex( CControlUI* pControl, int iIndex )  = 0;
	// ��ȡ�����ؼ�����
    virtual int GetCount() const = 0;
	// ����һ���ؼ���������
    virtual bool Add( CControlUI* pControl ) = 0;
	// ����һ���ؼ���������
    virtual bool AddAt( CControlUI* pControl, int iIndex )  = 0;
	// ɾ�������пؼ���
    virtual bool Remove( CControlUI* pControl ) = 0;
	// ɾ��ָ����ŵ������ؼ���
    virtual bool RemoveAt( int iIndex )  = 0;
	// ɾ�����������еĿؼ�
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
//	�����ؼ�
class CScrollBarUI;

class DIRECTUI_API CContainerUI : public CControlUI, public IContainerUI
{
public:
    CContainerUI();
    virtual ~CContainerUI();

public:
    LPCTSTR GetClass() const;
    LPVOID GetInterface( LPCTSTR pstrName );
	// ���û滭�¼��ص�
	void SetDrawEvent( IDrawEvent* pIDrawEvent ){ m_pIDrawEvent = pIDrawEvent; }

	// �������ظ���Ĵ��麯��
    CControlUI* GetItemAt( int iIndex ) const;
	int GetItemIndex( CControlUI* pControl ) const;
	int GetItemIndexByName( LPCTSTR pstrName ) const;
    bool SetItemIndex( CControlUI* pControl, int iIndex );
	bool SetItemIndexByName( LPCTSTR pstrName, int iIndex );
    int GetCount() const;
	// ��ȡ�����ؼ��б�
	CStdPtrArray& GetItemList();
    bool Add( CControlUI* pControl );
    bool AddAt( CControlUI* pControl, int iIndex );
    bool Remove( CControlUI* pControl );
    bool RemoveAt(int iIndex);
    void RemoveAll();

	bool Activate( TEventUI& event );
    void DoEvent( TEventUI& event );
    void SetVisible( bool bVisible = true );
    void SetInternVisible( bool bVisible = true );	// �����ڲ����ã���ЩUIӵ�д��ھ������Ҫ��д�˺���
    void SetMouseEnabled( bool bEnable = true );	// �����Ƿ�������¼�

	// ��ȡ/�����ڱ߾࣬�൱�����ÿͻ���
    virtual RECT GetInset() const;
    virtual void SetInset( RECT rcInset );

	// ��ȡ/���� �ؼ�����
    virtual int GetChildPadding() const;
    virtual void SetChildPadding( int iPadding );

	// ��ȡ/���������ڿؼ����Ƿ��Զ��ݻ�
    virtual bool IsAutoDestroy() const;
    virtual void SetAutoDestroy( bool bAuto );

	// ��ȡ/�������������Ƿ��ӳٴݻ�
    virtual bool IsDelayedDestroy() const;
    virtual void SetDelayedDestroy( bool bDelayed );

	// ����ȡ/���������пؼ��Ƿ���Ӧ����¼�
    virtual bool IsMouseChildEnabled() const;
    virtual void SetMouseChildEnabled( bool bEnable = true );

	// ������������һ����ѡ��
    virtual int FindSelectable( int iIndex, bool bForward = true ) const;

    void SetPos( RECT rc );							// ����λ��
    void DoPaint( HDC hDC, const RECT& rcPaint );	// ����

    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );	// ��������

	// ���ý��������
    void SetManager( CPaintManagerUI* pManager, CControlUI* pParent, bool bInit = true );
    CControlUI* FindControl( FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags );

	// �ú����ǲ��������FindControlд�ģ���ͬ�������ҵ��ؼ�ʱ������һ��SetPos���������߾�
	// ���ҵ��ؼ�����ֱ��return��Ӧ�ý��������������Ŀؼ���SetPosһ�¡��˺�����Ҫ�ṩ��
	// CPaintManagerUI::MessageHandler���ã��Խ��CPaintManagerUI::MessageHandler�ڴ�
	// ��WM_PAINT��Ϣʱ����ѭ�����⣬������ѭ��ԭ���FindControl_SetPos�ĵ��ô�˵����by zzx 2014/02/27
	// --�ú����ᵼ������������ʾ�����⣬�ݲ�ʹ�ã�����--
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

    virtual SIZE GetScrollPos() const;		// ��ȡ������λ��
    virtual SIZE GetScrollRange() const;	// ��ȡ��������Χ
    virtual void SetScrollPos( SIZE szPos );
    virtual void LineUp();					// ����һ�У�һ��ΪĬ������߶ȣ�
    virtual void LineDown();				// ����һ��
    virtual void PageUp();					// ����һҳ
    virtual void PageDown();				// ����һҳ
    virtual void HomeUp();					// ����
    virtual void EndDown();					// ����
    virtual void LineLeft();				// ����һ�У�8�����أ�
    virtual void LineRight();				// ����һ�У�8�����أ�
    virtual void PageLeft();				// ����һҳ
    virtual void PageRight();				// ����һҳ
    virtual void HomeLeft();				// ����
    virtual void EndRight();				// ����
	// ����������
    virtual void EnableScrollBar( bool bEnableVertical = true, bool bEnableHorizontal = false );
    // �õ����������
	virtual CScrollBarUI* GetVerticalScrollBar() const;
	// �õ����������
    virtual CScrollBarUI* GetHorizontalScrollBar() const;
	void SetEnabled( bool bEnable );
	void SetInternEnable(bool bEnable );
protected:
	// ��������λ��
    virtual void SetFloatPos( int iIndex );
	// ���������
    virtual void ProcessScrollBar( RECT rc, int cxRequired, int cyRequired );

protected:
	// ͬһ��Ŀؼ������ؼ�������Ӷ���
	// ����canvas�Ϸ��õİ�ť��combox��edit��list�����Ӷ�����ɣ���������tab��
	
	CStdPtrArray m_items;				// �����еĿռ���
    RECT m_rcInset;						// �����ڱ߾� �ͻ���
    int m_iChildPadding;				// �ؼ�����
    bool m_bAutoDestroy;				// �Զ��ݻ��ӿؼ�
    bool m_bDelayedDestroy;				// �ӳٴݻ��ӿؼ�
    bool m_bMouseChildEnabled;			// ������
    bool m_bScrollProcess;				// �Ƿ����������ֹSetPosѭ������

	IDrawEvent*   m_pIDrawEvent;
    CScrollBarUI* m_pVerticalScrollBar;		// �Ƿ�ʹ�ú������
    CScrollBarUI* m_pHorizontalScrollBar;	// �Ƿ�ʹ���ݹ�����
};

/////////////////////////////////////////////////////////////////////////////////////
//	���򲼾ֵ������ؼ�

class DIRECTUI_API CVerticalLayoutUI : public CContainerUI
{
public:
    CVerticalLayoutUI();

    LPCTSTR GetClass() const;					// �õ��ؼ�����
    LPVOID GetInterface( LPCTSTR pstrName );	// �õ��ؼ�ָ��
    UINT GetControlFlags() const;				// �õ��ؼ������ͱ�־

    void SetSepHeight( int iHeight );			// ���÷ָ����߶�
    int GetSepHeight() const;					// ��ȡ�ָ����߶�
    void SetSepImmMode( bool bImmediately );	// ����ˢ��ģʽ ����ˢ�»���ʱˢ��
    bool IsSepImmMode() const;					// ��ȡˢ��ģʽ
    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );// ��������
    void DoEvent( TEventUI& event );			// �����¼�

    void SetPos( RECT rc );
    void DoPostPaint( HDC hDC, const RECT& rcPaint );

    RECT GetThumbRect( bool bUseNew = false ) const;	// ��ȡ��ˢ�µ�����

protected:
    int m_iSepHeight;		// �ָ����߶�
    UINT m_uButtonState;	// �����ؼ�״̬
    POINT ptLastMouse;		// ���λ��
    RECT m_rcNewPos;		// ˢ������
    bool m_bImmMode;		// ����ˢ��ģʽ
};



/////////////////////////////////////////////////////////////////////////////////////
//	���򲼾ֵ������ؼ�

class DIRECTUI_API CHorizontalLayoutUI : public CContainerUI
{
public:
    CHorizontalLayoutUI();

	LPCTSTR GetClass() const;					// �õ��ؼ�����
	LPVOID GetInterface( LPCTSTR pstrName );	// �õ��ؼ�ָ��
	UINT GetControlFlags() const;				// �õ��ؼ������ͱ�־
    
    void SetSepWidth( int iWidth );		    // ���÷ָ������
	int GetSepWidth() const;					// ��ȡ�ָ������
	void SetSepImmMode( bool bImmediately );	// ����ˢ��ģʽ ����ˢ�»���ʱˢ��
	bool IsSepImmMode() const;					// ��ȡˢ��ģʽ
	void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );// ��������
	void DoEvent( TEventUI& event );			// �����¼�

	void SetPos( RECT rc );
	void DoPostPaint( HDC hDC, const RECT& rcPaint );

	RECT GetThumbRect( bool bUseNew = false ) const;	// ��ȡ��ˢ�µ�����

protected:
	int m_iSepWidth;		// �ָ������
	UINT m_uButtonState;	// �����ؼ�״̬
	POINT ptLastMouse;		// ���λ��
	RECT m_rcNewPos;		// ˢ������
	bool m_bImmMode;		// ����ˢ��ģʽ
};

/////////////////////////////////////////////////////////////////////////////////////
//	����ˮƽ����

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
//	ƽ�̲���

class DIRECTUI_API CTileLayoutUI : public CContainerUI
{
public:
    CTileLayoutUI();

    LPCTSTR GetClass() const;				// �õ��ؼ�����
    LPVOID GetInterface( LPCTSTR pstrName );// �õ��ؼ������ͱ�־

    void SetPos( RECT rc );					// �����������������ڿؼ���λ��

    SIZE GetItemSize() const;				// ��ȡ�ؼ����С
    void SetItemSize(SIZE szItem);			// ���ÿؼ����С
    int GetColumns() const;					// ��ȡ��������
    void SetColumns( int nCols );			// ���ò�������

    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );

protected:
    SIZE m_szItem;		// �ؼ����С
    int m_nColumns;		// ��������
};


/////////////////////////////////////////////////////////////////////////////////////
//	��ǩҳ����

class DIRECTUI_API CTabLayoutUI : public CContainerUI
{
public:
    CTabLayoutUI();

    LPCTSTR GetClass() const;				// �õ��ؼ�����
    LPVOID GetInterface( LPCTSTR pstrName );// �õ��ؼ�ָ��

	// ����������ӿؼ����������ѡ����������Ϊ�ǿɼ�
    bool Add( CControlUI* pControl );
	// ���ؼ���ӵ������ؼ��б��ָ��λ�ã���Ϊѡ����Ϊ�ǿɼ�
    bool AddAt( CControlUI* pControl, int iIndex );
	// �Ƴ��ؼ�
    bool Remove( CControlUI* pControl );
	// �Ƴ����пؼ�
    void RemoveAll();
	// �õ���ǰѡ�еĿؼ���ɼ��ؼ���
    int GetCurSel() const;
	// ���ÿؼ���Ϊѡ�������Ϊ�ɼ��ؼ���
    bool SelectItem( int iIndex );

	// ������������ؼ�λ��
    void SetPos( RECT rc );
	// ��������
    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );

protected:
    int m_iCurSel;	// ��ǰѡ�пؼ����ɼ���
};

} // namespace DirectUICore

#endif // __UICONTAINER_H__
