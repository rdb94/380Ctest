package com.example.a380ctest

// import androidx.activity.compose.setContent
import android.content.Intent
import android.os.Bundle
import android.os.Parcel
import android.os.Parcelable
import android.view.View
import android.widget.Switch
import androidx.activity.ComponentActivity
import com.example.a380ctest.databinding.ActivityMainBinding
import com.example.a380ctest.playback.AndroidAudioPlayer
import com.example.a380ctest.recorder.AndroidAudioRecorder
import java.io.File


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
        // Read data from the Parcel (if needed)
    }

    override fun writeToParcel(parcel: Parcel, flags: Int) {
        // Write data to the Parcel (if needed)
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

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = stringFromJNI()

        var switch: Switch = findViewById(R.id.switch1)

        switch.setOnClickListener {
            val intent = Intent(this, ClinicianModeScreen::class.java)
            startActivity(intent)
        }
    }

    fun recordClick(view: View?){
        println("Button clicked!")
    }

    fun audioClick(view: View?){
        println("Button clicked!")
    }
    external fun stringFromJNI(): String
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