#include "LsTimeVal.h"



typedef struct tm * ( *gettm) (const time_t *__timer);

bool IsSameDay( time_t t1, time_t  t2, bool isGmt)
{
    gettm fn = isGmt ? gmtime:localtime;
    struct tm curTm= *fn( &t1 );

    struct tm  lastTm = *fn( &t2 );
    if ( curTm.tm_year == lastTm.tm_year
         && curTm.tm_mon == lastTm.tm_mon
         && curTm.tm_mday == lastTm.tm_mday ) { //同一天
        return true;
    }
    return false;
}


LsUInt32 GetSameDayTimeStamp(LsUInt32 resetVitalityTime, LsUInt32 ct)
{
	time_t  curTime = ct;
	short ss = resetVitalityTime % 100;

	LsUInt32 temp = resetVitalityTime / 100;
	short mm  = temp % 100;
	short hh  =  temp / 100;
	//SYS_INFO( "update time %02d:%02d:%02d", _hh, _mm, _ss );

	struct tm* curTm= localtime( (time_t*)(&curTime) );
	//SYS_INFO( "cur time %02d:%02d:%02d",  curTm->tm_hour, curTm->tm_min, curTm->tm_sec );
	struct tm last;
	last = *curTm;
	last.tm_hour = hh;
	last.tm_min   = mm;
	last.tm_sec   = ss;
	return mktime( & last );
}

LsInt32 GetLeftTimeToday(LsInt32 curTime)
{
	time_t t = time(0);   // get time now  
	struct tm * zeroTm= localtime(&t);  
	unsigned long long zeroTime = 0;
	int left_time = 0;
	if( zeroTm ){
	
		zeroTm->tm_hour = 0;  
		zeroTm->tm_min = 0;  
		zeroTm->tm_sec = 0;  
		zeroTime = mktime(zeroTm);  
		left_time = zeroTime + 24 * 3600 - curTime;
		
	}
	
	if( left_time < 0 ){
		left_time = 0;
	}
	return left_time;
}



unsigned  int GetDate(time_t t )
{
	unsigned  int ret = 0;
	struct tm * tm = localtime( &t );
	ret = (tm->tm_year + 1900) * 100;
	ret  = (ret + tm->tm_mon+1)*100;
	ret += tm->tm_mday;
	return ret;
}
unsigned  int GetHms(time_t t )
{
	unsigned  int ret = 0;
	struct tm * tm = localtime( &t );
	ret = tm->tm_hour * 100;
	ret  = (ret + tm->tm_min)*100;
	ret += tm->tm_sec;
	return ret;
}
int GetTimeZone()
{
	time_t t1;
	time_t  t2;
	t2 = time( &t1 );
	struct tm * ptm1 =  gmtime ( &t1 );
	int hour1 = ptm1->tm_hour;
	struct tm * ptm2 =  localtime( &t2);
	int hour2 =  ptm2->tm_hour;
	if (  hour2 > hour1 )
		return hour2 - hour1;
	else if ( hour2 < hour1 )
		return  hour2 + 24  - hour1;
	
	return 0;
}
unsigned int GetDateHms(time_t t)
{
    unsigned int date = GetDate( t )% 100;
    unsigned int hhmmss = GetHms( t);
    return date* 10000+ hhmmss;
}


int GetTodaySec(time_t t)
{
	int sec = 0;
	struct tm * tm = localtime( &t );
	sec += (tm->tm_hour * 3600);
	sec += (tm->tm_min * 60);
	sec += tm->tm_sec;
	return sec;
}

int GetWeekSec( time_t t )
{
	int sec = 0;
	struct tm * tm = localtime( &t );
	sec += (tm->tm_wday) * 24 * 3600;
	sec += (tm->tm_hour * 3600);
	sec += (tm->tm_min * 60);
	sec += tm->tm_sec;
	return sec;
}

int GetWeekDay(time_t t)
{
	struct tm * tm = localtime( &t );
	return tm->tm_wday;
}