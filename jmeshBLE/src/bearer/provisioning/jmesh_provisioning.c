#include "jmesh_provisioning.h"
#include "../../onchip_system/os_timer_event.h"
#include "../../onchip_system/os_core.h"
#include"../../driver/jmesh_system.h"
#include"../../jmesh/jmesh_types.h"
#include"../../jmesh/jmesh_print.h"
#include"../../secure/AES_CMAC/toolbox/security_kn.h"

uint8_t LEN_PROVISION_PARAMETERS[] = {
    [Prov_Invite]        = 1,
    [Prov_Capabilities]  = 11,
    [Prov_Start]         = 5,
    [Prov_Public_Key]    = 64,
    [Prov_Input_Complete]= 0,
    [Prov_Confirmation]  = 16,
    [Prov_Random]        = 16,
    [Prov_Data]          = 33,
    [Prov_Complete]      = 0,
    [Prov_Failed]        = 1,
};

oob_output_action_t OOB_Blink                   = NULL;
oob_output_action_t OOB_Blink_stop              = NULL;
oob_output_action_t OOB_Beep                    = NULL;
oob_output_action_t OOB_Beep_stop               = NULL;
oob_output_action_t OOB_Vibrate                 = NULL;
oob_output_action_t OOB_Vibrate_stop            = NULL;
oob_output_action_t OOB_display_Num             = NULL;
oob_output_action_t OOB_display_Num_stop        = NULL;
oob_output_action_t OOB_display_Alphanum        = NULL;
oob_output_action_t OOB_display_Alphanum_stop   = NULL;

oob_output_action_t action_stop_fun             = NULL;

static os_timer_event_t oob_attention_timer;
static void attention_timeout_handler(os_data_t dat)
{
    if (action_stop_fun!= NULL)
        (*action_stop_fun)((void*)dat);
}
//device do authentication action
extern unsigned char provisioning_mac[6];
void do_authentication_action(uint8_t attention_duration, provision_start_format_t* start_dat, uint8_t* authentication_value)
{
    int i;
 os_timer_event_set(&oob_attention_timer, attention_duration*1000, attention_timeout_handler, NULL);//TODO: recalculate the duration
    //unprovisioned device's confirmation
    switch (start_dat->AuthenticationMethod) {
    case NoOOBAuth:
        memset(authentication_value, 0, 16);
        print_note("provisioning OOB no auth\n");
        break;
    case StaticOOBAuth:
        memset(authentication_value, 0, 16);
        //driver_device_pin(provisioning_mac,attention_duration,16,authentication_value);
        //memcpy(authentication_value, "3.14159265358979", 16);
        //jmesh_save_read(JMESH_SAVE_FLASH_SIN,sizeof(jmesh_key_t),authentication_value);
        print_buffer_note(16,authentication_value,"provisioning OOB static auth value:\n");
        break;
    case OutputOOBAuth:
        //TODO: make a random anthentication value
        print_buffer_note(16,authentication_value,"provisioning OOB output auth value:\n");
        switch (start_dat->AuthenticationAction) {
            case Blink :
                if (OOB_Blink != NULL)
                    OOB_Blink("*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*. blinking\n");
                else {
                    print_info("NOT SUPPORT!");
                }
                memset(authentication_value, Blink, 16);
                action_stop_fun = OOB_Blink_stop;
                break;
            case Beep:
                if (OOB_Beep != NULL)
                    OOB_Beep("=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_ beep \n");
                else {
                    print_info("NOT SUPPORT!");
                }
                memset(authentication_value, Beep, 16);
                action_stop_fun = OOB_Beep_stop;
                break;
            case Vibrate:
                if (OOB_Vibrate != NULL)
                    OOB_Vibrate("~~.~~.~~.~~.~~.~~.~~.~~.~~.~~.~~.~~. vibrate\n");
                else {
                    print_info("NOT SUPPORT!");
                }
                memset(authentication_value, Vibrate, 16);
                action_stop_fun = OOB_Vibrate_stop;
                break;
            case OutputNum:
                print_info("pairing code:");
                memset(authentication_value, 0, 16);
                for (i = 0; i < 6; i++) {
                    authentication_value[i] = jmesh_random_get(0,10);
                }
                if (OOB_display_Num != NULL) {
                    OOB_display_Num(authentication_value);
                }
                else {
                    print_info("NOT SUPPORT!");
                }
                action_stop_fun = OOB_display_Num_stop;
                break;
            case OutputAlph:
                print_info("pairing passphase:");
                memset(authentication_value, 0, 16);
                for ( i = 0; i < 6; i++) {
                    authentication_value[i] = jmesh_random_get('A','Z');
                }
                if (OOB_display_Alphanum != NULL)
                    OOB_display_Alphanum(authentication_value);
                else {
                    print_info("NOT SUPPORT!");
                }
                print_info("\n");
                action_stop_fun = OOB_display_Alphanum_stop;
            break;
            default:
                //print_error("unsupport action--link->start.AuthenticationAction:%d\n",start_dat->AuthenticationAction);
                break;
            }
        break;
    case InputOOBAuth:
        //TODO:start a input process
        print_note("provisioning input OOB,please input the ahth value!\n");
        //print_info("InputOOB function is not support\n");
        break;
    default:
        //print_error("unsupport authentication action\n");
        break;
    }
}

