/******************************************************************************
	模块名      : mediaplay
	文件名      : MediPly.cpp
	相关文件    : MediPly.h
	文件实现功能: 实现音乐播放功能
	作者        : 熊文凯
	版本        : 
	-------------------------------------------------------------------------------
	修改记录:
	日  期      版本        修改人      修改内容
	2017/3/1                熊文凯        创建
******************************************************************************/

#include "MediPly.h"
#include"MainWnd.h"

CMediPly::CMediPly(void *data)
:m_pVLC_Inst(NULL)
,m_pVLC_Player(NULL)
,m_media(NULL)
{
	m_pwnd = data;
}

CMediPly::~CMediPly(void)
{
	Release();
}

/*=========================================================================
	函数名		: CMediPly::Play
	功能		: 播放
	引用全局变量: 
	参数		: 
	返回值		: BOOL 成功返回TRUE，否则FALSE
=========================================================================*/
BOOL CMediPly::Play (void)
{
	if (m_pVLC_Player)
	{
		return 0 == libvlc_media_player_play(m_pVLC_Player);
	}
	return FALSE;
}

/*=========================================================================
	函数名		: CMediPly::Pause
	功能		: 暂停播放
	引用全局变量: 
	参数		: 
	返回值		: 
=========================================================================*/  
void CMediPly::Pause(void)                          
{
	if (m_pVLC_Player)
	{
		libvlc_media_player_pause(m_pVLC_Player);
	}
}

/*=========================================================================
	函数名		: CMediPly::Stop
	功能		: 停止播放
	引用全局变量: 
	参数		: 
	返回值		: 
=========================================================================*/  
void CMediPly::Stop (void)
{
	if (m_pVLC_Player)
	{
		libvlc_media_player_stop (m_pVLC_Player);      //停止播放   
		libvlc_media_player_release (m_pVLC_Player);   //释放媒体资源
		m_pVLC_Player = NULL;
	}
}

/*=========================================================================
	函数名		: CMediPly::Play
	功能		: 播放媒体文件
	引用全局变量: 
	参数		: strPath 媒体文件路径
	返回值		: BOOL 成功返回TRUE，否则FALSE
=========================================================================*/  
BOOL CMediPly::Play(const std::string &strPath)  
{
	if (! m_pVLC_Inst)
	{
		m_pVLC_Inst = libvlc_new(0, NULL);
	}

	if(strPath.empty() || ! m_pVLC_Inst)
	{
		return false;
	}

	Stop();

	BOOL bRet = FALSE;

	m_media = libvlc_media_new_path(m_pVLC_Inst, strPath.c_str());

	if (m_media)
	{
		if (m_pVLC_Player = libvlc_media_player_new_from_media(m_media))
		{
			libvlc_media_player_play(m_pVLC_Player);

			// 事件管理
			libvlc_event_manager_t *vlc_evt_man = libvlc_media_player_event_manager(m_pVLC_Player);
			libvlc_event_attach( vlc_evt_man, libvlc_MediaPlayerPlaying, OnVLC_Event, this);
			libvlc_event_attach( vlc_evt_man, libvlc_MediaPlayerPositionChanged, OnVLC_Event, this);
			libvlc_event_attach( vlc_evt_man, libvlc_MediaPlayerEndReached, OnVLC_Event, this);
			bRet = true;
		}

		libvlc_media_release(m_media);
	}
	return bRet;
}

/*=========================================================================
	函数名		: CMediPly::SeekPosPly
	功能		: 指定位置开始播放音乐
	引用全局变量: 
	参数		: dPosition 指定媒体播放的位置
	返回值		: 
=========================================================================*/ 
void CMediPly::SeekPosPly(DWORD_PTR dPosition)
{
	if (dPosition < 0 || dPosition > 1000)
	{
		return;
	}
	if (m_pVLC_Player)
	{
		libvlc_media_player_set_position( m_pVLC_Player, dPosition/(float)1000.0);
	}
}

