#include "sdk_test.h"
#include "sdk_tts.h"
#include "sdk_http.h"
#include "sdk_file.h"

int test_menu()
{
	int ret = 0;
	char *items[]={
		"tts test",
		"file test",
		"http test",
		"https test",
		"qr test"
	};

	int itemcount =  sizeof(items)/ sizeof(items[0]);
	while ( ret >=0 && ret < itemcount  ){
		ret = gui_select_page_ex( "test" , items,itemcount , 60000, ret );
		if(ret == 0){
			sdk_tts_test();
		}
		else if(ret == 1){
			fileTest();
		}
		else if(ret == 2){
			sdk_http_test();
		}
		else if(ret == 3){
			sdk_https_test();
		}
		else if(ret == 4){
			sdk_showQr("C1235558440;100,00;My coffee shop;0");
		}
	}
	return ret;

}