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

	if ((semid = semget(SEM_ID, 1, 0)) < 0) {
		sys_err("client: can not get semaphore");
	}

	if ((shmid = shmget(SHM_ID, sizeof (message_t), 0)) < 0) {
		sys_err("client: can not get shared memory segment");
	}

	if ((msg_p = (message_t *) shmat(shmid, 0, 0)) == NULL) {
		sys_err("client: shared memory attach error");
	}

	while (1) {
		scanf("%s", s);
		while (semctl(semid, 0, GETVAL, 0) || msg_p->type != MSG_TYPE_EMPTY);
		semctl(semid, 0, SETVAL, 1);

		if (strcmp(s, "end")) {
			msg_p->type = MSG_TYPE_STRING;
			strncpy(msg_p->string, s, MAX_STRING);
		} else {
			msg_p->type = MSG_TYPE_FINISH;
		};

		semctl(semid, 0, SETVAL, 0);
		if (!strcmp(s, "end")) {
			break;
		}
	}

	shmdt(msg_p);
}