#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include <uv.h>



class event_loop
{
public:
	event_loop(bool use_default = true);
	~event_loop();
	int run( uv_run_mode mode = UV_RUN_DEFAULT);
	int close();
	int stop();
    
    int alive();
    
    
	uv_loop_t* loop(){ return _loop;}
private:
	bool        _use_default;
	uv_loop_t*  _loop; 
    
   
};



#endif // EVENT_LOOP_H
