#ifndef __DUI_DELEGATE_H__
#define __DUI_DELEGATE_H__

#pragma once

namespace DirectUICore {
// 委托模式中的虚基类
class DIRECTUI_API CDelegateBase	 
{
public:
	// 构造函数，pObject为委托者的对象， pFn为执行方法
    CDelegateBase( void* pObject, void* pFn );
	// 拷贝构造函数
    CDelegateBase( const CDelegateBase& rhs );
    virtual ~CDelegateBase();
	// 比较两个委托者, true 一致 false不同
    bool Equals( const CDelegateBase& rhs ) const;
	// 响应委托进行处理
    bool operator() ( void* param );
	// 拷贝一个委托者
    virtual CDelegateBase* Copy() const = 0; // add const for gcc

protected:
	// 得到执行方法
    void* GetFn();
	// 得到委托者对象
    void* GetObject();
	// 调用执行方法
    virtual bool Invoke( void* param ) = 0;

private:
    void* m_pObject;	// 委托者
    void* m_pFn;		// 执行方法
};

// 静态委托，委托者为空，但有执行过程
class CDelegateStatic: public CDelegateBase
{
    typedef bool (*Fn)(void*);
public:
    CDelegateStatic( Fn pFn ) : CDelegateBase(NULL, pFn) { } 
    CDelegateStatic( const CDelegateStatic& rhs ) : CDelegateBase(rhs) { } 
    virtual CDelegateBase* Copy() const { return new CDelegateStatic(*this); }

protected:
    virtual bool Invoke( void* param )
    {
        Fn pFn = (Fn)GetFn();
        return (*pFn)(param); 
    }
};

template <class O, class T>
// 委托，委托者不为空
class CDelegate : public CDelegateBase
{
    typedef bool (T::* Fn)(void*);
public:
    CDelegate( O* pObj, Fn pFn ) : CDelegateBase(pObj, &pFn), m_pFn(pFn) { }
    CDelegate( const CDelegate& rhs ) : CDelegateBase(rhs) { m_pFn = rhs.m_pFn; } 
    virtual CDelegateBase* Copy() const { return new CDelegate(*this); }

protected:
    virtual bool Invoke( void* param )
    {
        O* pObject = (O*) GetObject();
        return (pObject->*m_pFn)(param); 
    }  

private:
    Fn m_pFn;
};

template <class O, class T>
// 产生委托
CDelegate<O, T> MakeDelegate(O* pObject, bool (T::* pFn)(void*))
{
    return CDelegate<O, T>(pObject, pFn);
}

inline CDelegateStatic MakeDelegate(bool (*pFn)(void*))
{
    return CDelegateStatic(pFn); 
}

// 事件源
class DIRECTUI_API CEventSource
{
    typedef bool (*FnType)(void*);
public:
    ~CEventSource();
    operator bool();
	// 加入一个委托者
    void operator+= ( const CDelegateBase& d ); // add const for gcc
    void operator+= ( FnType pFn );
	// 删除一个委托者
    void operator-= ( const CDelegateBase& d );
    void operator-= ( FnType pFn );
	// 响应事件进行处理
    bool operator() ( void* param );

protected:
    CStdPtrArray m_aDelegates;	// 委托者列表
};

} // namespace DirectUICore

#endif // __UIDELEGATE_H__