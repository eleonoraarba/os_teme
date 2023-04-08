#include <stdio.h>

#include <string.h>

#include <sys/types.h>

#include <dirent.h>

#include <sys/stat.h>

#include <unistd.h>

#include <stdlib.h>

#include <fcntl.h>


int list(const char* dirPath, off_t size_smaller, char *permissions, int r, int success,int Flag){

DIR *dir = NULL;

struct dirent *entry = NULL;

char fullPath[512];

struct stat statbuf;


dir = opendir(dirPath);

if(dir == NULL) {

   printf("ERROR");

   perror("Could not open directory");

   return -1	;
}


if(r==0){
printf("SUCCESS\n");



	while((entry = readdir(dir)) != 0) {



		if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {

	 	   snprintf(fullPath, 512, "%s/%s", dirPath, entry->d_name);
	 	

			if(lstat(fullPath, &statbuf) == 0) {

		            if(Flag ==1 ){

	    			if(S_ISREG(statbuf.st_mode)){
	    			              
	    					if(size_smaller>statbuf.st_size ){
	    						printf("%s\n", fullPath);
	    					}
	    				}
	    			else{
	    				//printf("%s\n", fullPath);
	    			}

			  }

			   else if (Flag==0){//caz fara flag uri print orice
		   			printf("%s\n", fullPath);	
		   		 }
		   	int ok=0;	 
		  if (Flag==2){
		   	 
		   	  
		   	if(permissions[0] == 'r'){
		        	if((statbuf.st_mode & S_IRUSR)!= S_IRUSR)
		        		
		        	
		        	        ok=1;
		        	  
		             }
		                
		     
		        if(permissions[1] == 'w'){
		        	if((statbuf.st_mode & S_IWUSR)!= S_IWUSR)
		        	 
		        	
		        	   ok=1;
                        }
                     
		        if(permissions[2] == 'e'){
		        	if((statbuf.st_mode & S_IXUSR)!= S_IXUSR)
		        	  
		        	
		        	    ok=1;
		        }
 
		         if(permissions[3] == 'r'){
		        	if((statbuf.st_mode & S_IRGRP)!= S_IRGRP)
		        	   
		        	
		        	 ok=1;
		        }
 
		        if(permissions[4] == 'w'){
		        	if((statbuf.st_mode & S_IWGRP)!= S_IWGRP)
		        		
		        	
		        	  ok=1;
		        }
		         
		        if(permissions[5] == 'e'){
				if((statbuf.st_mode & S_IXGRP)!= S_IXGRP)
		        	  
		        	
		        	   ok=1;
		        }

		        if(permissions[6] == 'r'){
		            if((statbuf.st_mode & S_IROTH)!= S_IROTH)
		        	
		        	
		        	   ok=1;
		        }

		        if(permissions[7] =='w'){
		        	if((statbuf.st_mode & S_IWOTH)!= S_IWOTH)
		        	  
		        	
		        	  ok=1;
		        }

		         if(permissions[8] == 'e'){
		        	if((statbuf.st_mode & S_IXOTH)!= S_IXOTH)
		           	 
		        	   ok=1;
		        }

		  
		   
		   if(ok==0){
		       
		   	printf("%s\n", fullPath);
		   	}
		   }
		}

		         else{

				perror("ERROR");

				printf( "invalid");

				}

  		 }

	}

}
else	{

	if(success==0){

		printf("SUCCESS\n");

		success = 1;
	}

	while((entry = readdir(dir)) != 0) {



		if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {



	 		snprintf(fullPath, 512, "%s/%s", dirPath, entry->d_name);

			if(lstat(fullPath, &statbuf) == 0) {

	
                              if(Flag==1){
	     			if(S_ISREG(statbuf.st_mode)){
                                    
                                      	if(size_smaller>statbuf.st_size){
						printf("%s\n", fullPath);
					}
				}
				    
		
	 			 else  if(S_ISDIR(statbuf.st_mode)){

	
		       			 //printf("%s\n", fullPath);

	    				list(fullPath,size_smaller ,permissions, 1, success, Flag);

	    			}
	
	  		 }
	  		 
	  		 else if (Flag==0){
	  		 	if(S_ISREG(statbuf.st_mode)){
                                   
					printf("%s\n", fullPath);
					
				}
				    
	 			 else  if(S_ISDIR(statbuf.st_mode)){

	
		       			 printf("%s\n", fullPath);

	    				list(fullPath,size_smaller ,permissions, 1, success, Flag);

	    			}
	  		 }
	  		
	  		 else if(Flag==2){
	  		 int ok=0;
	  		if(S_ISREG(statbuf.st_mode)){
	  		
	  		 if(permissions[0] == 'r'){
		        	if((statbuf.st_mode & S_IRUSR)!= S_IRUSR)
		        	        ok=1;	
		             } else {
		             	if((statbuf.st_mode & S_IRUSR)== S_IRUSR)
		        	        ok=1;
		             }
		               
		        if(permissions[1] == 'w'){
		        	if((statbuf.st_mode & S_IWUSR)!= S_IWUSR)
		        	 
		        	   ok=1;
                        }
                        else {
		             	if((statbuf.st_mode & S_IWUSR)== S_IWUSR)
		        	        ok=1;
		             }
                     
		        if(permissions[2] == 'e'){
		        	if((statbuf.st_mode & S_IXUSR)!= S_IXUSR)
		        	  
		        	    ok=1;
		        }
		        else {
		             	if((statbuf.st_mode & S_IXUSR)== S_IXUSR)
		        	        ok=1;
		             }
 
		         if(permissions[3] == 'r'){
		        	if((statbuf.st_mode & S_IRGRP)!= S_IRGRP)
		        	   
		        	 ok=1;
		        }
		        else {
		             	if((statbuf.st_mode & S_IRGRP)== S_IRGRP)
		        	        ok=1;
		             }
   
		        if(permissions[4] == 'w'){
		        	if((statbuf.st_mode & S_IWGRP)!= S_IWGRP)
		        		
		        	  ok=1;
		        }
		        else {
		             	if((statbuf.st_mode & S_IWGRP)== S_IWGRP)
		        	        ok=1;
		             }
   
		         
		        if(permissions[5] == 'e'){
				if((statbuf.st_mode & S_IXGRP)!= S_IXGRP)
		        	  
		        	   ok=1;
		        }
		        else {
		             	if((statbuf.st_mode & S_IXGRP)== S_IXGRP)
		        	        ok=1;
		             }

		        if(permissions[6] == 'r'){
		            if((statbuf.st_mode & S_IROTH)!= S_IROTH)
		        	
		        	   ok=1;
		        }
                        else {
		             	if((statbuf.st_mode & S_IROTH)== S_IROTH)
		        	        ok=1;
		             }
		        if(permissions[7] =='w'){
		        	if((statbuf.st_mode & S_IWOTH)!= S_IWOTH)
		        	  
		        	  ok=1;
		        }
                           else {
		             	if((statbuf.st_mode & S_IWOTH)== S_IWOTH)
		        	        ok=1;
		             }
		         if(permissions[8] == 'e'){
		        	if((statbuf.st_mode & S_IXOTH)!= S_IXOTH)
		           	 
		        	   ok=1;
		        }
		        
		        else {
		             	if((statbuf.st_mode & S_IXOTH)== S_IXOTH)
		        	        ok=1;
		             }

		   		if(ok==0){
		      			
		   				printf("%s\n", fullPath);
		   			}
		   	}
		   		
		   	
		   	else if(S_ISDIR(statbuf.st_mode)){ 
		   		 
		   	 
		   	  if(permissions[0] == 'r'){
		        	if((statbuf.st_mode & S_IRUSR)!= S_IRUSR)
		        		
		        	        ok=1;
		        	 
		             }
		                
		     
		        if(permissions[1] == 'w'){
		        	if((statbuf.st_mode & S_IWUSR)!= S_IWUSR)
		        	 
		        	   ok=1;
                        }
                     
		        if(permissions[2] == 'e'){
		        	if((statbuf.st_mode & S_IXUSR)!= S_IXUSR)
		        	  
		        	    ok=1;
		        }
 
		         if(permissions[3] == 'r'){
		        	if((statbuf.st_mode & S_IRGRP)!= S_IRGRP)
		        	
		        	 ok=1;
		        }
 
		        if(permissions[4] == 'w'){
		        	if((statbuf.st_mode & S_IWGRP)!= S_IWGRP)
		        	
		        	  ok=1;
		        }
		         
		        if(permissions[5] == 'e'){
				if((statbuf.st_mode & S_IXGRP)!= S_IXGRP)
		        	  
		        	   ok=1;
		        }

		        if(permissions[6] == 'r'){
		            if((statbuf.st_mode & S_IROTH)!= S_IROTH)
		        	
		        	   ok=1;
		        }

		        if(permissions[7] =='w'){
		        	if((statbuf.st_mode & S_IWOTH)!= S_IWOTH)
		        	  
		        	  ok=1;
		        }

		         if(permissions[8] == 'e'){
		        	if((statbuf.st_mode & S_IXOTH)!= S_IXOTH)
		           	 
		        	   ok=1;
		        }
		              
		              if(ok==0){

		   		        	 printf("%s\n", fullPath);

		   				list(fullPath,size_smaller ,permissions, 1, success, Flag);}
		   			}
		   			
		   		  }
	  	  	 }	
	  		 
                  
                   }
	    

	}
   }


closedir(dir);

return 0;

}

