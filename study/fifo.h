#define SERV_FIFO "././myfifo"

typedef struct{
	char returnFifo[32];
	char writer[32];
	char data[128];
	int isWrite;
} MsgType;
