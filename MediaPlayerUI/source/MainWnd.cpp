/******************************************************************************
	模块名      : mediaplay
	文件名      : MainWnd.cpp
	相关文件    : MainWnd.h
	文件实现功能: 实现主界面显示以及音乐播放逻辑
	作者        : 熊文凯
	版本        : 
	-------------------------------------------------------------------------------
	修改记录:
	日  期      版本        修改人      修改内容
	2017/3/1              熊文凯        创建
******************************************************************************/



#include "MainWnd.h"
#include "define.h"

//静态成员主界面背景控件初始化
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
,m_bIsNoVol(FALSE)			//是否是静音
,m_dwTotalTime(0)				//记录音乐总时间
,m_strLisPath(_T(""))		//记录当前播放列表的文件夹路径
,m_strPlyName(_T(""))		//记录当前播放列表的文件名
,m_emLoopMod(emLoopPlay)	//记录音乐的播放模式{随机，顺序，单曲，循环}
,m_pCMediPly(NULL)			//媒体播放类指针，负责媒体播放功能的实现
,m_pPlayListDlg(NULL)	    //用户登录对话框类指针,构造函数是时实例化
,m_pUseLogDlg(NULL)	        //用户登录对话框类指针
,m_pSkiChaDlg(NULL)     	//换肤对话框类指针
,m_myCrelisEleCount(0)  	//主界面中自建歌单栏中自建歌单的数量
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
,m_pSliMusPlyTim(NULL)	//音乐进度条
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
	函数名		: CMainWnd::OnClose
	功能		: 响应关闭按钮消息，退出主程序
	算法实现	: 
	引用全局变量: 
	参数		: msg 消息结构体
	返回值		: bool 处理了返回true，否则false