/*=========================================================================
	函数名		: CMediPly::OnVLC_Event
	功能		: 响应VLC播放器事件
	引用全局变量: 
	参数		: event vlc播放器事件消息， data传入参数的指针
	返回值		: 
=========================================================================*/ 
void CMediPly::OnVLC_Event( const libvlc_event_t *event, void *data)
{
	CMediPly *pAVPlayer = (CMediPly *) data;
	pfnCallback pfn = NULL;
	if (! pAVPlayer)
	{
		return;
	}
	switch(event->type)
	{
	case libvlc_MediaPlayerPlaying:			//媒体文件正在播放时的回调事件
		{
            pfn = pAVPlayer->StartPlayingCall;
		}
		break;

	case libvlc_MediaPlayerPositionChanged:	//媒体播放位置改变
		{
            pfn = pAVPlayer->PosChangeCall;
		}
		break;

	case libvlc_MediaPlayerEndReached:		//文件播放完毕的回调
		{
            pfn = pAVPlayer->EndReachedCall;
		}		
		break;

	default:
		break;
	}
	if (pfn)
	{
		/*
		*此回调函数还可以传入其他参数，除了data外，还有event的各种信息
		*（如event->u.media_player_position_changed.new_position）等等
		*/
		pfn(data);  
	}   
}

/*=========================================================================
	函数名		: CMediPly::GetPos
	功能		: 获取文件当前播放的位置
	引用全局变量: 
	参数		: 
	返回值		: int 媒体文件播放的位置
=========================================================================*/ 
int CMediPly::GetPos(void)                       
{
	if (m_pVLC_Player)
	{
		return (int)(1000*libvlc_media_player_get_position(m_pVLC_Player));
	}
	return 0;
}

/*=========================================================================
	函数名		: CMediPly::IsOpen
	功能		: 文件是否打开
	引用全局变量: 
	参数		: 
	返回值		: BOOL 媒体文件已打开返回TRUE,否则FALSE
=========================================================================*/ 
BOOL CMediPly::IsOpen(void)                      
{
	return NULL != m_pVLC_Player;
}

/*=========================================================================
	函数名		: CMediPly::IsPlaying
	功能		: 文件是否正在播放
	引用全局变量: 
	参数		: 
	返回值		: BOOL 正在播放返回TRUE,否则FALSE
=========================================================================*/  
BOOL CMediPly::IsPlaying(void)
{
	if (m_pVLC_Player)
	{
		return (1 == libvlc_media_player_is_playing(m_pVLC_Player));
	}

	return false;
}

/*=========================================================================
	函数名		: CMediPly::GetTotalTime
	功能		: 获取媒体文件总长度
	引用全局变量: 
	参数		: 
	返回值		: UINT_PTR 媒体文件的总长度大小值
=========================================================================*/  
UINT_PTR CMediPly::GetTotalTime(void)
{
	if (m_pVLC_Player)
	{
		return (UINT_PTR )libvlc_media_player_get_length(m_pVLC_Player);
	}

	return 0;
}

/*=========================================================================
	函数名		: CMediPly::GetTime
	功能		: 获取时间
	引用全局变量: 
	参数		: 
	返回值		: UINT_PTR 播放媒体文件当前已播放的时间
=========================================================================*/  
UINT_PTR CMediPly::GetTime(void)
{
	if (m_pVLC_Player)
	{
		return (UINT_PTR )libvlc_media_player_get_time(m_pVLC_Player);
	}

	return 0;
}

/*=========================================================================
	函数名		: CMediPly::GetVolume
	功能		: 获取音量
	引用全局变量: 
	参数		: 
	返回值		: int 播放媒体文件的声音大小
=========================================================================*/ 
int CMediPly::GetVolume(void)
{
	if (m_pVLC_Player)
	{
		return libvlc_audio_get_volume(m_pVLC_Player);
	}
	return 0;
}

/*=========================================================================
	函数名		: CMediPly::Volume
	功能		: 设置媒体播放额声音
	引用全局变量: 
	参数		: iVol 播放媒体文件的声音大小
	返回值		: 
=========================================================================*/
BOOL CMediPly::Volume(int iVol)
{
	if (iVol < 0)
	{
		return FALSE;
	} 

	if (m_pVLC_Player)
	{
		return libvlc_audio_set_volume( m_pVLC_Player, int(iVol)) == 0 ? TRUE : FALSE;
	}
	return FALSE;
}

/*=========================================================================
	函数名		: CMediPly::ReleaseMedia
	功能		: 增加声音音量
	引用全局变量: 
	参数		: 
	返回值		: 
=========================================================================*/
void CMediPly::VolumeIncrease(void)
{
	if (m_pVLC_Player)
	{
		int iVol = libvlc_audio_get_volume(m_pVLC_Player);
		
		//设置声音值为大于或等于（iVol * 1.1）的整数
		Volume((int)ceil(iVol * 1.1));
	}
}

/*=========================================================================
	函数名		: CMediPly::ReleaseMedia
	功能		: 降低声音音量
	引用全局变量: 
	参数		: 
	返回值		: 
=========================================================================*/
void CMediPly::VolumeReduce(void)
{
	if (m_pVLC_Player)
	{
		int iVol = libvlc_audio_get_volume(m_pVLC_Player);

		//设置声音值为小于或等于（iVol * 0.9）的整数
		Volume((int)floor(iVol * 0.9));
	}
}

