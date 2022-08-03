#include <stdio.h>
#include <cilktc.h>

#include <timedc_avtp.h>
#include "manifest.h"

task reader()
{
	printf("%s(): getting ready\n", __func__);
	NETFIFO_RX(mcast42);
	while (1) {
		uint64_t d = -1;
		READ_WAIT(mcast42, &d);
		if (!(d%100))
			printf("Counter received! -> %lu\n", d);

		if (d == -1) {
			printf("Magic terminator received, stopping\n");
			break;
		}
	}
	CLEANUP();
	return NULL;
}


void main()
{
	printf("Using %s\n", NIC);
	nf_set_nic(NIC);

#ifdef DO_SRP
	nf_use_srp();
	nf_set_logfile("netfifo_listener_rt_srp.csv");
	printf("Using SRP\n");
#else
	/* nf_keep_cstate(); */
	printf("Using RT\n");
	printf("NOT Using SRP\n");
	nf_set_logfile("netfifo_listener_rt_nosrp.csv");
#endif
	nf_log_delay();
	reader();
}
