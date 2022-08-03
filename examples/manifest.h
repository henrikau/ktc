#pragma once
#define DO_SRP 1
#define NIC "enp2s0.2"

#define LOOP_HZ 50
#define IT_MIN (50*60)
#define IT_HR (IT_MIN * 60)
#define LOOPS (1 * IT_HR)

#include <timedc_avtp.h>
struct net_fifo net_fifo_chans[] = {
	{
		/* DEFAULT_MCAST */
		.dst       = {0x01, 0x00, 0x5E, 0x01, 0x11, 0x42},
		.stream_id = 42,
		.class     = CLASS_A,
		.size      =  8,
		.freq      = 50,
		.name      = "mcast42"
	},


	{
		.dst       = {0x01, 0x00, 0x5E, 0x01, 0x11, 0x17},
		.stream_id = 17,
		.class     = CLASS_A,
		.size      =  8,
		.freq      = 10,
		.name      = "mcast17"
	},
	{
		.dst       = {0x01, 0x00, 0x5E, 0x01, 0x11, 0x18},
		.stream_id = 18,
		.class     = CLASS_A,
		.size      =  8,
		.freq      = 10,
		.name      = "mcast18"
	},
	{
		.dst       = {0x01, 0x00, 0x5E, 0x01, 0x11, 0x20},
		.stream_id = 20,
		.class     = CLASS_A,
		.size      =  80,
		.freq      = 100,
		.name      = "mcast20"
	}
};
