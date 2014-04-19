#ifndef mvirt_GPIO_DEFS_H_
#define mvirt_GPIO_DEFS_H_

#include <inttypes.h>
#include "types.h"

#define DM365_GPIO_BINTEN	0x01C67008
#define DM365_GPIO_BANK01	0x01C67010
#define DM365_GPIO_BANK23	0x01C67038
#define DM365_GPIO_BANK45	0x01C67060
#define DM365_GPIO_BANK67	0x01C67088


struct dm365_gpio_struct {
	vuint32_t DIR;
	vuint32_t OUT_DATA;
	vuint32_t SET_DATA;
	vuint32_t CLR_DATA;
	vuint32_t IN_DATA;
	vuint32_t SET_RISSING;
	vuint32_t CLR_RISSING;
	vuint32_t SET_FALLING;
	vuint32_t CLR_FALLING;
	vuint32_t INT_STAT;
};

struct dm365_gpio_bank {
	vint32_t num_gpio;
	vuint32_t irq_num;
	vuint32_t irq_mask;
	vuint64_t *in_use;
	vuint64_t base;
};

#define GPIO_BANK01 ((struct dm365_gpio_struct *)DM365_GPIO_BANK01)
#define GPIO_BANK23 ((struct dm365_gpio_struct *)DM365_GPIO_BANK23)
#define GPIO_BANK45 ((struct dm365_gpio_struct *)DM365_GPIO_BANK45)
#define GPIO_BANK67 ((struct dm365_gpio_struct *)DM365_GPIO_BANK67)

#endif
