/******************************************************************************
	ģ����      : mediaplay
	�ļ���      : MainApp.cpp
	����ļ�    : 
	�ļ�ʵ�ֹ���: ����ִ����ʼ��ڣ�������ʾ������
	����        : ���Ŀ�
	�汾        : 
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��      �汾        �޸���      �޸�����
	2017/3/1                ���Ŀ�        ����
******************************************************************************/

#include"stdafx.h"
#include"MainWnd.h"


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//ΪCPaintManagerUI����ʵ�����
	CPaintManagerUI::SetInstance(hInstance);

	//������Դ·��Ϊʵ��·��
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

	//ΪCSkinShadow����ʵ�����
	CSkinShadow::Initialize( hInstance );
	
	//���ñ�����ӰͼƬ
	CSkinShadow::SetImage( IDB_SHDAW_BK, _T("png"), hInstance );

	//��ʼ��com��(Ӧ�ó������com�⺯������CoGetMalloc���ڴ���亯����֮ǰ�����ʼ��com��)
	HRESULT Hr = ::CoInitialize(NULL);
    if (FAILED(Hr)) 
	{
		return 0;
	}

	//ʵ���������������
	CMainWnd* m_pwnd = new CMainWnd(IDR_XML_MAIN_FRAM); 
	if( m_pwnd == NULL )
	{
		return 0;
	}

	//����������
	m_pwnd->Create( NULL, _T("�ٶ�����"), UI_WNDSTYLE_DIALOG
		, WS_EX_DLGMODALFRAME|WS_EX_LAYERED, 0, 0,1000,660);

	//�����ھ���
	m_pwnd->CenterWindow();

	//��ʾ������
	m_pwnd->ShowWindow(true);

	CPaintManagerUI::MessageLoop();

	::CoUninitialize();

	return 0;
}