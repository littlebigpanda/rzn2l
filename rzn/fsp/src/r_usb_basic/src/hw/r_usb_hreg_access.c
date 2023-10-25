/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include <r_usb_basic.h>
#include <r_usb_basic_api.h>

#include "../driver/inc/r_usb_typedef.h"
#include "../driver/inc/r_usb_extern.h"
#include "inc/r_usb_bitdefine.h"
#include "inc/r_usb_reg_access.h"

#define USB_VALUE_50       (50)
#define USB_VALUE_100      (100)
#define USB_VALUE_450      (450)
#define USB_VALUE_500      (500)
#define USB_VALUE_0F00H    (0x0f00)

#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
 #if USB_IP_EHCI_OHCI == 0

/******************************************************************************
 * Function Name   : hw_usb_hset_rwupe
 * Description     : Set the RWUPE-bit specified port's DVSTCTR0 reg-
 *               : ister. When host. To allow detection of remote wake-up from
 *               : a USB Function.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hset_rwupe (usb_utr_t * ptr)
{
    ptr->ipp->DVSTCTR0 |= USB_RWUPE;
}

/******************************************************************************
 * End of function hw_usb_hset_rwupe
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hclear_rwupe
 * Description     : Clear the RWUPE-bit specified port's DVSTCTR0 reg-
 *               : ister. When host. To prohibit detection of remote wake-up from
 *               : a USB Function.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hclear_rwupe (usb_utr_t * ptr)
{
    ptr->ipp->DVSTCTR0 = (uint16_t) (ptr->ipp->DVSTCTR0 & (~USB_RWUPE));
}

/******************************************************************************
 * End of function hw_usb_hclear_rwupe
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hset_resume
 * Description     : Set the RESUME-bit specified port's DVSTCTR0 register
 *               : When host. To allow output of resume signal to a USB Function.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hset_resume (usb_utr_t * ptr)
{
    ptr->ipp->DVSTCTR0 |= USB_RESUME;
}

/******************************************************************************
 * End of function hw_usb_hset_resume
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hclear_resume
 * Description     : Clear the RESUME-bit specified port's DVSTCTR0 register
 *               : When host. To prohibit output of resume signal to a USB Func-
 *               : tion.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hclear_resume (usb_utr_t * ptr)
{
    ptr->ipp->DVSTCTR0 = (uint16_t) (ptr->ipp->DVSTCTR0 & (~USB_RESUME));
}

/******************************************************************************
 * End of function hw_usb_hset_uact
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hset_uact
 * Description     : Set UACT-bit (USB Bus Enable) specified port's DVSTCTR0
 *               : register. When Host, to output SOF.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hset_uact (usb_utr_t * ptr)
{
    ptr->ipp->DVSTCTR0 |= USB_UACT;
}

/******************************************************************************
 * End of function hw_usb_hset_uact
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hclear_uact
 * Description     : Clear UACT-bit (USB Bus Enable) specified port's DVSTCTR0
 *               : register. When Host, to prohibit output SOF.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hclear_uact (usb_utr_t * ptr)
{
    ptr->ipp->DVSTCTR0 = (uint16_t) (ptr->ipp->DVSTCTR0 & (~USB_UACT));
}

/******************************************************************************
 * End of function hw_usb_hclear_uact
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hwrite_intenb
 * Description     : Write the specified data to the specified port's INTENB register.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 *               : uint16_t  data   : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_hwrite_intenb (usb_utr_t * ptr, uint16_t data)
{
    ptr->ipp->INTENB1 = data;
}

/******************************************************************************
 * End of function hw_usb_hwrite_intenb
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hset_enb_ovrcre
 * Description     : Set specified port's OVRCRE-bit (Overcurrent Input Change Int-
 *               : errupt Status Enable) in the INTENB1 register.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hset_enb_ovrcre (usb_utr_t * ptr)
{
    ptr->ipp->INTENB1 |= USB_OVRCRE;
}

/******************************************************************************
 * End of function hw_usb_hset_enb_ovrcre
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hclear_enb_ovrcre
 * Description     : Clear the OVRCRE-bit of the specified port's INTENB1 register,
 *               : to prohibit VBUS interrupts.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hclear_enb_ovrcre (usb_utr_t * ptr)
{
    ptr->ipp->INTENB1 = (uint16_t) (ptr->ipp->INTENB1 & (~USB_OVRCRE));
}

/******************************************************************************
 * End of function hw_usb_hclear_enb_ovrcre
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hset_enb_bchge
 * Description     : The BCHGE-bit (USB Bus Change Interrupt Enable) is set in the
 *               : specified port's INTENB1 register. This will cause a BCHG
 *               : interrupt when a change of USB bus state has been detected.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hset_enb_bchge (usb_utr_t * ptr)
{
    ptr->ipp->INTENB1 |= USB_BCHGE;
}

/******************************************************************************
 * End of function hw_usb_hset_enb_bchge
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hclear_enb_bchge
 * Description     : The BCHGE-bit (USB Bus Change Interrupt Enable) is cleared in
 *               : the specified port's INTENB1 register.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hclear_enb_bchge (usb_utr_t * ptr)
{
    ptr->ipp->INTENB1 = (uint16_t) (ptr->ipp->INTENB1 & (~USB_BCHGE));
}

/******************************************************************************
 * End of function hw_usb_hclear_enb_bchge
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hset_enb_dtche
 * Description     : Enable the specified port's DTCHE-interrupt "Disconnection
 *               : Detection" by setting the DTCHE-bit.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hset_enb_dtche (usb_utr_t * ptr)
{
    ptr->ipp->INTENB1 |= USB_DTCHE;
}

/******************************************************************************
 * End of function hw_usb_hset_enb_dtche
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hclear_enb_dtche
 * Description     : Disable the specified port's DTCHE-interrupt "Disconnection
 *               : Detection" by clearing the DTCHE-bit.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hclear_enb_dtche (usb_utr_t * ptr)
{
    ptr->ipp->INTENB1 = (uint16_t) (ptr->ipp->INTENB1 & (~USB_DTCHE));
}

/******************************************************************************
 * End of function hw_usb_hclear_enb_dtche
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hset_enb_attche
 * Description     : Enable the specified port's ATTCHE-interrupt "Connection
 *               : Detection" by setting the ATTCHE-bit.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hset_enb_attche (usb_utr_t * ptr)
{
    ptr->ipp->INTENB1 |= USB_ATTCHE;
}

/******************************************************************************
 * End of function hw_usb_hset_enb_attche
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hclear_enb_attche
 * Description     : Disable the specified port's ATTCHE-interrupt "Disconnection
 *               : Detection" by clearing the ATTCHE-bit.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hclear_enb_attche (usb_utr_t * ptr)
{
    ptr->ipp->INTENB1 = (uint16_t) (ptr->ipp->INTENB1 & (~USB_ATTCHE));
}

/******************************************************************************
 * End of function hw_usb_hclear_enb_attche
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hset_enb_signe
 * Description     : Enable the SIGNE-interrupt "Setup Transaction
 *               : Error" by setting the SIGNE-bit.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hset_enb_signe (usb_utr_t * ptr)
{
    ptr->ipp->INTENB1 |= USB_SIGNE;
}

/******************************************************************************
 * End of function hw_usb_hset_enb_signe
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hset_enb_sacke
 * Description     : Enable the SACKE-interrupt "Setup Transaction
 *               : Normal Response" by setting the SACKE-bit.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hset_enb_sacke (usb_utr_t * ptr)
{
    ptr->ipp->INTENB1 |= USB_SACKE;
}

/******************************************************************************
 * End of function hw_usb_hset_enb_sacke
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hset_enb_pddetinte
 * Description     : Enable the PDDETINT-interrupt "Connection Detection for
 *               : Battery Charging Supporting Device" by setting
 *               : the PDDETINTE-bit.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hset_enb_pddetinte (usb_utr_t * ptr)
{
  #if defined(BSP_MCU_GROUP_RA6M3)
    if (USB_IP1 == ptr->ip)
    {
        ptr->ipp1->INTENB1 |= USB_PDDETINTE;
    }
  #else                                /* defined(BSP_MCU_GROUP_RA6M3) */
    (void) *ptr;
  #endif /* defined(BSP_MCU_GROUP_RA6M3) */
}

