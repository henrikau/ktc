#include <stdio.h>
#include <cilktc.h>

#include <timedc_avtp.h>
#include "manifest.h"

task reader()
{
	printf("%s(): getting ready\n", __func__);
	NETFIFO_RX(mcast42);
	while (1) {
		uint64_t d = 0;
		READ(mcast42, &d);
		printf("Counter received! -> %lu\n", d);
	}
}


void main()
{
	nf_set_nic("eth0");
	nf_verbose();
	reader();
}
