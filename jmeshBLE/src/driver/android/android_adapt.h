#ifndef ANDROID_ADAPT_H
#define ANDROID_ADAPT_H

enum{
    ANDROID_SHARE_1=0


};

int android_request(int type,int length,unsigned char* data,int ret_size,unsigned char* ret_buffer);


#endif // ANDROID_ADAPT_H
