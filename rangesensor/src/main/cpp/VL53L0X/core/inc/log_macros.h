//
// Created by Ragavendiran Balasubramanian on 09/11/23.
//

#ifndef RANGINGSENSORAPP_LOG_MACROS_H
#define RANGINGSENSORAPP_LOG_MACROS_H
#include <android/log.h>

#define LOG_TAG "VL53L0X"  // Define a tag for your logs

// Define the LOG_FUNCTION_START macro
#define LOG_FUNCTION_START(fmt, ...) \
    __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "Function Start: %s: " fmt, __FUNCTION__, ##__VA_ARGS__)

// Define the LOG_FUNCTION_END macro
#define LOG_FUNCTION_END(status) \
    __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "Function End: %s, Status: %d", __FUNCTION__, status)

#endif //RANGINGSENSORAPP_LOG_MACROS_H
