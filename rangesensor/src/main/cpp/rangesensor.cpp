#include <jni.h>
#include <string>
#include <jni.h>
#include <exception>
#include "vl53l0x_platform.h"
#include "vl53l0x_api.h"
#include "log_macros.h"

VL53L0X_DEV vl53L0XDev;
VL53L0X_RangingMeasurementData_t vl53L0XRangingMeasurementData;

uint8_t VL53L0X_COMMS_I2C=0;
uint32_t refSpadCount=16;
uint8_t isApertureSpads=0;
uint8_t pPhaseCal=0;
uint8_t pVhvSettings=0;
int32_t *pOffsetMicroMeter;
FixPoint1616_t  CalDistanceMilliMeter;

extern "C"
JNIEXPORT jchar JNICALL
Java_com_adiuvo_rangesensor_RangeSensor_dataInit(JNIEnv *env, jobject thiz) {
    vl53L0XDev = (VL53L0X_DEV)malloc(sizeof(VL53L0X_Dev_t));
    if (vl53L0XDev == NULL) {
        // Handle memory allocation error
        return -1;
    }
    vl53L0XDev->I2cDevAddr=0x29;
    vl53L0XDev->comms_type=VL53L0X_COMMS_I2C=0;
    vl53L0XDev->comms_speed_khz=100;
    return VL53L0X_DataInit(vl53L0XDev);
}
extern "C"
JNIEXPORT jchar JNICALL
Java_com_adiuvo_rangesensor_RangeSensor_staticInit(JNIEnv *env, jobject thiz) {
    vl53L0XDev = (VL53L0X_DEV)malloc(sizeof(VL53L0X_Dev_t));
    if (vl53L0XDev == NULL) {
        // Handle memory allocation error
        return -1;
    }
    vl53L0XDev->I2cDevAddr=0x29;
    vl53L0XDev->comms_type=VL53L0X_COMMS_I2C=0;
    vl53L0XDev->comms_speed_khz=100;
    return VL53L0X_StaticInit(vl53L0XDev);
}
extern "C"
JNIEXPORT jchar JNICALL
Java_com_adiuvo_rangesensor_RangeSensor_perfRefSpadManagement(JNIEnv *env, jobject thiz) {
    vl53L0XDev = (VL53L0X_DEV)malloc(sizeof(VL53L0X_Dev_t));
    if (vl53L0XDev == NULL) {
        // Handle memory allocation error
        return -1;
    }
    vl53L0XDev->I2cDevAddr=0x29;
    vl53L0XDev->comms_type=VL53L0X_COMMS_I2C=0;
    vl53L0XDev->comms_speed_khz=100;
    return VL53L0X_PerformRefSpadManagement(vl53L0XDev,&refSpadCount,&isApertureSpads);
}
extern "C"
JNIEXPORT jchar JNICALL
Java_com_adiuvo_rangesensor_RangeSensor_perfRefCalibration(JNIEnv *env, jobject thiz) {
    vl53L0XDev = (VL53L0X_DEV)malloc(sizeof(VL53L0X_Dev_t));
    if (vl53L0XDev == NULL) {
        // Handle memory allocation error
        return -1;
    }
    vl53L0XDev->I2cDevAddr=0x29;
    vl53L0XDev->comms_type=VL53L0X_COMMS_I2C=0;
    vl53L0XDev->comms_speed_khz=100;
    return VL53L0X_PerformRefCalibration(vl53L0XDev,&pVhvSettings,&pPhaseCal);
}
extern "C"
JNIEXPORT jchar JNICALL
Java_com_adiuvo_rangesensor_RangeSensor_perfOffsetCalibration(JNIEnv *env, jobject thiz) {
    vl53L0XDev = (VL53L0X_DEV)malloc(sizeof(VL53L0X_Dev_t));
    if (vl53L0XDev == NULL) {
        // Handle memory allocation error
        return -1;
    }
    vl53L0XDev->I2cDevAddr=0x29;
    vl53L0XDev->comms_type=VL53L0X_COMMS_I2C=0;
    vl53L0XDev->comms_speed_khz=100;
    return VL53L0X_PerformOffsetCalibration(vl53L0XDev,
                                            CalDistanceMilliMeter,
                                            pOffsetMicroMeter);
}
extern "C"
JNIEXPORT int JNICALL
Java_com_adiuvo_rangesensor_RangeSensor_deviceInit(JNIEnv *env, jobject thiz) {
    vl53L0XDev = (VL53L0X_DEV)malloc(sizeof(VL53L0X_Dev_t));
    if (vl53L0XDev == NULL) {
        // Handle memory allocation error
        return -1;
    }
    vl53L0XDev->I2cDevAddr=0x29;
    vl53L0XDev->comms_type=VL53L0X_COMMS_I2C=0;
    vl53L0XDev->comms_speed_khz=100;
    return VL53L0X_comms_initialise(vl53L0XDev->comms_type,vl53L0XDev->comms_speed_khz);

}
extern "C"
JNIEXPORT jint JNICALL
Java_com_adiuvo_rangesensor_RangeSensor_getDepthSingle(JNIEnv *env, jobject thiz) {
    // TODO: implement getDepthSingle()
    vl53L0XDev = (VL53L0X_DEV)malloc(sizeof(VL53L0X_Dev_t));
    vl53L0XDev->I2cDevAddr=0x29;
    vl53L0XDev->comms_type=VL53L0X_COMMS_I2C=0;
    vl53L0XDev->comms_speed_khz=100;
    LOG_FUNCTION_START("%s %d","Hey Look Here",VL53L0X_PerformSingleRangingMeasurement(vl53L0XDev,&vl53L0XRangingMeasurementData));
    return vl53L0XRangingMeasurementData.TimeStamp;
}