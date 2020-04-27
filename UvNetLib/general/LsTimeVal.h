#pragma once
#include <sys/time.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <typeinfo>

#include <list>
#include <string>

#include "z_typedef.h"

bool IsSameDay( time_t t1, time_t  t2, bool isGmt);

LsUInt32 GetSameDayTimeStamp( LsUInt32 resetVitalityTime, LsUInt32 curTime);
LsInt32 GetLeftTimeToday(LsInt32 curTime);
unsigned  int GetDate(time_t t );
unsigned  int GetHms(time_t t );
unsigned  int GetDateHms(time_t t );
int GetTodaySec( time_t t );
int GetWeekSec( time_t t );
int GetWeekDay( time_t t );
int GetTimeZone();//当前时区


struct LsTimeVal : public timeval {
	LsTimeVal() {
		this->tv_sec = 0;
		this->tv_usec = 0;
	}
	void operator +=(int64_t ms) {
		this->tv_sec = this->tv_sec + ms / 1000;
		this->tv_usec = this->tv_usec + (ms % 1000) * 1000;
		if (this->tv_usec > 1000000) {
			this->tv_usec -= 1000000;
			this->tv_sec++;
		}
	}

	//return ms
	int64_t  operator -(const struct LsTimeVal& v) {
		return (this->tv_sec - v.tv_sec) * (int64_t)1000
			+ (this->tv_usec - v.tv_usec) / 1000;
	}

	bool operator <(const struct LsTimeVal& v) {
		if (this->tv_sec < v.tv_sec)
			return true;
		if (this->tv_sec >= v.tv_sec)
			return false;
		return this->tv_usec < v.tv_usec;
	}

	bool operator >=(const struct LsTimeVal& v) {
		if (this->tv_sec > v.tv_sec)
			return true;
		if (this->tv_sec < v.tv_sec)
			return false;
		return this->tv_usec >= v.tv_usec;
	}

	bool operator <=(const struct LsTimeVal& v) {
		if (this->tv_sec < v.tv_sec)
			return true;
		if (this->tv_sec > v.tv_sec)
			return false;
		return this->tv_usec <= v.tv_usec;
	}
	void GetNow() {
		gettimeofday(this, NULL);
	}

	int64_t PassTime(LsTimeVal* pTime) {
		int64_t ret = 0;
		if (pTime) {
			ret = (this->tv_sec - pTime->tv_sec) * (int64_t)1000
				+ (this->tv_usec - pTime->tv_usec) / 1000;
		}
		return ret;
	}
	std::string GetUtcTimeStr() {
		char temp[64];
        time_t t = this->tv_sec;
		struct tm * tm = gmtime(&t);
		sprintf(temp, "%04d-%02d-%02d %02d:%02d:%02d"
			, (tm->tm_year + 1900)
			, tm->tm_mon + 1
			, tm->tm_mday
			, tm->tm_hour
			, tm->tm_min
			, tm->tm_sec);

		return temp;
	}
	std::string GetDateTimeStr() {
		char temp[64];
        time_t t = this->tv_sec;
		struct tm * tm = localtime(&t);
		sprintf(temp, "%04d-%02d-%02d %02d:%02d:%02d"
			, (tm->tm_year + 1900)
			, tm->tm_mon + 1
			, tm->tm_mday
			, tm->tm_hour
			, tm->tm_min
			, tm->tm_sec);
		return temp;
	}

};



class UseTime{
public:
	UseTime(){
		_start.GetNow();
	}
	
	long GetPassTime(){
		LsTimeVal cur;
		cur.GetNow();
		return cur.PassTime(&_start);
	}
	void Reset(){
		_start.GetNow();
	}
private:
	LsTimeVal _start;
};
