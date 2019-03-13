#ifndef __DUI_RENDER_H__
#define __DUI_RENDER_H__

namespace DirectUICore {
/////////////////////////////////////////////////////////////////////////////////////
// 区域引擎，设置在dc上绘制的区域，防止子控件绘制到父控件外侧（float属性控件除外）

class DIRECTUI_API CRenderClip
{
public:
    ~CRenderClip();
    RECT rcItem;
    HDC hDC;
    HRGN hRgn;
    HRGN hOldRgn;
	// 产生一个剪切区域, hDC窗口句柄, rc区域, clip[out]剪切区
    static void GenerateClip( HDC hDC, RECT rc, CRenderClip& clip );
	// 产生一个圆角剪切区域, hDC窗口句柄, rc区域, width 横向圆角弧度, height纵向圆角弧度, clip[out]剪切区
    static void GenerateRoundClip( HDC hDC, RECT rc, RECT rcItem, int width, int height, CRenderClip& clip );
	// 使用整个活跃区域作为剪切区, hDC窗口句柄, clip剪切区
    static void UseOldClipBegin( HDC hDC, CRenderClip& clip );
	// 使用当前控件有效区域作为剪切区, hDC窗口句柄, clip剪切区
    static void UseOldClipEnd( HDC hDC, CRenderClip& clip );
};

/////////////////////////////////////////////////////////////////////////////////////
// 渲染引擎

class DIRECTUI_API CRenderEngine
{
public:
    static DWORD AdjustColor( DWORD dwColor, short H, short S, short L );
	// 加载图像，详细见cpp
    static TImageInfo* LoadImage( STRINGorID bitmap, LPCTSTR type = NULL, DWORD mask = 0, bool bGray = false );
	static void FreeImage( const TImageInfo* bitmap );
	// 绘制图像，详细见cpp
    static void DrawImage( HDC hDC, HBITMAP hBitmap, const RECT& rc, const RECT& rcPaint
                         , const RECT& rcBmpPart, const RECT& rcCorners, bool alphaChannel
						 , BYTE uFade = 255, bool hole = false, bool xtiled = false, bool ytiled = false );
	static void DrawButtonImage( HDC hDC, HBITMAP hBitmap, const RECT& rc, const RECT& rcPaint
		                       , const RECT& rcBmpPart, const RECT& rcCorners, const RECT& rcIcon
							   , bool alphaChannel, BOOL bPicSize = FALSE );
	// 按标识字符串绘制图像，详细见cpp
    static bool DrawImageString( HDC hDC, CPaintManagerUI* pManager, const RECT& rcItem, const RECT& rcPaint
                               , LPCTSTR pStrImage, LPCTSTR pStrModify = NULL);
	static BOOL DrawButtonImageString( HDC hDC, CPaintManagerUI* pManager, const RECT& rcItem, const RECT& rcPaint
		                             , LPCTSTR pStrImage, int nCurState, int nStateCount, BOOL bPicSize = FALSE );
	// 功能：绘制矩形
	// 实现：如果不需要alpha混合则SetBkColor() ExtTextOut()
	//		 否则 创建一个像素大小的32位DIB
    static void DrawColor( HDC hDC, const RECT& rc, DWORD color );
	// 绘制渐变，详细见cpp
    static void DrawGradient( HDC hDC, const RECT& rc, DWORD dwFirst, DWORD dwSecond, bool bVertical, int nSteps );

    // 以下函数中的颜色参数alpha值无效
	// 绘制直线
    static void DrawLine( HDC hDC, const RECT& rc, int nSize, DWORD dwPenColor );
	// 绘制矩形
    static void DrawRect( HDC hDC, const RECT& rc, int nSize, DWORD dwPenColor );
	// 绘制圆角矩形
    static void DrawRoundRect( HDC hDC, const RECT& rc, int width, int height
		                     , int nSize, DWORD dwPenColor );
	// 绘制文字
    static void DrawText( HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText
                        , DWORD dwTextColor, int iFont, UINT uStyle);
	/************************************************************************/
	/*	功能 ：	绘制 "mini-html" 标识字符串
		参数 ：	hDC			- 设备句柄;	
				pManager	- 绘制管理者;	
				rc			- 对象区域;	
				pstrText	-  "mini-html" 标识字符串;
				dwTextColor	- 字符串类型;	
				pLinks		- 产生链接效果的区域组;	
				sLinks		- 产生链接效果的区域组数量;
				nLinkRects	- 产生链接效果的区域组数量;	
				uStyle		- 类型，同DrawText() Format Flags				*/
	/************************************************************************/
    static void DrawHtmlText( HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText 
                            , DWORD dwTextColor, RECT* pLinks, CStdString* sLinks
							, int& nLinkRects, UINT uStyle );
	// 功能：产生一个BMP位图
	// 参数：pManager - 绘制管理者	pControl - 控件句柄		rc - 对象区域
    static HBITMAP GenerateBitmap( CPaintManagerUI* pManager, CControlUI* pControl, RECT rc );
};

} // namespace DirectUICore

#endif // __UIRENDER_H__
