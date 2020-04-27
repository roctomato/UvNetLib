#include "z_idle_handler.h"
#include "event_loop.h"


static void idle_handler(uv_idle_t* handle)
{
	z_idle_handler* p_handler = (z_idle_handler*)handle->data;
	if (p_handler){
		p_handler->on_idle();
	}
}


int z_idle_handler::init_idle(event_loop& loop)
{
	return init_idle( loop.loop());
}

int z_idle_handler::init_idle(uv_loop_t* loop)
{
	_idler.data = this;
	return uv_idle_init(loop, &_idler);
}

int z_idle_handler::start()
{
	return uv_idle_start( &_idler, &idle_handler);
}

int z_idle_handler::stop()
{
	return uv_idle_stop(&_idler);
}

