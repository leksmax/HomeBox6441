#
# Openwrt Makefile for ifx-devm
#

#### Includes ###################################
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

#### Package Info ##############################
PKG_NAME:=ifx-devm
PKG_VERSION:=2.1.0.8
PKG_RELEASE:=1
PKG_MD5SUM:=69f65e9a59617376293809b2ef547363
PKG_BASE_NAME:=ifx_devm
PKG_SOURCE:=$(PKG_BASE_NAME)-$(PKG_VERSION).tar.gz
PKG_CAT:=zcat
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_BASE_NAME)-$(PKG_VERSION)
PKG_SOURCE_URL:=http://localhost
PKG_BUILD_DEPENDS:=PACKAGE_ifx-dsl-cpe-api-danube:ifx-dsl-cpe-api-danube PACKAGE_ifx-dsl-cpe-control-danube:ifx-dsl-cpe-control-danube base-files-ifxcpe PACKAGE_ifx-voip:ifx-voip PACKAGE_ifx-dsl-cpe-api-vrx:ifx-dsl-cpe-api-vrx PACKAGE_ifx-dsl-cpe-api-vrx-bonding:ifx-dsl-cpe-api-vrx-bonding PACKAGE_ifx-dsl-cpe-control-vrx:ifx-dsl-cpe-control-vrx PACKAGE_ifx-dsl-cpe-control-vrx-bonding:ifx-dsl-cpe-control-vrx-bonding
#PKG_FILE_DEPENDS:=$(STAGING_DIR)/usr/include/ifx_config.h
PKG_DEFAULT_CUSTOM_SOURCE_DIR:=$(TOPDIR)/../../../wlnsw/wireline_sw_devm/devm_ifx_config
PKG_NO_AUTORECONF=y

PKG_CONFIG_DEPENDS_REBUILD=y
PKG_CONFIG_DEPENDS:=\
        $(foreach _mr,$(shell grep -w config config/Config.in|awk '{ print $$2 }'),CONFIG_$(_mr)) \
        $(shell cat config/configs_used.list)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/package-version-override.mk

define Package/$(PKG_NAME)
	SECTION:=utils
	CATEGORY:=Lantiq
	TITLE:=Lantiq device manager module
	URL:=http://www.lantiq.com
	MAINTAINER:=Lantiq Technologies AG
	DEPENDS:=+ifx-oam +ifx-IFXAPIs
	MENU:=1
endef

define Package/$(PKG_NAME)/description
	This package contains Lantiq Device Manager module.
endef

define KernelPackage/ltq-netdev-adv-stats
	SUBMENU:=Lantiq
	TITLE:=Netdevice Advance Stats
	DEPENDS:=@LINUX_2_6
	KCONFIG:=CONFIG_LTQ_NETDEV_ADVANCE_STATS=y
endef

define KernelPackage/ltq-netdev-adv-stats/description
	Kernel module to support advance netdevice stats
endef


#### Directory Paths ############################
IFX_APIS_DIR:=$(wildcard $(BUILD_DIR)/ifx_IFXAPIs*)
IFX_DSL_CPE_API_INCLUDES:=$(STAGING_DIR)/usr/include/drv_dsl_cpe_api/
U_BOOT_SRC:=$(PKG_BUILD_DIR)/u-boot
VOIP_DIR:=$(wildcard $(BUILD_DIR)/ifx_voip-*)

### Menuconfig ##################################
define Package/$(PKG_NAME)/config
$(call Package/$(PKG_NAME)/override_version)
$(call Package/$(PKG_NAME)/override_source_path)
	menu "$(PKG_NAME) features"
	depends on PACKAGE_$(PKG_NAME)
	source "$(SOURCE)/config/Config.in"
	endmenu
endef

