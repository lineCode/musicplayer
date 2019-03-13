#ifndef __DUI_SCROLLBAR_H__
#define __DUI_SCROLLBAR_H__

namespace DirectUICore 
{

class DIRECTUI_API CScrollBarUI : public CControlUI
{
public:
    CScrollBarUI();

    LPCTSTR GetClass() const;					// ���ؿؼ���
    LPVOID GetInterface( LPCTSTR pstrName );	// �õ�����ָ��

    CContainerUI* GetOwner() const;				// �õ�������ӵ����
    void SetOwner( CContainerUI* pOwner );		// ���ù�����ӵ����

    void SetVisible( bool bVisible = true );	// ���ù������Ƿ�ɼ�
    void SetEnabled( bool bEnable = true );		// ���ù������Ƿ����
    void SetFocus();							// ���ý���

	// ��ȡ/���� ��������������
    bool IsHorizontal();
    void SetHorizontal( bool bHorizontal = true );

	// �õ�/���� ��������Χ
    int GetScrollRange() const;
    void SetScrollRange( int nRange );

	// �õ�/���� ������λ��
    int GetScrollPos() const;
    void SetScrollPos( int nPos );

	// �õ�/���� ������С
    int GetLineSize() const;
    void SetLineSize( int nSize );

	// ��ȡ/���� �ϻ���λ�õİ�ť ��ʾ״̬
    bool GetShowButton1();
    void SetShowButton1(bool bShow);

	// ��ȡ/���� �ϻ���λ�õİ�ť ����״̬ͼ
    LPCTSTR GetButton1NormalImage();
    void SetButton1NormalImage(LPCTSTR pStrImage);

	// ��ȡ/���� �ϻ���λ�õİ�ť ����״̬ͼ
    LPCTSTR GetButton1HotImage();
    void SetButton1HotImage(LPCTSTR pStrImage);

	// ��ȡ/���� �ϻ���λ�õİ�ť ����״̬ͼ
    LPCTSTR GetButton1PushedImage();
    void SetButton1PushedImage(LPCTSTR pStrImage);

	// ��ȡ/���� �ϻ���λ�õİ�ť �ǿ���״̬ͼ
    LPCTSTR GetButton1DisabledImage();
    void SetButton1DisabledImage(LPCTSTR pStrImage);

	// ��ȡ/���� �»���λ�õİ�ť ��ʾ״̬
    bool GetShowButton2();
    void SetShowButton2(bool bShow);

	// ��ȡ/���� �»���λ�õİ�ť ����״̬ͼ
    LPCTSTR GetButton2NormalImage();
    void SetButton2NormalImage(LPCTSTR pStrImage);

	// ��ȡ/���� �»���λ�õİ�ť ����״̬ͼ
    LPCTSTR GetButton2HotImage();
    void SetButton2HotImage(LPCTSTR pStrImage);

	// ��ȡ/���� �»���λ�õİ�ť ����״̬ͼ
    LPCTSTR GetButton2PushedImage();
    void SetButton2PushedImage(LPCTSTR pStrImage);

	// ��ȡ/���� �»���λ�õİ�ť �ǿ���״̬ͼ
    LPCTSTR GetButton2DisabledImage();
    void SetButton2DisabledImage(LPCTSTR pStrImage);

	// ��ȡ/���� ������ ����״̬ͼ
    LPCTSTR GetThumbNormalImage();
    void SetThumbNormalImage(LPCTSTR pStrImage);

	// ��ȡ/���� ������ ����״̬ͼ
    LPCTSTR GetThumbHotImage();
    void SetThumbHotImage(LPCTSTR pStrImage);

	// ��ȡ/���� ������ ����״̬ͼ
    LPCTSTR GetThumbPushedImage();
    void SetThumbPushedImage(LPCTSTR pStrImage);

	// ��ȡ/���� ������ �ǿ���״̬ͼ
    LPCTSTR GetThumbDisabledImage();
    void SetThumbDisabledImage(LPCTSTR pStrImage);

