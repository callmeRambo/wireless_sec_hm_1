#include <openssl/crypto.h>
#include <openssl/rand.h>
#include <openssl/rsa.h>

void main(int  argc,  char*  argv[]){
	char* filename = argv[1];
	
	struct  timeval start;
    struct  timeval end;
        //记录两个时间差
    unsigned  long diff;

        //第一次获取时间，即表示开始记时
    gettimeofday(&start,NULL);

        //运行自己的程序
    rsa(filename);

        //第二次获取时间，即表示结束记时
    gettimeofday(&end,NULL);

        //计算时间差，并打印
    diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
    printf("thedifference is %ld microsecond \n",diff);
}
int rsa(char* filename)
{

	unsigned char rbuff[256];
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    fscanf(fp, "%s", rbuff);

	RSA *key;
	//unsigned char rbuff[] = "RSA Clear Text";
	unsigned char wbuff[256];
	unsigned char exbuff[256];
	int num,i;
	static const char rnd_seed[] = "string to make the random number generator think it has entropy";

	printf("Clear Text: %s\n",rbuff);

	memset(wbuff,0,sizeof(wbuff));
	memset(exbuff,0,sizeof(exbuff));
	RAND_seed(rnd_seed, sizeof rnd_seed);
	if( (key = RSA_generate_key(2048,3,NULL,NULL)) == NULL)
		printf("\nerror generating key\n");

    	num = RSA_public_encrypt(sizeof(rbuff),rbuff,wbuff,key,RSA_PKCS1_PADDING);

	printf("RSA Encryption:");
	for(i=0;i<num;i++)
		printf("%x",wbuff[i]);	
	printf("\n");

    	num = RSA_private_decrypt(sizeof(wbuff),wbuff,exbuff,key,RSA_PKCS1_PADDING);

    	RSA_free(key);
}