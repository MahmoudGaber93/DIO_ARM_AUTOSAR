/*
 * dio.c
 *
 *  Created on: Jul 8, 2019
 *      Author: Muhammad.Elzeiny
 */

#include "utils/Bit_Math.h"
#include "utils/STD_Types.h"
#include "mcal/mcu_hw.h"
/*TODO: include the header file that contains register definitions */

#include "dio.h"
#include "config/DIO_Cfg.h"


uint32* ptr_portA_add =   (uint32*)PORTA_BaseAddr;
uint32* ptr_portB_add =   (uint32*)PORTB_BaseAddr;
uint32* ptr_portC_add =   (uint32*) PORTC_BaseAddr;
uint32* ptr_portD_add =   (uint32*) PORTD_BaseAddr;
uint32* ptr_portE_add =   (uint32*) PORTE_BaseAddr;
uint32* ptr_portF_add =   (uint32*)PORTF_BaseAddr;

uint8  gau8_Pins_LUT[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };

//extern  Dio_ChannelGroupType arr_PortGroupCnfg[];

#define PORT_DATA_OFFSET_MASK(PORT_BASE,CH_NO)          (uint32*)((((uint32)(PORT_BASE-(0x3fc/4))) + ((uint32)(1 << CH_NO)*4)))

#define PORT_DATA_GROUP_MASK(PORT_BASE,MASK,OFFSET)     (uint32*)((((uint32)(PORT_BASE-(0x3fc/4))) + ((uint32)((MASK << OFFSET)*4))))

Std_levelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    Std_levelType ret;
    Dio_PortType PortId = (Dio_PortType) (ChannelId / 8);
    Dio_ChannelType ChannelPos = (Dio_ChannelType) (ChannelId % 8);

    switch (PortId)
    {
    case Dio_Port_A:
        ret = (Std_levelType) (((*ptr_portA_add) & gau8_Pins_LUT[ChannelPos])
                >> ChannelPos);
        break;

    case Dio_Port_B:
        ret = (Std_levelType) (((*ptr_portB_add) & gau8_Pins_LUT[ChannelPos])
                >> ChannelPos);
        break;

    case Dio_Port_C:
        ret = (Std_levelType) (((*ptr_portC_add) & gau8_Pins_LUT[ChannelPos])
                >> ChannelPos);
        break;

    case Dio_Port_D:
        ret = (Std_levelType) (((*ptr_portD_add) & gau8_Pins_LUT[ChannelPos])
                >> ChannelPos);
        break;

    case Dio_Port_E:
        ret = (Std_levelType) (((*ptr_portE_add) & gau8_Pins_LUT[ChannelPos])
                >> ChannelPos);
        break;

    case Dio_Port_F:
        ret = (Std_levelType) (((*ptr_portF_add) & gau8_Pins_LUT[ChannelPos])
                >> ChannelPos);
        break;

    default:
        break;
    }

    /*TODO: Return the level value of given Channel ***done*/

    return ret;

}


