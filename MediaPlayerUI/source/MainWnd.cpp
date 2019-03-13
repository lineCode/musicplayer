/******************************************************************************
	ģ����      : mediaplay
	�ļ���      : MainWnd.cpp
	����ļ�    : MainWnd.h
	�ļ�ʵ�ֹ���: ʵ����������ʾ�Լ����ֲ����߼�
	����        : ���Ŀ�
	�汾        : 
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��      �汾        �޸���      �޸�����
	2017/3/1              ���Ŀ�        ����
******************************************************************************/



#include "MainWnd.h"
#include "define.h"

//��̬��Ա�����汳���ؼ���ʼ��
CVerticalLayoutUI *CMainWnd::m_pBkCtrl = NULL;

BEGIN_UI_MSG_MAP( CMainWnd, CAppWindow )
	MSG_CLICK( _T("CloseBtn"), OnClose )
	MSG_CLICK( _T("LeftLabBtn"), OnLeftLabBtn )
	MSG_CLICK( _T("RightLabBtn"), OnRightLabBtn )
	MSG_CLICK( _T("LeftTabBtn"), OnLeftTabBtn )
	MSG_CLICK( _T("RightTabBtn"), OnRightTabBtn )
	MSG_CLICK( _T("PlayBtn"), OnPlayBtn )
	MSG_CLICK( _T("PlayPrevBtn"), OnPlayPrevBtn )
	MSG_CLICK( _T("PlayNextBtn"), OnPlayNextBtn )
	MSG_CLICK( _T("LogoBtn"), OnLogoBtn )
	MSG_CLICK( _T("MyMessageBtn"), OnMyMessageBtn )
	MSG_CLICK( _T("SettingBtn"), OnSettingBtn )
	MSG_CLICK( _T("SkinChangeBtn"), OnSkinChangeBtn )
	MSG_CLICK( _T("MinBtn"), OnMinBtn )
	MSG_CLICK( _T("VoliceBtn"), OnVoliceBtn )
	MSG_CLICK( _T("ImportMusBtn"), OnImportMusBtn )
	MSG_CLICK( _T("CycleLisBtn"), OnCycleLisBtn )
	MSG_CLICK( _T("PlayQueueBtn"), OnPlayQueueBtn )
	MSG_CLICK( _T("CleanTextBtn"), OnCleanTextBtn )
	
	MSG_BUTTONDOWN( _T("CreateMusicListBtn"), OnCreateMusicListBtn )
	MSG_BUTTONDOWN( _T("CreateMusicListAddBtn"), OnCreateMusicListAddBtn )
	
	MSG_VALUECHANGED( _T("MusPlyTimSli"), OnMusPlyTimSli )
	MSG_VALUECHANGED( _T("VoliceSli"), OnVoliceSli )

	MSG_SELECT_CHANGED( _T("MusiLibrOpt"), OnMusiLibrOpt )
	MSG_SELECT_CHANGED( _T("MusiRankOpt"), OnMusiRankOpt )
	MSG_SELECT_CHANGED( _T("PlyListOpt"), OnPlyListOpt )
	MSG_SELECT_CHANGED( _T("BoarCastStaOpt"), OnBoarCastStaOpt )
	MSG_SELECT_CHANGED( _T("SingerOpt"), OnSingerOpt )
	MSG_SELECT_CHANGED( _T("ClaFicOpt"), OnClaFicOpt )
	MSG_SELECT_CHANGED( _T("LiveOpt"), OnLiveOpt )
	MSG_SELECT_CHANGED( _T("OnlineMusicOpt"), OnOnlineMusicOpt )
	MSG_SELECT_CHANGED( _T("ActiveOpt"), OnActiveOpt )
	MSG_SELECT_CHANGED( _T("TryListnMusicOpt"), OnTryListnMusicOpt )
	MSG_SELECT_CHANGED( _T("LocOpt"), OnLocOpt )
	MSG_SELECT_CHANGED( _T("DowLoaOpt"), OnDowLoaOpt )

	MSG_ITEM_CLICK( _T("RandPlayMod_MenuE"), OnRandPlayMod_MenuE )
	MSG_ITEM_CLICK( _T("LoopPlayMod_MenuE"), OnLoopPlayMod_MenuE )
	MSG_ITEM_CLICK( _T("SinglePlayMod_MenuE"), OnSinglePlayMod_MenuE )
	MSG_ITEM_CLICK( _T("LisOrderPlayMod_MenuE"), OnLisOrderPlayMod_MenuE )
	MSG_ITEM_CLICK( _T("ExitMenu"), OnClose )
	
	MSG_SETFOCUS( _T("SearchEdt"), OnSearchEditSetFoc )

END_UI_MSG_MAP()

CMainWnd::CMainWnd( STRINGorID strUI, unsigned int dwTransparent, bool bDeleteSelf)
:CAppWindow( strUI, dwTransparent, bDeleteSelf)
,m_bIsNoVol(FALSE)			//�Ƿ��Ǿ���
,m_dwTotalTime(0)				//��¼������ʱ��
,m_strLisPath(_T(""))		//��¼��ǰ�����б���ļ���·��
,m_strPlyName(_T(""))		//��¼��ǰ�����б���ļ���
,m_emLoopMod(emLoopPlay)	//��¼���ֵĲ���ģʽ{�����˳�򣬵�����ѭ��}
,m_pCMediPly(NULL)			//ý�岥����ָ�룬����ý�岥�Ź��ܵ�ʵ��
,m_pPlayListDlg(NULL)	    //�û���¼�Ի�����ָ��,���캯����ʱʵ����
,m_pUseLogDlg(NULL)	        //�û���¼�Ի�����ָ��
,m_pSkiChaDlg(NULL)     	//�����Ի�����ָ��
,m_myCrelisEleCount(0)  	//���������Խ��赥�����Խ��赥������
,m_pBtnPlay(NULL)
,m_pBtnVolice(NULL)
,m_pBtnCurTim(NULL)
,m_pBtnLeftTab(NULL)
,m_pBtnRightTab(NULL)
,m_pBtnCreateMusicList(NULL)
,m_pBtnCycleLis(NULL)
,m_pBtnCleanText(NULL)
,m_pEdt(NULL)
,m_pEdtSearch(NULL)
,m_pLisMusicList(NULL)
,m_pLisLocMusic(NULL)
,m_pBtnLeftLab(NULL)
,m_pBtnRightLab(NULL)
,m_pTabRecom(NULL)
,m_pTabShoufa(NULL)
,m_pTabMusiList(NULL)
,m_pTabMusiLibr(NULL)
,m_pWebBrowser(NULL)
,m_pSliVolice(NULL)
,m_pSliMusPlyTim(NULL)	//���ֽ�����
,m_pLabPlyCount(NULL)
,m_pVerMain(NULL)
,m_pLisConEle(NULL)
{

}

CMainWnd::~CMainWnd(void)
{
	if(m_pCMediPly)
	{
		delete m_pCMediPly;
		m_pCMediPly = NULL;
	}
}

