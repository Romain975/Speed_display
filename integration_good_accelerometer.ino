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

  unsigned long current_time = millis();
  float dt = (current_time - last_time) / 1000.0; // in seconds
  last_time = current_time;

  // Integrate acceleration to get velocity
  velocity_x += ax * dt;
  velocity_y += ay * dt;
  velocity_z += az * dt;

  // Calculate total velocity magnitude
  float total_velocity = sqrt(velocity_x * velocity_x +
                              velocity_y * velocity_y +
                              velocity_z * velocity_z);
  
  Serial.print("Accel X: "); Serial.print(ax);
  Serial.print(" Accel Y: "); Serial.print(ay);
  Serial.print(" Accel Z: "); Serial.print(az);
  Serial.print(" Gyro X: "); Serial.print(gx);
  Serial.print(" Gyro Y: "); Serial.print(gy);
  Serial.print(" Gyro Z: "); Serial.println(gz);
  
  delay(1000);
}