void Dio_WriteChannel(Dio_ChannelType ChannelId, Std_levelType Level)
{
    uint32* ptr_PortBase_Add=0;

    Dio_PortType PortId = (Dio_PortType) (ChannelId / 8);
    Dio_ChannelType ChannelPos = (Dio_ChannelType) ( ChannelId % 8);
    switch (PortId)
    {
    case Dio_Port_A:
        /***return the base address*****/
        ptr_PortBase_Add= (ptr_portA_add-(0x000003fc/4));
        if (Level == STD_high)
        {
            (*(ptr_PortBase_Add + gau8_Pins_LUT[ChannelPos] )) = 0xff;

        }
        else
        {
            (*(ptr_PortBase_Add + gau8_Pins_LUT[ChannelPos] )) = 0x00;
        }
        break;

    case Dio_Port_B:
        ptr_PortBase_Add= (ptr_portB_add-(0x000003fc/4));
        if (Level == STD_high)
        {
            (*(ptr_PortBase_Add + gau8_Pins_LUT[ChannelPos] )) = 0xff;

        }
        else
        {
            (*(ptr_PortBase_Add + gau8_Pins_LUT[ChannelPos] )) = 0x00;
        }
        break;

    case Dio_Port_C:
        ptr_PortBase_Add= (ptr_portC_add-(0x000003fc/4));
        if (Level == STD_high)
        {
            (*(ptr_PortBase_Add + gau8_Pins_LUT[ChannelPos] )) = 0xff;

        }
        else
        {
            (*(ptr_PortBase_Add + gau8_Pins_LUT[ChannelPos] )) = 0x00;
        }
        break;

    case Dio_Port_D:
        ptr_PortBase_Add= (ptr_portD_add-(0x000003fc/4));
        if (Level == STD_high)
        {
            (*(ptr_PortBase_Add + gau8_Pins_LUT[ChannelPos] )) = 0xff;

        }
        else
        {
            (*(ptr_PortBase_Add + gau8_Pins_LUT[ChannelPos] )) = 0x00;
        }
        break;

    case Dio_Port_E:
        ptr_PortBase_Add= (ptr_portE_add-(0x000003fc/4));
        if (Level == STD_high)
        {
            (*(ptr_PortBase_Add + gau8_Pins_LUT[ChannelPos] )) = 0xff;

        }
        else
        {
            (*(ptr_PortBase_Add + gau8_Pins_LUT[ChannelPos] )) = 0x00;
        }
        break;

    case Dio_Port_F:
        ptr_PortBase_Add= (ptr_portF_add-(0x000003fc/4));
        if (Level == STD_high)
        {
            (*(ptr_PortBase_Add + gau8_Pins_LUT[ChannelPos] )) = 0xff;

        }
        else
        {
            (*(ptr_PortBase_Add + gau8_Pins_LUT[ChannelPos] )) = 0x00;
        }
        break;

    default:
        break;
    }

    /*TODO: Write the input value in the corresponding ChannelId */
}

Dio_PortLevelType Dio_ReadPort( Dio_PortType PortId ){
    Dio_PortLevelType ret;

    switch (PortId)
    {
    case Dio_Port_A:
        ret = *ptr_portA_add;
        break;

    case Dio_Port_B:
        ret = *ptr_portB_add;
        break;

    case Dio_Port_C:
        ret = *ptr_portC_add;
        break;

    case Dio_Port_D:
        ret = *ptr_portD_add;
        break;

    case Dio_Port_E:
        ret = *ptr_portE_add;
        break;

    case Dio_Port_F:
        ret = *ptr_portF_add;
        break;

    default:
        break;
    }

    /*TODO: Return the Port Value*/

    return ret;
}
void Dio_WritePort( Dio_PortType PortId, Dio_PortLevelType Level )
{
    switch (PortId)
    {
    case Dio_Port_A:
        *ptr_portA_add = Level;
        break;

    case Dio_Port_B:
        *ptr_portB_add = Level;
        break;

    case Dio_Port_C:
        *ptr_portC_add = Level;
        break;

    case Dio_Port_D:
        *ptr_portD_add = Level;
        break;

    case Dio_Port_E:
        *ptr_portE_add = Level;
        break;

    case Dio_Port_F:
        *ptr_portF_add = Level;
        break;

    default:
        break;
    }

    /*TODO: Write the input value in the corresponding PortId */

}





void Dio_FlipChannel(Dio_ChannelType ChannelId)
{

    Dio_PortType PortId = (Dio_PortType) (ChannelId / 8);
    Dio_ChannelType ChannelPos = (Dio_ChannelType) (ChannelId % 8);

    switch (PortId)
    {

    case Dio_Port_A:
        *ptr_portA_add ^= (gau8_Pins_LUT[ChannelPos]);
        break;
    case Dio_Port_B:
        *ptr_portB_add ^= (gau8_Pins_LUT[ChannelPos]);
        break;
    case Dio_Port_C:
        *ptr_portC_add ^= (gau8_Pins_LUT[ChannelPos]);
        break;
    case Dio_Port_D:
        *ptr_portD_add ^= (gau8_Pins_LUT[ChannelPos]);
        break;
    case Dio_Port_E:
        *ptr_portE_add ^= (gau8_Pins_LUT[ChannelPos]);
        break;
    case Dio_Port_F:
        *ptr_portF_add ^= (gau8_Pins_LUT[ChannelPos]);
        break;
    default:
        break;

    }

    /* TODO: toggle the corresponding ChannelId */
}
void Dio_FlipPort(Dio_PortType PortId)
{

    switch (PortId)
    {
    case Dio_Port_A:
        *ptr_portA_add = (*ptr_portA_add) ^ 0XFF;
        break;

    case Dio_Port_B:
        *ptr_portB_add ^= 0XFF;
        break;

    case Dio_Port_C:
        *ptr_portC_add ^= 0XFF;
        break;

    case Dio_Port_D:
        *ptr_portD_add ^= 0XFF;
        break;

    case Dio_Port_E:
        *ptr_portE_add ^= 0XFF;
        break;

    case Dio_Port_F:
        *ptr_portF_add ^= 0XFF;
        break;

    default:
        break;
    }

    /*TODO: toggle the port value */

}

