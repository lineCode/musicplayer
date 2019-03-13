/*******************************************************
这是日历控件，新加了几个属性：是否禁用nextyear和nextmonth按钮以及显示方式，
通过继承button类，实现控制日历窗口，产生的点击消息不通过sendnotify而是回调的方式。
需要处理的话，就继承IDateTimeChangeEvent接口，并实现之。
*/
#ifndef  DIRECTUI_CALENDAR_H
#define DIRECTUI_CALENDAR_H


#define QUERY_CALENDAR_TABLE  88888
#define MONTH_TABLE_SIZE      32
namespace DirectUICore 
{
// 弹出框相对于button的显示位置
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
	virtual bool DoEvent( void *param ); //委托

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


// 日历控件
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
	bool m_bPreView;              // 预览这个月哪些日期可以有记录。
	DWORD m_dwAlignStyle;
	SYSTEMTIME m_sysTime;          // 保存的上次选中的日期，默认是今天
	std::vector<TMonthTable> m_MonthTableList;
};
}
#endif