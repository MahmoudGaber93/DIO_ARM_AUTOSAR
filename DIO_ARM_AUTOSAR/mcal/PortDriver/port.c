/*
 * port.c
 *
 *  Created on: Nov 12, 2019
 *      Author: Muammad Elzeiny
 */
#define MAX_NUM_OF_CH_IN_PORT       8
#define MAX_NUM_OF_PORTS            6

#include "utils/STD_Types.h"
#include "../../utils/Bit_Math.h"
#include "../../config/port_cfg.h"
#include "../mcu_hw.h"
#include "port_types.h"
#include "port.h"

extern Port_CfgType PortCfgArr[];
static volatile PORT_RegType* BaseAddrArr[MAX_NUM_OF_PORTS] = { PORTA_BaseAddr,
                                                                PORTB_BaseAddr,
                                                                PORTC_BaseAddr,
                                                                PORTD_BaseAddr,
                                                                PORTE_BaseAddr,
                                                                PORTF_BaseAddr };

void PORT_init(void)
{
    uint8 CfgArrIndex;
    Port_IdType PortId;
    Port_ChIdType ChannelId;
    uint8 ChannelPosInPort;
    volatile PORT_RegType* BaseAddr;

    for (CfgArrIndex = 0; CfgArrIndex < PORT_NUM_OF_ACTIVATED_CH; ++CfgArrIndex)
    {
        /*get channelID from CfgIndex*/
        ChannelId = PortCfgArr[CfgArrIndex].Channel;

        /*get PORTId using ChannelId*/
        ChannelPosInPort = ChannelId % MAX_NUM_OF_CH_IN_PORT;

        /*get Channel Position in PortGroup using ChannelId */
        PortId = (Port_IdType) (ChannelId / MAX_NUM_OF_CH_IN_PORT);

        /*get baseAddress using PortId*/
        BaseAddr = BaseAddrArr[PortId];

        /*NOTE use channel position in Group to write in corresponding bit in Desired Register */

        /*TODO: set channel direction */

        (*BaseAddr).GPIODIR |= (PortCfgArr[CfgArrIndex].Dir) << ChannelPosInPort;

        /*TODO: set channel mode */
        (*BaseAddr).GPIOPCTL |= (PortCfgArr[CfgArrIndex].Mode)<< (ChannelPosInPort * 4);/***because of the register divided to 8 parts***/

        /*TODO: set Interrupt configuration */
        if (PortCfgArr[CfgArrIndex].Interrupt == Port_IntDisable)
        {

            CLR_BIT(BaseAddr->GPIOIM, ChannelPosInPort);
        }
        else
        {
            SET_BIT(BaseAddr->GPIOIM, ChannelPosInPort);
            //SET_BIT(BaseAddr->GPIOMIS, ChannelPosInPort);
            /***sense for edges****/
            // CLR_BIT(BaseAddr->GPIOIS, ChannelPosInPort);

            if (PortCfgArr[CfgArrIndex].Interrupt == Port_IntFallingEdge)
            {
                /***not the both edges***/
                CLR_BIT(BaseAddr->GPIOIBE, ChannelPosInPort);
                CLR_BIT(BaseAddr->GPIOIEV ,ChannelPosInPort);

            }
            else if (PortCfgArr[CfgArrIndex].Interrupt == Port_IntRisingEdge)
            {
                /***not the both edges***/
                CLR_BIT(BaseAddr->GPIOIBE, ChannelPosInPort);
                SET_BIT(BaseAddr->GPIOIEV ,ChannelPosInPort);
            }
            else
            {
                /***the both edges***/
                SET_BIT(BaseAddr->GPIOIBE, ChannelPosInPort);
                CLR_BIT(BaseAddr->GPIOIEV ,ChannelPosInPort);


            }

        }

        if (PortCfgArr[CfgArrIndex].Dir == port_Dir_Input)
        {
            /*TODO: set Internal Attachment configuration */
            if (PortCfgArr[CfgArrIndex].AttachedRes
                    == Port_InternalAttach_OpenDrain)
            {
                SET_BIT(BaseAddr->GPIOODR, ChannelPosInPort);
            }
            else if (PortCfgArr[CfgArrIndex].AttachedRes
                    == Port_InternalAttach_PullUpRes)
            {
                SET_BIT(BaseAddr->GPIOPUR, ChannelPosInPort);

            }

            else if (PortCfgArr[CfgArrIndex].AttachedRes
                    == Port_InternalAttach_PullDownRes)
            {
                SET_BIT(BaseAddr->GPIOPDR, ChannelPosInPort);
            }
            else
            {
                CLR_BIT(BaseAddr->GPIOODR, ChannelPosInPort);
                CLR_BIT(BaseAddr->GPIOPUR, ChannelPosInPort);
                CLR_BIT(BaseAddr->GPIOPDR, ChannelPosInPort);

            }
        }
        else
        {

            CLR_BIT(BaseAddr->GPIOODR, ChannelPosInPort);
            CLR_BIT(BaseAddr->GPIOPUR, ChannelPosInPort);
            CLR_BIT(BaseAddr->GPIOPDR, ChannelPosInPort);
        }
        /*TODO: set current strength configuration */

        if (PortCfgArr[CfgArrIndex].CurrentDrive == Port_CurrDrive_2mA)
        {
            SET_BIT(BaseAddr->GPIODR2R, ChannelPosInPort);
            CLR_BIT(BaseAddr->GPIODR4R, ChannelPosInPort);
            CLR_BIT(BaseAddr->GPIODR8R, ChannelPosInPort);


        }
        else if (PortCfgArr[CfgArrIndex].CurrentDrive == Port_CurrDrive_4mA)
        {

            SET_BIT(BaseAddr->GPIODR4R, ChannelPosInPort);
            CLR_BIT(BaseAddr->GPIODR2R, ChannelPosInPort);
            CLR_BIT(BaseAddr->GPIODR8R, ChannelPosInPort);

        }
        else if (PortCfgArr[CfgArrIndex].CurrentDrive == Port_CurrDrive_8mA)
        {

            SET_BIT(BaseAddr->GPIODR8R, ChannelPosInPort);
            CLR_BIT(BaseAddr->GPIODR2R, ChannelPosInPort);
            CLR_BIT(BaseAddr->GPIODR4R, ChannelPosInPort);


        }
        else
        {
            CLR_BIT(BaseAddr->GPIODR8R, ChannelPosInPort);
            CLR_BIT(BaseAddr->GPIODR2R, ChannelPosInPort);
            CLR_BIT(BaseAddr->GPIODR4R, ChannelPosInPort);
        }

        /*Check if analog functionality is required*/
        if (PortCfgArr[CfgArrIndex].Mode != Port_Mode_AIN)
        {
            SET_BIT(BaseAddr->GPIODEN, ChannelPosInPort);

            CLR_BIT(BaseAddr->GPIOADCCTL, ChannelPosInPort);

            CLR_BIT(BaseAddr->GPIOAMSEL, ChannelPosInPort);

            /*TODO: enable digital and disable ADC  */

        }
        else
        {


            CLR_BIT(BaseAddr->GPIODEN, ChannelPosInPort);

            SET_BIT(BaseAddr->GPIOADCCTL, ChannelPosInPort);

            SET_BIT(BaseAddr->GPIOAMSEL, ChannelPosInPort);

            /*TODO: disable digital and enable ADC */

        }
    }
}
