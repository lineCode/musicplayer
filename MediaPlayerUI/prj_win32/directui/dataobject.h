#ifndef _H_DIRECTUI_DATA_OBJECT_H_
#define _H_DIRECTUI_DATA_OBJECT_H_

#include "dropsource.h"
#include "shlobj.h"
typedef struct _DATASTORAGE
{
	FORMATETC *m_formatEtc;
	STGMEDIUM *m_stgMedium;

} DATASTORAGE_t, *LPDATASTORAGE_t;



class DIRECTUI_API CDuiDataObject : public IDataObject
{
public:

	CDuiDataObject(CDuiDropSource *pDropSource = NULL);
	~CDuiDataObject(void);
	BOOL IsDataAvailable(CLIPFORMAT cfFormat);
	BOOL GetGlobalData(CLIPFORMAT cfFormat, void **ppData);
	BOOL GetGlobalDataArray(CLIPFORMAT cfFormat, 
		HGLOBAL *pDataArray, DWORD dwCount);
	BOOL SetGlobalData(CLIPFORMAT cfFormat, void *pData, int nSize );
	BOOL SetGlobalDataArray(CLIPFORMAT cfFormat, 
		HGLOBAL *pDataArray, DWORD dwCount, BOOL fRelease = TRUE);
//	BOOL SetDropTip(DROPIMAGETYPE type, PCWSTR pszMsg, PCWSTR pszInsert);

	// The com interface.
	IFACEMETHODIMP QueryInterface(REFIID riid, void **ppv);
	IFACEMETHODIMP_(ULONG) AddRef();
	IFACEMETHODIMP_(ULONG) Release();
	IFACEMETHODIMP GetData(FORMATETC *pformatetcIn, STGMEDIUM *pmedium);
	IFACEMETHODIMP SetData(FORMATETC *pformatetc,
		STGMEDIUM *pmedium, BOOL fRelease);
	IFACEMETHODIMP GetDataHere(FORMATETC *pformatetc , STGMEDIUM *pmedium );
	IFACEMETHODIMP QueryGetData(FORMATETC *pformatetc);
	IFACEMETHODIMP GetCanonicalFormatEtc(FORMATETC *pformatetcIn,  
		FORMATETC *pformatetcOut);
	IFACEMETHODIMP EnumFormatEtc(DWORD dwDirection, 
		IEnumFORMATETC **ppenumFormatEtc);
	IFACEMETHODIMP DAdvise(FORMATETC *pformatetc , DWORD advf , 
		IAdviseSink *pAdvSnk , DWORD *pdwConnection);
	IFACEMETHODIMP DUnadvise(DWORD dwConnection);
	IFACEMETHODIMP EnumDAdvise(IEnumSTATDATA **ppenumAdvise);
private:


	CDuiDataObject(const CDuiDataObject&);
	CDuiDataObject& operator = (const CDuiDataObject&);
	HRESULT CopyMedium(STGMEDIUM* pMedDest, 
		STGMEDIUM* pMedSrc, FORMATETC* pFmtSrc);
	HRESULT SetBlob(CLIPFORMAT cf, const void *pvBlob, UINT cbBlob);
	HGLOBAL CreateGlobalHandle(IN void* ptr, int size);
private:

	//!< The reference of count
	volatile LONG           m_dwRef;   
	//!< The pointer to CDropSource object  
	CDuiDropSource          *m_pDropSource;  
	//!< The collection of DATASTORAGE_t structure    
	std::vector<DATASTORAGE_t>   m_dataStorageCL;    
};

#endif