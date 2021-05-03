# AudioEffectDynamics
Dynamics Processor (Gate, Compressor &amp; Limiter) for the Teensy Audio Library

# my version of [MarkzP/AudioEffectDynamics](https://github.com/MarkzP/AudioEffectDynamics)
* removes theoretical divide by zero when rms == 0 (sqrt_uint32(0) will divide by zero, thou it doesnt seem to cause any issues) 
* uses running rms calculation and applies gain per sample instead of rms calculation per audio block and applying a constant gain to entire audio buffer 
* adds some build stuff
