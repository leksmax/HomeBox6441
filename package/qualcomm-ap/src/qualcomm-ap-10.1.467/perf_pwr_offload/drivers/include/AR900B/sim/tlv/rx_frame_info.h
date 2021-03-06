// Copyright (c) 2012 Qualcomm Atheros, Inc.  All rights reserved.
// $ATH_LICENSE_HW_HDR_C$
//
// DO NOT EDIT!  This file is automatically generated
//               These definitions are tied to a particular hardware layout


#ifndef _RX_FRAME_INFO_H_
#define _RX_FRAME_INFO_H_
#if !defined(__ASSEMBLER__)
#endif

// ################ START SUMMARY #################
//
//	Dword	Fields
//	0	frame_control[15:0], duration[31:16]
//	1	addr1_31_0[31:0]
//	2	addr1_47_32[15:0], addr2_15_0[31:16]
//	3	addr2_47_16[31:0]
//	4	ba_ts_cntl[15:0], ba_ts_seq[31:16]
//	5	ba_ts_bitmap_31_0[31:0]
//	6	ba_ts_bitmap_63_32[31:0]
//	7	pkt_type[1:0], reserved_7[2], rate_mcs[6:3], agc_cbw[8:7], sgi[9], stbc[10], ldpc[11], ampdu[12], vht_ack[13], rts_ta_grp_bit[14], cntl_frame_soliciting_resp[15], service_cbw[17:16], service_dynamic[18], m_pkt[19], partial_aid[29:20], cts_cbw[31:30]
//	8	group_id[4:0], ctrl_resp_pwr_mgmt[5], cbf_resp_pwr_mgmt[6], reserved_8[31:7]
//
// ################ END SUMMARY #################

#define NUM_OF_DWORDS_RX_FRAME_INFO 9

struct rx_frame_info {
    volatile uint32_t frame_control                   : 16, //[15:0]
                      duration                        : 16; //[31:16]
    volatile uint32_t addr1_31_0                      : 32; //[31:0]
    volatile uint32_t addr1_47_32                     : 16, //[15:0]
                      addr2_15_0                      : 16; //[31:16]
    volatile uint32_t addr2_47_16                     : 32; //[31:0]
    volatile uint32_t ba_ts_cntl                      : 16, //[15:0]
                      ba_ts_seq                       : 16; //[31:16]
    volatile uint32_t ba_ts_bitmap_31_0               : 32; //[31:0]
    volatile uint32_t ba_ts_bitmap_63_32              : 32; //[31:0]
    volatile uint32_t pkt_type                        :  2, //[1:0]
                      reserved_7                      :  1, //[2]
                      rate_mcs                        :  4, //[6:3]
                      agc_cbw                         :  2, //[8:7]
                      sgi                             :  1, //[9]
                      stbc                            :  1, //[10]
                      ldpc                            :  1, //[11]
                      ampdu                           :  1, //[12]
                      vht_ack                         :  1, //[13]
                      rts_ta_grp_bit                  :  1, //[14]
                      cntl_frame_soliciting_resp      :  1, //[15]
                      service_cbw                     :  2, //[17:16]
                      service_dynamic                 :  1, //[18]
                      m_pkt                           :  1, //[19]
                      partial_aid                     : 10, //[29:20]
                      cts_cbw                         :  2; //[31:30]
    volatile uint32_t group_id                        :  5, //[4:0]
                      ctrl_resp_pwr_mgmt              :  1, //[5]
                      cbf_resp_pwr_mgmt               :  1, //[6]
                      reserved_8                      : 25; //[31:7]
};

