#ifndef UI_RICHEDIT_HOST_H
#define UI_RICHEDIT_HOST_H

#include <imm.h>
#include <textserv.h>
#include "richole.h"
#pragma warning(disable:4192)
#ifdef _DEBUG
#import ".\\imageoleex.dll" named_guids
#else
#import ".\\imageoleex.dll" named_guids
#endif

#pragma warning(default:4192)
using namespace ImageOleExLib;

namespace DirectUICore {

//richedit鼠标滚轮的时钟ID
#define MOUSEWHEEL_TIMER_ID  433

class CRichEditUI;

class IRichOleEvent
{
public:
	virtual ~IRichOleEvent( void ) {}
	virtual void OnDeleteObject(LPOLEOBJECT lpoleobj){}
};

class IRichEditOleCallbackEx : public IRichEditOleCallback
{
public:
	IRichEditOleCallbackEx() : m_iNumStorages(0), m_dwRef(0), m_pREditOleEvent(NULL) {}
	virtual ~IRichEditOleCallbackEx() {}
	int m_iNumStorages;
	DWORD m_dwRef;
	IRichOleEvent* m_pREditOleEvent;

	void SetRichEditOleEvent( IRichOleEvent* e ) { m_pREditOleEvent=e; }

	virtual HRESULT STDMETHODCALLTYPE GetNewStorage(LPSTORAGE* lplpstg);
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void ** ppvObject);
	virtual ULONG STDMETHODCALLTYPE AddRef();
	virtual ULONG STDMETHODCALLTYPE Release();
	virtual HRESULT STDMETHODCALLTYPE GetInPlaceContext(LPOLEINPLACEFRAME FAR *lplpFrame,
		LPOLEINPLACEUIWINDOW FAR *lplpDoc, LPOLEINPLACEFRAMEINFO lpFrameInfo);
	virtual HRESULT STDMETHODCALLTYPE ShowContainerUI(BOOL fShow);
	virtual HRESULT STDMETHODCALLTYPE QueryInsertObject(LPCLSID lpclsid, LPSTORAGE lpstg, LONG cp);
	virtual HRESULT STDMETHODCALLTYPE DeleteObject(LPOLEOBJECT lpoleobj);
	virtual HRESULT STDMETHODCALLTYPE QueryAcceptData(LPDATAOBJECT lpdataobj, CLIPFORMAT FAR *lpcfFormat,
		DWORD reco, BOOL fReally, HGLOBAL hMetaPict);
	virtual HRESULT STDMETHODCALLTYPE ContextSensitiveHelp(BOOL fEnterMode);
	virtual HRESULT STDMETHODCALLTYPE GetClipboardData(CHARRANGE FAR *lpchrg, DWORD reco, LPDATAOBJECT FAR *lplpdataobj);
	virtual HRESULT STDMETHODCALLTYPE GetDragDropEffect(BOOL fDrag, DWORD grfKeyState, LPDWORD pdwEffect);
	virtual HRESULT STDMETHODCALLTYPE GetContextMenu(WORD seltyp, LPOLEOBJECT lpoleobj, CHARRANGE FAR *lpchrg,
		HMENU FAR *lphmenu);
};

class CTxtWinHost : public ITextHost
{
public:
	CTxtWinHost();
	BOOL Init(CRichEditUI *re , const CREATESTRUCT *pcs);
	virtual ~CTxtWinHost();

	BOOL InsertPic( LPCTSTR pstrPicPath, DWORD dwUser, bool bRefreshColor, BOOL bCompress );
	BOOL AddLink( LPCTSTR strName, LPCTSTR strId, DWORD dwUser, LOGFONT& font, BOOL bCanClick );
	BOOL InsertAt( LPCTSTR strName, LPCTSTR strId, DWORD dwUser, LOGFONT& font, BOOL bBeRefered = FALSE );
	IGifAnimator* FindImageOle( POINT pt, LPRECT prc );
	Ilinkole* FindLinkOle( POINT pt );
	bool IsMouseWheeling(){ return m_bMouseWheeling; } // 是否鼠标正在滚动

	void CalcLinkTextSize( LPCTSTR lpLinkText, LOGFONT font, SIZE& sizeText );
	void CalcAtTextSize( LPCTSTR strName, SIZE& sizeText );

	ITextServices* GetTextServices(void) { return pserv; }
	IRichEditOle* GetIRichEditOle() { return m_pRichEditOle; }
	void SetClientRect(RECT *prc);
	RECT* GetClientRect() { return &rcClient; }
	BOOL GetWordWrap(void) { return fWordWrap; }
	void SetWordWrap(BOOL fWordWrap);
	BOOL GetReadOnly();
	void SetReadOnly(BOOL fReadOnly);
	void SetFont(HFONT hFont);
	void SetColor(DWORD dwColor);
	void SetTextFont( const LOGFONT& font, COLORREF color );
	SIZEL* GetExtent();
	void SetExtent(SIZEL *psizelExtent);
	void LimitText(LONG nChars);
	BOOL IsCaptured();

	BOOL GetAllowBeep();
	void SetAllowBeep(BOOL fAllowBeep);
	WORD GetDefaultAlign();
	void SetDefaultAlign(WORD wNewAlign);
	BOOL GetRichTextFlag();
	void SetRichTextFlag(BOOL fNew);
	LONG GetDefaultLeftIndent();
	void SetDefaultLeftIndent(LONG lNewIndent);
	BOOL SetSaveSelection(BOOL fSaveSelection);
	HRESULT OnTxInPlaceDeactivate();
	HRESULT OnTxInPlaceActivate(LPCRECT prcClient);
	BOOL GetActiveState(void) { return fInplaceActive; }
	BOOL DoSetCursor(RECT *prc, POINT *pt);
	void SetTransparent(BOOL fTransparent);
	void GetControlRect(LPRECT prc);
	LONG SetAccelPos(LONG laccelpos);
	WCHAR SetPasswordChar(WCHAR chPasswordChar);
	void SetDisabled(BOOL fOn);
	LONG SetSelBarWidth(LONG lSelBarWidth);
	BOOL GetTimerState();