/******************************************************************************
 * End of function hw_usb_hset_enb_pddetinte
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hwrite_intsts
 * Description     : Write the specified data to the specified port's INTSTS1 reg-
 *               : ister.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 *               : uint16_t  data   : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_hwrite_intsts (usb_utr_t * ptr, uint16_t data)
{
    ptr->ipp->INTSTS1 = data;
}

/******************************************************************************
 * End of function hw_usb_hwrite_intsts
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hclear_sts_ovrcr
 * Description     : Clear the specified port's OVRCR-bit; "Overcurrent
 *               : Input Change Interrupt Status".
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hclear_sts_ovrcr (usb_utr_t * ptr)
{
    ptr->ipp->INTSTS1 = (uint16_t) ((~USB_OVRCR) & INTSTS1_MASK);
}

/******************************************************************************
 * End of function hw_usb_hclear_sts_ovrcr
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hclear_sts_bchg
 * Description     : Clear the specified port's BCHG-bit; "USB Bus Change Interrupt
 *               : Status".
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hclear_sts_bchg (usb_utr_t * ptr)
{
    ptr->ipp->INTSTS1 = (uint16_t) ((~USB_BCHG) & INTSTS1_MASK);
}                                      /* End of function hw_usb_hclear_sts_bchg() */

/******************************************************************************
 * End of function hw_usb_hclear_sts_bchg
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hclear_sts_dtch
 * Description     : Clear the specified port's DTCH-bit; "USB Disconnection Detec-
 *               : tion Interrupt Status".
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hclear_sts_dtch (usb_utr_t * ptr)
{
    ptr->ipp->INTSTS1 = (uint16_t) ((~USB_DTCH) & INTSTS1_MASK);
}

/******************************************************************************
 * End of function hw_usb_hclear_sts_dtch
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hclear_sts_attch
 * Description     : Clear the specified port's ATTCH-bit; "ATTCH Interrupt Status".
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hclear_sts_attch (usb_utr_t * ptr)
{
    ptr->ipp->INTSTS1 = (uint16_t) ((~USB_ATTCH) & INTSTS1_MASK);
}

/******************************************************************************
 * End of function hw_usb_hclear_sts_attch
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hclear_sts_sign
 * Description     : Clear the SIGN-bit; "Setup Transaction Error
 *               : Interrupt Status".
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hclear_sts_sign (usb_utr_t * ptr)
{
    ptr->ipp->INTSTS1 = (uint16_t) ((~USB_SIGN) & INTSTS1_MASK);
}

/******************************************************************************
 * End of function hw_usb_hclear_sts_sign
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hclear_sts_sack
 * Description     : Clear the SACK-bit; "Setup Transaction Normal
 *               : Response Interrupt Status".
 *               : Interrupt Status".
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hclear_sts_sack (usb_utr_t * ptr)
{
    ptr->ipp->INTSTS1 = (uint16_t) ((~USB_SACK) & INTSTS1_MASK);
}

/******************************************************************************
 * End of function hw_usb_hclear_sts_sack
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hclear_sts_pddetint
 * Description     : Clear the PDDETINT-bit; "
 *               : ".
 *               : Interrupt Status".
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hclear_sts_pddetint (usb_utr_t * ptr)
{
  #if defined(BSP_MCU_GROUP_RA6M3)
    if (USB_IP1 == ptr->ip)
    {
        ptr->ipp1->INTSTS1 = (uint16_t) ((~USB_PDDETINT) & INTSTS1_MASK);
    }
  #else                                /* defined(BSP_MCU_GROUP_RA6M3) */
    (void) *ptr;
  #endif /* defined(BSP_MCU_GROUP_RA6M3) */
}