/*

frame_control
			
			frame control field of the received frame

duration
			
			duration field of the received frame

addr1_31_0
			
			lower 32 bits of addr1 of the received frame

addr1_47_32
			
			upper 16 bits of addr1 of the received frame

addr2_15_0
			
			lower 16 bits of addr2 of the received frame

addr2_47_16
			
			upper 32 bits of addr2 of the received frame

ba_ts_cntl
			
			Transmit BA control. 

ba_ts_seq
			
			Transmit BA sequence number. 

ba_ts_bitmap_31_0
			
			Transmit BA bitmap[31:0]

ba_ts_bitmap_63_32
			
			Transmit BA bitmap[63:32]

pkt_type
			
			Packet type:
			
			<enum_typedef tx_phy_desc pkt_type>
			
			<enum 0 dot11a>
			
			<enum 1 dot11b>
			
			<enum 2 dot11n_mm>
			
			<enum 3 dot11ac>
			
			Note: HT Greenfield packet type is not supported
			
			<legal 0-3>

reserved_7
			
			Reserved: <legal 0>

rate_mcs
			

agc_cbw
			
			
			
			BW as detected by the AGC 
			
			<enum_typedef tx_phy_desc bandwidth>
			
			<enum 0     20_mhz>
			
			<enum 1     40_mhz>
			
			<enum 2     80_mhz>
			
			<enum 3     160_mhz> Unsupported
			
			<valid 0-2>

sgi
			
			Indicate Short GI

stbc
			
			Indicate STBC

ldpc
			
			Indicate LDPC

ampdu
			
			Does txpcu use this info to know whether to send ba or
			not? Or it's also used for other purpose? If the former, why
			the next bit is needed? 

vht_ack
			
			set when it's single mpdu inside ampdu

rts_ta_grp_bit
			
			frame is rts and TA G/I bit is set

cntl_frame_soliciting_resp
			
			frame is rts or ps_poll or cf_end or br_poll or ndpa and
			TA G/I bit is set

service_cbw
			
			CBW field extracted from Service field
			
			<enum_typedef tx_phy_desc bandwidth>
			
			<enum 0     20_mhz>
			
			<enum 1     40_mhz>
			
			<enum 2     80_mhz>
			
			<enum 3     160_mhz> Unsupported
			
			<valid 0-2>

service_dynamic
			
			Dynamic field extracted from Service field

m_pkt
			
			m_pkt in rtt3
			
			(What is the signal name used?)

partial_aid
			
			Specifies the partial AID of response frames transmitted
			at VHT rates.

cts_cbw
			
			Calculated bandwidth for the CTS response frame
			
			<enum_typedef tx_phy_desc bandwidth>
			
			<enum 0     20_mhz>
			
			<enum 1     40_mhz>
			
			<enum 2     80_mhz>
			
			<enum 3     160_mhz> Unsupported
			
			<valid 0-2>

group_id
			
			Specifies the Group ID of response frames transmitted at
			VHT rates.

ctrl_resp_pwr_mgmt
			
			RX PCU passes this bit (coming from the peer entry)
			setting on to TX PCU, where the setting of this bit is
			inserted in the pwr_mgt bit in the control field of the SIFS
			response control frames: ACK, CTS, BA
			
			<legal all>

cbf_resp_pwr_mgmt
			
			RX PCU passes this bit (coming from the peer entry)
			setting on to TX PCU, where the setting of this bit is
			inserted in the pwr_mgt bit in the control field of the Cbf
			frame.
			
			<legal all>

reserved_8
			
			Reserved: Generator should set to 0, consumer shall
			ignore <legal 0>
*/


/* Description		RX_FRAME_INFO_0_FRAME_CONTROL
			
			frame control field of the received frame
*/
#define RX_FRAME_INFO_0_FRAME_CONTROL_OFFSET                         0x00000000
#define RX_FRAME_INFO_0_FRAME_CONTROL_LSB                            0
#define RX_FRAME_INFO_0_FRAME_CONTROL_MASK                           0x0000ffff

/* Description		RX_FRAME_INFO_0_DURATION
			
			duration field of the received frame
*/
#define RX_FRAME_INFO_0_DURATION_OFFSET                              0x00000000
#define RX_FRAME_INFO_0_DURATION_LSB                                 16
#define RX_FRAME_INFO_0_DURATION_MASK                                0xffff0000

/* Description		RX_FRAME_INFO_1_ADDR1_31_0
			
			lower 32 bits of addr1 of the received frame
*/
#define RX_FRAME_INFO_1_ADDR1_31_0_OFFSET                            0x00000004
#define RX_FRAME_INFO_1_ADDR1_31_0_LSB                               0
#define RX_FRAME_INFO_1_ADDR1_31_0_MASK                              0xffffffff

