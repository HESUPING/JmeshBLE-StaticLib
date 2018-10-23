#include <stdio.h>
#include <stdlib.h>
#include"windows.h"
#include"src/driver/jmesh_uart.h"
#include"src/onchip_system/os_main.h"
#include"src/jmesh/jmesh_pdu.h"
#include"src/bearer/adv/jmesh_adv.h"
#include"src/bearer/beacon/jmesh_beacon.h"


int main()
{
    MSG msg;

    os_start();

    while(GetMessage(&msg,NULL,0,NULL)){
        if(msg.message== WM_TIMER){
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return 0;
}
