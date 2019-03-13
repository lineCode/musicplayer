// Combo�ؼ�
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

    void DoInit();	// ��ʼ��
	// ����tab�л�ͣ�����ԣ����ѡ�������Ϊ-1�����õ�0��Ϊѡ����
    UINT GetControlFlags() const;

    CStdString GetText() const;							// �õ��ı�����
	void SetText( LPCTSTR pstrText );                   // ���ñ༭������---pbl
	UINT_PTR GetTag() const;							// �ڵ���ǰ��ȷ��ǰ��������
	int GetIndexByItemTag( UINT_PTR dwTag ) const;		// �ڵ���ǰ��ȷ��ǰ��������
    void SetEnabled(bool bEnable = true);				// �����Ƿ����
	void SetVisible(bool bVisible);						// �����Ƿ�ɼ�

    CStdString GetDropBoxAttributeList();				// ��ȡ�����������б��ַ���
    void SetDropBoxAttributeList(LPCTSTR pstrList);		// ���������������б��ַ���
    SIZE GetDropBoxSize() const;						// �õ��������С
    void SetDropBoxSize(SIZE szDropBox);				// �����������С

    int GetCurSel() const;								// ��ȡ��ǰѡ����
    bool SelectItem(int iIndex, bool bTakeFocus = false);// ���õ�ǰѡ����

    bool SetItemIndex(CControlUI* pControl, int iIndex);// ����Ŀؼ�ָ���ȡ�����
    bool Add(CControlUI* pControl);						// ����һ��
    bool AddAt(CControlUI* pControl, int iIndex);		// ����һ��б�ָ��λ��
    bool Remove(CControlUI* pControl);					// ����ؼ���ָ���Ƴ�һ��
    bool RemoveAt(int iIndex);							// �Ƴ�ָ����ŵ�һ��
    void RemoveAll();									// �Ƴ�������

	// ���ÿؼ���Ծ��������ڷǻ�Ծ״̬������������δ�������򴴽���������
    bool Activate();

	// ��ȡ/���� �ı���ʽ
	void SetTextStyle( UINT uStyle );
	UINT GetTextStyle() const;

	void LimitText( int nMaxChar = 255 );

    RECT GetTextPadding() const;						// ��ȡ�ı���ؼ���Ե�ļ��
    void SetTextPadding(RECT rc);						// �����ı���ؼ���Ե�ļ��
    LPCTSTR GetNormalImage() const;						// ��ȡ����״̬ͼ
    void SetNormalImage(LPCTSTR pStrImage);				// ��������״̬ͼ
    LPCTSTR GetHotImage() const;						// ��ȡ��Ծ״̬ͼ
    void SetHotImage(LPCTSTR pStrImage);				// ���û�Ծ״̬ͼ
    LPCTSTR GetPushedImage() const;						// ��ȡ����״̬ͼ
    void SetPushedImage(LPCTSTR pStrImage);				// ���ð���״̬ͼ
    LPCTSTR GetFocusedImage() const;					// ��ȡ����״̬ͼ
    void SetFocusedImage(LPCTSTR pStrImage);			// ���ý���״̬ͼ
    LPCTSTR GetDisabledImage() const;					// ��ȡ�ǿ���״̬ͼ
    void SetDisabledImage(LPCTSTR pStrImage);			// ���÷ǿ���״̬ͼ

    TListInfoUI* GetListInfo();							// ��ȡ�б���Ϣ
    void SetItemFont(int index);						// ����������
    void SetItemTextStyle(UINT uStyle);					// �����������С
	RECT GetItemTextPadding() const;					// �õ����ı����
    void SetItemTextPadding(RECT rc);					// �������ı����
	DWORD GetItemTextColor() const;						// ��ȡ���ı���ɫ
    void SetItemTextColor(DWORD dwTextColor);			// �������ı���ɫ
	DWORD GetItemBkColor() const;						// ��ȡ���ɫ
    void SetItemBkColor(DWORD dwBkColor);				// �������ɫ
	LPCTSTR GetItemBkImage() const;						// ��ȡ���ͼ
    void SetItemBkImage(LPCTSTR pStrImage);				// �������ͼ
    bool IsAlternateBk() const;
    void SetAlternateBk(bool bAlternateBk);
	DWORD GetSelectedItemTextColor() const;				// ��ȡѡ��״̬���ı���ɫ
    void SetSelectedItemTextColor(DWORD dwTextColor);	// ����ѡ��״̬���ı���ɫ
	DWORD GetSelectedItemBkColor() const;				// �õ�ѡ�����ɫ
    void SetSelectedItemBkColor(DWORD dwBkColor);		// ����ѡ�����ɫ
	LPCTSTR GetSelectedItemImage() const;				// ��ȡѡ�����ͼ
    void SetSelectedItemImage(LPCTSTR pStrImage);		// ����ѡ�����ͼ
	DWORD GetHotItemTextColor() const;					// ��ȡ���Ծ״̬�ı�ɫ
    void SetHotItemTextColor(DWORD dwTextColor);		// �������Ծ״̬�ı�ɫ
	DWORD GetHotItemBkColor() const;					// ��ȡ���Ծ״̬����ɫ
    void SetHotItemBkColor(DWORD dwBkColor);			// �������Ծ״̬����ɫ
	LPCTSTR GetHotItemImage() const;					// ��ȡ���Ծ״̬ͼ
    void SetHotItemImage(LPCTSTR pStrImage);			// �������Ծ״̬ͼ
	DWORD GetDisabledItemTextColor() const;				// �õ���ǿ���״̬�ı�ɫ
    void SetDisabledItemTextColor(DWORD dwTextColor);	// ������ǿ���״̬�ı�ɫ
	DWORD GetDisabledItemBkColor() const;				// ��ȡ��ǿ���״̬����ɫ
    void SetDisabledItemBkColor(DWORD dwBkColor);		// ������ǿ���״̬����ɫ
	LPCTSTR GetDisabledItemImage() const;				// ��ȡ��ǿ���״̬ͼ
    void SetDisabledItemImage(LPCTSTR pStrImage);		// ������ǿ���״̬ͼ
	DWORD GetItemLineColor() const;						// ��ȡ��߿�ɫ
    void SetItemLineColor(DWORD dwLineColor);			// ������߿�ɫ
    bool IsItemShowHtml();								// ���Ƿ�ʹ����Ƕhtml��ʶ����
    void SetItemShowHtml(bool bShowHtml = true);		// �����Ƿ�ʹ����Ƕhtml��ʶ����
	void SetReadOnly(bool bReadOnly);			// ����ֻ��ģʽ
	bool IsReadOnly() const;					// ��ȡֻ��ģʽ

	void SetDropDown(bool bDropDown);

    SIZE EstimateSize(SIZE szAvailable);				// ����ؼ���С
    void SetPos(RECT rc);								// ���ÿؼ�λ��
    void DoEvent(TEventUI& event);						// �¼�����
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
    
    void DoPaint(HDC hDC, const RECT& rcPaint);
    void PaintText(HDC hDC);
    void PaintStatusImage(HDC hDC);

	int FindString(int nStartAfter, LPCTSTR lpszString);
	bool IsMultiSelectItem()const{return false;}
	void EnableScrollWheel( bool bEnable );
	bool IsEnableScrollWheel() const;

	//������������ʽ
	void SetWndLayoutInset( RECT rcInset );				// ��������
	RECT GetWndLayoutInset() const;
	void SetWndLayoutBkColor(DWORD dwBackColor);			// ���ñ���ɫ
	DWORD GetWndLayoutBkColor() const;
	void SetWndLayoutBorderColor(DWORD dwBorderColor);	// ���ñ߿�ɫ
	DWORD GetWndLayoutBorderColor() const;
	void SetWndLayoutBorderSize(int nSize);		// ���ñ߿��ϸ
	int GetWndLayoutBorderSize() const;

