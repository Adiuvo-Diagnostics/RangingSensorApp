/*
 * Programming Golden Rule: Keep it Simple!
 *
 */

/*!
 * \file   VL53L0X_platform.c
 * \brief  Code function defintions for Ewok Platform Layer
 *
 */

#include <stdio.h>    // sprintf(), vsnprintf(), printf()

#ifdef _MSC_VER
#define snprintf _snprintf
#endif

#include "vl53l0x_i2c_platform.h"
#include "vl53l0x_def.h"
#include <unistd.h>
#include <errno.h>

#include "vl53l0x_platform_log.h"

#ifdef VL53L0X_LOG_ENABLE
#define trace_print(level, ...) trace_print_module_function(TRACE_MODULE_PLATFORM, level, TRACE_FUNCTION_NONE, ##__VA_ARGS__)
#define trace_i2c(...) trace_print_module_function(TRACE_MODULE_NONE, TRACE_LEVEL_NONE, TRACE_FUNCTION_I2C, ##__VA_ARGS__)
#endif



char  debug_string[VL53L0X_MAX_STRING_LENGTH_PLT];


int32_t SOME_ERROR_CODE=-1;
#define MIN_COMMS_VERSION_MAJOR     1
#define MIN_COMMS_VERSION_MINOR     8
#define MIN_COMMS_VERSION_BUILD     1
#define MIN_COMMS_VERSION_REVISION  0

#define STATUS_OK              0x00
#define STATUS_FAIL            0x01

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <errno.h>
#include <linux/i2c.h>
#include <stdbool.h>

#define STATUS_OK 0  // Define this appropriately if not already defined
#define STATUS_FAIL 1

int file_i2c = -1;  // Global file descriptor for the I2C device


// Function to open the I2C device
bool openI2CDevice() {
    file_i2c = open("/dev/i2c-6", O_RDWR);
    return file_i2c >= 0;
}

// Function to close the I2C device
void closeI2CDevice() {
    if (file_i2c >= 0) {
        close(file_i2c);
        file_i2c = -1;
    }
}

// I2C write function
int32_t RANGING_SENSOR_COMMS_Write_V2W8(uint8_t address, uint8_t, uint8_t index, uint8_t *pdata, int32_t count) {
    openI2CDevice();
    if (file_i2c < 0) {
        return STATUS_FAIL;
    }

    if (ioctl(file_i2c, I2C_SLAVE, address) < 0) {
        return STATUS_FAIL;
    }

    uint8_t buffer[count + 1];
    buffer[0] = index;  // First byte is the register index
    memcpy(buffer + 1, pdata, count);

    if (write(file_i2c, buffer, count + 1) != count + 1) {
        return STATUS_FAIL;
    }

    return STATUS_OK;
}

// I2C read function
int32_t RANGING_SENSOR_COMMS_Read_V2W8(uint8_t address, uint8_t, uint8_t index, uint8_t *pdata, int32_t count) {
    if (file_i2c < 0) {
        return STATUS_FAIL;
    }

    if (ioctl(file_i2c, I2C_SLAVE, address) < 0) {
        return STATUS_FAIL;
    }

    if (write(file_i2c, &index, 1) != 1) {
        return STATUS_FAIL;
    }

    if (read(file_i2c, pdata, count) != count) {
        return STATUS_FAIL;
    }

    return STATUS_OK;
}

// Implement error handling function
void RANGING_SENSOR_COMMS_Get_Error_Text(char* debug_string) {
    // Implementation as discussed earlier
}

void RANGING_SENSOR_COMMS_Fini_V2W8(){

}

