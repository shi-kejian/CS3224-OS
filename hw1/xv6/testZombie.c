/*
Author: Kejian Shi 

This code illustrates that no matter what order it runs,
zombie will be created!!! 
*/

#include "types.h"
#include "user.h"
#include "stat.h"

int
main(void)
{
   int i;
    for (i = 0; i < 4; ++i){
        if(fork() == 0){
            printf(1,"foo\n");
            exit();
        }
        else{
            wait();
            exit();
        }
    }
    return 0;
}