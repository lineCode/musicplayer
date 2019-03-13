// 不知道干嘛的
#ifndef __DUI_TOOL_H__
#define __DUI_TOOL_H__

namespace DirectUICore 
{

class DIRECTUI_API CToolStripUI : public CHorizontalLayoutUI 
{
public:
	CToolStripUI();
	LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);
};

class DIRECTUI_API CToolStripButtonUI : public COptionUI 
{
public:
	CToolStripButtonUI();
	LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);
};

}

#endif // __UITOOL_H__