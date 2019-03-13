#ifndef UI_FLASH_CTRL_H
#define UI_FLASH_CTRL_H

namespace DirectUICore {

// ͷ��Ŀ��λ�����ͣ�ͨ���ƶ�ͷ��λ��ʵ��ͷ�������Ч��
enum EmPicPosType
{
	emInvalidPos = 0,  // ��Чλ��
	emLeftPos,         // ���λ��
	emMiddlePos,       // �м�λ��
	emRightPos         // �ұ�λ��
};

// ͷ�������ؼ�
class DIRECTUI_API CFlashCtrlUI : public CControlUI
{
public:
	CFlashCtrlUI();
	virtual ~CFlashCtrlUI();

	virtual LPCTSTR GetClass() const;
	virtual LPVOID GetInterface( LPCTSTR pstrName );

	virtual void DoEvent( TEventUI& event );
	virtual void SetPos( RECT rc );
	virtual void Invalidate();

	bool StartFlash();
	bool StopFlash();

	bool IsFlashing();

	bool SetTimerInterval( int nTimerInterval ); // ֧�ֶ�ʱ��ʱ�������Զ���

protected:
	bool m_bFlashing;
	RECT m_rcNomalItem;
	EmPicPosType m_emCurPicPosType;
	EmPicPosType m_emLastPicPosType;

	int m_nTimerInterval;  // ��ʱ��ʱ������ms��
};

} // namespace DirectUICore

#endif 
