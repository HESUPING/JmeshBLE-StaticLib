
#ifndef MESH_IV_UPDATE_TEST_H_
#define MESH_IV_UPDATE_TEST_H_


typedef enum
{
    SCENE_IVUPDATE_AND_BIG_ONE = 2,
    SCENE_IVUPDATE_LESS_FT,
    SCENE_IVUPDATE_BIG_FT,
    SCENE_IVUPDATE_PROC_IN
} mesh_iv_update_scene_cmd;



void iv_update_beacon_stub(void);
void iv_update_beacon_stub_iv(void);
void iv_update_ivrefresh_scene(uint32_t scene);


#endif
