/*
 * processor.c
 *
 *  Created on: Dec 2, 2019
 *      Author: Muhammad.Elzeiny
 */
#include "processor.h"


static PROCESSOR_ModeType REQUIRED_MODE =PROCESSOR_ModeNonPrivilege;

void PROCESSOR_switchMode(PROCESSOR_ModeType Mode)
{
    /* TODO use Svc assembly instruction to switch to handler mode*/

    REQUIRED_MODE=Mode;
    __asm(" SVC #1");

}

/*TODO: Put the following function address in Vector table */
void PROCESSOR_SvcHandler(void)
{
    /*TODO use TMPL bit field in CONTROL Register to switch between
     * privilege and non-privilege modes.See page(88) */
    switch(REQUIRED_MODE)
    {
    case PROCESSOR_ModePrivilege:
        __asm(" MOV R0, #0");
        __asm(" MSR CONTROL, R0");
        break;
    case PROCESSOR_ModeNonPrivilege:
        __asm(" MOV R0, #1");
        __asm(" MSR CONTROL, R0");
        break;
    default:
        break;
    }


}

void PROCESSOR_enableGlobalInt(void)
{
    PROCESSOR_switchMode(PROCESSOR_ModePrivilege);
    __asm("    cpsie   i\n");
    PROCESSOR_switchMode(PROCESSOR_ModeNonPrivilege);
}

void PROCESSOR_disableGlobalInt(void)
{
    PROCESSOR_switchMode(PROCESSOR_ModePrivilege);
    __asm("    cpsid   i\n");
    PROCESSOR_switchMode(PROCESSOR_ModeNonPrivilege);
}
