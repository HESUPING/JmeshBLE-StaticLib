#include"os_ram.h"

#define OS_RAM_END (OS_RAM_SIZE/2)

static unsigned short os_ram[OS_RAM_END];

void os_ram_init(void)
{
    os_ram[0]=OS_RAM_END;
    os_ram[1]=2;
}
void* os_ram_malloc(unsigned short size)
{
    unsigned short p,q;

    size=(size+1)/2;
    size+=2;

    p=0;
    do{
        if(os_ram[p]-os_ram[p+1]-p>=size){
            q=p+os_ram[p+1];
            os_ram[q]=os_ram[p];
            os_ram[q+1]=size;
            os_ram[p]=q;
            return os_ram+q+2;
        }
        p=os_ram[p];
    }while(p<OS_RAM_END);
    return NULL;
}
void os_ram_free(void* ptr)
{
    unsigned short p,q;

    p=0;
    q=os_ram[0];
    while(q<OS_RAM_SIZE){
        if(os_ram+q+2==(unsigned short*)ptr){
            os_ram[p]=os_ram[q];
            return;
        }
        p=q;
        q=os_ram[p];
    }
}

