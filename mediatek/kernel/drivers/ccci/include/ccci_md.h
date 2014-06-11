/*****************************************************************************
 *
 * Filename:
 * ---------
 *   ccci_md.h
 *
 * Project:
 * --------
 *   Andes
 *
 * Description:
 * ------------
 *   MT65XX Modem initialization and handshake header file
 *
 ****************************************************************************/

#ifndef __CCCI_MD_H__
#define __CCCI_MD_H__

#include <ccci.h>

/*
 * define constants
 */


#define CCCI_SYSFS_MD_INIT "modem"
#define CCCI_SYSFS_MD_BOOT_ATTR "boot"
#define CCCI_PCM_SMEM_SIZE (16 * 1024)
#define MD_BOOT_CMD_CHAR '0'
#define NORMAL_BOOT_ID 0
#define META_BOOT_ID 1
#define MD_RUNTIME_ADDR (CCIF_BASE + 0x0140)
#define UART_MAX_PORT_NUM 8
#define SLEEP_CON 0xF0001204
#define CCCI_CURRENT_VERSION 0x00000923
#define MD_EX_LOG_SIZE 512
#define MD_IMG_DUMP_SIZE (1<<8)
#define DSP_IMG_DUMP_SIZE (1<<9)
#define CCCI_TTY_BUFF_NR UART_MAX_PORT_NUM
#define NR_CCCI_RESET_USER 10
#define NR_CCCI_RESET_USER_NAME 16


#define CCCI_MD_EXCEPTION   0x1
#define CCCI_MD_RESET     0x2
#define CCCI_MD_BOOTUP    0x3

#define LOCK_MD_SLP 0x1
#define UNLOCK_MD_SLP 0x0
/*-----------------------------------------------------------*/
/* Device ID assignment */
#define CCCI_TTY_DEV_MAJOR		(169)	//(0: Modem; 1: Meta; 2:IPC)


enum { 
	MD_BOOT_STAGE_0 = 0, 
	MD_BOOT_STAGE_1 = 1, 
	MD_BOOT_STAGE_2 = 2,
	MD_BOOT_STAGE_EXCEPTION = 3
};

enum { 
	MD_INIT_START_BOOT = 0x00000000, 
	MD_INIT_CHK_ID = 0x5555FFFF,
	MD_EX = 0x00000004, 
	MD_EX_CHK_ID = 0x45584350,
	MD_EX_REC_OK = 0x00000006, 
	MD_EX_REC_OK_CHK_ID = 0x45524543, 
	MD_EX_RESUME_CHK_ID = 0x7, 
	CCCI_DRV_VER_ERROR = 0x5,
	//MD_DORMANT_NOTIFY = 0x100,
	//MD_SLP_REQUEST = 0x101,
	MD_WDT_MONITOR = 0x1000
};

enum { 
	ER_MB_START_CMD = -1, 
	ER_MB_CHK_ID = -2, 
	ER_MB_BOOT_READY = -3, 
	ER_MB_UNKNOW_STAGE = -4 
};

enum { 
	MD_EX_TYPE_INVALID = 0, 
	MD_EX_TYPE_UNDEF = 1, 
	MD_EX_TYPE_SWI = 2,
	MD_EX_TYPE_PREF_ABT = 3, 
	MD_EX_TYPE_DATA_ABT = 4, 
	MD_EX_TYPE_ASSERT = 5,
	MD_EX_TYPE_FATALERR_TASK = 6, 
	MD_EX_TYPE_FATALERR_BUF = 7,
	MD_EX_TYPE_LOCKUP = 8, 
	MD_EX_TYPE_ASSERT_DUMP = 9,
	MD_EX_TYPE_ASSERT_FAIL = 10,
	DSP_EX_TYPE_ASSERT = 11,
	DSP_EX_TYPE_EXCEPTION = 12,
	DSP_EX_FATAL_ERROR = 13,
	NUM_EXCEPTION
};
#define MD_EX_TYPE_EMI_CHECK 99



#ifdef AP_MD_EINT_SHARE_DATA
enum { 
	CCCI_EXCH_CORE_AWAKEN = 0, 
	CCCI_EXCH_CORE_SLEEP = 1, 
	CCCI_EXCH_CORE_SLUMBER = 2 
};
#endif

/* CCCI system message */
enum { 
	CCCI_SYS_MSG_RESET_MD = 0x20100406 
};

