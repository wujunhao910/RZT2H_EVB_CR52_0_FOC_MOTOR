/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2021 Renesas Electronics Corporation. All rights reserved.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 **       DSMIF APIs for RZ/T2 
 **       
 **
 **       revision 0.9 (31.Mar.2021)
 **
 **********************************************************************************************************************/

/*******************************************************************************
Includes <System Includes> , "Project Includes"
*******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "bsp_api.h"
#include "r_dsmif.h"


/*******************************************************************************
Macro definitions
*******************************************************************************/
#define SOFT_WAIT_CNT        (10000u)

#define DSMIF_TRY_COUNT_MAX     (100u)

/*******************************************************************************
Typedef definitions
*******************************************************************************/

/*******************************************************************************
Imported global variables and functions (from other files)
*******************************************************************************/

/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/

/*******************************************************************************
Private variables and functions
*******************************************************************************/
static void soft_wait(void);

static void dsmif_set_filter(uint32_t dsmifunum, uint32_t dsmifchnum, st_dsmif_filter_cfg_t* p_x1cfg);
static void dsmif_set_ovcfilter(uint32_t dsmifunum, uint32_t dsmifchnum, st_dsmif_filter_cfg_t* p_x1cfg);
static void dsmif_get_filter(uint8_t filter_setting, st_dsmif_filter_cfg_t* p_x1cfg);
static void dsmif_set_ovcthres(uint32_t dsmifunum, uint32_t dsmifchnum, st_dsmif_ovc_thres_cfg_t* p_cfg);
static void dsmif_set_scthres(uint32_t dsmifunum, uint32_t dsmifchnum, st_dsmif_sc_thres_cfg_t* p_cfg);


/*******************************************************************************
* Function Name: R_DSMIF_Ctrl
* Description  : control the DSMIF
* Arguments    : uint32_t dsmifunum:Unit number.
*                uint32_t dsmifchnum:Chnnel number.
*                st_dsmif_ctrl_t* param: Pointer to register setting patrameter.
* Return Value : dsmif_err_t
*******************************************************************************/
dsmif_err_t R_DSMIF_Ctrl(uint32_t dsmifunum, uint32_t dsmifchnum, st_dsmif_ctrl_t* param)
{
    if(DSMIF_UNIT0==dsmifunum)
    {
        /* Current Mesurement Clcok Control Register */
        R_DSMIF0->CH[dsmifchnum].DSCMCCR_b.CKDIR=param->mclk_mode; // DSMIF_MCLK_SLAVE
        R_DSMIF0->CH[dsmifchnum].DSCMCCR_b.SEDGE=param->mdat_edge; // DSMIF_MDAT_EDGE_NEG
        R_DSMIF0->CH[dsmifchnum].DSCMCCR_b.CKDIV=param->ckdiv; // 0u
        
        /* Current Mesurement Capture Trigger Control Register */
        R_DSMIF0->CH[dsmifchnum].DSCMCTCR_b.CTSELA=param->captrigA; // DSMIF_CAP_TRIG0
        R_DSMIF0->CH[dsmifchnum].DSCMCTCR_b.CTSELB=param->captrigB; // 0u:no capture
        R_DSMIF0->CH[dsmifchnum].DSCMCTCR_b.DITSEL=param->ditsel;
        R_DSMIF0->CH[dsmifchnum].DSCMCTCR_b.DEDGE=param->dedge;
        
        /* Interrupt Control Register Channel */
        R_DSMIF0->CH[dsmifchnum].DSICR= param->int_en;
    }
    else if(DSMIF_UNIT1==dsmifunum)
    {
        /* Current Mesurement Clcok Control Register */
        R_DSMIF1->CH[dsmifchnum].DSCMCCR_b.CKDIR=param->mclk_mode;
        R_DSMIF1->CH[dsmifchnum].DSCMCCR_b.SEDGE=param->mdat_edge;
        R_DSMIF1->CH[dsmifchnum].DSCMCCR_b.CKDIV=param->ckdiv;
        
        /* Current Mesurement Capture Trigger Control Register */
        R_DSMIF1->CH[dsmifchnum].DSCMCTCR_b.CTSELA=param->captrigA;
        R_DSMIF1->CH[dsmifchnum].DSCMCTCR_b.CTSELB=param->captrigB;
        R_DSMIF1->CH[dsmifchnum].DSCMCTCR_b.DITSEL=param->ditsel;
        R_DSMIF1->CH[dsmifchnum].DSCMCTCR_b.DEDGE=param->dedge;
        
        /* Interrupt Control Register Channel */
        R_DSMIF1->CH[dsmifchnum].DSICR= param->int_en;
    }
    else if(DSMIF_UNIT2==dsmifunum)
    {
        /* Current Mesurement Clcok Control Register */
        R_DSMIF2->CH[dsmifchnum].DSCMCCR_b.CKDIR=param->mclk_mode;
        R_DSMIF2->CH[dsmifchnum].DSCMCCR_b.SEDGE=param->mdat_edge;
        R_DSMIF2->CH[dsmifchnum].DSCMCCR_b.CKDIV=param->ckdiv;
        
        /* Current Mesurement Capture Trigger Control Register */
        R_DSMIF2->CH[dsmifchnum].DSCMCTCR_b.CTSELA=param->captrigA;
        R_DSMIF2->CH[dsmifchnum].DSCMCTCR_b.CTSELB=param->captrigB;
        R_DSMIF2->CH[dsmifchnum].DSCMCTCR_b.DITSEL=param->ditsel;
        R_DSMIF2->CH[dsmifchnum].DSCMCTCR_b.DEDGE=param->dedge;
        
        /* Interrupt Control Register Channel */
        R_DSMIF2->CH[dsmifchnum].DSICR= param->int_en;
    }
    else if(DSMIF_UNIT3==dsmifunum)
    {
        /* Current Mesurement Clcok Control Register */
        R_DSMIF3->CH[dsmifchnum].DSCMCCR_b.CKDIR=param->mclk_mode;
        R_DSMIF3->CH[dsmifchnum].DSCMCCR_b.SEDGE=param->mdat_edge;
        R_DSMIF3->CH[dsmifchnum].DSCMCCR_b.CKDIV=param->ckdiv;
        /* Current Mesurement Capture Trigger Control Register */
        R_DSMIF3->CH[dsmifchnum].DSCMCTCR_b.CTSELA=param->captrigA;
        R_DSMIF3->CH[dsmifchnum].DSCMCTCR_b.CTSELB=param->captrigB;
        R_DSMIF3->CH[dsmifchnum].DSCMCTCR_b.DITSEL=param->ditsel;
        R_DSMIF3->CH[dsmifchnum].DSCMCTCR_b.DEDGE=param->dedge;
        /* Interrupt Control Register Channel */
        R_DSMIF3->CH[dsmifchnum].DSICR= param->int_en;
    }
    else if(DSMIF_UNIT4==dsmifunum)
    {
        /* Current Mesurement Clcok Control Register */
        R_DSMIF4->CH[dsmifchnum].DSCMCCR_b.CKDIR=param->mclk_mode;
        R_DSMIF4->CH[dsmifchnum].DSCMCCR_b.SEDGE=param->mdat_edge;
        R_DSMIF4->CH[dsmifchnum].DSCMCCR_b.CKDIV=param->ckdiv;
        /* Current Mesurement Capture Trigger Control Register */
        R_DSMIF4->CH[dsmifchnum].DSCMCTCR_b.CTSELA=param->captrigA;
        R_DSMIF4->CH[dsmifchnum].DSCMCTCR_b.CTSELB=param->captrigB;
        R_DSMIF4->CH[dsmifchnum].DSCMCTCR_b.DITSEL=param->ditsel;
        R_DSMIF4->CH[dsmifchnum].DSCMCTCR_b.DEDGE=param->dedge;
        /* Interrupt Control Register Channel */
        R_DSMIF4->CH[dsmifchnum].DSICR= param->int_en;
    }
    else if(DSMIF_UNIT5==dsmifunum)
    {
        /* Current Mesurement Clcok Control Register */
        R_DSMIF5->CH[dsmifchnum].DSCMCCR_b.CKDIR=param->mclk_mode;
        R_DSMIF5->CH[dsmifchnum].DSCMCCR_b.SEDGE=param->mdat_edge;
        R_DSMIF5->CH[dsmifchnum].DSCMCCR_b.CKDIV=param->ckdiv;
        /* Current Mesurement Capture Trigger Control Register */
        R_DSMIF5->CH[dsmifchnum].DSCMCTCR_b.CTSELA=param->captrigA;
        R_DSMIF5->CH[dsmifchnum].DSCMCTCR_b.CTSELB=param->captrigB;
        R_DSMIF5->CH[dsmifchnum].DSCMCTCR_b.DITSEL=param->ditsel;
        R_DSMIF5->CH[dsmifchnum].DSCMCTCR_b.DEDGE=param->dedge;
        /* Interrupt Control Register Channel */
        R_DSMIF5->CH[dsmifchnum].DSICR= param->int_en;
    }
    else if(DSMIF_UNIT6==dsmifunum)
    {
        /* Current Mesurement Clcok Control Register */
        R_DSMIF6->CH[dsmifchnum].DSCMCCR_b.CKDIR=param->mclk_mode;
        R_DSMIF6->CH[dsmifchnum].DSCMCCR_b.SEDGE=param->mdat_edge;
        R_DSMIF6->CH[dsmifchnum].DSCMCCR_b.CKDIV=param->ckdiv;
        /* Current Mesurement Capture Trigger Control Register */
        R_DSMIF6->CH[dsmifchnum].DSCMCTCR_b.CTSELA=param->captrigA;
        R_DSMIF6->CH[dsmifchnum].DSCMCTCR_b.CTSELB=param->captrigB;
        R_DSMIF6->CH[dsmifchnum].DSCMCTCR_b.DITSEL=param->ditsel;
        R_DSMIF6->CH[dsmifchnum].DSCMCTCR_b.DEDGE=param->dedge;
        /* Interrupt Control Register Channel */
        R_DSMIF6->CH[dsmifchnum].DSICR= param->int_en;
    }
    else if(DSMIF_UNIT7==dsmifunum)
    {
        /* Current Mesurement Clcok Control Register */
        R_DSMIF7->CH[dsmifchnum].DSCMCCR_b.CKDIR=param->mclk_mode;
        R_DSMIF7->CH[dsmifchnum].DSCMCCR_b.SEDGE=param->mdat_edge;
        R_DSMIF7->CH[dsmifchnum].DSCMCCR_b.CKDIV=param->ckdiv;
        /* Current Mesurement Capture Trigger Control Register */
        R_DSMIF7->CH[dsmifchnum].DSCMCTCR_b.CTSELA=param->captrigA;
        R_DSMIF7->CH[dsmifchnum].DSCMCTCR_b.CTSELB=param->captrigB;
        R_DSMIF7->CH[dsmifchnum].DSCMCTCR_b.DITSEL=param->ditsel;
        R_DSMIF7->CH[dsmifchnum].DSCMCTCR_b.DEDGE=param->dedge;
        /* Interrupt Control Register Channel */
        R_DSMIF7->CH[dsmifchnum].DSICR= param->int_en;
    }
    else if(DSMIF_UNIT8==dsmifunum)
    {
        /* Current Mesurement Clcok Control Register */
        R_DSMIF8->CH[dsmifchnum].DSCMCCR_b.CKDIR=param->mclk_mode;
        R_DSMIF8->CH[dsmifchnum].DSCMCCR_b.SEDGE=param->mdat_edge;
        R_DSMIF8->CH[dsmifchnum].DSCMCCR_b.CKDIV=param->ckdiv;
        /* Current Mesurement Capture Trigger Control Register */
        R_DSMIF8->CH[dsmifchnum].DSCMCTCR_b.CTSELA=param->captrigA;
        R_DSMIF8->CH[dsmifchnum].DSCMCTCR_b.CTSELB=param->captrigB;
        R_DSMIF8->CH[dsmifchnum].DSCMCTCR_b.DITSEL=param->ditsel;
        R_DSMIF8->CH[dsmifchnum].DSCMCTCR_b.DEDGE=param->dedge;
        /* Interrupt Control Register Channel */
        R_DSMIF8->CH[dsmifchnum].DSICR= param->int_en;
    }
    else if(DSMIF_UNIT9==dsmifunum)
    {
        /* Current Mesurement Clcok Control Register */
        R_DSMIF9->CH[0].DSCMCCR_b.CKDIR=param->mclk_mode;
        R_DSMIF9->CH[0].DSCMCCR_b.SEDGE=param->mdat_edge;
        R_DSMIF9->CH[0].DSCMCCR_b.CKDIV=param->ckdiv;
        /* Current Mesurement Capture Trigger Control Register */
        R_DSMIF9->CH[0].DSCMCTCR_b.CTSELA=param->captrigA;
        R_DSMIF9->CH[0].DSCMCTCR_b.CTSELB=param->captrigB;
        R_DSMIF9->CH[0].DSCMCTCR_b.DITSEL=param->ditsel;
        R_DSMIF9->CH[0].DSCMCTCR_b.DEDGE=param->dedge;
        /* Interrupt Control Register Channel */
        R_DSMIF9->CH[0].DSICR= param->int_en;      
    }
    else
    {
       /* do nothing */
    }
    
    
    return DSMIF_SUCCESS;
}
/*******************************************************************************
End of function R_DSMIF_Ctrl
*******************************************************************************/

