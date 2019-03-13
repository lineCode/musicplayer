/******************************************************************************
	模块名      : mediaplay
	文件名      : CMediPly.h
	相关文件    : MainWnd.h
	文件实现功能: 音乐播放功能接口类
	作者        : 熊文凯
	版本        : 
	-------------------------------------------------------------------------------
	修改记录:
	日  期      版本        修改人      修改内容
	2017/3/1                熊文凯        创建
******************************************************************************/

#ifndef CMEDIPLY_H
#define CMEDIPLY_H

#include"stdafx.h"

typedef void (* pfnCallback) (void *data);  // VLC事件的回调函数指针

/** 枚举音乐播放模式 */
typedef enum EmLoopMod{
	emRandomPlay = 0,  //随机
	emOrderPlay,       //顺序
	emSinglePlay,      //单曲
	emLoopPlay         //循环
}emLoopMod;

class CMediPly
{
public:
	CMediPly(void *data);
	~CMediPly(void);

	static void  StartPlayingCall(void* data);   //音乐开始播放时回调
	static void  PosChangeCall(void* data);      // 文件位置改变时的回调函数
	static void  EndReachedCall(void* data);     // 文件播放完毕的回调函数

	static CStringA UnicodeToUTF8(const CStringW& strWide);

public:
	BOOL Play();                           // 播放
	void Pause();                          // 暂停
	void Stop();                           // 停止
	BOOL Play(const std::string &strPath); // 播放路径为strPath的文件
	void SeekPosPly(DWORD_PTR dPosition);  //设置音乐在该位置播放
	void *m_pwnd;

	// VLC的事件管理
	static void OnVLC_Event(const libvlc_event_t *event, void *data);

	int     GetPos(void);               // 获取文件当前播放的位置
	BOOL    IsOpen(void);               // 文件是否打开
	BOOL    IsPlaying(void);            // 文件是否正在播放
	UINT_PTR GetTotalTime(void);        // 获取总时间
	UINT_PTR GetTime(void);             // 获取时间

	int     GetVolume(void);            // 获取音量
	BOOL Volume(int iVol);              // 音量设置为iVol
	void VolumeIncrease(void);          // 音量增大
	void VolumeReduce(void);            // 音量减小
	void ReleaseMedia(void);			//保留媒体播放器的引用计数并示释放资源
	void Release(void);					//释放播放器资源

private:
	libvlc_instance_t       *m_pVLC_Inst;   // VLC实例
	libvlc_media_player_t   *m_pVLC_Player; // VLC播放器
	libvlc_media_t          *m_media;

};

#endif