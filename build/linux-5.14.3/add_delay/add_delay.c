
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/module.h>

SYSCALL_DEFINE2(add_delay, pid_t, id, unsigned long, delay){
	
	struct task_struct *task;
	int found = 0;
	//converting delay from ms to ns	
	delay*=1000000;
	if(id<0){
		return -EINVAL;
		}
	if(delay<0){
		return -EINVAL;}
	
	
	for_each_process(task){
		if(id==(long)task->pid ){
			found=1;
			task->se.added_delay+= delay;
			printk("added delay to the process %d \n" ,id);}
		}
	if(found==0){
		printk("NO such process \n");
		return -ESRCH;
	}

	return 0;
}