/*******************************************************************************
* Function Name: R_DSMIF_Start
* Description  : Start DSMIF filtration
* Arguments    : uint32_t dsmifunum:Unit number.
*                 uint32_t setval: setting value
* Return Value : dsmif_err_t
*******************************************************************************/
dsmif_err_t R_DSMIF_Start(uint32_t dsmifunum, uint32_t setval)
{
    
    /* Channel stop by software */
    if(DSMIF_UNIT0 == dsmifunum)
    {
        R_DSMIF0->DSCSTRTR=setval;
    }
    else if(DSMIF_UNIT1 == dsmifunum)
    {
        R_DSMIF1->DSCSTRTR=setval;
    }
    else if(DSMIF_UNIT2 == dsmifunum)
    {
        R_DSMIF2->DSCSTRTR=setval;      
    }
    else if(DSMIF_UNIT3 == dsmifunum)
    {
        R_DSMIF3->DSCSTRTR=setval;      
    }
    else if(DSMIF_UNIT4 == dsmifunum)
    {
        R_DSMIF4->DSCSTRTR=setval;      
    }
    else if(DSMIF_UNIT5 == dsmifunum)
    {
        R_DSMIF5->DSCSTRTR=setval;      
    }
    else if(DSMIF_UNIT6 == dsmifunum)
    {
        R_DSMIF6->DSCSTRTR=setval;      
    }
    else if(DSMIF_UNIT7 == dsmifunum)
    {
        R_DSMIF7->DSCSTRTR=setval;      
    }
    else if(DSMIF_UNIT8 == dsmifunum)
    {
        R_DSMIF8->DSCSTRTR=setval;      
    }
    else if(DSMIF_UNIT9 == dsmifunum)
    {
        R_DSMIF9->DSCSTRTR=setval;      
    }    
    else
    {
        /* do nothing */
    }
    
    return DSMIF_SUCCESS;
}
/*******************************************************************************
End of function R_DSMIF_Start
*******************************************************************************/

