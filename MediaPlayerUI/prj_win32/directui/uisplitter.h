#ifndef __UISPLITTER_H__
#define __UISPLITTER_H__

#pragma once

namespace DirectUICore
{
	class DIRECTUI_API CSplitterUI : public CControlUI
	{
	public:
		CSplitterUI();

		LPCTSTR GetClass() const;
		UINT GetControlFlags() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		//获取分割条区域
		RECT GetSplitterRect() const;
		void DoEvent(TEventUI& event);

		void SetEnabled(bool bEnable = true);
		//H为竖直拖动
		bool IsHorizontal();
		void SetHorizontal(bool bHorizontal = true);

		bool IsStretchForeImage();
		void SetStretchForeImage(bool bStretchForeImage = true);
		//移动的最大百分比
		int GetMaxPercent();
		void SetMaxPercent( int nMaxPercent );
		//移动的最小百分比
		int GetMinPercent();
		void SetMinPercent( int nMinPercent );

		LPCTSTR GetForeImage() const;
		void SetForeImage(LPCTSTR pStrImage);
		void SetSplitterRange( int nMinPercent, int nMaxPercent );


		void PaintStatusImage(HDC hDC);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	protected:
		UINT m_uButtonState;
		int m_nMinPercent;
		int m_nMaxPercent;
		bool m_bHorizontal;
		bool m_bStretchForeImage;

		CStdString m_sForeImage;
		CStdString m_sForeImageModify;
	};
}

#endif // __UISPLITTER_H__