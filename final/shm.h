#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#define	MY_ID		0x0034
#define	SHM_KEY		(0x9000 + MY_ID)
#define	SHM_SIZE	1024
#define	SHM_MODE	(SHM_R | SHM_W | IPC_CREAT)
#define SEM1_KEY	(MY_ID + 0x0100)
#define SEM2_KEY	(MY_ID + 0x0200)
