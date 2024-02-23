#include "scsi_notifier_list.h"
#include <linux/notifier.h>

BLOCKING_NOTIFIER_HEAD(sk_scsi_notify_list);
