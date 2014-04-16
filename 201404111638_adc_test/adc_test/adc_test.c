//*****************************************************************************
//
// File Name:  adc_test.c
//
//          Rev        Date         Name        Reason
//          -------    --------     --------    -------------------------------
//          1.00       11-04-14			S.Venroy		Created  
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
#include <linux/spi/spidev.h>

#include "adc_test.h"
#include "MEZ1500_mzio.h"
#include "adc1.h"

//-----------------------------------------------------------------------------
// Variables
// ~~~~~~~~~
int mLoop = 1;

	unsigned char spi_mode = SPI_MODE_0;
	unsigned char spi_bitsPerWord = 8;
	unsigned int 	spi_speed = 500000;

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










/*
//-----------------------------------------------------------------------------
//
// Controls CN1, CN2, CN3 or the master for all three. 
//
// Parameters:
//	control -	CNx - Set master on or off.
//            CN1 - Set CN1 on or off.
//           	CN2 - Set CN2 on or off.
//           	CN3 - Set CN3 on or off.
//
//	state -		1 = on, 0 = off
//
// Returns:
//	0 - Success
//	1 - Failed with a current limit fault
//
static int	ADC1_PowerSet(WORD fd, WORD control, BOOL state)
{
	DWORD bmask = 0;
	DWORD data = 0;

// Translate
	switch(control)
	{
		case CNx:
			bmask = bDAT_CLIM_EN_N_CAM_DATA3;
			break;
		case CN1:
			bmask = bDAT_CRNT_CN1_EN_N_CAM_DATA0;
			break;
		case CN2:
			bmask = bDAT_CRNT_CN2_EN_N_CAM_DATA1;
			break;
		case CN3:
			bmask = bDAT_CRNT_CN3_EN_N_CAM_DATA2;
			break;
	}

// Do the I/O
	if(state)
	{	// Turn on
		data = ioctl(fd, MZIO_CAMIF_GET_DAT, 0);
		data &= ~bmask;
		ioctl(fd, MZIO_CAMIF_SET_DAT, 	data);
	}
	else
	{	// Turn off
		data = ioctl(fd, MZIO_CAMIF_GET_DAT, 0);
		data |= bmask;
		ioctl(fd, MZIO_CAMIF_SET_DAT, 	data);
	}

// Some delay in case there's some inrush current
	usleep(100000);

// Check for current limit fault
	data = ioctl(fd, MZIO_CAMIF_GET_DAT, 0);
	if(!(data & bDAT_CLIM_FLT_N_CAM_DATA4))
	{
		// Switch off the master
		data |= bDAT_CLIM_EN_N_CAM_DATA3;
		ioctl(fd, MZIO_CAMIF_SET_DAT, 	data);
		return 1;
	}

	return 0;
}
//-----------------------------------------------------------------------------
//
// Reads the state of CN1, CN2, CN3 or the master for all three.
//
// Parameters:
//	state - A pointer to a bool that will contain the state. (1 = on, 0 = off)
//
// control - 	CNx
//						CN1
//						CN2
//						CN3
//
// Returns:
//	0 - Success
//	1 - state arg was NULL
//
static int	ADC1_PowerGet(WORD fd, WORD control, BOOL *state)
{
	DWORD bmask = 0;
	DWORD data = 0;

	if(state == NULL)
		return 1;

// Translate
	switch(control)
	{
		case CNx:
			bmask = bDAT_CLIM_EN_N_CAM_DATA3;
			break;
		case CN1:
			bmask = bDAT_CRNT_CN1_EN_N_CAM_DATA0;
			break;
		case CN2:
			bmask = bDAT_CRNT_CN2_EN_N_CAM_DATA1;
			break;
		case CN3:
			bmask = bDAT_CRNT_CN3_EN_N_CAM_DATA2;
			break;
	}

// Do the I/O
	data = ioctl(fd, MZIO_CAMIF_GET_DAT, 0);

	if(data & bmask)
		*state = false;
	else
		*state = true;

	return 0;
}
*/









static int spiWriteRead(WORD fd, unsigned char *data, int length){
 
  struct spi_ioc_transfer spi[length];
  int i = 0;
  int retVal = -1; 
 
// one spi transfer for each byte
 
  for (i = 0 ; i < length ; i++){
 
    spi[i].tx_buf        = (unsigned long)(data + i); // transmit from "data"
    spi[i].rx_buf        = (unsigned long)(data + i) ; // receive into "data"
    spi[i].len           = sizeof(*(data + i)) ;
    spi[i].delay_usecs   = 0 ;
    spi[i].speed_hz      = spi_speed ;
    spi[i].bits_per_word = spi_bitsPerWord ;
    spi[i].cs_change = 0;
}
 
 retVal = ioctl (fd, SPI_IOC_MESSAGE(length), &spi) ;
 
 if(retVal < 0){
    printf("Problem transmitting spi data..ioctl\n");
 }
 
return retVal;
 
}




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

	fd_mzio = open("/dev/mzio",  O_RDWR);
  if(fd_mzio < 0)
  {
    printf("Failed to open mzio device\n");
    goto exit;
  }
    
	fd_spi = open("/dev/spidev0.0",  O_RDWR);
  if(fd_spi < 0)
  {
    printf("Failed to open spi device\n");
    goto exit;
  }
//.............................................................................
//
// Set up mzio