/* MD Message, this is for user space deamon use */
enum {
	CCCI_MD_MSG_BOOT_READY			= 0xFAF50001,
	CCCI_MD_MSG_BOOT_UP				= 0xFAF50002,
	CCCI_MD_MSG_EXCEPTION			= 0xFAF50003,
	CCCI_MD_MSG_RESET				= 0xFAF50004,
	CCCI_MD_MSG_RESET_RETRY			= 0xFAF50005,
	CCCI_MD_MSG_RESET_REQUEST		= 0xFAF50006,
	CCCI_MD_MSG_BOOT_TIMEOUT		= 0xFAF50007,
	CCCI_MD_MSG_STOP_MD_REQUEST		= 0xFAF50008,
	CCCI_MD_MSG_START_MD_REQUEST	= 0xFAF50009,
};

/* MD Status, this is for user space deamon use */
enum {
	CCCI_MD_STA_BOOT_READY = 0,
	CCCI_MD_STA_BOOT_UP = 1,
	CCCI_MD_STA_RESET = 2,
};

#if 0
/* MODEM MAUI SW ASSERT LOG */
struct modem_assert_log
{
    char ex_type;
    char ex_nvram;
    short ex_serial;
    char data1[212];
    char filename[24];
    int linenumber;
    char data2[268];
};

/* MODEM MAUI SW FATAL ERROR LOG */
struct modem_fatalerr_log
{
    char ex_type;
    char ex_nvram;
    short ex_serial;
    char data1[212];
    int err_code1;
    int err_code2;
    char data2[288];
};
#endif

struct cores_sleep_info
{
    unsigned char AP_Sleep;
    unsigned char padding1[3];
    unsigned int RTC_AP_WakeUp;
    unsigned int AP_SettleTime; /* clock settle duration */
    unsigned char MD_Sleep;
    unsigned char padding2[3];
    unsigned int RTC_MD_WakeUp;
    unsigned int RTC_MD_Settle_OK;  /* clock settle done time */
};

/* MODEM MAUI Exception header (4 bytes)*/
typedef struct _exception_record_header_t
{
	unsigned char  ex_type;
	unsigned char  ex_nvram;
	unsigned short ex_serial_num;
}EX_HEADER_T;

/* MODEM MAUI Environment information (164 bytes) */
typedef struct _ex_environment_info_t
{
	unsigned char  boot_mode;
	unsigned char reserved1[8];
	unsigned char execution_unit[8];
	unsigned char reserved2[147];
}EX_ENVINFO_T;

/* MODEM MAUI Special for fatal error (8 bytes)*/
typedef struct _ex_fatalerror_code_t
{
	unsigned int code1;
	unsigned int code2;
}EX_FATALERR_CODE_T;

/* MODEM MAUI fatal error (296 bytes)*/
typedef struct _ex_fatalerror_t
{
	EX_FATALERR_CODE_T error_code;
	unsigned char reserved1[288];
}EX_FATALERR_T;

/* MODEM MAUI Assert fail (296 bytes)*/
typedef struct _ex_assert_fail_t
{
	unsigned char filename[24];
	unsigned int  linenumber;
	unsigned int  parameters[3];
	unsigned char reserved1[256];
}EX_ASSERTFAIL_T;

/* MODEM MAUI Globally exported data structure (300 bytes) */
typedef union
{
	EX_FATALERR_T fatalerr;
	EX_ASSERTFAIL_T assert;
}EX_CONTENT_T;

/* MODEM MAUI Standard structure of an exception log ( */
typedef struct _ex_exception_log_t
{
	EX_HEADER_T	header;
	unsigned char	reserved1[12];
	EX_ENVINFO_T	envinfo;
	unsigned char	reserved2[36];
	EX_CONTENT_T	content;
}EX_LOG_T;

struct core_eint_config
{
    unsigned char eint_no; 
    unsigned char Sensitivity;
    unsigned char ACT_Polarity;
    unsigned char Dbounce_En;
    unsigned int Dbounce_ms;
};

struct ccci_cores_exch_data
{
    struct cores_sleep_info sleep_info;
    unsigned int report_os_tick;    /* report OS Tick Periodic in second unit */
                                    /* ( 0 = disable ) */
    unsigned int nr_eint_config;
    unsigned int eint_config_offset;    /* offset from SysShareMemBase for struct coreeint_config */
};

#define CCCI_SYS_SMEM_SIZE sizeof(struct ccci_cores_exch_data)

struct ccci_reset_sta
{
    int is_allocate;
    int is_reset;
    char name[NR_CCCI_RESET_USER_NAME];
};

