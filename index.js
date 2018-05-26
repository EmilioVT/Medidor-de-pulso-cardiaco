// abrir puerto serial
var SerialPort = require('serialport');
var port = new SerialPort('COM3', {
  baudRate: 9600
});

var Sensor1 = 0;
var Sensor1Tmp = 0;
var Estado = 0;
var Sensor2 = 0;
var Sensor2Tmp = 0;

// medicion de datos
port.on('data', function(data) {
  console.log("Valor 1 " + Sensor1 );
  for (var i = 0; i < data.length; i++) {
    switch (Estado) {
      case 0:
        if (data[i] == 97) {
          Estado = 1;
          Sensor1Tmp = 0;
        } else if (data[i] == 100) {
          Estado = 2;
          Sensor2Tmp = 0;
        }
        break;
      case 1:
        if (data[i] == 99) {
          Sensor1 = Sensor1Tmp;
          Estado = 0;
          //console.log("El Valor es:" + Sensor1);
        } else {
          Sensor1Tmp = Sensor1Tmp * 10 + data[i];
        }
        break;
      case 2:
        if (data[i] == 101) {
          Sensor2 = Sensor2Tmp;
          Estado = 0;
          //console.log("El Valor es:" + Sensor1);
        } else {
          Sensor2Tmp = Sensor2Tmp * 10 + data[i];
        }
        break;
    }
  }
});

