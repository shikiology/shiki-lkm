#ifndef SHIKILKM_BIOS_SHIM_H
#define SHIKILKM_BIOS_SHIM_H

struct hw_config;
int register_bios_shim(const struct hw_config *hw);
int unregister_bios_shim(void);

#endif //SHIKILKM_BIOS_SHIM_H
