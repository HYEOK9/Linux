#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* tadd(void* sum){
	int res=0;
	int n=*(int*) sum;
	for(int i=n; i<n+50; i++)
		res+=i;
	//res에 리턴값을 넘기며 종료
	pthread_exit((void*) res);
}

int main(){
	pthread_t tid1,tid2;
	int sum1=1,sum2=51;
	int res1,res2;

	//tid1 쓰레드에서 1~50 더함
	if(pthread_create(&tid1,NULL,tadd,(void*) &sum1)<0){
		perror("pthread_create1");
		exit(1);
	}
	//tid2 쓰레드에서 51~100 더함
	if(pthread_create(&tid2,NULL,tadd,(void*) &sum2)<0){
		perror("pthread_create2");
		exit(1);
	}

	//res1에 tid1의 리턴값 저장
	if(pthread_join(tid1,(void**)&res1)<0){
		perror("pthread_join1");
		exit(1);
	}

	//res2에 tid2의 리턴값 저장
	if(pthread_join(tid2,(void**)&res2)<0){
		perror("pthread_join2");
		exit(1);
	}
	printf("%d\n",res1+res2);
}
