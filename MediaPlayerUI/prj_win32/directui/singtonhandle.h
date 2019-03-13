/******************************************************************************
	模块名      : skinui
	文件名      : singtonhandle.h
	相关文件    : singtonhandle.cpp
	文件实现功能: 一些供绘图用的公共实例
	作者        : 周艳华
	版本        : 1.0
	-------------------------------------------------------------------------------
	修改记录:
	日  期      版本        修改人      修改内容
	2010/09/21  1.0         周艳华        创建
******************************************************************************/
#ifndef SINGTON_HANDLE_H
#define SINGTON_HANDLE_H

#include "duiimage.h"

namespace DirectUICore 
{

// 安全释放Image指针
#define IMAGE_SAFE_DELETE( pImage ) if ( pImage != NULL ) { delete pImage; pImage = NULL; }

// 载入图片类型
#define IMAGE_TYPE   _T("PNG")


//判断
#define CHECK_SKINWND_VALID 	ASSERT( m_pSkinWnd );\
				if (m_pSkinWnd == NULL) \
				{\
				return;\
				}

class DIRECTUI_API CDefaultFont 
{
public:
	CDefaultFont( void);
	virtual ~CDefaultFont( void );
	static CDefaultFont& Instance();
	HFONT GetDefaultTextFont();
	HFONT GetDefaultTitleFont();

private:
	HFONT m_tDefaultTextFont;    // 9号常规微软雅黑
	HFONT m_tDefaultTitleFont;   // 10号粗体微软雅黑
};

class DIRECTUI_API CImageUtility
{
public:
	static CImageUtility& Instance();
	static CDuiImage * LoadCImage( UINT nID, LPCTSTR lpszType, HINSTANCE hInstance = NULL );
	
	// 因为CImage或者CDuiImage在对带透明区域的图片的缩放时是有问题的，透明区域会变黑，所以
	// 要处理带透明区域的缩放要使用gdi+中的Image类，by zzx 2015/11/02
	static Image * LoadImage( UINT nID, LPCTSTR szResourceType, HINSTANCE hInstance = NULL );
};

class DIRECTUI_API CDuiLogPrint
{
public:
	static bool s_bLogPirntOn;
	void SwitchPrint()
	{
		s_bLogPirntOn = !s_bLogPirntOn;
	}
};

}

#endif
