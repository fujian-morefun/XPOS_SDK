#pragma once

/**
* 输入金额界面。允许输入的金额最大值为9999999.99
* @title      [IN] 标题
* @maxLength  [IN] 最大长度，超过9默认为9
* @timeOver   [IN] 超时时间，秒为单位
* @return :   超时退出返回INPUT_INPUT_RET_TIMEOVER，按取消键退出返回INPUT_INPUT_RET_QUIT，否则返回输入的金额。分为单位
*			
*/
long long emv_inputamount_page(char* title, int maxLength, int timeOver);