typedef struct  S_Header
{
    char s_name[19];
    int s_type;
    int s_offset;
    int s_size;
} S_Header;



int parse(const char* dirPath)
{
char magic[5];
int fd1=-1, no_of_sections=0, version=0, header_size=0;
   
fd1=open(dirPath,O_RDONLY);
if(fd1 == -1)
  {   
   perror("could not open input file\n");
   printf("ERROR\n");
    return -1;
   }
   
//citirile
lseek(fd1, 0, SEEK_SET);
read(fd1, magic,4);
magic[4]='\0';
read(fd1, &header_size,2);
read(fd1,&version, 2);
read(fd1, &no_of_sections,1);

  if(strcmp(magic,"zL0R")!=0)
  {
        printf("ERROR\nwrong magic");
        return -1;
  }
  
  if(42>version || version>65)
  {
        printf("ERROR\nwrong version");
        return -1;
  }
  
  if(2>no_of_sections || no_of_sections>16)
  {
        printf("ERROR\nwrong sect_nr");
        return -1;
  }
    S_Header *struct_header=calloc(no_of_sections,sizeof(S_Header));
 for(int i=0; i<no_of_sections; i++)
    {
     char name[19];
     int type=0, offset=0, size=0;
      
     read(fd1,&name,18);
     name[18] = '\0';
     read(fd1,&type,2);
     read(fd1,&offset,4);
     read(fd1,&size,4);
        
//printf("%s\n",magic);

//printf("%d\n",header_size);

//printf("%d\n",version);

//printf("%d\n",no_of_sections);

  if(type!=39 && type!=82 && type!=35 && type!=86 && type!= 36)
   {
      printf("ERROR\nwrong sect_types");
      close(fd1);
      free(struct_header);
      return -1;
    }
        struct_header[i].s_name[0]='\0';
        strcpy(struct_header[i].s_name,name);
        struct_header[i].s_type = type;
        struct_header[i].s_offset = offset;
        struct_header[i].s_size = size;
    }
    printf("SUCCESS\n");
    printf("version=%d\n",version);
    printf("nr_sections=%d\n", no_of_sections);
    for(int i=0; i<no_of_sections; i++)
    {
        printf("section%d: %s %d %d\n", i+1, struct_header[i].s_name,struct_header[i].s_type, struct_header[i].s_size);
    }


    close(fd1);
    free(struct_header);
    return 0;
}




