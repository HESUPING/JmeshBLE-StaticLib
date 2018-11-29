#ifndef TEST_APP_CLIENT_CALLBACK_H
#define TEST_APP_CLIENT_CALLBACK_H


void test_client_start_status_callback(unsigned short src,unsigned short addr,unsigned short num);

void test_client_data_status_callback(unsigned short src,unsigned short tid,unsigned short received,unsigned short test_seq);

void test_client_result_status_callback(unsigned short src,unsigned short addr,unsigned short sent,unsigned short received,unsigned short responsed);
#endif

