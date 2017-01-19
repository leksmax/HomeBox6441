/*
 * Copyright (c) 2011 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#ifndef __HCI_H__
#define __HCI_H__

#include "pal_osapi.h"

#ifndef PAL_USER_SPACE_CODE
#define POSTPACK
#endif


#define HCI_CMD_OGF_MASK            0x3F
#define HCI_CMD_OGF_SHIFT           10
#define HCI_CMD_GET_OGF(opcode)     ((opcode >> HCI_CMD_OGF_SHIFT) & HCI_CMD_OGF_MASK)

#define HCI_CMD_OCF_MASK            0x3FF
#define HCI_CMD_OCF_SHIFT           0 
#define HCI_CMD_GET_OCF(opcode)     (((opcode) >> HCI_CMD_OCF_SHIFT) & HCI_CMD_OCF_MASK)

#define HCI_FORM_OPCODE(ocf, ogf)   (((ocf & HCI_CMD_OCF_MASK) << HCI_CMD_OCF_SHIFT) | ((ogf & HCI_CMD_OGF_MASK) << HCI_CMD_OGF_SHIFT))

/*---------------------- HCI Opcode groups-------------------------------------*/
#define OGF_NOP                                     0x00
#define OGF_LINK_CONTROL                            0x01
#define OGF_CONTROL_BASEBAND                        0x03
#define OGF_INFO_PARAMS                             0x04
#define OGF_STATUS                                  0x05
#define OGF_TESTING                                 0x06
#define OGF_BLUETOOTH                               0x3E
#define OGF_VENDOR_DEBUG                            0x3F

#define OCF_NOP                                     0x00
/*-----------------------Link Control Commands Opcode--------------------------*/
#define OCF_HCI_Create_Physical_Link                0x35
#define OCF_HCI_Accept_Physical_Link_Req            0x36
#define OCF_HCI_Disconnect_Physical_Link            0x37
#define OCF_HCI_Create_Logical_Link                 0x38
#define OCF_HCI_Accept_Logical_Link                 0x39
#define OCF_HCI_Disconnect_Logical_Link             0x3A
#define OCF_HCI_Logical_Link_Cancel                 0x3B
#define OCF_HCI_Flow_Spec_Modify                    0x3C
/*-------------------------Contorller & Baseband Commands Opcode---------------*/
#define OCF_HCI_Set_Event_Mask                      0x01
#define OCF_HCI_Reset                               0x03
#define OCF_HCI_Read_Conn_Accept_Timeout            0x15
#define OCF_HCI_Write_Conn_Accept_Timeout           0x16
#define OCF_HCI_Read_Link_Supervision_Timeout       0x36
#define OCF_HCI_Write_Link_Supervision_Timeout      0x37
#define OCF_HCI_Enhanced_Flush                      0x5F
#define OCF_HCI_Read_Logical_Link_Accept_Timeout    0x61
#define OCF_HCI_Write_Logical_Link_Accept_Timeout   0x62
#define OCF_HCI_Set_Event_Mask_Page_2               0x63
#define OCF_HCI_Read_Location_Data                  0x64
#define OCF_HCI_Write_Location_Data                 0x65
#define OCF_HCI_Read_Flow_Control_Mode              0x66
#define OCF_HCI_Write_Flow_Control_Mode             0x67
#define OCF_HCI_Read_BE_Flush_Timeout               0x69
#define OCF_HCI_Write_BE_Flush_Timeout              0x6A
#define OCF_HCI_Short_Range_Mode                    0x6B
/*--------------------------Info Commands Opcode-------------------------------*/
#define OCF_HCI_Read_Local_Ver_Info                 0x01
#define OCF_HCI_Read_Local_Supported_Cmds           0x02
#define OCF_HCI_Read_Data_Block_Size                0x0A
/*--------------------------Status Commands Opcode-----------------------------*/
#define OCF_HCI_Read_Failed_Contact_Counter         0x01
#define OCF_HCI_Reset_Failed_Contact_Counter        0x02
#define OCF_HCI_Read_Link_Quality                   0x03
#define OCF_HCI_Read_RSSI                           0x05
#define OCF_HCI_Read_Local_AMP_Info                 0x09    
#define OCF_HCI_Read_Local_AMP_ASSOC                0x0A
#define OCF_HCI_Write_Remote_AMP_ASSOC              0x0B


/*-------------------------AMP_ASSOC Specific TLV tags--------------------------*/
#define AMP_ASSOC_MAC_ADDRESS_INFO_TYPE             0x1
#define AMP_ASSOC_PREF_CHAN_LIST                    0x2
#define AMP_ASSOC_CONNECTED_CHAN                    0x3
#define AMP_ASSOC_PAL_CAPABILITIES                  0x4
#define AMP_ASSOC_PAL_VERSION                       0x5