int32_t VL53L0X_comms_initialise(uint8_t comms_type, uint16_t comms_speed_khz) {
    int32_t status = STATUS_OK;

    // Open the I2C device file, e.g., "/dev/i2c-6"
    int file_i2c = open("/dev/i2c-6", O_RDWR);
    if (file_i2c < 0) {
        // Handle error (unable to open the device file)
        return SOME_ERROR_CODE;
    }

    // Set the I2C slave address (example address used here)
    int addr = 0x29; // The I2C address of the VL53L0X sensor
    if (ioctl(file_i2c, I2C_SLAVE, addr) < 0) {
        // Handle error (unable to set I2C address)
        close(file_i2c);
        return SOME_ERROR_CODE;
    }

    close(file_i2c);
    return status;
}


int32_t VL53L0X_comms_close(void)
{
    int32_t status = STATUS_OK;

    RANGING_SENSOR_COMMS_Fini_V2W8();

    if(status != STATUS_OK)
    {
        RANGING_SENSOR_COMMS_Get_Error_Text(debug_string);
    }

    return status;
}

int32_t VL53L0X_write_multi(uint8_t address, uint8_t index, uint8_t *pdata, int32_t count)
{
    int32_t status = STATUS_OK;

#ifdef VL53L0X_LOG_ENABLE
    int32_t i = 0;
    char value_as_str[VL53L0X_MAX_STRING_LENGTH_PLT];
    char *pvalue_as_str;

    pvalue_as_str =  value_as_str;

    for(i = 0 ; i < count ; i++)
    {
        sprintf(pvalue_as_str,"%02X", *(pdata+i));

        pvalue_as_str += 2;
    }
    trace_i2c("Write reg : 0x%04X, Val : 0x%s\n", index, value_as_str);
#endif

    // write 8-bit standard V2W8 write (not paging mode)
    status = RANGING_SENSOR_COMMS_Write_V2W8(address, 0, index, pdata, count);

    if(status != STATUS_OK)
    {
        RANGING_SENSOR_COMMS_Get_Error_Text(debug_string);
    }

    return status;
}

int32_t VL53L0X_read_multi(uint8_t address, uint8_t index, uint8_t *pdata, int32_t count)
{
    int32_t status = STATUS_OK;

#ifdef VL53L0X_LOG_ENABLE
    int32_t      i = 0;
    char   value_as_str[VL53L0X_MAX_STRING_LENGTH_PLT];
    char *pvalue_as_str;
#endif

    // read 8-bit standard V2W8 write (not paging mode)
    status = RANGING_SENSOR_COMMS_Read_V2W8(address, 0, index, pdata, count);

    if(status != STATUS_OK)
    {
        RANGING_SENSOR_COMMS_Get_Error_Text(debug_string);
    }

#ifdef VL53L0X_LOG_ENABLE
    // Build  value as string;
    pvalue_as_str =  value_as_str;

    for(i = 0 ; i < count ; i++)
    {
        sprintf(pvalue_as_str, "%02X", *(pdata+i));
        pvalue_as_str += 2;
    }

    trace_i2c("Read  reg : 0x%04X, Val : 0x%s\n", index, value_as_str);
#endif

    return status;
}


int32_t VL53L0X_write_byte(uint8_t address, uint8_t index, uint8_t data)
{
    int32_t status = STATUS_OK;
    const int32_t cbyte_count = 1;

    status = VL53L0X_write_multi(address, index, &data, cbyte_count);

    return status;

}


int32_t VL53L0X_write_word(uint8_t address, uint8_t index, uint16_t data)
{
    int32_t status = STATUS_OK;

    uint8_t  buffer[BYTES_PER_WORD];

    // Split 16-bit word into MS and LS uint8_t
    buffer[0] = (uint8_t)(data >> 8);
    buffer[1] = (uint8_t)(data &  0x00FF);

    status = VL53L0X_write_multi(address, index, buffer, BYTES_PER_WORD);

    return status;

}


