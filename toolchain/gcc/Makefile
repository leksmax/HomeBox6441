#
# Copyright (C) 2002-2003 Erik Andersen <andersen@uclibc.org>
# Copyright (C) 2004 Manuel Novoa III <mjn3@uclibc.org>
# Copyright (C) 2005-2006 Felix Fietkau <nbd@openwrt.org>
# Copyright (C) 2006-2010 OpenWrt.org
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

include $(TOPDIR)/rules.mk

PKG_NAME:=gcc
GCC_VERSION:=$(call qstrip,$(CONFIG_GCC_VERSION))

ifeq ($(findstring linaro, $(CONFIG_GCC_VERSION)),linaro)
    ifeq ($(CONFIG_GCC_VERSION),"4.7-linaro")
      PKG_REV:=4.7-2012.10
      PKG_VERSION:=4.7.3
      PKG_VERSION_MAJOR:=4.7
      PKG_MD5SUM:=a5ca87667350f1395d4da40c94ef059c
    endif
    PKG_SOURCE_URL:=http://launchpad.net/gcc-linaro/$(PKG_VERSION_MAJOR)/$(PKG_REV)/+download/
    PKG_SOURCE:=$(PKG_NAME)-linaro-$(PKG_REV).tar.bz2
    GCC_DIR:=gcc-linaro-$(PKG_REV)
    HOST_BUILD_DIR:=$(BUILD_DIR_TOOLCHAIN)/$(GCC_DIR)
else
PKG_VERSION:=$(firstword $(subst +, ,$(GCC_VERSION)))
GCC_DIR:=$(PKG_NAME)-$(PKG_VERSION)

PKG_SOURCE_URL:=@GNU/gcc/gcc-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2

ifeq ($(PKG_VERSION),3.4.6)
  PKG_MD5SUM:=4a21ac777d4b5617283ce488b808da7b
endif
ifeq ($(PKG_VERSION),4.1.2)
  PKG_MD5SUM:=a4a3eb15c96030906d8494959eeda23c
endif
ifeq ($(PKG_VERSION),4.2.4)
  PKG_MD5SUM:=d79f553e7916ea21c556329eacfeaa16
endif
ifeq ($(PKG_VERSION),4.3.3)
  PKG_MD5SUM:=cc3c5565fdb9ab87a05ddb106ba0bd1f
endif
ifeq ($(PKG_VERSION),4.3.4)
  PKG_MD5SUM:=60df63222dbffd53ca11492a2545044f
endif
ifeq ($(PKG_VERSION),4,4,1)
  PKG_MD5SUM:=927eaac3d44b22f31f9c83df82f26436
endif
ifeq ($(PKG_VERSION),4.4.2)
  PKG_MD5SUM:=70f5ac588a79e3c9901d5b34f58d896d
endif
ifeq ($(PKG_VERSION),4.4.3)
  PKG_MD5SUM:=fe1ca818fc6d2caeffc9051fe67ff103
endif
endif

PATCH_DIR=./patches/$(GCC_VERSION)

include $(INCLUDE_DIR)/toolchain-build.mk

HOST_STAMP_BUILT:=$(TOOLCHAIN_DIR)/stamp/.gcc-initial_installed

HOST_BUILD_DIR0:=$(HOST_BUILD_DIR)-minimal
HOST_BUILD_DIR1:=$(HOST_BUILD_DIR)-initial
HOST_BUILD_DIR2:=$(HOST_BUILD_DIR)-final

SEP:=,
TARGET_LANGUAGES:="c$(if $(CONFIG_INSTALL_LIBSTDCPP),$(SEP)c++)$(if $(CONFIG_INSTALL_LIBGCJ),$(SEP)java)"

export libgcc_cv_fixed_point=no
ifdef CONFIG_USE_UCLIBC
  export glibcxx_cv_c99_math_tr1=no
endif

GCC_CONFIGURE:= \
	SHELL="$(BASH)" \
	$(HOST_BUILD_DIR)/configure \
		--prefix=$(TOOLCHAIN_DIR)/usr \
		--build=$(GNU_HOST_NAME) \
		--host=$(GNU_HOST_NAME) \
		--target=$(REAL_GNU_TARGET_NAME) \
		--with-gnu-ld \
		--enable-target-optspace \
		--disable-libgomp \
		--disable-libmudflap \
		--disable-multilib \
		--disable-nls \
		$(if $(CONFIG_GCC_USE_GRAPHITE),--with-host-libstdcxx=-lstdc++) \
		$(SOFT_FLOAT_CONFIG_OPTION) \
		$(call qstrip,$(CONFIG_EXTRA_GCC_CONFIG_OPTIONS)) \
		$(if $(CONFIG_GCC_VERSION_4_3_3_CS),--enable-poison-system-directories)

ifeq ($(CONFIG_GCC_LLVM),)
  GCC_BUILD_TARGET_LIBGCC:=y
  GCC_CONFIGURE+= \
		--with-gmp=$(TOPDIR)/staging_dir/host \
		--with-mpfr=$(TOPDIR)/staging_dir/host \
		--disable-decimal-float
