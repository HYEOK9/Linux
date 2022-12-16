#define	MY_ID		0x0034
#define	SHM_KEY		(0x9000 + MY_ID)
#define	SHM_SIZE	1024
#define SHM_MODE	(SHM_R | SHM_W | IPC_CREAT)
#define IPC_SEM_KEY	(0x8000 + MY_ID)
#define ISIN_SEM_KEY	(0x7000 + MY_ID)