=========================================================================*/
bool CMainWnd::OnClose(TNotifyUI& msg)
{
	PostQuitMessage(0);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnCreateMusicListBtn
	功能		: 响应自建歌单按钮点击事件
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnCreateMusicListBtn( TNotifyUI& msg )
{
	//自建歌单的按钮状态设置
	SetBtnState(m_pBtnCreateMusicList->GetName());
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnCreateMusicListAddBtn
	功能		: 响应自建歌单添加列表消息
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnCreateMusicListAddBtn(TNotifyUI& msg)
{
	//打开自建歌单列表
	SetListElementShow();

	//添加一个自建的歌单列表项
	AddListContainer();
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnLeftLabBtn
	功能		: 音乐库推荐页面第一栏左翻功能
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnLeftLabBtn(TNotifyUI& msg)
{
	m_pTabRecom->SelectItem(m_pTabRecom->GetCurSel()-1);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnRightLabBtn
	功能		: 音乐库推荐页面第一栏右翻功能
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnRightLabBtn(TNotifyUI& msg)
{
	m_pTabRecom->SelectItem(m_pTabRecom->GetCurSel()+1);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnLeftTabBtn
	功能		: 音乐库推荐页面首发项左翻功能
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnLeftTabBtn(TNotifyUI& msg)
{
	m_pTabShoufa->SelectItem(m_pTabShoufa->GetCurSel()-1);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnRightTabBtn
	功能		: 音乐库推荐页面首发项右翻功能
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnRightTabBtn(TNotifyUI& msg)
{
	m_pTabShoufa->SelectItem(m_pTabShoufa->GetCurSel()+1);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnPlayBtn
	功能		: 从暂停状态的音乐继续播放
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnPlayBtn(TNotifyUI& msg)
{
	StartPlay(_T(""));
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnPlayPrevBtn
	功能		: 播放前一首歌曲
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
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
	if(preSelected == 0 || preSelected>count)    //如果是列表的第一个
	{
		p = (CListTextElementUI*)m_pLisLocMusic->GetItemAt(count-1);
		strPreName = GetLocMusPath();
		strPreName += "\\";
		strPreName += p->GetText(1);

		//设置本地列表中该项为选中播放状态
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

	//设置播放列表中该项为选中状态
	m_pPlayListDlg->m_pLisPlay->SelectItem( m_pLisLocMusic->GetCurSel(), true);

	strUserData.Format( _T("%d"), m_pLisLocMusic->GetCurSel());
	m_pLisLocMusic->SetUserData(strUserData);

	StartPlay((CString)strPreName);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnPlayNextBtn
	功能		: 播放下一首歌曲
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
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
	if(preSelected >= count-1)			       //如果是列表的最后一个
	{
		p = (CListTextElementUI*)m_pLisLocMusic->GetItemAt(0);
		strPreName = GetLocMusPath();
		strPreName += "\\";
		strPreName += p->GetText(1);
		m_pLisLocMusic->SelectItem( 0, true);  //设置本地列表中该项为选中播放状态
	}
	else
	{
		p = (CListTextElementUI*)m_pLisLocMusic->GetItemAt(preSelected+1);
		strPreName = GetLocMusPath();
		strPreName += "\\";
		strPreName += p->GetText(1);

		//设置本地列表中该项为选中播放状态
		m_pLisLocMusic->SelectItem( preSelected+1, true);			
	}
	m_pCMediPly->Stop();		
	m_strPlyName = p->GetText(1);

	//设置播放列表中该项为选中状态
	m_pPlayListDlg->m_pLisPlay->SelectItem( m_pLisLocMusic->GetCurSel(), true);

	strUserData.Format( _T("%d"), m_pLisLocMusic->GetCurSel());
	m_pLisLocMusic->SetUserData(strUserData);

	StartPlay((CString)strPreName);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnLogoBtn
	功能		: 响应Logo点击事件
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnLogoBtn(TNotifyUI& msg)
{
	//创建系统菜单并弹出显示
	CreateMenuByXml( IDR_XML_SYS_MENU, msg.ptMouse);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnMyMessageBtn
	功能		: 我的消息按钮点击事件
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnMyMessageBtn(TNotifyUI& msg)
{
	//创建用户登录对话框并显示
	CreateUserLoginDlg();
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnSettingBtn
	功能		: 响应设置按钮点击消息
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnSettingBtn(TNotifyUI& msg)
{
	//创建系统菜单并弹出显示
	CreateMenuByXml( IDR_XML_SYS_MENU, msg.ptMouse);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnSkinChangeBtn
	功能		: 响应更改皮肤按钮点击事件
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnSkinChangeBtn(TNotifyUI& msg)
{
	//创建换肤对话框并显示
	CreateSkinChangeDlg(CPoint(msg.ptMouse));
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnMinBtn
	功能		: 响应最小化按钮点击事件
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnMinBtn(TNotifyUI& msg)
{
	//最小化窗口
	::ShowWindow(m_hWnd, SW_MINIMIZE);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnVoliceBtn
	功能		: 响应声音按钮点击事件
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnVoliceBtn(TNotifyUI& msg)
{
	if(m_bIsNoVol)
	{
		m_bIsNoVol = FALSE;
		//获取声音进度条的位置（0-100）并设置在媒体播放器中
		m_pCMediPly->Volume(GetVoiceSliVal());					
		m_pBtnVolice->SetNormalImage(BTN_MINIBIG_OPEN_STATE_PNG);
	}
	else
	{
		m_bIsNoVol = TRUE;
		m_pCMediPly->Volume(0); //静音
		m_pBtnVolice->SetNormalImage(BTN_MINIBIG_CLOSE_STATE_PNG);
	}
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnImportMusBtn
	功能		: 响应导入音乐按钮点击事件，打开导入音乐的对话框
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnImportMusBtn(TNotifyUI& msg)
{
	//打开导入音乐对话框
	OnOpenFileDlg();
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnCycleLisBtn
	功能		: 响应循环列表按钮点击事件并显示菜单
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnCycleLisBtn(TNotifyUI& msg)
{
	//创建循环模式菜单并弹出显示
	CreaLoopModeMenu();
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnPlayQueueBtn
	功能		: 响应循环列表按钮点击事件并显示菜单
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnPlayQueueBtn(TNotifyUI& msg)						
{
	if(!m_pPlayListDlg->IsWindowVisible())
	{
		//调整坐标位置，以保证播放列表对话框在正确的位置显示
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
	函数名		: CMainWnd::OnCleanTextBtn
	功能		: 响应清除输入文字钮点并清除搜索框文字
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnCleanTextBtn(TNotifyUI& msg)		
{
	m_pEdtSearch->SetText(_T(""));			//清理搜索框的文字	
	m_pBtnCleanText->SetVisible(false);		//清理按钮设置为不可见
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnMusPlyTimSli
	功能		: 响应音乐播放进度条的点击事件
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnMusPlyTimSli(TNotifyUI& msg)
{
	if(!m_pCMediPly->IsOpen())
	{
		//设置音乐播放进度条的值
		m_pSliMusPlyTim->SetValue(m_pSliMusPlyTim->GetMinValue());
		return true;
	}
	if( !m_pCMediPly->IsPlaying() && m_pCMediPly->IsOpen())
	{
		if(!m_pCMediPly->Play())
			return true;
	}

	//设置播放按钮的状态
	SetPlayBtnIsPlay(TRUE);

	//指定音乐从音乐进度条的位置开始播放
	m_pCMediPly->SeekPosPly(m_pSliMusPlyTim->GetValue());
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnVoliceSli
	功能		: 响应声音进度条的点击事件
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnVoliceSli(TNotifyUI& msg)
{
	int Vol = GetVoiceSliVal();
	if(Vol == 0)
	{
		//将声音按钮控件图片设置为静音状态图片（静音）
		m_pBtnVolice->SetNormalImage(BTN_MINIBIG_CLOSE_STATE_PNG);
		m_bIsNoVol = TRUE;
	}
	else
	{
		m_bIsNoVol = FALSE;

		//设置播放音乐的声音大小
		m_pCMediPly->Volume(GetVoiceSliVal());

		//将声音按钮控件图片设置为正常状态图片
		m_pBtnVolice->SetNormalImage(BTN_MINIBIG_OPEN_STATE_PNG);
	}
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnMusiLibrOpt
	功能		: 响应音乐库页面推荐项点击事件，并显示推荐页页面
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnMusiLibrOpt(TNotifyUI& msg)
{
	m_pTabMusiLibr->SelectItem(0);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnMusiRankOpt
	功能		: 响应音乐库页面榜单项点击事件，并显示榜单页页面
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnMusiRankOpt(TNotifyUI& msg)
{
	m_pTabMusiLibr->SelectItem(1);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnPlyListOpt
	功能		: 响应音乐库页面歌单项点击事件，并显示歌单页页面
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnPlyListOpt(TNotifyUI& msg)
{
	m_pTabMusiLibr->SelectItem(2);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnBoarCastStaOpt
	功能		: 响应音乐库页面电台项点击事件，并显示电台页页面
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnBoarCastStaOpt(TNotifyUI& msg)
{
	m_pTabMusiLibr->SelectItem(3);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnSingerOpt
	功能		: 响应音乐库页面歌手项点击事件，并显示歌手页页面
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnSingerOpt(TNotifyUI& msg)
{
	m_pTabMusiLibr->SelectItem(4);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnClaFicOpt
	功能		: 响应音乐库页面分类项点击事件，并显示分类页页面
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnClaFicOpt(TNotifyUI& msg)
{
	m_pTabMusiLibr->SelectItem(5);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnLiveOpt
	功能		: 响应音乐库页面直播项点击事件，并显示直播页页面
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnLiveOpt(TNotifyUI& msg)
{
	m_pTabMusiLibr->SelectItem(6);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnOnlineMusicOpt
	功能		: 响应音乐库项点击事件，并显示音乐库页面
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnOnlineMusicOpt(TNotifyUI& msg)	
{
	m_pTabMusiList->SelectItem(0);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnActiveOpt
	功能		: 响应动态项点击事件，并显示动态页页面
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnActiveOpt(TNotifyUI& msg)
{
	m_pTabMusiList->SelectItem(1);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnTryListnMusicOpt
	功能		: 响应试听列表项点击事件，并显示试听列表页面
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnTryListnMusicOpt(TNotifyUI& msg)
{
	m_pTabMusiList->SelectItem(2);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnLocOpt
	功能		: 响应本地音乐项点击事件，并显示本地音乐页面
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnLocOpt(TNotifyUI& msg)	
{
	m_pTabMusiList->SelectItem(3);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnDowLoaOpt
	功能		: 响应歌曲下载项点击事件，并显示歌曲下载页面
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnDowLoaOpt(TNotifyUI& msg)
{
	m_pTabMusiList->SelectItem(4);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnRandPlayMod_MenuE
	功能		: 响应播放模式菜单随机播放事件，并设置播放模式为随机播放模式
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnRandPlayMod_MenuE(TNotifyUI& msg)
{
	SetPlayMode(emRandomPlay);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnLoopPlayMod_MenuE
	功能		: 响应播放模式菜单循环播放事件，并设置播放模式为循环播放模式
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnLoopPlayMod_MenuE(TNotifyUI& msg)
{
	SetPlayMode(emLoopPlay);		//设置列表循环播放模式
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnSinglePlayMod_MenuE
	功能		: 响应播放模式菜单单曲循环事件，并设置播放模式为单曲循环模式
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnSinglePlayMod_MenuE(TNotifyUI& msg)
{
	SetPlayMode(emSinglePlay);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnLisOrderPlayMod_MenuE
	功能		: 响应播放模式菜单列表循环事件，并设置播放模式为列表循环模式
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnLisOrderPlayMod_MenuE(TNotifyUI& msg)
{
	SetPlayMode(emOrderPlay);
	return true;
}

/*=========================================================================
	函数名		: CMainWnd::OnSearchEditSetFoc
	功能		: 响应搜索框获得焦点事件，并将清除搜索文字按钮置为可见状态
	算法实现	: 
	引用全局变量: 
	参数		: msg  消息结构体
	返回值		: bool 处理完成返回true，否则false
=========================================================================*/
bool CMainWnd::OnSearchEditSetFoc(TNotifyUI& msg)
{
	m_pBtnCleanText->SetVisible();
	return true;
}

UINT CMainWnd::GetClassStyle(void) const	
{
	//该类风格如果没有则会导致List列表双击无效
	return CS_DBLCLKS;
}

/*=========================================================================
	函数名		: CMainWnd::CreateMenuByXml
	功能		: 创建系统菜单
	算法实现	: 
	引用全局变量: 
	参数		: xml xml配置文件的全路径, pos创建好的菜单显示的位置
	返回值		: 
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

	//播放器对象实例化
	m_pCMediPly = new CMediPly(this);

	//创建播放列表对话框，初始隐藏
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

		//过滤标题栏上的控件
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
			//停止音乐播放
			m_pCMediPly->Stop();

			strPath += _T("\\");
			strPath += p->GetText(1);

			//m_strPlyName私有成员记录当前播放的媒体文件名
			m_strPlyName = p->GetText(1);

			m_pPlayListDlg->m_pLisPlay->SelectItem( m_pLisLocMusic->GetCurSel(), true);

			//把本地音乐列表中正在播放的音乐项的下标转化成CString类型
			strUserData.Format( _T("%d"), selectItem);

			m_pLisLocMusic->SetUserData(strUserData);	//设置用户数据
			StartPlay(strPath);
			return true;
		}	
	}

	else if(msg.sType == NOTIFY_KILLFOCUS)	//移除焦点通知
	{	
		CStdString str = msg.pSender->GetName();
		if(msg.pSender->GetName() == _T("MyLisEditId"))
		{	
			//添加自建歌单列表中Option控件选项
			AddListOption();
		}
	}
	else if(msg.sType == NOTIFY_MOUSEENTER)	//鼠标进入范围事件通知
	{
		//音乐库页面中的左翻右翻按钮控件的显示与隐藏
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
	函数名		: CMainWnd::GetLocMusPath
	功能		: 获取本地音乐文件夹路径
	算法实现	: 
	引用全局变量: 
	参数		: 
	返回值		: CStdString 本地音乐列表的文件夹路径
=========================================================================*/
CStdString CMainWnd::GetLocMusPath(void) const
{
	return m_strLisPath;
}

/*=========================================================================
	函数名		: CMainWnd::SetLocMusPath
	功能		: 设置本地音乐文件夹的路径
	算法实现	: 
	引用全局变量: 
	参数		: strPath 本地音乐列表的文件夹路径
	返回值		: 
=========================================================================*/
void CMainWnd::SetLocMusPath(LPCTSTR strPath)
{
	m_strLisPath = strPath;
}

/*=========================================================================
	函数名		: CMainWnd::OnOpenFileDlg
	功能		: 打开文件对话框
	算法实现	: 
	引用全局变量: 
	参数		: 
	返回值		: 
=========================================================================*/
void CMainWnd::OnOpenFileDlg()
{
	TCHAR szBuffer[MAX_PATH] = { 0 };  
	BROWSEINFO bi = { 0 };  
	bi.hwndOwner = m_hWnd;                  //拥有着窗口句柄，为NULL表示对话框是非模态的
	bi.pszDisplayName = szBuffer;			//接收文件夹的缓冲区 
	bi.lpszTitle = TEXT("选择一个文件夹");	//标题  
	bi.ulFlags = BIF_NEWDIALOGSTYLE;  
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);//浏览文件窗口
	if (!SHGetPathFromIDList( idl, szBuffer))  //获取选定的文件夹路径
	{  
		 return ;
	}

	CStdString strNum = _T("");
	_tfinddata_t file_info = {0};
	CString current_path(bi.pszDisplayName);
	SetLocMusPath(bi.pszDisplayName);			//设置当前音乐文件夹的全路径
	current_path += _T("/*.mp3");

	int handle = _tfindfirst( current_path, &file_info);//获取查找文件的句柄，开始查找文件

	if(-1 == handle)
	{
		return;
	}
	do 
	{
		//将遍历到的文件名加入本地音乐列表
		CListTextElementUI *ptextItem = new CListTextElementUI;	
		m_pLisLocMusic->AddAt( ptextItem, m_pLisLocMusic->GetCount());
		strNum.Format( _T("%d"), m_pLisLocMusic->GetCount());
		ptextItem->SetAttribute( _T("height"), _T("40"));
		ptextItem->SetText( 0, strNum);
		ptextItem->SetText( 1, file_info.name);
		ptextItem->SetText( 2, _T(""));
		ptextItem->SetText( 3, _T(""));
		ptextItem->SetText( 4, _T(""));

		//将遍历到的文件名加入播放音乐列表
		CListTextElementUI *pPlayLisItem = new CListTextElementUI;	
		m_pPlayListDlg->m_pLisPlay->AddAt( pPlayLisItem, m_pPlayListDlg->m_pLisPlay->GetCount());
		pPlayLisItem->SetAttribute( _T("height"), _T("40"));
		pPlayLisItem->SetText( 0, strNum);
		pPlayLisItem->SetText( 1, file_info.name);
		pPlayLisItem->SetText( 2, _T(""));

	} while (!_tfindnext( handle, &file_info));

	_findclose(handle);		//释放查找文件的句柄

	strNum.Format( _T("%d"), m_pLisLocMusic->GetCount());
	m_pLabPlyCount->SetText(strNum);
}

/*=========================================================================
	函数名		: CMainWnd::SetTotalTime
	功能		: 设置媒体文件的总时长
	算法实现	: 
	引用全局变量: 
	参数		: time 媒体文件的总时长
	返回值		: 
=========================================================================*/
void CMainWnd::SetTotalTime(UINT_PTR time)
{
	m_dwTotalTime = time;
}

/*=========================================================================
	函数名		: CMainWnd::SetBtnState
	功能		: 设置Btn图片，以代表列表开或闭
	算法实现	: 
	引用全局变量: 
	参数		: strBtnName 按钮控件的名
	返回值		: 
=========================================================================*/
void CMainWnd::SetBtnState(LPCTSTR strBtnName)
{
	//设置自建歌单打开或关闭的图标，若要设置其他控件请自行扩展
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
	函数名		: CMainWnd::AddListContainer
	功能		: 在List列表中加入一个Edit控件，用于临时内容的输入
	算法实现	: 
	引用全局变量: 
	参数		:
	返回值		: 
=========================================================================*/
void CMainWnd::AddListContainer(void)
{
	CString str = _T("");
	int pMLCount = m_pLisMusicList->GetCount();
	m_pLisConEle = new CListContainerElementUI();
	m_pLisConEle->SetAttribute( _T("height"), _T("36"));
	str.Format( _T("我的列表%d"), ++m_myCrelisEleCount);
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

	//创建的自建歌单列表从第8个开始添加
	m_pLisMusicList->AddAt( m_pLisConEle, m_myCrelisEleCount+8);
	m_pEdt->SetFocus();			
	m_pEdt->SetSelAll();
}

/*=========================================================================
	函数名		: CMainWnd::AddListOption
	功能		: 向列表中添加Option项
	算法实现	: 
	引用全局变量: 
	参数		: 
	返回值		: 
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
	函数名		: CMainWnd::CreateUserLoginDlg
	功能		: 创建用户登录对话框
	算法实现	: 
	引用全局变量: 
	参数		: 
	返回值		: 
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
	函数名		: CMainWnd::CreateSkinChangeDlg
	功能		: 创建更改皮肤对话框
	算法实现	: 
	引用全局变量: 
	参数		: pos 皮肤对话框显示的位置（客户区坐标）
	返回值		: 
=========================================================================*/
void CMainWnd::CreateSkinChangeDlg(CPoint& pos)
{
	ClientToScreen(m_hWnd,&pos);
	if(m_pSkiChaDlg)
	{
		RECT rc = {0};
		if(m_pSkiChaDlg->GetWindowRect(&rc))
		{
			//指定换肤对话框在指定的地方显示
			SetWindowPos( m_pSkiChaDlg->GetHWND(), m_hWnd
				, pos.x, pos.y, rc.right-rc.left, rc.bottom-rc.top, 0);
			m_pSkiChaDlg->ShowWindow(true);
		}
	}
	else
	{
		//创建换肤对话框在指定的地方并显示
		m_pSkiChaDlg = new CSkinChangeDlg(IDR_XML_SKIN_CHANG);
		m_pSkiChaDlg->Create( m_hWnd, _T("SkinChangeDlg"), UI_WNDSTYLE_DIALOG
			, WS_EX_DLGMODALFRAME, pos.x, pos.y, 0, 0, NULL);
		m_pSkiChaDlg->ShowWindow(true);
		m_pSkiChaDlg->SetActiveWindow();
	}
}

/*=========================================================================
	函数名		: CMainWnd::CreatePlayListDlg
	功能		: 创建播放列表对话框
	算法实现	: 
	引用全局变量: 
	参数		: 
	返回值		: 
=========================================================================*/
void CMainWnd::CreatePlayListDlg()
{
	//创建播放列表对话框类，初始隐藏
	m_pPlayListDlg = new CPlayListDlg(IDR_XML_PLAYLIST_DLG);		
	m_pPlayListDlg->Create( m_hWnd, _T("PlyLisDlg")
		, UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE, 0, 0, 300, 390, NULL);
	m_pPlayListDlg->ShowWindow(false);
}

/*=========================================================================
	函数名		: CMainWnd::SetListElementShow
	功能		: 设置自建歌单列表是否隐藏
	算法实现	: 
	引用全局变量: 
	参数		: visible 显示true,不显示false
	返回值		: 
=========================================================================*/
void CMainWnd::SetListElementShow(bool visible)
{
	//列表的第八个（包括第八个）为自建歌单的列表元素
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
	函数名		: CMainWnd::StartPlay
	功能		: 播放音乐
	算法实现	: 
	引用全局变量: 
	参数		: strFullPath 媒体文件全路径
	返回值		: 
=========================================================================*/
void CMainWnd::StartPlay(CString strFullPath)
{	
	if(!m_pCMediPly->IsOpen())	//打开播放器资源
	{
		// 根据全路径文件名播放媒体文件,失败则释放播放器资源
		if( !m_pCMediPly->Play((LPCSTR)m_pCMediPly->UnicodeToUTF8(strFullPath)) )
		{
			m_pCMediPly->Stop();
		}
	}

	if(!m_pCMediPly->IsPlaying() && m_pCMediPly->IsOpen())
	{
		// 播放媒体文件,成功则设置播放按钮的图片
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
	函数名		: CMainWnd::CreaLoopModeMenu
	功能		: 创建循环模式菜单并弹出显示
	引用全局变量: 
	参数		:
	返回值		: 
=========================================================================*/
void CMainWnd::CreaLoopModeMenu()
{
	CMenuWnd *pLoopModeMenu = new CMenuWnd( IDR_XML_MENU_MODE,_T("xml"), &m_pm);
	ASSERT(pLoopModeMenu);

	CMenuElementUI *pElement = new CMenuElementUI();
	pElement->SetName(_T("RandPlayMod_MenuE"));
	pElement->SetText(_T("随机播放"));
	pElement->SetFixedHeight(32);
	pLoopModeMenu->AddMenuItem(pElement);

	pElement = new CMenuElementUI();
	pElement->SetName(_T("LisOrderPlayMod_MenuE"));
	pElement->SetText(_T("顺序播放"));
	pElement->SetFixedHeight(32);
	pLoopModeMenu->AddMenuItem(pElement);

	pElement = new CMenuElementUI();
	pElement->SetName(_T("SinglePlayMod_MenuE"));
	pElement->SetText(_T("单曲循环"));
	pElement->SetFixedHeight(32);
	pLoopModeMenu->AddMenuItem(pElement);

	pElement = new CMenuElementUI();
	pElement->SetName(_T("LoopPlayMod_MenuE"));
	pElement->SetText(_T("列表循环"));
	pElement->SetFixedHeight(32);
	pLoopModeMenu->AddMenuItem(pElement);

	CPoint pos;
	pos.SetPoint( m_pBtnCycleLis->GetPos().left, m_pBtnCycleLis->GetPos().top);
	ClientToScreen( m_hWnd, &pos);
	pLoopModeMenu->TrackPopupMenu( eMenuAlignment_Right|eMenuAlignment_Bottom, pos, m_hWnd);
}

/*=========================================================================
	函数名		: CMainWnd::SetPlayMode
	功能		: 设置播放模式
	引用全局变量: 
	参数		: dMode 播放模式
	返回值		: 
=========================================================================*/
void CMainWnd::SetPlayMode(emLoopMod dMode)
{
	m_emLoopMod = dMode;	//记录播放模式{顺序、循环...}
	switch(dMode)
	{
		case emRandomPlay:
			{
				//随机播放按钮图片状态
				m_pBtnCycleLis->SetNormalImage(PLAY_MODE_RAND_PNG);
				m_pBtnCycleLis->SetToolTip(_T("随机播放"));
			}
			break;	

		case emOrderPlay:
			{
				//顺序播放按钮图片状态
				m_pBtnCycleLis->SetNormalImage(PLAY_MODE_NEXT_PNG);
				m_pBtnCycleLis->SetToolTip(_T("顺序播放"));
			}  
			break;	

		case emSinglePlay:
			{
				//单曲循环播放按钮图片状态
				m_pBtnCycleLis->SetNormalImage(PLAY_MODE_SINGLE_PNG);
				m_pBtnCycleLis->SetToolTip(_T("单曲循环"));
			}
			break;	

		case emLoopPlay:
			{
				//列表循环播放按钮图片状态
				m_pBtnCycleLis->SetNormalImage(PLAY_MODE_CIRCLE_PNG);
				m_pBtnCycleLis->SetToolTip(_T("列表循环"));
			}
			break;	

		default:
			break;
	}
}

/*=========================================================================
	函数名		: CMainWnd::GetCurrentPlayName
	功能		: 获取当前播放音乐的名字
	引用全局变量: 
	参数		:
	返回值		: CStdString 当前正在播放音乐的名字
=========================================================================*/
CStdString CMainWnd::GetCurrentPlayName(void) const
{
	return m_strPlyName;
}

/*=========================================================================
	函数名		: CMainWnd::LoopPlay
	功能		: 本地列表循环播放
	引用全局变量: 
	参数		:
	返回值		: 
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

			//选中本地音乐列表中下标为nSelected+1的项
			m_pLisLocMusic->SelectItem( nSelected+1, true); 	
		}
		else
		{
			pTextEle = (CListTextElementUI*)m_pLisLocMusic->GetItemAt(0);
			strPlayName = GetLocMusPath()+_T("\\");
			strPlayName += (CString)pTextEle->GetText(1);

			//选中本地音乐列表中下标为0的项
			m_pLisLocMusic->SelectItem( 0, true); 	
		}

		//设置播放列表中该项为选中状态
		m_pPlayListDlg->m_pLisPlay->SelectItem( m_pLisLocMusic->GetCurSel(), true);

		//将本地音乐列表中正在播放的音乐的下标设置为用户数据，供后面GetUserData使用
		strUserData.Format( _T("%d"), m_pLisLocMusic->GetCurSel());
		m_pLisLocMusic->SetUserData(strUserData);	

		StartPlay(strPlayName);
	}
}

/*=========================================================================
	函数名		: CMainWnd::RandomPlay
	功能		: 本地列表随机播放
	引用全局变量: 
	参数		:
	返回值		: 
=========================================================================*/
void CMainWnd::RandomPlay()					
{
	CString strUserData = _T("");

	//获取本地音乐列表中的音乐的数量
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

		//选中本地音乐列表中下标为nSelected的项
		m_pLisLocMusic->SelectItem(nSelected, true);

		//设置播放列表中该项为选中状态
		m_pPlayListDlg->m_pLisPlay->SelectItem( m_pLisLocMusic->GetCurSel(), true);

		//将本地音乐列表中正在播放的音乐的下标设置用户数据，供后面GetUserData使用
		strUserData.Format( _T("%d"), m_pLisLocMusic->GetCurSel());
		m_pLisLocMusic->SetUserData(strUserData);	

		StartPlay(strPlayName);		
	}
}

/*=========================================================================
	函数名		: CMainWnd::OrderPlay
	功能		: 列表顺序播放
	引用全局变量: 
	参数		:
	返回值		: 
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

			//选中本地音乐列表中下标为nSelected+1的项
			m_pLisLocMusic->SelectItem(nSelected+1,true);

			//设置播放列表中该项为选中状态
			m_pPlayListDlg->m_pLisPlay->SelectItem( m_pLisLocMusic->GetCurSel(), true);

			//将本地音乐列表中正在播放的音乐的下标设置用户数据，供后面GetUserData使用
			strUserData.Format( _T("%d"), m_pLisLocMusic->GetCurSel());
			m_pLisLocMusic->SetUserData(strUserData);	

			StartPlay(strPlayName);
		}	
	}
}

/*=========================================================================
	函数名		: CMainWnd::SinglePlay
	功能		: 单曲循环播放
	引用全局变量: 
	参数		:
	返回值		: 
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

			//选中本地音乐列表中下标为nSelected的项
			m_pLisLocMusic->SelectItem(nSelected,true); 	

			//设置播放列表中该项为选中状态
			m_pPlayListDlg->m_pLisPlay->SelectItem(m_pLisLocMusic->GetCurSel(),true);

			//将本地音乐列表中正在播放的音乐的下标设置用户数据，供后面GetUserData使用
			strUserData.Format(_T("%d"),m_pLisLocMusic->GetCurSel());
			m_pLisLocMusic->SetUserData(strUserData);	

			StartPlay(strPlayName);
		}
	}
}

/*=========================================================================
	函数名		: CMainWnd::GetPlyMod
	功能		: 获得播放模式
	引用全局变量: 
	参数		:
	返回值		: emLoopMod 枚举类型，代表当前音乐的播放模式
=========================================================================*/
emLoopMod CMainWnd::GetPlyMod(void) const
{
	return m_emLoopMod;
}

/*=========================================================================
	函数名		: CMainWnd::GetCurrentPlayName
	功能		: 设置当前音乐播放的时间和音乐播放进度条的位置
	引用全局变量: 
	参数		:
	返回值		: 
=========================================================================*/
void CMainWnd::SetMusTime()
{
	 //获取当前播放的音乐位置
	UINT_PTR curPos = m_pCMediPly->GetTime();
	CString strTime;
	if(m_dwTotalTime == 0)
	{
		return;
	}
	else
	{
		//音乐播放进度条的位置
		int slipos = curPos*m_pSliMusPlyTim->GetMaxValue()/m_dwTotalTime; 
		UINT_PTR sec = curPos/1000%60;				                
		UINT_PTR min = curPos/1000/60;

		//转化成（分：秒）格式
		strTime.Format( _T("%0.2d:%0.2d"), min, sec);

		//显示播放的时间
		m_pBtnCurTim->SetText(strTime);

		//设置播放进度条的位置
		m_pSliMusPlyTim->SetValue(slipos);
	}
}

/*=========================================================================
	函数名		: CMainWnd::SetMusSliVal
	功能		: 设置音乐进度条的位置
	引用全局变量: 
	参数		: pos 音乐进度条的位置值
	返回值		:
=========================================================================*/
void CMainWnd::SetMusSliVal(int pos)
{
	m_pSliMusPlyTim->SetValue(pos);
}

/*=========================================================================
	函数名		: CMainWnd::GetMusSliVal
	功能		: 获取音乐进度条的值
	引用全局变量: 
	参数		: 
	返回值		: int 音乐进度条的位置值
=========================================================================*/
int CMainWnd::GetMusSliVal() const
{
	return m_pSliMusPlyTim->GetValue();
}

/*=========================================================================
	函数名		: CMainWnd::SetVoiceSliVal
	功能		: 设置声音进度条的值
	引用全局变量: 
	参数		: pos 声音进度条的位置值
	返回值		:
=========================================================================*/
void CMainWnd::SetVoiceSliVal(int pos) const
{
	m_pSliVolice->SetValue(pos);
}

/*=========================================================================
	函数名		: CMainWnd::GetVoiceSliVal
	功能		: 获取声音进度条的值
	引用全局变量: 
	参数		:
	返回值		: int 声音进度条的位置值
=========================================================================*/
int CMainWnd::GetVoiceSliVal() const
{
	return m_pSliVolice->GetValue();
}

/*=========================================================================
	函数名		: CMainWnd::SetPlayBtnIsPlay
	功能		: 设置播放按钮的的状态图片
	引用全局变量: 
	参数		: isPlaying 当前是否在播放音乐
	返回值		: 
=========================================================================*/
void CMainWnd::SetPlayBtnIsPlay(BOOL isPlaying)
{
	if(isPlaying)
	{
		//设置为正在播放状态图片
		m_pBtnPlay->SetNormalImage(BTN_PLAY_PNG);
	}
	else
	{
		//设置为暂停播放状态图片
		m_pBtnPlay->SetNormalImage(BTN_PAUSE_PNG);
	}
}