int extract(const char *dirPath, int section, int line){
	int fd1=-1;
	int no_of_sections=0;

	fd1=open(dirPath,O_RDONLY);
	if(fd1 == -1) { 
   		printf("ERROR\ninvalid file");
   		return -1;
   	}
   
	lseek(fd1,8,SEEK_SET);
 	read(fd1, &no_of_sections,1);
 
 	if(section>no_of_sections){
  		printf("ERROR\ninvalid section");
   		close(fd1);
   	 	return -1;
	}
 
 
 	 S_Header *struct_header=calloc(no_of_sections,sizeof(S_Header));
  	for(int i=0;i <no_of_sections; i++){
  
  		char name[19];
    	 	int type=0, offset=0, size=0;
      
    	 read(fd1,&name,18);
   	  name[18] = '\0';
    	 read(fd1,&type,2);
    	 read(fd1,&offset,4);
    	 read(fd1,&size,4);
     
        struct_header[i].s_name[0]='\0';
        strcpy(struct_header[i].s_name,name);
        struct_header[i].s_type = type;
        struct_header[i].s_offset = offset;
        struct_header[i].s_size = size;
  	}
   
 	//char line[];
 	char c;
 	int nr_linii=1;
 	int sec_size=0;
 	
 	lseek(fd1,  struct_header[section-1].s_offset, SEEK_SET);
 	  
 	   	      
 	   	      int Flag=0;
 	   	      while(1){
 	   	      	if(line != 1) {
 	   	      	 sec_size++;
 	   	      	  if(sec_size>struct_header[section-1].s_size){
 	   	      	  	break;
 	   	      	  }
 	   	      	  
 	   	      	 read(fd1, &c, 1);
 	   	      	 
 	   	      	 if(c=='\n'){
 	   	      	 	nr_linii++;
 	   	      	 	
 	   	      	 	if(nr_linii==line){
 	   	      	   		Flag=1;
 	   	      	 		break;
 	   	      	 	}
 	   	      	 }
 	   	      	} else {
 	   	      		Flag = 1;
 	   	      		break;
 	   	      	} 
 	   	     }
 	   	      
 	   	     char aux;
 	   	      if(Flag==0){
 	   	        printf("ERROR\ninvalid line");
 	   	      }
 	   	      else{
 	   	      	printf("SUCCESS\n");
 	   	      	
 	   	      	while(1) {
 	   	      		read(fd1,&aux, 1);
 	   	      		if(aux!='\n'){
 	   	      			printf("%c", aux);
 	   	      		} else {
 	   	      			break;
 	   	      		}
 	   	      	
 	   	      	}
 	   	      }
   
return 0;

}