/*--------------------------PAL Events-----------------------------------------*/
#define PAL_COMMAND_COMPLETE_EVENT                  0x0E
#define PAL_COMMAND_STATUS_EVENT                    0x0F
#define PAL_HARDWARE_ERROR_EVENT                    0x10
#define PAL_FLUSH_OCCURRED_EVENT                    0x11
#define PAL_NUM_COMPL_PACKET_EVENT                  0x13
#define PAL_LOOPBACK_EVENT                          0x19
#define PAL_BUFFER_OVERFLOW_EVENT                   0x1A
#define PAL_QOS_VIOLATION_EVENT                     0x1E
#define PAL_ENHANCED_FLUSH_COMPLT_EVENT             0x39
#define PAL_PHYSICAL_LINK_COMPL_EVENT               0x40
#define PAL_CHANNEL_SELECT_EVENT                    0x41
#define PAL_DISCONNECT_PHYSICAL_LINK_EVENT          0x42
#define PAL_PHY_LINK_EARLY_LOSS_WARNING_EVENT       0x43
#define PAL_PHY_LINK_RECOVERY_EVENT                 0x44
#define PAL_LOGICAL_LINK_COMPL_EVENT                0x45
#define PAL_DISCONNECT_LOGICAL_LINK_COMPL_EVENT     0x46
#define PAL_FLOW_SPEC_MODIFY_COMPL_EVENT            0x47
#define PAL_NUM_COMPL_DATA_BLOCK_EVENT              0x48
#define PAL_SHORT_RANGE_MODE_CHANGE_COMPL_EVENT     0x4C
#define PAL_AMP_STATUS_CHANGE_EVENT                 0x4D
#define PAL_DEBUG_EVENT                             0xFF
/*-----------------------End of PAL events definiton---------------------------*/



#define NUM_HCI_COMMAND_PKTS                        0x1  /* hci cmd process can handle one command every time */

