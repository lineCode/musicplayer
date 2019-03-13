#ifndef _OBSERVER_IMPL_BASE_H_
#define _OBSERVER_IMPL_BASE_H_
#include <map>

// 返回值ReturnT类型必须重载或者等价于重载bool函数：operator bool(){return true;}返回true代表消息不继续分发，false则继续分发，用法同dui
template <typename ReturnT, typename ParamT>
class ReceiverImplBase;

template <typename ReturnT, typename ParamT>
class ObserverImplBase
{
public:
	virtual void AddReceiver( ReceiverImplBase<ReturnT, ParamT>* receiver ) = 0;
	virtual void RemoveReceiver( ReceiverImplBase<ReturnT, ParamT>* receiver ) = 0;
	virtual ReturnT Broadcast( ParamT param ) = 0;
	virtual ReturnT RBroadcast( ParamT param ) = 0;
};

template <typename ReturnT, typename ParamT>
class ReceiverImplBase
{
public:
	virtual ReturnT Receive( ParamT param ) = 0;
};

template <typename ReturnT, typename ParamT>
class ReceiverImpl;

template <typename ReturnT, typename ParamT>
class ObserverImpl : public ObserverImplBase<ReturnT, ParamT>
{
	template <typename ReturnT, typename ParamT>
	friend class Iterator;
public:
	ObserverImpl()
	{}

	virtual ~ObserverImpl()	{}

	virtual void AddReceiver( ReceiverImplBase<ReturnT, ParamT>* receiver )
	{
		if ( NULL == receiver )
		{
			return;
		}

		receivers_.push_back( receiver );
	}

	virtual void RemoveReceiver( ReceiverImplBase<ReturnT, ParamT>* receiver )
	{
		if ( NULL == receiver )
		{
			return;
		}

		ReceiversVector::iterator it = receivers_.begin();
		for ( ; it != receivers_.end(); ++it )
		{
			if ( *it == receiver )
			{
				receivers_.erase( it );
				break;
			}
		}
	}

	virtual ReturnT Broadcast( ParamT param )
	{
		ReturnT Ret;
		ReceiversVector::iterator it = receivers_.begin();
		for ( ; it != receivers_.end(); ++it )
		{
			Ret = (*it)->Receive( param );
			if ( Ret )
			{
				break;
			}
		}

		return Ret;
	}

	virtual ReturnT RBroadcast( ParamT param )
	{
		ReceiversVector::reverse_iterator it = receivers_.rbegin();
		for ( ; it != receivers_.rend(); ++it )
		{
			(*it)->Receive( param );
		}

		return ReturnT();
	}

	template <typename ReturnT, typename ParamT>
	class Iterator
	{
		ObserverImpl<ReturnT, ParamT> & _tbl;
		DWORD index;
		ReceiverImplBase<ReturnT, ParamT>* ptr;
	public:
		Iterator( ObserverImpl & table )
			: _tbl( table ), index( 0 ), ptr( NULL )
		{}

		Iterator( const Iterator & v )
			: _tbl( v._tbl ), index( v.index ), ptr( v.ptr )
		{}

		ReceiverImplBase<ReturnT, ParamT>* next()
		{
			if ( index >= _tbl.receivers_.size() )
			{
				return NULL;
			}

			for ( ; index < _tbl.receivers_.size(); )
			{
				ptr = _tbl.receivers_[ index++ ];
				if ( ptr )
					return ptr;
			}
			return NULL;
		}
	};

protected:
	typedef std::vector<ReceiverImplBase<ReturnT, ParamT>*> ReceiversVector;
	ReceiversVector receivers_;
};


template <typename ReturnT, typename ParamT>
class ReceiverImpl : public ReceiverImplBase<ReturnT, ParamT>
{
public:
	ReceiverImpl(){}
	virtual ~ReceiverImpl()	{}
	virtual ReturnT Receive( ParamT param )
	{
		return ReturnT();
	}
};

#endif // _OBSERVER_IMPL_BASE_H_