/* Description		RX_FRAME_INFO_2_ADDR1_47_32
			
			upper 16 bits of addr1 of the received frame
*/
#define RX_FRAME_INFO_2_ADDR1_47_32_OFFSET                           0x00000008
#define RX_FRAME_INFO_2_ADDR1_47_32_LSB                              0
#define RX_FRAME_INFO_2_ADDR1_47_32_MASK                             0x0000ffff

/* Description		RX_FRAME_INFO_2_ADDR2_15_0
			
			lower 16 bits of addr2 of the received frame
*/
#define RX_FRAME_INFO_2_ADDR2_15_0_OFFSET                            0x00000008
#define RX_FRAME_INFO_2_ADDR2_15_0_LSB                               16
#define RX_FRAME_INFO_2_ADDR2_15_0_MASK                              0xffff0000

/* Description		RX_FRAME_INFO_3_ADDR2_47_16
			
			upper 32 bits of addr2 of the received frame
*/
#define RX_FRAME_INFO_3_ADDR2_47_16_OFFSET                           0x0000000c
#define RX_FRAME_INFO_3_ADDR2_47_16_LSB                              0
#define RX_FRAME_INFO_3_ADDR2_47_16_MASK                             0xffffffff

/* Description		RX_FRAME_INFO_4_BA_TS_CNTL
			
			Transmit BA control. 
*/
#define RX_FRAME_INFO_4_BA_TS_CNTL_OFFSET                            0x00000010
#define RX_FRAME_INFO_4_BA_TS_CNTL_LSB                               0
#define RX_FRAME_INFO_4_BA_TS_CNTL_MASK                              0x0000ffff

/* Description		RX_FRAME_INFO_4_BA_TS_SEQ
			
			Transmit BA sequence number. 
*/
#define RX_FRAME_INFO_4_BA_TS_SEQ_OFFSET                             0x00000010
#define RX_FRAME_INFO_4_BA_TS_SEQ_LSB                                16
#define RX_FRAME_INFO_4_BA_TS_SEQ_MASK                               0xffff0000

/* Description		RX_FRAME_INFO_5_BA_TS_BITMAP_31_0
			
			Transmit BA bitmap[31:0]
*/
#define RX_FRAME_INFO_5_BA_TS_BITMAP_31_0_OFFSET                     0x00000014
#define RX_FRAME_INFO_5_BA_TS_BITMAP_31_0_LSB                        0
#define RX_FRAME_INFO_5_BA_TS_BITMAP_31_0_MASK                       0xffffffff

/* Description		RX_FRAME_INFO_6_BA_TS_BITMAP_63_32
			
			Transmit BA bitmap[63:32]
*/
#define RX_FRAME_INFO_6_BA_TS_BITMAP_63_32_OFFSET                    0x00000018
#define RX_FRAME_INFO_6_BA_TS_BITMAP_63_32_LSB                       0
#define RX_FRAME_INFO_6_BA_TS_BITMAP_63_32_MASK                      0xffffffff

/* Description		RX_FRAME_INFO_7_PKT_TYPE
			
			Packet type:
			
			<enum_typedef tx_phy_desc pkt_type>
			
			<enum 0 dot11a>
			
			<enum 1 dot11b>
			
			<enum 2 dot11n_mm>
			
			<enum 3 dot11ac>
			
			Note: HT Greenfield packet type is not supported
			
			<legal 0-3>
*/
#define RX_FRAME_INFO_7_PKT_TYPE_OFFSET                              0x0000001c
#define RX_FRAME_INFO_7_PKT_TYPE_LSB                                 0
#define RX_FRAME_INFO_7_PKT_TYPE_MASK                                0x00000003

/* Description		RX_FRAME_INFO_7_RESERVED_7
			
			Reserved: <legal 0>
*/
#define RX_FRAME_INFO_7_RESERVED_7_OFFSET                            0x0000001c
#define RX_FRAME_INFO_7_RESERVED_7_LSB                               2
#define RX_FRAME_INFO_7_RESERVED_7_MASK                              0x00000004

/* Description		RX_FRAME_INFO_7_RATE_MCS
			
*/
#define RX_FRAME_INFO_7_RATE_MCS_OFFSET                              0x0000001c
#define RX_FRAME_INFO_7_RATE_MCS_LSB                                 3
#define RX_FRAME_INFO_7_RATE_MCS_MASK                                0x00000078

