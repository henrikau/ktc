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

task writer() {
	NETFIFO_TX(mcast42);
	for (uint64_t i = 0; i < 10; i++) {
		WRITE(mcast42, &i);
		printf("%lu: written\n", i);
		usleep(100000);
	}

}

void main()
{
	nf_set_nic("lo");
	nf_verbose();
	usleep(5000);
	writer();
}
