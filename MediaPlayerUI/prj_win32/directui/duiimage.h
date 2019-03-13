/******************************************************************************
	模块名      ： duilib
	文件名      ： CDuiImage.h
	相关文件    ： CDuiImage.cpp
	文件实现功能：要去除duilib对minimfc中CImage的依赖，使duilib完全独立，不依赖于其他的库。
	             由于CSkinShadow和CImageUtility等类中会用到CImage，所以将MFC中的CImage的
				 .h和.cpp文件放进来，重命名为CDuiImage，和CImage区别开（即使使用duilib的工
				 程是MFC工程，不会和MFC中CImage冲突）。该类是从VS2010中拿出来的。
	作者        ： 张振兴
	版本        ： 1.0.0.0
	-------------------------------------------------------------------------------
	修改记录:
	日  期      版本        修改人      修改内容
	2015/01/13  1.0        张振兴        创建
******************************************************************************/

// This is a part of the Active Template Library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

// 从MFC源码中剥离出来的CDuiImage类

#ifndef _CDUIIMAGE_CLASS_FROM_MFC_H_
#define _CDUIIMAGE_CLASS_FROM_MFC_H_


#include <atldef.h>
#include <atlbase.h>
//#include <atlstr.h>  // 不能包含该头文件，包含该头文件将会使用ATL的CString，会和本库中的CString冲突
#include <atlsimpcoll.h>
#include <atltypes.h>

#ifndef _ATL_NO_PRAGMA_WARNINGS
#pragma warning (push)
#pragma warning(disable : 4820)	// padding added after member
#endif //!_ATL_NO_PRAGMA_WARNINGS

#pragma warning( push, 3 )
#pragma push_macro("new")
#undef new
#include <gdiplus.h>
#pragma pop_macro("new")
#pragma warning( pop )

#include <shlwapi.h>

#ifndef _ATL_NO_DEFAULT_LIBS
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "gdiplus.lib")
#if WINVER >= 0x0500
#pragma comment(lib, "msimg32.lib")
#endif  // WINVER >= 0x0500
#endif  // !_ATL_NO_DEFAULT_LIBS

#pragma pack(push, _ATL_PACKING)

//namespace ATL
//{




const int CDUIIMAGE_DC_CACHE_SIZE = 4;


class DIRECTUI_API CDuiImage
{
private:
	class CDCCache
	{
	public:
		CDCCache() throw();
		~CDCCache() throw();

		HDC GetDC() throw();
		void ReleaseDC(_In_ HDC) throw();

	private:
		HDC m_ahDCs[CDUIIMAGE_DC_CACHE_SIZE];
	};

	class CInitGDIPlus
	{
	public:
		CInitGDIPlus() throw();
		~CInitGDIPlus() throw();

		bool Init() throw();
		void ReleaseGDIPlus() throw();
		void IncreaseCImageCount() throw();
		void DecreaseCImageCount() throw();

	private:
		ULONG_PTR m_dwToken;
		CRITICAL_SECTION m_sect;
		LONG m_nCImageObjects;
		DWORD m_dwLastError;
	};

public:
	static const DWORD createAlphaChannel = 0x01;

	static const DWORD excludeGIF = 0x01;
	static const DWORD excludeBMP = 0x02;
	static const DWORD excludeEMF = 0x04;
	static const DWORD excludeWMF = 0x08;
	static const DWORD excludeJPEG = 0x10;
	static const DWORD excludePNG = 0x20;
	static const DWORD excludeTIFF = 0x40;
	static const DWORD excludeIcon = 0x80;
	static const DWORD excludeOther = 0x80000000;
	static const DWORD excludeDefaultLoad = 0;
	static const DWORD excludeDefaultSave = excludeIcon|excludeEMF|excludeWMF;
	static const DWORD excludeValid = 0x800000ff;

	enum DIBOrientation
	{
		DIBOR_DEFAULT,
		DIBOR_TOPDOWN,
		DIBOR_BOTTOMUP
	};

public:
	CDuiImage() throw();
	virtual ~CDuiImage() throw();

