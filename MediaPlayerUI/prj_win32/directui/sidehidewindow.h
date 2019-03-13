/******************************************************************************
	ģ����      : �����ڲش�����
	�ļ���      : SideHideWindow.h
	����ļ�    : SideHideWindow.cpp
	�ļ�ʵ�ֹ���: ʵ�������ڵ���������
	����        : ������
	�汾        : 1.0
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��      �汾        �޸���      �޸�����
	2011/11/10  1.0         ������        ����
	2013/11/05  2.0         ��Ǯ��        DUI
******************************************************************************/
#ifndef SIDE_HIDE_WINDOW_H
#define SIDE_HIDE_WINDOW_H

namespace DirectUICore {

// ��������������ģʽ
enum EmSideHideMode
{
    SIDEHIDE_NONE   = 0,  // ������
    SIDEHIDE_TOP    = 1,  // ��������
    SIDEHIDE_LEFT   = 2,  // ��������
    SIDEHIDE_RIGHT  = 3,  // ��������
	SIDEHIDE_BOTTOM = 4,  // ��������
};
enum EmTaskBarSideMode
{
	TASKBAR_BOTTOM  = 0,   //���·�
	TASKBAR_TOP     = 1,   //���ϱ�
	TASKBAR_LEFT    = 2,   //�����
	TASKBAR_RIGHT   = 3,   //���ұ�
	TASKBAR_HIDE    = 4,   //����������״̬
};

//�����
class DIRECTUI_API CSideHideWindow : public CAppWindow
{
public:
	CSideHideWindow( STRINGorID strUI, unsigned int dwTransparent = 255, bool bDeleteSelf = true );
	virtual ~CSideHideWindow( void );

public:
	// Ĭ�ϻص�����
	virtual LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual LRESULT OnNcHitTest( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );

	// bEnable-TRUE��ʹ�������ڲأ�bEnable-FALSE��ȡ�������ڲ�
	void EnableSideHide( BOOL bEnable ); 
	// bCancelTop-TRUE��ȡ���ö���bCancelTop-FALSE����ȡ���ö�
	void IsCancelTop( BOOL bCancelTop ){ m_bCancelTop = bCancelTop; }
	EmSideHideMode GetSideHideMode();    // ��ȡ�����ڲ�ģʽ
 
	// ע�⣺��ʹ�������ڲغ�ȡ�������ڲ�֮���л�ʱ���ڵ���EnableSideHide()�ӿڵĺ����У���ڴ����ø�
	// ����(����FALSE����)�����ڴ����øú���(����TRUE����)����֤�л�ʱ������Ϊ����ʧȥ����״̬ʱ�����
	// �ڲ��쳣, 2011/12/22 (�˷����Ƚ�ǣǿ���д��Ż�)
	// QQ�����ŵȲ����������쳣����Ϊ���ǲ���Ҫ��ʹ�������ڲغ�ȡ�������ڲ�֮���л�
	void EnableInactiveWndHide( BOOL bEnable );
    void UpdateTaskBarSideMode(); //��ȡ������λ��
	CRect GetWorkArea(); //��ȡ������λ��
	EmTaskBarSideMode GetTaskBarSideMode(){ return m_emTaskBarSideMode; }
	void SetEdgeHeight( int nEdgeHeight ){ m_nEdgeHeight = nEdgeHeight; }
	int GetEdgeHeight() { return m_nEdgeHeight; }
	void SetEdgeWidth( int nEdgeWidth ){ m_nEdgeWidth = nEdgeWidth; }
	BOOL IsHide() { return m_bHide; }
	void SetHide(bool bHide) { m_bHide = bHide; }

protected:
	virtual void DoShowWnd();  // ��ʾ����
	virtual void DoHideWnd();  // �ڲش���

private:
	void FixMoving(LPRECT lpRect ); // ���ݴ����϶�ʱ�����λ�����ж��Ƿ�Ҫ�����ڲ�
	BOOL HasRunningMenu();
	
private:
	int  m_nEdgeHeight;   // ��Ե�߶�(�����������õ�)
	int  m_nEdgeWidth;    // ��Ե���(����������������õ�) 

	EmSideHideMode m_emSideHideMode;  // ����������ģʽ

	EmTaskBarSideMode m_emTaskBarSideMode; //��������λ��
	CRect m_rcWorkArea;

	BOOL m_bEnableSideHide;      // ʹ��/ȡ�������ڲر�ʶ(TRUE-ʹ�������ڲأ�FALSE-ȡ�������ڲ�)
	BOOL m_bCancelTop;           // �Ƿ�ȡ���ö���ʶ(TRUE-ȡ���ö���FALSE-��ȡ���ö�)
	BOOL m_bMouseDetectTimerSet; // ����ⶨʱ���Ƿ���(�������Ƿ�����������)
	BOOL m_bHide;                // �����Ƿ��ڲ�
	BOOL m_bMainWndSizeChanged;  // ���ڴ�С�Ƿ�ı䣬����Ѿ��ı���Ҫ������ǰ�Ĵ��ڸ߶ȼ�¼��m_dwOldMainWndHeight������
	BOOL m_bEnableInactiveWndHide; // ʹ�ܴ�����ʧȥ����״̬ʱ���ڲض��������������ʹ�������ڲغ�ȡ�������ڲ�֮���л�ʱ���쳣

	int m_nOldMainWndHeight;     // �������������ǰ�Ĵ��ڸ߶�(�˳���������״̬�󣬴���Ҫ���ԭ����С)
};

}
#endif