int32_t VL53L0X_write_dword(uint8_t address, uint8_t index, uint32_t data)
{
    int32_t status = STATUS_OK;
    uint8_t  buffer[BYTES_PER_DWORD];

    // Split 32-bit word into MS ... LS bytes
    buffer[0] = (uint8_t) (data >> 24);
    buffer[1] = (uint8_t)((data &  0x00FF0000) >> 16);
    buffer[2] = (uint8_t)((data &  0x0000FF00) >> 8);
    buffer[3] = (uint8_t) (data &  0x000000FF);

    status = VL53L0X_write_multi(address, index, buffer, BYTES_PER_DWORD);

    return status;

}


int32_t VL53L0X_read_byte(uint8_t address, uint8_t index, uint8_t *pdata)
{
    int32_t status = STATUS_OK;
    int32_t cbyte_count = 1;

    status = VL53L0X_read_multi(address, index, pdata, cbyte_count);

    return status;

}


int32_t VL53L0X_read_word(uint8_t address, uint8_t index, uint16_t *pdata)
{
    int32_t  status = STATUS_OK;
	uint8_t  buffer[BYTES_PER_WORD];

    status = VL53L0X_read_multi(address, index, buffer, BYTES_PER_WORD);
	*pdata = ((uint16_t)buffer[0]<<8) + (uint16_t)buffer[1];

    return status;

}

int32_t VL53L0X_read_dword(uint8_t address, uint8_t index, uint32_t *pdata)
{
    int32_t status = STATUS_OK;
	uint8_t  buffer[BYTES_PER_DWORD];

    status = VL53L0X_read_multi(address, index, buffer, BYTES_PER_DWORD);
    *pdata = ((uint32_t)buffer[0]<<24) + ((uint32_t)buffer[1]<<16) + ((uint32_t)buffer[2]<<8) + (uint32_t)buffer[3];

    return status;

}

int32_t VL53L0X_platform_wait_us(int32_t wait_us)
{
    int32_t status = STATUS_OK;

    // usleep takes microsecond arguments directly, so no conversion is needed
    if (usleep(wait_us) < 0) {
        // Handle error if needed
        if (errno == EINTR) {
            // Handle interruption by signal if necessary
        }
        // Set an appropriate error status if required
        // status = SOME_ERROR_CODE;
    }

#ifdef VL53L0X_LOG_ENABLE
    trace_i2c("Wait us : %6d\n", wait_us);
#endif

    return status;
}



int32_t VL53L0X_set_gpio(uint8_t level)
{
    int32_t status = STATUS_OK;
    //status = VL53L0X_set_gpio_sv(level);
#ifdef VL53L0X_LOG_ENABLE
    trace_i2c("// Set GPIO = %d;\n", level);
#endif

    return status;

}


int32_t VL53L0X_get_gpio(uint8_t *plevel)
{
    int32_t status = STATUS_OK;
#ifdef VL53L0X_LOG_ENABLE
    trace_i2c("// Get GPIO = %d;\n", *plevel);
#endif
    return status;
}


int32_t VL53L0X_release_gpio(void)
{
    int32_t status = STATUS_OK;
#ifdef VL53L0X_LOG_ENABLE
    trace_i2c("// Releasing force on GPIO\n");
#endif
    return status;

}

int32_t RANGING_SENSOR_COMMS_Cycle_Sensor_Power() {
    return 0;
}

int32_t VL53L0X_cycle_power(void)
{
    int32_t status = STATUS_OK;
#ifdef VL53L0X_LOG_ENABLE
    trace_i2c("// cycle sensor power\n");
#endif
    status = RANGING_SENSOR_COMMS_Cycle_Sensor_Power();

	if(status != STATUS_OK)
    {
        RANGING_SENSOR_COMMS_Get_Error_Text(debug_string);
    }

	return status;
}


int32_t VL53L0X_get_timer_frequency(int32_t *ptimer_freq_hz)
{
       *ptimer_freq_hz = 0;
       return STATUS_FAIL;
}


int32_t VL53L0X_get_timer_value(int32_t *ptimer_count)
{
       *ptimer_count = 0;
       return STATUS_FAIL;
}


