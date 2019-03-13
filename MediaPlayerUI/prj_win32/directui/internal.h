#ifndef __DUI_INTERNAL_H__
#define __DUI_INTERNAL_H__

#include <d3d9.h>
#include <math.h>

namespace DirectUICore {
/////////////////////////////////////////////////////////////////////////////////////
//
//

template< class T >
class CSafeRelease	// 安全释放对象t
{
public:
   CSafeRelease(T* p) : m_p(p) { };							// 构造
   ~CSafeRelease() { if( m_p != NULL ) m_p->Release(); };	// 析构
   T* Detach() { T* t = m_p; m_p = NULL; return t; };		// 分离
   T* m_p;													// 对象指针
};

/////////////////////////////////////////////////////////////////////////////////////
//
//

class CAnimationSpooler
{
public:
   CAnimationSpooler();
   ~CAnimationSpooler();

   enum { MAX_BUFFERS = 40 };

   bool Init(HWND hWnd);
   bool PrepareAnimation(HWND hWnd);
   void CancelJobs();
   bool Render();

   bool IsAnimating() const;
   bool IsJobScheduled() const;
   bool AddJob(CAnimJobUI* pJob);

protected:
   void Term();

   COLORREF TranslateColor(LPDIRECT3DSURFACE9 pSurface, COLORREF clr) const;
   bool SetColorKey(LPDIRECT3DTEXTURE9 pTexture, LPDIRECT3DSURFACE9 pSurface, int iTexSize, COLORREF clrColorKey);

   bool PrepareJob_Flat(CAnimJobUI* pJob);
   bool RenderJob_Flat(const CAnimJobUI* pJob, LPDIRECT3DSURFACE9 pSurface, DWORD dwTick);

protected:
   struct CUSTOMVERTEX 
   {
      FLOAT x, y, z;
      FLOAT rhw;
      DWORD color;
      FLOAT tu, tv;
   };
   typedef CUSTOMVERTEX CUSTOMFAN[4];

   HWND m_hWnd;
   bool m_bIsAnimating;
   bool m_bIsInitialized;
   CStdPtrArray m_aJobs;
   D3DFORMAT m_ColorFormat;
   LPDIRECT3D9 m_pD3D;
   LPDIRECT3DDEVICE9 m_p3DDevice;
   LPDIRECT3DSURFACE9 m_p3DBackSurface;
   //
   LPDIRECT3DVERTEXBUFFER9 m_p3DVertices[MAX_BUFFERS];
   LPDIRECT3DTEXTURE9 m_p3DTextures[MAX_BUFFERS];
   CUSTOMFAN m_fans[MAX_BUFFERS];
   int m_nBuffers;
};
} // namespace DirectUICore

#endif // !defined(AFX_INTERNAL_H__20060218_C01D_1618_FBA5_0080AD509054__INCLUDED_)
