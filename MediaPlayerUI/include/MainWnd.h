/******************************************************************************
	ģ����      : mediaplay
	�ļ���      : MainWnd.h
	����ļ�    : CUserLoginDlg.h, CSkinChangeDlg.h, CPlayListDlg.h, CMediPly.h
	�ļ�ʵ�ֹ���: �����������Լ����ֲ����߼�
	����        : ���Ŀ�
	�汾        : 
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��      �汾        �޸���      �޸�����
	2017/3/1                ���Ŀ�        ����
******************************************************************************/

#ifndef MAINWND_H
#define MAINWND_H

#include"stdafx.h"
#include"MediPly.h"
#include"UserLoginDlg.h"
#include"SkinChangeDlg.h"
#include"PlayListDlg.h"

class CMainWnd:public CAppWindow
{
public:
	CMainWnd( STRINGorID strUI, unsigned int dwTransparent = 255
		, bool bDeleteSelf = true);
	~CMainWnd(void);

	LPCTSTR GetWindowClassName(void) const;
	LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam );
	LRESULT OnSysCommand( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam,BOOL& bHandled);
	UINT GetClassStyle(void) const;
	void Prepare(void);

	//��ʼ��
	void Init(void);

	//��Ϣ֪ͨ
	bool Notify( TNotifyUI& msg );

	//��ȡ�������ֵ��ļ���·��
	CStdString GetLocMusPath(void) const;

	//�����б�ѭ������
	void LoopPlay(void);

	//�����б��������
	void RandomPlay(void);

	//�����б�˳�򲥷�
	void OrderPlay(void);

	//���ص���ѭ������
	void SinglePlay(void);

	//����������ʱ��
	void SetTotalTime(UINT_PTR time);

	//������ʾ��ʱ��
	void SetMusTime(void);

	//���ò��Ű�ť��ͼƬ״̬�ǲ��Ż���ֹͣ
	void SetPlayBtnIsPlay(BOOL isPlaying = true);

	//����\��ȡ���ֲ��Ž�������λ�ã�0-1000��
	void SetMusSliVal(int pos);
	int  GetMusSliVal(void) const;

	//����\��ȡ������������λ�ã�0-100��
	void SetVoiceSliVal(int pos) const;
	int GetVoiceSliVal() const;

	//��ȡ\���ò���ģʽ{�����˳�򣬵�����ѭ��}
	emLoopMod  GetPlyMod(void) const;
	void SetPlayMode(emLoopMod dMode);

protected:

	//���ļ��Ի���
	void OnOpenFileDlg(void);

	//��List�б��м���һ��Option�ؼ������ڻ�ȡ��ʱEDIT���ݲ���ʾ
	void AddListOption(void);

	//��List�б��м���һ��Edit�ؼ���������ʱ���ݵ�����
	void AddListContainer(void);
	
	//�����û���¼�Ի���
	void CreateUserLoginDlg(void);

	//�ڴ�������괦����Ƥ�����ĶԻ���
	void CreateSkinChangeDlg(CPoint& pos);

	//���������б�Ի���
	void CreatePlayListDlg(void);				

	//�����˵�ͨ��xml�����ļ�
	void CreateMenuByXml(STRINGorID xml, CPoint pos);

	//���������б���ģʽ�˵�
	void CreaLoopModeMenu(void);

	//���ݰ�ť�ؼ������ð�ťͼƬ
	void SetBtnState(LPCTSTR strBtnName);

	//�Խ��赥�б����ʾ������
	void SetListElementShow(bool visible = true);

	//��ʼ����{���š���ͣ��ֹͣ������}
	void StartPlay(CString strFullPath);						

	//���ñ������ֵ��ļ���·��
	void SetLocMusPath(LPCTSTR strPath);

	//��ȡ��ǰ���ڲ����б���ļ���
	CStdString GetCurrentPlayName(void) const;

