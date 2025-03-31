package com.example.a380ctest.playback

import java.io.File

interface AudioPlayer {
    fun playFile(file: File)
    fun stop()
}