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

	// 得到宿主窗口句柄
    HWND GetHostWindow() const;	

	// 设置获取延时创建activeX控件
    bool IsDelayCreate() const;
    void SetDelayCreate(bool bDelayCreate = true);

    bool CreateControl(const CLSID clsid);				// 按clsid创建控件
    bool CreateControl(LPCTSTR pstrCLSID);				// 按activeX名创建控件
    HRESULT GetControl(const IID iid, LPVOID* ppRet);	// 获取控件接口
	CLSID GetClisd() const;								// 得到ActiveX控件id
    CStdString GetModuleName() const;					// 得到控件名称
    void SetModuleName(LPCTSTR pstrText);				// 设置控件名称

    void SetVisible(bool bVisible = true);				// 设置是否可见
    void SetInternVisible(bool bVisible = true);
    void SetPos(RECT rc);								// 设置控件位置
    void DoPaint(HDC hDC, const RECT& rcPaint);			// 绘制CActiveXCtrl::IViewObject::Draw()

	// 设置控件属性
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	// 消息处理
    LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

protected:
    virtual void ReleaseControl();	// 释放控件，详细见cpp
    virtual bool DoCreateControl();	// 创建控件，详细见cpp

protected:
    CLSID m_clsid;				// ActiveX的ID
    CStdString m_sModuleName;	// ActiveX的模块名
    bool m_bCreated;			// 是否被创建
    bool m_bDelayCreate;		// 是否延时创建
    IOleObject* m_pUnk;			// 提供嵌入对象与其容器之间的联系
    CActiveXCtrl* m_pControl;	// ActiveX容器控件
    HWND m_hwndHost;			// 宿主窗口句柄
};

} // namespace DirectUICore

#endif // __UIACTIVEX_H__