//provisioner verity authentication
void verify_authentication_action(provision_start_format_t* start_dat, uint8_t* authentication_value)
{
    int i;
    //provisioner's confirmation
    switch (start_dat->AuthenticationMethod) {
    case NoOOBAuth:
        memset(authentication_value, 0, 16);print_info("no oob 0\n");
        break;
    case StaticOOBAuth:
        //memset(authentication_value, 0, 16);
        //memcpy(authentication_value, "3.14159265358979", 16);print_info("static oob 3.14\n");
        ;
        break;
    case OutputOOBAuth:
        switch (start_dat->AuthenticationAction) {
            case Blink:
                print_info("is device blinking?(y/n)[y]");
                setbuf(stdin, NULL);
                scanf("%c", &authentication_value[7]);
                if (authentication_value[7] == 'y')
                    memset(authentication_value, Blink, 16);
                else
                    memset(authentication_value, 0xff, 16);
                break;
            case Beep:
                print_info("is device Beep?(y/n)");
                setbuf(stdin, NULL);
                scanf("%c", &authentication_value[7]);
                print_info("you input:%c\n", authentication_value[7]);
                if (authentication_value[7] == 'y')
                    memset(authentication_value, Beep, 16);
                else
                    memset(authentication_value, 0xff, 16);
                break;
            case Vibrate:
                print_info("is device Vibrate?(y/n)");
                setbuf(stdin, NULL);
                scanf("%c", &authentication_value[7]);
                print_info("you input:%c\n", authentication_value[7]);
                if (authentication_value[7] == 'y')
                    memset(authentication_value, Vibrate, 16);
                else
                    memset(authentication_value, 0xff, 16);
                break;
            case OutputNum:
                memset(authentication_value, 0, 16);
                print_info("input Number:");
                setbuf(stdin, NULL);
                scanf("%s", authentication_value);
                print_info("input string length:%d\n",strlen((const char*)authentication_value));
                for ( i = 0; i < strlen((const char*)authentication_value); i++) {
                    authentication_value[i]-=0x30;
                }
                print_buffer_info(16,authentication_value,"complete code:");
                break;
            case OutputAlph:
                memset(authentication_value, 0, 16);
                print_info("input alphabet:");
                setbuf(stdin, NULL);
                scanf("%s", authentication_value);
            break;
            default:
                //print_error("not support authentication action--link->start.AuthenticationMethod:%d\n",start_dat->AuthenticationMethod);
            break;
        }
        break;
    case InputOOBAuth:
        print_info("InputOOB function not finished\n");
        break;
    default:
        //print_error("unsupport authentication action--link->start.AuthenticationMethod:%d\n",start_dat->AuthenticationMethod);
        break;
    }
}

