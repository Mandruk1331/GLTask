#ifndef SHRPTR_H
#define SHRPTR_H

namespace CtrBlock
{
	struct _control_block_ {
	private:
		_control_block_(_control_block_ &cpyCtr) {};
		_control_block_ &operator=(_control_block_ &cpyCtr) {};
		int m_iCtn;

	public:
		_control_block_() :
			m_iCtn(0)
		{};

		void incCounter()
		{
			m_iCtn++;
		}

		int getCounter()
		{
			return m_iCtn;
		}

		void decCounter()
		{
			m_iCtn--;
		}

		void resetCounter()
		{
			m_iCtn = 0;
		}
	};
}

namespace MyStd
{
	template <typename _PtrTemplate_>
	class _shared_pointer_ {

	private:
		CtrBlock::_control_block_ *m_pCount;
		_PtrTemplate_ *m_pShared;

	public:
		~_shared_pointer_();
		//! Init shared pointer with data
		explicit _shared_pointer_(_PtrTemplate_ *ptr = nullptr);

		//! Overload ctr and assignment operator
		_shared_pointer_(_shared_pointer_<_PtrTemplate_> &ptrCpy);
		_shared_pointer_ &operator = (_shared_pointer_<_PtrTemplate_> &ptrCpyAssign);

		int UseCount();
		void SwapPtr(_shared_pointer_<_PtrTemplate_> &ptrSwap);
		_PtrTemplate_ *GetDataPtr();
	};


	//! -----------------------Function definitions-----------------------

	template <typename _PtrTemplate_>
	_shared_pointer_<_PtrTemplate_>::~_shared_pointer_()
	{
		if (m_pCount != nullptr)
		{
			m_pCount->decCounter();

			if (m_pCount->getCounter() == 0)
			{
				delete m_pCount;
				delete m_pShared;
				m_pCount = nullptr;
				m_pShared = nullptr;
			}
		}
	}

	//! Explicit ctr
	template<typename _PtrTemplate_>
	inline _shared_pointer_<_PtrTemplate_>::_shared_pointer_(_PtrTemplate_ *ptr) :
		m_pCount(nullptr)
	{
		if (ptr != nullptr)
		{
			m_pShared = ptr;
			m_pCount = new CtrBlock::_control_block_();
			m_pCount->incCounter();
		}
	}

	template<typename _PtrTemplate_>
	_shared_pointer_<_PtrTemplate_>::_shared_pointer_(_shared_pointer_<_PtrTemplate_> &ptrCpy)
	{
		m_pShared = ptrCpy.m_pShared;
		m_pCount = ptrCpy.m_pCount;
		m_pCount->incCounter();
	}

	template<typename _PtrTemplate_>
	_shared_pointer_<_PtrTemplate_> &_shared_pointer_<_PtrTemplate_>::operator=(_shared_pointer_<_PtrTemplate_> &ptrCpyAssign)
	{
		//! Call cpy ctr
		this->_shared_pointer_(ptrCpyAssign);
	}

	template<typename _PtrTemplate_>
	void _shared_pointer_<_PtrTemplate_>::SwapPtr(_shared_pointer_<_PtrTemplate_> &ptrSwap)
	{
		std::swap(ptrSwap.m_pCount, m_pCount);
		std::swap(ptrSwap.m_pShared, m_pShared);
	}

	template<typename _PtrTemplate_>
	_PtrTemplate_ *_shared_pointer_<_PtrTemplate_>::GetDataPtr()
	{
		return m_pShared;
	}

	template<typename _PtrTemplate_>
	int _shared_pointer_<_PtrTemplate_>::UseCount()
	{
		if (m_pCount == nullptr)
		{ 
			return 0;
		}

		return m_pCount->getCounter();
	}
}

#endif SHRPTR_H