/*******************************************************
���������ؼ����¼��˼������ԣ��Ƿ����nextyear��nextmonth��ť�Լ���ʾ��ʽ��
ͨ���̳�button�࣬ʵ�ֿ����������ڣ������ĵ����Ϣ��ͨ��sendnotify���ǻص��ķ�ʽ��
��Ҫ����Ļ����ͼ̳�IDateTimeChangeEvent�ӿڣ���ʵ��֮��
*/
#ifndef  DIRECTUI_CALENDAR_H
#define DIRECTUI_CALENDAR_H


#define QUERY_CALENDAR_TABLE  88888
#define MONTH_TABLE_SIZE      32
namespace DirectUICore 
{
// �����������button����ʾλ��
enum CalendarAlignment
{
	CA_TopLeft = 1 << 1,
	CA_TopRight = 1 << 2,
	CA_ButtomLeft = 1 << 3,
	CA_BottomRight = 1 << 4,
};
struct TMonthTable
{
	int nYear;
	int nMonth;
	bool m_DayOfMonthEnable[32];
};


class CCalendarUI;
class CCalendarDlg : public CAppWindow, public IDrawEvent
{
public:
	friend class CCalendarUI;
	explicit CCalendarDlg();
	explicit CCalendarDlg( CCalendarUI *pOwner );
	~CCalendarDlg();
	virtual LPCTSTR GetWindowClassName() const;
	virtual LRESULT OnCreate( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam );
	virtual void OnFinalMessage( HWND hwnd );
	virtual void Init();
	virtual void OnDrawContainer( LPCTSTR pstrName, HDC hDC );
	virtual bool Notify( TNotifyUI& msg );
	virtual bool DoEvent( void *param ); //ί��

public:
	LRESULT InitWindow();

protected:
	RECT CalPos();
	void LimitDate();
	DWORD GetDay(int nYear, int nMonth );
	int GetWeekofFirstDay( int nYear, int nMonth, int nDay = 1 );
	DWORD GetPrevMonthDay( int nYear, int nMonth );
	DWORD GetNextMonthDay( int nYear, int nMonth );
	void InvalidatePage();
	void SelectDateTime();
	void CCalendarDlg::UpdateTable();
private:
	CContainerUI *m_pDay;
	CLabelUI *m_pCurDate;
	CCalendarUI *m_pOwner;
	CButtonUI *m_pNextMonth;
	SYSTEMTIME m_sysTime;
	int m_nWeek;
	int m_nDay;
    bool m_DayOfMonthEnable[32];
	SYSTEMTIME m_CurDay;
};


// �����ؼ�
class DIRECTUI_API CCalendarUI : public CButtonUI
{
	friend class CCalendarDlg;
public:
	CCalendarUI();
	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );
	void DoEvent(TEventUI& event);

public:
	void SetPreView( bool bView );
	bool IsPreView()const;
	void SetLimitDate( bool blimit );
	bool IsLimitDate()const;
	SYSTEMTIME GetTime()const;
	void SetTime(SYSTEMTIME* pst);
	void SetMonthTable( SYSTEMTIME st, bool arrClickDayEnable[32] );
	bool GetMonthTable( int nYear, int nMonth, bool arrClickDayEnable[32] );
	void QueryTable(SYSTEMTIME st);  
	void SetMonthTableList( std::vector<TMonthTable> MonthTableList );
	std::vector<TMonthTable> GetMonthtableList();
	void ClearMonthTable();
	void ClearSelectTime();
protected:
	CCalendarDlg* m_pWindow;
    bool m_bLimitDate;
	bool m_bPreView;              // Ԥ���������Щ���ڿ����м�¼��
	DWORD m_dwAlignStyle;
	SYSTEMTIME m_sysTime;          // ������ϴ�ѡ�е����ڣ�Ĭ���ǽ���
	std::vector<TMonthTable> m_MonthTableList;
};
}
#endif