/******************************************************************************
	ģ����      : mediaplay
	�ļ���      : MediPly.cpp
	����ļ�    : MediPly.h
	�ļ�ʵ�ֹ���: ʵ�����ֲ��Ź���
	����        : ���Ŀ�
	�汾        : 
	-------------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��      �汾        �޸���      �޸�����
	2017/3/1                ���Ŀ�        ����
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
	������		: CMediPly::Play
	����		: ����
	����ȫ�ֱ���: 
	����		: 
	����ֵ		: BOOL �ɹ�����TRUE������FALSE
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
	������		: CMediPly::Pause
	����		: ��ͣ����
	����ȫ�ֱ���: 
	����		: 
	����ֵ		: 
=========================================================================*/  
void CMediPly::Pause(void)                          
{
	if (m_pVLC_Player)
	{
		libvlc_media_player_pause(m_pVLC_Player);
	}
}

/*=========================================================================
	������		: CMediPly::Stop
	����		: ֹͣ����
	����ȫ�ֱ���: 
	����		: 
	����ֵ		: 
=========================================================================*/  
void CMediPly::Stop (void)
{
	if (m_pVLC_Player)
	{
		libvlc_media_player_stop (m_pVLC_Player);      //ֹͣ����   
		libvlc_media_player_release (m_pVLC_Player);   //�ͷ�ý����Դ
		m_pVLC_Player = NULL;
	}
}

/*=========================================================================
	������		: CMediPly::Play
	����		: ����ý���ļ�
	����ȫ�ֱ���: 
	����		: strPath ý���ļ�·��
	����ֵ		: BOOL �ɹ�����TRUE������FALSE
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

			// �¼�����
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
	������		: CMediPly::SeekPosPly
	����		: ָ��λ�ÿ�ʼ��������
	����ȫ�ֱ���: 
	����		: dPosition ָ��ý�岥�ŵ�λ��
	����ֵ		: 
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
	������		: CMediPly::OnVLC_Event
	����		: ��ӦVLC�������¼�
	����ȫ�ֱ���: 
	����		: event vlc�������¼���Ϣ�� data���������ָ��
	����ֵ		: 
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
	case libvlc_MediaPlayerPlaying:			//ý���ļ����ڲ���ʱ�Ļص��¼�
		{
            pfn = pAVPlayer->StartPlayingCall;
		}
		break;

	case libvlc_MediaPlayerPositionChanged:	//ý�岥��λ�øı�
		{
            pfn = pAVPlayer->PosChangeCall;
		}
		break;

	case libvlc_MediaPlayerEndReached:		//�ļ�������ϵĻص�
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
		*�˻ص����������Դ�����������������data�⣬����event�ĸ�����Ϣ
		*����event->u.media_player_position_changed.new_position���ȵ�
		*/
		pfn(data);  
	}   
}

/*=========================================================================
	������		: CMediPly::GetPos
	����		: ��ȡ�ļ���ǰ���ŵ�λ��
	����ȫ�ֱ���: 
	����		: 
	����ֵ		: int ý���ļ����ŵ�λ��
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
	������		: CMediPly::IsOpen
	����		: �ļ��Ƿ��
	����ȫ�ֱ���: 
	����		: 
	����ֵ		: BOOL ý���ļ��Ѵ򿪷���TRUE,����FALSE
=========================================================================*/ 
BOOL CMediPly::IsOpen(void)                      
{
	return NULL != m_pVLC_Player;
}

/*=========================================================================
	������		: CMediPly::IsPlaying
	����		: �ļ��Ƿ����ڲ���
	����ȫ�ֱ���: 
	����		: 
	����ֵ		: BOOL ���ڲ��ŷ���TRUE,����FALSE
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
	������		: CMediPly::GetTotalTime
	����		: ��ȡý���ļ��ܳ���
	����ȫ�ֱ���: 
	����		: 
	����ֵ		: UINT_PTR ý���ļ����ܳ��ȴ�Сֵ
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
	������		: CMediPly::GetTime
	����		: ��ȡʱ��
	����ȫ�ֱ���: 
	����		: 
	����ֵ		: UINT_PTR ����ý���ļ���ǰ�Ѳ��ŵ�ʱ��
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
	������		: CMediPly::GetVolume
	����		: ��ȡ����
	����ȫ�ֱ���: 
	����		: 
	����ֵ		: int ����ý���ļ���������С
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
	������		: CMediPly::Volume
	����		: ����ý�岥�Ŷ�����
	����ȫ�ֱ���: 
	����		: iVol ����ý���ļ���������С
	����ֵ		: 
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
	������		: CMediPly::ReleaseMedia
	����		: ������������
	����ȫ�ֱ���: 
	����		: 
	����ֵ		: 
=========================================================================*/
void CMediPly::VolumeIncrease(void)
{
	if (m_pVLC_Player)
	{
		int iVol = libvlc_audio_get_volume(m_pVLC_Player);
		
		//��������ֵΪ���ڻ���ڣ�iVol * 1.1��������
		Volume((int)ceil(iVol * 1.1));
	}
}