/*-----------------------NOP Cmd-----------------------------------------------*/
#define HCI_CMD_NOP                             HCI_FORM_OPCODE(OCF_NOP, OGF_NOP)
/*-----------------------Link Control Commands---------------------------------*/
#define HCI_Create_Physical_Link                HCI_FORM_OPCODE(OCF_HCI_Create_Physical_Link, OGF_LINK_CONTROL)
#define HCI_Accept_Physical_Link_Req            HCI_FORM_OPCODE(OCF_HCI_Accept_Physical_Link_Req, OGF_LINK_CONTROL)
#define HCI_Disconnect_Physical_Link            HCI_FORM_OPCODE(OCF_HCI_Disconnect_Physical_Link, OGF_LINK_CONTROL)
#define HCI_Create_Logical_Link                 HCI_FORM_OPCODE(OCF_HCI_Create_Logical_Link, OGF_LINK_CONTROL)
#define HCI_Accept_Logical_Link                 HCI_FORM_OPCODE(OCF_HCI_Accept_Logical_Link, OGF_LINK_CONTROL)
#define HCI_Disconnect_Logical_Link             HCI_FORM_OPCODE(OCF_HCI_Disconnect_Logical_Link, OGF_LINK_CONTROL)
#define HCI_Logical_Link_Cancel                 HCI_FORM_OPCODE(OCF_HCI_Logical_Link_Cancel, OGF_LINK_CONTROL)
#define HCI_Flow_Spec_Modify                    HCI_FORM_OPCODE(OCF_HCI_Flow_Spec_Modify, OGF_LINK_CONTROL)
/*-----------------------Controller & Baseband Commands------------------------*/
#define HCI_Set_Event_Mask                      HCI_FORM_OPCODE(OCF_HCI_Set_Event_Mask, OGF_CONTROL_BASEBAND)
#define HCI_Reset_Pal                           HCI_FORM_OPCODE(OCF_HCI_Reset, OGF_CONTROL_BASEBAND)
#define HCI_Read_Conn_Accept_Timeout            HCI_FORM_OPCODE(OCF_HCI_Read_Conn_Accept_Timeout, OGF_CONTROL_BASEBAND)
#define HCI_Write_Conn_Accept_Timeout           HCI_FORM_OPCODE(OCF_HCI_Write_Conn_Accept_Timeout, OGF_CONTROL_BASEBAND)
#define HCI_Enhanced_Flush                      HCI_FORM_OPCODE(OCF_HCI_Enhanced_Flush, OGF_CONTROL_BASEBAND)
#define HCI_Read_Logical_Link_Accept_Timeout    HCI_FORM_OPCODE(OCF_HCI_Read_Logical_Link_Accept_Timeout, OGF_CONTROL_BASEBAND)
#define HCI_Write_Logical_Link_Accept_Timeout   HCI_FORM_OPCODE(OCF_HCI_Write_Logical_Link_Accept_Timeout, OGF_CONTROL_BASEBAND)
#define HCI_Read_Link_Supervision_Timeout       HCI_FORM_OPCODE(OCF_HCI_Read_Link_Supervision_Timeout, OGF_CONTROL_BASEBAND)
#define HCI_Write_Link_Supervision_Timeout      HCI_FORM_OPCODE(OCF_HCI_Write_Link_Supervision_Timeout, OGF_CONTROL_BASEBAND)
#define HCI_Read_Location_Data                  HCI_FORM_OPCODE(OCF_HCI_Read_Location_Data, OGF_CONTROL_BASEBAND)
#define HCI_Write_Location_Data                 HCI_FORM_OPCODE(OCF_HCI_Write_Location_Data, OGF_CONTROL_BASEBAND)
#define HCI_Set_Event_Mask_Page_2               HCI_FORM_OPCODE(OCF_HCI_Set_Event_Mask_Page_2, OGF_CONTROL_BASEBAND)
#define HCI_Read_Flow_Control_Mode              HCI_FORM_OPCODE(OCF_HCI_Read_Flow_Control_Mode, OGF_CONTROL_BASEBAND)
#define HCI_Write_Flow_Control_Mode             HCI_FORM_OPCODE(OCF_HCI_Write_Flow_Control_Mode, OGF_CONTROL_BASEBAND)
#define HCI_Write_BE_Flush_Timeout              HCI_FORM_OPCODE(OCF_HCI_Write_BE_Flush_Timeout, OGF_CONTROL_BASEBAND)
#define HCI_Read_BE_Flush_Timeout               HCI_FORM_OPCODE(OCF_HCI_Read_BE_Flush_Timeout, OGF_CONTROL_BASEBAND)
#define HCI_Short_Range_Mode                    HCI_FORM_OPCODE(OCF_HCI_Short_Range_Mode, OGF_CONTROL_BASEBAND)            
/*------------------------Info Commands----------------------------------------*/
#define HCI_Read_Local_Ver_Info                 HCI_FORM_OPCODE(OCF_HCI_Read_Local_Ver_Info,  OGF_INFO_PARAMS)
#define HCI_Read_Local_Supported_Cmds           HCI_FORM_OPCODE(OCF_HCI_Read_Local_Supported_Cmds, OGF_INFO_PARAMS)
#define HCI_Read_Data_Block_Size                HCI_FORM_OPCODE(OCF_HCI_Read_Data_Block_Size, OGF_INFO_PARAMS)
/*------------------------Status Commands--------------------------------------*/
#define HCI_Read_Failed_Contact_Counter         HCI_FORM_OPCODE(OCF_HCI_Read_Failed_Contact_Counter, OGF_STATUS)
#define HCI_Reset_Failed_Contact_Counter        HCI_FORM_OPCODE(OCF_HCI_Reset_Failed_Contact_Counter, OGF_STATUS)
#define HCI_Read_Link_Quality                   HCI_FORM_OPCODE(OCF_HCI_Read_Link_Quality, OGF_STATUS)
#define HCI_Read_RSSI                           HCI_FORM_OPCODE(OCF_HCI_Read_RSSI, OGF_STATUS)
#define HCI_Read_Local_AMP_Info                 HCI_FORM_OPCODE(OCF_HCI_Read_Local_AMP_Info, OGF_STATUS)
#define HCI_Read_Local_AMP_ASSOC                HCI_FORM_OPCODE(OCF_HCI_Read_Local_AMP_ASSOC, OGF_STATUS)
#define HCI_Write_Remote_AMP_ASSOC              HCI_FORM_OPCODE(OCF_HCI_Write_Remote_AMP_ASSOC, OGF_STATUS)

/*-----------------------End of cmd definitions--------------------------------*/




/*--------------------- PAL Constants (Sec 6 of Doc)---------------------------*/
#define Max80211_PAL_PDU_Size               1492
#define Max80211_AMP_ASSOC_Len              250
#define MinGUserPrio                        4
#define MaxGUserPrio                        7
#define BEUserPrio0                         0
#define BEUserPrio1                         3
#define Max80211BeaconPeriod                2000    /* in millisec */
#define ShortRangeModePowerMax              4       /* dBm */

/*---------------------PAL Protocol Identifiers (Sec5.1) ------------------*/
typedef enum {
    ACL_DATA = 0x01,
    ACTIVITY_REPORT,
    SECURED_FRAMES,
    LINK_SUPERVISION_REQ,
    LINK_SUPERVISION_RESP,
} PAL_PROTOCOL_IDENTIFIERS;

typedef enum {
    LSTO_REQ = 0x01,
    LSTO_RESP,
    GET_ACT_RPT,
} DEBUG_EVENT_TYPE;