	// ��ȡ/���� �����켣 ����״̬ͼ
    LPCTSTR GetRailNormalImage();
    void SetRailNormalImage(LPCTSTR pStrImage);

	// ��ȡ/���� �����켣 ����״̬ͼ
    LPCTSTR GetRailHotImage();
    void SetRailHotImage(LPCTSTR pStrImage);

	// ��ȡ/���� �����켣 ����״̬ͼ
    LPCTSTR GetRailPushedImage();
    void SetRailPushedImage(LPCTSTR pStrImage);

	// ��ȡ/���� �����켣 �ǿ���״̬ͼ
    LPCTSTR GetRailDisabledImage();
    void SetRailDisabledImage(LPCTSTR pStrImage);

	// ��ȡ/���� ����ͼ ����״̬ͼ
    LPCTSTR GetBkNormalImage();
    void SetBkNormalImage(LPCTSTR pStrImage);

	// ��ȡ/���� ����ͼ ����״̬ͼ
    LPCTSTR GetBkHotImage();
    void SetBkHotImage(LPCTSTR pStrImage);

	// ��ȡ/���� ����ͼ ����״̬ͼ
    LPCTSTR GetBkPushedImage();
    void SetBkPushedImage(LPCTSTR pStrImage);

	// ��ȡ/���� ����ͼ �ǿ���״̬ͼ
    LPCTSTR GetBkDisabledImage();
    void SetBkDisabledImage(LPCTSTR pStrImage);

    void SetPos(RECT rc);			// ���ù�����
    void DoEvent(TEventUI& event);	// �¼�����
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

    void DoPaint(HDC hDC, const RECT& rcPaint);	// ����

    void PaintBk(HDC hDC);			// ���Ʊ���
    void PaintButton1(HDC hDC);		// �����ϻ�����İ�ť
    void PaintButton2(HDC hDC);		// �����»���λ�õİ�ť
    void PaintThumb(HDC hDC);		// ���ƹ�����
    void PaintRail(HDC hDC);		// ���ƹ����켣

protected:

    enum { 
        DEFAULT_SCROLLBAR_SIZE = 16,// ������Ĭ�ϴ�С
        DEFAULT_TIMERID = 10,		// Ĭ�ϼ�ʱ��id
    };

    bool m_bHorizontal;				// ���������ݷ���
    int m_nRange;					// ��Χ
    int m_nScrollPos;				// ������λ��
    int m_nLineSize;				// ����
    CContainerUI* m_pOwner;			// ������ӵ����
    POINT ptLastMouse;				// ���λ��
    int m_nLastScrollPos;			// ������λ��
    int m_nLastScrollOffset;		// ������ƫ���� δʹ��
    int m_nScrollRepeatDelay;		// δʹ��

    CStdString m_sBkNormalImage;
    CStdString m_sBkHotImage;
    CStdString m_sBkPushedImage;
    CStdString m_sBkDisabledImage;

    bool m_bShowButton1;
    RECT m_rcButton1;
    UINT m_uButton1State;
    CStdString m_sButton1NormalImage;
    CStdString m_sButton1HotImage;
    CStdString m_sButton1PushedImage;
    CStdString m_sButton1DisabledImage;

    bool m_bShowButton2;
    RECT m_rcButton2;
    UINT m_uButton2State;
    CStdString m_sButton2NormalImage;
    CStdString m_sButton2HotImage;
    CStdString m_sButton2PushedImage;
    CStdString m_sButton2DisabledImage;

    RECT m_rcThumb;
    UINT m_uThumbState;
    CStdString m_sThumbNormalImage;
    CStdString m_sThumbHotImage;
    CStdString m_sThumbPushedImage;
    CStdString m_sThumbDisabledImage;

    CStdString m_sRailNormalImage;
    CStdString m_sRailHotImage;
    CStdString m_sRailPushedImage;
    CStdString m_sRailDisabledImage;

    CStdString m_sImageModify;
};

}

#endif // __UISCROLLBAR_H__