#include <stdlib.h>
#include "event_loop.h"


event_loop::event_loop(bool use_default)
	:_use_default(use_default)
{
	if ( _use_default ) {
		_loop = ::uv_default_loop();
	} else {
		_loop = (uv_loop_t*)malloc(sizeof(uv_loop_t));
		uv_loop_init(_loop);
	}
	_loop->data = this;
}

event_loop::~event_loop()
{
	if ( !_use_default ) {
		free( _loop );
	}
}

int event_loop::close()
{
	return uv_loop_close(_loop);
}

int event_loop::run(uv_run_mode mode)
{
	return uv_run(_loop, mode);
}

int event_loop::stop()
{
     uv_stop(_loop);
     return 0;
}

int event_loop::alive()
{
    return uv_loop_alive(_loop);
}

