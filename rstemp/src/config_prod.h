#ifndef _CONFIG_H_

#define _CONFIG_H_

#define MIN_SLEEP_TIME 5
#define MAX_SLEEP_TIME 86400 // 24h
#define DEFAULT_REPEAT 1
#define DEFAULT_CLEAR_LCD 0

#define W1_COUNT "/sys/devices/w1_bus_master1/w1_master_slave_count"
#define W1_SENSORS "/sys/bus/w1/devices/w1_bus_master1/w1_master_slaves"
#define W1_SENSOR_VALUE_1 "/sys/bus/w1/drivers/w1_slave_driver/"
#define W1_SENSOR_VALUE_2 "/w1_slave"

#define LCD_DEV "/dev/klcd"

#endif