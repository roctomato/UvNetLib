#include "appnetstack.h"
#include "zby_debug.h"
#include "sys_tools.h"

#define CMMD_BUF_LEN  1024

AppNetStack* AppNetStack::s_ins = NULL;

AppNetStack::AppNetStack():_iApp(NULL)
,event_loop(true)
{
	_daemon = false;
	_bExit = false;
    this->_asyncCmmd.Init(this->loop(),CMMD_BUF_LEN);
}

AppNetStack::~AppNetStack()
{
}

AppNetStack* AppNetStack::Instance()
{
	if ( NULL == s_ins ){
		s_ins = new AppNetStack();
	}
	return s_ins;
}

pid_t AppNetStack::ReadPid()
{
	pid_t pid = 0;
	FILE * fp = fopen( _pidFile.c_str(),"r");
	if ( fp )
	{
		fscanf(fp,"%u", &pid );
		fclose(fp);
	}
	return pid;
}

bool AppNetStack::WritePid()
{
	FILE * fp = fopen(_pidFile.c_str(),"w");
	if ( NULL == fp )
		return false;
		
	fprintf(fp,"%u", getpid() );
    fclose(fp);
	return true;
}

bool AppNetStack::Init(int argv, char* argc [], IAppStart* ia)
{
	bool ret = true;
	this->_iApp = ia;
	std::string name = argc[0];
	GenPidFileName( &name[0]);
	if ( ia ){
		ret = ia->Init( argv, argc, this );
	}
	return ret;
}
void AppNetStack::GenPidFileName(char* app)
{
	const char * delim =  "\\/";
	char* last;
	char *pch = strtok( app, delim );
	while( pch != NULL ){
		last = pch;
		pch  = strtok( NULL, delim );
	}
	
	this->_pidFile = last;
    this->_pidFile += ".pid";
	SYS_DEBUG( "PIDFILE %s", this->_pidFile.c_str() );
}

bool AppNetStack::StartWork()
{
	bool ret = true;
	if (  _daemon && daemonize() )
	{
		return false;
	}
	_bExit = false;
	
	SetSignal();
	
	if ( this->_iApp ){
		ret = this->_iApp->StartWork(this);
	}
	
	if ( ret  ){
        this->WritePid();
        PushCammand<AppNetStack>(  this,  & AppNetStack::OnStart, NULL, 0 );
		this->run();
        this->close();
	}
	return ret;
}

static void
sigint_cb (uv_signal_t* handle, int signum)
{
	AppNetStack::Instance()->StopApp();
}

void AppNetStack::SetSignal()
{
	uv_signal_t* aev[] = { 
        &this->INT_signal_watcher
#ifndef __WIN32__
        , &this->QUIT_signal_watcher
#endif
        , &this->TERM_signal_watcher };
        
	int signal[]     = { 
      SIGINT
#ifndef __WIN32__
    , SIGQUIT
#endif
    , SIGTERM };
	for( int i = 0; i < ARRAY_SIZE(aev); i ++ ){
		 uv_signal_init ( this->loop(), aev[i]);
		 uv_signal_start( aev[i], sigint_cb, signal[i]);
	}
}

void AppNetStack::StopApp()
{
    _bExit =true;
    PushCammand<AppNetStack>(  this,  & AppNetStack::OnExit, NULL, 0 );
}

void AppNetStack::Kill()
{
	pid_t pid = ReadPid();
#ifndef __WIN32__
	kill (pid, SIGINT);
#endif
}

bool AppNetStack::OnStart(void* pBuf, int len)
{
	SYS_INFO( "stack start");
	if (this->_iApp ){
		this->_iApp->OnstackStart(this);
	}
	return true;
}
bool AppNetStack::OnExit(void* pBuf, int len)
{
    SYS_INFO( "stack exit");
    if ( NULL == this->_iApp ||  this->_iApp->AllowExit(this) ){
        if (this->_iApp ){
            this->_iApp->OnExit(this);
        }
        int ret =this->stop();
        
        
        if ( ret){
            SYS_INFO("EXIT result %d %s", ret, uv_strerror(ret));
        }
          
    }
    return true;
}
