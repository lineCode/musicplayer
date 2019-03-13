#ifndef __DUI_DLGBUILDER_H__
#define __DUI_DLGBUILDER_H__

namespace DirectUICore {
// 构建UI时回调类 用于创造用户自定义的控件
class IDialogBuilderCallback
{
public:
	// 创建用户自定义控件, pstrClass控件名
    virtual CControlUI* CreateControl( LPCTSTR pstrClass ) = 0;
};

class DIRECTUI_API CDialogBuilder
{
public:
    CDialogBuilder();
	// 构建UI
    CControlUI* Create( STRINGorID xml, LPCTSTR type = NULL, IDialogBuilderCallback* pCallback = NULL
                      , CPaintManagerUI* pManager = NULL, CControlUI* pParent = NULL );
    CControlUI* Create( IDialogBuilderCallback* pCallback = NULL, CPaintManagerUI* pManager = NULL
                      , CControlUI* pParent = NULL);

    CMarkup* GetMarkup();
	// 获取错误信息
    void GetLastErrorMessage( LPTSTR pstrMessage, SIZE_T cchMax ) const;
	// 获取出错位置
    void GetLastErrorLocation( LPTSTR pstrSource, SIZE_T cchMax ) const;
private:
    CControlUI* _Parse( CMarkupNode* parent, CControlUI* pParent = NULL, CPaintManagerUI* pManager = NULL );

    CMarkup m_xml;							// CMarkup对象
    IDialogBuilderCallback* m_pCallback;	//构建控件回调
    LPCTSTR m_pstrtype;	
};

} // namespace DirectUICore

#endif // __UIDLGBUILDER_H__
