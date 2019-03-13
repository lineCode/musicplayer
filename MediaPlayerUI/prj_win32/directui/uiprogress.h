// �������ؼ�
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

	// ��ȡ/���� ����������
    bool IsHorizontal();
    void SetHorizontal(bool bHorizontal = true);

	//���������ʵλ��
	void SetZeroStartPoint( SIZE szXY );

	// ��ȡ/���� ǰ��ͼƽ�̣�ͼƬ���ڻ滭����ʱ���ã�
	bool IsForeTiled();
	void SetForeTiled( bool bForeTiled = true );
	void SetForeStartPort( SIZE szXY );
	
	// ��ȡ/���� ��Сֵ
    int GetMinValue() const;
    void SetMinValue(int nMin);

	// ��ȡ/���� ���ֵ
    int GetMaxValue() const;
    void SetMaxValue(int nMax);

	// ��ȡ/���� ��ǰֵ
    int GetValue() const;
    void SetValue(int nValue);

	// ��ȡ/���� ǰ��ͼ
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
    bool m_bHorizontal;				// �������ؼ�����
	bool m_bForeTiled;				// ǰ��ͼ�Ƿ���Ҫƽ�̣�����ͼƬ������Ҫ���Ƶ������޷�ֱ��ͨ��ƽ����ɣ���ʱʵʱ����source�������
    SIZE m_szForeTiledXY;				// ǰ��ͼ��ʼ��λ�ã�source��left,topֵ��
	SIZE m_szZeroPointXY;				// �����ʼ��λ��
	int m_nMax;						// ���ֵ
    int m_nMin;						// ��Сֵ
    int m_nValue;					// ��ǰֵ

    CStdString m_sForeImage;		// ǰ��ͼ
	CStdString m_sForeDisableImage;	// ǰ��ͼ
    CStdString m_sForeImageModify;	// ǰ��ͼ 2

	CStdString m_sBkDisableImage;	// ����ͼ
};

}

#endif // __UIPROGRESS_H__