/******************************************************************************
 * End of function hw_usb_hclear_sts_pddetint
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hwrite_usbreq
 * Description     : Write bRequest and bmRequestType to USBREQ register.
 *               : When Host, the values of bRequest and bmRequestType
 *               : to be transmitted are written. (When Function, the received
 *               : values of bRequest and bmRequestType are stored in USBREQ).
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 *               : uint16_t  data   : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_hwrite_usbreq (usb_utr_t * ptr, uint16_t data)
{
    ptr->ipp->USBREQ = data;
}

/******************************************************************************
 * End of function hw_usb_hwrite_usbreq
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hset_usbval
 * Description     : Write the specified 'wValue' to USBVAL register,
 *               : to write the USB request. When Host, the value of
 *               : wValue to be transmitted is set. (When Function, the value of
 *               : wValue that has been received is stored in USBREQ.)
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 *               : uint16_t  data   : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_hset_usbval (usb_utr_t * ptr, uint16_t data)
{
    ptr->ipp->USBVAL = data;
}

/******************************************************************************
 * End of function hw_usb_hset_usbval
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hset_usbindx
 * Description     : Write the specified 'wIndex', the USB request, to USBINDX
 *               : register, for host setup requests for control
 *               : transfers.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 *               : uint16_t  data   : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_hset_usbindx (usb_utr_t * ptr, uint16_t data)
{
    ptr->ipp->USBINDX = data;
}

/******************************************************************************
 * End of function hw_usb_hset_usbindx
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hset_usbleng
 * Description     : Write the specified 'wLength' value to USBINDX register,
 *               : for host setup requests for control.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 *               : uint16_t  data   : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_hset_usbleng (usb_utr_t * ptr, uint16_t data)
{
    ptr->ipp->USBLENG = data;
}

/******************************************************************************
 * End of function hw_usb_hset_usbleng
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hwrite_dcpctr
 * Description     : Write the specified data value to the DCPCTR register.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 *               : uint16_t  data   : Setting value
 * Return value    : none
 ******************************************************************************/
