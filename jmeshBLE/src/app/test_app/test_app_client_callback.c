#include"test_app_client_callback.h"
#include "../../jmesh/jmesh_print.h"
#include "../app_include.h"
#include"../../onchip_system/os_queue.h"
#if (JMESH_DRIVER_ANDROID)
#include "../../driver/android/JAA_adapt.h"
#endif
test_result_t test_result;
void test_client_start_status_callback(unsigned short src,unsigned short addr,unsigned short num)
{
    print_info("test dest %x addr %x num %d start success\n",src,addr,num);
//    JAA_pdu_t pdu;
//    pdu.type=JAA_APP_TEST;
//    pdu.len=7;
//    pdu.pdu[0]=0;
//    JMESH_BIG_ENDIAN_FILL2(src,pdu.pdu+1);
//    JMESH_BIG_ENDIAN_FILL2(addr,pdu.pdu+3);
//    JMESH_BIG_ENDIAN_FILL2(num,pdu.pdu+5);
//    JAA_adapt_send(&pdu);
}

void test_client_data_status_callback(unsigned short src,unsigned short tid,unsigned short received,unsigned short test_seq)
{
    print_info("test data received src %x,tid %d,received %d\n",src,tid,received);

		if(test_result.test_seq == test_seq)
		{
				test_result.received=received;
				test_result.responsed++;
				test_result.test_seq = 0;					
		}
}

void test_client_result_status_callback(unsigned short src,unsigned short addr,unsigned short sent,unsigned short received,unsigned short responsed)
{
    print_info("rest data result src %x,sent %d,received %d,responsed %d\n",src,sent,received,responsed);
//    JAA_pdu_t pdu;
//    pdu.type=JAA_APP_TEST;
//    pdu.len=11;
//    pdu.pdu[0]=1;
//    JMESH_BIG_ENDIAN_FILL2(src,pdu.pdu+1);
//    JMESH_BIG_ENDIAN_FILL2(addr,pdu.pdu+3);
//    JMESH_BIG_ENDIAN_FILL2(sent,pdu.pdu+5);
//    JMESH_BIG_ENDIAN_FILL2(received,pdu.pdu+7);
//    JMESH_BIG_ENDIAN_FILL2(responsed,pdu.pdu+9);
//    JAA_adapt_send(&pdu);
}