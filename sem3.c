#include "mylib.h"
int cli_num = 0,length ,q_reg;
key_t key_reg,*key_cli;
mymsgbuf keybuf_cli;
void *funk_reg()
{
	while(1)
	{
		msgrcv(q_reg,&keybuf_cli,length,1,0);
		key_cli[cli_num++] = keybuf_cli.key;
	}
}
void main()
{
	pthread_t pth_reg;
	key_cli = calloc(sizeof(key_t),100);
	key_reg = ftok("/home/buin/",'r');
	key_t key_msg = ftok("/home/buin/",'m');
	length = sizeof(mymsgbuf) - sizeof(long);
	mymsgbuf msg;
	int q_msg, i;
	if ((q_reg = msgget(key_reg,IPC_CREAT | 0777)) == -1) perror("msget q_reg");
	if ((q_msg = msgget(key_msg,IPC_CREAT | 0777)) == -1) perror("msgget q_msg");
	pthread_create(&pth_reg, NULL, funk_reg, NULL);
	while(1)
	{
		msgrcv(q_msg,&msg,length,1,0);
		if (strcmp(msg.str,"quit") == 0)
		{ 
			break;
		}
		for (i=0;i<cli_num;i++)
		{
			msgsnd(key_cli[i],&msg,length,0);
		}
		printf("%d\n",key_cli[0] );
	}
	if ((msgctl(key_reg,IPC_RMID,0)) == -1) perror("msgctl key_reg");
	if ((msgctl(key_msg,IPC_RMID,0)) == -1) perror("msgctl key_msg");
	pthread_cancel(pth_reg);
}