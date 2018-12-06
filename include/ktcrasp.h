
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <setjmp.h>
#include <pthread.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <stdbool.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <ktcpipe.h>
/*#include  "../../FreeRTOSv9.0.0/FreeRTOS/Source/include/FreeRTOS.h"
#include  "../../FreeRTOSv9.0.0/FreeRTOS/Source/include/task.h"
#include "../../FreeRTOSv9.0.0/FreeRTOS/Source/include/timers.h"
*/

enum sched_policy{EDF, FIFO_RM, RR_RM, FIFO_DM, RR_DM};
int policy = 0;
//#define spolicy(X) if( (X) == EDF) spolicy_edf(); else spolicy_other(); sleep(0)
#define spriority(c) ktc_set_priority(c);
#define gettime(unit)  ktc_gettime(unit);sdelay(-1404, 0)
#define spolicy(X) setschedvar = 1; policy =X; sdelay(-2103, ms); 
#define task void* __attribute__((task))
#define sdelay(intr, ...) sdelay(intr, intr, ##__VA_ARGS__)
#define stp(pr, dl, unit) sdelay(pr, dl, unit)
#define ftp(pr, dl, unit) if (pr == 0) skipdelay;  fdelay(pr, dl, unit)
#define fdelay(intr, ...) fdelay(intr, intr, ##__VA_ARGS__)
#define SEC_TO_NANO 1000000000
#define MILLI_TO_NANO 1000000
#define MICRO_TO_NANO 1000
#define MILLI 1000
#define MICRO 1000000 
#define NANO  1000000000

#define CONSTRUCTOR __attribute__((constructor))


#define ExactRGB(r,g,b) __attribute__((ExactRGB((r),(g),(b))))
#define LowerRGB(r,g,b) __attribute__((LowerRGB((r),(g),(b))))
#define UpperRGB(r,g,b) __attribute__((UpperRGB((r),(g),(b))))

#define AddRGB(x,r,g,b) (typeof(x) ExactRGB(r,g,b))x


#define red   __attribute__((red))
#define green __attribute__((green))
#define blue  __attribute__((blue))
#define AddColor(c,x) (typeof(x) c)x
#define task void* __attribute__((task))

#define cache_report if((void *__attribute__((cache_report)))0)

//#define sdelay(c)    printf("%d", c)

#define invariant(c,i,...) __blockattribute__((invariant((c),(i),__VA_ARGS__)))
#define post(c) __attribute__((post((c))))
#define pre(c)  __attribute__((pre((c))))
extern int period;
extern int runtime;
extern int deadline;

#define critical if((void *__attribute__((critical)))0)
#define skipdelay if((void *__attribute__((next)))0) next()
#define exec_child(x) if(x == 0)
//#define cread(chan, ptr)   if((void *__attribute__((read_block))) (sizeof(#chan) > &ptr)){sleep(0);}
//#define cwrite(chan, ptrw) if((void *__attribute__((write_block))) (sizeof(#chan) > ptrw)){sleep(0);}

#define cread(chan, ptr)  pipe_pop(chan##_consumer, &ptr, 1)
#define cwrite(chan, ptr) pipe_push(chan##_producer, &ptr, 1)
#define cinit(chan, val) chan ##_pipe = pipe_new(sizeof(chan), 0); chan ##_consumer = pipe_consumer_new(chan##_pipe); chan##_producer = pipe_producer_new(chan##_pipe); pipe_free(chan##_pipe)
#define nelem(chan) pipe_nelem(chan##_consumer)

#define lvchannel __attribute__((lvchannel))
#define fifochannel(chan) chan ; pipe_t* chan ##_pipe ; pipe_consumer_t* chan ##_consumer; pipe_producer_t* chan ##_producer  

//# task if((void *__attribute__((task)))1)
#define main() *dummyglobalvariable; int populatelist(int num){ if(num == 1){return 0;} qsort (list_dl, num, sizeof(int), compare_qsort); qsort (list_pr, num, sizeof(int), compare_qsort); } void main()
#define aperiodic(val, ms)   list_dl[0] = val/1000;list_pr[0] = val/1000; runtime = val/1000; deadline = val/1000; period = val/1000; ktc_set_sched(policy, runtime, period, deadline);
#define ms -3
#define ns -9
#define sec 0
#define us -6

struct threadqueue {
   pthread_mutex_t mutex ;
   pthread_cond_t cond ;
};


void *checked_dlsym(void *handle, const char *sym);
pid_t gettid();

void perf_init(pid_t pid);
uint64_t perf_get_cache_refs();
uint64_t perf_get_cache_miss();
void perf_deinit();
uint64_t tut_get_time();