/* ampDbgWdmEnable setting*/
#define AMP_WDM_DBG_ENABLE                  (1<<0)//bit 0
#define PAL_LSTO_TEST                       (1<<1)//bit 1
#define PAL_ACT_RPT_TEST                    (1<<2)//bit 2
#define PAL_DISABLE_QOS_TEST                (1<<3)//bit 3

#define HCI_CMD_HDR_SZ                      3
#define HCI_EVENT_HDR_SIZE                  2
#define HCI_ACL_HDR_SZ                      4
#define MAX_EVT_PKT_SZ                      255
#define AMP_ASSOC_MAX_FRAG_SZ               248

#define DEFAULT_CONN_ACCPT_TO              15960  //5.6 seconds
#define DEFAULT_LL_ACCPT_TO                 8960  //5.6 seconds
#define DEFAULT_DISCONN_TO                  2000  //We noy give MP 2 second to disconnect
#define DEFAULT_STOP_BEACON_TO              5000  //Give MP 2 second to stop beacon

#define PACKET_BASED_FLOW_CONTROL_MODE      0x00
#define DATA_BLK_BASED_FLOW_CONTROL_MODE    0x01

#define SERVICE_TYPE_BEST_EFFORT            0x01
#define SERVICE_TYPE_GUARANTEED             0x02

#define MAC_ADDR_LEN                        6
#define LINK_KEY_LEN                        32
#define CCMP_KEY_LEN                        16

#define ACL_DATA_HEADER                     4

#define PAL_INVALID_PHYSICAL_LINK_ID        0

#define AMP_PACKET_BOUNDRY_FLAG             0x3000

#if (defined(_WIN32) || defined(_WIN64))
#include <pshpack1.h>
#endif

typedef struct reg_triplet_t {
    A_UINT8 first_chan;
    A_UINT8 num_of_chan;
    A_UINT8 tx_pwr;
}POSTPACK REG_TRIPLET;

typedef struct reg_extn_triplet_t{
    A_UINT8   identifier;
    A_UINT8   reg_class;
    A_UINT8   reg_coverage_class;
}POSTPACK REG_EXTN_TRIPLET;

/* Command pkt */
typedef struct  hci_cmd_pkt_t {
    A_UINT16    opcode;
    A_UINT8     param_length;
    A_UINT8     params[255];
} POSTPACK HCI_CMD_PKT;

/* Data pkt */
typedef struct  hci_acl_data_pkt_t {
    A_UINT16    hdl_and_flags;
    A_UINT16    data_len;
    A_UINT8     data[Max80211_PAL_PDU_Size];
} POSTPACK HCI_ACL_DATA_PKT;

/* Event pkt */
typedef struct  hci_event_pkt_t {
    A_UINT8     event_code;
    A_UINT8     param_len;
    A_UINT8     params[254];
} POSTPACK HCI_EVENT_PKT;

/*--------------------------HCI Command definitions---------------------------*/
typedef struct hci_cmd_head_t{
    A_UINT16    opcode;
    A_UINT8     param_length;
} POSTPACK HCI_CMD_HEAD;

typedef struct hci_cmd_phy_link_t {
    A_UINT16    opcode;
    A_UINT8     param_length;
    A_UINT8     phy_link_hdl;
    A_UINT8     link_key_len;
    A_UINT8     link_key_type;
    A_UINT8     link_key[LINK_KEY_LEN];
} POSTPACK HCI_CMD_PHY_LINK;

typedef struct  hci_cmd_write_rem_amp_assoc_t {
    A_UINT16    opcode;
    A_UINT8     param_length;
    A_UINT8     phy_link_hdl;
    A_UINT16    len_so_far;
    A_UINT16    amp_assoc_remaining_len;
    A_UINT8     amp_assoc_frag[AMP_ASSOC_MAX_FRAG_SZ];
} POSTPACK HCI_CMD_WRITE_REM_AMP_ASSOC;


typedef struct  hci_cmd_opcode_hdl_t {
    A_UINT16    opcode;
    A_UINT8     param_length;
    A_UINT16    hdl;
} POSTPACK HCI_CMD_READ_LINK_QUAL,
           HCI_CMD_READ_LINK_SUPERVISION_TIMEOUT;

typedef struct  hci_cmd_enhanced_flush_t{
    A_UINT16    opcode;
    A_UINT8     param_length;
    A_UINT16    hdl;
    A_UINT8     type;
} POSTPACK HCI_CMD_ENHANCED_FLUSH;

typedef struct  hci_cmd_write_be_flush_t{
    A_UINT16    opcode;
    A_UINT8     param_length;
    A_UINT16    hdl;
    A_UINT32    tout;
} POSTPACK HCI_CMD_WRITE_BE_FLUSH;