protected:
    CComboWnd* m_pWindow;			// �����򴰿�
	CEditUI* m_pEdit;

    bool m_bReadOnly;				// ֻ����ʽ
    int m_iCurSel;					// ��ǰѡ����
	UINT m_uTextStyle;				// ��ʽ, Ĭ�Ͼ���
    RECT m_rcTextPadding;			// �ı���ؼ���Ե���
    CStdString m_sDropBoxAttributes;// ����������
    SIZE m_szDropBox;				// ���������С
    UINT m_uButtonState;			// �ؼ�״̬
	bool m_bDropDown;				// �Ƿ��Ǵ�Edit��DropDown
	bool m_bEnableScrollWheel;		// �Ƿ�����combo����

	int m_nDropIconWidth;           // DropDown���ͼ��Ŀ��

    CStdString m_sNormalImage;		// ����״̬ͼ
    CStdString m_sHotImage;			// ��Ծ״̬ͼ
    CStdString m_sPushedImage;		// ����״̬ͼ
    CStdString m_sFocusedImage;		// ��ý���״̬ͼ
    CStdString m_sDisabledImage;	// �ǿ���״̬ͼ

	RECT m_rcWndLayoutInset;						// �����������ڱ߾�
	int m_nWndLayoutBorderSize;                  //���������߿��ϸ
	DWORD m_dwWndLayoutBackColor;        //���������򱳾�
	DWORD m_dwWndLayoutBorderColor;      //����������߿���ɫ

    TListInfoUI m_ListInfo;			// ����������б�
};

