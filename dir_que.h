#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <dirent.h>

 typedef struct dir_node dir_node;  
 typedef struct dir_que dir_que;  

static int number_of_elements = 0;

typedef struct dir_que
{
  dir_node* head;
  dir_node* tail;
  
}dir_que;

typedef struct dir_node
{
  char* Path;
  dir_node* nextDirectory;
}dir_node;
struct dir_que initialize_que()
{
  struct dir_que que; 
  que.head = NULL;
  que.tail = NULL;

  return que;
}

int not_empty(struct dir_que que)
{
  return number_of_elements;
}


int push(struct dir_que *que, char* path)
{
  
  struct dir_node dir = {.Path = path, .nextDirectory = NULL};
  if(not_empty(*que))
    {
      struct dir_node tail = *que->tail;
      tail.nextDirectory = &dir;
      que->tail = &dir;
      number_of_elements++;
      return 1; 
    }else
    {
      que->head = &dir;
      que->tail= &dir;
      number_of_elements++;
      return 1;
    }

  return 0; //Fail case (Directory already present maybe?)
}


struct dir_node pop(struct dir_que *que)
{

  if(not_empty(*que))
    {
      struct dir_node node = *que->head;
      &node; //Program does not work without this...... wTF?
      que->head = node.nextDirectory;
      number_of_elements--;
      return node;
    }
  //Tried to pop off of empty que error and exit.
  printf("error 3\n");
  exit(3);
}
