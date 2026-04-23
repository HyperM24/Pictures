int coil1 = 10;
int coil2 = 11;
float scaler = 0;

void setup() {
  Serial.begin(9600);
  pinMode(coil1, OUTPUT);
  pinMode(coil2, OUTPUT);
}

void playNote(float frequency, float duration)
{
  if (frequency <= 0) {
    delay(duration);
  } else
  {
    float halfPeriod = 500000.0 / frequency;
    long iterations = (duration * 1000.0) / (halfPeriod * 2.0);
    for (long i = 0; i < iterations; i++) {
      digitalWrite(coil1, HIGH);
      digitalWrite(coil2, LOW);
      delayMicroseconds(halfPeriod);
      digitalWrite(coil1, LOW);
      digitalWrite(coil2, HIGH);
      delayMicroseconds(halfPeriod);
    }
    digitalWrite(coil1, LOW);
    digitalWrite(coil2, LOW);
  }
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    if (input.length() > 0) {
      if (input.indexOf(':') == -1) {
        scaler = input.toFloat();
        Serial.print("K");
      } 
      else {
        int separatorIndex = input.indexOf(':');
        float frequency = input.substring(0, separatorIndex).toFloat();
        float scale = input.substring(separatorIndex + 1).toFloat();
        float duration = scale * scaler;
        playNote(frequency, duration);
        Serial.print("K");
      }
    }
  }
}
