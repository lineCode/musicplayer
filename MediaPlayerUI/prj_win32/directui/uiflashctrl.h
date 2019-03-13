#ifndef UI_FLASH_CTRL_H
#define UI_FLASH_CTRL_H

namespace DirectUICore {

// 头像目标位置类型，通过移动头像位置实现头像的闪动效果
enum EmPicPosType
{
	emInvalidPos = 0,  // 无效位置
	emLeftPos,         // 左边位置
	emMiddlePos,       // 中间位置
	emRightPos         // 右边位置
};

// 头像闪动控件
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

	bool SetTimerInterval( int nTimerInterval ); // 支持定时器时间间隔的自定义

protected:
	bool m_bFlashing;
	RECT m_rcNomalItem;
	EmPicPosType m_emCurPicPosType;
	EmPicPosType m_emLastPicPosType;

	int m_nTimerInterval;  // 定时器时间间隔（ms）
};

} // namespace DirectUICore

#endif 
