#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>

#define SEM_ID 6661
#define SHM_ID 6662
#define PERMS  0666

#define MSG_TYPE_EMPTY  0
#define MSG_TYPE_STRING 1
#define MSG_TYPE_FINISH 2

#define MAX_STRING 120

typedef struct {
  int type;
  char string [MAX_STRING];
} message_t;