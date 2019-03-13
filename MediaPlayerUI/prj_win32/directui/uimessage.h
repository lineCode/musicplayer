#ifndef __DUI_MESSAGE_H__
#define __DUI_MESSAGE_H__

namespace DirectUICore {

//////////////////////////////////////////////////////////////////////////
// 消息定义,与Windows消息对应
//////////////////////////////////////////////////////////////////////////
typedef enum EVENTTYPE_UI
{
	UIEVENT__FIRST = 1,
	UIEVENT__KEYBEGIN,
	UIEVENT_KEYDOWN,
	UIEVENT_KEYUP,
	UIEVENT_CHAR,
	UIEVENT_SYSKEY,
	UIEVENT__KEYEND,
	UIEVENT__MOUSEBEGIN,
	UIEVENT_MOUSEMOVE,
	UIEVENT_MOUSELEAVE,
	UIEVENT_MOUSEENTER,
	UIEVENT_MOUSEHOVER,
	UIEVENT_BUTTONDOWN,
	UIEVENT_BUTTONUP,
	UIEVENT_RBUTTONDOWN,
	UIEVENT_RBUTTONUP,
	UIEVENT_DBLCLICK,
	UIEVENT_CONTEXTMENU,
	UIEVENT_SCROLLWHEEL,
	UIEVENT__MOUSEEND,
	UIEVENT_KILLFOCUS,
	UIEVENT_SETFOCUS,
	UIEVENT_WINDOWSIZE,
	UIEVENT_SETCURSOR,
	UIEVENT_TIMER,
	UIEVENT_NOTIFY,
	UIEVENT_COMMAND,
	UIEVENT__LAST,
};

// 通知事件
#define NOTIFY_KILLFOCUS		_T("killfocus")
#define NOTIFY_SETFOCUS		    _T("setfocus")
#define NOTIFY_INIWINDOW		_T("windowinit")
#define NOTIFY_TABLESELECT		_T("tabselect")
#define NOTIFY_RETURN			_T("return")
#define NOTIFY_SHOWACTIVEX		_T("showactivex")
#define NOTIFY_MENU			    _T("menu")
#define NOTIFY_SELECT_CHANGED	_T("selectchanged")
#define NOTIFY_LINK			    _T("link")
#define NOTIFY_VALUECHANGED	    _T("valuechanged")
#define NOTIFY_TEXTCHANGED		_T("textchanged")
#define NOTIFY_ITEMSELECT		_T("itemselect")
#define NOTIFY_ITEM_CLICK		_T("itemclick")
#define NOTIFY_DROPDOWN		    _T("dropdown")
#define NOTIFY_KEYDOWN          _T("keydown") 
#define NOTIFY_BUTTONDOWN       _T("buttondown") 
#define NOTIFY_CHILD_BTNDOWN    _T("childbtndown")
#define NOTIFY_BUTTONUP         _T("buttonup") 
#define NOTIFY_DBCLICK          _T("dbclick")
#define NOTIFY_RBUTTONDOWN		_T("rbuttondown")
#define NOTIFY_RBUTTONUP        _T("rbuttonup") 
#define NOTIFY_MOUSEMOVE        _T("mousemove") 
#define NOTIFY_MOUSEENTER       _T("mouseenter") 
#define NOTIFY_MOUSELEAVE       _T("mouseleave") 
#define NOTIFY_CLICK		    _T("click")
#define NOTIFY_TIMER            _T("timer")
#define NOTIFY_ANIM_STOP        _T("animstop")
#define NOTIFY_SHOW_WINDOW      _T("showwindow")
#define NOTIFY_FILELINK_ERR		_T("filelinkerr")
#define NOTIFY_NOLONGER_TIP		_T("nolongertip")
#define NOTIFY_RICH_SETTING		_T("richsetting")

//添加滚动条通知事件
#define NOTIFY_SCROLL             _T("scroll")
#define NOTIFY_MOUSEWHEEL  _T("mousewheel")

class CControlUI;
// Structure for notifications from the system
// to the control implementation.
typedef struct tagTEventUI
{
	int Type;
	CControlUI* pSender;
	DWORD dwTimestamp;
	POINT ptMouse;
	TCHAR chKey;
	WORD  wKeyState;
	WPARAM wParam;
	LPARAM lParam;
} TEventUI;

// Structure for notifications to the outside world
typedef struct tagTNotifyUI 
{
	CStdString sType;     // 消息类型
	CStdString sClassName;// 消息发送者类名
	CControlUI* pSender;  // 消息发送者
	CControlUI* pOrigSender; // 消息发送者地址，只用于比较
	DWORD dwTimestamp;    // 时间戳
	POINT ptMouse;       // 消息产生时鼠标位置
	WPARAM wParam;       // 消息参数
	LPARAM lParam;       // 消息参数
} TNotifyUI;

// 消息响应接口
class INotifyUI
{
public:
	virtual bool Notify( TNotifyUI& msg ) = 0;
};

class ITranslateAccelerator
{
public:
	virtual LRESULT TranslateAccelerator(MSG *pMsg) = 0;
};

// MessageFilter interface
class IMessageFilterUI
{
public:
	virtual LRESULT MessageHandler( UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled ) = 0;
};

class CNotifyUIImpl;
typedef void (CNotifyUIImpl::*MSG_FUNC)(void);

union MessageMapFuncs
{
	MSG_FUNC pfn;   // generic member function pointer
	bool (INotifyUI::*pfn_bn)( TNotifyUI& msg );
	bool (INotifyUI::*pfn_bwlb)( WPARAM wParam, LPARAM lParam, bool& bHandled );
};

enum EMFuncType
{
	emFunc_vv = 0,		// 返回void 参数void
	emFunc_bn,			// 返回bool 参数TNOTIFYUI
	emFunc_bwlb			// 返回bool 参数WAPRAM LPARAM bool
};

enum UILIB_RESOURCETYPE
{
	UILIB_FILE=1,		// 来自磁盘文件
	UILIB_ZIP,			// 来自磁盘zip压缩包
	UILIB_RESOURCE,	    // 来自资源
	UILIB_ZIPRESOURCE,	// 来自资源的zip压缩包
};

#define MAX_EVENT_NAME_LEN	 32
#define MAX_CONTROL_NAME_LEN 32
struct MSGMAP_ENTRY
{
	unsigned int	m_dwEvent;	// 非自定义消息，此变量为0
	TCHAR			m_chEvent[MAX_EVENT_NAME_LEN];
	TCHAR			m_chControl[MAX_CONTROL_NAME_LEN];
	unsigned int	m_wSig;
	MSG_FUNC		m_pfn;   
};

struct MSGMAP
{
	const MSGMAP* pBaseMap;
	const MSGMAP_ENTRY* lpEntries;
};

// 变量定义
#define DECLARE_UI_MSG_MAP() \
private: \
	static const MSGMAP_ENTRY _messageEntries[]; \
protected: \
	static const MSGMAP messageMap; \
	virtual const MSGMAP* GetMessageMap() const; \


// 消息数组初始化 同 END_MSG_MAP配套使用 
#define BEGIN_UI_MSG_MAP( theClass, baseClass ) \
	const MSGMAP* theClass::GetMessageMap() const \
	{ return &theClass::messageMap; } \
	const MSGMAP theClass::messageMap = \
	{ &baseClass::messageMap, &theClass::_messageEntries[0] }; \
	const MSGMAP_ENTRY theClass::_messageEntries[] = \
	{ \


#define END_UI_MSG_MAP() \
	{ \
	0, _T(""), _T(""), 0, 0 } \
	}; \

#define MSG_KILLFOCUS( name, func ) \
	{ 0, NOTIFY_KILLFOCUS, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_SETFOCUS( name, func ) \
    { 0, NOTIFY_SETFOCUS, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_INIWINDOW( name, func ) \
    { 0, NOTIFY_INIWINDOW, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_TABLESELECT( name, func ) \
	{ 0, NOTIFY_TABLESELECT, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_RETURN( name, func ) \
    { 0, NOTIFY_RETURN, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_SHOWACTIVEX( name, func ) \
    { 0, NOTIFY_SHOWACTIVEX, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_MENU( name, func ) \
    { 0, NOTIFY_MENU, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_SELECT_CHANGED( name, func ) \
    { 0, NOTIFY_SELECT_CHANGED, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_LINK( name, func ) \
    { 0, NOTIFY_LINK, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_VALUECHANGED( name, func ) \
    { 0, NOTIFY_VALUECHANGED, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_TEXTCHANGED( name, func ) \
    { 0, NOTIFY_TEXTCHANGED, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_ITEMSELECT( name, func ) \
    { 0, NOTIFY_ITEMSELECT, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_DROPDOWN( name, func ) \
    { 0, NOTIFY_DROPDOWN, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_KEYDOWN( name, func ) \
    { 0, NOTIFY_KEYDOWN, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_BUTTONDOWN( name, func ) \
    { 0, NOTIFY_BUTTONDOWN, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_CHILD_BTNDOWN( name, func ) \
    { 0, NOTIFY_CHILD_BTNDOWN, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_BUTTONUP( name, func ) \
    { 0, NOTIFY_BUTTONUP, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_DBCLICK( name, func ) \
    { 0, NOTIFY_DBCLICK, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_MOUSEMOVE( name, func ) \
    { 0, NOTIFY_MOUSEMOVE, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_MOUSEENTER( name, func ) \
    { 0, NOTIFY_MOUSEENTER, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_MOUSELEAVE( name, func ) \
    { 0, NOTIFY_MOUSELEAVE, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_CLICK( name, func ) \
    { 0, NOTIFY_CLICK, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_TIMER( name, func ) \
	{ 0, NOTIFY_TIMER, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define USER_MSG( msgid, func ) \
    { msgid, _T(""), _T(""), emFunc_bwlb, (MSG_FUNC)(bool (CNotifyUIImpl::*)(WPARAM,LPARAM,bool&))&func },

#define MSG_ANIM_STOP( name, func ) \
	{ 0, NOTIFY_ANIM_STOP, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

// TNotifyUI的wParam决定是显示还是隐藏
#define MSG_SHOW_WINDOW( name, func ) \
	{ 0, NOTIFY_SHOW_WINDOW, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_ITEM_CLICK( name, func ) \
	{ 0, NOTIFY_ITEM_CLICK, name, emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },


class DIRECTUI_API CNotifyUIImpl : public INotifyUI, public IMessageFilterUI
{
public:
	CNotifyUIImpl(){}	
	virtual bool Notify( TNotifyUI& msg );
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

protected:
	virtual const MSGMAP* GetMessageMap() const;
	bool Invoke( const MSGMAP* pMsg, TNotifyUI& msg );
	void Invoke( const MSGMAP* pMsg, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled );

private: 
	static const MSGMAP_ENTRY _messageEntries[];

protected: 
	static const MSGMAP messageMap; 
};

}
#endif