/*=========================================================================
	函数名		: CMediPly::ReleaseMedia
	功能		: 减少播放器对象的引用计数，并释放播放对象资源
	引用全局变量: 
	参数		: 
	返回值		: 
=========================================================================*/
void CMediPly::ReleaseMedia(void)
{
	if(m_pVLC_Player)
	{
		//保留媒体播放对象的引用计数
		libvlc_media_player_retain(m_pVLC_Player);

		//释放媒体播放对象的引用计数
		libvlc_media_player_release(m_pVLC_Player);
		m_pVLC_Player = NULL;
	}
}

/*=========================================================================
	函数名		: CMediPly::Release
	功能		: 将CStringW转化为CStringA
	引用全局变量: 
	参数		: strWide CStringW字符串
	返回值		: CStringA 转化后的字符串
=========================================================================*/
CStringA CMediPly::UnicodeToUTF8(const CStringW& strWide)
{
	CStringA strUTF8 = "";
	int nLen = ::WideCharToMultiByte( CP_UTF8, 0, strWide, -1
		, NULL, 0, NULL, NULL);

	if (nLen > 1)
	{
		::WideCharToMultiByte( CP_UTF8, 0, strWide, -1
			, strUTF8.GetBuffer(nLen - 1), nLen, NULL, NULL);
		strUTF8.ReleaseBuffer();
	}
	
	return strUTF8;
}

/*=========================================================================
	函数名		: CMediPly::Release
	功能		: 释放并摧毁VLC实例
	引用全局变量: 
	参数		:
	返回值		: 
=========================================================================*/
void CMediPly::Release(void)
{
	Stop();

	if (m_pVLC_Inst)
	{
		//减少libvlc的引用计数并摧毁它
		libvlc_release (m_pVLC_Inst);
		m_pVLC_Inst = NULL;
	}
}

/*=========================================================================
	函数名		: CMediPly::PosChangeCall
	功能		: 音乐开始播放时回调
	引用全局变量: 
	参数		: data 传入的数据指针
	返回值		: 
=========================================================================*/
void CMediPly::StartPlayingCall(void* data)
{
	CMediPly *pme = (CMediPly*)data;
	CMainWnd *pfw = (CMainWnd*)pme->m_pwnd;

	//将媒体文件的总时间获取并设置在CMainWnd类成员中
	pfw->SetTotalTime(pme->GetTotalTime());
}

/*=========================================================================
	函数名		: CMediPly::PosChangeCall
	功能		: 文件位置改变时的回调函数
	引用全局变量: 
	参数		: data 传入的数据指针
	返回值		: 
=========================================================================*/
void CMediPly::PosChangeCall(void* data)
{
	CMediPly *pme = (CMediPly*)data;
	CMainWnd *pfw = (CMainWnd*)pme->m_pwnd;

	//设置并显示主界面中媒体文件的播放时间
	pfw->SetMusTime();
	
	//此处设置媒体文件开始播放初始音量值
	//不在音乐开始播放时回调函数中设置的原因是在发布版本下播放声音的初始值会无效
	static BOOL areadySetVolic=FALSE;
	if(areadySetVolic == FALSE)
	{
		areadySetVolic=pme->Volume(pfw->GetVoiceSliVal());
	}		
}


/*=========================================================================
	函数名		: CMediPly::EndReachedCall
	功能		: 文件播放完毕的回调函数
	引用全局变量: 
	参数		: data 传入的数据指针
	返回值		: 
=========================================================================*/ 
void CMediPly::EndReachedCall(void* data)
{
	CMediPly *pme = (CMediPly*)data; 
	CMainWnd *pfw = (CMainWnd*)pme->m_pwnd;
	pme->ReleaseMedia();

	//将音乐播放进度条设置为初始位置0
	pfw->SetMusSliVal(0);

	//设置播放按钮状态
	pfw->SetPlayBtnIsPlay(FALSE);
	
	switch(pfw->GetPlyMod())
	{
	case emRandomPlay:	 pfw->RandomPlay();   break;	//随机播放
	case emOrderPlay:	 pfw->OrderPlay();	 break;	//顺序播放
	case emSinglePlay:	 pfw->SinglePlay();   break;	//单曲循环
	case emLoopPlay:	 pfw->LoopPlay();     break;	//列表循环播放
	default:
		break;
	}
}