package com.example.a380ctest


// import androidx.activity.compose.setContent
import android.content.Intent
import android.os.Bundle
import android.os.Parcel
import android.Manifest
import android.annotation.SuppressLint
import android.content.pm.PackageManager
import android.os.Parcelable
import android.util.Log
import android.view.View
import android.widget.Switch
import android.widget.Toast
import androidx.activity.ComponentActivity
import android.content.ContentValues
import android.media.AudioFormat
import android.media.AudioRecord
import android.media.MediaRecorder
import android.media.MediaRecorder.AudioSource.MIC
import android.os.Environment
import android.os.Parcelable.Creator
import android.provider.MediaStore
import android.media.session.PlaybackState
import android.media.session.MediaSession
import android.media.session.MediaController
import android.media.session.MediaSessionManager
import androidx.annotation.RequiresPermission
import java.io.FileOutputStream

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material.Button
import androidx.compose.material.Text
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import androidx.lifecycle.findViewTreeViewModelStoreOwner
import com.example.a380ctest.databinding.ActivityMainBinding
import com.example.a380ctest.playback.AndroidAudioPlayer
import com.example.a380ctest.recorder.AndroidAudioRecorder
import org.w3c.dom.Text
import java.io.File
import java.io.IOException





class MainActivity() : ComponentActivity(), Parcelable {

    private lateinit var binding: ActivityMainBinding

    private val recorder by lazy {
        AndroidAudioRecorder(applicationContext)
    }

    private val player by lazy {
        AndroidAudioPlayer(applicationContext)
    }

    private var audioFile: File? = null



    // Constructor for Parcelable
    constructor(parcel: Parcel) : this() {

    }

    override fun writeToParcel(parcel: Parcel, flags: Int) {

    }

    override fun describeContents(): Int {
        return 0
    }

    // Companion object for Parcelable and Library Loading
    companion object {
        // Load the native library
        init {
            System.loadLibrary("a380ctest")
        }

        // Parcelable CREATOR
        @JvmField
        val CREATOR: Parcelable.Creator<MainActivity> = object : Parcelable.Creator<MainActivity> {
            override fun createFromParcel(parcel: Parcel): MainActivity {
                return MainActivity(parcel)
            }

            override fun newArray(size: Int): Array<MainActivity?> {
                return arrayOfNulls(size)
            }
        }
    }


    private val REQUESTMICPERMISSION = 200


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        //  binding.sampleText.text = stringFromJNI()

        var switch: Switch = findViewById(R.id.switch1)

        switch.setOnClickListener {
            val intent = Intent(this, ClinicianModeScreen::class.java)
            startActivity(intent)
        }

        if (ContextCompat.checkSelfPermission(
                this,
                Manifest.permission.RECORD_AUDIO
            ) != PackageManager.PERMISSION_GRANTED
        ) {
            ActivityCompat.requestPermissions(
                this,
                arrayOf(Manifest.permission.RECORD_AUDIO),
                REQUESTMICPERMISSION
            )
        } else {
            startAnalysis()
        }




        if(ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(this, arrayOf(Manifest.permission.WRITE_EXTERNAL_STORAGE), 1)
        }


        //NOT THIS NOT USING ANYWAY LEAVE COMMENTED OUT
//        setContent {
//            AudioRecorderTheme{
//                Column(
//                    modifier = Modifier.fillMaxSize(),
//                    verticalArrangement = Arrangement.Center,
//                    horizontalAlignment = Alignment.CenterHorizontally
//                ) {
//                    Button(onClick = {
//                        File(cacheDir, "audio.mp3").also {
//                            recorder.start(it)
//                            audioFile = it
//                        }
//                    }) {
//                        Text(text = "Start Recording")
//                    }
//                }
//            }
//        }

    }


    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<out String>,
        grantResults: IntArray,
        deviceId: Int

    ) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults, deviceId)

        if (requestCode == REQUESTMICPERMISSION) {
            if (grantResults.isNotEmpty() && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                startAnalysis()
            } else {
                Toast.makeText(this, "Microphone permission is required", Toast.LENGTH_SHORT).show()
            }
        }
    }

//    private fun startAnalysis() {
//
//    }

    //TRYING OUT NEW CODE
    private lateinit var audioRecord: AudioRecord
    private lateinit var audioData: ByteArray

    private val sampleRate = 44100  // Sample rate, for example 44.1kHz
    private val channelConfig = AudioFormat.CHANNEL_IN_MONO
    private val audioFormat = AudioFormat.ENCODING_PCM_16BIT
    private val bufferSize = AudioRecord.getMinBufferSize(sampleRate, channelConfig, audioFormat)

    private fun startAnalysis() {
        audioData = ByteArray(bufferSize)
        @SuppressLint("MissingPermission")
        audioRecord = AudioRecord(
            MIC,
            sampleRate,
            channelConfig,
            audioFormat,
            bufferSize
        )
    }

    //New