/*******************************************************************************
* Function Name: R_DSMIF_ReadStaus
* Description  : Read DSMIF Channel Error Status
* Arguments    : uint32_t dsmifunum:Unit number.
* Return Value : uint32_t: Channel Error Status
*******************************************************************************/
uint32_t R_DSMIF_ReadStaus(uint32_t dsmifunum)
{
    uint32_t readstatus;

    /* Channel stop by software */
    if(DSMIF_UNIT0 == dsmifunum)
    {
        /* Read Error status */
        readstatus=R_DSMIF0->DSCESR;
        /* Clear Error status */
        R_DSMIF0->DSCESCR |= readstatus;
    }
    else if(DSMIF_UNIT1 == dsmifunum)
    {
        readstatus=R_DSMIF1->DSCESR;
        R_DSMIF1->DSCESCR |= readstatus;
    }
    else if(DSMIF_UNIT2 == dsmifunum)
    {
        readstatus=R_DSMIF2->DSCESR;
        R_DSMIF2->DSCESCR |= readstatus;      
    }
    else if(DSMIF_UNIT3 == dsmifunum)
    {
        readstatus=R_DSMIF3->DSCESR;
        R_DSMIF3->DSCESCR |= readstatus;      
    }
    else if(DSMIF_UNIT4 == dsmifunum)
    {
        readstatus=R_DSMIF4->DSCESR;
        R_DSMIF4->DSCESCR |= readstatus;      
    }
    else if(DSMIF_UNIT5 == dsmifunum)
    {
        readstatus=R_DSMIF5->DSCESR;
        R_DSMIF5->DSCESCR |= readstatus;      
    }
    else if(DSMIF_UNIT6 == dsmifunum)
    {
        readstatus=R_DSMIF6->DSCESR;
        R_DSMIF6->DSCESCR |= readstatus;      
    }
    else if(DSMIF_UNIT7 == dsmifunum)
    {
        readstatus=R_DSMIF7->DSCESR;
        R_DSMIF7->DSCESCR |= readstatus;      
    }
    else if(DSMIF_UNIT8 == dsmifunum)
    {
        readstatus=R_DSMIF8->DSCESR;
        R_DSMIF8->DSCESCR |= readstatus;      
    }
    else if(DSMIF_UNIT9 == dsmifunum)
    {
        readstatus=R_DSMIF9->DSCESR;
        R_DSMIF9->DSCESCR |= readstatus;      
    }
    else
    {
        /* do nothing */
    }
    return readstatus;
}
/*******************************************************************************
End of function R_DSMIF_ReadStaus
*******************************************************************************/

/*******************************************************************************
* Function Name: R_DSMIF_Stop
* Description  : Stop DSMIF filtration
* Arguments    : uint32_t dsmifunum:Unit number.
* Return Value : dsmif_err_t
*******************************************************************************/
dsmif_err_t R_DSMIF_Stop(uint32_t dsmifunum)
{
    uint8_t try_count=0u;
    dsmif_err_t ret = DSMIF_SUCCESS;
    
    /* Channel stop by software */
    if(DSMIF_UNIT0 == dsmifunum)
    {
        R_DSMIF0->DSCSTPTR=0x07u;
        do{
            soft_wait();
            try_count++;
            if(DSMIF_TRY_COUNT_MAX< try_count)
            {
                ret= DSMIF_ERR_TMOUT;
                break;
            }
        }while(0u !=R_DSMIF0->DSCSSR);
        
        /* Disable Overcurrent detection
            of all target channels */
        R_DSMIF0->CH[0].DSODCR=0u;
        R_DSMIF0->CH[1].DSODCR=0u;
        R_DSMIF0->CH[2].DSODCR=0u;
        
        /*  Disable Sum Error detection */
        R_DSMIF0->DSSECR=0u;
    }
    else if(DSMIF_UNIT1 == dsmifunum)
    {
        R_DSMIF1->DSCSTPTR=0x07u;
        do{
            soft_wait();
            try_count++;
            if(DSMIF_TRY_COUNT_MAX< try_count)
            {
                ret= DSMIF_ERR_TMOUT;
                break;
            }
        }while(0u !=R_DSMIF1->DSCSSR);
        R_DSMIF1->CH[0].DSODCR=0u;
        R_DSMIF1->CH[1].DSODCR=0u;
        R_DSMIF1->CH[2].DSODCR=0u;
        R_DSMIF1->DSSECR=0u;
    }
    else if(DSMIF_UNIT2 == dsmifunum)
    {
        R_DSMIF2->DSCSTPTR=0x07u;
        do{
            soft_wait();
            try_count++;
            if(DSMIF_TRY_COUNT_MAX< try_count)
            {
                ret= DSMIF_ERR_TMOUT;
                break;
            }
        }while(0u !=R_DSMIF2->DSCSSR);
        R_DSMIF2->CH[0].DSODCR=0u;
        R_DSMIF2->CH[1].DSODCR=0u;
        R_DSMIF2->CH[2].DSODCR=0u;
        R_DSMIF2->DSSECR=0u;
    }
    else if(DSMIF_UNIT3 == dsmifunum)
    {
        R_DSMIF3->DSCSTPTR=0x07u;
        do{
            soft_wait();
            try_count++;
            if(DSMIF_TRY_COUNT_MAX< try_count)
            {
                ret= DSMIF_ERR_TMOUT;
                break;
            }
        }while(0u !=R_DSMIF3->DSCSSR);
        R_DSMIF3->CH[0].DSODCR=0u;
        R_DSMIF3->CH[1].DSODCR=0u;
        R_DSMIF3->CH[2].DSODCR=0u;
        R_DSMIF3->DSSECR=0u;
    }
    else if(DSMIF_UNIT4 == dsmifunum)
    {
        R_DSMIF4->DSCSTPTR=0x07u;
        do{
            soft_wait();
            try_count++;
            if(DSMIF_TRY_COUNT_MAX< try_count)
            {
                ret= DSMIF_ERR_TMOUT;
                break;
            }
        }while(0u !=R_DSMIF4->DSCSSR);
        R_DSMIF4->CH[0].DSODCR=0u;
        R_DSMIF4->CH[1].DSODCR=0u;
        R_DSMIF4->CH[2].DSODCR=0u;
        R_DSMIF4->DSSECR=0u;
    }
    else if(DSMIF_UNIT5 == dsmifunum)
    {
        R_DSMIF5->DSCSTPTR=0x07u;
        do{
            soft_wait();
            try_count++;
            if(DSMIF_TRY_COUNT_MAX< try_count)
            {
                ret= DSMIF_ERR_TMOUT;
                break;
            }
        }while(0u !=R_DSMIF5->DSCSSR);
        R_DSMIF5->CH[0].DSODCR=0u;
        R_DSMIF5->CH[1].DSODCR=0u;
        R_DSMIF5->CH[2].DSODCR=0u;
        R_DSMIF5->DSSECR=0u;
    }
    else if(DSMIF_UNIT6 == dsmifunum)
    {
        R_DSMIF6->DSCSTPTR=0x07u;
        do{
            soft_wait();
            try_count++;
            if(DSMIF_TRY_COUNT_MAX< try_count)
            {
                ret= DSMIF_ERR_TMOUT;
                break;
            }
        }while(0u !=R_DSMIF6->DSCSSR);
        R_DSMIF6->CH[0].DSODCR=0u;
        R_DSMIF6->CH[1].DSODCR=0u;
        R_DSMIF6->CH[2].DSODCR=0u;
        R_DSMIF6->DSSECR=0u;
    }
    else if(DSMIF_UNIT7 == dsmifunum)
    {
        R_DSMIF7->DSCSTPTR=0x07u;
        do{
            soft_wait();
            try_count++;
            if(DSMIF_TRY_COUNT_MAX< try_count)
            {
                ret= DSMIF_ERR_TMOUT;
                break;
            }
        }while(0u !=R_DSMIF7->DSCSSR);
        R_DSMIF7->CH[0].DSODCR=0u;
        R_DSMIF7->CH[1].DSODCR=0u;
        R_DSMIF7->CH[2].DSODCR=0u;
        R_DSMIF7->DSSECR=0u;
    }
    else if(DSMIF_UNIT8 == dsmifunum)
    {
        R_DSMIF8->DSCSTPTR=0x07u;
        do{
            soft_wait();
            try_count++;
            if(DSMIF_TRY_COUNT_MAX< try_count)
            {
                ret= DSMIF_ERR_TMOUT;
                break;
            }
        }while(0u !=R_DSMIF8->DSCSSR);
        R_DSMIF8->CH[0].DSODCR=0u;
        R_DSMIF8->CH[1].DSODCR=0u;
        R_DSMIF8->CH[2].DSODCR=0u;
        R_DSMIF8->DSSECR=0u;
    }
    else if(DSMIF_UNIT9 == dsmifunum)
    {
        R_DSMIF9->DSCSTPTR=0x07u;
        do{
            soft_wait();
            try_count++;
            if(DSMIF_TRY_COUNT_MAX< try_count)
            {
                ret= DSMIF_ERR_TMOUT;
                break;
            }
        }while(0u !=R_DSMIF9->DSCSSR);
        R_DSMIF9->CH[0].DSODCR=0u;
        R_DSMIF9->DSSECR=0u;
    }
    else
    {
        /* do nothing */
    }
    
    return ret;
}
/*******************************************************************************
End of function R_DSMIF_Stop
*******************************************************************************/

