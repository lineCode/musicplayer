
/******************************************************************************
	ģ����      : skinshadow
	�ļ���      : skinshadow.h
	����ļ�    : skinshadow.cpp
	�ļ�ʵ�ֹ���: ʵ�ִ��ڵ���Ӱ
	����        : 
	�汾        : 1.0
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��      �汾        �޸���      �޸�����
	2011/11/14  1.0         ���ٱ�       
******************************************************************************/
#ifndef UI_SHADOW_H
#define UI_SHADOW_H

#include "duiimage.h"

#pragma warning(push)
#pragma warning(disable:4786)
#include "map"
#pragma warning(pop) 

namespace DirectUICore
{

class DIRECTUI_API CSkinShadow
{
public:
	CSkinShadow(void);
	virtual ~CSkinShadow(void);

protected:
	//ʵ�����������ע�ᴮ����ʹ�������
	static HINSTANCE s_hInstance;
	HWND m_hWnd;
	HWND m_hParent;
#pragma warning(push)
#pragma warning(disable:4786)
		static std::map<HWND, CSkinShadow *> s_Shadowmap;
#pragma warning(pop) 
		
	LONG m_OriParentProc;	// Original WndProc of parent window
	BYTE m_Status;

	enum ShadowStatus
	{
		SS_ENABLED = 1,				// Shadow is enabled, if not, the following one is always false
		SS_VISABLE = 1 << 1,		// Shadow window is visible
		SS_PARENTVISIBLE = 1<< 2,	// Parent window is visible, if not, the above one is always false
	};

	signed char m_nEdgeSize;    // Shadow window size, relative to parent window size
	LPARAM m_WndSize;			// Restore last parent window size, 
								// used to determine the update strategy when parent window is resized
	bool m_bUpdate;				// Set this to true if the shadow should not be update until next WM_PAINT is received

	static CDuiImage m_Image;

//	HINSTANCE m_hInstance;
public:
	static bool Initialize(HINSTANCE hInstance);
	static void SetImage( UINT nID, LPCTSTR lpszType, HINSTANCE hInstance );
	void   Create( HWND hParentWnd );
	bool   SetSize(int NewSize = 0);

	// Redraw, resize and move the shadow
	// called when window resized or shadow properties changed, but not only moved without resizing
	void Update(HWND hParent);

	void ShowShadow(BOOL bShow, HWND hParent);

	// Show or hide the shadow, depending on the enabled status stored in m_Status
	void Show(HWND hParent); 

protected:
	//static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK ParentProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
}

#endif