//    private val sampleRate = 44100  // Sample rate, for example 44.1kHz
//    private val channelConfig = AudioFormat.CHANNEL_IN_MONO
//    private val audioFormat = AudioFormat.ENCODING_PCM_16BIT

//    private val bufferSize = AudioRecord.getMinBufferSize(sampleRate, channelConfig, audioFormat)
    //needs permission first but app already has permission in general so can't figure out why this is unhappy
//    @SuppressLint("MissingPermission")
//    @RequiresPermission(value = "android.permission.RECORD_AUDIO")
//    private val audioRecord = AudioRecord(
//        MIC,
//        sampleRate,
//        channelConfig,
//        audioFormat,
//        bufferSize
//    )

//    private val audioData = ByteArray(bufferSize)  // This will hold the audio data captured from the microphone

    private val outputStream = FileOutputStream(audioFile)
    //END NEW CODE


    fun recordClick(view: View?) {
        println("Button clicked!")
        File(cacheDir, "audio.mp3").also {
            recorder.start(it)
            audioFile = it
            // Start recording
            audioRecord.startRecording()

            // Record audio for 5 seconds (for example)
            val audioFile = File(filesDir, "audio_recording.pcm")
//            val uri = contentResolver.insert(MediaStore.Audio.Media.EXTERNAL_CONTENT_URI, values)
//            uri?.let {
//                contentResolver.openOutputStream(it)?.use { outputStream ->
//                    outputStream.write(audioData)
//                }
//            }

//            val outputStream = FileOutputStream(audioFile)

                val read = audioRecord.read(audioData, 0, bufferSize)
                if (read > 0) {
                    // Write the audio data into the file
                    outputStream.write(audioData, 0, read)
                }


// trying to save externally
            val values = ContentValues().apply {
                put(MediaStore.Audio.Media.DISPLAY_NAME, "newAudio.mp3")
                put(MediaStore.Audio.Media.MIME_TYPE, "audio/wav")
                put(MediaStore.Audio.Media.RELATIVE_PATH, Environment.DIRECTORY_MUSIC)

            }
            val contentResolver = contentResolver
            val uri = contentResolver.insert(MediaStore.Audio.Media.EXTERNAL_CONTENT_URI,values)
    }
        val audioFile = File(filesDir, "audio_recording.pcm")
        val outputStream = FileOutputStream(audioFile)

        outputStream.write(audioData)
        outputStream.close()
        }


            fun recordStop(view: View?) {
                recorder.stop()

                //new
                audioRecord.stop()
                audioRecord.release()
                outputStream.close()

            }

            fun playStart(view: View?) {

                player.playFile(audioFile ?: return)
            }

            fun playStop(view: View?) {
                player.stop()
            }

            fun audioClick(view: View?) {
                println("Button clicked!")
            }

            // external fun stringFromJNI(): String


        }




