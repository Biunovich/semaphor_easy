#include "mylib.h"
key_t key_private;
mymsgbuf rec;
int length, stat =0 ,q_private;
void *recieve_funk()
{
	while(1)
	{
		msgrcv(q_private,&rec,length,1,0);
		printf("[%s] : %s\n",rec.name ,rec.str);
		if ((strcmp(rec.str,"quit")) == 0)
		{
			stat =1;
			printf("CHAT CLOSED PRESS ENTER/n");
			break;
		}
	}
}
void main()
{
	pthread_t pth_recieve;
	key_t key_reg = ftok("/home/buin/",'r');
	key_t key_msg = ftok("/home/buin/",'m');
	key_private = ftok("/home/buin",rand()%255);
	printf("%d\n", key_msg);
	length = sizeof(mymsgbuf) - sizeof(long);
	mymsgbuf msg;
	int q_reg, q_msg;
	if ((q_reg = msgget(key_reg,IPC_CREAT | 0777)) == -1) perror("msget q_reg");
	if ((q_msg = msgget(key_msg,IPC_CREAT | 0777)) == -1) perror("msgget q_msg");
	if ((q_private = msgget(key_private,IPC_CREAT | 0777)) == -1) perror("msgget q_private");
	printf("%d\n",q_private);
	printf("ENTER NAME: ");
	scanf("%s",msg.name);
	msg.mtype =1;
	msg.key = q_private;
	msgsnd(q_reg,&msg,length,0);
	pthread_create(&pth_recieve,NULL,recieve_funk,NULL);
	while(stat == 0)
	{
		scanf("%s",msg.str);
		msgsnd(q_msg,&msg,length,0);
		if ((strcmp(msg.str,"quit")) == 0) break;
	}
	sleep(1);
	if ((msgctl(q_private,IPC_RMID,0)) == -1) perror("msgctl key_private");
	pthread_cancel(pth_recieve);
}