/*******************************************************************************
* Function Name: R_DSMIF_ReadCapDataA
* Description  : read capture data A register
* Arguments    : uint32_t dsmifunum:Unit number.
*                uint32_t dsmifchnum:Chnnel number.
* Return Value : read_data
*                    capture data A
*******************************************************************************/
uint16_t R_DSMIF_ReadCapDataA(uint32_t dsmifunum, uint32_t dsmifchnum)
{
    uint16_t read_data;
    if(DSMIF_UNIT0==dsmifunum)
    {
        read_data=R_DSMIF0->CH[dsmifchnum].DSCCDRA;
    }
    else if(DSMIF_UNIT1==dsmifunum)
    {
        read_data=R_DSMIF1->CH[dsmifchnum].DSCCDRA;
    }
    else if(DSMIF_UNIT2==dsmifunum)
    {
        read_data=R_DSMIF2->CH[dsmifchnum].DSCCDRA;      
    }
    else if(DSMIF_UNIT3==dsmifunum)
    {
        read_data=R_DSMIF3->CH[dsmifchnum].DSCCDRA;      
    }
    else if(DSMIF_UNIT4==dsmifunum)
    {
        read_data=R_DSMIF4->CH[dsmifchnum].DSCCDRA;      
    }    
    else if(DSMIF_UNIT5==dsmifunum)
    {
        read_data=R_DSMIF5->CH[dsmifchnum].DSCCDRA;      
    }    
    else if(DSMIF_UNIT6==dsmifunum)
    {
        read_data=R_DSMIF6->CH[dsmifchnum].DSCCDRA;      
    }
    else if(DSMIF_UNIT7==dsmifunum)
    {
        read_data=R_DSMIF7->CH[dsmifchnum].DSCCDRA;      
    }
    else if(DSMIF_UNIT8==dsmifunum)
    {
        read_data=R_DSMIF8->CH[dsmifchnum].DSCCDRA;      
    }
    else if(DSMIF_UNIT9==dsmifunum)
    {
        read_data=R_DSMIF9->CH[0].DSCCDRA;      
    }
    else 
    {
        /* do nothing */
    }
    return read_data;
}

/*******************************************************************************
End of function R_DSMIF_ReadCapDataA
*******************************************************************************/

/*******************************************************************************
* Function Name: R_DSMIF_SetFilter
* Description  : configure filter setting
* Arguments    : x1_setting
*                    filter setting for X1DATA register
*                x2_setting
*                    filter setting for X2DATA register
* Return Value : none
*******************************************************************************/
void R_DSMIF_SetFilter(uint32_t dsmifunum, uint32_t dsmifchnum, uint8_t filter_setting)
{
    st_dsmif_filter_cfg_t filter_cfg_x1;
    
    dsmif_get_filter(filter_setting, &filter_cfg_x1);

    /* set filter */
    dsmif_set_filter(dsmifunum, dsmifchnum, &filter_cfg_x1);
    
}
/*******************************************************************************
End of function R_DSMIF_SetFilter
*******************************************************************************/

/*******************************************************************************
* Function Name: R_DSMIF_OvcSCCtrl
* Description  : read capture data A register
* Arguments    : uint32_t dsmifunum:Unit number.
*                uint32_t dsmifchnum:Chnnel number.
* Return Value : read_data
*                    capture data A
*******************************************************************************/
dsmif_err_t R_DSMIF_OvcSCCtrl(uint32_t dsmifunum, uint32_t dsmifchnum, st_dsmif_ovcsc_ctrl_t* param)
{
    st_dsmif_filter_cfg_t filter_cfg_x1;
    
    /* Set each channel's Overcurrent detection Low/High Threshold. */
    dsmif_set_ovcthres(dsmifunum, dsmifchnum, &param->ovc_thres);
    
    
    /* Set each channel's Overcurrent detection filter setting. */
    dsmif_get_filter(param->filter_setting, &filter_cfg_x1);
    
    dsmif_set_ovcfilter(dsmifunum, dsmifchnum, &filter_cfg_x1);
    
    /* Set each channel's Short Circuit detection Low/High Threshold. */
    dsmif_set_scthres(dsmifunum, dsmifchnum, &param->sc_thres);

    return DSMIF_SUCCESS;
}

/*******************************************************************************
End of function R_DSMIF_OvcSCCtrl
*******************************************************************************/

