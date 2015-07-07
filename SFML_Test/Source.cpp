#include<SFML\Audio.hpp> 
#include <cmath>
#include<vector>
#include<map>
#include <iostream>
using namespace std; 
using namespace sf; 

int main() {
 
	const unsigned SAMPLES = 992;			// Samples = time period * sample rate = 22.5*44100 = 992 samples
	const unsigned SAMPLE_RATE = 44100;		// Standard for audio 
	double AMPLITUDE = 30000;					// Amplitude need to be sorted out accoring to DX8 standard 
	double microsec = 44; 
	double sync = 0;	
	vector<Int16> frame;					// raw stream of samples 
											// fill one time period in the raw sample array
	vector<Int16>::iterator it; 
	it = frame.begin(); 

	map<int, double > PPMChannels; 
	PPMChannels[1] = 00.00	; 
	PPMChannels[2] = 50.00	;
	PPMChannels[3] = 50.00	;
	PPMChannels[4] = 50.00	;
	PPMChannels[5] = 50.00	;
	PPMChannels[6] = 50.00	;
	PPMChannels[7] = 50.00	;
	PPMChannels[8] = 50.00	;
	



	for(int i = 1; i <= 8; i++)
	{
		sync += PPMChannels[i];
	}
	sync = (int)(13.3-((sync)*0.008)) * 44;
	cout << sync; 
	

	frame.insert(it, (int)(sync), AMPLITUDE);
	it = frame.end(); 
	frame.insert(it, (int)(0.4*microsec), -1*AMPLITUDE); 
	it = frame.end(); 

	for (int i = 1; i <= 8; i++){
	
		frame.insert(it, (int)(.7*microsec), AMPLITUDE); 
		it = frame.end(); 
		frame.insert(it, (int)(PPMChannels[i] * 0.8*microsec / 100), AMPLITUDE); 
		it = frame.end(); 
		frame.insert(it, (int)(0.4*microsec), -1*AMPLITUDE); 
		it = frame.end(); 
	}

	cout << frame.size();
	//size_t SAMPLES = frame.size(); 
	/*for (unsigned i = SAMPLES / 2; i < SAMPLES; i++){
		frame[i] = 0; 
	}*/
	
	Int16* p = &frame[0]; 

	SoundBuffer Buffer;						// define a sound buffer and load raw samples to buffer 
	if (!Buffer.loadFromSamples(p, frame.size(), 1, SAMPLE_RATE)) {
		std::cerr << "Loading failed!" << std::endl;
		return 1;
	}

	Sound Sound;						// create sound object 
	Sound.setBuffer(Buffer);			// pass the buffer we created 
	Sound.setLoop(true);				// play sound in loop 
	Sound.play();					
	while (1) {							// If the program ends, the audio will end too so we make it wait infinitely 	
		sleep(milliseconds(10));
	}
	return 0;
}