### Configurations depends on Menuconfig ########
IFX_ROOTFS_DIR:=$(PKG_BUILD_DIR) #Need to modify this later
STATIC=0
TR69DEBUG=0
DEBUG=0 
STANDALONE=0
TR69SYSLOG=
TR69APPL=1
TR69_DEVELOPMENT=0
BUILD_ROOTFS_DIR:=$(PKG_BUILD_DIR) #Need to modify this later
IFX_RCCONF_LOCN:=$(STAGING_DIR)/usr/include

#Defined Cross Compiler
#TARGET=mips-linux-

ifeq ($(CONFIG_FEATURE_IFX_TR69_HOSTENV),)
TARGET=$(TARGET_CROSS)
endif
export $(TARGET_CONFIGURE_OPTS)

ifeq ($(CONFIG_PACKAGE_matrixtunnel),y)
	SSL:=MATRIXSSL
else
	SSL:=OPENSSL
endif

IFX_CFLAGS_y:=
IFX_LDFLAGS_y:=

IFX_CFLAGS_y +=$(TARGET_CFLAGS) -Wall -DBUILD_FROM_LTQ_APPS
IFX_CFLAGS_y +=-I$(IFX_APIS_DIR)/include
IFX_CFLAGS_y +=-I$(STAGING_DIR)/usr/include

ifeq ($(CONFIG_IFX_CONFIG_FLASH_TYPE),"SPI")
	IFX_CFLAGS_y +=-DSPI_SUPPORT
endif

ifdef CONFIG_IFX_DECT_SUPPORT
IFX_CFLAGS_y += -DDECT_SUPPORT
endif

ifeq ($(CONFIG_FEATURE_IFX_TR69_DEBUG),y)
#  DEBUG=1 
  TR69DEBUG=1
  DBUG=_dbg
  PKG_DBUG=
  PKG_TR69DEBUG=0
else
  DBUG=
  PKG_DBUG=_dbg
  PKG_TR69DEBUG=1
endif

ifeq ($(CONFIG_FEATURE_LTQ_VALGRIND_DEVM),y)
export CONFIG_FEATURE_LTQ_VALGRIND_DEVM
endif

ifeq ($(CONFIG_PACKAGE_ifx-dsl-cpe-api-danube),y)
	IFX_CFLAGS_y +=-DLINUX \
		-I$(IFX_DSL_CPE_API_INCLUDES) \
		-DDSL_CHANNELS_PER_LINE=1

	ifeq ($(CONFIG_IFX_CONFIG_CPU),"AMAZON_SE")
		IFX_CFLAGS_y +=-DINCLUDE_DSL_CPE_API_DANUBE -DCONFIG_PACKAGE_IFX_DSL_CPE_API \
			-DINCLUDE_DSL_ADSL_MIB
	endif

	ifeq ($(CONFIG_IFX_CONFIG_CPU),"DANUBE")
		IFX_CFLAGS_y +=-DINCLUDE_DSL_CPE_API_DANUBE -DCONFIG_PACKAGE_IFX_DSL_CPE_API \
			-DINCLUDE_DSL_ADSL_MIB
	endif

	ifeq ($(CONFIG_IFX_CONFIG_CPU),"AMAZON_S")
		IFX_CFLAGS_y +=-DINCLUDE_DSL_CPE_API_DANUBE -DCONFIG_PACKAGE_IFX_DSL_CPE_API \
			-DINCLUDE_DSL_ADSL_MIB
	endif

	ifeq ($(CONFIG_IFX_CONFIG_CPU),"XRX3XX")
		IFX_CFLAGS_y +=-DINCLUDE_DSL_CPE_API_DANUBE -DCONFIG_PACKAGE_IFX_DSL_CPE_API \
			-DINCLUDE_DSL_ADSL_MIB
	endif
