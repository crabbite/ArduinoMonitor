
#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library


#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

int previousMode = 1;
int time = 0;
int lasttime = 0;

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Elegoo_TFTLCD tft;

void setup() {
  Serial.begin(9600);
  tft.reset();
  tft.begin(0x9341); // Deine Chip-ID
  tft.setRotation(1); // Querformat
  tft.fillScreen(BLACK);
  
  tft.setCursor(10, 10);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("PC MONITOR");
}

void loop() {
  if (Serial.available() > 0) {
    if(Serial.find('#')){
      int mode = Serial.parseInt();
      int cpuVal = Serial.parseInt();
      int cpuFreq = Serial.parseInt();
      int ramVal = Serial.parseInt();
      int disk = Serial.parseInt();
      if(mode == 1){
        Stats(cpuVal,cpuFreq,ramVal,disk);
      }else{
        Timer();
      }
    }
  }  
}
void Stats(int cpuVal,int cpuFreq,int ramVal,int disk){
  if(previousMode==2){
    tft.fillScreen(BLACK);
    time = 0;
  }
  previousMode =1;
    tft.setCursor(10, 10);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print("PC MONITOR");
 // CPU Anzeige
    tft.setCursor(10, 60);
    tft.setTextColor(WHITE, BLACK); 
    tft.print("CPU: ");
    tft.print(cpuVal);
    tft.print("%  "); // Leerzeichen am Ende löschen Reste von 100% auf 9%
    // CPU Freq Anzeige
    tft.setCursor(10, 110);
    tft.setTextColor(WHITE, BLACK); 
    tft.print("CPU freq: ");
    tft.print(cpuFreq);
    tft.print("mHz  "); // Leerzeichen am Ende löschen Reste von 100% auf 9%
    // RAM Anzeige
    tft.setCursor(10, 160);
    tft.setTextColor(WHITE, BLACK);
    tft.print("RAM: ");
    tft.print(ramVal);
    tft.print("%  ");
    // Disk Anzeige
    tft.setCursor(10, 210);
    tft.setTextColor(WHITE, BLACK);
    tft.print("Disk: ");
    tft.print(disk);
    tft.print("%  ");
}
void Timer(){
  if(previousMode==1){
    tft.fillScreen(BLACK);
  }
  previousMode = 2;
  if(millis()-lasttime>= 1000){
      time ++;
  }
    tft.setCursor(10, 10);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print("Timer");
 // CPU Anzeige
    int hours = time/3600;
    int minutes = (time-hours*3600)/60;
    int seconds = (time-hours*3600)-minutes*60;
    tft.setCursor(10, 60);
    tft.setTextColor(WHITE, BLACK); 
    tft.print("    ");
    printzwei(hours);
    tft.print("h"); 
    printzwei(minutes);
    tft.print("m");
    printzwei(seconds);
    tft.print("s");// Leerzeichen am Ende löschen Reste von 100% auf 9%
}
void printzwei(int zahl){
  if(zahl<10){
    tft.print("0");
  }
  tft.print(zahl);
}






