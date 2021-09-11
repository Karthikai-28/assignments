/**
 * simple.c
 *
 * A simple kernel module. 
 * 
 * To compile, run makefile by entering "make"
 *
 * Operating System Concepts - 10th Edition
 * Copyright John Wiley & Sons - 2018
 */

#define MODULE
#define LINUX
#define __KERNEL__

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

int inp_pid = 0;
struct task_struct *task, *child;
struct list_head* iter;

module_param(inp_pid, int, 0);
MODULE_PARM_DESC(inp_pid, "The minimum PID of each process to be returned");

/* This function is called when the module is loaded. */
int simple_init(void)
{
       	printk(KERN_INFO "Loading Module\n");

	for_each_process(task) {
		if(task->pid > inp_pid){
			printk(KERN_INFO "%-25s%-15s%-10s%-10s%-10s%-10s", "PROCESS", "PID", "STATE", "PRIO", "ST_PRIO", "NORM_PRIO");
			printk(KERN_INFO "%-25s%-15d%-10d%-10d%-10d%-10d", task->comm, task->pid, task->state, task->prio, task->static_prio, task->normal_prio);
			printk(KERN_INFO "PARENT");
			printk(KERN_INFO "%-25s%-15d%-10d%-10d%-10d%-10d", task->real_parent->comm, task->real_parent->pid, task->real_parent->state, task->real_parent->prio, task->real_parent->static_prio, task->real_parent->normal_prio);
			list_for_each(iter, &task->children) {
				child = list_entry(iter, struct task_struct, children);
				printk(KERN_INFO "CHILD");
				printk(KERN_INFO "%-25s%-15d%-10d%-10d%-10d%-10d", child->comm, child->pid, child->state, child->prio, child->static_prio, child->normal_prio);
			}
			printk(KERN_INFO "\n");	
		}	
	}
	

       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");