else
  ifeq ($(CONFIG_PACKAGE_ifx-dsl-cpe-api-vrx),y)
   	IFX_CFLAGS_y +=-DLINUX \
		-I$(IFX_DSL_CPE_API_INCLUDES) \
		-DDSL_CHANNELS_PER_LINE=1

	IFX_CFLAGS_y +=-DINCLUDE_DSL_CPE_API_VRX -DCONFIG_PACKAGE_IFX_DSL_CPE_API \
			-DINCLUDE_DSL_ADSL_MIB
  endif
  ifeq ($(CONFIG_PACKAGE_ifx-dsl-cpe-api-vrx-bonding),y)
   	IFX_CFLAGS_y +=-DLINUX \
		-I$(IFX_DSL_CPE_API_INCLUDES) \
		-DDSL_CHANNELS_PER_LINE=1

	IFX_CFLAGS_y +=-DINCLUDE_DSL_CPE_API_VRX -DCONFIG_PACKAGE_IFX_DSL_CPE_API \
			-DINCLUDE_DSL_ADSL_MIB
  endif

endif

ifeq ($(CONFIG_FEATURE_IFX_WIRELESS),y)
	IFX_CFLAGS_y +=-DIFX_CONFIG_WIRELESS -DCONFIG_FEATURE_IFX_WIRELESS
endif

ifeq ($(CONFIG_FEATURE_IFX_WLAN_WPS),y)
	IFX_CFLAGS_y +=-DIFX_MAPI_WLAN_WPS -DCONFIG_FEATURE_IFX_WLAN_WPS
endif

ifeq ($(CONFIG_FEATURE_IFX_WLAN_WMM),y)
	IFX_CFLAGS_y +=-DIFX_MAPI_WLAN_WMM -DCONFIG_FEATURE_IFX_WLAN_WMM
endif

ifeq ($(CONFIG_FEATURE_IFX_CONCURRENT_DUAL_WIRELESS),y)
        IFX_CFLAGS_y +=-DIFX_MAPI_CONCURRENT_DUAL_WIRELESS -DCONFIG_FEATURE_IFX_CONCURRENT_DUAL_WIRELESS
endif

ifeq ($(CONFIG_FEATURE_IFX_TR111_STUN),y)
	IFX_CFLAGS_y +=-DCONFIG_FEATURE_IFX_TR111_STUN
endif

ifeq ($(CONFIG_TARGET_$(BOARD)_platform_danube),y)
	IFX_CFLAGS_y +=-DPLATFORM_DANUBE
endif
ifeq ($(CONFIG_TARGET_$(BOARD)_platform_ar9),y)
	IFX_CFLAGS_y +=-DPLATFORM_AR9
endif
ifeq ($(CONFIG_TARGET_$(BOARD)_platform_ar10),y)
ifeq ($(CONFIG_TARGET_$(BOARD)_platform_ar10_vrx318),y)
 	IFX_CFLAGS_y +=-DPLATFORM_AR10_VRX318 -DPLATFORM_VR9
else
	IFX_CFLAGS_y +=-DPLATFORM_AR9 -DPLATFORM_AR10
endif
endif
ifeq ($(CONFIG_TARGET_$(BOARD)_platform_amazon_se),y)
	IFX_CFLAGS_y +=-DPLATFORM_AMAZON_SE
endif
ifeq ($(CONFIG_TARGET_$(BOARD)_platform_vr9),y)
	IFX_CFLAGS_y +=-DPLATFORM_VR9
endif

ifeq ($(CONFIG_IFX_MODEL_NAME),"AMAZON_SE_RT_EL_1ETH_PNOR_SAMPLE")
  IFX_CFLAGS_y += -DAMAZON_SE_RT_EL_1ETH_PNOR_SAMPLE
endif

# UBI flag to indicate a change in firmware download location
IFX_CFLAGS_$(CONFIG_TARGET_UBI_MTD_SUPPORT) += -DCONFIG_TARGET_UBI_MTD_SUPPORT

