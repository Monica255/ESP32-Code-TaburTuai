// branch mamasa

// Library Firebase ESP32
#include <WiFi.h>
#include <FirebaseESP32.h>

// Library Sensor DHT
#include <DHT.h>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// Pin Sensor
#define SOILPIN       32   // Soil sensor 1 (ADC input)
#define SOILPIN2      35   // Soil sensor 2 (ADC input, input only)
#define DHTPIN        5    // DHT sensor (moved from 15 to 5 for safety)

// Pin Pumps
#define POMPA1PIN     4
#define POMPA2PIN     16
#define POMPA3PIN     18
#define POMPA4PIN     19

// Pin Solenoids
#define SELENOID1PIN  21
#define SELENOID2PIN  22
#define SELENOID3PIN  23
#define SELENOID4PIN  25
#define SELENOID5PIN  26
#define SELENOID6PIN  27
#define SELENOID7PIN  13
#define SELENOID8PIN  14
#define SELENOID9PIN  12
#define SELENOID10PIN 33

// Pin Water Flow
#define WATER_FLOW    17   // Water flow sensor (interrupt capable)

//#define DHTTYPE Sensor;
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//wifi dan password
#define WIFI_SSID "Wifi"
#define WIFI_PASSWORD "Wifi12345"

#define API_KEY "AIzaSyAU9mj87Pq1ixTQm7lkzMHtaz1Eqm0Iht0"
#define USER_EMAIL "test@test.com"
#define USER_PASSWORD "123456"
#define UID "ptU23GhT8Fe6X2hcURilMcz4ykv2"

FirebaseData fbdo;
FirebaseJson json;
FirebaseAuth auth;
FirebaseConfig config;

String uid, path, pathPompaK1, pathPompaK2, pathPompaK3, pathPompaK4, pathMonitoring;
String pathSelenoid1, pathSelenoid2, pathSelenoid3, pathSelenoid4, pathSelenoid5, pathSelenoid6, pathSelenoid7, pathSelenoid8, pathSelenoid9, pathSelenoid10;

// init variabel value sensor
//int bacaSensorPH = 0;   //membaca hasil dari sensor pH
int valTemp, valHum;
// int valCm;
int valSoil;
int valSoil2;

// init variabel status 0/1
int statePompa1, statePompa2, statePompa3, statePompa4;
int stateSelenoid1, stateSelenoid2, stateSelenoid3, stateSelenoid4, stateSelenoid5, stateSelenoid6, stateSelenoid7, stateSelenoid8, stateSelenoid9, stateSelenoid10;


// init variable water level, flow, and out
long currentMillis = 0;
long previousMillis = 0;
int interval = 1000;
float calibrationFactor = 4.5;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

void IRAM_ATTR pulseCounter()
{
 pulseCount++;
}

void initPin() {
  pinMode(POMPA1PIN, OUTPUT);
  pinMode(POMPA2PIN, OUTPUT);
  pinMode(POMPA3PIN, OUTPUT);
  pinMode(POMPA4PIN, OUTPUT);

  pinMode(SELENOID1PIN, OUTPUT);
  pinMode(SELENOID2PIN, OUTPUT);
  pinMode(SELENOID3PIN, OUTPUT);
  pinMode(SELENOID4PIN, OUTPUT);
  pinMode(SELENOID5PIN, OUTPUT);
  pinMode(SELENOID6PIN, OUTPUT);
  pinMode(SELENOID7PIN, OUTPUT);
  pinMode(SELENOID8PIN, OUTPUT);
  pinMode(SELENOID9PIN, OUTPUT);
  pinMode(SELENOID10PIN, OUTPUT);

  pinMode(SOILPIN, INPUT);
  pinMode(SOILPIN2, INPUT);
  
  pinMode(WATER_FLOW, INPUT_PULLUP);
}

void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}

void initFirebase() {
  config.api_key = API_KEY;
    auth.user.email = "test@test.com";
    auth.user.password = "123456";
    uid = UID; 

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  config.database_url = "smart-farming-andro-default-rtdb.asia-southeast1.firebasedatabase.app"; 
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
}


void setup() {
  Serial.begin(115200);

  dht.begin();
  
  initPin();
  initWiFi();
  Serial.println("Connection to Firebase");
  
  initFirebase();
  readFirebase();
   
  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  previousMillis = 0;

  attachInterrupt(digitalPinToInterrupt(WATER_FLOW), pulseCounter, FALLING);
}

void readFirebase(){
  Serial.println("Getting User UID");

  path = "/smart_farming/" + String(uid) + "/realtime_kebun";

  pathPompaK1 =  String(path) + "/kebun_1/controlling/pompa_1/state";
  pathPompaK2 =  String(path) + "/kebun_1/controlling/pompa_2/state";
  pathPompaK3 =  String(path) + "/kebun_1/controlling/pompa_3/state";
  pathPompaK4 =  String(path) + "/kebun_1/controlling/pompa_4/state";

  pathSelenoid1 =  String(path) + "/kebun_1/controlling/selenoid_1/state";
  pathSelenoid2 =  String(path) + "/kebun_1/controlling/selenoid_2/state";
  pathSelenoid3 =  String(path) + "/kebun_1/controlling/selenoid_3/state";
  pathSelenoid4 =  String(path) + "/kebun_1/controlling/selenoid_4/state";
  pathSelenoid5 =  String(path) + "/kebun_1/controlling/selenoid_5/state";
  pathSelenoid6 =  String(path) + "/kebun_1/controlling/selenoid_6/state";
  pathSelenoid7 =  String(path) + "/kebun_1/controlling/selenoid_7/state";
  pathSelenoid8 =  String(path) + "/kebun_1/controlling/selenoid_8/state";
  pathSelenoid9 =  String(path) + "/kebun_1/controlling/selenoid_9/state";
  pathSelenoid10 =  String(path) + "/kebun_1/controlling/selenoid_10/state";

  pathMonitoring = String (path) + "/kebun_1/monitoring";
}

void loop() {
  Serial.print("looping");
  if(!Firebase.ready()){
    initFirebase();
    readFirebase();
    Serial.print("Firebase now ready");
  }
  
  // GET CONNECTION STATE
  get_connection();
  
  // GET STATUS KONTROL
  get_status();

  // READ DATA SENSOR
  read_sensor();

  // KIRIM DATA SENSOR KE FIREBASE
  sent_data();

  delay(1000); 
}