int success = 0;
int findall(const char *dirPath){
DIR *dir = NULL;

struct dirent *entry = NULL;
char fullPath[512];
printf("muie");
struct stat statbuf;
int no_of_sections;
dir=opendir(dirPath);
if(dir == NULL) {

   printf("ERROR\n");

   perror("invalid directory path");

   return -1	;
}
   	while((entry = readdir(dir)) != 0) {



		if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {



	 		snprintf(fullPath, 512, "%s/%s", dirPath, entry->d_name);

			if(lstat(fullPath, &statbuf) == 0) {

	     			if(S_ISREG(statbuf.st_mode)){
	     			
	int fd1 = -1;
	fd1=open(fullPath,O_RDONLY);
	if(fd1 == -1) { 
   		printf("ERROR\ninvalid file");
   		return -1;
   	}
	
	lseek(fd1,8,SEEK_SET);
 	read(fd1, &no_of_sections,1);
 
 	 S_Header *struct_header=calloc(no_of_sections,sizeof(S_Header));
  	for(int i=0;i <no_of_sections; i++){
  
  		char name[19];
    	 	int type=0, offset=0, size=0;
      
    	 read(fd1,&name,18);
   	  name[18] = '\0';
    	 read(fd1,&type,2);
    	 read(fd1,&offset,4);
    	 read(fd1,&size,4);
     
        struct_header[i].s_name[0]='\0';
        strcpy(struct_header[i].s_name,name);
        struct_header[i].s_type = type;
        struct_header[i].s_offset = offset;
        struct_header[i].s_size = size;
  	}
 	
 	
 	for(int i = 0; i < no_of_sections; i++) {
 		int nr_linii=1;
 		int sec_size=0;
 		char c;
 		
 		lseek(fd1, struct_header[i].s_offset, SEEK_SET);
 	
 		while(sec_size<struct_header[i].s_size){
 	   	      	 sec_size++;
 	   	      	  
 	   	      	 read(fd1, &c, 1);
 	   	      	 
 	   	      	 if(c=='\n'){
 	   	      	 	nr_linii++;
 	   	      	 }
 	   	     }
 	   	if(c=='\n') {
 	   		nr_linii--;
 	   	}
 	   	
 	   	if(nr_linii > 13) {
 	   	if(success == 0) {
 	   		printf("SUCCESS\n");
 	   		success = 1;
 	   	}
 	   		printf("%s\n", fullPath);
 	   		break;
 	   	}
 	}
 	} else {
 		findall(fullPath);
 	}
 	}
 	}
 	}
 return 0;
}

