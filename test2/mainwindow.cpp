#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "/opt/MEZ1500Rev2dLinux/Sources/linux-2.6.32.2/drivers/char/MEZ1500_mzio.h"
#include "/opt/MEZ1500Rev2dLinux/Sources/linux-2.6.32.2/include/linux/spi/spidev.h"
#include <sys/time.h>
#include "adc1.h"

#define CRNT_CN1_EN_N_CAM_DATA0     MZIO_CAMIF_DAT0
#define CRNT_CN2_EN_N_CAM_DATA1     MZIO_CAMIF_DAT1
#define CRNT_CN3_EN_N_CAM_DATA2     MZIO_CAMIF_DAT2
#define CLIM_EN_N_CAM_DATA3         MZIO_CAMIF_DAT3
#define CLIM_FLT_N_CAM_DATA4        MZIO_CAMIF_DAT4
#define ADC_RD_EN_N_CAM_DATA5       MZIO_CAMIF_DAT5
#define ADC_CNV_START_CAM_DATA6     MZIO_CAMIF_DAT6
#define ADC_CNV_BSY_N_CAM_DATA7     MZIO_CAMIF_DAT7

unsigned char   spi_mode = SPI_MODE_0;
unsigned char   spi_bitsPerWord = 8;
unsigned int    spi_speed = 500000;

// --------------------------------------------------------------------
// Internal Functions
// --------------------------------------------------------------------
static int spiWriteRead(int fd, unsigned char *data, int length);
static int spiWriteRead(int fd, unsigned char *data, int length)
{
    struct spi_ioc_transfer spi[length];
    int i = 0;
    int retVal = -1;

    // One spi transfer for each byte
    for (i = 0 ; i < length ; i++)
    {
        spi[i].tx_buf        = (unsigned long)(data + i); // transmit from "data"
        spi[i].rx_buf        = (unsigned long)(data + i); // receive into "data"
        spi[i].len           = sizeof(*(data + i));
        spi[i].delay_usecs   = 0;
        spi[i].speed_hz      = spi_speed;
        spi[i].bits_per_word = spi_bitsPerWord;
        spi[i].cs_change = 0;
    }

    retVal = ioctl (fd, SPI_IOC_MESSAGE(length), &spi);
    if(retVal < 0){
    printf("Problem transmitting spi data..ioctl\n");
    fflush(stdout);
    }

    return retVal;
}
// --------------------------------------------------------------------


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    count   = 0;
    fd_mzio = 0;
    fd_spi  = 0;

    // Unload the MZIO driver
    system("rmmod MEZ1500_mzio");

    // Load the MZIO driver
    system("insmod /lib/modules/2.6.32.2-MEZ1500/kernel/drivers/char/MEZ1500_mzio.ko");
    system("modprobe MEZ1500_mzio");


    fd_mzio = open("/dev/mzio", O_RDWR);
    if (fd_mzio < 0)
        printf("Failed to open MZIO module");
    else
        printf("Openned MZIO module");

    fd_spi  = open("/dev/spidev0.0",  O_RDWR);
    if (fd_spi < 0)
        printf("Failed to open SPI module");
    else
        printf("Openned SPI module");

exit:
    fflush(stdout);
}

MainWindow::~MainWindow()
{
    delete ui;
    // Unload the MZIO driver
    system("rmmod MEZ1500_mzio");

    ::close (fd_mzio);
    ::close (fd_spi);
}




void MainWindow::on_modpwron_clicked()
{
    unsigned int mzio_data;
    ui->status->setText("MOD_PWR on");
    if (fd_mzio>0)
    {
//        ioctl(fd_mzio, MZIO_GPIO_SET_DIR_OUT, MZIO_MOD_PWR);
//        ioctl(fd_mzio, MZIO_GPIO_SET_HIGH, MZIO_MOD_PWR);

        ioctl(fd_mzio, MZIO_CAMIF_SET_DAT, 	bGPDAT_CAM_init);
        ioctl(fd_mzio, MZIO_CAMIF_SET_UP, 	bGPUP_CAM_init);
        ioctl(fd_mzio, MZIO_CAMIF_SET_CFG, 	bGPCON_CAM_init);

        ioctl(fd_mzio, MZIO_GPIO_SET_LOW,  	MZIO_5V_MZ_ENn);
        mzio_data = ioctl(fd_mzio, MZIO_CAMIF_GET_DAT, 0);
        mzio_data &= ~(bDAT_CRNT_CN3_EN_N_CAM_DATA2|bDAT_CLIM_EN_N_CAM_DATA3);
        ioctl(fd_mzio, MZIO_CAMIF_SET_DAT, 	mzio_data);
    }
}

