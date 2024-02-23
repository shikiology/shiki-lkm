#ifndef SHIKI_PMU_SHIM_H
#define SHIKI_PMU_SHIM_H

typedef struct hw_config hw_config_;
int register_pmu_shim(const struct hw_config *hw);
int unregister_pmu_shim(void);

#endif //SHIKI_PMU_SHIM_H
