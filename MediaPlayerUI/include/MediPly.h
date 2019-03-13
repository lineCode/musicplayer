/******************************************************************************
	ģ����      : mediaplay
	�ļ���      : CMediPly.h
	����ļ�    : MainWnd.h
	�ļ�ʵ�ֹ���: ���ֲ��Ź��ܽӿ���
	����        : ���Ŀ�
	�汾        : 
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��      �汾        �޸���      �޸�����
	2017/3/1                ���Ŀ�        ����
******************************************************************************/

#ifndef CMEDIPLY_H
#define CMEDIPLY_H

#include"stdafx.h"

typedef void (* pfnCallback) (void *data);  // VLC�¼��Ļص�����ָ��

/** ö�����ֲ���ģʽ */
typedef enum EmLoopMod{
	emRandomPlay = 0,  //���
	emOrderPlay,       //˳��
	emSinglePlay,      //����
	emLoopPlay         //ѭ��
}emLoopMod;

class CMediPly
{
public:
	CMediPly(void *data);
	~CMediPly(void);

	static void  StartPlayingCall(void* data);   //���ֿ�ʼ����ʱ�ص�
	static void  PosChangeCall(void* data);      // �ļ�λ�øı�ʱ�Ļص�����
	static void  EndReachedCall(void* data);     // �ļ�������ϵĻص�����

	static CStringA UnicodeToUTF8(const CStringW& strWide);

public:
	BOOL Play();                           // ����
	void Pause();                          // ��ͣ
	void Stop();                           // ֹͣ
	BOOL Play(const std::string &strPath); // ����·��ΪstrPath���ļ�
	void SeekPosPly(DWORD_PTR dPosition);  //���������ڸ�λ�ò���
	void *m_pwnd;

	// VLC���¼�����
	static void OnVLC_Event(const libvlc_event_t *event, void *data);

	int     GetPos(void);               // ��ȡ�ļ���ǰ���ŵ�λ��
	BOOL    IsOpen(void);               // �ļ��Ƿ��
	BOOL    IsPlaying(void);            // �ļ��Ƿ����ڲ���
	UINT_PTR GetTotalTime(void);        // ��ȡ��ʱ��
	UINT_PTR GetTime(void);             // ��ȡʱ��

	int     GetVolume(void);            // ��ȡ����
	BOOL Volume(int iVol);              // ��������ΪiVol
	void VolumeIncrease(void);          // ��������
	void VolumeReduce(void);            // ������С
	void ReleaseMedia(void);			//����ý�岥���������ü�����ʾ�ͷ���Դ
	void Release(void);					//�ͷŲ�������Դ

private:
	libvlc_instance_t       *m_pVLC_Inst;   // VLCʵ��
	libvlc_media_player_t   *m_pVLC_Player; // VLC������
	libvlc_media_t          *m_media;

};

#endif