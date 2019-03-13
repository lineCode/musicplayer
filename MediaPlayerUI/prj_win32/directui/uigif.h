#ifndef UI_GIF_IMAGE_H
#define UI_GIF_IMAGE_H


#include <GdiPlus.h>
using namespace Gdiplus;

namespace DirectUICore {

class DIRECTUI_API CGifImageUI : public CControlUI
{

public:
	CGifImageUI( /*HWND hParentWnd*/ );
	~CGifImageUI();

	virtual LPCTSTR GetClass() const;
	virtual LPVOID GetInterface( LPCTSTR pstrName );

	virtual void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );
	virtual void DoEvent( TEventUI& event );
	virtual void PaintStatusImage( HDC hDC );

public:
//	void SetContorl( CControlUI* pCtrl ){ m_pLoadCtrl = pCtrl; }
	void SetFrameBKColor( DWORD dwColor ){ m_dwBgFrameColor = dwColor; }
// 	void SetPaintRect( CRect rc ){ m_rcPaint = rc; }
// 	CRect GetPaintRect(){ return m_rcPaint; }

	void SetSameScale( bool bSameScale ){ m_bSameScale = bSameScale; }

	bool DrawFrameGIF( HDC hDC );
	bool IsAnimatedGIF() { return m_nFrameCount > 1; }
	bool Start();
	bool Load( LPCTSTR szFileName );
	bool Load( HGLOBAL hGlobal, DWORD dwSize );
	bool Load( LPCTSTR szResourceName, LPCTSTR szResourceType, HINSTANCE hInstance );
	bool Stop();

private:
	void Destroy();

	bool TestForAnimatedGIF();
//	bool PrepareDC(int nWidth, int nHeight);

protected:
	HWND					m_hParentWnd;
	UINT					m_nFrameCount;
	UINT					m_nFramePosition;
	Gdiplus::PropertyItem*	m_pPropertyItem;
	CRect                   m_rcPaint;
	CPoint					m_pt;
	HDC                     m_hMemDC;
	HBITMAP					m_hBitmap;
	HBITMAP					m_hOldBitmap;
	int		                m_iGifWidth;
	int		                m_iGifHeight;
	int		                m_iDelayTime;
	int		                m_iPrevDelayTime;
	Image*                  m_pImage;
	bool                    m_bSameScale;  // 是否需要等比缩放
	DWORD					m_dwBgFrameColor;	// 背景色						
};

} // namespace DirectUICore

#endif 