typedef struct  hci_cmd_read_be_flush_t{
    A_UINT16    opcode;
    A_UINT8     param_length;
    A_UINT16    hdl;
} POSTPACK HCI_CMD_READ_BE_FLUSH;

typedef struct  hci_cmd_read_failed_cnt_t{
    A_UINT16    opcode;
    A_UINT8     param_length;
    A_UINT16    hdl;
} POSTPACK HCI_CMD_READ_FAILED_CNT;

typedef struct  hci_cmd_read_local_amp_assoc_t {
    A_UINT16    opcode;
    A_UINT8     param_length;
    A_UINT8     phy_link_hdl;
    A_UINT16    len_so_far;
    A_UINT16    max_rem_amp_assoc_len;
} POSTPACK HCI_CMD_READ_LOCAL_AMP_ASSOC;


typedef struct hci_cmd_set_event_mask_t {
    A_UINT16    opcode;
    A_UINT8     param_length;
    A_UINT64    mask;
} POSTPACK HCI_CMD_SET_EVT_MASK, HCI_CMD_SET_EVT_MASK_PG_2;


typedef struct  hci_cmd_write_timeout_t {
    A_UINT16    opcode;
    A_UINT8     param_length;
    A_UINT16    timeout;
} POSTPACK  HCI_CMD_WRITE_TIMEOUT;

typedef struct  hci_cmd_write_link_supervision_timeout_t {
    A_UINT16    opcode;
    A_UINT8     param_length;
    A_UINT16    hdl;
    A_UINT16    timeout;
} POSTPACK HCI_CMD_WRITE_LINK_SUPERVISION_TIMEOUT;

typedef struct  hci_cmd_write_flow_control_t {
    A_UINT16    opcode;
    A_UINT8     param_length;
    A_UINT8     mode;
} POSTPACK  HCI_CMD_WRITE_FLOW_CONTROL;

typedef struct  location_data_cfg_t {
    A_UINT8     reg_domain_aware;
    A_UINT8     reg_domain[3];
    A_UINT8     reg_options;
} POSTPACK LOCATION_DATA_CFG;

typedef struct  hci_cmd_write_location_data_t {
    A_UINT16    opcode;
    A_UINT8     param_length;
    LOCATION_DATA_CFG   cfg;
} POSTPACK  HCI_CMD_WRITE_LOCATION_DATA;


typedef struct  flow_spec_t {
    A_UINT8     id;
    A_UINT8     service_type;
    A_UINT16    max_sdu;
    A_UINT32    sdu_inter_arrival_time;
    A_UINT32    access_latency;
    A_UINT32    flush_timeout;
} POSTPACK FLOW_SPEC;


typedef struct  hci_cmd_create_logical_link_t {
    A_UINT16    opcode;
    A_UINT8     param_length;
    A_UINT8     phy_link_hdl;
    FLOW_SPEC   tx_flow_spec;
    FLOW_SPEC   rx_flow_spec;
} POSTPACK HCI_CMD_CREATE_LOGICAL_LINK;

typedef struct  hci_cmd_flow_spec_modify_t {
    A_UINT16    opcode;
    A_UINT8     param_length;
    A_UINT16    hdl;
    FLOW_SPEC   tx_flow_spec;
    FLOW_SPEC   rx_flow_spec;
} POSTPACK HCI_CMD_FLOW_SPEC_MODIFY;

typedef struct hci_cmd_logical_link_cancel_t {
    A_UINT16    opcode;
    A_UINT8     param_length;
    A_UINT8     phy_link_hdl;
    A_UINT8     tx_flow_spec_id;
} POSTPACK HCI_CMD_LOGICAL_LINK_CANCEL;

typedef struct  hci_cmd_disconnect_logical_link_t {
    A_UINT16    opcode;
    A_UINT8     param_length;
    A_UINT16    logical_link_hdl;
    A_UINT8     reason;
} POSTPACK HCI_CMD_DISCONNECT_LOGICAL_LINK;

typedef struct  hci_cmd_disconnect_phy_link_t {
    A_UINT16    opcode;
    A_UINT8     param_length;
    A_UINT8     phy_link_hdl;
} POSTPACK HCI_CMD_DISCONNECT_PHY_LINK;

typedef struct  hci_cmd_srm_t {
    A_UINT16    opcode;
    A_UINT8     param_length;
    A_UINT8     phy_link_hdl;
    A_UINT8     mode;
} POSTPACK HCI_CMD_SHORT_RANGE_MODE;
/*------------------------HCI Command definitions end-------------------------*/



/*------------------------HCI Event definitions-------------------------------*/
/* Debug event */
typedef struct  hci_debug_event_t {
    A_UINT8     event_code; /*will be 0xFF*/
    A_UINT8     param_len;
    A_UINT8     event_type;
    A_UINT8     params[250];
} POSTPACK HCI_DEBUG_EVENT;