	void SetCharFormat(CHARFORMAT2W &c);
	void SetParaFormat(PARAFORMAT2 &p);

	void UpdateAtRect();
	bool HasCN( LPCTSTR pstr ) const;
	void ReSetcharFormat();
	CStdString OsVersion();

	// -----------------------------
	//	IUnknown interface
	// -----------------------------
	virtual HRESULT _stdcall QueryInterface(REFIID riid, void **ppvObject);
	virtual ULONG _stdcall AddRef(void);
	virtual ULONG _stdcall Release(void);

	// -----------------------------
	//	ITextHost interface
	// -----------------------------
	virtual HDC TxGetDC();
	virtual INT TxReleaseDC(HDC hdc);
	virtual BOOL TxShowScrollBar(INT fnBar, BOOL fShow);
	virtual BOOL TxEnableScrollBar (INT fuSBFlags, INT fuArrowflags);
	virtual BOOL TxSetScrollRange(INT fnBar, LONG nMinPos, INT nMaxPos, BOOL fRedraw);
	virtual BOOL TxSetScrollPos (INT fnBar, INT nPos, BOOL fRedraw);
	virtual void TxInvalidateRect(LPCRECT prc, BOOL fMode);
	virtual void TxViewChange(BOOL fUpdate);
	virtual BOOL TxCreateCaret(HBITMAP hbmp, INT xWidth, INT yHeight);
	virtual BOOL TxShowCaret(BOOL fShow);
	virtual BOOL TxSetCaretPos(INT x, INT y);
	virtual BOOL TxSetTimer(UINT idTimer, UINT uTimeout);
	virtual void TxKillTimer(UINT idTimer);
	virtual void TxScrollWindowEx (INT dx, INT dy, LPCRECT lprcScroll, LPCRECT lprcClip, HRGN hrgnUpdate, LPRECT lprcUpdate, UINT fuScroll);
	virtual void TxSetCapture(BOOL fCapture);
	virtual void TxSetFocus();
	virtual void TxSetCursor(HCURSOR hcur, BOOL fText);
	virtual BOOL TxScreenToClient (LPPOINT lppt);
	virtual BOOL TxClientToScreen (LPPOINT lppt);
	virtual HRESULT TxActivate( LONG * plOldState );
	virtual HRESULT TxDeactivate( LONG lNewState );
	virtual HRESULT TxGetClientRect(LPRECT prc);
	virtual HRESULT TxGetViewInset(LPRECT prc);
	virtual HRESULT TxGetCharFormat(const CHARFORMATW **ppCF );
	virtual HRESULT TxGetParaFormat(const PARAFORMAT **ppPF);
	virtual COLORREF TxGetSysColor(int nIndex);
	virtual HRESULT TxGetBackStyle(TXTBACKSTYLE *pstyle);
	virtual HRESULT TxGetMaxLength(DWORD *plength);
	virtual HRESULT TxGetScrollBars(DWORD *pdwScrollBar);
	virtual HRESULT TxGetPasswordChar(TCHAR *pch);
	virtual HRESULT TxGetAcceleratorPos(LONG *pcp);
	virtual HRESULT TxGetExtent(LPSIZEL lpExtent);
	virtual HRESULT OnTxCharFormatChange (const CHARFORMATW * pcf);
	virtual HRESULT OnTxParaFormatChange (const PARAFORMAT * ppf);
	virtual HRESULT TxGetPropertyBits(DWORD dwMask, DWORD *pdwBits);
	virtual HRESULT TxNotify(DWORD iNotify, void *pv);
	virtual HIMC TxImmGetContext(void);
	virtual void TxImmReleaseContext(HIMC himc);
	virtual HRESULT TxGetSelectionBarWidth (LONG *lSelBarWidth);

private:
	CRichEditUI *m_re;
	ULONG	cRefs;					// Reference Count
	ITextServices	*pserv;		    // pointer to Text Services object
	IRichEditOle*   m_pRichEditOle;
	IRichEditOleCallbackEx* m_pIRichEditOleCallback;

	// Properties
	DWORD		dwStyle;				// style bits

	unsigned	fEnableAutoWordSel	:1;	// enable Word style auto word selection?
	unsigned	fWordWrap			:1;	// Whether control should word wrap
	unsigned	fAllowBeep			:1;	// Whether beep is allowed
	unsigned	fRich				:1;	// Whether control is rich text
	unsigned	fSaveSelection		:1;	// Whether to save the selection when inactive
	unsigned	fInplaceActive		:1; // Whether control is inplace active
	unsigned	fTransparent		:1; // Whether control is transparent
	unsigned	fTimer				:1;	// A timer is set
	unsigned    fCaptured           :1;

	LONG		lSelBarWidth;			// Width of the selection bar
	LONG  		cchTextMost;			// maximum text size
	DWORD		dwEventMask;			// DoEvent mask to pass on to parent window
	LONG		icf;
	LONG		ipf;
	RECT		rcClient;				// Client Rect for this control
	SIZEL		sizelExtent;			// Extent array
	CHARFORMAT2W cf;					// Default character format
	PARAFORMAT2	 pf;					    // Default paragraph format
	LONG		laccelpos;				// Accelerator position
	WCHAR		chPasswordChar;		    // Password character
	bool        m_bResized;             // 修正光标bug
	bool        m_bMouseWheeling;       // 是否鼠标正在滚动
};

}

#endif