TR69_COMPILE_FLAGS:=CONFIG_IFX_CONFIG_FLASH_SIZE=$(CONFIG_IFX_CONFIG_FLASH_SIZE) \
	STATIC=$(STATIC) STANDALONE=${STANDALONE} \
	$(if $(CONFIG_FEATURE_IFX_TR69_HOSTENV),,TARGET=${TARGET}) TR69SYSLOG=${TR69SYSLOG} \
	TR69APPL=${TR69APPL} SSL=${SSL} CONFIG_PACKAGE_IFX_DEVM=${CONFIG_PACKAGE_IFX_DEVM} \
	CONFIG_FEATURE_IFX_TR69_IGD=${CONFIG_FEATURE_IFX_TR69_IGD} \
	CONFIG_FEATURE_IFX_TR69_WIFILAN=${CONFIG_FEATURE_IFX_TR69_WIFILAN} \
	CONFIG_FEATURE_IFX_TR69_WIFILAN_WMM=${CONFIG_FEATURE_IFX_TR69_WIFILAN_WMM} \
	CONFIG_FEATURE_IFX_TR69_WIFILAN_WPS=${CONFIG_FEATURE_IFX_TR69_WIFILAN_WPS} \
	CONFIG_FEATURE_IFX_TR69_USBLAN=${CONFIG_FEATURE_IFX_TR69_USBLAN} \
	CONFIG_FEATURE_IFX_TR69_ETHERNETLAN=${CONFIG_FEATURE_IFX_TR69_ETHERNETLAN} \
	CONFIG_FEATURE_IFX_TR69_ETHERNETWAN=${CONFIG_FEATURE_IFX_TR69_ETHERNETWAN} \
	CONFIG_FEATURE_IFX_TR69_ADSLWAN=${CONFIG_FEATURE_IFX_TR69_ADSLWAN} \
	CONFIG_FEATURE_IFX_TR69_TIME=${CONFIG_FEATURE_IFX_TR69_TIME} \
	CONFIG_FEATURE_IFX_TR69_IPPING=${CONFIG_FEATURE_IFX_TR69_IPPING} \
	CONFIG_FEATURE_IFX_TR157_PROCESSSTATUS=${CONFIG_FEATURE_IFX_TR157_PROCESSSTATUS} \
        CONFIG_FEATURE_IFX_TR143_DOWNLOADDIAGNOSTICS=${CONFIG_FEATURE_IFX_TR143_DOWNLOADDIAGNOSTICS} \
	CONFIG_FEATURE_IFX_TR143_UPLOADDIAGNOSTICS=${CONFIG_FEATURE_IFX_TR143_UPLOADDIAGNOSTICS} \
        CONFIG_FEATURE_IFX_TR69_CHUNKED_RESP=${CONFIG_FEATURE_IFX_TR69_CHUNKED_RESP} \
	CONFIG_FEATURE_IFX_TR157_USERINFO=${CONFIG_FEATURE_IFX_TR157_USERINFO} \
        CONFIG_FEATURE_IFX_TR64_DIGEST_AUTH=${CONFIG_FEATURE_IFX_TR64_DIGEST_AUTH} \
	CONFIG_FEATURE_IFX_TR157_MEMORYSTATUS=${CONFIG_FEATURE_IFX_TR157_MEMORYSTATUS} \
	CONFIG_FEATURE_IFX_TR157_FIREWALL=${CONFIG_FEATURE_IFX_TR157_FIREWALL} \
	CONFIG_FEATURE_IFX_TR69_X_LTQ_IPPROTOCOLVERSION=${CONFIG_FEATURE_IFX_TR69_X_LTQ_IPPROTOCOLVERSION} \
	CONFIG_FEATURE_IFX_TR69_QUEUED_UPLOAD=${CONFIG_FEATURE_IFX_TR69_QUEUED_UPLOAD} \
	CONFIG_FEATURE_IFX_TR69_QUEUED_DOWNLOAD=${CONFIG_FEATURE_IFX_TR69_QUEUED_DOWNLOAD} \
        CONFIG_FEATURE_IFX_TR69_WANDSLOBJS_FULL_FULL=${CONFIG_FEATURE_IFX_TR69_WANDSLOBJS_FULL_FULL} \
	CONFIG_FEATURE_IFX_TR157_NSLOOKUP=${CONFIG_FEATURE_IFX_TR157_NSLOOKUP} \
        CONFIG_FEATURE_IFX_TR157_SELFTEST=${CONFIG_FEATURE_IFX_TR157_SELFTEST} \
        CONFIG_FEATURE_IFX_TR69_PERFORMDIAG=${CONFIG_FEATURE_IFX_TR69_PERFORMDIAG} \
	CONFIG_FEATURE_DEVM_OVER_IPV6=${CONFIG_FEATURE_DEVM_OVER_IPV6} \
	CONFIG_FEATURE_IFX_TR69_TRACEROUTE=${CONFIG_FEATURE_IFX_TR69_TRACEROUTE} \
	CONFIG_FEATURE_IFX_TR69_ATMLOOPBACK=${CONFIG_FEATURE_IFX_TR69_ATMLOOPBACK} \
	CONFIG_FEATURE_IFX_TR69_DSLDIAGNOSTICS=${CONFIG_FEATURE_IFX_TR69_DSLDIAGNOSTICS} \
	CONFIG_FEATURE_IFX_TR111_STUN=${CONFIG_FEATURE_IFX_TR111_STUN} \
	CONFIG_FEATURE_IFX_TR69_DEVICE_ASSOCIATION=${CONFIG_FEATURE_IFX_TR69_DEVICE_ASSOCIATION} \
	CONFIG_FEATURE_IFX_LMP=${CONFIG_FEATURE_IFX_LMP} \
	CONFIG_FEATURE_IFX_TR69_IPQOS=${CONFIG_FEATURE_IFX_TR69_IPQOS} \
	CONFIG_FEATURE_IFX_TR69_DEVICE=${CONFIG_FEATURE_IFX_TR69_DEVICE} \
	CONFIG_FEATURE_IFX_TR69_DEVICE_LAN=${CONFIG_FEATURE_IFX_TR69_DEVICE_LAN} \
	CONFIG_FEATURE_IFX_TR69_SSL=${CONFIG_FEATURE_IFX_TR69_SSL} \
	CONFIG_FEATURE_IFX_TR69_HOSTENV=$(CONFIG_FEATURE_IFX_TR69_HOSTENV) \
	CONFIG_PACKAGE_matrixssl=${CONFIG_PACKAGE_matrixssl} CONFIG_FEATURE_IFX_TR69_TR64_OVER_IPV6=${CONFIG_FEATURE_IFX_TR69_TR64_OVER_IPV6} \
	BUILD_ROOTFS_DIR=${BUILD_ROOTFS_DIR} IFX_ROOTFS_DIR=${IFX_ROOTFS_DIR} IFX_RCCONF_LOCN=${IFX_RCCONF_LOCN}