	operator HBITMAP() const throw();
#if WINVER >= 0x0500
	BOOL AlphaBlend(
		_In_ HDC hDestDC,
		_In_ int xDest,
		_In_ int yDest,
		_In_ BYTE bSrcAlpha = 0xff,
		_In_ BYTE bBlendOp = AC_SRC_OVER) const throw();
	BOOL AlphaBlend(
		_In_ HDC hDestDC,
		_In_ const POINT& pointDest,
		_In_ BYTE bSrcAlpha = 0xff,
		_In_ BYTE bBlendOp = AC_SRC_OVER) const throw();
	BOOL AlphaBlend(
		_In_ HDC hDestDC,
		_In_ int xDest,
		_In_ int yDest,
		_In_ int nDestWidth,
		_In_ int nDestHeight,
		_In_ int xSrc,
		_In_ int ySrc,
		_In_ int nSrcWidth,
		_In_ int nSrcHeight,
		_In_ BYTE bSrcAlpha = 0xff,
		_In_ BYTE bBlendOp = AC_SRC_OVER) const throw();
	BOOL AlphaBlend(
		_In_ HDC hDestDC,
		_In_ const RECT& rectDest,
		_In_ const RECT& rectSrc,
		_In_ BYTE bSrcAlpha = 0xff,
		_In_ BYTE bBlendOp = AC_SRC_OVER) const throw();
#endif  // WINVER >= 0x0500
	void Attach(
		_In_ HBITMAP hBitmap,
		_In_ DIBOrientation eOrientation = DIBOR_DEFAULT) throw();
	BOOL BitBlt(
		_In_ HDC hDestDC,
		_In_ int xDest,
		_In_ int yDest,
		_In_ DWORD dwROP = SRCCOPY) const throw();
	BOOL BitBlt(
		_In_ HDC hDestDC,
		_In_ const POINT& pointDest,
		_In_ DWORD dwROP = SRCCOPY) const throw();
	BOOL BitBlt(
		_In_ HDC hDestDC,
		_In_ int xDest,
		_In_ int yDest,
		_In_ int nDestWidth,
		_In_ int nDestHeight,
		_In_ int xSrc,
		_In_ int ySrc,
		_In_ DWORD dwROP = SRCCOPY) const throw();
	BOOL BitBlt(
		_In_ HDC hDestDC,
		_In_ const RECT& rectDest,
		_In_ const POINT& pointSrc,
		_In_ DWORD dwROP = SRCCOPY) const throw();
	BOOL Create(
		_In_ int nWidth,
		_In_ int nHeight,
		_In_ int nBPP,
		_In_ DWORD dwFlags = 0) throw();
	BOOL CreateEx(
		_In_ int nWidth,
		_In_ int nHeight,
		_In_ int nBPP,
		_In_ DWORD eCompression,
		_In_opt_count_c_(3) const DWORD* pdwBitmasks = NULL,
		_In_ DWORD dwFlags = 0) throw();
	void Destroy() throw();
	HBITMAP Detach() throw();
	BOOL Draw(
		_In_ HDC hDestDC,
		_In_ int xDest,
		_In_ int yDest,
		_In_ int nDestWidth,
		_In_ int nDestHeight,
		_In_ int xSrc,
		_In_ int ySrc,
		_In_ int nSrcWidth,
		_In_ int nSrcHeight) const throw();
	BOOL Draw(
		_In_ HDC hDestDC,
		_In_ const RECT& rectDest,
		_In_ const RECT& rectSrc) const throw();
	BOOL Draw(
		_In_ HDC hDestDC,
		_In_ int xDest,
		_In_ int yDest) const throw();
	BOOL Draw(
		_In_ HDC hDestDC,
		_In_ const POINT& pointDest) const throw();
	BOOL Draw(
		_In_ HDC hDestDC,
		_In_ int xDest,
		_In_ int yDest,
		_In_ int nDestWidth,
		_In_ int nDestHeight ) const throw();
	BOOL Draw(
		_In_ HDC hDestDC,
		_In_ const RECT& rectDest) const throw();
	BOOL Draw(
		_In_ HDC hDestDC,
		_In_ const RECT& rectDest,
		_In_ Gdiplus::InterpolationMode interpolationMode) const throw();
	const void* GetBits() const throw();
	void* GetBits() throw();
	int GetBPP() const throw();
	void GetColorTable(
		_In_ UINT iFirstColor,
		_In_ UINT nColors,
		_In_ RGBQUAD* prgbColors) const throw();
	HDC GetDC() const throw();
// 	static HRESULT GetExporterFilterString(
// 		_Inout_ CSimpleString& strExporters,
// 		_Inout_ CSimpleArray< GUID >& aguidFileTypes,
// 		_In_opt_z_ LPCTSTR pszAllFilesDescription = NULL,
// 		_In_ DWORD dwExclude = excludeDefaultSave,
// 		_In_ TCHAR chSeparator = _T( '|' ) );
// 	static HRESULT GetImporterFilterString(
// 		_Inout_ CSimpleString& strImporters,
// 		_Inout_ CSimpleArray< GUID >& aguidFileTypes,
// 		_In_opt_z_ LPCTSTR pszAllFilesDescription = NULL,
// 		_In_ DWORD dwExclude = excludeDefaultLoad,
// 		_In_ TCHAR chSeparator = _T( '|' ) );
	int GetHeight() const throw();
	int GetMaxColorTableEntries() const throw();
	int GetPitch() const throw();
	const void* GetPixelAddress(
		_In_ int x,
		_In_ int y) const throw();
	void* GetPixelAddress(
		_In_ int x,
		_In_ int y) throw();
	COLORREF GetPixel(
		_In_ int x,
		_In_ int y) const throw();
	LONG GetTransparentColor() const throw();
	int GetWidth() const throw();
	bool IsDIBSection() const throw();
	bool IsIndexed() const throw();
	bool IsNull() const throw();
	HRESULT Load(_In_z_ LPCTSTR pszFileName) throw();
	HRESULT Load(_Inout_ IStream* pStream) throw();
	void LoadFromResource(
		_In_opt_ HINSTANCE hInstance,
		_In_z_ LPCTSTR pszResourceName) throw();
	void LoadFromResource(
		_In_opt_ HINSTANCE hInstance,
		_In_ UINT nIDResource) throw();
	BOOL MaskBlt(
		_In_ HDC hDestDC,
		_In_ int xDest,
		_In_ int yDest,
		_In_ int nDestWidth,
		_In_ int nDestHeight,
		_In_ int xSrc,
		_In_ int ySrc,
		_In_ HBITMAP hbmMask,
		_In_ int xMask,
		_In_ int yMask,
		_In_ DWORD dwROP = SRCCOPY) const throw();
	BOOL MaskBlt(
		_In_ HDC hDestDC,
		_In_ const RECT& rectDest,
		_In_ const POINT& pointSrc,
		_In_ HBITMAP hbmMask,
		_In_ const POINT& pointMask,
		_In_ DWORD dwROP = SRCCOPY) const throw();
	BOOL MaskBlt(
		_In_ HDC hDestDC,
		_In_ int xDest,
		_In_ int yDest,
		_In_ HBITMAP hbmMask,
		_In_ DWORD dwROP = SRCCOPY) const throw();
	BOOL MaskBlt(
		_In_ HDC hDestDC,
		_In_ const POINT& pointDest,
		_In_ HBITMAP hbmMask,
		_In_ DWORD dwROP = SRCCOPY) const throw();
	BOOL PlgBlt(
		_In_ HDC hDestDC,
		_In_count_c_(3) const POINT* pPoints,
		_In_opt_ HBITMAP hbmMask = NULL) const throw();
	BOOL PlgBlt(
		_In_ HDC hDestDC,
		_In_count_c_(3) const POINT* pPoints,
		_In_ int xSrc,
		_In_ int ySrc,
		_In_ int nSrcWidth,
		_In_ int nSrcHeight,
		_In_opt_ HBITMAP hbmMask = NULL,
		_In_ int xMask = 0,
		_In_ int yMask = 0) const throw();
	BOOL PlgBlt(
		_In_ HDC hDestDC,
		_In_count_c_(3) const POINT* pPoints,
		_In_ const RECT& rectSrc,
		_In_opt_ HBITMAP hbmMask = NULL,
		_In_ const POINT& pointMask = CPoint( 0, 0 )) const throw();
	void ReleaseDC() const throw();
	HRESULT Save(
		_Inout_ IStream* pStream,
		_In_ REFGUID guidFileType) const throw();
	HRESULT Save(
		_In_z_ LPCTSTR pszFileName,
		_In_ REFGUID guidFileType = GUID_NULL) const throw();
	void SetColorTable(
		_In_ UINT iFirstColor,
		_In_ UINT nColors,
		_In_ const RGBQUAD* prgbColors) throw();
	void SetPixel(
		_In_ int x,
		_In_ int y,
		_In_ COLORREF color) throw();
	void SetPixelIndexed(
		_In_ int x,
		_In_ int y,
		_In_ int iIndex) throw();
	void SetPixelRGB(
		_In_ int x,
		_In_ int y,
		_In_ BYTE r,
		_In_ BYTE g,
		_In_ BYTE b) throw();
	void SetHasAlphaChannel(_In_ bool bHasAlphaChannel) throw();
	LONG SetTransparentColor(_In_ LONG iTransparentColor) throw();
	COLORREF SetTransparentColor(_In_ COLORREF clrTransparentColor) throw();
	BOOL StretchBlt(
		_In_ HDC hDestDC,
		_In_ int xDest,
		_In_ int yDest,
		_In_ int nDestWidth,
		_In_ int nDestHeight,
		_In_ DWORD dwROP = SRCCOPY) const throw();
	BOOL StretchBlt(
		_In_ HDC hDestDC,
		_In_ const RECT& rectDest,
		_In_ DWORD dwROP = SRCCOPY) const throw();
	BOOL StretchBlt(
		_In_ HDC hDestDC,
		_In_ int xDest,
		_In_ int yDest,
		_In_ int nDestWidth,
		_In_ int nDestHeight,
		_In_ int xSrc,
		_In_ int ySrc,
		_In_ int nSrcWidth,
		_In_ int nSrcHeight,
		_In_ DWORD dwROP = SRCCOPY) const throw();
	BOOL StretchBlt(
		_In_ HDC hDestDC,
		_In_ const RECT& rectDest,
		_In_ const RECT& rectSrc,
		_In_ DWORD dwROP = SRCCOPY) const throw();
#if WINVER >= 0x0500
	BOOL TransparentBlt(
		_In_ HDC hDestDC,
		_In_ int xDest,
		_In_ int yDest,
		_In_ int nDestWidth,
		_In_ int nDestHeight,
		_In_ UINT crTransparent = CLR_INVALID) const throw();
	BOOL TransparentBlt(
		_In_ HDC hDestDC,
		_In_ const RECT& rectDest,
		_In_ UINT crTransparent = CLR_INVALID) const throw();
	BOOL TransparentBlt(
		_In_ HDC hDestDC,
		_In_ int xDest,
		_In_ int yDest,
		_In_ int nDestWidth,
		_In_ int nDestHeight,
		_In_ int xSrc,
		_In_ int ySrc,
		_In_ int nSrcWidth,
		_In_ int nSrcHeight,
		_In_ UINT crTransparent = CLR_INVALID) const throw();
	BOOL TransparentBlt(
		_In_ HDC hDestDC,
		_In_ const RECT& rectDest,
		_In_ const RECT& rectSrc,
		_In_ UINT crTransparent = CLR_INVALID) const throw();
#endif  // WINVER >= 0x0500

