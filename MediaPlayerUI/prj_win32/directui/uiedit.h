#ifndef __DUI_EDIT_H__
#define __DUI_EDIT_H__
#include <vector>

namespace DirectUICore 
{

//
// TODO: Try to add AutoComplete support
//

typedef enum 
{
	None = 0, Append, Suggest, SuggestAppend
} AutoCompleteMode;

template  class __declspec( dllexport ) std::allocator<CStdString>;
template  class __declspec( dllexport ) std::vector<CStdString, std::allocator<CStdString> >;

class CEditWnd;

class DIRECTUI_API CEditUI : public CLabelUI
{
    friend class CEditWnd;
public:
    CEditUI();
	~CEditUI();

    LPCTSTR GetClass() const;					// ���ؿؼ���
    LPVOID GetInterface(LPCTSTR pstrName);		// �õ�����ָ���
    UINT GetControlFlags() const;				// �õ��ؼ������ͱ�־

    void SetEnabled(bool bEnable = true);		// ���ñ༭��ؼ��Ƿ����
    void SetText(LPCTSTR pstrText);				// �����ı�
    void SetMaxChar(UINT uMax);					// ���������ı���������
    UINT GetMaxChar();							// ��ȡ��������ı�����
    void SetReadOnly(bool bReadOnly);			// ����ֻ��ģʽ
    bool IsReadOnly() const;					// ��ȡֻ��ģʽ
    void SetPasswordMode(bool bPasswordMode);	// ��������༭��ģʽ
    bool IsPasswordMode() const;				// ��ȡ����༭ģʽ
    void SetPasswordChar(TCHAR cPasswordChar);	// ��������ģʽ��ʾ�ַ�
    TCHAR GetPasswordChar() const;				// ��ȡ����ģʽ��ʾ�ַ�Edit_SetPasswordChar

	void SetAutoCompleteMode(AutoCompleteMode pAutoCompleteMode);
	AutoCompleteMode GetAutoCompleteMode() const;
	void SetAutoCompleteSource(std::vector<CStdString> pAutoCompleteSource);
	std::vector<CStdString> GetAutoCompleteSource();

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

	LPCTSTR GetAllowInputFilter();
	void SetAllowInputFilter(LPCTSTR pStrFilter);
	bool IsHasAllowInputFilter(){ return m_bAllowInputFilter; }

	LPCTSTR GetInhibitInputFilter();
	void SetInhibitInputFilter(LPCTSTR pStrFilter);
	bool IsHasInhibitInputFilter(){ return m_bInhibitInputFilter; }

	// ��ȡ/���� ԭ���༭�򱳾�ɫ
    void SetNativeEditBkColor(DWORD dwBkColor);
    DWORD GetNativeEditBkColor() const;

	CStdString GetSel();
    void SetSel(long nStartChar, long nEndChar);
    void SetSelAll();
	void SetPosition( int nPosition );
    void SetReplaceSel(LPCTSTR lpszReplace);

    void SetPos(RECT rc);						    // �õ��༭��λ��
    void SetVisible(bool bVisible = true);		// ���ÿɼ�״̬
    void SetInternVisible(bool bVisible = true);// �����ڲ����ã���ЩUIӵ�д��ھ������Ҫ��д�˺���
    SIZE EstimateSize(SIZE szAvailable);		// Ԥ���ؼ���С
    void DoEvent(TEventUI& event);				// �����¼�
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	// ��ȡ/���� �ı���ʽ
	void SetLineStyle( bool bMultiLine );
	bool GetIsMultiLine() const;

    void PaintStatusImage(HDC hDC);
    void PaintText(HDC hDC);

	//------------------------------------------------
	int GetLineCount();
 	int LineIndex(int nLine /* = -1 */) const;
	int LineLength(int nLine /* = -1 */) const;
	int GetLine( int nIndex, _Out_cap_post_count_(nMaxLength, return) LPTSTR lpszBuffer, int nMaxLength) const;

protected:
    CEditWnd* m_pWindow;		// ԭ���༭�򴰿�

	bool m_bAllowInputFilter;    //���������
	bool m_bInhibitInputFilter;   //��ֹ�����
    bool m_bReadOnly;			// ֻ����ʽ
    bool m_bPasswordMode;		// ��ʾ����ģʽ
    TCHAR m_cPasswordChar;		// ����ģʽ��ʾ���ַ�
	bool m_bMultiLine;          // �Ƿ����

	UINT m_uWndStyle;         //����EDIT���ڵ�����
	UINT m_uMaxChar;			// �ı���������
    UINT m_uButtonState;		// �༭��״̬
	AutoCompleteMode m_pAutoCompleteMode;
	std::vector<CStdString> m_pAutoCompleteSource;

    CStdString m_sNormalImage;	// ����״̬ͼ
    CStdString m_sHotImage;		// ����״̬ͼ
    CStdString m_sFocusedImage;	// ѡ��״̬ͼ
	CStdString m_sDisabledImage;// ������״̬ͼ
	CStdString m_sAllowInputFilter;
	CStdString m_sInhibitInputFilter;
	DWORD m_dwEditbkColor;		// �༭�򱳾�ɫ
};

}

#endif // __UIEDIT_H__