#ifndef _H_DIRECTUI_DROP_SOURCE_H_
#define _H_DIRECTUI_DROP_SOURCE_H_

// һ������£�ֻ��Ҫָ����ʽ�����������ݺͳ��ȣ�����ʵ���϶�Ч��������о����Ҫ����Ҫ�Լ�ʵ�֣�����ֻ��һ���Եķ�װ��
DIRECTUI_API HRESULT DoDragDropProc( CLIPFORMAT cf, LPVOID pData, UINT nSize, HWND hSourcWnd = NULL );

class DIRECTUI_API CDuiDropSource : public IDropSource
{
public:

	CDuiDropSource();
	~CDuiDropSource();

	void SetSourceHwnd(HWND hWnd){m_Hwnd = hWnd;}

	// Methods of IUnknown
	IFACEMETHODIMP QueryInterface(REFIID riid, void **ppv);
	IFACEMETHODIMP_(ULONG) AddRef(void);
	IFACEMETHODIMP_(ULONG) Release(void);

	// Methods of IDropSource
	IFACEMETHODIMP QueryContinueDrag(BOOL fEscapePressed, DWORD grfKeyState);
	IFACEMETHODIMP GiveFeedback(DWORD dwEffect);
	//WINOLEAPI DoDragDrop( IDataObject * pDataObject, /*Pointer to the data object */ IDropSource * pDropSource, /*Pointer to the source */ DWORD dwOKEffect, /*Effects allowed by the source */ DWORD * pdwEffect /*Pointer to effects on the source */ );
private:
	volatile LONG   m_dwRef;     //!< The reference count
	HWND m_Hwnd;
};

#endif