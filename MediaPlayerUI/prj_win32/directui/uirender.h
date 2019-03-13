#ifndef __DUI_RENDER_H__
#define __DUI_RENDER_H__

namespace DirectUICore {
/////////////////////////////////////////////////////////////////////////////////////
// �������棬������dc�ϻ��Ƶ����򣬷�ֹ�ӿؼ����Ƶ����ؼ���ࣨfloat���Կؼ����⣩

class DIRECTUI_API CRenderClip
{
public:
    ~CRenderClip();
    RECT rcItem;
    HDC hDC;
    HRGN hRgn;
    HRGN hOldRgn;
	// ����һ����������, hDC���ھ��, rc����, clip[out]������
    static void GenerateClip( HDC hDC, RECT rc, CRenderClip& clip );
	// ����һ��Բ�Ǽ�������, hDC���ھ��, rc����, width ����Բ�ǻ���, height����Բ�ǻ���, clip[out]������
    static void GenerateRoundClip( HDC hDC, RECT rc, RECT rcItem, int width, int height, CRenderClip& clip );
	// ʹ��������Ծ������Ϊ������, hDC���ھ��, clip������
    static void UseOldClipBegin( HDC hDC, CRenderClip& clip );
	// ʹ�õ�ǰ�ؼ���Ч������Ϊ������, hDC���ھ��, clip������
    static void UseOldClipEnd( HDC hDC, CRenderClip& clip );
};

/////////////////////////////////////////////////////////////////////////////////////
// ��Ⱦ����

class DIRECTUI_API CRenderEngine
{
public:
    static DWORD AdjustColor( DWORD dwColor, short H, short S, short L );
	// ����ͼ����ϸ��cpp
    static TImageInfo* LoadImage( STRINGorID bitmap, LPCTSTR type = NULL, DWORD mask = 0, bool bGray = false );
	static void FreeImage( const TImageInfo* bitmap );
	// ����ͼ����ϸ��cpp
    static void DrawImage( HDC hDC, HBITMAP hBitmap, const RECT& rc, const RECT& rcPaint
                         , const RECT& rcBmpPart, const RECT& rcCorners, bool alphaChannel
						 , BYTE uFade = 255, bool hole = false, bool xtiled = false, bool ytiled = false );
	static void DrawButtonImage( HDC hDC, HBITMAP hBitmap, const RECT& rc, const RECT& rcPaint
		                       , const RECT& rcBmpPart, const RECT& rcCorners, const RECT& rcIcon
							   , bool alphaChannel, BOOL bPicSize = FALSE );
	// ����ʶ�ַ�������ͼ����ϸ��cpp
    static bool DrawImageString( HDC hDC, CPaintManagerUI* pManager, const RECT& rcItem, const RECT& rcPaint
                               , LPCTSTR pStrImage, LPCTSTR pStrModify = NULL);
	static BOOL DrawButtonImageString( HDC hDC, CPaintManagerUI* pManager, const RECT& rcItem, const RECT& rcPaint
		                             , LPCTSTR pStrImage, int nCurState, int nStateCount, BOOL bPicSize = FALSE );
	// ���ܣ����ƾ���
	// ʵ�֣��������Ҫalpha�����SetBkColor() ExtTextOut()
	//		 ���� ����һ�����ش�С��32λDIB
    static void DrawColor( HDC hDC, const RECT& rc, DWORD color );
	// ���ƽ��䣬��ϸ��cpp
    static void DrawGradient( HDC hDC, const RECT& rc, DWORD dwFirst, DWORD dwSecond, bool bVertical, int nSteps );

    // ���º����е���ɫ����alphaֵ��Ч
	// ����ֱ��
    static void DrawLine( HDC hDC, const RECT& rc, int nSize, DWORD dwPenColor );
	// ���ƾ���
    static void DrawRect( HDC hDC, const RECT& rc, int nSize, DWORD dwPenColor );
	// ����Բ�Ǿ���
    static void DrawRoundRect( HDC hDC, const RECT& rc, int width, int height
		                     , int nSize, DWORD dwPenColor );
	// ��������
    static void DrawText( HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText
                        , DWORD dwTextColor, int iFont, UINT uStyle);
	/************************************************************************/
	/*	���� ��	���� "mini-html" ��ʶ�ַ���
		���� ��	hDC			- �豸���;	
				pManager	- ���ƹ�����;	
				rc			- ��������;	
				pstrText	-  "mini-html" ��ʶ�ַ���;
				dwTextColor	- �ַ�������;	
				pLinks		- ��������Ч����������;	
				sLinks		- ��������Ч��������������;
				nLinkRects	- ��������Ч��������������;	
				uStyle		- ���ͣ�ͬDrawText() Format Flags				*/
	/************************************************************************/
    static void DrawHtmlText( HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText 
                            , DWORD dwTextColor, RECT* pLinks, CStdString* sLinks
							, int& nLinkRects, UINT uStyle );
	// ���ܣ�����һ��BMPλͼ
	// ������pManager - ���ƹ�����	pControl - �ؼ����		rc - ��������
    static HBITMAP GenerateBitmap( CPaintManagerUI* pManager, CControlUI* pControl, RECT rc );
};

} // namespace DirectUICore

#endif // __UIRENDER_H__
