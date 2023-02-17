// Basic demo for readings from Adafruit BNO08x
#include <Adafruit_BNO08x.h>
#include <Math.h>

// For SPI mode, we need a CS pin
#define BNO08X_CS 10
#define BNO08X_INT 9

// For SPI mode, we also need a RESET
//#define BNO08X_RESET 5
// but not for I2C or UART
#define BNO08X_RESET -1

Adafruit_BNO08x bno08x(BNO08X_RESET);
sh2_SensorValue_t sensorValue;

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit BNO08x test!");

  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);

  // Try to initialize!
  if (!bno08x.begin_I2C()) {
    // if (!bno08x.begin_UART(&Serial1)) {  // Requires a device with > 300 byte
    // UART buffer! if (!bno08x.begin_SPI(BNO08X_CS, BNO08X_INT)) {
    Serial.println("Failed to find BNO08x chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("BNO08x Found!");

  for (int n = 0; n < bno08x.prodIds.numEntries; n++) {
    Serial.print("Part ");
    Serial.print(bno08x.prodIds.entry[n].swPartNumber);
    Serial.print(": Version :");
    Serial.print(bno08x.prodIds.entry[n].swVersionMajor);
    Serial.print(".");
    Serial.print(bno08x.prodIds.entry[n].swVersionMinor);
    Serial.print(".");
    Serial.print(bno08x.prodIds.entry[n].swVersionPatch);
    Serial.print(" Build ");
    Serial.println(bno08x.prodIds.entry[n].swBuildNumber);
  }

  setReports();

  Serial.println("Reading events");
  delay(100);
}

// Here is where you define the sensor outputs you want to receive
void setReports(void) {
  Serial.println("Setting desired reports");
  if (!bno08x.enableReport(SH2_ACCELEROMETER)) {
    Serial.println("Could not enable accelerometer");
  }
}
void printActivity(uint8_t activity_id) {
  switch (activity_id) {
  case PAC_UNKNOWN:
    Serial.print("Unknown");
    break;
  case PAC_IN_VEHICLE:
    Serial.print("In Vehicle");
    break;
  case PAC_ON_BICYCLE:
    Serial.print("On Bicycle");
    break;
  case PAC_ON_FOOT:
    Serial.print("On Foot");
    break;
  case PAC_STILL:
    Serial.print("Still");
    break;
  case PAC_TILTING:
    Serial.print("Tilting");
    break;
  case PAC_WALKING:
    Serial.print("Walking");
    break;
  case PAC_RUNNING:
    Serial.print("Running");
    break;
  case PAC_ON_STAIRS:
    Serial.print("On Stairs");
    break;
  default:
    Serial.print("NOT LISTED");
  }
  Serial.print(" (");
  Serial.print(activity_id);
  Serial.print(")");
}

int counter = 0;
int pp_p = 0, pp_n = 0, pn_p = 0, pn_n = 0;
void loop() {
  delay(20);

  if (bno08x.wasReset()) {
    Serial.print("sensor was reset ");
    setReports();
  }

  if (!bno08x.getSensorEvent(&sensorValue)) {
    delay(10);
    return;
  }
  if (counter == 0)
    delay(5000);
  else if (counter < 50)
    Serial.println("MOVE OBJECT");
  else if (counter == 50)
    delay(5000);
  else if (counter < 101)
    Serial.println("STOP");
  else {
    Serial.print("pp_p");
    Serial.println(pp_p);
    Serial.print("pp_n");
    Serial.println(pp_n);
    Serial.print("pn_p");
    Serial.println(pn_p);
    Serial.print("pn_n");
    Serial.println(pn_n);
    return;
  }

  double x = 0, y = 0, z = 0;
  switch (sensorValue.sensorId) {

    case SH2_ACCELEROMETER:
    Serial.print("Accelerometer - x: ");
    x = sensorValue.un.accelerometer.x;
    Serial.print(x);
    Serial.print(" y: ");
    y = sensorValue.un.accelerometer.y;
    Serial.print(y);
    Serial.print(" z: ");
    z = sensorValue.un.accelerometer.z;
    Serial.println(sensorValue.un.accelerometer.z);
    double magnitude = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
    Serial.print("magnitude = ");
    Serial.println(magnitude);
    Serial.println(double(x));
    Serial.println(double(y));
    Serial.println(double(z));
    if (magnitude > 10) {
      Serial.println("****In Motion****");
      if (counter < 50)
        pp_p++;
      else if (counter < 100)
        pp_n++;
    }
    else {
      Serial.println("****Stable****");
      if (counter < 50)
        pn_p++;
      else if (counter < 100)
        pn_n++;  
    }
    counter++;
    break;

//  case SH2_STABILITY_CLASSIFIER: {
//    Serial.print("Stability Classification: ");
//    sh2_StabilityClassifier_t stability = sensorValue.un.stabilityClassifier;
//    switch (stability.classification) {
//    case STABILITY_CLASSIFIER_UNKNOWN:
//      Serial.println("Unknown");
//      break;
//    case STABILITY_CLASSIFIER_ON_TABLE:
//      Serial.println("On Table");
//      break;
//    case STABILITY_CLASSIFIER_STATIONARY:
//      Serial.println("Stationary");
//      break;
//    case STABILITY_CLASSIFIER_STABLE:
//      Serial.println("Stable");
//      break;
//    case STABILITY_CLASSIFIER_MOTION:
//      Serial.println("In Motion");
//      break;
//    }
//    break;
//  }

  }
}
