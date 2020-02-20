
/**
 * main.c
 */


#include "mcal/nvic/nvic.h"
#include "mcal/PortDriver/port.h"
#include "mcal/dio/dio.h"
#include "config/DIO_lcfg.h"
#include "mcal/SysCtr/SysCtr.h"


int main(void)
{
    SysCtr_init();
    SysCtr_prepheralClkEnable(SYSCTL_PERIPH_GPIOF);
    SysCtr_prepheralClkEnable(SYSCTL_PERIPH_GPIOA);
    SysCtr_prepheralClkEnable(SYSCTL_PERIPH_GPIOB);
    SysCtr_prepheralClkEnable(SYSCTL_PERIPH_GPIOC);
    SysCtr_prepheralClkEnable(SYSCTL_PERIPH_GPIOD);
    SysCtr_prepheralClkEnable(SYSCTL_PERIPH_GPIOE);
    PORT_init();

    Dio_WriteChannelGroup(EMPTY_GROUP_0, STD_high);

    while (1)
    {

    }

}
