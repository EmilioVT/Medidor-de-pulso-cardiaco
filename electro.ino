/*---------------------------------------------------------
            Arquitectura de computadoras.
                Electrocardiograma.
 
            Integrantes:
            Ruiz Rivas, Juan Alexander
            Villatoro Torres, Emilio Jose 
            Cañas Barrientos, Dennis Vladimir
            Mejia Granados, Juan Antonio
---------------------------------------------------------*/
#define PLOTT_DATA 
#define MAX_BUFFER 100

uint32_t prevData[MAX_BUFFER];
uint32_t sumData=0;
uint32_t maxData=0;
uint32_t avgData=0;
uint32_t roundrobin=0;
uint32_t countData=0;
uint32_t period=0;
uint32_t lastperiod=0;
uint32_t millistimer=millis();
double frequency;
double beatspermin=0;
uint32_t newData;

void freqDetec() {
  if (countData==MAX_BUFFER) {
   if (prevData[roundrobin] < avgData*1.5 && newData >= avgData*1.5){ // incrementando y cruzando el último punto medio
    period = millis()-millistimer;//obtener un período del valor del temporizador actual
    millistimer = millis();//reset timer
    maxData = 0;
   }
  }
 roundrobin++;
 if (roundrobin >= MAX_BUFFER) {
    roundrobin=0;
 }
 if (countData<MAX_BUFFER) {
    countData++;
    sumData+=newData;
 } else {
    sumData+=newData-prevData[roundrobin];
 }
 avgData = sumData/countData;
 if (newData>maxData) {
  maxData = newData;
 }

#ifdef PLOTT_DATA
 Serial.print(newData);
 Serial.print("\t");
 Serial.print(avgData);
 Serial.print("\t");
 Serial.print(avgData*1.5);
 Serial.print("\t");
 Serial.print(maxData);
 Serial.print("\t");
 Serial.println(beatspermin);
#endif
 prevData[roundrobin] = newData;//almacena valor anterior
}

void setup() {
  Serial.begin(4800);
}

void loop() {
  newData = analogRead(25);
  freqDetec();
  if (period!=lastperiod) {
     frequency = 10000/(double)period;//tasa/periodo
     if (frequency*60 > 20 && frequency*60 < 200) { 
      beatspermin=frequency*60;
#ifndef PLOTT_DATA
        Serial.print(frequency);
        Serial.print(" hz");
        Serial.print(" ");
        Serial.print(beatspermin);
        Serial.println(" bpm");
#endif
        lastperiod=period;
     }
  }
  delay(5);
}
