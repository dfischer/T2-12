/* PRU-specific (PRU0 vs PRU1) definitions  -*- C -*- */
#ifndef PRUX_H
#define PRUX_H

#ifndef ON_PRU
#error Symbol ON_PRU must be defined
#endif

#define xstr(a) str(a)
#define str(a) #a
#define CONC(a,b) a##b

#define HOST_UNUSED 255

#if ON_PRU==0

#define PRUX PRU0
#define PRUX_STR "PRU0"
#define PRUX_SCRATCH 10
#define PRUX_CTRL PRU0_CTRL
#define PRUX_CTRL_ADDR 0x22000
#define TO_ARM_HOST	16	
#define FROM_ARM_HOST	17
#define HOST_INT_BIT    30
#define HOST_INT   ((uint32_t) 1 << HOST_INT_BIT) /* 0x40000000 */
#define PRU0_TO_ARM_CHANNEL  2
#define PRU0_FROM_ARM_CHANNEL 0
#define PRU1_TO_ARM_CHANNEL  HOST_UNUSED
#define PRU1_FROM_ARM_CHANNEL HOST_UNUSED
#define TO_ARM_CHANNEL  PRU0_TO_ARM_CHANNEL
#define FROM_ARM_CHANNEL PRU0_FROM_ARM_CHANNEL

/* on PRU0 (FRED), prudirs 0,1,2 are ET,SE,SW */
#define DIRCODE_FOR_PRUDIR0 2
#define DIRCODE_FOR_PRUDIR1 3
#define DIRCODE_FOR_PRUDIR2 5

#define PRUDIR0_TXRDY_R30_BIT 3
#define PRUDIR0_TXDAT_R30_BIT 4
#define PRUDIR0_RXRDY_R31_BIT 0
#define PRUDIR0_RXDAT_R31_BIT 1

#define PRUDIR1_TXRDY_R30_BIT 5
#define PRUDIR1_TXDAT_R30_BIT 6
#define PRUDIR1_RXRDY_R31_BIT 2
#define PRUDIR1_RXDAT_R31_BIT 14

#define PRUDIR2_TXRDY_R30_BIT 7
#define PRUDIR2_TXDAT_R30_BIT 14
#define PRUDIR2_RXRDY_R31_BIT 15 
#define PRUDIR2_RXDAT_R31_BIT 16

#elif ON_PRU==1

#define PRUX PRU1
#define PRUX_STR "PRU1"
#define PRUX_SCRATCH 11
#define PRUX_CTRL PRU1_CTRL
#define PRUX_CTRL_ADDR 0x24000
#define TO_ARM_HOST	18	
#define FROM_ARM_HOST	19
#define HOST_INT_BIT    31
#define HOST_INT   ((uint32_t) 1 << HOST_INT_BIT) /* 0x80000000 */
#define PRU1_TO_ARM_CHANNEL  3
#define PRU1_FROM_ARM_CHANNEL 1
#define PRU0_TO_ARM_CHANNEL  HOST_UNUSED
#define PRU0_FROM_ARM_CHANNEL HOST_UNUSED
#define TO_ARM_CHANNEL  PRU1_TO_ARM_CHANNEL
#define FROM_ARM_CHANNEL PRU1_FROM_ARM_CHANNEL

/* on PRU1 (GINGER), prudirs 0,1,2 are WT,NW,NE */
#define DIRCODE_FOR_PRUDIR0 6
#define DIRCODE_FOR_PRUDIR1 7
#define DIRCODE_FOR_PRUDIR2 1

#define PRUDIR0_TXRDY_R30_BIT 0
#define PRUDIR0_TXDAT_R30_BIT 1
#define PRUDIR0_RXRDY_R31_BIT 6
#define PRUDIR0_RXDAT_R31_BIT 7

#define PRUDIR1_TXRDY_R30_BIT 8
#define PRUDIR1_TXDAT_R30_BIT 9
#define PRUDIR1_RXRDY_R31_BIT 2
#define PRUDIR1_RXDAT_R31_BIT 3

#define PRUDIR2_TXRDY_R30_BIT 10
#define PRUDIR2_TXDAT_R30_BIT 11
#define PRUDIR2_RXRDY_R31_BIT 4 
#define PRUDIR2_RXDAT_R31_BIT 5

#else
#error Must define symbol ON_PRU to be either 0 or 1
#endif

/*
 * Using the name 'itc-pkt' does seemingly probe the itc_pkt driver
 * that we install at /lib/modules/$(shell uname r)/itc/itc_pkt.ko
 */
#define CHAN_NAME  "itc-pkt"
#define CHAN_DESC  "Channel " xstr(HOST_INT_BIT) 
#define CHAN_PORT  (HOST_INT_BIT)

#endif /* PRUX_H */