/*
        fun main() {
            val Fs = 4000
            val Channels = 1
            val bits = 16
            val duration = 5

            println("Please begin speaking")
            println("Recording Started")
            val X = recordAudio(Fs, bits, Channels, duration)
            println("Recording Stopped")

            // Audio filtering
            val BandStop60Hz = createBandStopFilter(Fs)
            val filteredX = filter(BandStop60Hz, X)

            // Check to see if there's noise in the signal (Seems fine)
            val Test = fft(filteredX)
            val T0 = filteredX.size.toDouble() / Fs
            val freqStep = 1 / T0
            val freqVec = DoubleArray(filteredX.size) { i -> -Fs / 2 + i * freqStep }

            plotFrequencyDomain(freqVec, Test)

            // Ask for gender
            val scanner = Scanner(System.`in`)
            println("Is the sex of the subject male or female? Please enter M/F: ")
            val sex = scanner.nextLine()

            plotTimeDomain(filteredX, Fs)

            val HNR = calculateHNR(filteredX, Fs)
            val HNRpublish = abs(HNR) * 100
            val (jitt, shim) = analyzePeriodicity(filteredX, Fs)
            val yourvals = doubleArrayOf(abs(HNR) * 100, jitt, shim)

            checkRanges(sex, jitt, shim, HNRpublish)

            val StatsCol = arrayOf("Measured Value", "Recommended Value")
            val StatsRows = arrayOf("HNR", "Jitter %", "Shimmer%")
            val StatsTable = arrayOf(yourvals, getRecommendedValues(sex))

            displayStatsTable(StatsTable, StatsCol, StatsRows)
        }

        fun recordAudio(Fs: Int, bits: Int, Channels: Int, duration: Int): DoubleArray {
            // Implement audio recording logic here
            return DoubleArray(Fs * duration)
        }

        fun createBandStopFilter(Fs: Int): DoubleArray {
            // Implement band-stop filter creation logic here
            return DoubleArray(Fs)
        }

        fun filter(filter: DoubleArray, signal: DoubleArray): DoubleArray {
            // Implement filtering logic here
            return signal
        }

        fun fft(signal: DoubleArray): DoubleArray {
            // Implement FFT logic here
            return signal
        }

        fun plotFrequencyDomain(freqVec: DoubleArray, Test: DoubleArray) {
            // Implement frequency domain plotting logic here
        }

        fun plotTimeDomain(signal: DoubleArray, Fs: Int) {
            // Implement time domain plotting logic here
        }

        fun calculateHNR(signal: DoubleArray, Fs: Int): Double {
            // Implement HNR calculation logic here
            return 0.0
        }

        fun analyzePeriodicity(signal: DoubleArray, Fs: Int): Pair<Double, Double> {
            // Implement periodicity analysis logic here
            return Pair(0.0, 0.0)
        }

        fun checkRanges(sex: String, jitt: Double, shim: Double, HNRpublish: Double) {
            val reccvalues = if (sex == "F") {
                arrayOf("0.10 - 0.11", "1.6 - 33.3", "0.14 - 0.17")
            } else {
                arrayOf("0.13", "2.0 - 4.3", "1 - 1.04")
            }

            // Check jitter
            if (sex == "F") {
                if (jitt in 1.6..33.3) {
                    println("Jitter is within acceptable range")
                } else {
                    val jittError = if (jitt < 1.6) 1.6 - jitt else jitt - 33.3
                    println("Jitter is outside of acceptable range by ${"%.2f".format(jittError)}%")
                }
            } else {
                if (jitt in 2.0..4.3) {
                    println("Jitter is within acceptable range")
                } else {
                    val jittError = if (jitt < 2.0) 2.0 - jitt else jitt - 4.3
                    println("Jitter is outside of acceptable range by ${"%.2f".format(jittError)}%")
                }
            }

            // Check shimmer
            if (sex == "F") {
                if (shim in 0.14..0.17) {
                    println("Shimmer is within acceptable range")
                } else {
                    val shimError = if (shim < 0.14) 0.14 - shim else shim - 0.17
                    println("Shimmer is outside of acceptable range by ${"%.2f".format(shimError)}%")
                }
            } else {
                if (shim in 1.0..1.04) {
                    println("Shimmer is within acceptable range")
                } else {
                    val shimError = if (shim < 1.0) 1.0 - shim else shim - 1.04
                    println("Shimmer is outside of acceptable range by ${"%.2f".format(shimError)}%")
                }
            }

            // Check HNR
            if (sex == "F") {
                if (HNRpublish in 0.10..0.11) {
                    println("Harmonic to noise ratio is within acceptable range")
                } else {
                    val hnrError = if (HNRpublish < 0.10) 0.10 - HNRpublish else HNRpublish - 0.11
                    println(
                        "Harmonic to noise ratio is outside of acceptable range by ${
                            "%.2f".format(
                                hnrError
                            )
                        }"
                    )
                }
            } else {
                if (HNRpublish == 0.13) {
                    println("Harmonic to noise ratio is within acceptable range")
                } else {
                    val hnrError = if (HNRpublish < 0.13) 0.13 - HNRpublish else HNRpublish - 0.13
                    println(
                        "Harmonic to noise ratio is outside of acceptable range by ${
                            "%.2f".format(
                                hnrError
                            )
                        }"
                    )
                }
            }
        }

        fun getRecommendedValues(sex: String): DoubleArray {
            return if (sex == "F") {
                doubleArrayOf(0.10, 1.6, 0.14)
            } else {
                doubleArrayOf(0.13, 2.0, 1.0)
            }
        }

        fun displayStatsTable(
            StatsTable: Array<DoubleArray>,
            StatsCol: Array<String>,
            StatsRows: Array<String>
        ) {
            println(StatsCol.joinToString("\t"))
            for (i in StatsRows.indices) {
                println("${StatsRows[i]}\t${StatsTable[0][i]}\t${StatsTable[1][i]}")
            }
        }
    }
}

 */