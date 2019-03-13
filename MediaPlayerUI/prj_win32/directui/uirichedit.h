#ifndef __DUI_RICHEDIT_H__
#define __DUI_RICHEDIT_H__

#include <Imm.h>
#pragma comment(lib,"imm32.lib")

#include "uirichedithost.h"

namespace DirectUICore {

class DIRECTUI_API CRichEditUI : public CContainerUI, public IMessageFilterUI
{
public:
    CRichEditUI();
    ~CRichEditUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);
    UINT GetControlFlags() const;
	void SetManager( CPaintManagerUI* pManager, CControlUI* pParent, bool bInit = true );

	IRichEditOle* GetIRichEditOle();
	CStdString GetContent();
	CStdString GetContentText( std::vector<DWORD>& vInsertedPicIndexList );
	CStdString GetPureText();
	bool IsMouseWheeling(); // �Ƿ�������ڹ���
	BOOL InsertPic( LPCTSTR pstrPicPath, DWORD dwUser, BOOL bCompress = TRUE, bool bRefreshColor = false );
	BOOL AddLink( LPCTSTR strName, LPCTSTR strId, DWORD dwUser, BOOL bCanClick );   // ���û�����ID�ŷ��ڶ�����
	BOOL InsertAt( LPCTSTR strName, LPCTSTR strId, DWORD dwUser, BOOL bBeRefered = FALSE );

	// �ڽ�Link����ʱ����Ҫ���¼���Link���ֵĳ��ȣ�ע���ʱҪ��header���崫����
	BOOL CalcLinkTextSize( LPCTSTR strName, LOGFONT font, SIZE& sizeText );
	// �ڽ�@jid����Ϊ@shownameʱ����Ҫ���¼���@showname�ĳ���
	BOOL CalcAtTextSize( LPCTSTR strName, SIZE& sizeText );

	void SetAutoDown( BOOL bAutoDown ){ m_bAutoDown = bAutoDown; }
	void SetPicCompress( BOOL bCompress );  // ͼƬ�Ƿ�ѹ��
	LOGFONT GetTextFont(){ return m_font; }
	IGifAnimator* GetLastImageOle(){ return m_pLastImageOle; }
	RECT GetLastImageOleRect(){ return m_rcLastImageOle; }
	Ilinkole* GetLinkOle(){ return m_pLinkOle; }   // �������Ӷ���

