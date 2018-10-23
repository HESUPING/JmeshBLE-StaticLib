#include"jmesh_features.h"
#include"jmesh_save.h"
#include"jmesh_types.h"

static struct st_jmesh_features{
    union{
        unsigned char features;
        struct{
            unsigned char proxy:2;
            unsigned char friend:2;
            unsigned char relay:2;
            unsigned char lowpower:2;
        };
    };
}jmesh_features;

void jmesh_features_init(void){
    if(1!=jmesh_save_read(JMESH_SAVE_FEATURES,1,&jmesh_features.features)){
        jmesh_features.proxy=JMESH_FEATURE_PROXY;
        jmesh_features.friend=JMESH_FEATURE_FRIEND;
        jmesh_features.relay=JMESH_FEATURE_RELAY;
        jmesh_features.lowpower=JMESH_FEATURE_LOWPOWER;
    }
}

unsigned char jmesh_get_proxy_feature(void){
    return jmesh_features.proxy;
}
unsigned char jmesh_get_friend_feature(void){
    return jmesh_features.friend;
}
unsigned char jmesh_get_relay_feature(void){
    return jmesh_features.relay;
}
unsigned char jmesh_get_lowpower_feature(void){
    return jmesh_features.lowpower;
}

int jmesh_set_proxy_feature(unsigned char feature){
    if(JMESH_FEATURE_PROXY==JMESH_FEATURE_UNSUPPORTED||feature>=JMESH_FEATURE_UNSUPPORTED){
        return JMESH_STATUS_CANNOT_SET;
    }
    jmesh_features.proxy=feature;
    jmesh_save_write(JMESH_SAVE_FEATURES,1,&jmesh_features.features);
    return JMESH_STATUS_SUCCESS;
}
int jmesh_set_friend_feature(unsigned char feature){
    if(JMESH_FEATURE_FRIEND==JMESH_FEATURE_UNSUPPORTED||feature>=JMESH_FEATURE_UNSUPPORTED){
        return JMESH_STATUS_CANNOT_SET;
    }
    jmesh_features.friend=feature;
    jmesh_save_write(JMESH_SAVE_FEATURES,1,&jmesh_features.features);
    return JMESH_STATUS_SUCCESS;
}
int jmesh_set_relay_feature(unsigned char feature){
    if(JMESH_FEATURE_RELAY==JMESH_FEATURE_UNSUPPORTED||feature>=JMESH_FEATURE_UNSUPPORTED){
        return JMESH_STATUS_CANNOT_SET;
    }
    jmesh_features.relay=feature;
    jmesh_save_write(JMESH_SAVE_FEATURES,1,&jmesh_features.features);
    return JMESH_STATUS_SUCCESS;
}
int jmesh_set_lowpower_feature(unsigned char feature){
    if(JMESH_FEATURE_LOWPOWER==JMESH_FEATURE_UNSUPPORTED||feature>=JMESH_FEATURE_UNSUPPORTED){
        return JMESH_STATUS_CANNOT_SET;
    }
    jmesh_features.lowpower=feature;
    jmesh_save_write(JMESH_SAVE_FEATURES,1,&jmesh_features.features);
    return JMESH_STATUS_SUCCESS;
}
