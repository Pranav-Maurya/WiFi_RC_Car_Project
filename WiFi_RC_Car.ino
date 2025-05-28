#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoOTA.h>
#include <DHT.h>

// Motor Control Pins
int in1 = D5;
int in2 = D6;
int in3 = D7;
int in4 = D8;

// Other Components
const int buzPin = D0;
const int ledPin = D1;
const int wifiLedPin = D2;

// Ultrasonic Sensor Pins
const int trigPin = D3;
const int echoPin = D4;

// DHT11 Temperature & Humidity Sensor
#define DHTPIN 3  // GPIO3 (RX)
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

String command;
int SPEED = 122;
int speed_Coeff = 3;

ESP8266WebServer server(80);
unsigned long previousMillis = 0;
String sta_ssid = "";
String sta_password = "";

void setup() {
  Serial.begin(115200);
  Serial.println("\n*WiFi Robot with Sensors*");

  pinMode(buzPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(wifiLedPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(buzPin, LOW);
  digitalWrite(ledPin, LOW);
  digitalWrite(wifiLedPin, HIGH);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  dht.begin();  // Initialize DHT11 sensor

  WiFi.mode(WIFI_AP);
  WiFi.softAP("WiFi_RC_Car");
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  server.on("/", HTTP_handleRoot);
  server.on("/sensorData", HTTP_handleSensorData);
  server.onNotFound(HTTP_handleRoot);
  server.begin();
  ArduinoOTA.begin();
}

void loop() {
  ArduinoOTA.handle();
  server.handleClient();
  command = server.arg("State");
  if (command == "F") Forward();
  else if (command == "B") Backward();
  else if (command == "R") TurnRight();
  else if (command == "L") TurnLeft();
  else if (command == "G") ForwardLeft();
  else if (command == "H") BackwardLeft();
  else if (command == "I") ForwardRight();
  else if (command == "J") BackwardRight();
  else if (command == "S") Stop();
  else if (command == "V") BeepHorn();
  else if (command == "W") TurnLightOn();
  else if (command == "w") TurnLightOff();
}

// 🖥 Web Page
void HTTP_handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
        <title>ESP8266 Sensor Data</title>
        <style>
            body { font-family: Arial, sans-serif; text-align: center; background-color: #f2f2f2; }
            .container { width: 80%%; margin: auto; background: white; padding: 20px; box-shadow: 0px 0px 10px #aaa; border-radius: 10px; }
            h1 { color: #333; }
            .data-box { font-size: 24px; font-weight: bold; color: #007bff; margin: 10px; }
        </style>
        <script>
            function updateData() {
                fetch('/sensorData')
                .then(response => response.json())
                .then(data => {
                    document.getElementById('distance').innerText = data.distance + ' cm';
                    document.getElementById('temperature').innerText = data.temperature + ' °C';
                    document.getElementById('humidity').innerText = data.humidity + ' %';
                });
            }
            setInterval(updateData, 1000);
        </script>
    </head>
    <body>
        <div class="container">
            <h1>ESP8266 Sensor Data</h1>
            <p class="data-box">Distance: <span id="distance">--</span></p>
            <p class="data-box">Temperature: <span id="temperature">--</span></p>
            <p class="data-box">Humidity: <span id="humidity">--</span></p>
        </div>
    </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", html);
}

// 🌡 Sensor Data Response
void HTTP_handleSensorData() {
  float distance = measureDistance();
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  String response = "{\"distance\": " + String(distance) + 
                    ", \"temperature\": " + String(temperature) + 
                    ", \"humidity\": " + String(humidity) + "}";

  server.send(200, "application/json", response);
}

// 📏 Ultrasonic Distance Measurement
float measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
  return distance;
}

// 🏎 Motor Controls
void Forward() {
  analogWrite(in1, SPEED);
  digitalWrite(in2, LOW);
  analogWrite(in3, SPEED);
  digitalWrite(in4, LOW);
}

void Backward() {
  digitalWrite(in1, LOW);
  analogWrite(in2, SPEED);
  digitalWrite(in3, LOW);
  analogWrite(in4, SPEED);
}

void TurnRight() {
  digitalWrite(in1, LOW);
  analogWrite(in2, SPEED);
  analogWrite(in3, SPEED);
  digitalWrite(in4, LOW);
}

void TurnLeft() {
  analogWrite(in1, SPEED);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  analogWrite(in4, SPEED);
}

void ForwardLeft() {
  analogWrite(in1, SPEED);
  digitalWrite(in2, LOW);
  analogWrite(in3, SPEED / speed_Coeff);
  digitalWrite(in4, LOW);
}

void BackwardLeft() {
  digitalWrite(in1, LOW);
  analogWrite(in2, SPEED);
  digitalWrite(in3, LOW);
  analogWrite(in4, SPEED / speed_Coeff);
}

void ForwardRight() {
  analogWrite(in1, SPEED / speed_Coeff);
  digitalWrite(in2, LOW);
  analogWrite(in3, SPEED);
  digitalWrite(in4, LOW);
}

void BackwardRight() {
  digitalWrite(in1, LOW);
  analogWrite(in2, SPEED / speed_Coeff);
  digitalWrite(in3, LOW);
  analogWrite(in4, SPEED);
}

void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

// 🚨 Beep Horn
void BeepHorn() {
  digitalWrite(buzPin, HIGH);
  delay(150);
  digitalWrite(buzPin, LOW);
  delay(80);
}

// 💡 Lights
void TurnLightOn() {
  digitalWrite(ledPin, HIGH);
}

void TurnLightOff() {
  digitalWrite(ledPin, LOW);
}
