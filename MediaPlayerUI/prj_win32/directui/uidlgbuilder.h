#ifndef __DUI_DLGBUILDER_H__
#define __DUI_DLGBUILDER_H__

namespace DirectUICore {
// ����UIʱ�ص��� ���ڴ����û��Զ���Ŀؼ�
class IDialogBuilderCallback
{
public:
	// �����û��Զ���ؼ�, pstrClass�ؼ���
    virtual CControlUI* CreateControl( LPCTSTR pstrClass ) = 0;
};

class DIRECTUI_API CDialogBuilder
{
public:
    CDialogBuilder();
	// ����UI
    CControlUI* Create( STRINGorID xml, LPCTSTR type = NULL, IDialogBuilderCallback* pCallback = NULL
                      , CPaintManagerUI* pManager = NULL, CControlUI* pParent = NULL );
    CControlUI* Create( IDialogBuilderCallback* pCallback = NULL, CPaintManagerUI* pManager = NULL
                      , CControlUI* pParent = NULL);

    CMarkup* GetMarkup();
	// ��ȡ������Ϣ
    void GetLastErrorMessage( LPTSTR pstrMessage, SIZE_T cchMax ) const;
	// ��ȡ����λ��
    void GetLastErrorLocation( LPTSTR pstrSource, SIZE_T cchMax ) const;
private:
    CControlUI* _Parse( CMarkupNode* parent, CControlUI* pParent = NULL, CPaintManagerUI* pManager = NULL );

    CMarkup m_xml;							// CMarkup����
    IDialogBuilderCallback* m_pCallback;	//�����ؼ��ص�
    LPCTSTR m_pstrtype;	
};

} // namespace DirectUICore

#endif // __UIDLGBUILDER_H__