/* Command complete event */
typedef struct  hci_event_cmd_complete_t {
    A_UINT8     event_code;
    A_UINT8     param_len;
    A_UINT8     num_hci_cmd_pkts;
    A_UINT16    opcode;
    A_UINT8     params[250];
} POSTPACK HCI_EVENT_CMD_COMPLETE;


/* Command status event */
typedef struct  hci_event_cmd_status_t {
    A_UINT8     event_code;
    A_UINT8     param_len;
    A_UINT8     status;
    A_UINT8     num_hci_cmd_pkts;
    A_UINT16    opcode;
} POSTPACK HCI_EVENT_CMD_STATUS;

/* Hardware Error event */
typedef struct  hci_event_hw_err_t {
    A_UINT8     event_code;
    A_UINT8     param_len;
    A_UINT8     hw_err_code;
} POSTPACK HCI_EVENT_HW_ERR;

/* Flush occured event */
/* Qos Violation event */
typedef struct  hci_event_handle_t {
    A_UINT8     event_code;
    A_UINT8     param_len;
    A_UINT16    handle;
} POSTPACK HCI_EVENT_FLUSH_OCCRD,
           HCI_EVENT_QOS_VIOLATION;

/* Loopback command event */
typedef struct hci_loopback_cmd_t {
    A_UINT8     event_code;
    A_UINT8     param_len;
    A_UINT8     params[252];
} POSTPACK HCI_EVENT_LOOPBACK_CMD;

/* Data buffer overflow event */
typedef struct  hci_data_buf_overflow_t {
    A_UINT8     event_code;
    A_UINT8     param_len;
    A_UINT8     link_type;
} POSTPACK  HCI_EVENT_DATA_BUF_OVERFLOW;

/* Enhanced Flush complete event */
typedef struct hci_enhanced_flush_complt_t{
    A_UINT8     event_code;
    A_UINT8     param_len;
    A_UINT16    hdl;
} POSTPACK  HCI_EVENT_ENHANCED_FLUSH_COMPLT;

/* Channel select event */
typedef struct  hci_event_chan_select_t {
    A_UINT8     event_code;
    A_UINT8     param_len;
    A_UINT8     phy_link_hdl;
} POSTPACK HCI_EVENT_CHAN_SELECT;

/* Physical Link Complete event */
typedef struct  hci_event_phy_link_complete_event_t {
    A_UINT8     event_code;
    A_UINT8     param_len;
    A_UINT8     status;
    A_UINT8     phy_link_hdl;
} POSTPACK HCI_EVENT_PHY_LINK_COMPLETE;

/* Logical Link complete event */
typedef struct hci_event_logical_link_complete_event_t {
    A_UINT8     event_code;
    A_UINT8     param_len;
    A_UINT8     status;
    A_UINT16    logical_link_hdl;
    A_UINT8     phy_hdl;
    A_UINT8     TxFlowId;
} POSTPACK HCI_EVENT_LOGICAL_LINK_COMPLETE_EVENT;

/* Disconnect Logical Link complete event */
typedef struct hci_event_disconnect_logical_link_event_t {
    A_UINT8     event_code;
    A_UINT8     param_len;
    A_UINT8     status;
    A_UINT16    logical_link_hdl;
    A_UINT8     reason;
} POSTPACK HCI_EVENT_DISCONNECT_LOGICAL_LINK_EVENT;

/* Disconnect Physical Link complete event */
typedef struct hci_event_disconnect_phy_link_complete_t {
    A_UINT8     event_code;
    A_UINT8     param_len;
    A_UINT8     status;
    A_UINT8     phy_link_hdl;
    A_UINT8     reason;
} POSTPACK HCI_EVENT_DISCONNECT_PHY_LINK_COMPLETE;

typedef struct hci_event_physical_link_loss_early_warning_t{
    A_UINT8     event_code;
    A_UINT8     param_len;
    A_UINT8     phy_hdl;
    A_UINT8     reason;
} POSTPACK HCI_EVENT_PHY_LINK_LOSS_EARLY_WARNING;

typedef struct hci_event_physical_link_recovery_t{
    A_UINT8     event_code;
    A_UINT8     param_len;
    A_UINT8     phy_hdl;
} POSTPACK HCI_EVENT_PHY_LINK_RECOVERY;


/* Flow spec modify complete event */
/* Flush event */
typedef struct hci_event_status_handle_t {
    A_UINT8     event_code;
    A_UINT8     param_len;
    A_UINT8     status;
    A_UINT16    handle;
} POSTPACK HCI_EVENT_FLOW_SPEC_MODIFY,
           HCI_EVENT_FLUSH;