	static BOOL IsTransparencySupported() throw();

private:
	HBITMAP m_hBitmap;
	void* m_pBits;
	int m_nWidth;
	int m_nHeight;
	int m_nPitch;
	int m_nBPP;
	bool m_bIsDIBSection;
	bool m_bHasAlphaChannel;
	LONG m_iTransparentColor;
	COLORREF m_clrTransparentColor;

	static CInitGDIPlus s_initGDIPlus;

public:
	inline static void ReleaseGDIPlus();

// Implementation
private:
	static CLSID FindCodecForExtension(
		_In_z_ LPCTSTR pszExtension,
		_In_count_(nCodecs) const Gdiplus::ImageCodecInfo* pCodecs,
		_In_ UINT nCodecs);
	static CLSID FindCodecForFileType(
		_In_ REFGUID guidFileType,
		_In_count_(nCodecs) const Gdiplus::ImageCodecInfo* pCodecs,
		_In_ UINT nCodecs);
// 	static void BuildCodecFilterString(
// 		_In_count_(nCodecs) const Gdiplus::ImageCodecInfo* pCodecs,
// 		_In_ UINT nCodecs,
// 		_Inout_ CSimpleString& strFilter,
// 		_Inout_ CSimpleArray< GUID >& aguidFileTypes,
// 		_In_opt_z_ LPCTSTR pszAllFilesDescription,
// 		_In_ DWORD dwExclude,
// 		_In_ TCHAR chSeparator);

	static bool ShouldExcludeFormat(
		_In_ REFGUID guidFileType,
		_In_ DWORD dwExclude) throw();
	void UpdateBitmapInfo(_In_ DIBOrientation eOrientation);
	HRESULT CreateFromGdiplusBitmap(_Inout_ Gdiplus::Bitmap& bmSrc) throw();

	static bool InitGDIPlus() throw();

	static int ComputePitch(
		_In_ int nWidth,
		_In_ int nBPP)
	{
		return( (((nWidth*nBPP)+31)/32)*4 );
	}
	COLORREF GetTransparentRGB() const;

private:
	mutable HDC m_hDC;
	mutable int m_nDCRefCount;
	mutable HBITMAP m_hOldBitmap;

	static CDCCache s_cache;
};


//};  // namespace ATL

#pragma pack(pop)

#ifndef _ATL_NO_PRAGMA_WARNINGS
#pragma warning (pop)
#endif

#endif  // _CIMAGE_CLASS_FROM_MFC_H_
