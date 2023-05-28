#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <dirent.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <unistd.h>

#include <sys/types.h>

#include <ctype.h>

#include <sys/wait.h>

#include <semaphore.h>

#include <pthread.h>

#include <sys/mman.h>

#define PIPE1 "RESP_PIPE_16778"
#define PIPE2 "REQ_PIPE_16778"

int main() {
    

    if (mkfifo(PIPE1, 0600) != 0) {
        printf("ERROR: Cannot create the response pipe\n");
        return -1;
    }

    int fd2 = open(PIPE2, O_RDONLY);
    if (fd2 == -1) {
        printf("ERROR: Cannot open the request pipe\n");
        return -1;
    }

    int fd1 = open(PIPE1, O_WRONLY);
    if (fd1 == -1) {
        printf("ERROR: Cannot open the response pipe\n");
        return -1;
    }

	
    write(fd1, "HELLO!", 6);
    printf("SUCCESS\n");

    while(1){
    
    char reqMsj[251];
    int cnt=0;
    int sharedMem;
    char *addr;	
    unsigned int size =0;
    	
      int fd=-1;
	while(read(fd2, &reqMsj[cnt],1)>0){
		if(reqMsj[cnt]=='!'){
			break;
		}
		cnt++;
	}
	
	reqMsj[cnt+1]='\0';
	

        if (strcmp(reqMsj, "VARIANT!") == 0) {
            char msj1[] = "VARIANT!";
            char msj2[] = "VALUE!";
            unsigned int nr = 16778;

            write(fd1, msj1, 8);
            write(fd1, msj2, 6);
            write(fd1, &nr, sizeof(unsigned int));
            
        } 
        
        
        else if(strcmp(reqMsj, "CREATE_SHM!")==0){
        	
        	read(fd2, &size, sizeof(unsigned int));
        	
		sharedMem = shm_open("/BQtZSSc",O_CREAT|O_RDWR,0664);
		
		if( sharedMem< 0  ){
			write(fd1, "CREATE_SHM!",11);
			write(fd1, "ERROR!", 6);
			
		}
		
		if (ftruncate(sharedMem, size) == -1) {
       		 	write(fd1, "CREATE_SHM!", 11);
        		write(fd1, "ERROR!", 6);
       			 
   		 }
	
	
	addr = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, sharedMem, 0);
		   
     	if(addr==(void*)-1){
     		write(fd1, "CREATE_SHM!",11);
		write(fd1, "ERROR!", 6);
		
     	}
     	
    
   	
	write(fd1, "CREATE_SHM!",11);
	write(fd1, "SUCCESS!", 8);
   	
        }
        
        else if(strcmp(reqMsj, "WRITE_TO_SHM!")==0){
        	unsigned int offset=0, value=0;
        	read(fd2, &offset, sizeof(unsigned int));
        	read(fd2, &value, sizeof(unsigned int));
        	

            if (offset < 0 || offset+3 >= 4146142) {
                write(fd1, "WRITE_TO_SHM!", 13);
                write(fd1, "ERROR!", 6);
                
            }

            unsigned int* new = (unsigned int*)(addr+offset);
            
            *new = value;

            write(fd1, "WRITE_TO_SHM!", 13);
            write(fd1, "SUCCESS!", 8);
        
        }
        
      else if (strcmp(reqMsj, "MAP_FILE!") == 0) {
      	   struct stat buf;
      	   off_t siz;
            char filename[100];
            int cnt=0;
            
         while(read(fd2, &filename[cnt],1)>0){
		if(filename[cnt]=='!'){
			break;
		}
		cnt++;
	}
	
	filename[cnt+1]='\0';

             fd = open(filename, O_RDONLY);
            if (fd == -1) {
                write(fd1, "MAP_FILE!", 9);
                write(fd1, "ERROR!", 6);
               
            }

            
            if (fstat(fd, &buf) != 0) {
            
            
                write(fd1, "MAP_FILE!", 9);
                write(fd1, "ERROR!", 6);
               
            }
            
            
            siz = buf.st_size;
            addr = mmap(NULL, siz, PROT_READ, MAP_SHARED, fd, 0);

           
            write(fd1, "MAP_FILE!", 9);
            write(fd1, "SUCCESS!", 8);
             close(fd);
        }
        
     	

         
        else if (strcmp(reqMsj, "EXIT!") == 0) {
            break;
        }
        
 }
    unlink(PIPE1);
    close(fd1);
    close(fd2);

    return 0;
}

