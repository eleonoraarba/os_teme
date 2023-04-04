#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int permisiune(char * permissions[9] ){

  int c1=0;
  int c2=0;
  int c3=0;
  char per[3];
  int per_code;
  
  for(int i =0; i<3; i++){
  	if(strcmp(permissions[i],"r")!=0){
  		c1+=4;
  	}
  	if(strcmp(permissions[i],"w")!=0){
  		c1+=2;
  	}
  	if(strcmp(permissions[i],"e")!=0){
  		c1+=1;
  	}
  }	
  
  for(int i =3; i<6; i++){
  	if(strcmp(permissions[i],"r")!=0){
  		c2+=4;
  	}
  	if(strcmp(permissions[i],"w")!=0){
  		c2+=2;
  	}
  	if(strcmp(permissions[i],"e")!=0){
  		c2+=1;
  		
  	}
  }
  
    for(int i =6; i<9; i++){
  	if(strcmp(permissions[i],"r")!=0){
  		c3+=4;
  	}
  	if(strcmp(permissions[i],"w")!=0){
  		c3+=2;
  	}
  	if(strcmp(permissions[i],"e")!=0){
  		c3+=1;
  	}
  	
  }	
  	per[0]=c1;
  	per[1]=c2;
  	per[2]=c3;
  
  	per_code = atoi(per);
   return per_code;
  }

int list(const char* dirPath, off_t size_smaller, char *permissions[9]){

DIR *dir = NULL;

struct dirent *entry = NULL;

char fullPath[512];

struct stat statbuf;


dir = opendir(dirPath);

if(dir == NULL) {

   perror("EROOR");
   printf("%s", "Could not open directory");

   return -1	;

}

int p= permisiune(permissions);
int cnt=0;
while((entry = readdir(dir)) != 0) {

	if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {

	 	snprintf(fullPath, 512, "%s/%s", dirPath, entry->d_name);
	if(lstat(fullPath, &statbuf) == 0) {
		
	    if(S_ISREG(statbuf.st_mode)){
			
		    if((size_smaller>0 && statbuf.st_size < size_smaller && p==0) || (size_smaller==0 && p==0) || (size_smaller==0 && p!=-1) ){
		        
		        if(strcmp(permissions[0],"r")!=0){
		        	
		        	if((statbuf.st_mode & S_IRUSR)== S_IRUSR)
		        		continue;
		        	else
		        	  break;
		        
		        }
		        
		        if(strcmp(permissions[1],"w")!=0){
		        	
		        	if((statbuf.st_mode & S_IWUSR)== S_IWUSR)
		        		continue;
		        	else
		        	  break;
		        
		        }
		        
		        if(strcmp(permissions[2],"e")!=0){
		        	
		        	if((statbuf.st_mode & S_IXUSR)== S_IXUSR)
		        		continue;
		        	else
		        	  break;
		        
		        }
		        
		         if(strcmp(permissions[3],"r")!=0){
		        	
		        	if((statbuf.st_mode & S_IRGRP)== S_IRGRP)
		        		continue;
		        	else
		        	  break;
		        
		        }
		        
		        if(strcmp(permissions[4],"w")!=0){
		        	
		        	if((statbuf.st_mode & S_IWGRP)== S_IWGRP)
		        		continue;
		        	else
		        	  break;
		        
		        }
		        
		        if(strcmp(permissions[5],"e")!=0){
		        	
		        	if((statbuf.st_mode & S_IXGRP)== S_IXGRP)
		        		continue;
		        	else
		        	  break;
		        
		        }
		        
		        if(strcmp(permissions[6],"r")!=0){
		        	
		        	if((statbuf.st_mode & S_IROTH)== S_IROTH)
		        		continue;
		        	else
		        	  break;
		        
		        }
		        
		        if(strcmp(permissions[7],"w")!=0){
		        	
		        	if((statbuf.st_mode & S_IWOTH)== S_IWOTH)
		        		continue;
		        	else
		        	  break;
		        
		        }
		        
		         if(strcmp(permissions[8],"e")!=0){
		        	
		        	if((statbuf.st_mode & S_IXOTH)== S_IXOTH)
		        		continue;
		        	else
		        	  break;
		        
		        }
		   	printf("%s\n", fullPath);
		   	
		    }
		}
		
		else
		    if(p!=-1){
			
			if(strcmp(permissions[0],"r")!=0){
		        	
		        	if((statbuf.st_mode & S_IRUSR)== S_IRUSR)
		        		continue;
		        	else
		        	  break;
		        
		        }
		        
		        if(strcmp(permissions[1],"w")!=0){
		        	
		        	if((statbuf.st_mode & S_IWUSR)== S_IWUSR)
		        		continue;
		        	else
		        	
		        	  break;
		        
		        }
		        
		        if(strcmp(permissions[2],"e")!=0){
		        	
		        	if((statbuf.st_mode & S_IXUSR)== S_IXUSR)
		        		continue;
		        	else
		        	  break;
		        
		        }
		        
		         if(strcmp(permissions[3],"r")!=0){
		        	
		        	if((statbuf.st_mode & S_IRGRP)== S_IRGRP)
		        		continue;
		        	else
		        	  break;
		        
		        }
		        
		        if(strcmp(permissions[4],"w")!=0){
		        	
		        	if((statbuf.st_mode & S_IWGRP)== S_IWGRP)
		        		continue;
		        	else
		        	  break;
		        
		        }
		        
		        if(strcmp(permissions[5],"e")!=0){
		        	
		        	if((statbuf.st_mode & S_IXGRP)== S_IXGRP)
		        		continue;
		        	else
		        	  break;
		        
		        }
		        
		        if(strcmp(permissions[6],"r")!=0){
		        	
		        	if((statbuf.st_mode & S_IROTH)== S_IROTH)
		        		continue;
		        	else
		        	  break;
		        
		        }
		        
		        if(strcmp(permissions[7],"w")!=0){
		        	
		        	if((statbuf.st_mode & S_IWOTH)== S_IWOTH)
		        		continue;
		        	else
		        	  break;
		        
		        }
		        
		         if(strcmp(permissions[8],"e")!=0){
		        	
		        	if((statbuf.st_mode & S_IXOTH)== S_IXOTH)
		        		continue;
		        	else
		        	  break;
		        
		        }
		   	printf("%s\n", fullPath);
		   	cnt++;
			}
	
	}
	else{
	perror("EROARE");
	printf("%s", "invalid");
	}

}
}
if(cnt==0){
printf("%s","SUCCES");
}
closedir(dir);
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
          	if(strcmp(argv[1],"list")!=0 && strncmp(argv[2],"path=", 5)!=0) {
          		
          		int i=5;
          		int j=0;
          		while(argv[2][i] != '\0'){
          		  
          		   dir[j] = argv[2][i];
          		   i++;
          		   j++;
          		}
          	  	
                }
                char *p[9];
                p[9]="---------";
                /*for(int k=0; k<9;k++){
                	*p[k]='-';
            
                }*/
            list(dir,0, p);
    }
               
          
     
  
    return 0;
}
