#ifndef __LS_ILOCK_H__
#define __LS_ILOCK_H__

/*! \brief 各种读写锁的统一接口
 *
 *   该抽象类包括四个纯虚函数:
 *   ReadLock()   上读取锁.
 *   ReadUnlock()  解读取锁
 *   WriteLock()   上写入锁.
 *   WriteUnlock()  解写入锁
 */
class IRWLock {
public:
    virtual ~IRWLock() = 0;
	virtual void ReadLock() = 0;
	virtual void ReadUnlock() = 0;
	virtual void WriteLock() = 0;
	virtual void WriteUnlock() = 0;
};
/*! \brief 各种类型锁的统一接口
 *
 *   该抽象类包括三个纯虚函数:
 *   Lock() 上锁.
 *   TryLock() 尝试上锁，锁住返回true,失败返回false.
 *   Unlock() 解锁
 */
class ILock {
public:
    virtual ~ILock(){}
	virtual void Lock() = 0;
	virtual bool TryLock() = 0;
	virtual void Unlock() = 0;
	virtual void UnlockEx(bool bYield = true) =0;
};

/*! \brief 实现一种无锁的锁接口
 *
 *  该类主要用于某些需要锁的代码转换成不要锁的代码时，简单替换原先的锁类
 */
class NullLock: public ILock {
public:
    virtual ~NullLock(){}

	virtual void Lock() {
	}
	virtual bool TryLock() {
		return true;
	}
	virtual void Unlock() {
	}
	void UnlockEx(bool bYield = true) {
	}
};

/*! \brief 自动锁
 *
 *  在构造函数中上锁，在析构函数中解锁
 */
class CAutoLocker {
public:
	CAutoLocker(ILock* pCurLock_) :
			_pLock(pCurLock_) {
		if (_pLock)
			_pLock->Lock();
	}

	~CAutoLocker() {
		if (_pLock)
			_pLock->Unlock();
	}

private:
	ILock* _pLock;
};

#endif
