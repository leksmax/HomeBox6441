/*
 * Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 2000, 2001, 2004 MIPS Technologies, Inc.
 * Copyright (C) 2001 Ralf Baechle
 *
 *  This program is free software; you can distribute it and/or modify it
 *  under the terms of the GNU General Public License (Version 2) as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place - Suite 330, Boston MA 02111-1307, USA.
 *
 */
#include <linux/init.h>
#include <linux/interrupt.h>
#include <asm/irq_cpu.h>
#include <asm/mipsregs.h>
#include <asm/system.h>
#include <linux/sched.h>
#include <linux/ioport.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/kernel_stat.h>
#include <linux/kernel.h>
#include <linux/random.h>
#include <linux/platform_device.h>
#include <asm/ifx/ifx_regs.h>
#include <asm/mips-boards/generic.h>
#include <asm/mips-boards/prom.h>
#include <asm/bootinfo.h>
#include <asm/reboot.h>
#include <linux/netdevice.h>

/* List of the devices and their resources for enumeration during platform init */

#define MTLK_DEVICE_NAME    "mtlk"

#define MTLK_MEM_BAR0_NAME  "mtlk_wlan_bar0"
/* This memory region covers NPU memory from  */
/* start of shared RAM and until end of HTExt */
/* See http://narnia/svn/hyp3.5/VLSI/Specs/NPU/DRD-054-006%20NPU%20top%20VLSI%20spec.docx */
//#define MTLK_MEM_BAR1_START (0x06000000)
//#define MTLK_MEM_BAR1_END   (0x062FFFFF)


#define MTLK_MEM_BAR1_NAME  "mtlk_wlan_bar1"
#define MTLK_MEM_BAR1_START (0x1A000000)
#define MTLK_MEM_BAR1_END   (0x1A7FFFFF)

#define MTLK_WIRELESS_IRQ_IN_INDEX INT_NUM_IM0_IRL18 
#define MTLK_WIRELESS_IRQ_OUT_INDEX INT_NUM_IM0_IRL18

unsigned int wlanm_val;

static struct resource mtlk_ahb_resources[] = {
  [0] = {
    .name  = MTLK_MEM_BAR0_NAME,
    .start = 0,
    .end   = 0,
    .flags = IORESOURCE_MEM,
  },
  [1] = {
    .name  = MTLK_MEM_BAR1_NAME,
    .start = MTLK_MEM_BAR1_START,
    .end   = MTLK_MEM_BAR1_END,
    .flags = IORESOURCE_MEM,
  },
  [2] = {
    .start = MTLK_WIRELESS_IRQ_IN_INDEX,
    .end   = MTLK_WIRELESS_IRQ_OUT_INDEX,
    .flags = IORESOURCE_IRQ,
    }
};

static struct platform_device mtlk_device = {
	.name = MTLK_DEVICE_NAME,
	.id	= 0,
    .num_resources = ARRAY_SIZE(mtlk_ahb_resources),
	.resource = mtlk_ahb_resources,
};

/* If needed, more devices should be added to this array */
static struct platform_device *mtlk_platform_devices[] __initdata = {
	&mtlk_device,
};
static int __init get_wlanm(char *str)
{
	int retval;
	retval=get_option(&str, &wlanm_val);
	return 1;
}

static int __init mtlk_platform_init(void)
{
	mtlk_ahb_resources[0].start = wlanm_val << 20;
	mtlk_ahb_resources[0].end = mtlk_ahb_resources[0].start + 0xfffff;
	printk("!!!!!!! WAVE400 system registeration on AHB \n");
	printk("MTLK_MEM_BAR0_START is %x\n", mtlk_ahb_resources[0].start);
	printk("MTLK_MEM_BAR0_END is %x\n", mtlk_ahb_resources[0].end);
	printk("MTLK_MEM_BAR1_START is %x\n", MTLK_MEM_BAR1_START);
	printk("MTLK_MEM_BAR1_END is %x\n", MTLK_MEM_BAR1_END);
	printk("MTLK_WIRELESS_IRQ_IN_INDEX is %d\n",  MTLK_WIRELESS_IRQ_IN_INDEX);

	return platform_add_devices(mtlk_platform_devices,
			                    ARRAY_SIZE(mtlk_platform_devices));
}

__setup("wlanm=", get_wlanm);
arch_initcall(mtlk_platform_init);
