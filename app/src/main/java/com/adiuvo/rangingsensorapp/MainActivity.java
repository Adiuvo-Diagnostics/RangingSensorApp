package com.adiuvo.rangingsensorapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;

import com.adiuvo.rangesensor.RangeSensor;
import com.adiuvo.rangingsensorapp.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {
    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        RangeSensor rangeSensor= new RangeSensor();

        binding.deviceInit.setOnClickListener(view -> {
            setText("Device Initialization Status: "+String.valueOf(rangeSensor.deviceInit()));
        });

        binding.dataInit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                setText("Data Initialization Status: "+String.valueOf(rangeSensor.dataInit()));
            }
        });

        binding.staticInit.setOnClickListener(view -> setText("Static Initialization Status: "+String.valueOf(rangeSensor.staticInit())));

        binding.refSpadCalib.setOnClickListener(view -> {
            setText("Ref Spad Calibration Status: "+String.valueOf(rangeSensor.perfRefSpadManagement()));
        });

        binding.perfRefCalib.setOnClickListener(view -> {
            setText("Ref Spad Calibration Status: "+String.valueOf(rangeSensor.perfRefCalibration()));
        });

        binding.perfOffsetCalib.setOnClickListener(view -> {
            setText("Ref Spad Calibration Status: "+String.valueOf(rangeSensor.perfOffsetCalibration()));
        });
        binding.getDepth.setOnClickListener(view -> {
            setText("GetDepthData: "+String.valueOf(rangeSensor.getDepthSingle()));
        });

    }

    void setText(String s){
        binding.sampleText.setText(s);
    }


}