// Set all to reset state
	ioctl(fd_mzio, MZIO_CAMIF_SET_UP, 	0x1FFF);	// Pull-ups off
	ioctl(fd_mzio, MZIO_CAMIF_SET_CFG, 	0);				// All inputs
	ioctl(fd_mzio, MZIO_CAMIF_SET_DAT, 	0);				// All data low

// Enable power
	ioctl(fd_mzio, MZIO_GPIO_SET_LOW,  	MZIO_5V_MZ_ENn);
	ioctl(fd_mzio, MZIO_GPIO_SET_LOW,  	MZIO_3V3_EXT_ENn);
	ioctl(fd_mzio, MZIO_GPIO_SET_HIGH,  MZIO_MOD_PWR);
	
// Now configure lines
	ioctl(fd_mzio, MZIO_CAMIF_SET_DAT, 	bGPDAT_CAM_init);
	ioctl(fd_mzio, MZIO_CAMIF_SET_UP, 	bGPUP_CAM_init);
	ioctl(fd_mzio, MZIO_CAMIF_SET_CFG, 	bGPCON_CAM_init);
	
/*
//-------------------------------			
// Debug - Kit leds :)	
{
	#define KIT_DLY	100			// uS
	
	int x;
	
	// Turn on the master ctrl	
	ADC1_PowerSet(fd_mzio, CNx, 1);
	
	for(x=0; x<20; x++)
	{
	ADC1_PowerSet(fd_mzio, CN1, 1);
	usleep(KIT_DLY);
	ADC1_PowerSet(fd_mzio, CN1, 0);
	
	ADC1_PowerSet(fd_mzio, CN2, 1);
	usleep(KIT_DLY);
	ADC1_PowerSet(fd_mzio, CN2, 0);

	ADC1_PowerSet(fd_mzio, CN3, 1);
	usleep(KIT_DLY);
	ADC1_PowerSet(fd_mzio, CN3, 0);
			
	ADC1_PowerSet(fd_mzio, CN2, 1);
	usleep(KIT_DLY);
	ADC1_PowerSet(fd_mzio, CN2, 0);
	}
	
	// Turn off the master ctrl	
	ADC1_PowerSet(fd_mzio, CNx, 1);
}	
//-------------------------------	
*/



// Setup the SPI
	err = ioctl(fd_spi, SPI_IOC_WR_MODE, &spi_mode);
	if(err < 0)
	{
		printf("Could not set SPIMode\n");
		goto exit;
	}
	
	err = ioctl(fd_spi, SPI_IOC_WR_BITS_PER_WORD, &spi_bitsPerWord);
	if(err < 0)
	{
		printf("Could not set SPI bitsPerWord\n");
		goto exit;
	}
	
	err = ioctl(fd_spi, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed);    
	if(err < 0)
	{
		printf("Could not set SPI speed\n");
		goto exit;
	}
 





{
	int x;
	unsigned int a2dVal = 0;
	unsigned char adc_data[2];
	
	
	
	DWORD mzio_data = 0;
	
	
	for(x=1; x<=2; x++)
	{
		switch(x)
		{
			case 1:	adc_data[0] = ADC_SINGLE_ENDED_INPUT1 | ADC_5V_UNI; break;
			case 2:	adc_data[0] = ADC_SINGLE_ENDED_INPUT2 | ADC_5V_UNI; break;
			case 3:	adc_data[0] = ADC_SINGLE_ENDED_INPUT3 | ADC_5V_UNI; break;
			case 4:	adc_data[0] = ADC_SINGLE_ENDED_INPUT4 | ADC_5V_UNI; break;
			case 5:	adc_data[0] = ADC_SINGLE_ENDED_INPUT5 | ADC_5V_UNI; break;
			case 6:	adc_data[0] = ADC_SINGLE_ENDED_INPUT6 | ADC_5V_UNI; break;
			case 7:	adc_data[0] = ADC_SINGLE_ENDED_INPUT7 | ADC_5V_UNI; break;
			case 8:	adc_data[0] = ADC_SINGLE_ENDED_INPUT8 | ADC_5V_UNI; break;
		}
		
		adc_data[1] = 0;
		
		


		
// Start conversion and wait until done
	mzio_data = ioctl(fd_mzio, MZIO_CAMIF_GET_DAT, 0);
	mzio_data |= bDAT_ADC_CNV_START_CAM_DATA6;
	ioctl(fd_mzio, MZIO_CAMIF_SET_DAT, 	mzio_data);

	sleep(1);

/*

	dwStart = GetTickCount();
	while((GetTickCount() - dwStart) <= 10)
	{
		data = ioctl(fd, MZIO_CAMIF_GET_DAT, 0);
		if(data & bDAT_ADC_CNV_BSY_N_CAM_DATA7)
			break;
	}
		
*/		
		
	mzio_data = ioctl(fd_mzio, MZIO_CAMIF_GET_DAT, 0);
	mzio_data &= ~bDAT_ADC_CNV_START_CAM_DATA6;
	ioctl(fd_mzio, MZIO_CAMIF_SET_DAT, 	mzio_data);
		
		
		
		spiWriteRead(fd_spi, adc_data, 2);
		
		
		//printf("adc_data[1] = 0x%X  adc_data[0] = 0x%X\n", adc_data[1], adc_data[0]);
		
	
		a2dVal = (adc_data[0]<< 8) | adc_data[1];
		a2dVal >>= 4;
		
		
		printf("The CH:%d result is: 0x%x\n", x, a2dVal);

	}


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


