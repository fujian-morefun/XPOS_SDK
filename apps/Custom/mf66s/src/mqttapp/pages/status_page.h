#pragma once

typedef enum {
	page_status,
	page_waiting,
	page_qr,
}e_pagemode;


void status_page_showqr(const char *qr);
void status_page_showwaiting(const char *msg);


void status_page();
