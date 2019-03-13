// 进度条控件
#ifndef __DUI_PROGRESS_H__
#define __DUI_PROGRESS_H__

namespace DirectUICore 
{

class DIRECTUI_API CProgressUI : public CLabelUI
{
public:
    CProgressUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);

	// 获取/设置 进度条方向
    bool IsHorizontal();
    void SetHorizontal(bool bHorizontal = true);

	//设置零点其实位置
	void SetZeroStartPoint( SIZE szXY );

	// 获取/设置 前景图平铺（图片大于绘画区域时设置）
	bool IsForeTiled();
	void SetForeTiled( bool bForeTiled = true );
	void SetForeStartPort( SIZE szXY );
	
	// 获取/设置 最小值
    int GetMinValue() const;
    void SetMinValue(int nMin);

	// 获取/设置 最大值
    int GetMaxValue() const;
    void SetMaxValue(int nMax);

	// 获取/设置 当前值
    int GetValue() const;
    void SetValue(int nValue);

	// 获取/设置 前景图
    LPCTSTR GetForeImage() const;
    void SetForeImage(LPCTSTR pStrImage);

	LPCTSTR GetForeDisableImage() const;
	void SetForeDisableImage(LPCTSTR pStrImage);

	void SetBkDisableImage( LPCTSTR pStrImage );

    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
    void PaintStatusImage(HDC hDC);
	void UpdateTooltip();

private:
	void GetImageRect( CStdString strImage, CStdString strAttribute, CDirectRect& rcItem );

protected:
    bool m_bHorizontal;				// 进度条控件方向
	bool m_bForeTiled;				// 前景图是否需要平铺，由于图片大于需要绘制的区域，无法直接通过平铺完成，此时实时更新source属性完成
    SIZE m_szForeTiledXY;				// 前景图起始点位置（source的left,top值）
	SIZE m_szZeroPointXY;				// 零点起始点位置
	int m_nMax;						// 最大值
    int m_nMin;						// 最小值
    int m_nValue;					// 当前值

    CStdString m_sForeImage;		// 前景图
	CStdString m_sForeDisableImage;	// 前景图
    CStdString m_sForeImageModify;	// 前景图 2

	CStdString m_sBkDisableImage;	// 背景图
};

}

#endif // __UIPROGRESS_H__