# Context switch
#
#   void swtch(struct context **old, struct context *new);
# 
# Save current register context in old
# and then load register context from new.


 /** 
    *  搞清楚谁calls swich. 就知道谁是 OLD ！！！ 
    *   switch BETWEEN (from .. to and vice versa)scheduler procekernel process  
   **/


  /**
    Basically gives control to new process.
    **/


.globl swtch
swtch:
  movl 4(%esp), %eax  // ** set eax to contain the &old_context
  movl 8(%esp), %edx // set edx to contain &new_context

  # Save old callee-save registers
/**
  push things onto CURRENT( OLD ) Stack
  **/
  pushl %ebp 
  pushl %ebx
  pushl %esi
  pushl %edi

  # Switch stacks
  movl %esp, (%eax) // old stack address 


  # esp points to new stack !!
  movl %edx, %esp // Set SP to NEW STACK!!! 
  # esp points to new stack !!


  # Load new callee-save registers
  popl %edi
  popl %esi
  popl %ebx
  popl %ebp
  ret


