#include "mylib.h"
void main()
{
	key_t key = ftok("/home/buin/msg",'m');
	int length = sizeof(mymsgbuf) - sizeof(long);
	int qid = msgget(key,IPC_CREAT | 0777);
	mymsgbuf reciv;
	char ch;
	while(ch != 'q')
	{
		msgrcv(qid,&reciv,length,1,0);
		printf("%s\n",reciv.str);
		ch = reciv.str[0];
	}
	msgctl(qid,IPC_RMID,0);
}