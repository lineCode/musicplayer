/******************************************************************************
	ģ����      : skinui
	�ļ���      : singtonhandle.h
	����ļ�    : singtonhandle.cpp
	�ļ�ʵ�ֹ���: һЩ����ͼ�õĹ���ʵ��
	����        : ���޻�
	�汾        : 1.0
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��      �汾        �޸���      �޸�����
	2010/09/21  1.0         ���޻�        ����
******************************************************************************/
#ifndef SINGTON_HANDLE_H
#define SINGTON_HANDLE_H

#include "duiimage.h"

namespace DirectUICore 
{

// ��ȫ�ͷ�Imageָ��
#define IMAGE_SAFE_DELETE( pImage ) if ( pImage != NULL ) { delete pImage; pImage = NULL; }

// ����ͼƬ����
#define IMAGE_TYPE   _T("PNG")


//�ж�
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
	HFONT m_tDefaultTextFont;    // 9�ų���΢���ź�
	HFONT m_tDefaultTitleFont;   // 10�Ŵ���΢���ź�
};

class DIRECTUI_API CImageUtility
{
public:
	static CImageUtility& Instance();
	static CDuiImage * LoadCImage( UINT nID, LPCTSTR lpszType, HINSTANCE hInstance = NULL );
	
	// ��ΪCImage����CDuiImage�ڶԴ�͸�������ͼƬ������ʱ��������ģ�͸��������ڣ�����
	// Ҫ�����͸�����������Ҫʹ��gdi+�е�Image�࣬by zzx 2015/11/02
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
