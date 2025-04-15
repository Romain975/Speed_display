#include "Wire.h"
#include "MPU6050.h"

MPU6050 mpu;

void setup() {
  Wire.begin();
  mpu.initialize();
  
  Serial.begin(9600);
  while (!Serial) {
    // Attendez que la connexion série soit établie (pour les cartes Arduino qui nécessitent cela)
  }
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  Serial.print("Accel X: "); Serial.print(ax);
  Serial.print(" Accel Y: "); Serial.print(ay);
  Serial.print(" Accel Z: "); Serial.print(az);
  Serial.print(" Gyro X: "); Serial.print(gx);
  Serial.print(" Gyro Y: "); Serial.print(gy);
  Serial.print(" Gyro Z: "); Serial.println(gz);
  
  delay(1000);
}
