#include <openssl/sha.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void main(int  argc,  char*  argv[]){
	char* filename = argv[1];
	
	struct  timeval start;
    struct  timeval end;
        //记录两个时间差
    unsigned  long diff;

        //第一次获取时间，即表示开始记时
    gettimeofday(&start,NULL);

        //运行自己的程序
    sha1(filename);

        //第二次获取时间，即表示结束记时
    gettimeofday(&end,NULL);

        //计算时间差，并打印
    diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
    printf("thedifference is %ld microsecond \n",diff);
}
void sha1(char* filename)
{

	unsigned char rbuff[3000000];
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    fscanf(fp, "%s", rbuff);

	int i;
	//unsigned char rbuff[]="SHA-1 Clear Text";
	unsigned char wbuff[strlen(rbuff)];
	SHA_CTX	c;

	memset(wbuff,0,sizeof(wbuff));

	SHA1_Init(&c);
	SHA1_Update(&c,rbuff,sizeof(rbuff));
	SHA1_Final(wbuff,&c);

	printf("Clear text: %s\n",rbuff);
	printf("SHA-1 digest:");
	for (i=0;i<sizeof(wbuff);i++)
		printf("%x",wbuff[i]);
	printf("\n");
}
