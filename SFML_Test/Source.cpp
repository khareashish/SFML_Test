#include<SFML\Audio.hpp> 
#include <cmath>
#include <iostream>
using namespace std; 
using namespace sf; 

int main() {
 
	const unsigned SAMPLES = 992;			// Samples = time period * sample rate = 22.5*44100 = 992 samples
	const unsigned SAMPLE_RATE = 44100;		// Standard for audio 
	const unsigned AMPLITUDE = 30000;		// Amplitude need to be sorted out accoring to DX8 standard 

	Int16 raw[SAMPLES];						// raw stream of samples 
											// fill one time period in the raw sample array 								
				
	for (unsigned i = 0; i < SAMPLES/2; i++) { 
		raw[i] = AMPLITUDE ;
	}
	for (unsigned i = SAMPLES / 2; i < SAMPLES; i++){
		raw[i] = 0; 
	}

	SoundBuffer Buffer;						// define a sound buffer and load raw samples to buffer 
	if (!Buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE)) {
		std::cerr << "Loading failed!" << std::endl;
		return 1;
	}

	Sound Sound;						// create sound object 
	Sound.setBuffer(Buffer);			// pass the buffer we created 
	Sound.setLoop(true);				// play sound in loop 
	Sound.play();					
	while (1) {							// If the program ends, the audio will end too so we make it wait infinitely 	
		sleep(milliseconds(1000));
	}
	return 0;
}