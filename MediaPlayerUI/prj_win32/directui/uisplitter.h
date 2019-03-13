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

		//��ȡ�ָ�������
		RECT GetSplitterRect() const;
		void DoEvent(TEventUI& event);

		void SetEnabled(bool bEnable = true);
		//HΪ��ֱ�϶�
		bool IsHorizontal();
		void SetHorizontal(bool bHorizontal = true);

		bool IsStretchForeImage();
		void SetStretchForeImage(bool bStretchForeImage = true);
		//�ƶ������ٷֱ�
		int GetMaxPercent();
		void SetMaxPercent( int nMaxPercent );
		//�ƶ�����С�ٷֱ�
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