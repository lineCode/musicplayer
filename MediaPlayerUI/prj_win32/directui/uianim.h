#ifndef __DUI_ANIM_H__
#define __DUI_ANIM_H__

namespace DirectUICore {
/////////////////////////////////////////////////////////////////////////////////////
//

typedef enum
{
   UIANIMTYPE_FLAT,
   UIANIMTYPE_SWIPE,
} UITYPE_ANIM;


/////////////////////////////////////////////////////////////////////////////////////
//

class DIRECTUI_API CAnimJobUI
{
public:
   CAnimJobUI( const CAnimJobUI& src );
   CAnimJobUI( UITYPE_ANIM AnimType, DWORD dwStartTick, DWORD dwDuration
	        , COLORREF clrBack, COLORREF clrKey, RECT rcFrom, int xtrans
			, int ytrans, int ztrans, int alpha, float zrot );

   typedef enum
   {
      INTERPOLATE_LINEAR,
      INTERPOLATE_COS,
   } INTERPOLATETYPE;

   typedef struct PLOTMATRIX
   {
      int xtrans;
      int ytrans;
      int ztrans;
      int alpha;
      float zrot;
   } PLOTMATRIX;

   UITYPE_ANIM AnimType;
   DWORD dwStartTick;
   DWORD dwDuration;
   int iBufferStart;
   int iBufferEnd;
   union
   {
      struct 
      {
         COLORREF clrBack;
         COLORREF clrKey;
         RECT rcFrom;
         PLOTMATRIX mFrom;
         INTERPOLATETYPE iInterpolate;
      } plot;
   } data;
};
} // namespace DirectUICore


#endif // !defined(AFX_UIANIM_H__20050522_5560_2E48_0B2D_0080AD509054__INCLUDED_)

