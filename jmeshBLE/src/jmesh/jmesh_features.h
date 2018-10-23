#ifndef JMESH_FEATURES_H
#define JMESH_FEATURES_H


#define JMESH_FEATURE_DISABLE     0
#define JMESH_FEATURE_ENABLE      1
#define JMESH_FEATURE_UNSUPPORTED 2

void jmesh_features_init(void);

unsigned char jmesh_get_proxy_feature(void);
unsigned char jmesh_get_friend_feature(void);
unsigned char jmesh_get_relay_feature(void);
unsigned char jmesh_get_lowpower_feature(void);

int jmesh_set_proxy_feature(unsigned char feature);
int jmesh_set_friend_feature(unsigned char feature);
int jmesh_set_relay_feature(unsigned char feature);
int jmesh_set_lowpower_feature(unsigned char feature);


#endif // JMESH_FEATURES_H