IFX_LDFLAGS_y +=-L$(IFX_APIS_DIR)/lib
IFX_LDFLAGS_y +=-L$(STAGING_DIR)/usr/lib -Wl,-rpath-link,$(STAGING_DIR)/usr/lib

IFX_CFLAGS:=$(IFX_CFLAGS_y)
IFX_LDFLAGS:=$(IFX_LDFLAGS_y)

#### Export Section for FEATURE & Others ########
export CONFIG_FEATURE_IFX_TR104 CONFIG_FEATURE_IFX_TR69_DEVICE CONFIG_FEATURE_IFX_TR69_DEVICE_LAN
export CONFIG_FEATURE_IFX_TR69_DEVICE_ASSOCIATION CONFIG_FEATURE_IFX_TR69_ETHERNETLAN
export CONFIG_FEATURE_IFX_TR69_USBLAN CONFIG_FEATURE_IFX_TR69_ADSLWAN CONFIG_FEATURE_IFX_TR69_ATMLOOPBACK
export CONFIG_FEATURE_IFX_TR69_PTMWAN CONFIG_FEATURE_IFX_TR69_INFORM_DEBUG_TRACE
export CONFIG_FEATURE_IFX_TR69_DSLDIAGNOSTICS CONFIG_FEATURE_IFX_TR69_WIFILAN CONFIG_FEATURE_IFX_TR104
export CONFIG_FEATURE_IFX_TR69_WIFILAN_WMM CONFIG_FEATURE_IFX_TR69_WIFILAN_WPS
export CONFIG_FEATURE_IFX_TR157_USERINFO CONFIG_FEATURE_IFX_TR157_PROCESSSTATUS CONFIG_FEATURE_IFX_TR157_MEMORYSTATUS
export CONFIG_FEATURE_IFX_TR143_DOWNLOADDIAGNOSTICS CONFIG_FEATURE_IFX_TR143_UPLOADDIAGNOSTICS
export CONFIG_FEATURE_IFX_TR64_DIGEST_AUTH CONFIG_FEATURE_IFX_TR69_CHUNKED_RESP
export CONFIG_FEATURE_IFX_TR69_X_LTQ_IPPROTOCOLVERSION CONFIG_FEATURE_IFX_TR69_TRACEROUTE
export CONFIG_FEATURE_IFX_TR157_FIREWALL CONFIG_FEATURE_IFX_TR157_NSLOOKUP
export CONFIG_FEATURE_IFX_TR69_QUEUED_UPLOAD CONFIG_FEATURE_IFX_TR69_QUEUED_DOWNLOAD CONFIG_FEATURE_IFX_TR69_WANDSLOBJS_FULL
export CONFIG_FEATURE_IFX_TR69_TIME CONFIG_FEATURE_IFX_TR69_IPPING CONFIG_FEATURE_IFX_TR69_IPQOS
export CONFIG_FEATURE_UPNP_IGD_VERSION_1 CONFIG_FEATURE_UPNP_IGD_VERSION_2
export CONFIG_FEATURE_IFX_TR69_DEVICE CONFIG_FEATURE_IFX_ADM6996_UTILITY CONFIG_FEATURE_IFX_TR69_STUN
export CONFIG_FEATURE_IFX_LMP CONFIG_PACKAGE_IFX_DSL_CPE_API CONFIG_PACKAGE_ifx-devm
export CONFIG_FEATURE_IFX_TR69_IGD CONFIG_FEATURE_IFX_TR69_SSL CONFIG_PACKAGE_matrixssl
export CONFIG_FEATURE_IFX_TR69_ADSL2WAN CONFIG_FEATURE_IFX_TR69_VDSL2WAN
export CONFIG_FEATURE_IFX_TR69_ADSL2DSLDIAGNOSTICS CONFIG_FEATURE_IFX_TR69_VDSL2DSLDIAGNOSTICS
export CONFIG_PACKAGE_ifx-voip CONFIG_FEATURE_IFX_TR69_HOSTENV
export CONFIG_FEATURE_DEVM_OVER_IPv6 CONFIG_FEATURE_IFX_TR157_SELFTEST
export CONFIG_FEATURE_IFX_TR69_PERFORMDIAG
export IFX_DECTSS_DIR=$(VOIP_DIR)
#### Target Rules ###############################
define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR)/devm_ifx_cwmp upnpc \
	        $(TR69_COMPILE_FLAGS) \
	        IFX_CFLAGS="$(IFX_CFLAGS)" TR69DEBUG=$(TR69DEBUG) IFX_LDFLAGS="$(IFX_LDFLAGS)"

	$(MAKE) -C $(PKG_BUILD_DIR)/devm_ifx_cwmp devm$(DBUG) \
		$(TR69_COMPILE_FLAGS) TR69DEBUG=$(TR69DEBUG) DEBUG=0 \
		IFX_CFLAGS="$(IFX_CFLAGS)" IFX_LDFLAGS="$(IFX_LDFLAGS)"

