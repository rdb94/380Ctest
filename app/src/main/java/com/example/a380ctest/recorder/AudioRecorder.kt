package com.example.a380ctest.recorder
import java.io.File

interface AudioRecorder {
    fun start(outputFile: File)
    fun stop()
}