void MainWindow::on_modpwroff_clicked()
{
    unsigned int mzio_data;
    ui->status->setText("MOD_PWR off");
    if (fd_mzio>0)
    {
//        ioctl(fd_mzio, MZIO_GPIO_SET_DIR_OUT, MZIO_MOD_PWR);
 //       ioctl(fd_mzio, MZIO_GPIO_SET_LOW, MZIO_MOD_PWR);

        ioctl(fd_mzio, MZIO_GPIO_SET_LOW,  	MZIO_5V_MZ_ENn);
        mzio_data = ioctl(fd_mzio, MZIO_CAMIF_GET_DAT, 0);
        mzio_data |= bDAT_CRNT_CN3_EN_N_CAM_DATA2;
        ioctl(fd_mzio, MZIO_CAMIF_SET_DAT, 	mzio_data);
    }
}

void MainWindow::on_modrston_clicked()
{
    ui->status->setText("MZIO_MOD_RESET on");
    if (fd_mzio>0)
    {
        ioctl(fd_mzio, MZIO_GPIO_SET_DIR_OUT, MZIO_MOD_RESET);
        ioctl(fd_mzio, MZIO_GPIO_SET_HIGH, MZIO_MOD_RESET);
    }
}

void MainWindow::on_modrstoff_clicked()
{
    ui->status->setText("MZIO_MOD_RESET off");
    if (fd_mzio>0)
    {
        ioctl(fd_mzio, MZIO_GPIO_SET_DIR_OUT, MZIO_MOD_RESET);
        ioctl(fd_mzio, MZIO_GPIO_SET_LOW, MZIO_MOD_RESET);
    }
}

