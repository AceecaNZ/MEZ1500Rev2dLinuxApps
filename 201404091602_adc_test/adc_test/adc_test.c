//*****************************************************************************
//
// File Name:  adc_test.c
//
//          Rev        Date         Name        Reason
//          -------    --------     --------    -------------------------------
//          1.00       23-04-08			S.Venroy		Created  
//
//*****************************************************************************
// Includes
// ~~~~~~~~
#include <signal.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

#include <errno.h>


#include "MEZ1500_mzio.h"

#include "adc1.h"

//-----------------------------------------------------------------------------
// Variables
// ~~~~~~~~~
int mLoop = 1;
//-----------------------------------------------------------------------------
//
// Create a compile date and time stamp
#define COMPILE_HOUR (((__TIME__[0]-'0')*10) + (__TIME__[1]-'0'))
#define COMPILE_MIN	 (((__TIME__[3]-'0')*10) + (__TIME__[4]-'0'))
#define COMPILE_SEC	 (((__TIME__[6]-'0')*10) + (__TIME__[7]-'0'))

#define YEAR ((((__DATE__ [7]-'0')*10+(__DATE__ [8]-'0'))*10+ \
(__DATE__ [9]-'0'))*10+(__DATE__ [10]-'0'))

/* Month: 0 - 11 */
#define MONTH ( __DATE__ [2] == 'n' ? (__DATE__ [1] == 'a' ? 0 : 5) \
	            : __DATE__ [2] == 'b' ? 1 \
              : __DATE__ [2] == 'r' ? (__DATE__ [0] == 'M' ? 2 : 3) \
              : __DATE__ [2] == 'y' ? 4 \
              : __DATE__ [2] == 'l' ? 6 \
              : __DATE__ [2] == 'g' ? 7 \
              : __DATE__ [2] == 'p' ? 8 \
              : __DATE__ [2] == 't' ? 9 \
              : __DATE__ [2] == 'v' ? 10 : 11)

#define DAY ((__DATE__ [4]==' ' ? 0 : __DATE__ [4]-'0')*10+(__DATE__[5]-'0'))

static int GetCompileHour  (void){int hour  = COMPILE_HOUR;return(hour);}
static int GetCompileMinute(void){int minute= COMPILE_MIN; return(minute);}
static int GetCompileYear  (void){int year  = YEAR;        return(year);}
static int GetCompileMonth (void){int month = MONTH;       return(month + 1);}
static int GetCompileDay   (void){int day   = DAY;         return((char)day);}
//-----------------------------------------------------------------------------
//
// Here when app or service receives a signal
static void sighandler(int sig)
{
	mLoop = 0;
}
//=============================================================================
// Program entry point
// ~~~~~~~~~~~~~~~~~~~
int main(int argc, char *argv[])
{
	int 	err = 0;
	
	int		fd_mzio = 0;
	int		fd_spi = 0;

	//int		state = 0;
//.............................................................................
//
// For tidy exit using kill -SIGABRT pid
	signal(SIGABRT, &sighandler);
	signal(SIGTERM, &sighandler);
	signal(SIGINT,  &sighandler);
//.............................................................................
//
// Display the compile date and time stamp
	printf("gpiotest version %d%02d%02d%02d%02d\n", GetCompileYear(),
	GetCompileMonth(), GetCompileDay(), GetCompileHour(), GetCompileMinute());

	fd_mzio = open("/dev/mzio", 0);
  if(fd_mzio < 0)
  {
    printf("Failed to open mzio device\n");
    goto exit;
  }
    
	fd_spi = open("/dev/spidev0.0", 0);
  if(fd_spi < 0)
  {
    printf("Failed to open spi device\n");
    goto exit;
  }
//.............................................................................
//
// Set up mzio


// Set all to reset state
	ioctl(fd_mzio, MZIO_CAMIF_SET_UP, 	0);		// Pull-ups on
	ioctl(fd_mzio, MZIO_CAMIF_SET_CFG, 	0);		// All inputs
	ioctl(fd_mzio, MZIO_CAMIF_SET_DAT, 	0);		// All data low

// Enable power
	ioctl(fd_mzio, MZIO_GPIO_SET_LOW,  	MZIO_5V_MZ_ENn);
	ioctl(fd_mzio, MZIO_GPIO_SET_LOW,  	MZIO_3V3_EXT_ENn);
	ioctl(fd_mzio, MZIO_GPIO_SET_HIGH,  MZIO_MOD_PWR);
	
// Now configure lines
	ioctl(fd_mzio, MZIO_CAMIF_SET_DAT, 	bGPDAT_CAM_init);
	ioctl(fd_mzio, MZIO_CAMIF_SET_UP, 	bGPUP_CAM_init);
	ioctl(fd_mzio, MZIO_CAMIF_SET_CFG, 	bGPCON_CAM_init);
	
	
	
	
	
	
	
// Turn on middle led as a test

{
	int bmask;
	int data;
	
	bmask = bDAT_CLIM_EN_N_CAM_DATA3;
	data = ioctl(fd_mzio, MZIO_CAMIF_GET_DAT, 0);
	data &= ~bmask;
	ioctl(fd_mzio, MZIO_CAMIF_SET_DAT, 	data);
	
	
	bmask = bDAT_CRNT_CN2_EN_N_CAM_DATA1;
	data = ioctl(fd_mzio, MZIO_CAMIF_GET_DAT, 0);
	data &= ~bmask;
	ioctl(fd_mzio, MZIO_CAMIF_SET_DAT, 	data);
	
	
	
	
}	
	
	
	
	
	
	

//.............................................................................
//
/*
	printf("Entering main loop\n");
    

	while(mLoop)
	{
		if(state)
		{
      //ioctl(fd_mzio, MZIO_GPIO_SET_LOW, MZIO_MOD_RESET);
			state=0;
		}
		else
		{
      //ioctl(fd_mzio, MZIO_GPIO_SET_HIGH, MZIO_MOD_RESET);
			state=1;
		}

//    sleep(1);    //Sleep for x seconds
	}

	printf("Exiting main loop\n");
*/	
//.............................................................................
//
exit:
	close(fd_spi);
	close(fd_mzio);

	printf("exit code: %d\n", err);
	
return err;
}
//-----------------------------------------------------------------------------

