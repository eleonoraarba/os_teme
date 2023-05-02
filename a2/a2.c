#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "a2_helper.h"
#include <stdlib.h>



int main(){
    init();
	
    info(BEGIN, 1, 0);
    pid_t  p2, p3, p4, p5, p6, p7, p8, p9;
  
     p2=fork();
 	 if(p2==0){
 	 
 	     info(BEGIN, 2, 0);
 	     
  		p6=fork();
  		  if(p6==0){
  		  	info(BEGIN, 6, 0);
  		  	info(END, 6, 0);
  		  	exit(0);
  		  }
  		waitpid(p6,0,0);
  		info(END, 2, 0);
  		exit(0);
  	}
  	
  	
     p3=fork();
  	if(p3==0){
  	
  	info(BEGIN, 3, 0);
  	
  	 	p5=fork();
  	 	if(p5==0){
  	 		info(BEGIN, 5, 0);
  		  	info(END, 5, 0);
  		  	exit(0);
  	 	}
  	 	
  		p7=fork();
  		if(p7==0){
  	 		info(BEGIN, 7, 0);
  		  	info(END, 7, 0);
  		  	exit(0);
  	 	}
  	 waitpid(p5,0,0);
  	 waitpid(p7,0,0);
  	 info(END, 3, 0);
  	 exit(0);
        }
        
     p4=fork();
     if(p4==0){
     	info(BEGIN, 4, 0);
        info(END, 4, 0);
        exit(0);
     }
     
     p8=fork();
     if(p8==0){
     	info(BEGIN, 8, 0);
        info(END, 8, 0);
        exit(0);
     }
     p9=fork();
     if(p9==0){
     	info(BEGIN, 9, 0);
        info(END, 9, 0);
        exit(0);
     }
     
    waitpid(p2,0,0);
    waitpid(p3,0,0);
    waitpid(p4,0,0);
    waitpid(p8,0,0);
    waitpid(p9,0,0);
    info(END, 1, 0);
    exit(0);
    return 0;
}
