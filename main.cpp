#include <Audio.h>
#include <SD.h>
#include "effect_dynamics.h"
// GUItool: begin automatically generated code
#ifdef BUILD_FOR_LINUX
#include <output_soundio.h>
#include <input_soundio.h>
#include "teensy_main.h"
AudioOutputSoundIO       output;           //xy=740,266
#else
AudioOutputTDM             output;           //xy=740,266
#endif
AudioEffectDynamics      dynamics;
AudioPlaySdRaw           raw;
AudioRecordQueue         queue;
AudioConnection connection1(raw,        0, dynamics,    0);
AudioConnection connection2(dynamics,   0, output,      0);
AudioConnection connection3(dynamics,   0, queue,       0);
// GUItool: end automatically generated code

File file;

void setup() {
    Serial.begin(57600);
    AudioMemory(24);
    #ifdef BUILD_FOR_LINUX
    SD.setSDCardFolderPath("../");
    #endif
    raw.play("original.raw");
    dynamics.makeupGain(6.0f);
    queue.begin();
    file = SD.open("compressed.raw", O_WRITE);
}

void loop() {
    if (!raw.isPlaying()) {
        queue.end();
        file.close();
    }

    if (queue.available()) {
        uint8_t *buffer = reinterpret_cast<uint8_t *>(queue.readBuffer());
        file.write(buffer, AUDIO_BLOCK_SAMPLES * 2);
        queue.freeBuffer();
        file.flush();
    }
}

