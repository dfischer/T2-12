#ifndef PIN_INFO_MAPS_H
#define PIN_INFO_MAPS_H

/*PIN INFO MACRO MAPS*/
/* for direction name to (six way) ITCDir use ITC_DIR__<ET> etc */

/* six way ITCDir to (eight way) dir num */
/*      ITC_DIR_TO_DIR_NUM__NT 0 North non-existent in T2-12*/
#define ITC_DIR_TO_DIR_NUM__NE 1
#define ITC_DIR_TO_DIR_NUM__ET 2
#define ITC_DIR_TO_DIR_NUM__SE 3
/*      ITC_DIR_TO_DIR_NUM__ST 4 South non-existent in T2-12*/
#define ITC_DIR_TO_DIR_NUM__SW 5
#define ITC_DIR_TO_DIR_NUM__WT 6
#define ITC_DIR_TO_DIR_NUM__NW 7
#define ITC_DIR_TO_DIR_NUM(dir) ITC_DIR_TO_DIR_NUM__##dir

/* direction to pru# */
#define ITC_DIR_TO_PRU__NE 1
#define ITC_DIR_TO_PRU__ET 0
#define ITC_DIR_TO_PRU__SE 0
#define ITC_DIR_TO_PRU__SW 0
#define ITC_DIR_TO_PRU__WT 1
#define ITC_DIR_TO_PRU__NW 1
#define ITC_DIR_TO_PRU(dir) ITC_DIR_TO_PRU__##dir

/* direction to prudir# */
#define ITC_DIR_TO_PRUDIR__NE 2
#define ITC_DIR_TO_PRUDIR__ET 0
#define ITC_DIR_TO_PRUDIR__SE 1
#define ITC_DIR_TO_PRUDIR__SW 2
#define ITC_DIR_TO_PRUDIR__WT 0
#define ITC_DIR_TO_PRUDIR__NW 1
#define ITC_DIR_TO_PRUDIR(dir) ITC_DIR_TO_PRUDIR__##dir

/* pru# + prudir# to direction */
#define ITC_PRU_PRU_DIR_TO_DIR__0_0 ET
#define ITC_PRU_PRU_DIR_TO_DIR__0_1 SE
#define ITC_PRU_PRU_DIR_TO_DIR__0_2 SW
#define ITC_PRU_PRU_DIR_TO_DIR__1_0 WT
#define ITC_PRU_PRU_DIR_TO_DIR__1_1 NW
#define ITC_PRU_PRU_DIR_TO_DIR__1_2 NE
#define ITC_PRU_PRU_DIR_TO_DIR(pru,prudir) ITC_PRU_PRU_DIR_TO_DIR__##pru##_##prudir

/* pin name to itc pin number */
#define ITC_PIN_NAME_TO_PIN_NUMBER__TXRDY 0
#define ITC_PIN_NAME_TO_PIN_NUMBER__TXDAT 1
#define ITC_PIN_NAME_TO_PIN_NUMBER__RXRDY 2
#define ITC_PIN_NAME_TO_PIN_NUMBER__RXDAT 3
#define ITC_PIN_NAME_TO_PIN_NUMBER(pname) ITC_PIN_NAME_TO_PIN_NUMBER__##pname

/* dir+name to R30 output/R31 output pin numbers */
#define ITC_DIR_NAME_TO_R30_PIN__NE_TXRDY 10
#define ITC_DIR_NAME_TO_R30_PIN__NE_TXDAT 11
#define ITC_DIR_NAME_TO_R31_PIN__NE_RXRDY 4
#define ITC_DIR_NAME_TO_R31_PIN__NE_RXDAT 5

#define ITC_DIR_NAME_TO_R30_PIN__ET_TXRDY 3
#define ITC_DIR_NAME_TO_R30_PIN__ET_TXDAT 4
#define ITC_DIR_NAME_TO_R31_PIN__ET_RXRDY 0
#define ITC_DIR_NAME_TO_R31_PIN__ET_RXDAT 1

#define ITC_DIR_NAME_TO_R30_PIN__SE_TXRDY 5
#define ITC_DIR_NAME_TO_R30_PIN__SE_TXDAT 6
#define ITC_DIR_NAME_TO_R31_PIN__SE_RXRDY 2
#define ITC_DIR_NAME_TO_R31_PIN__SE_RXDAT 14

#define ITC_DIR_NAME_TO_R30_PIN__SW_TXRDY 7
#define ITC_DIR_NAME_TO_R30_PIN__SW_TXDAT 14
#define ITC_DIR_NAME_TO_R31_PIN__SW_RXRDY 15
#define ITC_DIR_NAME_TO_R31_PIN__SW_RXDAT 16

#define ITC_DIR_NAME_TO_R30_PIN__WT_TXRDY 0
#define ITC_DIR_NAME_TO_R30_PIN__WT_TXDAT 1
#define ITC_DIR_NAME_TO_R31_PIN__WT_RXRDY 6
#define ITC_DIR_NAME_TO_R31_PIN__WT_RXDAT 7

#define ITC_DIR_NAME_TO_R30_PIN__NW_TXRDY 8
#define ITC_DIR_NAME_TO_R30_PIN__NW_TXDAT 9
#define ITC_DIR_NAME_TO_R31_PIN__NW_RXRDY 2
#define ITC_DIR_NAME_TO_R31_PIN__NW_RXDAT 3

/* example: ITC_DIR_AND_PIN_TO_R30_BIT(ET,RXRDY) */
#define ITC_DIR_AND_PIN_TO_R30_BIT(dir,pin) ITC_DIR_NAME_TO_R30_PIN__##dir##_##pin
#define ITC_DIR_AND_PIN_TO_R31_BIT(dir,pin) ITC_DIR_NAME_TO_R31_PIN__##dir##_##pin

/* MACRO ITERATORS */
#define FOR_XX_IN_ITC_ALL_DIR XX(NE) XX(ET) XX(SE) XX(SW) XX(WT) XX(NW)
#define FOR_XX_IN_ITC_ALL_PRUDIR XX(0) XX(1) XX(2)

#endif /* PIN_INFO_MAPS_H */