//calculate confirmation
void calculate_confirmation(provision_invite_format_t*       invite_dat,
                            provision_capabilities_format_t* capabilities_dat,
                            provision_start_format_t*        start_dat,
                            provision_public_key_format_t*   provisioner_publickey,
                            provision_public_key_format_t*   unporv_device_publickey,
                            uint8_t secret_key[32],
                            uint8_t authentication_value[16],
                            provision_random_format_t* random_output,
                            provision_confirmation_format_t* confirmation_output,
                            uint8_t*                         confirmation_salt,
                            uint8_t*                         confirmation_key)
{
    //1. calculate confirmation key
    /*
     * 1.0. confirmationInputs = ProvisioningInvitePDUValue || ProvisioningCapabilitiesPDUValue ||
     *      ProvisioningStartPDUValue || PublicKeyProvisioner || PublicKeyDevice
     *
     * 1.1. ConfirmationSalt = s1(confirmationInputs)
     *
     * 1.2 ConfirmationKey = k1(ECDHSecret, ConfirmationSalt, "prck")
     *
     * 1.3 ConfirmationDevice = AES-CMAC<ConfirmationKey> (RandomDevice || AuthValue)
     *
     * 1.4 ConfirmationProvisioner = AES-CMAC<ConfirmationKey> (RandomProvisioner || AuthValue)
     *
     *
     */
    //1.0 confirmationInputs
    uint8_t i,confirmationInputs[confirmationInputsLength];
    uint8_t* p = confirmationInputs;
    memcpy(p, (uint8_t*)invite_dat, LEN_PROVISION_PARAMETERS[Prov_Invite]);
    p += LEN_PROVISION_PARAMETERS[Prov_Invite];
    memcpy(p, (uint8_t*)capabilities_dat, LEN_PROVISION_PARAMETERS[Prov_Capabilities]);
    p += LEN_PROVISION_PARAMETERS[Prov_Capabilities];
    memcpy(p, (uint8_t*)start_dat, LEN_PROVISION_PARAMETERS[Prov_Start]);
    p += LEN_PROVISION_PARAMETERS[Prov_Start];
    //first, provisioner's public-key , then device's public-key
    memcpy(p, provisioner_publickey, LEN_PROVISION_PARAMETERS[Prov_Public_Key]);
    p += LEN_PROVISION_PARAMETERS[Prov_Public_Key];
    memcpy(p, unporv_device_publickey, LEN_PROVISION_PARAMETERS[Prov_Public_Key]);

    //1.1 ConfirmationSalt
    security_s1_salt_generation(confirmationInputs, confirmationInputsLength, confirmation_salt);

    //1.2 ConfirmationKey
    k1_result_t k1_val;
    security_k1_derivation(secret_key, 32, "prck", 4, confirmation_salt, &k1_val);
    memcpy(confirmation_key, k1_val.k1, 16);
    //1.3 Confirmation(Device)
    uint8_t msg[32];
    for ( i = 0; i < 16; i++) {
        random_output->Random[i] = jmesh_random_get(0,255);
    }
    memcpy(msg, random_output, 16);
    memcpy(msg+16, authentication_value, 16);
    security_AES_CMAC(confirmation_key, 32, msg, (uint8_t*)confirmation_output);
}