class DIRECTUI_API CComboWnd : public CWindowWnd
{
public:
	CComboWnd():m_pOwner(nullptr),m_pLayout(nullptr),m_iOldSel(-1),m_iCurHover(-1),m_bUnSelect(false),m_bDisappear(false){}
	// ��ʼ��Combo���ڣ����㴰�ڴ���λ�ã���������
    void Init(CComboUI* pOwner);
    LPCTSTR GetWindowClassName() const;
	// ���ڱ�����ʱ�������Ϣ������
    void OnFinalMessage(HWND hWnd);

	/************************************************************************/
	/*	��Ϣ����
		WM_CREATE:����һ���������������ؼ����������������
		WM_CLOSE:CComboUI::SetManager() CComboUI::SetPos9) CComboUI::SetFocus()
		WM_LBUTTONUP:���ҵ����λ�ã������ǰλ���пؼ����Ҳ��ǹ������ؼ�����������ʧȥ������Ϣ
		WM_KEYDOWN:�ո�� �ָ�ԭ��ѡ�� �س�����������ʧȥ������Ϣ����������CComboUI::DoEvent()����
		WM_MOUSEWHEEL:��CComboUI::DoEvent
		WM_KILLFOCUS:��������WM_CLOSE									    */
	/************************************************************************/
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	// ����λ�ã�Scroll 
    void EnsureVisible(int iIndex);
	// �������������λ��
    void Scroll(int dx, int dy);
	// Ϊ����Ӧɾ����ť
	void SetManager( CPaintManagerUI* pManager ){m_pManager = pManager;}
	virtual bool Notify( TNotifyUI& msg );

#if(_WIN32_WINNT >= 0x0501)
	virtual UINT GetClassStyle() const;
#endif

public:
    CPaintManagerUI m_pm;			// ���ƹ�����
	CPaintManagerUI* m_pManager;    // ��¼����manager��ͨ��������¼���ڷ����ʺ�ɾ����ť���֪ͨ��Ϣ
    CComboUI* m_pOwner;				// ComboUI�ؼ�
    CVerticalLayoutUI* m_pLayout;	// ��������
    int m_iOldSel;					// ��һ��ѡ����
	int m_iCurHover;
	bool m_bUnSelect;               // ��־λ
	bool m_bSelectOld;              // ��־λ
	bool m_bDisappear;              // �Ƿ���Ҫ��������ʧ
         
};

class DIRECTUI_API CComboBoxUI : public CComboUI
{
public:
	CComboBoxUI();
	~CComboBoxUI();
	LPCTSTR GetClass() const;

	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	// ��ȡ/���� ����״̬������ɫ
	void SetTextColor( DWORD dwTextColor, bool bRgb = true );
	DWORD GetTextColor() const;
	void SetFrontImage( LPCTSTR pstrText );            // ���ñ༭�򱳾�ͼ---pbl

	void PaintText(HDC hDC);
	void PaintStatusImage(HDC hDC);

protected:
	DWORD m_dwTextColor;			// ����ʱ������ɫ
	CStdString m_sArrowImage;
	int        m_nArrowWidth;
	CStdString m_sFrontImage;
};

} // namespace DirectUICore

#endif // __UICOMBO_H__
