#pragma once
#include <timedc_avtp.h>

struct net_fifo net_fifo_chans[] = {
	{
		.dst       = DEFAULT_MCAST,
		.stream_id = 42,
		.size      =  8,
		.freq      = 50,
		.name      = "mcast42"
	}
};
