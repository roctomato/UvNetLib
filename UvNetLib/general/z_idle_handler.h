#ifndef Z_IDLE_HANDLER_H
#define Z_IDLE_HANDLER_H

#include <uv.h>


class event_loop;

class z_idle_handler
{
public:
	int init_idle( uv_loop_t* loop);
	int init_idle( event_loop& loop);
	
	int start();
	int stop();
	
	virtual void on_idle() = 0;
private:
	uv_idle_t _idler;
};


#endif // Z_IDLE_HANDLER_H