/*******************************************************************************
* Function Name: R_DSMIF_OvcSCCtrlValid
* Description  : read capture data A register
* Arguments    : uint32_t dsmifunum:Unit number.
*                uint32_t dsmifchnum:Chnnel number.
* Return Value : read_data
*                    capture data A
*******************************************************************************/
dsmif_err_t R_DSMIF_OvcSCCtrlValid(uint32_t dsmifunum, uint32_t dsmifchnum)
{
    /* Set each channel's Overcurrent detection control bit. */
    if(DSMIF_UNIT0==dsmifunum)
    {
        R_DSMIF0->CH[dsmifchnum].DSODCR=DSMIF_OVC_VALID; // ODEL0 and ODEH0 are 1.
    }
    else if(DSMIF_UNIT1==dsmifunum)
    {
        R_DSMIF1->CH[dsmifchnum].DSODCR=DSMIF_OVC_VALID;
    }
    else if(DSMIF_UNIT2==dsmifunum)
    {
        R_DSMIF2->CH[dsmifchnum].DSODCR=DSMIF_OVC_VALID;      
    }
    else if(DSMIF_UNIT3==dsmifunum)
    {
        R_DSMIF3->CH[dsmifchnum].DSODCR=DSMIF_OVC_VALID;      
    }
    else if(DSMIF_UNIT4==dsmifunum)
    {
        R_DSMIF4->CH[dsmifchnum].DSODCR=DSMIF_OVC_VALID;      
    }
    else if(DSMIF_UNIT5==dsmifunum)
    {
        R_DSMIF5->CH[dsmifchnum].DSODCR=DSMIF_OVC_VALID;      
    }
    else if(DSMIF_UNIT6==dsmifunum)
    {
        R_DSMIF6->CH[dsmifchnum].DSODCR=DSMIF_OVC_VALID;      
    }
    else if(DSMIF_UNIT7==dsmifunum)
    {
        R_DSMIF7->CH[dsmifchnum].DSODCR=DSMIF_OVC_VALID;      
    }
    else if(DSMIF_UNIT8==dsmifunum)
    {
        R_DSMIF8->CH[dsmifchnum].DSODCR=DSMIF_OVC_VALID;      
    }
    else if(DSMIF_UNIT9==dsmifunum)
    {
        R_DSMIF9->CH[0].DSODCR=DSMIF_OVC_VALID;      
    }
    else
    {
        /* do nothing */
    }

    /* Set each channel's Short Circuit detection control bit. */
    if(DSMIF_UNIT0==dsmifunum)
    {
        R_DSMIF0->CH[dsmifchnum].DSEDCR=DSMIF_SC_VALID; // SDE(Short Cicuit Detection enable bit) is 1.
    }
    else if(DSMIF_UNIT1==dsmifunum)
    {
        R_DSMIF1->CH[dsmifchnum].DSEDCR=DSMIF_SC_VALID;
    }
    else if(DSMIF_UNIT2==dsmifunum)
    {
        R_DSMIF2->CH[dsmifchnum].DSEDCR=DSMIF_SC_VALID;      
    }
    else if(DSMIF_UNIT3==dsmifunum)
    {
        R_DSMIF3->CH[dsmifchnum].DSEDCR=DSMIF_SC_VALID;      
    }
    else if(DSMIF_UNIT4==dsmifunum)
    {
        R_DSMIF4->CH[dsmifchnum].DSEDCR=DSMIF_SC_VALID;      
    }
    else if(DSMIF_UNIT5==dsmifunum)
    {
        R_DSMIF5->CH[dsmifchnum].DSEDCR=DSMIF_SC_VALID;      
    }
    else if(DSMIF_UNIT5==dsmifunum)
    {
        R_DSMIF5->CH[dsmifchnum].DSEDCR=DSMIF_SC_VALID;      
    }
    else if(DSMIF_UNIT6==dsmifunum)
    {
        R_DSMIF6->CH[dsmifchnum].DSEDCR=DSMIF_SC_VALID;      
    }
    else if(DSMIF_UNIT7==dsmifunum)
    {
        R_DSMIF7->CH[dsmifchnum].DSEDCR=DSMIF_SC_VALID;      
    }
    else if(DSMIF_UNIT8==dsmifunum)
    {
        R_DSMIF8->CH[dsmifchnum].DSEDCR=DSMIF_SC_VALID;      
    }
    else if(DSMIF_UNIT9==dsmifunum)
    {
        R_DSMIF9->CH[0].DSEDCR=DSMIF_SC_VALID;      
    }
    else
    {
        /* do nothing */
    }

    return DSMIF_SUCCESS;
}
/*******************************************************************************
End of function R_DSMIF_OvcSCCtrlValid
*******************************************************************************/


/*******************************************************************************
Private variables and functions
*******************************************************************************/


/*******************************************************************************
* Function Name: soft_wait
* Description  : soft wait function using NOP
* Arguments    : none
* Return Value : none
*******************************************************************************/
static void soft_wait(void)
{
    uint32_t loop;

#ifdef  __ICCARM__
    asm volatile ("dsb");
#elif  __GNUC__
        __asm__("dsb");
#endif

    for (loop = 0u; loop < SOFT_WAIT_CNT ; loop++ )
    {
#ifdef __CC_ARM
        __asm("nop");
#elif  __ICCARM__
        asm volatile("nop");
#elif  __GNUC__
        __asm__("nop");
#endif
    }
}
/*******************************************************************************
 End of function soft_wait
*******************************************************************************/

/*******************************************************************************
* Function Name: dsmif_set_filter
* Description  : set filter to register
* Arguments    : uint32_t dsmifunum:Unit number.
*              : uint32_t dsmifchnum:Chnnel number.
*              : p_x1cfg: pointer to filter setting struct
* Return Value : none
*******************************************************************************/
static void dsmif_set_filter(uint32_t dsmifunum, uint32_t dsmifchnum, st_dsmif_filter_cfg_t* p_x1cfg)
{
    /* set X1DATA register */
    if(DSMIF_UNIT0==dsmifunum)
    {
        R_DSMIF0->CH[dsmifchnum].DSCMFCR_b.CMSINC=p_x1cfg->sincsel;// DSCMFCR: Current Measurement Filter Control Register
        R_DSMIF0->CH[dsmifchnum].DSCMFCR_b.CMDEC=p_x1cfg->wordgen;
        R_DSMIF0->CH[dsmifchnum].DSCMFCR_b.CMSH=p_x1cfg->bitshift;
    }
    else if(DSMIF_UNIT1==dsmifunum)
    {
        R_DSMIF1->CH[dsmifchnum].DSCMFCR_b.CMSINC=p_x1cfg->sincsel;
        R_DSMIF1->CH[dsmifchnum].DSCMFCR_b.CMDEC=p_x1cfg->wordgen;
        R_DSMIF1->CH[dsmifchnum].DSCMFCR_b.CMSH=p_x1cfg->bitshift;
    }
    else if(DSMIF_UNIT2==dsmifunum)
    {
        R_DSMIF2->CH[dsmifchnum].DSCMFCR_b.CMSINC=p_x1cfg->sincsel;
        R_DSMIF2->CH[dsmifchnum].DSCMFCR_b.CMDEC=p_x1cfg->wordgen;
        R_DSMIF2->CH[dsmifchnum].DSCMFCR_b.CMSH=p_x1cfg->bitshift;      
    }
    else if(DSMIF_UNIT3==dsmifunum)
    {
        R_DSMIF3->CH[dsmifchnum].DSCMFCR_b.CMSINC=p_x1cfg->sincsel;
        R_DSMIF3->CH[dsmifchnum].DSCMFCR_b.CMDEC=p_x1cfg->wordgen;
        R_DSMIF3->CH[dsmifchnum].DSCMFCR_b.CMSH=p_x1cfg->bitshift;      
    }
    else if(DSMIF_UNIT4==dsmifunum)
    {
        R_DSMIF4->CH[dsmifchnum].DSCMFCR_b.CMSINC=p_x1cfg->sincsel;
        R_DSMIF4->CH[dsmifchnum].DSCMFCR_b.CMDEC=p_x1cfg->wordgen;
        R_DSMIF4->CH[dsmifchnum].DSCMFCR_b.CMSH=p_x1cfg->bitshift;      
    }
    else if(DSMIF_UNIT5==dsmifunum)
    {
        R_DSMIF5->CH[dsmifchnum].DSCMFCR_b.CMSINC=p_x1cfg->sincsel;
        R_DSMIF5->CH[dsmifchnum].DSCMFCR_b.CMDEC=p_x1cfg->wordgen;
        R_DSMIF5->CH[dsmifchnum].DSCMFCR_b.CMSH=p_x1cfg->bitshift;      
    }
    else if(DSMIF_UNIT6==dsmifunum)
    {
        R_DSMIF6->CH[dsmifchnum].DSCMFCR_b.CMSINC=p_x1cfg->sincsel;
        R_DSMIF6->CH[dsmifchnum].DSCMFCR_b.CMDEC=p_x1cfg->wordgen;
        R_DSMIF6->CH[dsmifchnum].DSCMFCR_b.CMSH=p_x1cfg->bitshift;      
    }
    else if(DSMIF_UNIT7==dsmifunum)
    {
        R_DSMIF7->CH[dsmifchnum].DSCMFCR_b.CMSINC=p_x1cfg->sincsel;
        R_DSMIF7->CH[dsmifchnum].DSCMFCR_b.CMDEC=p_x1cfg->wordgen;
        R_DSMIF7->CH[dsmifchnum].DSCMFCR_b.CMSH=p_x1cfg->bitshift;      
    }
    else if(DSMIF_UNIT8==dsmifunum)
    {
        R_DSMIF8->CH[dsmifchnum].DSCMFCR_b.CMSINC=p_x1cfg->sincsel;
        R_DSMIF8->CH[dsmifchnum].DSCMFCR_b.CMDEC=p_x1cfg->wordgen;
        R_DSMIF8->CH[dsmifchnum].DSCMFCR_b.CMSH=p_x1cfg->bitshift;      
    }
    else if(DSMIF_UNIT9==dsmifunum)
    {
        R_DSMIF9->CH[0].DSCMFCR_b.CMSINC=p_x1cfg->sincsel;
        R_DSMIF9->CH[0].DSCMFCR_b.CMDEC=p_x1cfg->wordgen;
        R_DSMIF9->CH[0].DSCMFCR_b.CMSH=p_x1cfg->bitshift;      
    }
    else
    {
      /* do nothing */
    }
    
}
/*******************************************************************************
End of function dsmif_set_filter
*******************************************************************************/