endif

ifneq ($(CONFIG_SSP_SUPPORT),)
  GCC_CONFIGURE+= \
		--enable-libssp
else
  GCC_CONFIGURE+= \
		--disable-libssp
endif

ifneq ($(CONFIG_EXTRA_TARGET_ARCH),)
  GCC_CONFIGURE+= \
		--enable-biarch \
		--enable-targets=$(call qstrip,$(CONFIG_EXTRA_TARGET_ARCH_NAME))-linux-$(TARGET_SUFFIX)
endif

ifeq ($(LIBC),uClibc)
  GCC_CONFIGURE+= \
		--disable-__cxa_atexit
else
  GCC_CONFIGURE+= \
		--enable-__cxa_atexit
endif

GCC_CONFIGURE_STAGE0:= \
	$(GCC_CONFIGURE) \
		--with-newlib \
		--without-headers \
		--enable-languages=c \
		--disable-libssp \
		--disable-shared \
		--disable-threads \

GCC_CONFIGURE_STAGE1:= \
	$(GCC_CONFIGURE) \
		--with-newlib \
		--with-sysroot=$(BUILD_DIR_TOOLCHAIN)/$(LIBC)-dev \
		--enable-languages=c \
		--disable-shared \
		--disable-threads \

GCC_CONFIGURE_STAGE2:= \
	$(GCC_CONFIGURE) \
		--enable-languages=$(TARGET_LANGUAGES) \
		--enable-shared \
		--enable-threads \
		--with-slibdir=$(TOOLCHAIN_DIR)/lib \

ifneq ($(CONFIG_TLS_SUPPORT),)
  GCC_CONFIGURE_STAGE2+= \
		--enable-tls
else
  GCC_CONFIGURE_STAGE2+= \
		--disable-tls
endif

ifdef CONFIG_powerpc
  TARGET_CFLAGS := $(patsubst -Os,-O2,$(TARGET_CFLAGS))
endif

GCC_MAKE:= \
	export SHELL="$(BASH)"; \
	$(MAKE) \
		CFLAGS_FOR_TARGET="$(TARGET_CFLAGS)" \
		CXXFLAGS_FOR_TARGET="$(TARGET_CFLAGS)"

define Host/SetToolchainInfo
	$(SED) 's,TARGET_CROSS=.*,TARGET_CROSS=$(REAL_GNU_TARGET_NAME)-,' $(TOOLCHAIN_DIR)/info.mk
	$(SED) 's,GCC_VERSION=.*,GCC_VERSION=$(GCC_VERSION),' $(TOOLCHAIN_DIR)/info.mk
endef


define Stage0/Configure
	mkdir -p $(HOST_BUILD_DIR0)
	(cd $(HOST_BUILD_DIR0); rm -f config.cache; \
		$(GCC_CONFIGURE_STAGE0) \
	);
endef

define Stage0/Compile
	$(GCC_MAKE) -C $(HOST_BUILD_DIR0) all-gcc
endef

define Stage0/Install
	$(GCC_MAKE) -C $(HOST_BUILD_DIR0) install-gcc
endef


define Stage1/Configure
	mkdir -p $(HOST_BUILD_DIR1)
	(cd $(HOST_BUILD_DIR1); rm -f config.cache; \
		$(GCC_CONFIGURE_STAGE1) \
	);
endef