protected:
	bool OnClose(TNotifyUI& msg);
	bool OnCreateMusicListBtn( TNotifyUI& msg );//�Խ��赥(Button)��Ӧ
	bool OnCreateMusicListAddBtn(TNotifyUI& msg);//���Ӷ�̬�赥(Button)��Ӧ
	bool OnLeftLabBtn(TNotifyUI& msg);			//���ֿ��Ƽ�ҳ���͵Ļ�����(Button)��Ӧ
	bool OnRightLabBtn(TNotifyUI& msg);			//���ֿ��Ƽ�ҳ���͵Ļ����ҷ�(Button)��Ӧ
	bool OnLeftTabBtn(TNotifyUI& msg);			//���ֿ��Ƽ�ҳ�׷�������(Button)��Ӧ
	bool OnRightTabBtn(TNotifyUI& msg);			//���ֿ��Ƽ�ҳ�׷������ҷ�(Button)��Ӧ
	bool OnPlayBtn(TNotifyUI& msg);				//��������(Button)��Ӧ
	bool OnPlayPrevBtn(TNotifyUI& msg);			//������һ��(Button)��Ӧ
	bool OnPlayNextBtn(TNotifyUI& msg);			//������һ��(Button)��Ӧ
	bool OnLogoBtn(TNotifyUI& msg);				//�������ϰٶ�����logo(Button)��Ӧ
	bool OnMyMessageBtn(TNotifyUI& msg);		//�ҵ���Ϣ(Button)��Ӧ
	bool OnSettingBtn(TNotifyUI& msg);			//����(Button)��Ӧ
	bool OnSkinChangeBtn(TNotifyUI& msg);		//�ı�Ƥ��(Button)��Ӧ
	bool OnMinBtn(TNotifyUI& msg);				//��С��(Button)��Ӧ
	bool OnVoliceBtn(TNotifyUI& msg);			//����(Button)��Ӧ
	bool OnImportMusBtn(TNotifyUI& msg);		//��������(Button)��Ӧ
	bool OnCycleLisBtn(TNotifyUI& msg);			//ѭ���б�(Button)��Ӧ
	bool OnPlayQueueBtn(TNotifyUI& msg);		//���Ŷ����б�(Button)��Ӧ
	bool OnCleanTextBtn(TNotifyUI& msg);		//��������������

	bool OnMusPlyTimSli(TNotifyUI& msg);		//������ֲ��Ž�����(Slider)��Ӧ
	bool OnVoliceSli(TNotifyUI& msg);			//�������������(Slider)��Ӧ

	bool OnMusiLibrOpt(TNotifyUI& msg);			//���ֿ�ҳ�����Ƽ�(Option)��Ӧ
	bool OnMusiRankOpt(TNotifyUI& msg);			//���ֿ�ҳ���а�(Option)��Ӧ
	bool OnPlyListOpt(TNotifyUI& msg);			//���ֿ�ҳ���и赥(Option)��Ӧ
	bool OnBoarCastStaOpt(TNotifyUI& msg);		//���ֿ�ҳ���е�̨(Option)��Ӧ
	bool OnSingerOpt(TNotifyUI& msg);			//���ֿ�ҳ���и���(Option)��Ӧ
	bool OnClaFicOpt(TNotifyUI& msg);			//���ֿ�ҳ���з���(Option)��Ӧ
	bool OnLiveOpt(TNotifyUI& msg);				//���ֿ�ҳ����ֱ��(Option)��Ӧ
	bool OnOnlineMusicOpt(TNotifyUI& msg);		//���ֿ�(Option)��Ӧ
	bool OnActiveOpt(TNotifyUI& msg);			//��̬(Option)��Ӧ
	bool OnTryListnMusicOpt(TNotifyUI& msg);	//�����б�(Option)��Ӧ
	bool OnLocOpt(TNotifyUI& msg);				//��������(Option)��Ӧ
	bool OnDowLoaOpt(TNotifyUI& msg);			//��������(Option)��Ӧ

	bool OnRandPlayMod_MenuE(TNotifyUI& msg);	//�������ģʽ(MenuElement)��Ӧ
	bool OnLoopPlayMod_MenuE(TNotifyUI& msg);	//ѭ������ģʽ(MenuElement)��Ӧ
	bool OnSinglePlayMod_MenuE(TNotifyUI& msg);	//����ѭ��ģʽ(MenuElement)��Ӧ
	bool OnLisOrderPlayMod_MenuE(TNotifyUI& msg);//�б�˳��ģʽ(MenuElement)��Ӧ

	bool OnSearchEditSetFoc(TNotifyUI& msg);	//�����༭�ؼ���ý���(SearchEdit)��Ӧ
	DECLARE_UI_MSG_MAP()

public:
	static CVerticalLayoutUI *m_pBkCtrl;	//�����ؼ�ָ��

protected:
	int m_myCrelisEleCount;	//���������Խ��赥�����Խ��赥������

	//CButtonUI
	CButtonUI *m_pBtnPlay;
	CButtonUI *m_pBtnVolice;
	CButtonUI *m_pBtnCurTim;
	CButtonUI *m_pBtnLeftTab;
	CButtonUI *m_pBtnRightTab;
	CButtonUI *m_pBtnCreateMusicList;
	CButtonUI *m_pBtnCycleLis;
	CButtonUI *m_pBtnCleanText;
	CButtonUI *m_pBtnLeftLab;
	CButtonUI *m_pBtnRightLab;

	//CEditUI
	CEditUI	*m_pEdt;
	CEditUI	*m_pEdtSearch;
	
	//CListUI
	CListUI	*m_pLisMusicList;
	CListUI	*m_pLisLocMusic;

	//CTableLayoutUI
	CTabLayoutUI *m_pTabRecom;
	CTabLayoutUI *m_pTabShoufa;
	CTabLayoutUI *m_pTabMusiList;
	CTabLayoutUI *m_pTabMusiLibr;

	//CWebBrowserUI
	CWebBrowserUI *m_pWebBrowser;

	//CSliderUI
	CSliderUI *m_pSliVolice;
	CSliderUI *m_pSliMusPlyTim;	//���ֽ�����

	//CLabelUI
	CLabelUI *m_pLabPlyCount;

	//CVerticalLayoutUI
	CVerticalLayoutUI *m_pVerMain;

	//ListContainerElement
	CListContainerElementUI *m_pLisConEle;

private:
	BOOL			m_bIsNoVol;		//�Ƿ��Ǿ���
	ULONG_PTR		m_dwTotalTime;	//��¼������ʱ��
	CStdString		m_strLisPath;	//��¼��ǰ�����б���ļ���·��
	CStdString		m_strPlyName;	//��¼��ǰ�����б���ļ���
	emLoopMod		m_emLoopMod;	//��¼���ֵĲ���ģʽ{�����˳�򣬵�����ѭ��}

	CMediPly        *m_pCMediPly;	//ý�岥����ָ�룬����ý�岥�Ź��ܵ�ʵ��
	CPlayListDlg    *m_pPlayListDlg;//�û���¼�Ի�����ָ��,���캯����ʱʵ����
	CUserLoginDlg   *m_pUseLogDlg;	//�û���¼�Ի�����ָ��
	CSkinChangeDlg  *m_pSkiChaDlg;	//�����Ի�����ָ��
};

#endif
