#ifndef _H_DIRECTUI_DROP_TARGET_H
#define _H_DIRECTUI_DROP_TARGET_H

#include "dataobject.h"

///////////////////////////////////////////////////////////////////////////
//拖动操作自定义消息
//////////////////////////////////////////////////////////////////////////
#define DROPM_DRAGENTER				WM_USER + 1976
#define DROPM_DRAGOVER				WM_USER + 1977
#define DROPM_DROP					WM_USER + 1978
#define DROPM_DROPEX				WM_USER + 1979
#define DROPM_DRAGLEAVE				WM_USER + 1980

typedef DWORD DROPEFFECT;

class  DIRECTUI_API CDuiDropTarget : public IDropTarget
{
public:

	CDuiDropTarget();
	~CDuiDropTarget();

	void RegisterFormat(CLIPFORMAT cf );
	bool Register(HWND hWnd);
	void Revoke();
	void AllowDragDrop(bool bAllowDrop = true);
	bool QueryDataObject(IDataObject *pDataObject);
	DWORD DropEffect(DWORD grfKeyState, POINTL pt, DWORD dwAllowed);

	IFACEMETHODIMP QueryInterface(REFIID riid, void **ppv);
	IFACEMETHODIMP_(ULONG) AddRef(void);
	IFACEMETHODIMP_(ULONG) Release(void);

	IFACEMETHODIMP DragEnter(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	IFACEMETHODIMP DragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	IFACEMETHODIMP DragLeave(void);
	IFACEMETHODIMP Drop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);


private: 
	LONG                                m_dwRef;
	HWND                                m_hWnd;
	bool                                m_bAllowDrag;
	FORMATETC                           m_fmtetc;
};
#endif