/*=========================================================================
	������		: CMainWnd::OnClose
	����		: ��Ӧ�رհ�ť��Ϣ���˳�������
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg ��Ϣ�ṹ��
	����ֵ		: bool �����˷���true������false
=========================================================================*/
bool CMainWnd::OnClose(TNotifyUI& msg)
{
	PostQuitMessage(0);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnCreateMusicListBtn
	����		: ��Ӧ�Խ��赥��ť����¼�
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnCreateMusicListBtn( TNotifyUI& msg )
{
	//�Խ��赥�İ�ť״̬����
	SetBtnState(m_pBtnCreateMusicList->GetName());
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnCreateMusicListAddBtn
	����		: ��Ӧ�Խ��赥����б���Ϣ
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnCreateMusicListAddBtn(TNotifyUI& msg)
{
	//���Խ��赥�б�
	SetListElementShow();

	//���һ���Խ��ĸ赥�б���
	AddListContainer();
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnLeftLabBtn
	����		: ���ֿ��Ƽ�ҳ���һ���󷭹���
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnLeftLabBtn(TNotifyUI& msg)
{
	m_pTabRecom->SelectItem(m_pTabRecom->GetCurSel()-1);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnRightLabBtn
	����		: ���ֿ��Ƽ�ҳ���һ���ҷ�����
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnRightLabBtn(TNotifyUI& msg)
{
	m_pTabRecom->SelectItem(m_pTabRecom->GetCurSel()+1);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnLeftTabBtn
	����		: ���ֿ��Ƽ�ҳ���׷����󷭹���
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnLeftTabBtn(TNotifyUI& msg)
{
	m_pTabShoufa->SelectItem(m_pTabShoufa->GetCurSel()-1);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnRightTabBtn
	����		: ���ֿ��Ƽ�ҳ���׷����ҷ�����
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnRightTabBtn(TNotifyUI& msg)
{
	m_pTabShoufa->SelectItem(m_pTabShoufa->GetCurSel()+1);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnPlayBtn
	����		: ����ͣ״̬�����ּ�������
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnPlayBtn(TNotifyUI& msg)
{
	StartPlay(_T(""));
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnPlayPrevBtn
	����		: ����ǰһ�׸���
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnPlayPrevBtn(TNotifyUI& msg)
{
	CStdString strPreName = _T("");
	CString strUserData = _T("");
	strUserData=m_pLisLocMusic->GetUserData();
	int count = m_pLisLocMusic->GetCount();
	int preSelected = _ttoi(strUserData);
	if(count <= 0)
		return true;

	CListTextElementUI *p = NULL;
	if(preSelected == 0 || preSelected>count)    //������б�ĵ�һ��
	{
		p = (CListTextElementUI*)m_pLisLocMusic->GetItemAt(count-1);
		strPreName = GetLocMusPath();
		strPreName += "\\";
		strPreName += p->GetText(1);

		//���ñ����б��и���Ϊѡ�в���״̬
		m_pLisLocMusic->SelectItem( count-1, true);
	}
	else
	{
		p = (CListTextElementUI*)m_pLisLocMusic->GetItemAt(preSelected-1);
		strPreName = GetLocMusPath();
		strPreName += "\\";
		strPreName += p->GetText(1);
		m_pLisLocMusic->SelectItem( preSelected-1, true);
	}
	m_pCMediPly->Stop();
	m_strPlyName = p->GetText(1);

	//���ò����б��и���Ϊѡ��״̬
	m_pPlayListDlg->m_pLisPlay->SelectItem( m_pLisLocMusic->GetCurSel(), true);

	strUserData.Format( _T("%d"), m_pLisLocMusic->GetCurSel());
	m_pLisLocMusic->SetUserData(strUserData);

	StartPlay((CString)strPreName);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnPlayNextBtn
	����		: ������һ�׸���
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnPlayNextBtn(TNotifyUI& msg)
{
	CStdString strPreName = _T("");
	CString strUserData = _T("");
	strUserData = m_pLisLocMusic->GetUserData();
	int count = m_pLisLocMusic->GetCount();
	int preSelected = _ttoi(strUserData);
	if(count <= 0)
		return true;

	CListTextElementUI *p = NULL;
	if(preSelected >= count-1)			       //������б�����һ��
	{
		p = (CListTextElementUI*)m_pLisLocMusic->GetItemAt(0);
		strPreName = GetLocMusPath();
		strPreName += "\\";
		strPreName += p->GetText(1);
		m_pLisLocMusic->SelectItem( 0, true);  //���ñ����б��и���Ϊѡ�в���״̬
	}
	else
	{
		p = (CListTextElementUI*)m_pLisLocMusic->GetItemAt(preSelected+1);
		strPreName = GetLocMusPath();
		strPreName += "\\";
		strPreName += p->GetText(1);

		//���ñ����б��и���Ϊѡ�в���״̬
		m_pLisLocMusic->SelectItem( preSelected+1, true);			
	}
	m_pCMediPly->Stop();		
	m_strPlyName = p->GetText(1);

	//���ò����б��и���Ϊѡ��״̬
	m_pPlayListDlg->m_pLisPlay->SelectItem( m_pLisLocMusic->GetCurSel(), true);

	strUserData.Format( _T("%d"), m_pLisLocMusic->GetCurSel());
	m_pLisLocMusic->SetUserData(strUserData);

	StartPlay((CString)strPreName);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnLogoBtn
	����		: ��ӦLogo����¼�
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnLogoBtn(TNotifyUI& msg)
{
	//����ϵͳ�˵���������ʾ
	CreateMenuByXml( IDR_XML_SYS_MENU, msg.ptMouse);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnMyMessageBtn
	����		: �ҵ���Ϣ��ť����¼�
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnMyMessageBtn(TNotifyUI& msg)
{
	//�����û���¼�Ի�����ʾ
	CreateUserLoginDlg();
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnSettingBtn
	����		: ��Ӧ���ð�ť�����Ϣ
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnSettingBtn(TNotifyUI& msg)
{
	//����ϵͳ�˵���������ʾ
	CreateMenuByXml( IDR_XML_SYS_MENU, msg.ptMouse);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnSkinChangeBtn
	����		: ��Ӧ����Ƥ����ť����¼�
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnSkinChangeBtn(TNotifyUI& msg)
{
	//���������Ի�����ʾ
	CreateSkinChangeDlg(CPoint(msg.ptMouse));
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnMinBtn
	����		: ��Ӧ��С����ť����¼�
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnMinBtn(TNotifyUI& msg)
{
	//��С������
	::ShowWindow(m_hWnd, SW_MINIMIZE);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnVoliceBtn
	����		: ��Ӧ������ť����¼�
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnVoliceBtn(TNotifyUI& msg)
{
	if(m_bIsNoVol)
	{
		m_bIsNoVol = FALSE;
		//��ȡ������������λ�ã�0-100����������ý�岥������
		m_pCMediPly->Volume(GetVoiceSliVal());					
		m_pBtnVolice->SetNormalImage(BTN_MINIBIG_OPEN_STATE_PNG);
	}
	else
	{
		m_bIsNoVol = TRUE;
		m_pCMediPly->Volume(0); //����
		m_pBtnVolice->SetNormalImage(BTN_MINIBIG_CLOSE_STATE_PNG);
	}
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnImportMusBtn
	����		: ��Ӧ�������ְ�ť����¼����򿪵������ֵĶԻ���
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnImportMusBtn(TNotifyUI& msg)
{
	//�򿪵������ֶԻ���
	OnOpenFileDlg();
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnCycleLisBtn
	����		: ��Ӧѭ���б�ť����¼�����ʾ�˵�
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnCycleLisBtn(TNotifyUI& msg)
{
	//����ѭ��ģʽ�˵���������ʾ
	CreaLoopModeMenu();
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnPlayQueueBtn
	����		: ��Ӧѭ���б�ť����¼�����ʾ�˵�
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnPlayQueueBtn(TNotifyUI& msg)						
{
	if(!m_pPlayListDlg->IsWindowVisible())
	{
		//��������λ�ã��Ա�֤�����б�Ի�������ȷ��λ����ʾ
		POINT posLT = { msg.pSender->GetPos().left, msg.pSender->GetPos().top};	
		POINT posRB = { msg.pSender->GetPos().right, msg.pSender->GetPos().bottom}; 
		posLT.x = posLT.x-300;
		posLT.y = posLT.y-445;
		posRB.x = posRB.x+42;
		posRB.y = posRB.y-50;
		ClientToScreen( m_hWnd, &posLT);
		ClientToScreen( m_hWnd, &posRB);
		RECT rect = { posLT.x, posLT.y, posRB.x, posRB.y};
		m_pPlayListDlg->MoveWindow( &rect, FALSE);
		m_pPlayListDlg->ShowWindow(true);
	}
	else
	{
		m_pPlayListDlg->ShowWindow(!m_pPlayListDlg->IsWindowVisible());
	}
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnCleanTextBtn
	����		: ��Ӧ�����������ť�㲢�������������
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnCleanTextBtn(TNotifyUI& msg)		
{
	m_pEdtSearch->SetText(_T(""));			//���������������	
	m_pBtnCleanText->SetVisible(false);		//����ť����Ϊ���ɼ�
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnMusPlyTimSli
	����		: ��Ӧ���ֲ��Ž������ĵ���¼�
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnMusPlyTimSli(TNotifyUI& msg)
{
	if(!m_pCMediPly->IsOpen())
	{
		//�������ֲ��Ž�������ֵ
		m_pSliMusPlyTim->SetValue(m_pSliMusPlyTim->GetMinValue());
		return true;
	}
	if( !m_pCMediPly->IsPlaying() && m_pCMediPly->IsOpen())
	{
		if(!m_pCMediPly->Play())
			return true;
	}

	//���ò��Ű�ť��״̬
	SetPlayBtnIsPlay(TRUE);

	//ָ�����ִ����ֽ�������λ�ÿ�ʼ����
	m_pCMediPly->SeekPosPly(m_pSliMusPlyTim->GetValue());
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnVoliceSli
	����		: ��Ӧ�����������ĵ���¼�
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnVoliceSli(TNotifyUI& msg)
{
	int Vol = GetVoiceSliVal();
	if(Vol == 0)
	{
		//��������ť�ؼ�ͼƬ����Ϊ����״̬ͼƬ��������
		m_pBtnVolice->SetNormalImage(BTN_MINIBIG_CLOSE_STATE_PNG);
		m_bIsNoVol = TRUE;
	}
	else
	{
		m_bIsNoVol = FALSE;

		//���ò������ֵ�������С
		m_pCMediPly->Volume(GetVoiceSliVal());

		//��������ť�ؼ�ͼƬ����Ϊ����״̬ͼƬ
		m_pBtnVolice->SetNormalImage(BTN_MINIBIG_OPEN_STATE_PNG);
	}
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnMusiLibrOpt
	����		: ��Ӧ���ֿ�ҳ���Ƽ������¼�������ʾ�Ƽ�ҳҳ��
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnMusiLibrOpt(TNotifyUI& msg)
{
	m_pTabMusiLibr->SelectItem(0);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnMusiRankOpt
	����		: ��Ӧ���ֿ�ҳ��������¼�������ʾ��ҳҳ��
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnMusiRankOpt(TNotifyUI& msg)
{
	m_pTabMusiLibr->SelectItem(1);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnPlyListOpt
	����		: ��Ӧ���ֿ�ҳ��赥�����¼�������ʾ�赥ҳҳ��
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnPlyListOpt(TNotifyUI& msg)
{
	m_pTabMusiLibr->SelectItem(2);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnBoarCastStaOpt
	����		: ��Ӧ���ֿ�ҳ���̨�����¼�������ʾ��̨ҳҳ��
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnBoarCastStaOpt(TNotifyUI& msg)
{
	m_pTabMusiLibr->SelectItem(3);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnSingerOpt
	����		: ��Ӧ���ֿ�ҳ����������¼�������ʾ����ҳҳ��
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnSingerOpt(TNotifyUI& msg)
{
	m_pTabMusiLibr->SelectItem(4);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnClaFicOpt
	����		: ��Ӧ���ֿ�ҳ����������¼�������ʾ����ҳҳ��
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnClaFicOpt(TNotifyUI& msg)
{
	m_pTabMusiLibr->SelectItem(5);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnLiveOpt
	����		: ��Ӧ���ֿ�ҳ��ֱ�������¼�������ʾֱ��ҳҳ��
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnLiveOpt(TNotifyUI& msg)
{
	m_pTabMusiLibr->SelectItem(6);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnOnlineMusicOpt
	����		: ��Ӧ���ֿ������¼�������ʾ���ֿ�ҳ��
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnOnlineMusicOpt(TNotifyUI& msg)	
{
	m_pTabMusiList->SelectItem(0);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnActiveOpt
	����		: ��Ӧ��̬�����¼�������ʾ��̬ҳҳ��
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnActiveOpt(TNotifyUI& msg)
{
	m_pTabMusiList->SelectItem(1);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnTryListnMusicOpt
	����		: ��Ӧ�����б������¼�������ʾ�����б�ҳ��
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnTryListnMusicOpt(TNotifyUI& msg)
{
	m_pTabMusiList->SelectItem(2);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnLocOpt
	����		: ��Ӧ�������������¼�������ʾ��������ҳ��
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnLocOpt(TNotifyUI& msg)	
{
	m_pTabMusiList->SelectItem(3);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnDowLoaOpt
	����		: ��Ӧ�������������¼�������ʾ��������ҳ��
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnDowLoaOpt(TNotifyUI& msg)
{
	m_pTabMusiList->SelectItem(4);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnRandPlayMod_MenuE
	����		: ��Ӧ����ģʽ�˵���������¼��������ò���ģʽΪ�������ģʽ
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnRandPlayMod_MenuE(TNotifyUI& msg)
{
	SetPlayMode(emRandomPlay);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnLoopPlayMod_MenuE
	����		: ��Ӧ����ģʽ�˵�ѭ�������¼��������ò���ģʽΪѭ������ģʽ
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnLoopPlayMod_MenuE(TNotifyUI& msg)
{
	SetPlayMode(emLoopPlay);		//�����б�ѭ������ģʽ
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnSinglePlayMod_MenuE
	����		: ��Ӧ����ģʽ�˵�����ѭ���¼��������ò���ģʽΪ����ѭ��ģʽ
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnSinglePlayMod_MenuE(TNotifyUI& msg)
{
	SetPlayMode(emSinglePlay);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnLisOrderPlayMod_MenuE
	����		: ��Ӧ����ģʽ�˵��б�ѭ���¼��������ò���ģʽΪ�б�ѭ��ģʽ
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnLisOrderPlayMod_MenuE(TNotifyUI& msg)
{
	SetPlayMode(emOrderPlay);
	return true;
}

/*=========================================================================
	������		: CMainWnd::OnSearchEditSetFoc
	����		: ��Ӧ�������ý����¼�����������������ְ�ť��Ϊ�ɼ�״̬
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: msg  ��Ϣ�ṹ��
	����ֵ		: bool ������ɷ���true������false
=========================================================================*/
bool CMainWnd::OnSearchEditSetFoc(TNotifyUI& msg)
{
	m_pBtnCleanText->SetVisible();
	return true;
}

UINT CMainWnd::GetClassStyle(void) const	
{
	//���������û����ᵼ��List�б�˫����Ч
	return CS_DBLCLKS;
}

/*=========================================================================
	������		: CMainWnd::CreateMenuByXml
	����		: ����ϵͳ�˵�
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: xml xml�����ļ���ȫ·��, pos�����õĲ˵���ʾ��λ��
	����ֵ		: 
=========================================================================*/
void CMainWnd::CreateMenuByXml( STRINGorID xml, CPoint pos) 
{
	CMenuWnd* pMenu = NULL;
	::ClientToScreen( m_hWnd, &pos);
	pMenu = new CMenuWnd( xml, _T("xml"), &m_pm);
	pMenu->TrackPopupMenu( eMenuAlignment_Left|eMenuAlignment_Top, pos, m_hWnd);
}

void CMainWnd::Init(void)
{
	//CButtonUI
	m_pBtnCreateMusicList = static_cast<CButtonUI*>(m_pm.FindControl(_T("CreateMusicListBtn")));
	ASSERT(m_pBtnCreateMusicList);

	m_pBtnLeftLab         = static_cast<CButtonUI*>(m_pm.FindControl(_T("LeftLabBtn")));
	ASSERT(m_pBtnLeftLab);

	m_pBtnRightLab        = static_cast<CButtonUI*>(m_pm.FindControl(_T("RightLabBtn")));
	ASSERT(m_pBtnRightLab);

	m_pBtnLeftTab         = static_cast<CButtonUI*>(m_pm.FindControl(_T("LeftTabBtn")));
	ASSERT(m_pBtnLeftTab);

	m_pBtnRightTab        = static_cast<CButtonUI*>(m_pm.FindControl(_T("RightTabBtn")));
	ASSERT(m_pBtnRightTab);

	m_pBtnPlay            = static_cast<CButtonUI*>(m_pm.FindControl(_T("PlayBtn")));
	ASSERT(m_pBtnPlay);

	m_pBtnVolice          = static_cast<CButtonUI*>(m_pm.FindControl(_T("VoliceBtn")));
	ASSERT(m_pBtnVolice);

	m_pBtnCurTim          = static_cast<CButtonUI*>(m_pm.FindControl(_T("CurTimBtn")));
	ASSERT(m_pBtnCurTim);

	m_pBtnCycleLis        = static_cast<CButtonUI*>(m_pm.FindControl(_T("CycleLisBtn")));
	ASSERT(m_pBtnCycleLis);

	m_pBtnCleanText       = static_cast<CButtonUI*>(m_pm.FindControl(_T("CleanTextBtn")));
	m_pBtnCleanText->SetVisible(false);
	ASSERT(m_pBtnCleanText);

	//CListUI
	m_pLisMusicList = static_cast<CListUI*>(m_pm.FindControl(_T("MusicList")));
	ASSERT(m_pLisMusicList);

	m_pLisLocMusic = static_cast<CListUI*>(m_pm.FindControl(_T("LocMusLis")));
	ASSERT(m_pLisLocMusic);

	//CTabLayoutUI
	m_pTabMusiLibr = static_cast<CTabLayoutUI*>(m_pm.FindControl(_T("MusiLibrTab")));
	ASSERT(m_pTabMusiLibr);

	m_pTabRecom    = static_cast<CTabLayoutUI*>(m_pm.FindControl(_T("RecomTab")));
	ASSERT(m_pTabRecom);

	m_pTabShoufa   = static_cast<CTabLayoutUI*>(m_pm.FindControl(_T("ShoufaTab")));
	ASSERT(m_pTabShoufa);

	m_pTabMusiList = static_cast<CTabLayoutUI*>(m_pm.FindControl(_T("MusiListTab")));
	ASSERT(m_pTabMusiList);

	//CWebBrowserUI
	m_pWebBrowser = static_cast<CWebBrowserUI*>(m_pm.FindControl(_T("FmWeb")));
	ASSERT(m_pWebBrowser);

	//CSliderUI
	m_pSliMusPlyTim = static_cast<CSliderUI*>(m_pm.FindControl(_T("MusPlyTimSli")));
	ASSERT(m_pSliMusPlyTim);
	m_pSliVolice    = static_cast<CSliderUI*>(m_pm.FindControl(_T("VoliceSli")));
	ASSERT(m_pSliVolice);

	//CLabelUI
	m_pLabPlyCount = static_cast<CLabelUI*>(m_pm.FindControl(_T("PlyCountLab")));
	ASSERT(m_pLabPlyCount);

	//CEditUI
	m_pEdtSearch = static_cast<CEditUI*>(m_pm.FindControl(_T("SearchEdt")));
	ASSERT(m_pEdtSearch);

	//CVerticalLayoutUI
	m_pBkCtrl = static_cast<CVerticalLayoutUI*>(m_pm.FindControl(_T("MainVer")));
	ASSERT(m_pBkCtrl);

	//����������ʵ����
	m_pCMediPly = new CMediPly(this);

	//���������б�Ի��򣬳�ʼ����
	CreatePlayListDlg();
}

void CMainWnd::Prepare(void)
{
	SetIcon(IDI_APPICON);
}

LPCTSTR CMainWnd::GetWindowClassName(void) const 
{
	return _T("MediaPlayer");
}

LRESULT CMainWnd::OnSysCommand( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	return  CAppWindow::OnSysCommand( uMsg, wParam, lParam,bHandled );
}

LRESULT CMainWnd::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return CAppWindow::HandleMessage(uMsg,wParam,lParam);
}

LRESULT CMainWnd::OnNcHitTest( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt = {0};
	pt.x = GET_X_LPARAM(lParam);
	pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient( m_hWnd, &pt);
	RECT rcCaption = {0};
	GetClientRect(&rcCaption);
	rcCaption.bottom = m_pm.GetCaptionRect().bottom;
	if(::PtInRect( &rcCaption, pt))
	{
		CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));

		//���˱������ϵĿؼ�
		if( pControl && _tcsicmp( pControl->GetClass(), _T("EditUI")) != 0 
			&& _tcsicmp( pControl->GetClass(), _T("OptionUI")) != 0 
			&& _tcsicmp( pControl->GetClass(), _T("ButtonUI")) != 0)
		{
			return HTCAPTION;
		}
	}
	return HTCLIENT;/*1*/
}

bool CMainWnd::Notify( TNotifyUI& msg )
{
	if(msg.sType == _T("itemactivate"))
	{
		CString strPath(GetLocMusPath());
		CString strUserData = _T("");
		int selectItem = m_pLisLocMusic->GetCurSel();
		CListTextElementUI* p = (CListTextElementUI*)m_pLisLocMusic->GetItemAt(selectItem);
		if(p != NULL)
		{
			//ֹͣ���ֲ���
			m_pCMediPly->Stop();

			strPath += _T("\\");
			strPath += p->GetText(1);

			//m_strPlyName˽�г�Ա��¼��ǰ���ŵ�ý���ļ���
			m_strPlyName = p->GetText(1);

			m_pPlayListDlg->m_pLisPlay->SelectItem( m_pLisLocMusic->GetCurSel(), true);

			//�ѱ��������б������ڲ��ŵ���������±�ת����CString����
			strUserData.Format( _T("%d"), selectItem);

			m_pLisLocMusic->SetUserData(strUserData);	//�����û�����
			StartPlay(strPath);
			return true;
		}	
	}

	else if(msg.sType == NOTIFY_KILLFOCUS)	//�Ƴ�����֪ͨ
	{	
		CStdString str = msg.pSender->GetName();
		if(msg.pSender->GetName() == _T("MyLisEditId"))
		{	
			//����Խ��赥�б���Option�ؼ�ѡ��
			AddListOption();
		}
	}
	else if(msg.sType == NOTIFY_MOUSEENTER)	//�����뷶Χ�¼�֪ͨ
	{
		//���ֿ�ҳ���е����ҷ���ť�ؼ�����ʾ������
		if(PtInRect( &(m_pTabRecom->GetPos()), msg.ptMouse))
		{
			m_pBtnLeftLab->SetVisible(true);
			m_pBtnRightLab->SetVisible(true);
		}
		else
		{
			m_pBtnLeftLab->SetVisible(false);
			m_pBtnRightLab->SetVisible(false);
		}
		if(PtInRect( &(m_pTabShoufa->GetPos()), msg.ptMouse))
		{
			m_pBtnLeftTab->SetVisible(true);
			m_pBtnRightTab->SetVisible(true);
		}
		else
		{
			m_pBtnLeftTab->SetVisible(false);
			m_pBtnRightTab->SetVisible(false);
		}
	}
	return CAppWindow::Notify(msg);
}

/*=========================================================================
	������		: CMainWnd::GetLocMusPath
	����		: ��ȡ���������ļ���·��
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: 
	����ֵ		: CStdString ���������б���ļ���·��
=========================================================================*/
CStdString CMainWnd::GetLocMusPath(void) const
{
	return m_strLisPath;
}

/*=========================================================================
	������		: CMainWnd::SetLocMusPath
	����		: ���ñ��������ļ��е�·��
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: strPath ���������б���ļ���·��
	����ֵ		: 
=========================================================================*/
void CMainWnd::SetLocMusPath(LPCTSTR strPath)
{
	m_strLisPath = strPath;
}

/*=========================================================================
	������		: CMainWnd::OnOpenFileDlg
	����		: ���ļ��Ի���
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: 
	����ֵ		: 
=========================================================================*/
void CMainWnd::OnOpenFileDlg()
{
	TCHAR szBuffer[MAX_PATH] = { 0 };  
	BROWSEINFO bi = { 0 };  
	bi.hwndOwner = m_hWnd;                  //ӵ���Ŵ��ھ����ΪNULL��ʾ�Ի����Ƿ�ģ̬��
	bi.pszDisplayName = szBuffer;			//�����ļ��еĻ����� 
	bi.lpszTitle = TEXT("ѡ��һ���ļ���");	//����  
	bi.ulFlags = BIF_NEWDIALOGSTYLE;  
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);//����ļ�����
	if (!SHGetPathFromIDList( idl, szBuffer))  //��ȡѡ�����ļ���·��
	{  
		 return ;
	}

	CStdString strNum = _T("");
	_tfinddata_t file_info = {0};
	CString current_path(bi.pszDisplayName);
	SetLocMusPath(bi.pszDisplayName);			//���õ�ǰ�����ļ��е�ȫ·��
	current_path += _T("/*.mp3");

	int handle = _tfindfirst( current_path, &file_info);//��ȡ�����ļ��ľ������ʼ�����ļ�

	if(-1 == handle)
	{
		return;
	}
	do 
	{
		//�����������ļ������뱾�������б�
		CListTextElementUI *ptextItem = new CListTextElementUI;	
		m_pLisLocMusic->AddAt( ptextItem, m_pLisLocMusic->GetCount());
		strNum.Format( _T("%d"), m_pLisLocMusic->GetCount());
		ptextItem->SetAttribute( _T("height"), _T("40"));
		ptextItem->SetText( 0, strNum);
		ptextItem->SetText( 1, file_info.name);
		ptextItem->SetText( 2, _T(""));
		ptextItem->SetText( 3, _T(""));
		ptextItem->SetText( 4, _T(""));

		//�����������ļ������벥�������б�
		CListTextElementUI *pPlayLisItem = new CListTextElementUI;	
		m_pPlayListDlg->m_pLisPlay->AddAt( pPlayLisItem, m_pPlayListDlg->m_pLisPlay->GetCount());
		pPlayLisItem->SetAttribute( _T("height"), _T("40"));
		pPlayLisItem->SetText( 0, strNum);
		pPlayLisItem->SetText( 1, file_info.name);
		pPlayLisItem->SetText( 2, _T(""));

	} while (!_tfindnext( handle, &file_info));

	_findclose(handle);		//�ͷŲ����ļ��ľ��

	strNum.Format( _T("%d"), m_pLisLocMusic->GetCount());
	m_pLabPlyCount->SetText(strNum);
}

/*=========================================================================
	������		: CMainWnd::SetTotalTime
	����		: ����ý���ļ�����ʱ��
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: time ý���ļ�����ʱ��
	����ֵ		: 
=========================================================================*/
void CMainWnd::SetTotalTime(UINT_PTR time)
{
	m_dwTotalTime = time;
}

/*=========================================================================
	������		: CMainWnd::SetBtnState
	����		: ����BtnͼƬ���Դ����б����
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: strBtnName ��ť�ؼ�����
	����ֵ		: 
=========================================================================*/
void CMainWnd::SetBtnState(LPCTSTR strBtnName)
{
	//�����Խ��赥�򿪻�رյ�ͼ�꣬��Ҫ���������ؼ���������չ
	if(_tcscmp( strBtnName, m_pBtnCreateMusicList->GetName()) == 0)
	{
		bool flag = m_pLisMusicList->GetItemAt(8)->IsVisible();
		if(flag)
		{
			SetListElementShow(false);			
		}
		else
		{
			SetListElementShow();
		}
	}
}

/*=========================================================================
	������		: CMainWnd::AddListContainer
	����		: ��List�б��м���һ��Edit�ؼ���������ʱ���ݵ�����
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		:
	����ֵ		: 
=========================================================================*/
void CMainWnd::AddListContainer(void)
{
	CString str = _T("");
	int pMLCount = m_pLisMusicList->GetCount();
	m_pLisConEle = new CListContainerElementUI();
	m_pLisConEle->SetAttribute( _T("height"), _T("36"));
	str.Format( _T("�ҵ��б�%d"), ++m_myCrelisEleCount);
	if(!m_pEdt)
	{
		m_pEdt = new CEditUI;
		m_pEdt->SetAttribute( _T("name"), _T("MyLisEditId"));
		m_pEdt->SetAttribute( _T("float"), _T("true"));
		m_pEdt->SetAttribute( _T("text"), str);
		m_pEdt->SetAttribute( _T("pos"), _T("30,5,160,35"));
	}
	else
	{
		RECT pos = { 30, 5, 160, 35};
		m_pEdt->SetPos(pos);
		m_pEdt->SetText(str);
		m_pEdt->SetVisible(true);
	}
	m_pLisConEle->Add(m_pEdt);

	//�������Խ��赥�б�ӵ�8����ʼ���
	m_pLisMusicList->AddAt( m_pLisConEle, m_myCrelisEleCount+8);
	m_pEdt->SetFocus();			
	m_pEdt->SetSelAll();
}

/*=========================================================================
	������		: CMainWnd::AddListOption
	����		: ���б������Option��
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: 
	����ֵ		: 
=========================================================================*/
void CMainWnd::AddListOption(void)
{
	COptionUI *pOption = new COptionUI;
	m_pLisConEle->Add(pOption);
	pOption->SetAttribute( _T("group"), _T("leftlist"));
	pOption->SetAttribute( _T("text"), m_pEdt->GetText());
	pOption->SetAttribute( _T("align"), _T("left"));
	pOption->SetAttribute( _T("textpadding"), _T("46,2,2,2"));
	pOption->SetAttribute( _T("textcolor"), _T("#FFFEFFFF"));
	pOption->SetAttribute( _T("bkimage")
		, LIST_TYPE_ICON );
	pOption->SetAttribute( _T("selectedimage"), BROWSER_TITLE_BG);
	m_pLisConEle->Remove(m_pEdt);
	m_pEdt = NULL;
	m_pLisConEle = NULL;
}

/*=========================================================================
	������		: CMainWnd::CreateUserLoginDlg
	����		: �����û���¼�Ի���
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: 
	����ֵ		: 
=========================================================================*/
void CMainWnd::CreateUserLoginDlg(void)
{
	m_pUseLogDlg = new CUserLoginDlg(IDR_XML_LOGIN_FRAM);
	m_pUseLogDlg->Create( m_hWnd, _T("UserLoginDlg"), UI_WNDSTYLE_DIALOG
		, WS_EX_DLGMODALFRAME, 100, 100, 298, 390, NULL);
	m_pUseLogDlg->CenterWindow();
	m_pUseLogDlg->ShowModal();
}

/*=========================================================================
	������		: CMainWnd::CreateSkinChangeDlg
	����		: ��������Ƥ���Ի���
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: pos Ƥ���Ի�����ʾ��λ�ã��ͻ������꣩
	����ֵ		: 
=========================================================================*/
void CMainWnd::CreateSkinChangeDlg(CPoint& pos)
{
	ClientToScreen(m_hWnd,&pos);
	if(m_pSkiChaDlg)
	{
		RECT rc = {0};
		if(m_pSkiChaDlg->GetWindowRect(&rc))
		{
			//ָ�������Ի�����ָ���ĵط���ʾ
			SetWindowPos( m_pSkiChaDlg->GetHWND(), m_hWnd
				, pos.x, pos.y, rc.right-rc.left, rc.bottom-rc.top, 0);
			m_pSkiChaDlg->ShowWindow(true);
		}
	}
	else
	{
		//���������Ի�����ָ���ĵط�����ʾ
		m_pSkiChaDlg = new CSkinChangeDlg(IDR_XML_SKIN_CHANG);
		m_pSkiChaDlg->Create( m_hWnd, _T("SkinChangeDlg"), UI_WNDSTYLE_DIALOG
			, WS_EX_DLGMODALFRAME, pos.x, pos.y, 0, 0, NULL);
		m_pSkiChaDlg->ShowWindow(true);
		m_pSkiChaDlg->SetActiveWindow();
	}
}

/*=========================================================================
	������		: CMainWnd::CreatePlayListDlg
	����		: ���������б�Ի���
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: 
	����ֵ		: 
=========================================================================*/
void CMainWnd::CreatePlayListDlg()
{
	//���������б�Ի����࣬��ʼ����
	m_pPlayListDlg = new CPlayListDlg(IDR_XML_PLAYLIST_DLG);		
	m_pPlayListDlg->Create( m_hWnd, _T("PlyLisDlg")
		, UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE, 0, 0, 300, 390, NULL);
	m_pPlayListDlg->ShowWindow(false);
}

/*=========================================================================
	������		: CMainWnd::SetListElementShow
	����		: �����Խ��赥�б��Ƿ�����
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: visible ��ʾtrue,����ʾfalse
	����ֵ		: 
=========================================================================*/
void CMainWnd::SetListElementShow(bool visible)
{
	//�б�ĵڰ˸��������ڰ˸���Ϊ�Խ��赥���б�Ԫ��
	for( int i = 8; i <= m_myCrelisEleCount + 8; i++)
	{
		m_pLisMusicList->GetItemAt(i)->SetVisible(visible);
	}
	if(visible)
	{
		m_pBtnCreateMusicList->SetAttribute( _T("normalimage")
			, OPEN_TRIANGLE);
	}
	else
	{
		m_pBtnCreateMusicList->SetAttribute( _T("normalimage")
			, CLOSE_TRIANGLE);
	}
}

/*=========================================================================
	������		: CMainWnd::StartPlay
	����		: ��������
	�㷨ʵ��	: 
	����ȫ�ֱ���: 
	����		: strFullPath ý���ļ�ȫ·��
	����ֵ		: 
=========================================================================*/
void CMainWnd::StartPlay(CString strFullPath)
{	
	if(!m_pCMediPly->IsOpen())	//�򿪲�������Դ
	{
		// ����ȫ·���ļ�������ý���ļ�,ʧ�����ͷŲ�������Դ
		if( !m_pCMediPly->Play((LPCSTR)m_pCMediPly->UnicodeToUTF8(strFullPath)) )
		{
			m_pCMediPly->Stop();
		}
	}

	if(!m_pCMediPly->IsPlaying() && m_pCMediPly->IsOpen())
	{
		// ����ý���ļ�,�ɹ������ò��Ű�ť��ͼƬ
		if(m_pCMediPly->Play())
		{
			m_pCMediPly->Volume(GetVoiceSliVal());
			SetPlayBtnIsPlay(TRUE);
		}
	}
	else if(m_pCMediPly->IsPlaying())
	{
		m_pCMediPly->Pause();
		SetPlayBtnIsPlay(FALSE);
	}	
}

/*=========================================================================
	������		: CMainWnd::CreaLoopModeMenu
	����		: ����ѭ��ģʽ�˵���������ʾ
	����ȫ�ֱ���: 
	����		:
	����ֵ		: 
=========================================================================*/
void CMainWnd::CreaLoopModeMenu()
{
	CMenuWnd *pLoopModeMenu = new CMenuWnd( IDR_XML_MENU_MODE,_T("xml"), &m_pm);
	ASSERT(pLoopModeMenu);

	CMenuElementUI *pElement = new CMenuElementUI();
	pElement->SetName(_T("RandPlayMod_MenuE"));
	pElement->SetText(_T("�������"));
	pElement->SetFixedHeight(32);
	pLoopModeMenu->AddMenuItem(pElement);

	pElement = new CMenuElementUI();
	pElement->SetName(_T("LisOrderPlayMod_MenuE"));
	pElement->SetText(_T("˳�򲥷�"));
	pElement->SetFixedHeight(32);
	pLoopModeMenu->AddMenuItem(pElement);

	pElement = new CMenuElementUI();
	pElement->SetName(_T("SinglePlayMod_MenuE"));
	pElement->SetText(_T("����ѭ��"));
	pElement->SetFixedHeight(32);
	pLoopModeMenu->AddMenuItem(pElement);

	pElement = new CMenuElementUI();
	pElement->SetName(_T("LoopPlayMod_MenuE"));
	pElement->SetText(_T("�б�ѭ��"));
	pElement->SetFixedHeight(32);
	pLoopModeMenu->AddMenuItem(pElement);

	CPoint pos;
	pos.SetPoint( m_pBtnCycleLis->GetPos().left, m_pBtnCycleLis->GetPos().top);
	ClientToScreen( m_hWnd, &pos);
	pLoopModeMenu->TrackPopupMenu( eMenuAlignment_Right|eMenuAlignment_Bottom, pos, m_hWnd);
}

/*=========================================================================
	������		: CMainWnd::SetPlayMode
	����		: ���ò���ģʽ
	����ȫ�ֱ���: 
	����		: dMode ����ģʽ
	����ֵ		: 
=========================================================================*/
void CMainWnd::SetPlayMode(emLoopMod dMode)
{
	m_emLoopMod = dMode;	//��¼����ģʽ{˳��ѭ��...}
	switch(dMode)
	{
		case emRandomPlay:
			{
				//������Ű�ťͼƬ״̬
				m_pBtnCycleLis->SetNormalImage(PLAY_MODE_RAND_PNG);
				m_pBtnCycleLis->SetToolTip(_T("�������"));
			}
			break;	

		case emOrderPlay:
			{
				//˳�򲥷Ű�ťͼƬ״̬
				m_pBtnCycleLis->SetNormalImage(PLAY_MODE_NEXT_PNG);
				m_pBtnCycleLis->SetToolTip(_T("˳�򲥷�"));
			}  
			break;	

		case emSinglePlay:
			{
				//����ѭ�����Ű�ťͼƬ״̬
				m_pBtnCycleLis->SetNormalImage(PLAY_MODE_SINGLE_PNG);
				m_pBtnCycleLis->SetToolTip(_T("����ѭ��"));
			}
			break;	

		case emLoopPlay:
			{
				//�б�ѭ�����Ű�ťͼƬ״̬
				m_pBtnCycleLis->SetNormalImage(PLAY_MODE_CIRCLE_PNG);
				m_pBtnCycleLis->SetToolTip(_T("�б�ѭ��"));
			}
			break;	

		default:
			break;
	}
}

/*=========================================================================
	������		: CMainWnd::GetCurrentPlayName
	����		: ��ȡ��ǰ�������ֵ�����
	����ȫ�ֱ���: 
	����		:
	����ֵ		: CStdString ��ǰ���ڲ������ֵ�����
=========================================================================*/
CStdString CMainWnd::GetCurrentPlayName(void) const
{
	return m_strPlyName;
}

/*=========================================================================
	������		: CMainWnd::LoopPlay
	����		: �����б�ѭ������
	����ȫ�ֱ���: 
	����		:
	����ֵ		: 
=========================================================================*/
void CMainWnd::LoopPlay()				
{
	CString strUserData(m_pLisLocMusic->GetUserData());
	int count = m_pLisLocMusic->GetCount();
	int nSelected = _ttoi(strUserData);
	if( count <= 0)
	{
		return;
	}
	else
	{
		CString strPlayName = _T("");
		CListTextElementUI* pTextEle;
		if(nSelected < count-1)
		{
			pTextEle = (CListTextElementUI*)m_pLisLocMusic->GetItemAt(nSelected+1);
			strPlayName = GetLocMusPath()+_T("\\");
			strPlayName += (CString)pTextEle->GetText(1);

			//ѡ�б��������б����±�ΪnSelected+1����
			m_pLisLocMusic->SelectItem( nSelected+1, true); 	
		}
		else
		{
			pTextEle = (CListTextElementUI*)m_pLisLocMusic->GetItemAt(0);
			strPlayName = GetLocMusPath()+_T("\\");
			strPlayName += (CString)pTextEle->GetText(1);

			//ѡ�б��������б����±�Ϊ0����
			m_pLisLocMusic->SelectItem( 0, true); 	
		}

		//���ò����б��и���Ϊѡ��״̬
		m_pPlayListDlg->m_pLisPlay->SelectItem( m_pLisLocMusic->GetCurSel(), true);

		//�����������б������ڲ��ŵ����ֵ��±�����Ϊ�û����ݣ�������GetUserDataʹ��
		strUserData.Format( _T("%d"), m_pLisLocMusic->GetCurSel());
		m_pLisLocMusic->SetUserData(strUserData);	

		StartPlay(strPlayName);
	}
}

/*=========================================================================
	������		: CMainWnd::RandomPlay
	����		: �����б��������
	����ȫ�ֱ���: 
	����		:
	����ֵ		: 
=========================================================================*/
void CMainWnd::RandomPlay()					
{
	CString strUserData = _T("");

	//��ȡ���������б��е����ֵ�����
	int count = m_pLisLocMusic->GetCount();

	int nSelected = 0;
	if( count <= 0)
	{
		return;
	}
	else
	{
		CListTextElementUI* pTextEle = NULL;
		CString strPlayName = _T("");
		time_t systime = time(0);
		srand((UINT)systime);
		nSelected = rand()%count;
		pTextEle = (CListTextElementUI*)m_pLisLocMusic->GetItemAt(nSelected);
		strPlayName = GetLocMusPath()+_T("\\");
		strPlayName += (CString)pTextEle->GetText(1);

		//ѡ�б��������б����±�ΪnSelected����
		m_pLisLocMusic->SelectItem(nSelected, true);

		//���ò����б��и���Ϊѡ��״̬
		m_pPlayListDlg->m_pLisPlay->SelectItem( m_pLisLocMusic->GetCurSel(), true);

		//�����������б������ڲ��ŵ����ֵ��±������û����ݣ�������GetUserDataʹ��
		strUserData.Format( _T("%d"), m_pLisLocMusic->GetCurSel());
		m_pLisLocMusic->SetUserData(strUserData);	

		StartPlay(strPlayName);		
	}
}

/*=========================================================================
	������		: CMainWnd::OrderPlay
	����		: �б�˳�򲥷�
	����ȫ�ֱ���: 
	����		:
	����ֵ		: 
=========================================================================*/
void CMainWnd::OrderPlay()
{
	CString strUserData(m_pLisLocMusic->GetUserData());
	int count = m_pLisLocMusic->GetCount();
	int nSelected = _ttoi(strUserData);
	if( count <= 0)
	{
		return;
	}
	else
	{
		if(nSelected == count-1 || nSelected >= count)
		{
			return;
		}
		else
		{
			CString strPlayName = _T("");
			CListTextElementUI* pTextEle = NULL;
			pTextEle = (CListTextElementUI*)m_pLisLocMusic->GetItemAt(nSelected+1);
			strPlayName = GetLocMusPath()+_T("\\");
			strPlayName += (CString)pTextEle->GetText(1);

			//ѡ�б��������б����±�ΪnSelected+1����
			m_pLisLocMusic->SelectItem(nSelected+1,true);

			//���ò����б��и���Ϊѡ��״̬
			m_pPlayListDlg->m_pLisPlay->SelectItem( m_pLisLocMusic->GetCurSel(), true);

			//�����������б������ڲ��ŵ����ֵ��±������û����ݣ�������GetUserDataʹ��
			strUserData.Format( _T("%d"), m_pLisLocMusic->GetCurSel());
			m_pLisLocMusic->SetUserData(strUserData);	

			StartPlay(strPlayName);
		}	
	}
}

/*=========================================================================
	������		: CMainWnd::SinglePlay
	����		: ����ѭ������
	����ȫ�ֱ���: 
	����		:
	����ֵ		: 
=========================================================================*/
void CMainWnd::SinglePlay()
{
	CString strUserData(m_pLisLocMusic->GetUserData());
	int count = m_pLisLocMusic->GetCount();
	int nSelected = _ttoi(strUserData);
	if( count <= 0)
	{
		return;
	}
	else
	{
		if(nSelected >= count)
			return;
		else
		{
			CString strPlayName = _T("");
			CListTextElementUI* pTextEle = NULL;
			pTextEle = (CListTextElementUI*)m_pLisLocMusic->GetItemAt(nSelected);
			strPlayName = GetLocMusPath()+_T("\\");
			strPlayName += (CString)pTextEle->GetText(1);

			//ѡ�б��������б����±�ΪnSelected����
			m_pLisLocMusic->SelectItem(nSelected,true); 	

			//���ò����б��и���Ϊѡ��״̬
			m_pPlayListDlg->m_pLisPlay->SelectItem(m_pLisLocMusic->GetCurSel(),true);

			//�����������б������ڲ��ŵ����ֵ��±������û����ݣ�������GetUserDataʹ��
			strUserData.Format(_T("%d"),m_pLisLocMusic->GetCurSel());
			m_pLisLocMusic->SetUserData(strUserData);	

			StartPlay(strPlayName);
		}
	}
}

/*=========================================================================
	������		: CMainWnd::GetPlyMod
	����		: ��ò���ģʽ
	����ȫ�ֱ���: 
	����		:
	����ֵ		: emLoopMod ö�����ͣ�����ǰ���ֵĲ���ģʽ
=========================================================================*/
emLoopMod CMainWnd::GetPlyMod(void) const
{
	return m_emLoopMod;
}

/*=========================================================================
	������		: CMainWnd::GetCurrentPlayName
	����		: ���õ�ǰ���ֲ��ŵ�ʱ������ֲ��Ž�������λ��
	����ȫ�ֱ���: 
	����		:
	����ֵ		: 
=========================================================================*/
void CMainWnd::SetMusTime()
{
	 //��ȡ��ǰ���ŵ�����λ��
	UINT_PTR curPos = m_pCMediPly->GetTime();
	CString strTime;
	if(m_dwTotalTime == 0)
	{
		return;
	}
	else
	{
		//���ֲ��Ž�������λ��
		int slipos = curPos*m_pSliMusPlyTim->GetMaxValue()/m_dwTotalTime; 
		UINT_PTR sec = curPos/1000%60;				                
		UINT_PTR min = curPos/1000/60;

		//ת���ɣ��֣��룩��ʽ
		strTime.Format( _T("%0.2d:%0.2d"), min, sec);

		//��ʾ���ŵ�ʱ��
		m_pBtnCurTim->SetText(strTime);

		//���ò��Ž�������λ��
		m_pSliMusPlyTim->SetValue(slipos);
	}
}

/*=========================================================================
	������		: CMainWnd::SetMusSliVal
	����		: �������ֽ�������λ��
	����ȫ�ֱ���: 
	����		: pos ���ֽ�������λ��ֵ
	����ֵ		:
=========================================================================*/
void CMainWnd::SetMusSliVal(int pos)
{
	m_pSliMusPlyTim->SetValue(pos);
}

/*=========================================================================
	������		: CMainWnd::GetMusSliVal
	����		: ��ȡ���ֽ�������ֵ
	����ȫ�ֱ���: 
	����		: 
	����ֵ		: int ���ֽ�������λ��ֵ
=========================================================================*/
int CMainWnd::GetMusSliVal() const
{
	return m_pSliMusPlyTim->GetValue();
}

/*=========================================================================
	������		: CMainWnd::SetVoiceSliVal
	����		: ����������������ֵ
	����ȫ�ֱ���: 
	����		: pos ������������λ��ֵ
	����ֵ		:
=========================================================================*/
void CMainWnd::SetVoiceSliVal(int pos) const
{
	m_pSliVolice->SetValue(pos);
}

/*=========================================================================
	������		: CMainWnd::GetVoiceSliVal
	����		: ��ȡ������������ֵ
	����ȫ�ֱ���: 
	����		:
	����ֵ		: int ������������λ��ֵ
=========================================================================*/
int CMainWnd::GetVoiceSliVal() const
{
	return m_pSliVolice->GetValue();
}

/*=========================================================================
	������		: CMainWnd::SetPlayBtnIsPlay
	����		: ���ò��Ű�ť�ĵ�״̬ͼƬ
	����ȫ�ֱ���: 
	����		: isPlaying ��ǰ�Ƿ��ڲ�������
	����ֵ		: 
=========================================================================*/
void CMainWnd::SetPlayBtnIsPlay(BOOL isPlaying)
{
	if(isPlaying)
	{
		//����Ϊ���ڲ���״̬ͼƬ
		m_pBtnPlay->SetNormalImage(BTN_PLAY_PNG);
	}
	else
	{
		//����Ϊ��ͣ����״̬ͼƬ
		m_pBtnPlay->SetNormalImage(BTN_PAUSE_PNG);
	}
}