int main(int argc, char **argv){

    if(argc == 2){

        if(strcmp(argv[1], "variant") == 0){

            printf("16778\n");

        }

     }

     if(argc==3){

         char dir[512];

          	if(strcmp(argv[1],"list")==0 && strncmp(argv[2],"path=", 5)==0) {

          		int i=5;

          		int j=0;

          		while(argv[2][i] != '\0'){

          		   dir[j] = argv[2][i];

          		   i++;

          		   j++;

          		}

   			dir[j] = '\0';       		

          	char p[10] = {'-','-','-','-','-','-','-','-','-','\0'};

           	 list(dir,0, p, 0, 0, 0);

                }

                

    		  else  if(strcmp(argv[2],"list")==0 && strncmp(argv[1],"path=", 5)==0) {

          		
          		int i=5;

          		int j=0;

          		while(argv[2][i] != '\0'){

          		  

          		   dir[j] = argv[2][i];

          		   i++;

          		   j++;

          		}
			
			dir[j] = '\0'; 
			
          		char p[10] = {'-','-','-','-','-','-','-','-','-','\0'};

                
           			 list(dir,0, p,0,0,0);	

          	  	

    		}
    		
    			else if(strcmp(argv[1],"parse")==0 &&  strncmp(argv[2],"path=", 5)==0){
          			int i=5;
          		       int j=0;

          			while(argv[2][i] != '\0'){

          		  	 dir[j] = argv[2][i];

          		  	 	i++;

          		   		j++;

          	
          			}
          			
          			dir[j] = '\0';
          			
          		parse(dir);

          		}
          	   
          	   else if(strcmp(argv[1], "findall")==0 && strncmp(argv[2],"path=", 5)==0){
          	   	int i=5;
          		       int j=0;

          			while(argv[2][i] != '\0'){

          		  	 dir[j] = argv[2][i];

          		  	 	i++;

          		   		j++;

          	
          			}
          			
          			dir[j] = '\0';
          			
          		findall(dir);
          	   }

    }

           

           if(argc==4){
           	
		 int Flag=0;
           	  char s_size[100000];

            	  int r=0;

                  int size=0;

                  char dir[512];

                  char p[10] = {'-','-','-','-','-','-','-','-','-','\0'};

                  for(int i=1; i<argc;i++){

                  	if(strcmp(argv[i],"list")==0){

                  	
                  	}

                  
                   	if(strcmp(argv[i],"recursive")==0){

                   		r=1;
                  	}

                  	
                   	if(strncmp(argv[i],"path=", 5)==0){

                   		int k=5;

          			int j=0;

          			while(argv[i][k] != '\0'){

          		  
          		   		dir[j] = argv[i][k];

          		   		k++;

          		   		j++;

          			}
          			
          			dir[j] = '\0';

                   	}

                   	

                   	if(strncmp(argv[i], "size_smaller=", 13)==0){

                   		int k=13;

          			int j=0;

          			while(argv[i][k] != '\0'){

          		   		s_size[j] = argv[i][k];

          		   		k++;

          		   		j++;
			 	
				
          			}
          			s_size[j] = '\0';
				Flag=1;	
          			size=atoi(s_size);
				
                   	}

                   	
                   	if(strncmp(argv[i], "permissions=", 12)==0){
				Flag=2;	
                   		int k=12;

          			int j=0;

          			while(argv[i][k] != '\0'){

          		   		p[j] = argv[i][k];

          		   		k++;

          		   		j++;

          			}
          		
          		 
				
                   	}

                  }
			
                  

                 	if(r!=1){

                 		list(dir,size ,p, 0,0,Flag);

                 	}

                 	else{

                 		list(dir,size ,p, 1,0,Flag);

                 	}
       
    }

     

         if(argc==5){
                  int extr=0;
		  int Flag=0;
           	  char s_size[10000];

            	  int r=0;

                  int cnt=0;

                  int size=0;

                  char dir[512];

                  char p[10] = {'-','-','-','-','-','-','-','-','-','\0'};
	          char s_section[2];
	          int section=0;
	          char s_line[100000];
	          int line=0;
                  for(int i=1; i<argc;i++){

                  	if(strcmp(argv[i],"list")==0){

                  		cnt+=1;

                  	}

                   	

                   	if(strcmp(argv[i],"recursive")==0){

                   		r=1;
	

                  	}

                  	

                   	if(strncmp(argv[i],"path=", 5)==0){

                   		int k=5;

          			int j=0;

          			while(argv[i][k] != '\0'){

          		   		dir[j] = argv[i][k];

          		   		k++;

          		   		j++;

          			}
          			dir[j] = '\0';

                   	}

                   	

                   	if(strncmp(argv[i], "size_smaller=", 13)==0){

                   		int k=13;

          			int j=0;

          			while(argv[i][k] != '\0'){

          		  

          		   		s_size[j] = argv[i][k];

          		   		k++;

          		   		j++;

          			}
          			s_size[j] = '\0';
				Flag=1;	
          			size=atoi(s_size);

                   	}

                   	

                   	if(strncmp(argv[i], "permissions=", 12)==0){

                   		int k=12;

          			int j=0;

          			while(argv[i][k] != '\0'){

          		   		p[j] = argv[i][k];

          		   		k++;

          		   		j++;

          			}
				Flag=2;
                   	}
                   	
                   	if(strcmp(argv[i], "extract")==0){
                   		extr=1;
                   	}
		        
		        if(strncmp(argv[i], "section=",8)==0){
		                 int k=8;

          			int j=0;

          			while(argv[i][k] != '\0'){

          		   		s_section[j] = argv[i][k];

          		   		k++;

          		   		j++;

                   		}
                   	s_section[j]='\0';
                   	section=atoi(s_section);
                   	}
                   	
                   	if(strncmp(argv[i], "line=",5)==0){
                   		 int k=5;

          			int j=0;

          			while(argv[i][k] != '\0'){

          		   		s_line[j] = argv[i][k];

          		   		k++;

          		   		j++;
                   	}
                   	s_line[j]='\0';
		        line=atoi(s_line);
                  }
                  
		}	
			if(extr==1){
                 		
                 		extract(dir, section,line);
                 	
                 	}
                 	
                 	if(r==0){
                 	if(extr!=1){

                 		list(dir,size ,p, 0, 0,Flag);
                 		}

                 	}

                 	else{

                 		list(dir,size ,p, 1, 0,Flag);

                 	}
                 	
                 	

    }

    return 0;

}

