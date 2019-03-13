/******************************************************************************
	模块名      : mediaplay
	文件名      : MainWnd.h
	相关文件    : CUserLoginDlg.h, CSkinChangeDlg.h, CPlayListDlg.h, CMediPly.h
	文件实现功能: 播放器界面以及音乐播放逻辑
	作者        : 熊文凯
	版本        : 
	-------------------------------------------------------------------------------
	修改记录:
	日  期      版本        修改人      修改内容
	2017/3/1                熊文凯        创建
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

	//初始化
	void Init(void);

	//消息通知
	bool Notify( TNotifyUI& msg );

	//获取本地音乐的文件夹路径
	CStdString GetLocMusPath(void) const;

	//本地列表循环播放
	void LoopPlay(void);

	//本地列表随机播放
	void RandomPlay(void);

	//本地列表顺序播放
	void OrderPlay(void);

	//本地单曲循环播放
	void SinglePlay(void);

	//设置音乐总时间
	void SetTotalTime(UINT_PTR time);

	//设置显示的时间
	void SetMusTime(void);

	//设置播放按钮的图片状态是播放还是停止
	void SetPlayBtnIsPlay(BOOL isPlaying = true);

	//设置\获取音乐播放进度条的位置（0-1000）
	void SetMusSliVal(int pos);
	int  GetMusSliVal(void) const;

	//设置\获取声音进度条的位置（0-100）
	void SetVoiceSliVal(int pos) const;
	int GetVoiceSliVal() const;

	//获取\设置播放模式{随机，顺序，单曲，循环}
	emLoopMod  GetPlyMod(void) const;
	void SetPlayMode(emLoopMod dMode);

protected:

	//打开文件对话框
	void OnOpenFileDlg(void);

	//在List列表中加入一个Option控件，用于获取临时EDIT内容并显示
	void AddListOption(void);

	//在List列表中加入一个Edit控件，用于临时内容的输入
	void AddListContainer(void);
	
	//创建用户登录对话框
	void CreateUserLoginDlg(void);

	//在传入的坐标处创建皮肤更改对话框
	void CreateSkinChangeDlg(CPoint& pos);

	//创建播放列表对话框
	void CreatePlayListDlg(void);				

	//创建菜单通过xml配置文件
	void CreateMenuByXml(STRINGorID xml, CPoint pos);

	//创建歌曲列表播放模式菜单
	void CreaLoopModeMenu(void);

	//根据按钮控件名设置按钮图片
	void SetBtnState(LPCTSTR strBtnName);

	//自建歌单列表的显示或隐藏
	void SetListElementShow(bool visible = true);

	//开始播放{播放、暂停、停止、音乐}
	void StartPlay(CString strFullPath);						

	//设置本地音乐的文件夹路径
	void SetLocMusPath(LPCTSTR strPath);

	//获取当前正在播放列表的文件名
	CStdString GetCurrentPlayName(void) const;

protected:
	bool OnClose(TNotifyUI& msg);
	bool OnCreateMusicListBtn( TNotifyUI& msg );//自建歌单(Button)响应
	bool OnCreateMusicListAddBtn(TNotifyUI& msg);//增加动态歌单(Button)响应
	bool OnLeftLabBtn(TNotifyUI& msg);			//音乐库推荐页推送的画面左翻(Button)响应
	bool OnRightLabBtn(TNotifyUI& msg);			//音乐库推荐页推送的画面右翻(Button)响应
	bool OnLeftTabBtn(TNotifyUI& msg);			//音乐库推荐页首发项中左翻(Button)响应
	bool OnRightTabBtn(TNotifyUI& msg);			//音乐库推荐页首发项中右翻(Button)响应
	bool OnPlayBtn(TNotifyUI& msg);				//播放音乐(Button)响应
	bool OnPlayPrevBtn(TNotifyUI& msg);			//播放上一个(Button)响应
	bool OnPlayNextBtn(TNotifyUI& msg);			//播放下一个(Button)响应
	bool OnLogoBtn(TNotifyUI& msg);				//标题栏上百度音乐logo(Button)响应
	bool OnMyMessageBtn(TNotifyUI& msg);		//我的消息(Button)响应
	bool OnSettingBtn(TNotifyUI& msg);			//设置(Button)响应
	bool OnSkinChangeBtn(TNotifyUI& msg);		//改变皮肤(Button)响应
	bool OnMinBtn(TNotifyUI& msg);				//最小化(Button)响应
	bool OnVoliceBtn(TNotifyUI& msg);			//音量(Button)响应
	bool OnImportMusBtn(TNotifyUI& msg);		//导入音乐(Button)响应
	bool OnCycleLisBtn(TNotifyUI& msg);			//循环列表(Button)响应
	bool OnPlayQueueBtn(TNotifyUI& msg);		//播放队列列表(Button)响应
	bool OnCleanTextBtn(TNotifyUI& msg);		//清除搜索框的文字

	bool OnMusPlyTimSli(TNotifyUI& msg);		//点击音乐播放进度条(Slider)响应
	bool OnVoliceSli(TNotifyUI& msg);			//点击音量进度条(Slider)响应

	bool OnMusiLibrOpt(TNotifyUI& msg);			//音乐库页面中推荐(Option)响应
	bool OnMusiRankOpt(TNotifyUI& msg);			//音乐库页面中榜单(Option)响应
	bool OnPlyListOpt(TNotifyUI& msg);			//音乐库页面中歌单(Option)响应
	bool OnBoarCastStaOpt(TNotifyUI& msg);		//音乐库页面中电台(Option)响应
	bool OnSingerOpt(TNotifyUI& msg);			//音乐库页面中歌手(Option)响应
	bool OnClaFicOpt(TNotifyUI& msg);			//音乐库页面中分类(Option)响应
	bool OnLiveOpt(TNotifyUI& msg);				//音乐库页面中直播(Option)响应
	bool OnOnlineMusicOpt(TNotifyUI& msg);		//音乐库(Option)响应
	bool OnActiveOpt(TNotifyUI& msg);			//动态(Option)响应
	bool OnTryListnMusicOpt(TNotifyUI& msg);	//试听列表(Option)响应
	bool OnLocOpt(TNotifyUI& msg);				//本地音乐(Option)响应
	bool OnDowLoaOpt(TNotifyUI& msg);			//歌曲下载(Option)响应

	bool OnRandPlayMod_MenuE(TNotifyUI& msg);	//随机播放模式(MenuElement)响应
	bool OnLoopPlayMod_MenuE(TNotifyUI& msg);	//循环播放模式(MenuElement)响应
	bool OnSinglePlayMod_MenuE(TNotifyUI& msg);	//单曲循环模式(MenuElement)响应
	bool OnLisOrderPlayMod_MenuE(TNotifyUI& msg);//列表顺序模式(MenuElement)响应

	bool OnSearchEditSetFoc(TNotifyUI& msg);	//搜索编辑控件获得焦点(SearchEdit)响应
	DECLARE_UI_MSG_MAP()

public:
	static CVerticalLayoutUI *m_pBkCtrl;	//背景控件指针

protected:
	int m_myCrelisEleCount;	//主界面中自建歌单栏中自建歌单的数量

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
	CSliderUI *m_pSliMusPlyTim;	//音乐进度条

	//CLabelUI
	CLabelUI *m_pLabPlyCount;

	//CVerticalLayoutUI
	CVerticalLayoutUI *m_pVerMain;

	//ListContainerElement
	CListContainerElementUI *m_pLisConEle;

private:
	BOOL			m_bIsNoVol;		//是否是静音
	ULONG_PTR		m_dwTotalTime;	//记录音乐总时间
	CStdString		m_strLisPath;	//记录当前播放列表的文件夹路径
	CStdString		m_strPlyName;	//记录当前播放列表的文件名
	emLoopMod		m_emLoopMod;	//记录音乐的播放模式{随机，顺序，单曲，循环}

	CMediPly        *m_pCMediPly;	//媒体播放类指针，负责媒体播放功能的实现
	CPlayListDlg    *m_pPlayListDlg;//用户登录对话框类指针,构造函数是时实例化
	CUserLoginDlg   *m_pUseLogDlg;	//用户登录对话框类指针
	CSkinChangeDlg  *m_pSkiChaDlg;	//换肤对话框类指针
};

#endif
