#ifndef SHIKILKM_BOOT_DEVICE_SHIM_H
#define SHIKILKM_BOOT_DEVICE_SHIM_H

struct boot_media;
int register_boot_shim(const struct boot_media *boot_dev_config);
int unregister_boot_shim(void);

#endif //SHIKILKM_BOOT_DEVICE_SHIM_H