# -find $(PKG_BUILD_DIR)/ -follow -type f -name "*.o" |grep -v -e "devm\.o" -e "devm_dbg\.o"| xargs rm -f 
ifeq ($(TR69_DEVELOPMENT),0)
	echo -en "\n\n\nRecompiling with debug support.................\n\n"
	$(MAKE) -C $(PKG_BUILD_DIR)/devm_ifx_cwmp devm$(PKG_DBUG) \
		$(TR69_COMPILE_FLAGS) TR69DEBUG=$(PKG_TR69DEBUG) DEBUG=0 \
		IFX_CFLAGS="$(IFX_CFLAGS)" IFX_LDFLAGS="$(IFX_LDFLAGS)"
endif
endef

TR69_INSTALL_DIR=/ramdisk_copy/etc/tr69/
define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/$(TR69_INSTALL_DIR)
	$(INSTALL_DIR) $(1)/ramdisk_copy/flash/
	$(INSTALL_DIR) $(1)/lib
	$(INSTALL_DIR) $(1)/etc/
	$(INSTALL_DIR) $(1)/etc/init.d/
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/devm_ifx_cwmp/bin/devm$(DBUG) $(1)/usr/sbin/devm
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/devm_ifx_cwmp/bin/devmapp$(DBUG) $(1)/usr/sbin/devmapp
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/devm_ifx_cwmp/bin/minissdpd $(1)/usr/sbin/minissdpd
	$(if $(CONFIG_FEATURE_IFX_TR111_STUN),$(INSTALL_BIN) $(PKG_BUILD_DIR)/devm_ifx_cwmp/bin/libifxstun.so $(1)/lib/)
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/devm_ifx_cwmp/bin/tr69_db.txt $(1)/$(TR69_INSTALL_DIR)
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/devm_ifx_cwmp/bin/devm.conf $(1)/$(TR69_INSTALL_DIR)
	$(if $(CONFIG_FEATURE_IFX_LMP),$(INSTALL_BIN) $(PKG_BUILD_DIR)/devm_ifx_cwmp/bin/tr64_upnp_db.txt $(1)/$(TR69_INSTALL_DIR))
	if [ A$(SSL) = AOPENSSL ]; then \
		$(INSTALL_BIN) $(PKG_BUILD_DIR)/devm_ifx_cwmp/bin/stunnel.conf $(1)/$(TR69_INSTALL_DIR); \
		$(INSTALL_BIN) $(PKG_BUILD_DIR)/devm_ifx_cwmp/bin/stunnel.key $(1)/$(TR69_INSTALL_DIR); \
		$(INSTALL_BIN) $(PKG_BUILD_DIR)/devm_ifx_cwmp/bin/Cert.pem $(1)/ramdisk_copy/flash/; \
	fi
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/devm_open_miniupnpc/upnpc $(1)/usr/sbin/upnpc
	echo "DEVM Sub System : $(PKG_VERSION)"  >>  $(1)/usr/sbin/DEVM_VERSION  
	chmod +x ./scripts/lq_devm_event.sh	
	$(CP) ./scripts/lq_devm_event.sh $(1)/etc/init.d/
endef

define Build/Clean
	if [ -d $(PKG_BUILD_DIR) ]; then $(MAKE) -C $(PKG_BUILD_DIR)/devm_ifx_cwmp clean \
	$(TR69_COMPILE_FLAGS) \
	IFX_CFLAGS="$(IFX_CFLAGS)" IFX_LDFLAGS="$(IFX_LDFLAGS)"; \
	$(RM) -rf $(PKG_BUILD_DIR)/ipkg-$(BOARD); fi
	if [ -d $(PKG_BUILD_DIR) ]; then $(MAKE) -C $(PKG_BUILD_DIR)/devm_ifx_cwmp clean \
	$(TR69_COMPILE_FLAGS) TR69DEBUG=1 DEBUG=0 \
	IFX_CFLAGS="$(IFX_CFLAGS)" IFX_LDFLAGS="$(IFX_LDFLAGS)"; \
	$(RM) -rf $(PKG_BUILD_DIR)/ipkg-$(BOARD); fi
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
$(eval $(call KernelPackage,ltq-netdev-adv-stats))
