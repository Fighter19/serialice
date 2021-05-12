/*
 * SerialICE
 *
 * Copyright (C) 2011 Idwer Vollering <vidwer@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc.
 */

const char boardname[33]="ASRock P4V88                    ";

#define SUPERIO_CONFIG_PORT 0x2e

/* Winbond W83627HG */
static void superio_init(void)
{
        pnp_enter_ext_func_mode(SUPERIO_CONFIG_PORT);
	/* Set the clock to 48MHz (skipped for now, will be fine....) */
        //pnp_write_register(SUPERIO_CONFIG_PORT, 0x24, 0xc0);
        pnp_write_register(SUPERIO_CONFIG_PORT, 0x24, 0x58);
        pnp_write_register(SUPERIO_CONFIG_PORT, 0x23, 0xfe);
        pnp_write_register(SUPERIO_CONFIG_PORT, 0x25, 0x00);
        pnp_write_register(SUPERIO_CONFIG_PORT, 0x26, 0x00);
        pnp_write_register(SUPERIO_CONFIG_PORT, 0x28, 0x00);
        pnp_write_register(SUPERIO_CONFIG_PORT, 0x29, 0x00);
        pnp_write_register(SUPERIO_CONFIG_PORT, 0x2A, 0xff);
    
        pnp_set_logical_device(SUPERIO_CONFIG_PORT, 2);
        pnp_set_enable(SUPERIO_CONFIG_PORT, 0);
        pnp_set_iobase0(SUPERIO_CONFIG_PORT, 0x3f8);
        pnp_set_irq0(SUPERIO_CONFIG_PORT, 4);
        pnp_set_enable(SUPERIO_CONFIG_PORT, 1);
        pnp_exit_ext_func_mode(SUPERIO_CONFIG_PORT);
}

static void chipset_init(void)
{
        superio_init();
        
    __asm__ __volatile__("\
	jmp skip\n\
	.align 128\n\
	.global via_romstrap\n\
	via_romstrap:\n\
	.long 0x22112211, 0X00000875\n\
	.long 0x0, 0x0\n\
	.long 0x0, 0x0\n\
	.long 0x0\n\
	.long 0x0\n\
	.long 0x0\n\
	.long 0x0\n\
	.long 0x0\n\
	.long 0x0\n\
	.long 0x0\n\
	.long 0x0\n\
	.long 0x0\n\
	.long 0x0\n\
	.long 0x0\n\
	.long 0x0\n\
	.align 128\n\
	skip:\n");
}