struct timespec* timepecptr;
timer_t ftimer;
sigset_t sigtype;
struct timespec diff_timespec(struct timespec, struct timespec);
struct timespec add_timespec(struct timespec, struct timespec);
int cmp_timespec(struct timespec, struct timespec);
long convert_timespec_to_ms(struct timespec);
long convert_to_ms(long, char*);
struct timespec convert_to_timespec(long, char*);
long timespec_to_unit(struct timespec val, char* unit);
int ktc_critical_end(sigset_t* orig_mask);
int ktc_critical_start(sigset_t* orig_mask);
int ktc_set_sched(int policy, int runtime, int deadline, int period) ;
int ktc_set_priority(int prio);

void toggle_lock_tracking();

struct tp_struct{
        int waiting;
        jmp_buf env;
        timer_t* tmr;
};


bool boolvar;
struct tp_struct tp_struct_data;
int list_pr[500];
int list_dl[500];
void ktc_create_timer(timer_t* ktctimer, struct tp_struct* tp, int num);
extern int ktc_start_time_init(struct timespec* start_time) ;
extern long ktc_sdelay_init(int deadline, int period, int unit, struct timespec* start_time, int id ) ;
extern long ktc_gettime(char* unit);
extern long ktc_fdelay_init(int interval, char* unit, struct timespec* start_time, int id, int num, int retjmp);
sigjmp_buf buf_struct;


typedef struct cbm{
	int use;
	int data;
	struct cbm* nextc;
} cbm;

struct cab_ds{
	struct cbm* free;
	struct cbm* mrb;
	int maxcbm; 
	
};

cbm cabmsgv;
struct cab_ds cabdsv;

struct fifolist{
	int data;
	struct timespec ts;
	struct fifolist* nextf;
	pthread_mutex_t mutx;
};

struct sched_attr {
	__u32 size;

	__u32 sched_policy;
	__u64 sched_flags;

	/* SCHED_NORMAL, SCHED_BATCH */
	__s32 sched_nice;

	/* SCHED_FIFO, SCHED_RR */
	__u32 sched_priority;

	/* SCHED_DEADLINE (nsec) */
	__u64 sched_runtime;
	__u64 sched_deadline;
	__u64 sched_period;
 };

struct sched_attr sae;
struct fifolist fifoex;

extern int compare_qsort (const void * elem1, const void * elem2);
extern int populatelist(int num);
struct cbm* ktc_htc_reserve(struct cab_ds* cab);
void ktc_htc_putmes(struct cab_ds* cab, struct cbm* buffer);
cbm* ktc_htc_getmes(struct cab_ds* cab);
void ktc_htc_unget (struct cab_ds* cab, cbm* buffer);
void ktc_fifo_init(struct fifolist** chan);
int ktc_fifo_read_aux(struct fifolist** chan, int* data,  pthread_mutex_t* mutx);
void ktc_fifo_write_aux(struct fifolist** chan, int data,  pthread_mutex_t* mutx);
int ktc_fifo_read(struct fifolist** chan, int* data);
void ktc_fifo_write(struct fifolist** chan, int data);
void ktc_simpson(int* sdata, int* tdata);
#include <getopt.h>
size_t s;
struct option o;
static inline int sched_getattr(pid_t pid, struct sched_attr *attr, unsigned int size, unsigned int flags){return syscall(315, pid, attr, size, flags);}
/*
static inline int setjmpdummy(){
	sigsetjmp(buf_struct, 1);
}
*/

//#pragma cilnoremove("getoptdummy")

static inline int getoptdummy()
{
  int i;
  optarg = NULL;
  sscanf(NULL,"%d",&i);
  return getopt_long(0, NULL, NULL, NULL, NULL);
}

#define ARG_HAS_OPT 1

