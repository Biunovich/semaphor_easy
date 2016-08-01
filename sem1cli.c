#include "mylib.h"
void main()
{
	char str[100];
	struct sembuf sops;
	key_t key = ftok("/home/buin/sem",'a');
	int shmid = shmget(key,256,0777);
	char *shmaddr = shmat(shmid,NULL,0);
	int semid = semget(key,1,0777);
	sops.sem_num = 0;
	sops.sem_flg = 0;
	while(str[0] != 'q')
	{
		sops.sem_op = -1;
		semop(semid,&sops,1);
		strcpy(str,shmaddr);
		printf("%s\n",str);
	}
	shmdt(shmaddr);
}