/* Description		RX_FRAME_INFO_7_AGC_CBW
			
			
			
			BW as detected by the AGC 
			
			<enum_typedef tx_phy_desc bandwidth>
			
			<enum 0     20_mhz>
			
			<enum 1     40_mhz>
			
			<enum 2     80_mhz>
			
			<enum 3     160_mhz> Unsupported
			
			<valid 0-2>
*/
#define RX_FRAME_INFO_7_AGC_CBW_OFFSET                               0x0000001c
#define RX_FRAME_INFO_7_AGC_CBW_LSB                                  7
#define RX_FRAME_INFO_7_AGC_CBW_MASK                                 0x00000180

/* Description		RX_FRAME_INFO_7_SGI
			
			Indicate Short GI
*/
#define RX_FRAME_INFO_7_SGI_OFFSET                                   0x0000001c
#define RX_FRAME_INFO_7_SGI_LSB                                      9
#define RX_FRAME_INFO_7_SGI_MASK                                     0x00000200

/* Description		RX_FRAME_INFO_7_STBC
			
			Indicate STBC
*/
#define RX_FRAME_INFO_7_STBC_OFFSET                                  0x0000001c
#define RX_FRAME_INFO_7_STBC_LSB                                     10
#define RX_FRAME_INFO_7_STBC_MASK                                    0x00000400

/* Description		RX_FRAME_INFO_7_LDPC
			
			Indicate LDPC
*/
#define RX_FRAME_INFO_7_LDPC_OFFSET                                  0x0000001c
#define RX_FRAME_INFO_7_LDPC_LSB                                     11
#define RX_FRAME_INFO_7_LDPC_MASK                                    0x00000800

/* Description		RX_FRAME_INFO_7_AMPDU
			
			Does txpcu use this info to know whether to send ba or
			not? Or it's also used for other purpose? If the former, why
			the next bit is needed? 
*/
#define RX_FRAME_INFO_7_AMPDU_OFFSET                                 0x0000001c
#define RX_FRAME_INFO_7_AMPDU_LSB                                    12
#define RX_FRAME_INFO_7_AMPDU_MASK                                   0x00001000

/* Description		RX_FRAME_INFO_7_VHT_ACK
			
			set when it's single mpdu inside ampdu
*/
#define RX_FRAME_INFO_7_VHT_ACK_OFFSET                               0x0000001c
#define RX_FRAME_INFO_7_VHT_ACK_LSB                                  13
#define RX_FRAME_INFO_7_VHT_ACK_MASK                                 0x00002000

/* Description		RX_FRAME_INFO_7_RTS_TA_GRP_BIT
			
			frame is rts and TA G/I bit is set
*/
#define RX_FRAME_INFO_7_RTS_TA_GRP_BIT_OFFSET                        0x0000001c
#define RX_FRAME_INFO_7_RTS_TA_GRP_BIT_LSB                           14
#define RX_FRAME_INFO_7_RTS_TA_GRP_BIT_MASK                          0x00004000

/* Description		RX_FRAME_INFO_7_CNTL_FRAME_SOLICITING_RESP
			
			frame is rts or ps_poll or cf_end or br_poll or ndpa and
			TA G/I bit is set
*/
#define RX_FRAME_INFO_7_CNTL_FRAME_SOLICITING_RESP_OFFSET            0x0000001c
#define RX_FRAME_INFO_7_CNTL_FRAME_SOLICITING_RESP_LSB               15
#define RX_FRAME_INFO_7_CNTL_FRAME_SOLICITING_RESP_MASK              0x00008000

/* Description		RX_FRAME_INFO_7_SERVICE_CBW
			
			CBW field extracted from Service field
			
			<enum_typedef tx_phy_desc bandwidth>
			
			<enum 0     20_mhz>
			
			<enum 1     40_mhz>
			
			<enum 2     80_mhz>
			
			<enum 3     160_mhz> Unsupported
			
			<valid 0-2>
*/
#define RX_FRAME_INFO_7_SERVICE_CBW_OFFSET                           0x0000001c
#define RX_FRAME_INFO_7_SERVICE_CBW_LSB                              16
#define RX_FRAME_INFO_7_SERVICE_CBW_MASK                             0x00030000

