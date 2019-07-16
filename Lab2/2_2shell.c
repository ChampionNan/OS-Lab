#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
//error:1.some error at delete first command;2.';'is ignored, and command is not devided well 3.ls gets wrong sometimes?
int main(){
	char cmdline[256];
	memset(cmdline, '\0', 256);
	char exchange[256];
	memset(exchange, '\0', 256);
	while(1){
	printf("OSLab2->");
	gets(cmdline);
//printf("ok at line:12, judge if the input is right,the cmdline:%s\n", cmdline);
	int i,j,k,m,cmd_num, first_site,flag, parts;
	char command[30];
	int cmd_len = strlen(cmdline);
//printf("sizeof(cmdline):%d\n", cmd_len);
	cmd_num = 1;
	for(i = 0; i < cmd_len; i++){
		if(cmdline[i] == ';') cmd_num = cmd_num + 1;}
//printf("ok at line:20, num of command:%d\n", cmd_num);
	for(j = 0; j < cmd_num; j++){
		//for(m = 0; m < 10; m++)memset(cmd[m], "\0", sizeof(cmd[i]));
		//memset(argv, NULL, sizeof(argv));
		flag = 0;		//if therte is a pipe
		int flag_site = 0;	//site of pipe sign |
		parts = 0;		//if there is more than one command
		int parts_num = 0;	//certain parts inner position
		first_site = 0;		//site of ;
		memset(command, '\0', sizeof(command));
		for(m = 0; m < cmd_len; m++) 
			if(cmdline[m] == ';'){ 
				parts = 1;first_site = m;break;}
//printf("strlen cmdline:%d,site of ;:%d\n", cmd_len,first_site);
		if(parts == 1){//more than one command
			strncpy(command, cmdline, first_site);
			command[first_site] = '\0';
			strncpy(exchange, &cmdline[first_site + 1], strlen(cmdline)-first_site-1);
			exchange[strlen(cmdline)-first_site-1] = '\0';
			memset(cmdline, '\0', sizeof(cmdline));
			strcpy(cmdline, exchange);
			}
		else {strcpy(command, cmdline);command[strlen(cmdline)] = '\0';}
		//get the command
//printf("command%d:%s\n", j+1,command);
		for(m = 0; m < strlen(command); m++){
			if(command[m] == '|'){flag = 1;flag_site = m;}
			//if(command[m] == ' ')command[m] = '\0';
		}
//printf("flag:%d\n", flag);
		if(flag == 1){//pipe type
			char command1[15];
			char command2[15];
			char buf[100];
			strncpy(command1, command, flag_site);
			command1[flag_site-1] = '\0';
			strncpy(command2, &command[flag_site+2], strlen(command)-(flag_site+2));
			command2[strlen(command)-(flag_site+2)] = '\0';
//printf("command1:%s, command2:%s\n", command1, command2);
			FILE *fr = popen(command1, "r");
			FILE *fw = popen(command2, "w");
			fread(buf, sizeof(char), sizeof(buf), fr);
			fwrite(buf, sizeof(char), sizeof(buf), fw);
			pclose(fr);
			pclose(fw);
		}
		else{//usual type
			int small_parts = 0;
			char cmd[10][20] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
			//for(m = 0; m < 30; m++) cmd[m] = {'\0'};
			char *argv[10];
			for(m = 0; m < strlen(command); m++){
				if(command[m] != ' ' && command[m] != '\0')cmd[small_parts][parts_num++] = command[m];
				else if(command[m] == ' '){cmd[small_parts][parts_num] = '\0';small_parts++;parts_num = 0;}
			}
			for(m = 0; m <= small_parts; m++){
				argv[m] = cmd[m];
			}
			argv[m] = NULL;
//printf("seperste parts:1.%s,2.%s, 3.%s\n", argv[0], argv[1], argv[2]);
			argv[m] = NULL;
			pid_t child_pid = fork();
			if(child_pid == 0){
				execvp(argv[0], argv);
			}
			else{
				int status;
				status = waitpid(child_pid, &status, 0);
			}
		}
	}
}
}		
		





















	