void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level)
{

    uint8 arr_iterator = 0;
    for (arr_iterator = 0; arr_iterator < 1; arr_iterator++)
    {
        switch (ChannelGroupIdPtr[arr_iterator].port)
        {
        case Dio_Port_A:

            *PORT_DATA_GROUP_MASK(ptr_portA_add, ChannelGroupIdPtr[arr_iterator].mask,
                                  ChannelGroupIdPtr[arr_iterator].offset) = Level;
            break;

        case Dio_Port_B:
            *PORT_DATA_GROUP_MASK(ptr_portB_add, ChannelGroupIdPtr[arr_iterator].mask,
                                  ChannelGroupIdPtr[arr_iterator].offset) = Level;
            break;

        case Dio_Port_C:
            *PORT_DATA_GROUP_MASK(ptr_portC_add, ChannelGroupIdPtr[arr_iterator].mask,
                                  ChannelGroupIdPtr[arr_iterator].offset) = Level;
            break;

        case Dio_Port_D:
            *PORT_DATA_GROUP_MASK(ptr_portD_add, ChannelGroupIdPtr[arr_iterator].mask,
                                  ChannelGroupIdPtr[arr_iterator].offset) = Level;
            break;

        case Dio_Port_E:
            *PORT_DATA_GROUP_MASK(ptr_portE_add, ChannelGroupIdPtr[arr_iterator].mask,
                                  ChannelGroupIdPtr[arr_iterator].offset) = Level;
            break;

        case Dio_Port_F:
            *PORT_DATA_GROUP_MASK(ptr_portF_add, ChannelGroupIdPtr[arr_iterator].mask,
                                  ChannelGroupIdPtr[arr_iterator].offset) = Level;
            break;

        default:
            break;
        }
    }
    /*TODO: Write the input value in the corresponding ChannelId */
}



Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr)
{
    uint8 data = 0;
    uint8 arr_iterator = 0;
    for (arr_iterator = 0; arr_iterator < 1; arr_iterator++)
    {
        switch (ChannelGroupIdPtr[arr_iterator].port)
        {
        case Dio_Port_A:

            data = *PORT_DATA_GROUP_MASK(ptr_portA_add, ChannelGroupIdPtr[arr_iterator].mask,
                                  ChannelGroupIdPtr[arr_iterator].offset);
            break;

        case Dio_Port_B:
            data = *PORT_DATA_GROUP_MASK(ptr_portB_add, ChannelGroupIdPtr[arr_iterator].mask,
                                  ChannelGroupIdPtr[arr_iterator].offset);
            break;

        case Dio_Port_C:
            data = *PORT_DATA_GROUP_MASK(ptr_portC_add, ChannelGroupIdPtr[arr_iterator].mask,
                                  ChannelGroupIdPtr[arr_iterator].offset);
            break;

        case Dio_Port_D:
            data = *PORT_DATA_GROUP_MASK(ptr_portD_add, ChannelGroupIdPtr[arr_iterator].mask,
                                  ChannelGroupIdPtr[arr_iterator].offset);
            break;

        case Dio_Port_E:
            data = *PORT_DATA_GROUP_MASK(ptr_portE_add, ChannelGroupIdPtr[arr_iterator].mask,
                                  ChannelGroupIdPtr[arr_iterator].offset);
            break;

        case Dio_Port_F:
            data = *PORT_DATA_GROUP_MASK(ptr_portF_add, ChannelGroupIdPtr[arr_iterator].mask,
                                  ChannelGroupIdPtr[arr_iterator].offset);
            break;

        default:
            break;
        }
    }
    return data;
}