#define argument(argtype, argname, ...) \
argtype argname; \
int argname##got; \
struct ciltut_##argname { \
  char    *short_form; \
  char    *help_text; \
  char    *format; \
  argtype  def; \
  void    *requires; \
  int      has_opt; \
} __attribute__((ciltutarg, ##__VA_ARGS__)) _ciltut_##argname =

#define arg_assert(e) (void *__attribute__((ciltut_assert((e)))))0


#define autotest    __attribute__((autotest))
#define instrument  __attribute__((instrument))
#define input       __attribute__((input))
#define inputarr(s) __attribute__((inputarr(s)))
#define inputnt     __attribute__((inputnt))

void assign(uint64_t lhs, uint64_t op, int opk, uint64_t opv);
void assgn_bop(uint64_t lhs, uint64_t lhsv, int bop,
               uint64_t op1, int op1k, uint64_t op1v,
               uint64_t op2, int op2k, uint64_t op2v);
void assgn_uop(uint64_t lhs, uint64_t lhsv, int uop,
               uint64_t op, int opk, uint64_t opv);

void cond(int cid, int r, uint64_t op, int opk, uint64_t opv);
void cond_bop(int cid, int bop, int r,
              uint64_t op1, int op1k, uint64_t op1v,
              uint64_t op2, int op2k, uint64_t op2v);
void cond_uop(int cid, int uop, int r,
              uint64_t op, int opk, uint64_t opv);

void register_input(char *name, uint64_t addr, int bits);
void register_arr_input(char *name, uint64_t start, int sz, int cnt);
void register_nt_input(char *name, char *start);
//int ktc_sdelay_end(char const   *f , int l , int intrval , char *unit ) ;
//void ktc_sdelay_init(char const   *f , int l ) ;
int ktc_fdelay_start_timer(int interval, char* unit, timer_t ktctimer, struct timespec* start_time);
pthread_t pthread_id_example;




/** FREERTOS**/
/*
TaskHandle_t tskhndl;
TimerHandle_t tmrhndl;
UBaseType_t idle_prio = tskIDLE_PRIORITY;
TickType_t tckvar;
TimerHandle_t ktc_timer_init_free();
long ktc_sdelay_init_free(int intrval, char* unit, TickType_t *start_time, int id);
void ktc_start_time_init_free(TickType_t *start_time);
#pragma cilnoremove("tmrhndl")
#pragma cilnoremove("tckvar")
#pragma cilnoremove("tskhdl")
#pragma cilnoremove("idle_prio")
#pragma cilnoremove("xTaskCreate")
#pragma cilnoremove("xTaskGetTickCount")
#pragma cilnoremove("vTaskDelayUntil")
#pragma cilnoremove("vTaskDelete")
#pragma cilnoremove("ktc_start_time_init_free")
#pragma cilnoremove("ktc_timer_init_free")
#pragma cilnoremove("ktc_sdelay_init_free")
/*FREERTOS*/

#pragma cilnoremove("compare_qsort")
#pragma cilnoremove("ktc_htc_reserve")
#pragma cilnoremove("ktc_htc_putmes")
#pragma cilnoremove("ktc_htc_getmes")
#pragma cilnoremove("ktc_htc_unget")
#pragma cilnoremove("cabmsgv")
#pragma cilnoremove("cabdsv")
#pragma cilnoremove("boolvar")
#pragma cilnoremove("fork")
#pragma cilnoremove("exec_child")
#pragma cilnoremove("pthread_id_example")
#pragma cilnoremove("sigtype")
#pragma cilnoremove("next")
#pragma cilnoremove("ktc_start_time_init")
#pragma cilnoremove("ktc_sdelay_init")
#pragma cilnoremove("ktc_fdelay_init")
#pragma cilnoremove("timepecptr")
#pragma cilnoremove("env")
#pragma cilnoremove("ftimer")
#pragma cilnoremove("ktc_create_timer")
#pragma cilnoremove("tp_struct_data")
#pragma cilnoremove("__sigsetjmp")
#pragma cilnoremove("pthread_join")
#pragma cilnoremove("pthread_create")
#pragma cilnoremove("ktc_fdelay_start_timer")
#pragma cilnoremove("ktc_critical_end")
#pragma cilnoremove("ktc_critical_start")
#pragma cilnoremove("fifoex")
#pragma cilnoremove("ktc_fifo_init")
#pragma cilnoremove("ktc_fifo_read")
#pragma cilnoremove("ktc_fifo_write")
#pragma cilnoremove("ktc_simpson")
#pragma cilnoremove("ktc_set_sched")
#pragma cilnoremove("ktc_gettime")
#pragma cilnoremove("list_dl")
#pragma cilnoremove("list_pr")
#pragma cilnoremove("populatelist")
#pragma cilnoremove("sched_getattr")
#pragma cilnoremove("sae")
extern int autotest_finished;
//extern int ktc_sdelay_end(char const   *f , int l , int intrval , char *unit ) ;
//extern long ktc_sdelay_init(char const   *f , int l, int intrval, char* unit, struct timespec* start_time ) ;
void gen_new_input();

void val_push(uint64_t v);
uint64_t val_pop(char *name);
void pop_array(char *name, char *base, int cnt, int sz);
void pop_nt(char * name, char *base);

void return_push(uint64_t p, uint64_t v);
void return_pop(uint64_t p, uint64_t v);

void autotest_reset();

//int ktc_sdelay_end(char const   *f , int l , int intrval , char *unit ) ;
//void ktc_sdelay_init(char const   *f , int l ) ;