/* Num of completed data blocks event */
typedef struct hci_event_num_of_compl_data_blks_t {
    A_UINT8     event_code;
    A_UINT8     param_len;
    A_UINT16    num_data_blks;
    A_UINT8     num_handles;
    A_UINT8     params[250];
} POSTPACK HCI_EVENT_NUM_COMPL_DATA_BLKS;

typedef struct hci_event_num_of_compl_packets_t {
    A_UINT8     event_code;
    A_UINT8     param_len;
    A_UINT8     num_handles;
    A_UINT8     params[250];
} POSTPACK HCI_EVENT_NUM_COMPL_PACKETS;

/* Short range mode change complete event */
typedef struct  hci_srm_cmpl_t {
    A_UINT8     event_code;
    A_UINT8     param_len;
    A_UINT8     status;
    A_UINT8     phy_link;
    A_UINT8     state;
} POSTPACK HCI_EVENT_SRM_COMPL;

typedef struct hci_event_amp_status_change_t{
    A_UINT8     event_code;
    A_UINT8     param_len;
    A_UINT8     status;
    A_UINT8     amp_status;
} POSTPACK HCI_EVENT_AMP_STATUS_CHANGE;


/*----------------Event definitions end---------------------------------------*/

/*----------------HCI command event parameters definination-------------------*/
typedef struct  local_amp_info_resp_t {
    A_UINT8     status;
    A_UINT8     amp_status;
    A_UINT32    total_bw;           /* kbps */
    A_UINT32    max_guranteed_bw;   /* kbps */
    A_UINT32    min_latency;
    A_UINT32    max_pdu_size;
    A_UINT8     amp_type;
    A_UINT16    pal_capabilities;
    A_UINT16    amp_assoc_len;
    A_UINT32    max_flush_timeout;  /* in ms */
    A_UINT32    be_flush_timeout;   /* in ms */
    A_UINT8     hci_version;        /* HCI protocol version */
    A_UINT16    hci_revision;       /* HCI protocol revision */
    A_UINT8     pal_ver;            /* PAL version*/
    A_UINT16    pal_sig_name;       /* SIG assigned company identifier */
    A_UINT16    pal_sub_ver;        /* PAL sub version*/
} POSTPACK  LOCAL_AMP_INFO;

typedef struct  amp_assoc_cmd_resp_t{
    A_UINT8     status;
    A_UINT8     phy_hdl;
    A_UINT16    amp_assoc_len;
    A_UINT8     amp_assoc_frag[AMP_ASSOC_MAX_FRAG_SZ];
} POSTPACK AMP_ASSOC_CMD_RESP;

typedef struct  be_timeout_read_t {
    A_UINT8     status;
    A_UINT32    timeout;
} POSTPACK BE_TIMEOUT_INFO;

typedef struct  failed_cnt_t {
    A_UINT8     status;
    A_UINT16    hdl;
    A_UINT16    failedCnt;
} POSTPACK FAILED_COUNT_INFO;

typedef struct  link_rssi_t {
    A_UINT8     status;
    A_UINT16    hdl;
    A_UINT8     rssi;
} POSTPACK LINK_RSSI_INFO;

typedef struct  timeout_read_t {
    A_UINT8     status;
    A_UINT16    timeout;
} POSTPACK TIMEOUT_INFO;

typedef struct  link_supervision_timeout_read_t {
    A_UINT8     status;
    A_UINT16    hdl;
    A_UINT16    timeout;
} POSTPACK LINK_SUPERVISION_TIMEOUT_INFO;

typedef struct  status_hdl_t {
    A_UINT8     status;
    A_UINT16    hdl;
} POSTPACK INFO_STATUS_HDL;

typedef struct write_remote_amp_assoc_t{
    A_UINT8     status;
    A_UINT8     hdl;
} POSTPACK WRITE_REMOTE_AMP_ASSOC_INFO;

typedef struct  read_loc_info_t {
    A_UINT8             status;
    LOCATION_DATA_CFG   loc;
} POSTPACK READ_LOC_INFO;

typedef struct  read_flow_ctrl_mode_t {
    A_UINT8     status;
    A_UINT8     mode;
} POSTPACK READ_FLWCTRL_INFO;

typedef struct  read_data_blk_size_t {
    A_UINT8     status;
    A_UINT16    max_acl_data_pkt_len;
    A_UINT16    data_block_len;
    A_UINT16    total_num_data_blks;
} POSTPACK READ_DATA_BLK_SIZE_INFO;

typedef struct link_qual_t {
    A_UINT8     status;
    A_UINT16    hdl;
    A_UINT8     link_qual;
} POSTPACK READ_LINK_QUAL_INFO;

