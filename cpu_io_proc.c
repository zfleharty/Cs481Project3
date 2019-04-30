#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include "dir_que.h"
#include <dirent.h>
#define numArgs 2

void collectFilesIntoQue();
void processFilesInQue(void *vargp);
char *pathcat(const char *str1, char *str2);
void processFileDir(struct dirent *dp,char* path, struct dir_que que);

int main(int argc, char* argv[]){

  /*Check for correct number of arguments and version of program*/
  if(argc != numArgs){
    printf("incorrect number of arguments\n");
    exit(1);
  }

  /*get flag for concurrency: (0 means not concurrent, 1 means concurrent)*/
  //int flag = (int)argv[1];
  //TODO: figure out how to grab argv.. how the shit work again
  //TODO: Add branch here to run process concurrently or not

  collectFilesIntoQue();
  
  
  return 0;
}

void collectFilesIntoQue(){
  struct dir_que que = initialize_que("/nfs/student/z/zfleharty/");
  struct dir_node current_dir = pop(que); 
  struct dirent *dp; 
  int new_iteration = 0;
  do{
    
    if(new_iteration)
      { //Process the next directory if not on first iteration of loop
    	struct dir_node *temp = &current_dir;
    	current_dir = *current_dir.nextDirectory;
    	free(temp);
      }
    
    new_iteration = 1;
    DIR *dir = opendir(current_dir.Path);    
    while(dp=readdir(dir))
      {
	//TODO: check for null pointer of dp, indicates error occured
	processFileDir(dp,current_dir.Path,que);
      }
    
    closedir(dir);
  }while(current_dir.nextDirectory != NULL);
  

}

void processFileDir(struct dirent *dp,char* path, struct dir_que que){
  if(dp->d_name[0] == '.')
    { //ignore hidden directories
      return;
    }

  char *fullpath;
  switch(dp->d_type)
    {
    case DT_REG:
      // Regular file
      fullpath = pathcat(path,dp->d_name);
      printf("%s:",fullpath);
      printf(" This is a file\n");
      free(fullpath);
      break;
    case DT_DIR:
      // Directory
      fullpath = pathcat(path, dp->d_name);
      printf("%s:",fullpath);
      printf(" This is a directory\n");
      free(fullpath);
      break;
      //default: defualt action in case unhandled exception
    }

}

/*Code retrieved from https://stackoverflow.com/questions/25070751/navigating-through-files-using-dirent-h. May keep. */
char *pathcat(const char *str1, char *str2)
{
    char *res;
    size_t strlen1 = strlen(str1);
    size_t strlen2 = strlen(str2);
    int i, j;
    res = malloc((strlen1+strlen2+1)*sizeof *res);
    strcpy(res, str1);
    for (i=strlen1, j=0; ((i<(strlen1+strlen2)) && (j<strlen2)); i++, j++)
        res[i] = str2[j];
    res[strlen1+strlen2] = '\0';
    return res;
}