void hw_usb_hwrite_dcpctr (usb_utr_t * ptr, uint16_t data)
{
    ptr->ipp->DCPCTR = data;
}

/******************************************************************************
 * End of function hw_usb_hwrite_dcpctr
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hset_sureq
 * Description     : Set SUREQ-bit in the DCPCTR register
 *               : (Set SETUP packet send when HostController function is selected)
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hset_sureq (usb_utr_t * ptr)
{
    ptr->ipp->DCPCTR |= USB_SUREQ;
}

/******************************************************************************
 * End of function hw_usb_hset_sureq
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hread_devadd
 * Description     : Return the DEVADD register value for the specified USB device
 *               ; address.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 *               : uint16_t  devsel : USB device address value
 * Return value    : DEVADDx content
 ******************************************************************************/
uint16_t hw_usb_hread_devadd (usb_utr_t * ptr, uint16_t devsel)
{
    volatile uint16_t * preg;
    uint16_t            devadr;
    uint16_t            return_value;
    uint16_t            result;

    devadr = devsel >> USB_DEVADDRBIT;

    if (devadr > USB_MAXDEVADDR)
    {
        result = USB_ERROR;
    }
    else
    {
        preg         = (uint16_t *) &(ptr->ipp->DEVADD[0]) + devadr;
        return_value = ((*preg) & ((USB_UPPHUB | USB_HUBPORT) | USB_USBSPD));
        result       = return_value;
    }

    return result;
}

/******************************************************************************
 * End of function hw_usb_hread_devadd
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hrmw_devadd
 * Description     : Read-modify-write the specified devsel's DEVADD.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 *               : uint16_t  devsel : USB device address value
 *               : uint16_t  data   : The value to write.
 *               : uint16_t  width  : Bit pattern to read-modify-write.
 * Return value    : none
 ******************************************************************************/
void hw_usb_hrmw_devadd (usb_utr_t * ptr, uint16_t devsel, uint16_t data, uint16_t width)
{
    volatile uint16_t * preg;
    uint16_t            buf;
    uint16_t            devadr;

    devadr = devsel >> USB_DEVADDRBIT;

    preg = (uint16_t *) &(ptr->ipp->DEVADD[0]) + devadr;

    buf   = *preg;
    buf   = (uint16_t) (buf & (~width));
    buf  |= (data & width);
    *preg = buf;
}

/******************************************************************************
 * End of function hw_usb_hrmw_devadd
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hset_usbspd
 * Description     : Set the DEVADD register's USBSPD for the specified device add-
 *               : ress.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 *               : uint16_t  devsel : USB device address value
 *               : uint16_t  data   : The value to write.
 * Return value    : none
 ******************************************************************************/
