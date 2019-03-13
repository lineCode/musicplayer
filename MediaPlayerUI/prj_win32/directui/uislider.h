// »¬¶¯Ìõ¿Ø¼þ
#ifndef __DUI_SLIDER_H__
#define __DUI_SLIDER_H__

namespace DirectUICore 
{

class DIRECTUI_API CSliderUI : public CProgressUI
{
public:
    CSliderUI();

    LPCTSTR GetClass() const;
    UINT GetControlFlags() const;
    LPVOID GetInterface(LPCTSTR pstrName);

    void SetEnabled( bool bEnable = true );

    int GetChangeStep();
    void SetChangeStep( int step );

    void SetThumbSize( SIZE szXY );
    RECT GetThumbRect() const;

    LPCTSTR GetThumbImage() const;
    void SetThumbImage( LPCTSTR pStrImage );
    LPCTSTR GetThumbHotImage() const;
    void SetThumbHotImage( LPCTSTR pStrImage );
    LPCTSTR GetThumbPushedImage() const;
    void SetThumbPushedImage( LPCTSTR pStrImage );
	LPCTSTR GetThumbDisableImage() const;
	void SetThumbDisableImage( LPCTSTR pStrImage );

    void DoEvent( TEventUI& event );
    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );
    void PaintStatusImage( HDC hDC );

protected:
    SIZE m_szThumb;
    UINT m_uButtonState;
    int m_nStep;

    CStdString m_sThumbImage;
    CStdString m_sThumbHotImage;
    CStdString m_sThumbPushedImage;
	CStdString m_sThumbDisableImage;

    CStdString m_sImageModify;
};

}

#endif // __UISLIDER_H__