//check confirmation received after have receive random
int check_confirmation(provision_random_format_t* peer_random,
                        uint8_t* authentication_value,
                        uint8_t* confirmation_key,
                        provision_confirmation_format_t* peer_confirmation)
{
    uint8_t msg[32];
    uint8_t peer_confirmation_recalc[32];
    memcpy(msg, peer_random, 16);
    memcpy(msg+16, authentication_value, 16);
	
		print_buffer_info(16,peer_random,"peer_random:");
		print_buffer_info(16,authentication_value,"authentication_value:");
		print_buffer_info(16,peer_confirmation,"peer_confirmation:");
	
    security_AES_CMAC(confirmation_key, 32, msg,  peer_confirmation_recalc);
		print_buffer_info(16,peer_confirmation_recalc,"peer_confirmation_recalc:");
	
    if (memcmp(peer_confirmation_recalc, (uint8_t*)peer_confirmation, 16) == 0) {
        return 1;
    }
    else {
        print_note("provisioning confirmation check fail\n");
        print_buffer_note(16,peer_random,"peer random:");
        print_buffer_note(16,authentication_value,"auth value:");
        print_buffer_note(16,confirmation_key,"confirm key:");

        print_buffer_note(16,peer_confirmation_recalc,"my confirmation:");
        print_buffer_note(16,peer_confirmation,"peer confirmation:");

        return 0;
    }
}
void calculate_provision_key(uint8_t* confirmation_salt,
                                provision_random_format_t* random_prov,
                                provision_random_format_t* random_dev,
                                uint8_t* secret_key,
                                uint8_t* session_key,
                                uint8_t* session_nonce,
                                uint8_t* device_key)
{
    /* encrypt
    *  1. ProvisioningSalt = s1(ConfirmationSalt || RandomProvisioner || RandomDevice)

        2. SessionKey = k1(ECDHSecret, ProvisioningSalt, ��prsk��)

        3. The nonce shall be the 13 least significant octets of:
            SessionNonce = k1(ECDHSecret, ProvisioningSalt, ��prsn��)

        4. The provisioning data shall be encrypted and authenticated using:
            Provisioning Data = Network Key || Key Index || Flags || IV Index || Unicast Address

        5.  Encrypted Provisioning Data, Provisioning Data MIC = AES-CCM (SessionKey, SessionNonce,
        Provisioning Data)

        The size of the Provisioning Data MIC is 8 octets.
    *
    *  6.  DevKey = k1(ECDHSecret, ProvisioningSalt, ��prdk��)
    */

    k1_result_t k1_val;
    ///1. ProvisioningSalt
    uint8_t msg[16+16+16] = {0};
    uint8_t provisioning_salt[16];
    memcpy(msg, confirmation_salt, 16);
    memcpy(msg+16, random_prov, 16);
    memcpy(msg+32, random_dev, 16);
    print_buffer_note(16,confirmation_salt,"confirmation_salt:");
    print_buffer_note(16,random_prov,"random_prov:");
    print_buffer_note(16,random_dev,"random_dev:");
    security_s1_salt_generation(msg, 48, provisioning_salt);

    print_buffer_note(16,provisioning_salt,"provisioning salt:");
    ///2. sessionKey
    security_k1_derivation(secret_key, 32, "prsk", 4, provisioning_salt, &k1_val);

    memcpy(session_key, k1_val.k1, 16);
    print_buffer_note(16,session_key,"provisioning session key:");
    ///3. session_nonce
    security_k1_derivation(secret_key, 32, "prsn", 4, provisioning_salt, &k1_val);
    memcpy(session_nonce, k1_val.k1, 16);

    print_buffer_note(16,session_nonce,"provisioning session nonce:");
    ///6. device key
    security_k1_derivation(secret_key, 32, "prdk", 4, provisioning_salt, &k1_val);
    memcpy(device_key, k1_val.k1, 16);
    print_buffer_note(16,device_key,"provisioning device key:");
}

void encrypt_provision_data(uint8_t* session_key, uint8_t* session_nonce, provision_data_format_t* ciphertext)
{
    ///5. encrypt
    security_aes_ccm_encrypt2(session_key, session_nonce, (uint8_t*)ciphertext, LEN_PROVISION_PARAMETERS[Prov_Data]-MODE_MIC64, 0, MODE_MIC64);
}

int decrypt_provision_data(uint8_t* session_key, uint8_t* session_nonce, provision_data_format_t* plaintext)
{
    int ret = security_aes_ccm_decrypt2(session_key, session_nonce, (uint8_t*)plaintext, LEN_PROVISION_PARAMETERS[Prov_Data], 0, MODE_MIC64);
    return ret;
}


