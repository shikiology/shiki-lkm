#ifndef SHIKI_NATIVE_SATA_BOOT_SHIM_H
#define SHIKI_NATIVE_SATA_BOOT_SHIM_H

struct boot_media;
int register_native_sata_boot_shim(const struct boot_media *config);
int unregister_native_sata_boot_shim(void);

#endif //SHIKI_NATIVE_SATA_BOOT_SHIM_H
