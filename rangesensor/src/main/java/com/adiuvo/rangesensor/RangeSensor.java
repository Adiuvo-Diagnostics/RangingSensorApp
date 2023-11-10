package com.adiuvo.rangesensor;

public class RangeSensor {

    // Used to load the 'rangesensor' library on application startup.
    static {
        System.loadLibrary("rangesensor");
    }

    /**
     * A native method that is implemented by the 'rangesensor' native library,
     * which is packaged with this application.
     */

    public native int deviceInit();
    public native char dataInit();
    public native char staticInit();
    public native char perfRefSpadManagement();
    public native char perfRefCalibration();
    public native char perfOffsetCalibration();

    public native int getDepthSingle();
}