#ifndef __IEVENT_H__
#define __IEVENT_H__

class IEvent {
public:
    virtual ~IEvent(){}
	virtual bool WaitEvent(int timeout_) = 0;
	virtual void SetEvent() = 0;
	virtual void ResetEvent() = 0;
	virtual int SetEventEx(bool broadcast) =0;
};

class NullEvent: public IEvent {
public:
    virtual ~NullEvent(){}

	bool WaitEvent(int timeout_) {
		return true;
	}
	void SetEvent() {
	}
	void ResetEvent() {
	}
	int SetEventEx(bool broadcast) {
		return 0;
	}
};

#endif