typedef struct ll_cancel_resp_t {
    A_UINT8     status;
    A_UINT8     phy_link_hdl;
    A_UINT8     tx_flow_spec_id;
} POSTPACK LL_CANCEL_RESP;

typedef struct local_ver_t{
        A_UINT8     status;
        A_UINT8     hci_version;
        A_UINT16    hci_revision;
        A_UINT8     pal_version;
        A_UINT8     sig_company_name[2];
        A_UINT16    pal_subversion;
} POSTPACK LOCAL_VERSION_INFO;

typedef struct  schedule_triplet_t {
    A_UINT32    st_time;
    A_UINT32    duration;
    A_UINT32    periodicity;
} POSTPACK SCHEDULE;

typedef struct activity_rpt_hdr_t {
    A_UINT8     schedule_known;
    A_UINT8     num_rpts;
} POSTPACK ACTIVITY_RPT_HDR;

typedef struct  event_code_tbl_t {
    A_UINT8     event_code;
    A_UINT8     evt_name[40];
} EVENT_CODE_TBL;

#if (defined(_WIN32) || defined(_WIN64))
#include <poppack.h>
#endif

//---------------------------------------------------------------------
//PAL In_Queue Event Processing starts from here
//---------------------------------------------------------------------


enum PAL_HCI_CMD_STATUS {
    PAL_HCI_CMD_PROCESSED,
    PAL_HCI_CMD_IGNORED
}; 


/* ----------------- HCI Error Codes ---------------------*/
#define HCI_SUCCESS                             0x00
#define HCI_ERR_UNKNOW_CMD                      0x01
#define HCI_ERR_UNKNOWN_CONN_ID                 0x02
#define HCI_ERR_HW_FAILURE                      0x03
#define HCI_ERR_PAGE_TIMEOUT                    0x04
#define HCI_ERR_AUTH_FAILURE                    0x05
#define HCI_ERR_KEY_MISSING                     0x06
#define HCI_ERR_MEM_CAP_EXECED                  0x07
#define HCI_ERR_CON_TIMEOUT                     0x08
#define HCI_ERR_CON_LIMIT_EXECED                0x09
#define HCI_ERR_ACL_CONN_ALRDY_EXISTS           0x0B
#define HCI_ERR_COMMAND_DISALLOWED              0x0C
#define HCI_ERR_CONN_REJ_BY_LIMIT_RES           0x0D
#define HCI_ERR_CONN_REJ_BY_SEC                 0x0E
#define HCI_ERR_CONN_REJ_BY_BAD_ADDR            0x0F
#define HCI_ERR_CONN_ACCPT_TIMEOUT              0x10
#define HCI_ERR_UNSUPPORT_FEATURE               0x11
#define HCI_ERR_INVALID_HCI_CMD_PARAMS          0x12
#define HCI_ERR_CON_TERM_BY_HOST                0x16
#define HCI_ERR_UNSPECIFIED_ERROR               0x1F
#define HCI_ERR_ENCRYPTION_MODE_NOT_SUPPORT     0x25
#define HCI_ERR_REQUESTED_QOS_NOT_SUPPORT       0x27
#define HCI_ERR_QOS_UNACCEPTABLE_PARM           0x2C
#define HCI_ERR_QOS_REJECTED                    0x2D
#define HCI_ERR_CONN_REJ_NO_SUITABLE_CHAN       0x39

//Special error code to indicate the PAL processing thead
//we are not ready to process this command yet, re-queue it
#define HCI_ERR_PAL_SM_NOT_READY                0XFD
/*-------------------HCI Error Codes End -------------------*/

#include "pal_cfg.h"
/*-------------------HCI Reasons codes ---------------------*/
#define REASON_CONN_TIMEOUT                     0x08
#define REASON_CONN_TERM_BY_HOST                0x16

/*------------------ HCI Reasons codes End -----------------*/


/*------------------ PAL HCI APIs --------------------------*/
typedef int (* pal_evt_dispatcher)(PVOID pDev, A_UINT8 *buf, A_UINT16 sz);
typedef int (* acl_data_dispatcher)(PVOID pDev, A_UINT8 *buf, A_UINT16 sz);
void        pal_evt_set_dispatcher(pal_evt_dispatcher fn);
void        pal_data_set_dispatcher(acl_data_dispatcher fn);        /* Rx func for stack . Pkt PAL to stack */


/*------------------ Utility API ----------------------------*/
A_UINT32    test_link_activity(A_UINT8 phy_hdl);

void        PAL_dump_frame(A_UINT8  *frm, A_UINT32 len);
void        pal_decode_event(A_UINT8 *buf, A_UINT16 sz);

#ifdef WLAN_DRV_INTF
acl_data_dispatcher data_dispatcher = NULL;
#else
extern  acl_data_dispatcher data_dispatcher;
#endif

#endif  /* __HCI_H__ */