/* Description		RX_FRAME_INFO_7_SERVICE_DYNAMIC
			
			Dynamic field extracted from Service field
*/
#define RX_FRAME_INFO_7_SERVICE_DYNAMIC_OFFSET                       0x0000001c
#define RX_FRAME_INFO_7_SERVICE_DYNAMIC_LSB                          18
#define RX_FRAME_INFO_7_SERVICE_DYNAMIC_MASK                         0x00040000

/* Description		RX_FRAME_INFO_7_M_PKT
			
			m_pkt in rtt3
			
			(What is the signal name used?)
*/
#define RX_FRAME_INFO_7_M_PKT_OFFSET                                 0x0000001c
#define RX_FRAME_INFO_7_M_PKT_LSB                                    19
#define RX_FRAME_INFO_7_M_PKT_MASK                                   0x00080000

/* Description		RX_FRAME_INFO_7_PARTIAL_AID
			
			Specifies the partial AID of response frames transmitted
			at VHT rates.
*/
#define RX_FRAME_INFO_7_PARTIAL_AID_OFFSET                           0x0000001c
#define RX_FRAME_INFO_7_PARTIAL_AID_LSB                              20
#define RX_FRAME_INFO_7_PARTIAL_AID_MASK                             0x3ff00000

/* Description		RX_FRAME_INFO_7_CTS_CBW
			
			Calculated bandwidth for the CTS response frame
			
			<enum_typedef tx_phy_desc bandwidth>
			
			<enum 0     20_mhz>
			
			<enum 1     40_mhz>
			
			<enum 2     80_mhz>
			
			<enum 3     160_mhz> Unsupported
			
			<valid 0-2>
*/
#define RX_FRAME_INFO_7_CTS_CBW_OFFSET                               0x0000001c
#define RX_FRAME_INFO_7_CTS_CBW_LSB                                  30
#define RX_FRAME_INFO_7_CTS_CBW_MASK                                 0xc0000000

/* Description		RX_FRAME_INFO_8_GROUP_ID
			
			Specifies the Group ID of response frames transmitted at
			VHT rates.
*/
#define RX_FRAME_INFO_8_GROUP_ID_OFFSET                              0x00000020
#define RX_FRAME_INFO_8_GROUP_ID_LSB                                 0
#define RX_FRAME_INFO_8_GROUP_ID_MASK                                0x0000001f

/* Description		RX_FRAME_INFO_8_CTRL_RESP_PWR_MGMT
			
			RX PCU passes this bit (coming from the peer entry)
			setting on to TX PCU, where the setting of this bit is
			inserted in the pwr_mgt bit in the control field of the SIFS
			response control frames: ACK, CTS, BA
			
			<legal all>
*/
#define RX_FRAME_INFO_8_CTRL_RESP_PWR_MGMT_OFFSET                    0x00000020
#define RX_FRAME_INFO_8_CTRL_RESP_PWR_MGMT_LSB                       5
#define RX_FRAME_INFO_8_CTRL_RESP_PWR_MGMT_MASK                      0x00000020

/* Description		RX_FRAME_INFO_8_CBF_RESP_PWR_MGMT
			
			RX PCU passes this bit (coming from the peer entry)
			setting on to TX PCU, where the setting of this bit is
			inserted in the pwr_mgt bit in the control field of the Cbf
			frame.
			
			<legal all>
*/
#define RX_FRAME_INFO_8_CBF_RESP_PWR_MGMT_OFFSET                     0x00000020
#define RX_FRAME_INFO_8_CBF_RESP_PWR_MGMT_LSB                        6
#define RX_FRAME_INFO_8_CBF_RESP_PWR_MGMT_MASK                       0x00000040

/* Description		RX_FRAME_INFO_8_RESERVED_8
			
			Reserved: Generator should set to 0, consumer shall
			ignore <legal 0>
*/
#define RX_FRAME_INFO_8_RESERVED_8_OFFSET                            0x00000020
#define RX_FRAME_INFO_8_RESERVED_8_LSB                               7
#define RX_FRAME_INFO_8_RESERVED_8_MASK                              0xffffff80


#endif // _RX_FRAME_INFO_H_