void hw_usb_hset_usbspd (usb_utr_t * ptr, uint16_t devsel, uint16_t data)
{
    volatile uint16_t * preg;
    uint16_t            devadr;

    devadr = devsel >> USB_DEVADDRBIT;

    preg = (uint16_t *) &(ptr->ipp->DEVADD[0]) + devadr;

    (*preg) = (uint16_t) ((*preg) & (~USB_USBSPD));
    (*preg) = (uint16_t) ((*preg) | data);
}

/******************************************************************************
 * End of function hw_usb_hset_usbspd
 ******************************************************************************/

/******************************************************************************
 * Function Name   : hw_usb_hset_dcpmode
 * Description     : Set DCPMODE bit.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hset_dcpmode (usb_utr_t * ptr)
{
  #if defined(BSP_MCU_GROUP_RA6M3)
    if (USB_IP1 == ptr->ip)
    {
        ptr->ipp1->BCCTRL |= USB_DCPMODE;
    }
  #else                                /* defined(BSP_MCU_GROUP_RA6M3) */
    (void) *ptr;
  #endif
}

/******************************************************************************
 * End of function hw_usb_hset_dcpmode
 ******************************************************************************/
 #endif                                /* USB_IP_EHCI_OHCI == 0 */

/******************************************************************************
 * Function Name   : hw_usb_hmodule_init
 * Description     : USB module initialization for USB Host mode
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hmodule_init (usb_ctrl_t * p_api_ctrl)
{
 #if USB_IP_EHCI_OHCI == 0
    usb_instance_ctrl_t * p_ctrl = (usb_instance_ctrl_t *) p_api_ctrl;

    uint16_t sts;

    if (USB_IP0 == p_ctrl->module_number)
    {
        USB_M0->SYSCFG |= USB_SCKE;

        /* WAIT_LOOP */
        while (USB_SCKE != (USB_M0->SYSCFG & USB_SCKE))
        {
            /* none */
        }

  #if defined(BSP_MCU_GROUP_RA6M3)
        USB_M0->PHYSLEW = 0x5;
  #endif                               /* defined(BSP_MCU_GROUP_RA6M3) */

        USB_M0->SYSCFG |= USB_DCFM;

        USB_M0->SYSCFG |= USB_DRPD;

        sts = usb_chattaring((uint16_t *) &USB_M0->SYSSTS0);

        USB_M0->SYSCFG |= USB_USBE;

        USB_M0->CFIFOSEL  = USB0_CFIFO_MBW;
        USB_M0->D0FIFOSEL = USB0_D0FIFO_MBW;
        USB_M0->D1FIFOSEL = USB0_D1FIFO_MBW;

  #if USB_CFG_ENDIAN == USB_CFG_BIG
        USB_M0->CFIFOSEL  |= USB_BIGEND;
        USB_M0->D0FIFOSEL |= USB_BIGEND;
        USB_M0->D1FIFOSEL |= USB_BIGEND;
  #endif                                                    /* USB_CFG_ENDIAN == USB_CFG_BIG */

        switch (sts)
        {
            case USB_FS_JSTS:                               /* USB device already connected */
            case USB_LS_JSTS:
            {
                USB_M0->DVSTCTR0 |= USB_USBRST;
                usb_cpu_delay_xms((uint16_t) USB_VALUE_50); /* Need to wait greater equal 10ms in USB spec */
                USB_M0->DVSTCTR0 = (uint16_t) (USB_M0->DVSTCTR0 & (~USB_USBRST));

                /* WAIT_LOOP */
                while (USB_HSPROC == (USB_M0->DVSTCTR0 & USB_HSPROC))
                {
                    /* HSPROC = 0100b */
                }

                if (USB_LSMODE == (USB_M0->DVSTCTR0 & USB_RHST))
                {
                    USB_M0->SOFCFG |= USB_TRNENSEL;
                }

                USB_M0->DVSTCTR0 |= USB_UACT;
                break;
            }

            case USB_SE0:              /* USB device no connected */
            {
                USB_M0->INTENB1 = USB_ATTCH;
                break;
            }

            default:
            {
                break;
            }
        }

        USB_M0->INTSTS1 &= ((~USB_OVRCRE) & INTSTS1_MASK);
        USB_M0->INTENB0  = ((USB_BEMPE | USB_NRDYE) | USB_BRDYE);
        USB_M0->INTENB1  = (USB_OVRCRE | USB_ATTCH);
    }

  #if USB_NUM_USBIP == 2
    else
    {
   #if defined(BSP_MCU_GROUP_RA6M3)
    #if USB_CFG_CLKSEL == USB_CFG_20MHZ
        USB_M1->PHYSET &= (uint16_t) ~USB_CLKSEL;
        USB_M1->PHYSET |= USB_CLKSEL_20;
    #endif                             /* USB_CFG_CLKSEL == USB_CFG_20MHZ */

    #if USB_CFG_CLKSEL == USB_CFG_12MHZ
        USB_M1->PHYSET &= (uint16_t) ~USB_CLKSEL;
        USB_M1->PHYSET |= USB_CLKSEL_12;
    #endif                             /* USB_CFG_CLKSEL == USB_CFG_12MHZ */

    #if USB_CFG_CLKSEL == USB_CFG_OTHER
        USB_M1->PHYSET |= USB_HSEB;
    #else /* USB_CFG_OTHER == USB_CFG_OTHER */
        USB_M1->PHYSET |= USB_REPSEL_16;
    #endif                               /* USB_CFG_OTHER == USB_CFG_OTHER */

        usb_cpu_delay_1us((uint16_t) 1); /* wait 1usec */

        USB_M1->PHYSET = (uint16_t) (USB_M1->PHYSET & (~USB_DIRPD));
        usb_cpu_delay_xms(1);            /* wait 1msec */

    #if ((USB_CFG_CLKSEL == USB_CFG_12MHZ) || (USB_CFG_CLKSEL == USB_CFG_20MHZ) || (USB_CFG_CLKSEL == USB_CFG_24MHZ))
        USB_M1->PHYSET = (uint16_t) (USB_M1->PHYSET & (~USB_PLLRESET));
    #endif /* (USB_CFG_CLKSEL == USB_CFG_12MHZ) || (USB_CFG_CLKSEL == USB_CFG_20MHZ) || (USB_CFG_CLKSEL == USB_CFG_24MHZ) */

        USB_M1->LPSTS |= USB_SUSPENDM;

    #if ((USB_CFG_CLKSEL == USB_CFG_12MHZ) || (USB_CFG_CLKSEL == USB_CFG_20MHZ) || (USB_CFG_CLKSEL == USB_CFG_24MHZ))

        /* WAIT_LOOP */
        while (USB_PLLLOCK != (USB_M1->PLLSTA & USB_PLLLOCK))
        {
            /* Wait for PLL Lock */
        }
        ;
    #endif                             /* (USB_CFG_CLKSEL == USB_CFG_12MHZ) || (USB_CFG_CLKSEL == USB_CFG_20MHZ) || (USB_CFG_CLKSEL == USB_CFG_24MHZ) */

        USB_M1->SYSCFG |= USB_DRPD;

        USB_M1->SYSCFG |= USB_CNEN;

        USB_M1->BUSWAIT = (USB_CFG_BUSWAIT | USB_VALUE_0F00H);
        usb_cpu_delay_1us((uint16_t) 1); /* wait 1usec */
   #endif /* defined(BSP_MCU_GROUP_RA6M3) */

        USB_M1->SOFCFG |= USB_INTL;

        USB_M1->SYSCFG |= USB_DCFM;

        sts = usb_chattaring((uint16_t *) &USB_M1->SYSCFG);

        USB_M1->SYSCFG |= USB_USBE;

        USB_M1->CFIFOSEL  = USB1_CFIFO_MBW;
        USB_M1->D0FIFOSEL = USB1_D0FIFO_MBW;
        USB_M1->D1FIFOSEL = USB1_D1FIFO_MBW;

   #if USB_CFG_ENDIAN == USB_CFG_BIG
        USB_M1->CFIFOSEL  |= USB_BIGEND;
        USB_M1->D0FIFOSEL |= USB_BIGEND;
        USB_M1->D1FIFOSEL |= USB_BIGEND;
   #endif
        switch (sts)
        {
            case USB_FS_JSTS:          /* USB device already connected */
            case USB_LS_JSTS:
            {
                if (USB_FS_JSTS == sts)
                {
                    USB_M1->SYSCFG |= USB_HSE;
                }

                USB_M1->DVSTCTR0 |= USB_USBRST;

                usb_cpu_delay_xms((uint16_t) USB_VALUE_50); /* Need to wait greater equal 10ms in USB spec */

                USB_M1->DVSTCTR0 = (uint16_t) (USB_M1->DVSTCTR0 & (~USB_USBRST));

                /* WAIT_LOOP */
                while (USB_HSPROC == (USB_M1->DVSTCTR0 & USB_HSPROC))
                {
                    /* Wait for USB reset handshake in progress */
                }

                ;

                if (USB_LSMODE == (USB_M1->DVSTCTR0 & USB_RHST))
                {
                    USB_M1->SOFCFG |= USB_TRNENSEL;
                }

                USB_M1->DVSTCTR0 |= USB_UACT;
                break;
            }

            case USB_SE0:              /* USB device no connected */
            {
   #if defined(BSP_MCU_GROUP_RA6M3)
                USB_M1->INTENB1 = USB_ATTCH;
   #endif /* defined(BSP_MCU_GROUP_RA6M3) */
                break;
            }

            default:
            {
                break;
            }
        }

        USB_M1->INTSTS1 &= (~USB_OVRCRE & INTSTS1_MASK);
        USB_M1->INTENB0  = (USB_BEMPE | USB_NRDYE | USB_BRDYE);
   #if defined(BSP_MCU_GROUP_RA6M3)
        USB_M1->INTENB1 = (USB_OVRCRE | USB_ATTCH);
   #endif                              /* defined(BSP_MCU_GROUP_RA6M3) */
    }
  #endif                               /* USB_NUM_USBIP == 2 */
 #else /* USB_IP_EHCI_OHCI == 0 */
    volatile unsigned long dummy;
    volatile uint8_t       dummy_buf = 0;

    FSP_PARAMETER_NOT_USED(dummy_buf);
    FSP_PARAMETER_NOT_USED(p_api_ctrl);

  #if 0
    CPG.STBCR6.BYTE &= 0xFD;             /* Release module standby */
    dummy_buf        = CPG.STBCR6.BYTE;

   #if (BSP_CFG_BOARD == BSP_CFG_BOARD_RZA2_EVB)
    USB00.PHYCLK_CTRL.LONG = 0x00000001; /* USBPHY select : USB_X1 */
   #else
    USB00.PHYCLK_CTRL.LONG = 0x00000000; /* USBPHY select : EXTAL */
   #endif /* (BSP_CFG_BOARD == BSP_CFG_BOARD_RZA2_EVB) */
  #endif /* 0 */
    for (dummy = 0; dummy < (USB_VALUE_450 * USB_VALUE_500); dummy++)
    {
        ;                              /* Wait 500us */
    }

    USB00->COMMCTRL_b.PERI = 0;        /* Operation mode setting (0 : Host, 1 : Peri) */

    USB00->USBCTR &= ~0x00000002U;     /* UTMI+PHY reset release */

    for (dummy = 0; dummy < (USB_VALUE_450 * USB_VALUE_100); dummy++)
    {
        ;                              /* Wait 100us */
    }
 #endif /* USB_IP_EHCI_OHCI == 0 */
}

/******************************************************************************
 * End of function hw_usb_hmodule_init
 ******************************************************************************/
 #if USB_IP_EHCI_OHCI == 0

/******************************************************************************
 * Function Name   : hw_usb_hset_trnensel
 * Description     : When host, set the TRNENSEL-bit; "Transac-
 *               : tion-Enabled Time Select" for low-speed USB communication.
 *               : This bit should be set to 0 if USB Function.
 * Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 * Return value    : none
 ******************************************************************************/
void hw_usb_hset_trnensel (usb_utr_t * ptr)
{
    ptr->ipp->SOFCFG |= USB_TRNENSEL;
}

/******************************************************************************
 * End of function hw_usb_hset_trnensel
 ******************************************************************************/

 #endif                                /* USB_IP_EHCI_OHCI == 0 */
#endif /* ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST) */

/******************************************************************************
 * End of file
 ******************************************************************************/
