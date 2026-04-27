#ifndef __I2C_CONFIG_H__
#define __I2C_CONFIG_H__

/* config */

#define HWI2C 1
#define I2C_WAIT_US 5000

#define BR100K 100000
#define BR200K 200000
#define BR400K 400000

#define BR_I2C BR400K

/* macros */

#ifndef HWI2C
#define HWI2C 1
#endif

#ifndef I2C_WAIT_US
#define I2C_WAIT_US 0
#endif

#if HWI2C

#else

#endif

#if I2C_WAIT_US

#define i2c_write_blocking(A, B, C, D, E) i2c_write_blocking_until(A, B, C, D, E, get_absolute_time() + I2C_WAIT_US)

#define i2c_read_blocking(A, B, C, D, E) i2c_read_blocking_until(A, B, C, D, E, get_absolute_time() + I2C_WAIT_US)

#endif

#endif