    bool IsWantTab();
    void SetWantTab(bool bWantTab = true);
    bool IsWantReturn();
    void SetWantReturn(bool bWantReturn = true);
    bool IsWantCtrlReturn();
    bool IsRich();
    void SetRich(bool bRich = true);
    bool IsReadOnly();
    void SetReadOnly(bool bReadOnly = true);
    bool GetWordWrap();
    void SetWordWrap(bool bWordWrap = true);
    int GetFont();
    void SetFont(int index);
    void SetFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);
	void SetTextFont( const LOGFONT& font, COLORREF color );
    LONG GetWinStyle();
    void SetWinStyle(LONG lStyle);
    COLORREF GetTextColor();
    void SetTextColor(DWORD dwTextColor, bool bRgb = true);
    int GetLimitText();
    void SetLimitText(int iChars);
    long GetTextLength(DWORD dwFlags = GTL_DEFAULT) const;
    CStdString GetText() const;
    void SetText(LPCTSTR pstrText);
    bool GetModify() const;
    void SetModify(bool bModified = true) const;
    void GetSel(CHARRANGE &cr) const;
    void GetSel(long& nStartChar, long& nEndChar) const;
    int SetSel(CHARRANGE &cr);
    int SetSel(long nStartChar, long nEndChar);
    void ReplaceSel(LPCTSTR lpszNewText, bool bCanUndo = false);
    void ReplaceSelW(LPCWSTR lpszNewText, bool bCanUndo = false);
    CStdString GetSelText() const;
	CStdString GetSelPureText();
    int SetSelAll();
    int SetSelNone();
    WORD GetSelectionType() const;
    bool GetZoom(int& nNum, int& nDen) const;
    bool SetZoom(int nNum, int nDen);
    bool SetZoomOff();
    bool GetAutoURLDetect() const;
    bool SetAutoURLDetect(bool bAutoDetect = true);
    DWORD GetEventMask() const;
    DWORD SetEventMask(DWORD dwEventMask);
    CStdString GetTextRange(long nStartChar, long nEndChar) const;
    void HideSelection(bool bHide = true, bool bChangeStyle = false);
    void ScrollCaret();
    int InsertText(long nInsertAfterChar, LPCTSTR lpstrText, bool bCanUndo = false);
    int AppendText(LPCTSTR lpstrText, bool bCanUndo = false);
    DWORD GetDefaultCharFormat(CHARFORMAT2 &cf) const;
    bool SetDefaultCharFormat(CHARFORMAT2 &cf);
    DWORD GetSelectionCharFormat(CHARFORMAT2 &cf) const;
    bool SetSelectionCharFormat(CHARFORMAT2 &cf);
    bool SetWordCharFormat(CHARFORMAT2 &cf);
    DWORD GetParaFormat(PARAFORMAT2 &pf) const;
    bool SetParaFormat(PARAFORMAT2 &pf);
	void SetWantCopy( bool bEnable );
	bool IsWantCopy() const;
    bool Redo();
    bool Undo();
    void Clear();
    void Copy();
    void Cut();
    void Paste();
    int GetLineCount() const;
    CStdString GetLine(int nIndex, int nMaxLength) const;
    int LineIndex(int nLine = -1) const;
    int LineLength(int nLine = -1) const;
    bool LineScroll(int nLines, int nChars = 0);
	CDirectPoint GetCharPos(long lChar) const;
    long LineFromChar(long nIndex) const;
    CDirectPoint PosFromChar(UINT nChar) const;
    int CharFromPos(CDirectPoint pt) const;
    void EmptyUndoBuffer();
    UINT SetUndoLimit(UINT nLimit);
    long StreamIn(int nFormat, EDITSTREAM &es);
    long StreamOut(int nFormat, EDITSTREAM &es);

    void DoInit();
    // ע�⣺TxSendMessage��SendMessage��������ģ�TxSendMessageû��multibyte��unicode�Զ�ת���Ĺ��ܣ�
    // ��richedit2.0�ڲ�����unicodeʵ�ֵģ���multibyte�����У������Լ�����unicode��multibyte��ת��
    HRESULT TxSendMessage(UINT msg, WPARAM wparam, LPARAM lparam, LRESULT *plresult) const; 
    IDropTarget* GetTxDropTarget();
    virtual bool OnTxViewChanged();
    virtual void OnTxNotify(DWORD iNotify, void *pv);

    void SetScrollPos(SIZE szPos);
    void LineUp();
    void LineDown();
    void PageUp();
    void PageDown();
    void HomeUp();
    void EndDown();
    void LineLeft();
    void LineRight();
    void PageLeft();
    void PageRight();
    void HomeLeft();
    void EndRight();

    SIZE EstimateSize(SIZE szAvailable);
	void SetToolTip( LPCTSTR pstrText );
    void SetPos(RECT rc);
    void DoEvent(TEventUI& event);
    void DoPaint(HDC hDC, const RECT& rcPaint);

    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
    LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	void SetCaretHeight( INT yHeight ){ m_nCaretHeight = yHeight; }
	INT GetCaretHeight(){ return m_nCaretHeight; }

	void UpdateAtRect();

protected:
	// ��ȡ�����ļ����͡����ļ��С�����ǰ������֣��������ļ�������·��
	CStdString GetFilePath( UINT nCurPos );
	void OnURLClick( ENLINK *pLink );

	// ʵ�ִ��ļ��в�ѡ�ж�Ӧ���ļ������ʹ��ShellExecute���ڵ�����
	// ʹ��ShellExecute���ڵ����⣺����ļ����Ѿ��򿪣���ʱ����ShellExecuteִ��
	// �������ļ��еĲ������Ὣ�ļ�����ǰ��ʾ��������ѡ�и��ļ���ѡ�еĻ�����һ
	// �ε��ļ�
	bool OpenFolderAndSelFile( CStdString strFilePath );

	CTxtWinHost* m_pTwh;
    bool m_bVScrollBarFixing;
    bool m_bWantTab;
    bool m_bWantReturn;
    bool m_bRich;
    bool m_bReadOnly;
    bool m_bWordWrap;
    DWORD m_dwTextColor;
    int m_iFont;
    int m_iLimitText;
    LONG m_lTwhStyle;

	int  m_nPreWidth;
	INT m_nCaretHeight;
	BOOL m_bAutoDown;
	BOOL m_bCompress;
	BOOL m_bCanClick;
	BOOL m_bDownUrl; 
	LOGFONT m_font;
	IGifAnimator* m_pLastImageOle;
	RECT m_rcLastImageOle;
	Ilinkole* m_pLinkOle;

	bool m_bCanCopy;   // �Լ������ݼ���Ϣ
};

} // namespace DirectUICore

#endif // __UIRICHEDIT_H__