void MainWindow::on_initadc_clicked()
{
    printf("Init ADC\n");
    fflush(stdout);

    if (fd_mzio > 0)
    {
        ioctl(fd_mzio, MZIO_GPIO_SET_HIGH,   CRNT_CN1_EN_N_CAM_DATA0);
        ioctl(fd_mzio, MZIO_GPIO_SET_HIGH,   CRNT_CN2_EN_N_CAM_DATA1);
        ioctl(fd_mzio, MZIO_GPIO_SET_HIGH,   CRNT_CN3_EN_N_CAM_DATA2);
        ioctl(fd_mzio, MZIO_GPIO_SET_HIGH,   CLIM_EN_N_CAM_DATA3);
        ioctl(fd_mzio, MZIO_GPIO_SET_LOW,    CLIM_FLT_N_CAM_DATA4);
        ioctl(fd_mzio, MZIO_GPIO_SET_HIGH,   ADC_RD_EN_N_CAM_DATA5);
        ioctl(fd_mzio, MZIO_GPIO_SET_LOW,    ADC_CNV_START_CAM_DATA6);
        ioctl(fd_mzio, MZIO_GPIO_SET_LOW,    ADC_CNV_BSY_N_CAM_DATA7);

        ioctl(fd_mzio, MZIO_GPIO_SET_DIR_OUT, CRNT_CN1_EN_N_CAM_DATA0);
        ioctl(fd_mzio, MZIO_GPIO_SET_DIR_OUT, CRNT_CN2_EN_N_CAM_DATA1);
        ioctl(fd_mzio, MZIO_GPIO_SET_DIR_OUT, CRNT_CN3_EN_N_CAM_DATA2);
        ioctl(fd_mzio, MZIO_GPIO_SET_DIR_OUT, CLIM_EN_N_CAM_DATA3);
        ioctl(fd_mzio, MZIO_GPIO_SET_DIR_IN,  CLIM_FLT_N_CAM_DATA4);
        ioctl(fd_mzio, MZIO_GPIO_SET_DIR_OUT, ADC_RD_EN_N_CAM_DATA5);
        ioctl(fd_mzio, MZIO_GPIO_SET_DIR_OUT, ADC_CNV_START_CAM_DATA6);
        ioctl(fd_mzio, MZIO_GPIO_SET_DIR_IN,  ADC_CNV_BSY_N_CAM_DATA7);

        ioctl(fd_mzio, MZIO_GPIO_SET_HIGH,   CRNT_CN1_EN_N_CAM_DATA0);
        ioctl(fd_mzio, MZIO_GPIO_SET_HIGH,   CRNT_CN2_EN_N_CAM_DATA1);
        ioctl(fd_mzio, MZIO_GPIO_SET_HIGH,   CRNT_CN3_EN_N_CAM_DATA2);
        ioctl(fd_mzio, MZIO_GPIO_SET_HIGH,   CLIM_EN_N_CAM_DATA3);
        ioctl(fd_mzio, MZIO_GPIO_SET_LOW,    CLIM_FLT_N_CAM_DATA4);
        ioctl(fd_mzio, MZIO_GPIO_SET_HIGH,   ADC_RD_EN_N_CAM_DATA5);
        ioctl(fd_mzio, MZIO_GPIO_SET_LOW,    ADC_CNV_START_CAM_DATA6);
        ioctl(fd_mzio, MZIO_GPIO_SET_LOW,    ADC_CNV_BSY_N_CAM_DATA7);

        ioctl(fd_mzio, MZIO_GPIO_SET_PU_OFF,  CRNT_CN1_EN_N_CAM_DATA0);
        ioctl(fd_mzio, MZIO_GPIO_SET_PU_OFF,  CRNT_CN2_EN_N_CAM_DATA1);
        ioctl(fd_mzio, MZIO_GPIO_SET_PU_OFF,  CRNT_CN3_EN_N_CAM_DATA2);
        ioctl(fd_mzio, MZIO_GPIO_SET_PU_OFF,  CLIM_EN_N_CAM_DATA3);
        ioctl(fd_mzio, MZIO_GPIO_SET_PU_OFF,  CLIM_FLT_N_CAM_DATA4);
        ioctl(fd_mzio, MZIO_GPIO_SET_PU_OFF,  ADC_RD_EN_N_CAM_DATA5);
        ioctl(fd_mzio, MZIO_GPIO_SET_PU_OFF,  ADC_CNV_START_CAM_DATA6);

        ioctl(fd_mzio, MZIO_GPIO_SET_PU_OFF,  ADC_CNV_BSY_N_CAM_DATA7);
    }
}

void MainWindow::on_readADC_clicked()
{
    int retVal;
    int err;
    unsigned int a2dVal = 0;
    unsigned char adc_data[2];
    printf("Reading ADC\n");
    fflush(stdout);

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

    printf("SPI setup done\n");

    {
        int x;
        unsigned int a2dVal = 0;
        unsigned char adc_data[2];

        int mzio_data = 0;

        for(x=1; x<=2; x++)
        {

            printf("1\n");

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
            mzio_data &= ~(bDAT_CRNT_CN3_EN_N_CAM_DATA2);
            ioctl(fd_mzio, MZIO_CAMIF_SET_DAT, 	mzio_data);

            sleep(2);

            printf("2\n");

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
            mzio_data |= bDAT_CRNT_CN3_EN_N_CAM_DATA2;
            ioctl(fd_mzio, MZIO_CAMIF_SET_DAT, 	mzio_data);

            printf("3\n");

            retVal = spiWriteRead(fd_spi, adc_data, 2);


            //printf("adc_data[1] = 0x%X  adc_data[0] = 0x%X\n", adc_data[1], adc_data[0]);

            a2dVal = (adc_data[0]<< 8) | adc_data[1];
            a2dVal >>= 4;


            printf("The CH:%d result is: 0x%x\n", x, a2dVal);
        }
    }
exit:
    fflush(stdout);
}
