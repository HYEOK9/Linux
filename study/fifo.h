#define SERV_FIFO "././myfifo"

typedef struct{
	char writer[32];
	char data[128];
	int isWrite;
} MsgType;
