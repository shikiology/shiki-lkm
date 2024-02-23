/**
 * Overrides HWMONGetPSUStatusByI2C to provide fake psu status for SA6400 and RS4021xsp
 * to find the required symbol you can consult the mfgbios output while booting the dev LKM
 */
#include "bios_psu_status_shim.h"
#include "../../common.h"
#include "../shim_base.h"
#include "../../internal/override/override_symbol.h" //overriding HWMONGetPSUStatusByI2C
#include "../../config/platform_types.h" //hw_config, platform_has_hwmon_*
#include <linux/synobios.h> //CAPABILITY_*, CAPABILITY

#define SHIM_NAME "mfgBIOS HWMONGetPSUStatusByI2C"

static const struct hw_config *hw_config = NULL;
static override_symbol_inst *HWMONGetPSUStatusByI2C_ovs = NULL;
static override_symbol_inst *RS4021xspI2CGetPowerInfo_ovs = NULL;

static int HWMONGetPSUStatusByI2C_shim(void)
{
    return 1;
}

static int RS4021xspI2CGetPowerInfo_shim(void)
{
    return 1;
}



int register_bios_psu_status_shim(const struct hw_config *hw)
{
    shim_reg_in();

    if (unlikely(HWMONGetPSUStatusByI2C_ovs))
        shim_reg_already();
    if (unlikely(RS4021xspI2CGetPowerInfo_ovs))
        shim_reg_already();



    hw_config = hw;
    override_symbol_or_exit_int(HWMONGetPSUStatusByI2C_ovs, "HWMONGetPSUStatusByI2C", HWMONGetPSUStatusByI2C_shim);
    override_symbol_or_exit_int(RS4021xspI2CGetPowerInfo_ovs, "RS4021xspI2CGetPowerInfo_ovs", RS4021xspI2CGetPowerInfo_shim);

    shim_reg_ok();
    return 0;
}

int unregister_bios_psu_status_shim(void)
{
    shim_ureg_in();

    if (unlikely(!HWMONGetPSUStatusByI2C_ovs))
        return 0; //this is deliberately a noop
    if (unlikely(!RS4021xspI2CGetPowerInfo_ovs))
        return 0; //this is deliberately a noop

    int out = restore_symbol(HWMONGetPSUStatusByI2C_ovs);
    if (unlikely(out != 0)) {
        pr_loc_err("Failed to restore HWMONGetPSUStatusByI2C - error=%d", out);
        return out;
    }
    HWMONGetPSUStatusByI2C_ovs = NULL;

     int outrs4021xsp = restore_symbol(RS4021xspI2CGetPowerInfo_ovs);
    if (unlikely(outrs4021xsp != 0)) {
        pr_loc_err("Failed to restore RS4021xspI2CGetPowerInfo - error=%d", out);
        return out;
    }
    HWMONGetPSUStatusByI2C_ovs = NULL;
    RS4021xspI2CGetPowerInfo_ovs = NULL;


    shim_ureg_ok();
    return 0;
}

int reset_bios_psu_status_shim(void)
{
    shim_reset_in();
    put_overridden_symbol(HWMONGetPSUStatusByI2C_ovs);
    HWMONGetPSUStatusByI2C_ovs = NULL;

    put_overridden_symbol(RS4021xspI2CGetPowerInfo_ovs);
    RS4021xspI2CGetPowerInfo_ovs = NULL;


    shim_reset_ok();
    return 0;
}