/*******************************************************************************
* Function Name: dsmif_set_ovcfilter
* Description  : set overcurrent detect filter to register
* Arguments    : uint32_t dsmifunum:Unit number.
*              : uint32_t dsmifchnum:Chnnel number.
*              : p_x1cfg: pointer to filter setting struct
* Return Value : none
*******************************************************************************/
static void dsmif_set_ovcfilter(uint32_t dsmifunum, uint32_t dsmifchnum, st_dsmif_filter_cfg_t* p_x1cfg)
{
    /* set X1DATA register */
    if(DSMIF_UNIT0==dsmifunum)
    {
        R_DSMIF0->CH[dsmifchnum].DSOCFCR_b.OCSINC=p_x1cfg->sincsel;// DSOCFCR: Over Current Detect Filter Control Register
        R_DSMIF0->CH[dsmifchnum].DSOCFCR_b.OCDEC=p_x1cfg->wordgen;
        R_DSMIF0->CH[dsmifchnum].DSOCFCR_b.OCSH=p_x1cfg->bitshift;
    }
    else if(DSMIF_UNIT1==dsmifunum)
    {
        R_DSMIF1->CH[dsmifchnum].DSOCFCR_b.OCSINC=p_x1cfg->sincsel;
        R_DSMIF1->CH[dsmifchnum].DSOCFCR_b.OCDEC=p_x1cfg->wordgen;
        R_DSMIF1->CH[dsmifchnum].DSOCFCR_b.OCSH=p_x1cfg->bitshift;
    }
    else if(DSMIF_UNIT2==dsmifunum)
    {
        R_DSMIF2->CH[dsmifchnum].DSOCFCR_b.OCSINC=p_x1cfg->sincsel;
        R_DSMIF2->CH[dsmifchnum].DSOCFCR_b.OCDEC=p_x1cfg->wordgen;
        R_DSMIF2->CH[dsmifchnum].DSOCFCR_b.OCSH=p_x1cfg->bitshift;      
    }
    else if(DSMIF_UNIT3==dsmifunum)
    {
        R_DSMIF3->CH[dsmifchnum].DSOCFCR_b.OCSINC=p_x1cfg->sincsel;
        R_DSMIF3->CH[dsmifchnum].DSOCFCR_b.OCDEC=p_x1cfg->wordgen;
        R_DSMIF3->CH[dsmifchnum].DSOCFCR_b.OCSH=p_x1cfg->bitshift;      
    }
    else if(DSMIF_UNIT4==dsmifunum)
    {
        R_DSMIF4->CH[dsmifchnum].DSOCFCR_b.OCSINC=p_x1cfg->sincsel;
        R_DSMIF4->CH[dsmifchnum].DSOCFCR_b.OCDEC=p_x1cfg->wordgen;
        R_DSMIF4->CH[dsmifchnum].DSOCFCR_b.OCSH=p_x1cfg->bitshift;      
    }
    else if(DSMIF_UNIT5==dsmifunum)
    {
        R_DSMIF5->CH[dsmifchnum].DSOCFCR_b.OCSINC=p_x1cfg->sincsel;
        R_DSMIF5->CH[dsmifchnum].DSOCFCR_b.OCDEC=p_x1cfg->wordgen;
        R_DSMIF5->CH[dsmifchnum].DSOCFCR_b.OCSH=p_x1cfg->bitshift;      
    }
    else if(DSMIF_UNIT6==dsmifunum)
    {
        R_DSMIF6->CH[dsmifchnum].DSOCFCR_b.OCSINC=p_x1cfg->sincsel;
        R_DSMIF6->CH[dsmifchnum].DSOCFCR_b.OCDEC=p_x1cfg->wordgen;
        R_DSMIF6->CH[dsmifchnum].DSOCFCR_b.OCSH=p_x1cfg->bitshift;      
    }
    else if(DSMIF_UNIT7==dsmifunum)
    {
        R_DSMIF7->CH[dsmifchnum].DSOCFCR_b.OCSINC=p_x1cfg->sincsel;
        R_DSMIF7->CH[dsmifchnum].DSOCFCR_b.OCDEC=p_x1cfg->wordgen;
        R_DSMIF7->CH[dsmifchnum].DSOCFCR_b.OCSH=p_x1cfg->bitshift;      
    }
    else if(DSMIF_UNIT8==dsmifunum)
    {
        R_DSMIF8->CH[dsmifchnum].DSOCFCR_b.OCSINC=p_x1cfg->sincsel;
        R_DSMIF8->CH[dsmifchnum].DSOCFCR_b.OCDEC=p_x1cfg->wordgen;
        R_DSMIF8->CH[dsmifchnum].DSOCFCR_b.OCSH=p_x1cfg->bitshift;      
    }
    else if(DSMIF_UNIT9==dsmifunum)
    {
        R_DSMIF9->CH[0].DSOCFCR_b.OCSINC=p_x1cfg->sincsel;
        R_DSMIF9->CH[0].DSOCFCR_b.OCDEC=p_x1cfg->wordgen;
        R_DSMIF9->CH[0].DSOCFCR_b.OCSH=p_x1cfg->bitshift;      
    }
    else
    {
        /* do nothing */
    }
}
/*******************************************************************************
End of function dsmif_set_ovcfilter
*******************************************************************************/


