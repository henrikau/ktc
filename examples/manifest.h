#pragma once
#include <timedc_avtp.h>
struct net_fifo net_fifo_chans[] = {
	{
		/* DEFAULT_MCAST */
		.dst       = {0x01, 0x00, 0x5E, 0x00, 0x00, 0x00},
		.stream_id = 42,
		.size      =  8,
		.freq      = 50,
		.name      = "mcast42"
	}
};
