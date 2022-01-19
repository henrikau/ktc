#include <stdlib.h>
#include <stdio.h>
#include<cilktc.h>
#include<ktcpipe.h>

#include <ifaddrs.h>
#include <netdb.h>

#include <timedc_avtp.h>
#include "manifest.h"

/*
 * To connect to docker-image to run second process:
 * sudo docker exec -it $(sudo docker ps|grep ktcbuild|awk '{print $NF}') /bin/bash --login
 */

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
	nf_set_nic("lo");
	nf_verbose();
	reader();
}