/*******************************************************************************
* Function Name: dsmif_get_filter
* Description  : Get overcurrent detect filter
* Arguments    : uint32_t dsmifunum:Unit number.
*              : uint32_t dsmifchnum:Chnnel number.
*              : p_x1cfg: pointer to filter setting struct
* Return Value : none
*******************************************************************************/
static void dsmif_get_filter(uint8_t filter_setting, st_dsmif_filter_cfg_t* p_x1cfg)
{
    /* filter setting */
    switch(filter_setting)
    {
    case DSMIF_FILTER_SET_0:
        p_x1cfg->sincsel = DSMIF_SINC_3;
        p_x1cfg->wordgen = DSMIF_DIV_MCLK_8;
        p_x1cfg->bitshift = DSMIF_BITSHIFT_8;
        break;
    case DSMIF_FILTER_SET_1:
        p_x1cfg->sincsel = DSMIF_SINC_3;
        p_x1cfg->wordgen = DSMIF_DIV_MCLK_16;
        p_x1cfg->bitshift = DSMIF_BITSHIFT_6;
        break;
    case DSMIF_FILTER_SET_2:
        p_x1cfg->sincsel = DSMIF_SINC_3;
        p_x1cfg->wordgen = DSMIF_DIV_MCLK_32;
        p_x1cfg->bitshift = DSMIF_BITSHIFT_4;
        break;
    case DSMIF_FILTER_SET_3:
        p_x1cfg->sincsel = DSMIF_SINC_3;
        p_x1cfg->wordgen = DSMIF_DIV_MCLK_64;
        p_x1cfg->bitshift = DSMIF_BITSHIFT_2;
        break;
    case DSMIF_FILTER_SET_4:
        p_x1cfg->sincsel = DSMIF_SINC_3;
        p_x1cfg->wordgen = DSMIF_DIV_MCLK_128;
        p_x1cfg->bitshift = DSMIF_BITSHIFT_3;
        break;
    case DSMIF_FILTER_SET_5:
        p_x1cfg->sincsel = DSMIF_SINC_3;
        p_x1cfg->wordgen = DSMIF_DIV_MCLK_256;
        p_x1cfg->bitshift = DSMIF_BITSHIFT_0;
        break;
    case DSMIF_FILTER_SET_6:
        p_x1cfg->sincsel = DSMIF_SINC_2;
        p_x1cfg->wordgen = DSMIF_DIV_MCLK_16;
        p_x1cfg->bitshift = DSMIF_BITSHIFT_9;
        break;
    case DSMIF_FILTER_SET_7:
        p_x1cfg->sincsel = DSMIF_SINC_2;
        p_x1cfg->wordgen = DSMIF_DIV_MCLK_32;
        p_x1cfg->bitshift = DSMIF_BITSHIFT_7;
        break;
    case DSMIF_FILTER_SET_8:
        p_x1cfg->sincsel = DSMIF_SINC_2;
        p_x1cfg->wordgen = DSMIF_DIV_MCLK_64;
        p_x1cfg->bitshift = DSMIF_BITSHIFT_6;
        break;
    case DSMIF_FILTER_SET_9:
        p_x1cfg->sincsel = DSMIF_SINC_2;
        p_x1cfg->wordgen = DSMIF_DIV_MCLK_128;
        p_x1cfg->bitshift = DSMIF_BITSHIFT_5;
        break;
    case DSMIF_FILTER_SET_10:
        p_x1cfg->sincsel = DSMIF_SINC_2;
        p_x1cfg->wordgen = DSMIF_DIV_MCLK_256;
        p_x1cfg->bitshift = DSMIF_BITSHIFT_3;
        break;
    case DSMIF_FILTER_SET_11:
        p_x1cfg->sincsel = DSMIF_SINC_1;
        p_x1cfg->wordgen = DSMIF_DIV_MCLK_32;
        p_x1cfg->bitshift = DSMIF_BITSHIFT_12;
        break;
    case DSMIF_FILTER_SET_12:
        p_x1cfg->sincsel = DSMIF_SINC_1;
        p_x1cfg->wordgen = DSMIF_DIV_MCLK_64;
        p_x1cfg->bitshift = DSMIF_BITSHIFT_11;
        break;
    case DSMIF_FILTER_SET_13:
        p_x1cfg->sincsel = DSMIF_SINC_1;
        p_x1cfg->wordgen = DSMIF_DIV_MCLK_128;
        p_x1cfg->bitshift = DSMIF_BITSHIFT_10;
        break;
    case DSMIF_FILTER_SET_14:
        p_x1cfg->sincsel = DSMIF_SINC_1;
        p_x1cfg->wordgen = DSMIF_DIV_MCLK_256;
        p_x1cfg->bitshift = DSMIF_BITSHIFT_9;
        break;
    default:
        /* In case of an abnormal parameter, be initialized as No.0. */
        p_x1cfg->sincsel = DSMIF_SINC_3;
        p_x1cfg->wordgen = DSMIF_DIV_MCLK_8;
        p_x1cfg->bitshift = DSMIF_BITSHIFT_8;
        break;
    }

}
/*******************************************************************************
End of function dsmif_get_filter
*******************************************************************************/

