#ifndef __DUI_DELEGATE_H__
#define __DUI_DELEGATE_H__

#pragma once

namespace DirectUICore {
// ί��ģʽ�е������
class DIRECTUI_API CDelegateBase	 
{
public:
	// ���캯����pObjectΪί���ߵĶ��� pFnΪִ�з���
    CDelegateBase( void* pObject, void* pFn );
	// �������캯��
    CDelegateBase( const CDelegateBase& rhs );
    virtual ~CDelegateBase();
	// �Ƚ�����ί����, true һ�� false��ͬ
    bool Equals( const CDelegateBase& rhs ) const;
	// ��Ӧί�н��д���
    bool operator() ( void* param );
	// ����һ��ί����
    virtual CDelegateBase* Copy() const = 0; // add const for gcc

protected:
	// �õ�ִ�з���
    void* GetFn();
	// �õ�ί���߶���
    void* GetObject();
	// ����ִ�з���
    virtual bool Invoke( void* param ) = 0;

private:
    void* m_pObject;	// ί����
    void* m_pFn;		// ִ�з���
};

// ��̬ί�У�ί����Ϊ�գ�����ִ�й���
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
// ί�У�ί���߲�Ϊ��
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
// ����ί��
CDelegate<O, T> MakeDelegate(O* pObject, bool (T::* pFn)(void*))
{
    return CDelegate<O, T>(pObject, pFn);
}

inline CDelegateStatic MakeDelegate(bool (*pFn)(void*))
{
    return CDelegateStatic(pFn); 
}

// �¼�Դ
class DIRECTUI_API CEventSource
{
    typedef bool (*FnType)(void*);
public:
    ~CEventSource();
    operator bool();
	// ����һ��ί����
    void operator+= ( const CDelegateBase& d ); // add const for gcc
    void operator+= ( FnType pFn );
	// ɾ��һ��ί����
    void operator-= ( const CDelegateBase& d );
    void operator-= ( FnType pFn );
	// ��Ӧ�¼����д���
    bool operator() ( void* param );

protected:
    CStdPtrArray m_aDelegates;	// ί�����б�
};

} // namespace DirectUICore

#endif // __UIDELEGATE_H__