const int IRledPin = 13;

void pulseIR(long microsecs) {
   // we'll count down from the number of microseconds we are told to wait
   cli();  // this turns off any background interrupts
   while (microsecs > 0) {
     // 38 kHz is about 13 microseconds high and 13 microseconds low
    digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
    delayMicroseconds(10);         // hang out for 10 microseconds
    digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
    delayMicroseconds(10);         // hang out for 10 microseconds
    // so 26 microseconds altogether
    microsecs -= 26;
   }
   sei();  // this turns them back on
 }

 void SendChannelUpCode() {
   // This is the code for the CHANNEL + for the TV COMCAST
      delayMicroseconds(37988);
      pulseIR(3560);
      delayMicroseconds(2580);
      pulseIR(760);
      delayMicroseconds(1200);
      pulseIR(940);
      delayMicroseconds(1120);
      pulseIR(960);
      delayMicroseconds(1100);
      pulseIR(980);
      delayMicroseconds(1080);
      pulseIR(980);
      delayMicroseconds(1040);
      pulseIR(1020);
      delayMicroseconds(1040);
      pulseIR(1020);
      delayMicroseconds(2140);
      pulseIR(880);
      delayMicroseconds(1100);
      pulseIR(1040);
      delayMicroseconds(1020);
      pulseIR(1060);
      delayMicroseconds(980);
      pulseIR(1080);
      delayMicroseconds(980);
      pulseIR(1080);
      delayMicroseconds(980);
      pulseIR(1080);
      delayMicroseconds(2060);
      pulseIR(960);
      delayMicroseconds(1040);
      pulseIR(1120);
      delayMicroseconds(2020);
      pulseIR(1000);
      delayMicroseconds(2060);
      pulseIR(1040);
      delayMicroseconds(3600);
      pulseIR(1020);
      delayMicroseconds(23060);
      pulseIR(3680);
      delayMicroseconds(2440);
      pulseIR(1160);
      delayMicroseconds(840);
      pulseIR(1220);
      delayMicroseconds(840);
      pulseIR(1200);
      delayMicroseconds(860);
      pulseIR(1200);
      delayMicroseconds(860);
      pulseIR(1200);
      delayMicroseconds(840);
      pulseIR(1200);
      delayMicroseconds(860);
      pulseIR(1200);
      delayMicroseconds(1940);
      pulseIR(1140);
      delayMicroseconds(860);
      pulseIR(1200);
      delayMicroseconds(860);
      pulseIR(1200);
      delayMicroseconds(880);
      pulseIR(1180);
      delayMicroseconds(860);
      pulseIR(1180);
      delayMicroseconds(880);
      pulseIR(1180);
      delayMicroseconds(1960);
      pulseIR(1100);
      delayMicroseconds(900);
      pulseIR(1180);
      delayMicroseconds(1980);
      pulseIR(1060);
      delayMicroseconds(2020);
      pulseIR(1060);
      delayMicroseconds(3600);
      pulseIR(960);
      delayMicroseconds(23180);
      pulseIR(3580);
      delayMicroseconds(2560);
      pulseIR(780);
      delayMicroseconds(1240);
      pulseIR(880);
      delayMicroseconds(1140);
      pulseIR(920);
      delayMicroseconds(1140);
      pulseIR(900);
      delayMicroseconds(1180);
      pulseIR(860);
      delayMicroseconds(1200);
      pulseIR(840);
      delayMicroseconds(1220);
      pulseIR(820);
      delayMicroseconds(2340);
      pulseIR(620);
      delayMicroseconds(1380);
      pulseIR(740);
      delayMicroseconds(1320);
      pulseIR(740);
      delayMicroseconds(1300);
      pulseIR(740);
      delayMicroseconds(1320);
      pulseIR(720);
      delayMicroseconds(1340);
      pulseIR(720);
      delayMicroseconds(2440);
      pulseIR(540);
      delayMicroseconds(1460);
      pulseIR(660);
      delayMicroseconds(2480);
      pulseIR(0);
      delayMicroseconds(20);
      pulseIR(500);
      delayMicroseconds(2580);
      pulseIR(480);
      delayMicroseconds(4180);
      pulseIR(380);


 }
