#include"test_app_server_callback.h"
#include "../../onchip_system/os_timer_event.h"
#include "../app_include.h"
#include "../../jmesh/jmesh_print.h"
#include"../../network/jmesh_seq.h"
#include"../../onchip_system/os_queue.h"
static os_timer_event_t test_timer;
static unsigned short test_num;
static unsigned short test_aid;
static unsigned char test_repeats;
static unsigned char test_interval;
static unsigned char current_repeat = 0;
static unsigned short test_start_id=0;

void test_process(void){
			
	current_repeat++;		
	
	if(current_repeat > test_repeats || test_result.test_seq ==0){
		if(test_result.sent >=test_num) return;
		test_result.sent++;
		current_repeat = 0;
	}				
	test_result.test_seq = jmesh_seq_get()&0xffff;	
	test_client_send(test_result.dst, test_aid,test_start_id,test_result.sent,test_result.test_seq);				
	os_timer_event_restart(&test_timer);
}

void test_server_start_callback(unsigned short addr,unsigned short aid,unsigned short num,unsigned char repeat,unsigned char interval){
    test_result.dst=addr;
    test_num=num;
	test_repeats = repeat;
	test_interval = interval;
	if(test_repeats == 0)  test_result.sent = 0;
    else test_result.sent = 1;
	test_result.responsed = 0;
	test_result.received = 0;
	test_result.test_seq = 0xffff;
	current_repeat = 0;
    test_aid=aid;
    test_start_id++;
	if(interval <5) interval = 5;
    os_timer_event_set(&test_timer,interval*100,(os_timer_event_caller_t)test_process,NULL);
    print_info("test start addr %x,aid %x,num %x\n",addr,aid,num);
}
unsigned short jmesh_server_data_callback(unsigned short src,unsigned short nid,unsigned short start_id,unsigned short tid){

    static unsigned short test_received=0;
    static unsigned short test_src=0;
	static unsigned short temp_tid = 0;
    if(test_src!=src||test_start_id!=start_id){
        test_received=0;
        test_src=src;
        test_start_id=start_id;
		temp_tid = 0;
    }
	if(tid>temp_tid)
	{
		temp_tid = tid;
		test_received++;			
	}
    return test_received;
}