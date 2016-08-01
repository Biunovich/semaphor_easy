#include "mylib.h"
void main()
{
	key_t key = ftok("/home/buin/msg",'m');
	int length = sizeof(mymsgbuf) - sizeof(long);
	int qid = msgget(key,IPC_CREAT | 0777);
	mymsgbuf sent;
	sent.mtype = 1;
	while(sent.str[0] != 'q')
	{
		printf("ENTER STRING: ");
		scanf("%s",sent.str);
		msgsnd(qid,&sent,length,0);
	}
	msgctl(qid,IPC_RMID,0);
}