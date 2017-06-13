#ifdef ENABLE_BLYNK
#include <SPI.h>
#include <BlynkSimpleEsp8266.h>
//#define BLYNK_PRINT Serial

//should get our auth tokens from the web config
//and do real handling of the relay based on the sonoff boilerplate code

//char auth[] = "d80682aa4d8d43b8aee217d0b1f0f86b";

BlynkTimer timer;

//WidgetLED led0(V0);

bool ledStatusBlynk = false;
int sliderValue = 0;
int sliderValueR = 0;
int sliderValueG = 0;
int sliderValueB = 0;

long assembledColor = 0;

void blynkConfigure() {
	  //get the blynkAuth setting
		String blynkToken = getSetting("blynkToken", BLYNK_TOKEN);
		String blynkServer = getSetting("blynkServer",BLYNK_SERVER);
		int blynkPort = getSetting("blynkPort", BLYNK_PORT);
    //fauxmo.enable(getSetting("fauxmoEnabled", FAUXMO_ENABLED).toInt() == 1);
		Blynk.config(blynkToken, blynkServer, blynkPort);

}


void blynkSetup()
{
	blynkConfigure();
  while (Blynk.connect() == false) {
  }
}


void blynkLoop()
{
	Blynk.run();
  timer.run();
}


void timerTick()
{
  if (ledStatusBlynk == 0){
    //DEBUG_MSG_P(PSTR("[blynk] LED on V0 : %s\n"), ledStatusBlynk);
    //led0.off();
    return;
    } else {
      //led0.on();
    }
}


long newColor(){
  int r = sliderValueR << 16;
  int g = sliderValueG << 8;
  int b = sliderValueB;

  long combo = r + g + b;
  return combo;
}


//RED
BLYNK_WRITE(V2){
  sliderValueR = param.asInt();
  long c = newColor();
  String s = "#" + String(c,HEX);
  //DEBUG_MSG_P(PSTR("[blynk] new Color R : %d\n"), sliderValueR);
  //led0.setColor(s);
}

//GREEN
BLYNK_WRITE(V3){
  sliderValueG = param.asInt();
  long c = newColor();
  String s = "#" + String(c,HEX);
  //DEBUG_MSG_P(PSTR("[blynk] new Color G : %d\n"), sliderValueG);
  //led0.setColor(s);
}

//BLUE
BLYNK_WRITE(V4){
  sliderValueB = param.asInt();
  long c = newColor();
  String s = "#" + String(c,HEX);
  //DEBUG_MSG_P(PSTR("[blynk] new Color B : %d\n"), sliderValueB);
  //led0.setColor(s);
}

BLYNK_WRITE(V1)
{
  ledStatusBlynk = param.asInt(); // assigning incoming value from pin V1 to a variable
  //DEBUG_MSG_P(PSTR("[blynk] V1 value is : %d\n"), ledStatusBlynk);
}


#endif
