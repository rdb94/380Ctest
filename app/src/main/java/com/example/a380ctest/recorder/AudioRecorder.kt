package com.example.a380ctest.recorder

interface AudioRecorder {
    fun start(outputFile: File)
    fun stop()
}