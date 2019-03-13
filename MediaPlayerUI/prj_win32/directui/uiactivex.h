#ifndef __DUI_ACTIVEX_H__
#define __DUI_ACTIVEX_H__

struct IOleObject;

namespace DirectUICore {
/////////////////////////////////////////////////////////////////////////////////////
//

class CActiveXCtrl;


/////////////////////////////////////////////////////////////////////////////////////
//

class DIRECTUI_API CActiveXUI : public CControlUI, public IMessageFilterUI
{
    friend class CActiveXCtrl;
public:
    CActiveXUI();
    virtual ~CActiveXUI();

    LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	// �õ��������ھ��
    HWND GetHostWindow() const;	

	// ���û�ȡ��ʱ����activeX�ؼ�
    bool IsDelayCreate() const;
    void SetDelayCreate(bool bDelayCreate = true);

    bool CreateControl(const CLSID clsid);				// ��clsid�����ؼ�
    bool CreateControl(LPCTSTR pstrCLSID);				// ��activeX�������ؼ�
    HRESULT GetControl(const IID iid, LPVOID* ppRet);	// ��ȡ�ؼ��ӿ�
	CLSID GetClisd() const;								// �õ�ActiveX�ؼ�id
    CStdString GetModuleName() const;					// �õ��ؼ�����
    void SetModuleName(LPCTSTR pstrText);				// ���ÿؼ�����

    void SetVisible(bool bVisible = true);				// �����Ƿ�ɼ�
    void SetInternVisible(bool bVisible = true);
    void SetPos(RECT rc);								// ���ÿؼ�λ��
    void DoPaint(HDC hDC, const RECT& rcPaint);			// ����CActiveXCtrl::IViewObject::Draw()

	// ���ÿؼ�����
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	// ��Ϣ����
    LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

protected:
    virtual void ReleaseControl();	// �ͷſؼ�����ϸ��cpp
    virtual bool DoCreateControl();	// �����ؼ�����ϸ��cpp

protected:
    CLSID m_clsid;				// ActiveX��ID
    CStdString m_sModuleName;	// ActiveX��ģ����
    bool m_bCreated;			// �Ƿ񱻴���
    bool m_bDelayCreate;		// �Ƿ���ʱ����
    IOleObject* m_pUnk;			// �ṩǶ�������������֮�����ϵ
    CActiveXCtrl* m_pControl;	// ActiveX�����ؼ�
    HWND m_hwndHost;			// �������ھ��
};

} // namespace DirectUICore

#endif // __UIACTIVEX_H__
