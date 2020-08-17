#ifndef _MF_RTC_H_
#define _MF_RTC_H_

#ifdef __cplusplus
extern "C" {
#endif

struct rtc_time {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

int mf_rtc_init(void);

int mf_rtc_set_time(struct rtc_time *tm);
int mf_rtc_get_time(struct rtc_time *tm);

#ifdef __cplusplus
}
#endif

#endif /* __MF_RTC_H */


