#ifndef UI_ANIM_CTRL_H
#define UI_ANIM_CTRL_H

namespace DirectUICore {

enum eAnimateMode 
{
	eAnimate_Loop,
	eAnimate_Once
};

class DIRECTUI_API CAnimCtrlUI : public CControlUI
{
public:
	CAnimCtrlUI();
	virtual ~CAnimCtrlUI();

	virtual LPCTSTR GetClass() const;
	virtual LPVOID GetInterface( LPCTSTR pstrName );

	virtual void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );
	virtual void DoEvent( TEventUI& event );
	virtual void PaintStatusImage( HDC hDC );

	void SetAnimImage( LPCTSTR pStrImage );
	void SetFrameCount( int nFrameCount );

	bool Play( eAnimateMode mode = eAnimate_Loop, UINT uiFrameRate = 0 );
	bool Stop();
	bool IsPlaying()const;

protected:
	int m_nCurrFrame;
	int m_nFrameCount;
	bool m_bIsRunning;
	UINT m_uiFrameRate;
	eAnimateMode m_PlayMode;
	CStdString m_sAnimImage;
};

} // namespace DirectUICore

#endif 