struct modem_runtime_t
{
    int Prefix;             // "CCIF"
    int Platform_L;       // Hardware Platform String ex: "TK6516E0"
    int Platform_H;
    int DriverVersion;      // 0x00000923 since W09.23
    int BootChannel;        // Channel to ACK AP with boot ready
    int BootingStartID;     // MD is booting. NORMAL_BOOT_ID or META_BOOT_ID 
    int BootAttributes;     // Attributes passing from AP to MD Booting
    int BootReadyID;        // MD response ID if boot successful and ready
    int MdlogShareMemBase;
    int MdlogShareMemSize; 
    int PcmShareMemBase;
    int PcmShareMemSize;
    int UartPortNum;
    int UartShareMemBase[UART_MAX_PORT_NUM];
    int UartShareMemSize[UART_MAX_PORT_NUM];    
    int FileShareMemBase;
    int FileShareMemSize;
    int RpcShareMemBase;
    int RpcShareMemSize;	
    int PmicShareMemBase;
    int PmicShareMemSize;
    int ExceShareMemBase;
    int ExceShareMemSize;   // 512 Bytes Required 
    int SysShareMemBase;
    int SysShareMemSize;
    int IPCShareMemBase;
    int IPCShareMemSize;
    int CheckSum;
    int Postfix;        //"CCIF" 
//int RpcShareMemBase;
 // int RpcShareMemSize;	
}; 


typedef struct _MD_CALL_BACK_QUEUE {
	void (*call)(struct _MD_CALL_BACK_QUEUE*,unsigned long data);	
	struct _MD_CALL_BACK_QUEUE *next;
}MD_CALL_BACK_QUEUE;

typedef struct {
	spinlock_t lock;
	MD_CALL_BACK_QUEUE *next;
}MD_CALL_BACK_HEAD_T;


#if 0
struct IMG_CHECK_INFO{
	char *product_ver;	/* debug/release/invalid */
	char *image_type;	/*2G/3G/invalid*/
        char *platform;	    /* MT6573_S00(MT6573E1) or MT6573_S01(MT6573E2) */
	char *build_time;	/* build time string */
	char *build_ver;	/* project version, ex:11A_MD.W11.28 */
};


#define  NAME_LEN 100
struct image_info
{
	int idx;            /*idx=0,modem image; idx=1, dsp image */
	char file_name[NAME_LEN];
	unsigned long address;
	ssize_t size;
	loff_t offset;
	struct IMG_CHECK_INFO img_info;
	struct IMG_CHECK_INFO ap_info;
	int (*load_firmware)(struct image_info *info);
};
#endif 

typedef int (*ccci_cores_sleep_info_base_req)(void *);
typedef int (*ccci_core_eint_config_setup)(int, void *);


int __init ccci_md_init_mod_init(void);
void __exit ccci_md_init_mod_exit(void);


extern int ccci_uart_setup(int port, int *addr_virt, int *addr_phy, int *len);
extern int ccci_uart_base_req(int port, void *addr_phy, int *len);
extern int ccci_fs_setup(int *addr_virt, int *addr_phy, int *len);
extern int ccci_fs_base_req(void *addr_phy, int *len);
extern int ccci_pmic_setup(int *addr_virt, int *addr_phy, int *len);
extern int ccci_pmic_base_req(void *addr_phy, int *len);
extern int ccci_reset_register(char *name);
extern int ccci_reset_request(int handle);
extern int ccci_reset_index(void);
extern int ccci_ipc_setup(int *addr_virt, int *addr_phy, int *len);
extern int ccci_ipc_base_req(void *addr_phy, int *len);
extern int ccci_rpc_setup(int *addr_virt,int *addr_phy, int *len);
extern int ccci_pcm_base_req(void *addr_phy, int *len);
extern int ccci_mdlog_base_req(void *addr_phy, int *len);
extern int reset_md(void);
extern void md_call_chain(MD_CALL_BACK_HEAD_T *head,unsigned long data);
extern int md_register_call_chain(MD_CALL_BACK_HEAD_T *head,MD_CALL_BACK_QUEUE *queue);
extern int md_unregister_call_chain(MD_CALL_BACK_HEAD_T *head,MD_CALL_BACK_QUEUE *queue);
extern void check_data_connected(int channel);


//extern int ccci_sys_smem_base_phy;
extern int ccci_smem_size ;
extern int *ccci_smem_virt ;
extern dma_addr_t ccci_smem_phy;
extern int is_first_boot;
extern  MD_CALL_BACK_HEAD_T md_notifier;



#endif  /* !__CCCI_MD_H__ */
