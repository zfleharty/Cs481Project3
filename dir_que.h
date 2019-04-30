#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <dirent.h>

typedef struct dir_node dir_node; 
typedef struct dir_que dir_que; 

struct dir_que
{
  dir_node* head;
  dir_node* tail;
  
};
struct dir_node
{
  char* Path;
  dir_node* nextDirectory;
};

int empty(que);
struct dir_node pop(struct dir_que que);

struct dir_que initialize_que(char* startPath)
{
  struct dir_node startDirectory = {.Path = startPath, .nextDirectory = NULL};
  struct dir_que que;
  que.head = &startDirectory;
  que.tail = NULL;
  return que;
}

int empty(struct dir_que que)
{
  if(que.head == NULL)
    {
      return 0;
    }
  return 1;
}


int push(struct dir_que que,char* path)
{
  struct dir_node dir = {.Path = path, .nextDirectory = NULL};
  if(empty(que))
    {
      que.head = &dir;
      que.tail= dir.nextDirectory;
      return 1;
    }else
    {
      struct dir_node tail = *que.tail;
      tail.nextDirectory = dir;
      que.tail = &dir;
      return 1;
    }

  return 0; //Fail case (Directory already present maybe?)
}

struct dir_node pop(struct dir_que que)
{  
  if(empty(que))
    {
      return NULL;
    }
  struct dir_node head = *que.head;  
  que.head = head.nextDirectory;
  return head;
}
