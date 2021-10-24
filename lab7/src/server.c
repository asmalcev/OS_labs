#include <stdio.h>
#include <string.h>
#include "message.h"

void sys_err(char *msg) {
	puts(msg);
}

int main () {
	int semid;
	int shmid;
	message_t * msg_p;
	char s[MAX_STRING];

	if ((semid = semget(SEM_ID, 1, PERMS | IPC_CREAT)) < 0) {
		sys_err("server: can not create semaphore");
	}

	if ((shmid = shmget(SHM_ID, sizeof (message_t), PERMS | IPC_CREAT)) < 0) {
		sys_err("server: can not create shared memory segment");
	}

	if ((msg_p = (message_t *) shmat(shmid, 0, 0)) == NULL) {
		sys_err("server: shared memory attach error");
	}

	semctl(semid, 0, SETVAL, 0);
	msg_p->type = MSG_TYPE_EMPTY;

	while (1) {
		if (msg_p->type != MSG_TYPE_EMPTY) {
			if (semctl(semid, 0, GETVAL, 0)) {
				continue;
			}

			semctl(semid, 0, SETVAL, 1);
			if (msg_p->type == MSG_TYPE_STRING) {
				printf("%s\n", msg_p->string);
			}
			if (msg_p->type == MSG_TYPE_FINISH) {
				break;
			}

			msg_p->type = MSG_TYPE_EMPTY;
			semctl(semid, 0, SETVAL, 0);
		}
	}

	if (semctl(semid, 0, IPC_RMID, (struct semid_ds *) 0) < 0) {
		sys_err("server: semaphore remove error");
	}

	shmdt(msg_p);
	if (shmctl(shmid, IPC_RMID, (struct shmid_ds *) 0) < 0) {
		sys_err("server: shared memory remove error");
	}
}