/*=========================================================================
	������		: CMediPly::ReleaseMedia
	����		: ������������
	����ȫ�ֱ���: 
	����		: 
	����ֵ		: 
=========================================================================*/
void CMediPly::VolumeReduce(void)
{
	if (m_pVLC_Player)
	{
		int iVol = libvlc_audio_get_volume(m_pVLC_Player);

		//��������ֵΪС�ڻ���ڣ�iVol * 0.9��������
		Volume((int)floor(iVol * 0.9));
	}
}

/*=========================================================================
	������		: CMediPly::ReleaseMedia
	����		: ���ٲ�������������ü��������ͷŲ��Ŷ�����Դ
	����ȫ�ֱ���: 
	����		: 
	����ֵ		: 
=========================================================================*/
void CMediPly::ReleaseMedia(void)
{
	if(m_pVLC_Player)
	{
		//����ý�岥�Ŷ�������ü���
		libvlc_media_player_retain(m_pVLC_Player);

		//�ͷ�ý�岥�Ŷ�������ü���
		libvlc_media_player_release(m_pVLC_Player);
		m_pVLC_Player = NULL;
	}
}

/*=========================================================================
	������		: CMediPly::Release
	����		: ��CStringWת��ΪCStringA
	����ȫ�ֱ���: 
	����		: strWide CStringW�ַ���
	����ֵ		: CStringA ת������ַ���
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
	������		: CMediPly::Release
	����		: �ͷŲ��ݻ�VLCʵ��
	����ȫ�ֱ���: 
	����		:
	����ֵ		: 
=========================================================================*/
void CMediPly::Release(void)
{
	Stop();

	if (m_pVLC_Inst)
	{
		//����libvlc�����ü������ݻ���
		libvlc_release (m_pVLC_Inst);
		m_pVLC_Inst = NULL;
	}
}

/*=========================================================================
	������		: CMediPly::PosChangeCall
	����		: ���ֿ�ʼ����ʱ�ص�
	����ȫ�ֱ���: 
	����		: data ���������ָ��
	����ֵ		: 
=========================================================================*/
void CMediPly::StartPlayingCall(void* data)
{
	CMediPly *pme = (CMediPly*)data;
	CMainWnd *pfw = (CMainWnd*)pme->m_pwnd;

	//��ý���ļ�����ʱ���ȡ��������CMainWnd���Ա��
	pfw->SetTotalTime(pme->GetTotalTime());
}

/*=========================================================================
	������		: CMediPly::PosChangeCall
	����		: �ļ�λ�øı�ʱ�Ļص�����
	����ȫ�ֱ���: 
	����		: data ���������ָ��
	����ֵ		: 
=========================================================================*/
void CMediPly::PosChangeCall(void* data)
{
	CMediPly *pme = (CMediPly*)data;
	CMainWnd *pfw = (CMainWnd*)pme->m_pwnd;

	//���ò���ʾ��������ý���ļ��Ĳ���ʱ��
	pfw->SetMusTime();
	
	//�˴�����ý���ļ���ʼ���ų�ʼ����ֵ
	//�������ֿ�ʼ����ʱ�ص����������õ�ԭ�����ڷ����汾�²��������ĳ�ʼֵ����Ч
	static BOOL areadySetVolic=FALSE;
	if(areadySetVolic == FALSE)
	{
		areadySetVolic=pme->Volume(pfw->GetVoiceSliVal());
	}		
}


/*=========================================================================
	������		: CMediPly::EndReachedCall
	����		: �ļ�������ϵĻص�����
	����ȫ�ֱ���: 
	����		: data ���������ָ��
	����ֵ		: 
=========================================================================*/ 
void CMediPly::EndReachedCall(void* data)
{
	CMediPly *pme = (CMediPly*)data; 
	CMainWnd *pfw = (CMainWnd*)pme->m_pwnd;
	pme->ReleaseMedia();

	//�����ֲ��Ž���������Ϊ��ʼλ��0
	pfw->SetMusSliVal(0);

	//���ò��Ű�ť״̬
	pfw->SetPlayBtnIsPlay(FALSE);
	
	switch(pfw->GetPlyMod())
	{
	case emRandomPlay:	 pfw->RandomPlay();   break;	//�������
	case emOrderPlay:	 pfw->OrderPlay();	 break;	//˳�򲥷�
	case emSinglePlay:	 pfw->SinglePlay();   break;	//����ѭ��
	case emLoopPlay:	 pfw->LoopPlay();     break;	//�б�ѭ������
	default:
		break;
	}
}