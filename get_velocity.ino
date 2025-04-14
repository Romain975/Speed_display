#include <math.h>

// Analog pins for accelerometer
const int x_out = A1;
const int y_out = A2;
const int z_out = A3;

// Constants for calibration
const float zero_g_voltage_x = 1.65; // Volts
const float zero_g_voltage_y = 1.65;
const float zero_g_voltage_z = 1.80; // ADXL335 often has slightly different Z offset
const float sensitivity = 0.330;     // Volts per g (adjust for your sensor)

// State variables
double velocity_x = 0;
double velocity_y = 0;
double velocity_z = 0;
unsigned long last_time = 0;

void setup() {
  Serial.begin(9600);
  last_time = millis();
}

void loop() {
  // Read analog values
  int x_adc = analogRead(x_out);
  int y_adc = analogRead(y_out);
  int z_adc = analogRead(z_out);

  // Convert to voltage
  float x_voltage = (x_adc * 5.0) / 1024.0;
  float y_voltage = (y_adc * 5.0) / 1024.0;
  float z_voltage = (z_adc * 5.0) / 1024.0;

  // Convert to acceleration in g
  float x_g = (x_voltage - zero_g_voltage_x) / sensitivity;
  float y_g = (y_voltage - zero_g_voltage_y) / sensitivity;
  float z_g = (z_voltage - zero_g_voltage_z) / sensitivity;

  // Convert to acceleration in m/s²
  float ax = x_g * 9.81;
  float ay = y_g * 9.81;
  float az = z_g * 9.81;

  // Get time delta
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

  // Print raw acceleration
  Serial.print("Ax = "); Serial.print(ax); Serial.print(" m/s^2\t");
  Serial.print("Ay = "); Serial.print(ay); Serial.print(" m/s^2\t");
  Serial.print("Az = "); Serial.print(az); Serial.println(" m/s^2");

  // Print velocity
  Serial.print("Vx = "); Serial.print(velocity_x); Serial.print(" m/s\t");
  Serial.print("Vy = "); Serial.print(velocity_y); Serial.print(" m/s\t");
  Serial.print("Vz = "); Serial.print(velocity_z); Serial.println(" m/s");

  // Print total velocity magnitude
  Serial.print("Total Speed = ");
  Serial.print(total_velocity);
  Serial.println(" m/s");

  Serial.println("------------------------");
  delay(100);
}
