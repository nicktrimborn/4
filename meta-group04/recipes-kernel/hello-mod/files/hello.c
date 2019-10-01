/******************************************************************************
 *
 *   Copyright (C) 2011  Intel Corporation. All rights reserved.
 *
 *   This program is free software;  you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; version 2 of the License.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY;  without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 *   the GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program;  if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 *****************************************************************************/

#include <linux/kernel.h>
#include <linux/module.h> 
#include <linux/moduleparam.h> 

static char *Load = "Hello World";
module_param(Load,charp,0660);
static char *Unload = "Goodbye cruel World";
module_param(Unload,charp,0660);
int init_module(void)
{
	printk("%s\n", Load);
	return 0;
}

void cleanup_module(void)
{
	printk("%s\n", Unload);
}

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("This is Hello World Kernel Module for the Real-time systems course");
MODULE_AUTHOR("Nicolas Trimborn");
MODULE_AUTHOR("Tarun Reddy");
MODULE_AUTHOR("Emmanuel Aidoo");
MODULE_VERSION("1.0");
