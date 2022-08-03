#include <stdio.h>
#include <cilktc.h>

#include <timedc_avtp.h>
#include "manifest.h"

static bool running = false;
void sighandler(int signum)
{
	printf("%s(): Got signal (%d), closing\n", __func__, signum);
	fflush(stdout);
	running = false;
}

task writer()
{
	printf("%s(): getting ready\n", __func__);
	NETFIFO_TX(mcast42);

	for (uint64_t i = 0; i < LOOPS && running; i++) {
		WRITE_WAIT(mcast42, &i);
		if (!(i%100))
			printf("%lu: written\n", i);
		sdelay(20, ms);
	}

	uint64_t stop = -1;
	WRITE_WAIT(mcast42, &stop);
	printf("Magic stop marker written\n");

	CLEANUP();
	return NULL;
}


void main()
{
	nf_set_nic(NIC);
	printf("Run for %d, using %s\n", LOOPS, NIC);

#ifdef DO_SRP
	printf("Using SRP\n");
	nf_use_srp();
	nf_set_logfile("netfifo_talker_rt_srp.csv");
#else
	/* nf_keep_cstate(); */
	printf("Using RT\n");
	printf("NOT Using SRP\n");
	nf_set_logfile("netfifo_talker_rt_nosrp.csv");
#endif

	nf_log_delay();

	running = true;
	signal(SIGINT, sighandler);
	usleep(5000);
	writer();
}
