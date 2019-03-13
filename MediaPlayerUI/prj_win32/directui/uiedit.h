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

    LPCTSTR GetClass() const;					// 返回控件名
    LPVOID GetInterface(LPCTSTR pstrName);		// 得到对象指针块
    UINT GetControlFlags() const;				// 得到控件的类型标志

    void SetEnabled(bool bEnable = true);		// 设置编辑框控件是否可用
    void SetText(LPCTSTR pstrText);				// 设置文本
    void SetMaxChar(UINT uMax);					// 设置输入文本长度限制
    UINT GetMaxChar();							// 获取最大输入文本长度
    void SetReadOnly(bool bReadOnly);			// 设置只读模式
    bool IsReadOnly() const;					// 获取只读模式
    void SetPasswordMode(bool bPasswordMode);	// 设置密码编辑框模式
    bool IsPasswordMode() const;				// 获取密码编辑模式
    void SetPasswordChar(TCHAR cPasswordChar);	// 设置密码模式显示字符
    TCHAR GetPasswordChar() const;				// 获取密码模式显示字符Edit_SetPasswordChar

	void SetAutoCompleteMode(AutoCompleteMode pAutoCompleteMode);
	AutoCompleteMode GetAutoCompleteMode() const;
	void SetAutoCompleteSource(std::vector<CStdString> pAutoCompleteSource);
	std::vector<CStdString> GetAutoCompleteSource();

	// 获取/设置 正常状态图
    LPCTSTR GetNormalImage();
    void SetNormalImage(LPCTSTR pStrImage);

	// 获取/设置 悬浮状态图
    LPCTSTR GetHotImage();
    void SetHotImage(LPCTSTR pStrImage);

	// 获取/设置 选中状态图
    LPCTSTR GetFocusedImage();
    void SetFocusedImage(LPCTSTR pStrImage);

	// 获取/设置 不可用状态图
	LPCTSTR GetDisabledImage();
	void SetDisabledImage(LPCTSTR pStrImage);

	LPCTSTR GetAllowInputFilter();
	void SetAllowInputFilter(LPCTSTR pStrFilter);
	bool IsHasAllowInputFilter(){ return m_bAllowInputFilter; }

	LPCTSTR GetInhibitInputFilter();
	void SetInhibitInputFilter(LPCTSTR pStrFilter);
	bool IsHasInhibitInputFilter(){ return m_bInhibitInputFilter; }

	// 获取/设置 原生编辑框背景色
    void SetNativeEditBkColor(DWORD dwBkColor);
    DWORD GetNativeEditBkColor() const;

	CStdString GetSel();
    void SetSel(long nStartChar, long nEndChar);
    void SetSelAll();
	void SetPosition( int nPosition );
    void SetReplaceSel(LPCTSTR lpszReplace);

    void SetPos(RECT rc);						    // 得到编辑框位置
    void SetVisible(bool bVisible = true);		// 设置可见状态
    void SetInternVisible(bool bVisible = true);// 仅供内部调用，有些UI拥有窗口句柄，需要重写此函数
    SIZE EstimateSize(SIZE szAvailable);		// 预估控件大小
    void DoEvent(TEventUI& event);				// 处理事件
    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	// 获取/设置 文本样式
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
    CEditWnd* m_pWindow;		// 原生编辑框窗口

	bool m_bAllowInputFilter;    //允许输入的
	bool m_bInhibitInputFilter;   //禁止输入的
    bool m_bReadOnly;			// 只读方式
    bool m_bPasswordMode;		// 显示密码模式
    TCHAR m_cPasswordChar;		// 密码模式显示的字符
	bool m_bMultiLine;          // 是否多行

	UINT m_uWndStyle;         //设置EDIT窗口的属性
	UINT m_uMaxChar;			// 文本长度限制
    UINT m_uButtonState;		// 编辑框状态
	AutoCompleteMode m_pAutoCompleteMode;
	std::vector<CStdString> m_pAutoCompleteSource;

    CStdString m_sNormalImage;	// 正常状态图
    CStdString m_sHotImage;		// 悬浮状态图
    CStdString m_sFocusedImage;	// 选中状态图
	CStdString m_sDisabledImage;// 不可用状态图
	CStdString m_sAllowInputFilter;
	CStdString m_sInhibitInputFilter;
	DWORD m_dwEditbkColor;		// 编辑框背景色
};

}

#endif // __UIEDIT_H__