define Stage1/Compile
	$(CP) $(BUILD_DIR_TOOLCHAIN)/linux-dev/* $(BUILD_DIR_TOOLCHAIN)/$(LIBC)-dev/
	$(GCC_MAKE) -C $(HOST_BUILD_DIR1) \
		all-build-libiberty \
		all-gcc \
		$(if $(GCC_BUILD_TARGET_LIBGCC),all-target-libgcc)
endef

define Stage1/Install
	$(GCC_MAKE) -C $(HOST_BUILD_DIR1) \
		install-gcc \
		$(if $(GCC_BUILD_TARGET_LIBGCC),install-target-libgcc)
	
	# XXX: glibc insists on linking against libgcc_eh
	( cd $(TOOLCHAIN_DIR)/usr/lib/gcc/$(REAL_GNU_TARGET_NAME)/$(PKG_VERSION) ; \
		[ -e libgcc_eh.a ] || ln -sf libgcc.a libgcc_eh.a ; \
		cp libgcc.a libgcc_initial.a; \
	)
endef


define Stage2/Configure
	mkdir -p $(HOST_BUILD_DIR2) $(TOOLCHAIN_DIR)/usr/$(REAL_GNU_TARGET_NAME)
	# Important!  Required for limits.h to be fixed.
	rm -rf $(TOOLCHAIN_DIR)/usr/$(REAL_GNU_TARGET_NAME)/sys-include
	ln -sf ../include $(TOOLCHAIN_DIR)/usr/$(REAL_GNU_TARGET_NAME)/sys-include
	rm -rf $(TOOLCHAIN_DIR)/usr/$(REAL_GNU_TARGET_NAME)/lib
	ln -sf ../lib $(TOOLCHAIN_DIR)/usr/$(REAL_GNU_TARGET_NAME)/lib
	$(if $(CONFIG_mips64)$(CONFIG_mips64el)$(CONFIG_x86_64),ln -sf ../lib64 $(TOOLCHAIN_DIR)/usr/$(REAL_GNU_TARGET_NAME)/lib64)
	(cd $(HOST_BUILD_DIR2); rm -f config.cache; \
		$(GCC_CONFIGURE_STAGE2) \
	);
endef

define Stage2/Compile
	$(GCC_MAKE) -C $(HOST_BUILD_DIR2) all
endef

define SetupExtraArch
	for app in $(TOOLCHAIN_DIR)/usr/bin/$(OPTIMIZE_FOR_CPU)*-{gcc,gcc-*,g++}; do \
		[ -e $$$$app ] || continue; \
		old_base=$$$$(basename $$$$app); \
		new_base=$(call qstrip,$(CONFIG_EXTRA_TARGET_ARCH_NAME))-$$$${old_base##$(OPTIMIZE_FOR_CPU)-}; \
		sed -e "s/@CC_BASE@/$$$$old_base/" \
			-e 's/@EXTRA_ARCH_OPTS@/$(call qstrip,$(CONFIG_EXTRA_TARGET_ARCH_OPTS))/' \
			 ./files/alternate-arch-cc.in > \
			 $(TOOLCHAIN_DIR)/usr/bin/$$$$new_base; \
		chmod a+x $(TOOLCHAIN_DIR)/usr/bin/$$$$new_base; \
	done
endef

define Stage2/Install
	$(_SINGLE)$(GCC_MAKE) -C $(HOST_BUILD_DIR2) install
	# Set up the symlinks to enable lying about target name.
	set -e; \
	(cd $(TOOLCHAIN_DIR)/usr; \
		ln -sf $(REAL_GNU_TARGET_NAME) $(GNU_TARGET_NAME); \
		cd bin; \
		for app in $(REAL_GNU_TARGET_NAME)-* ; do \
			ln -sf $$$${app} \
		   	$(GNU_TARGET_NAME)$$$${app##$(REAL_GNU_TARGET_NAME)}; \
		done; \
	);
	$(if $(CONFIG_EXTRA_TARGET_ARCH),$(call SetupExtraArch))
endef


BUGURL=https://dev.openwrt.org/

define Host/Prepare
	$(call Host/SetToolchainInfo)
	$(call Host/Prepare/Default)
	ln -snf $(GCC_DIR) $(BUILD_DIR_TOOLCHAIN)/$(PKG_NAME)
	$(CP) $(SCRIPT_DIR)/config.{guess,sub} $(HOST_BUILD_DIR)/
	$(SED) 's,^MULTILIB_OSDIRNAMES,# MULTILIB_OSDIRNAMES,' $(HOST_BUILD_DIR)/gcc/config/*/t-*
	$(SED) 's,\(version_string.. = "[0-9\.]*\).*\(";\),\1 (OpenWrt-2.0)\2,' $(HOST_BUILD_DIR)/gcc/version.c
	$(SED) 's,\(bug_report_url.. = "\).*\(";\),\1<URL:$(BUGURL)>\2,' $(HOST_BUILD_DIR)/gcc/version.c
	$(SED) 's,http://gcc.gnu.org/bugs.html,$(BUGURL),' $(HOST_BUILD_DIR)/gcc/configure
	#(cd $(HOST_BUILD_DIR)/libstdc++-v3; autoconf;);
	$(SED) 's,gcc_no_link=yes,gcc_no_link=no,' $(HOST_BUILD_DIR)/libstdc++-v3/configure
	$(call Stage0/Configure)
	$(call Stage0/Compile)
	$(call Stage0/Install)
endef

define Host/Configure
endef

define Host/Compile
	$(call Stage1/Configure)
	$(call Stage1/Compile)
	$(call Stage1/Install)
endef

define Host/Install
	$(call Stage2/Configure)
	$(call Stage2/Compile)
	$(call Stage2/Install)
endef

define Host/Clean
	rm -rf \
		$(HOST_BUILD_DIR) \
		$(HOST_BUILD_DIR0) \
		$(HOST_BUILD_DIR1) \
		$(HOST_BUILD_DIR2) \
		$(BUILD_DIR_TOOLCHAIN)/$(PKG_NAME) \
		$(TOOLCHAIN_DIR)/usr/$(REAL_GNU_TARGET_NAME) \
		$(TOOLCHAIN_DIR)/usr/bin/$(REAL_GNU_TARGET_NAME)-gc* \
		$(TOOLCHAIN_DIR)/usr/bin/$(REAL_GNU_TARGET_NAME)-c*
endef

$(eval $(call HostBuild))