/*******************************************************************************
* Function Name: dsmif_set_ovcthres
* Description  : set overcurrent detection threshold
* Arguments    : uint32_t dsmifunum:Unit number.
*              : uint32_t dsmifchnum:Chnnel number.
*              : p_cfg: pointer to overcurrent detection threshold struct
* Return Value : none
*******************************************************************************/
static void dsmif_set_ovcthres(uint32_t dsmifunum, uint32_t dsmifchnum, st_dsmif_ovc_thres_cfg_t* p_cfg)
{
    /* set X1DATA register */
    if(DSMIF_UNIT0==dsmifunum)
    {
        R_DSMIF0->CH[dsmifchnum].TR[0].DSOCL= p_cfg->low; // DSOCL: Over Current Low
        R_DSMIF0->CH[dsmifchnum].TR[1].DSOCL= p_cfg->low;
        R_DSMIF0->CH[dsmifchnum].TR[2].DSOCL= p_cfg->low;
        R_DSMIF0->CH[dsmifchnum].TR[0].DSOCH= p_cfg->high;// DSOCH: Over Current Highs
        R_DSMIF0->CH[dsmifchnum].TR[1].DSOCH= p_cfg->high;
        R_DSMIF0->CH[dsmifchnum].TR[2].DSOCH= p_cfg->high;
    }
    else if(DSMIF_UNIT1==dsmifunum)
    {
        R_DSMIF1->CH[dsmifchnum].TR[0].DSOCL= p_cfg->low;
        R_DSMIF1->CH[dsmifchnum].TR[1].DSOCL= p_cfg->low;
        R_DSMIF1->CH[dsmifchnum].TR[2].DSOCL= p_cfg->low;
        R_DSMIF1->CH[dsmifchnum].TR[0].DSOCH= p_cfg->high;
        R_DSMIF1->CH[dsmifchnum].TR[1].DSOCH= p_cfg->high;
        R_DSMIF1->CH[dsmifchnum].TR[2].DSOCH= p_cfg->high;
    }
    else if(DSMIF_UNIT2==dsmifunum)
    {
        R_DSMIF2->CH[dsmifchnum].TR[0].DSOCL= p_cfg->low;
        R_DSMIF2->CH[dsmifchnum].TR[1].DSOCL= p_cfg->low;
        R_DSMIF2->CH[dsmifchnum].TR[2].DSOCL= p_cfg->low;
        R_DSMIF2->CH[dsmifchnum].TR[0].DSOCH= p_cfg->high;
        R_DSMIF2->CH[dsmifchnum].TR[1].DSOCH= p_cfg->high;
        R_DSMIF2->CH[dsmifchnum].TR[2].DSOCH= p_cfg->high;
    }
    else if(DSMIF_UNIT3==dsmifunum)
    {
        R_DSMIF3->CH[dsmifchnum].TR[0].DSOCL= p_cfg->low;
        R_DSMIF3->CH[dsmifchnum].TR[1].DSOCL= p_cfg->low;
        R_DSMIF3->CH[dsmifchnum].TR[2].DSOCL= p_cfg->low;
        R_DSMIF3->CH[dsmifchnum].TR[0].DSOCH= p_cfg->high;
        R_DSMIF3->CH[dsmifchnum].TR[1].DSOCH= p_cfg->high;
        R_DSMIF3->CH[dsmifchnum].TR[2].DSOCH= p_cfg->high;
    }
    else if(DSMIF_UNIT4==dsmifunum)
    {
        R_DSMIF4->CH[dsmifchnum].TR[0].DSOCL= p_cfg->low;
        R_DSMIF4->CH[dsmifchnum].TR[1].DSOCL= p_cfg->low;
        R_DSMIF4->CH[dsmifchnum].TR[2].DSOCL= p_cfg->low;
        R_DSMIF4->CH[dsmifchnum].TR[0].DSOCH= p_cfg->high;
        R_DSMIF4->CH[dsmifchnum].TR[1].DSOCH= p_cfg->high;
        R_DSMIF4->CH[dsmifchnum].TR[2].DSOCH= p_cfg->high;
    }
    else if(DSMIF_UNIT5==dsmifunum)
    {
        R_DSMIF5->CH[dsmifchnum].TR[0].DSOCL= p_cfg->low;
        R_DSMIF5->CH[dsmifchnum].TR[1].DSOCL= p_cfg->low;
        R_DSMIF5->CH[dsmifchnum].TR[2].DSOCL= p_cfg->low;
        R_DSMIF5->CH[dsmifchnum].TR[0].DSOCH= p_cfg->high;
        R_DSMIF5->CH[dsmifchnum].TR[1].DSOCH= p_cfg->high;
        R_DSMIF5->CH[dsmifchnum].TR[2].DSOCH= p_cfg->high;
    }
    else if(DSMIF_UNIT6==dsmifunum)
    {
        R_DSMIF6->CH[dsmifchnum].TR[0].DSOCL= p_cfg->low;
        R_DSMIF6->CH[dsmifchnum].TR[1].DSOCL= p_cfg->low;
        R_DSMIF6->CH[dsmifchnum].TR[2].DSOCL= p_cfg->low;
        R_DSMIF6->CH[dsmifchnum].TR[0].DSOCH= p_cfg->high;
        R_DSMIF6->CH[dsmifchnum].TR[1].DSOCH= p_cfg->high;
        R_DSMIF6->CH[dsmifchnum].TR[2].DSOCH= p_cfg->high;
    }
    else if(DSMIF_UNIT7==dsmifunum)
    {
        R_DSMIF7->CH[dsmifchnum].TR[0].DSOCL= p_cfg->low;
        R_DSMIF7->CH[dsmifchnum].TR[1].DSOCL= p_cfg->low;
        R_DSMIF7->CH[dsmifchnum].TR[2].DSOCL= p_cfg->low;
        R_DSMIF7->CH[dsmifchnum].TR[0].DSOCH= p_cfg->high;
        R_DSMIF7->CH[dsmifchnum].TR[1].DSOCH= p_cfg->high;
        R_DSMIF7->CH[dsmifchnum].TR[2].DSOCH= p_cfg->high;
    }
    else if(DSMIF_UNIT8==dsmifunum)
    {
        R_DSMIF8->CH[dsmifchnum].TR[0].DSOCL= p_cfg->low;
        R_DSMIF8->CH[dsmifchnum].TR[1].DSOCL= p_cfg->low;
        R_DSMIF8->CH[dsmifchnum].TR[2].DSOCL= p_cfg->low;
        R_DSMIF8->CH[dsmifchnum].TR[0].DSOCH= p_cfg->high;
        R_DSMIF8->CH[dsmifchnum].TR[1].DSOCH= p_cfg->high;
        R_DSMIF8->CH[dsmifchnum].TR[2].DSOCH= p_cfg->high;
    }
    else if(DSMIF_UNIT9==dsmifunum)
    {
        R_DSMIF9->CH[0].TR[0].DSOCL= p_cfg->low;
        R_DSMIF9->CH[0].TR[1].DSOCL= p_cfg->low;
        R_DSMIF9->CH[0].TR[2].DSOCL= p_cfg->low;
        R_DSMIF9->CH[0].TR[0].DSOCH= p_cfg->high;
        R_DSMIF9->CH[0].TR[1].DSOCH= p_cfg->high;
        R_DSMIF9->CH[0].TR[2].DSOCH= p_cfg->high;
    }
    else
    {
        /* do nothing */
    }
}
/*******************************************************************************
End of function dsmif_set_ovcthres
*******************************************************************************/

/*******************************************************************************
* Function Name: dsmif_set_scthres
* Description  : set short circuit detection threshold
* Arguments    : uint32_t dsmifunum:Unit number.
*              : uint32_t dsmifchnum:Chnnel number.
*              : p_cfg: pointer to short circuit detection threshold struct
* Return Value : none
*******************************************************************************/
static void dsmif_set_scthres(uint32_t dsmifunum, uint32_t dsmifchnum, st_dsmif_sc_thres_cfg_t* p_cfg)
{
    /* set X1DATA register */
    if(DSMIF_UNIT0==dsmifunum)
    {
        R_DSMIF0->CH[dsmifchnum].DSSCTSR_b.SCNTL= p_cfg->low; // DSSCTSR: Short Circuit Threshold Setting Register
        R_DSMIF0->CH[dsmifchnum].DSSCTSR_b.SCNTH= p_cfg->high;
    }
    else if(DSMIF_UNIT1==dsmifunum)
    {
        R_DSMIF1->CH[dsmifchnum].DSSCTSR_b.SCNTL= p_cfg->low;
        R_DSMIF1->CH[dsmifchnum].DSSCTSR_b.SCNTH= p_cfg->high;
    }
    else if(DSMIF_UNIT2==dsmifunum)
    {
        R_DSMIF2->CH[dsmifchnum].DSSCTSR_b.SCNTL= p_cfg->low;
        R_DSMIF2->CH[dsmifchnum].DSSCTSR_b.SCNTH= p_cfg->high;      
    }
    else if(DSMIF_UNIT3==dsmifunum)
    {
        R_DSMIF3->CH[dsmifchnum].DSSCTSR_b.SCNTL= p_cfg->low;
        R_DSMIF3->CH[dsmifchnum].DSSCTSR_b.SCNTH= p_cfg->high;      
    }
    else if(DSMIF_UNIT4==dsmifunum)
    {
        R_DSMIF4->CH[dsmifchnum].DSSCTSR_b.SCNTL= p_cfg->low;
        R_DSMIF4->CH[dsmifchnum].DSSCTSR_b.SCNTH= p_cfg->high;      
    }
    else if(DSMIF_UNIT5==dsmifunum)
    {
        R_DSMIF5->CH[dsmifchnum].DSSCTSR_b.SCNTL= p_cfg->low;
        R_DSMIF5->CH[dsmifchnum].DSSCTSR_b.SCNTH= p_cfg->high;      
    }
    else if(DSMIF_UNIT6==dsmifunum)
    {
        R_DSMIF6->CH[dsmifchnum].DSSCTSR_b.SCNTL= p_cfg->low;
        R_DSMIF6->CH[dsmifchnum].DSSCTSR_b.SCNTH= p_cfg->high;      
    }
    else if(DSMIF_UNIT7==dsmifunum)
    {
        R_DSMIF7->CH[dsmifchnum].DSSCTSR_b.SCNTL= p_cfg->low;
        R_DSMIF7->CH[dsmifchnum].DSSCTSR_b.SCNTH= p_cfg->high;      
    }
    else if(DSMIF_UNIT8==dsmifunum)
    {
        R_DSMIF8->CH[dsmifchnum].DSSCTSR_b.SCNTL= p_cfg->low;
        R_DSMIF8->CH[dsmifchnum].DSSCTSR_b.SCNTH= p_cfg->high;      
    }
    else if(DSMIF_UNIT9==dsmifunum)
    {
        R_DSMIF9->CH[0].DSSCTSR_b.SCNTL= p_cfg->low;
        R_DSMIF9->CH[0].DSSCTSR_b.SCNTH= p_cfg->high;      
    }
    else
    {
        /* do nothing */
    }
}
/*******************************************************************************
End of function dsmif_set_scthres
*******************************************************************************/
/* End of File */
