#ifndef UI_HOTKEY_H
#define UI_HOTKEY_H
#include <vector>

namespace DirectUICore 
{

class CHotKeyWnd;

class DIRECTUI_API CHotKeyUI : public CLabelUI
{
    friend class CHotKeyWnd;
public:
    CHotKeyUI();
	~CHotKeyUI();

    LPCTSTR GetClass() const;					// ���ؿؼ���
    LPVOID GetInterface(LPCTSTR pstrName);		// �õ�����ָ���
    UINT GetControlFlags() const;				// �õ��ؼ������ͱ�־

	void DoInit();

    void SetEnabled(bool bEnable = true);		// ���ñ༭��ؼ��Ƿ����
    void SetText(LPCTSTR pstrText);				// �����ı�

	void SetHotKey( WORD wVirtualKey, WORD wSysKey );
	void GetHotKey( WORD& wVirtualKey, WORD& wSysKey );

	// ��ȡ/���� ����״̬ͼ
    LPCTSTR GetNormalImage();
    void SetNormalImage(LPCTSTR pStrImage);

	// ��ȡ/���� ����״̬ͼ
    LPCTSTR GetHotImage();
    void SetHotImage(LPCTSTR pStrImage);

	// ��ȡ/���� ѡ��״̬ͼ
    LPCTSTR GetFocusedImage();
    void SetFocusedImage(LPCTSTR pStrImage);

	// ��ȡ/���� ������״̬ͼ
	LPCTSTR GetDisabledImage();
	void SetDisabledImage(LPCTSTR pStrImage);

    void SetPos(RECT rc);						// �õ��༭��λ��
    void SetVisible(bool bVisible = true);		// ���ÿɼ�״̬
    void SetInternVisible(bool bVisible = true);// �����ڲ����ã���ЩUIӵ�д��ھ������Ҫ��д�˺���
    SIZE EstimateSize(SIZE szAvailable);		// Ԥ���ؼ���С
    void DoEvent(TEventUI& event);				// �����¼�
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

    void PaintStatusImage(HDC hDC);
    void PaintText(HDC hDC);

protected:
    CHotKeyWnd* m_pWindow;		// ԭ���༭�򴰿�

    UINT m_uButtonState;		// �༭��״̬

    CStdString m_sNormalImage;	// ����״̬ͼ
    CStdString m_sHotImage;		// ����״̬ͼ
    CStdString m_sFocusedImage;	// ѡ��״̬ͼ
	CStdString m_sDisabledImage;// ������״̬ͼ
};

}

#endif // __UIEDIT_H__