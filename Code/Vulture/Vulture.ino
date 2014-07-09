//////////////////////////////////////////////////////////////////////
///     Robot Vulture                                              ///
///    Written by Ward Prescott  CPE Bucknell '17                  ///
///                              								   ///
///    for Joe Meiser - 2014                                       ///
///                                                                ///
//////////////////////////////////////////////////////////////////////

//#include "VultureBoard.h"
#include "WaveUtil.h"
#include "WaveHC.h"

SdReader card;
FatVolume vol;
FatReader root;
FatReader f;

uint8_t dirLevel;
dir_t dirBuf;

WaveHC wave;


void setup(){           ///Consider robustness offered by the tutorial document
	Serial.begin(9600);

	Serial.println("Program Starting.");

	Serial.print("Free RAM:");
	Serial.println(FreeRam());

	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);

	if (!card.init(true)) {
		Serial.println("Card initialization Failed");
		sdErrorCheck();
		while(1);
	}

	card.partialBlockRead(true);

	uint8_t part;
	for (part =0; part< 5;part++){
		if (vol.init(card, part)){
			break;
		}
		
		if (part == 5){
			Serial.println("No Valid FAT Partition");
			sdErrorCheck();
			while(1);
		}	

	}

	Serial.println("Using Partition:");
	Serial.print(part, DEC);
	Serial.print(vol.fatType(),DEC);

	if (!root.openRoot(vol)){
		Serial.println("Cant open root directory");
		while(1);
	}





}

void loop(){
playfile("EPICSAX.WAV");
while(wave.isplaying){
			Serial.print(".");
			delay(100);
		}
delay(5000);
}


void playfile(char *name){
if(wave.isplaying){
  wave.stop();
}
if (!f.open(root, name)){
}
if(!wave.create(f)){
}
wave.play();
}
//void playFile(){
//	Serial.println("Playing");
//	if (!wave.create(file)){
//		Serial.println("Not a proper WAV");
//	}
//	else{
//		wave.play();
//
//
//	}
//}

///// Movement Helper Functions   ////

void moveHead(int amount){

}


void flapWings(int amount){

}

void moveWingL(int amount){

}

void moveWingR(int amount){

}

void sdErrorCheck(void) {
  if (!card.errorCode()) return;
  PgmPrint("\r\nSD I/O error: ");
  Serial.print(card.errorCode(), HEX);
  PgmPrint(", ");
  Serial.println(card.errorData(), HEX);
  while(1);
}
