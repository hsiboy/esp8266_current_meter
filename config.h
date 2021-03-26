/* Config for WiFi and MQTT */


//#define STATIC_IP
IPAddress ip(192, 168, 1, 33);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

const char* SSID_1 = "AP";
const char* Password_1 = "Password";

const char* SSID_2 = "AP";
const char* Password_2 = "Password";

// MQTT Broker
const char* mqtt_server = "192.168.1.10";
const int mqtt_port = 1883;
// MQTT Topics
const char* InStatus = "Current/Status";
const char* InControl = "Current/Control";
String Broadcast_All = "*ALL";

#define Heartbeat_Range   99                      // Event count max value
#define Heatbeat    1000                         // Heartbeat timer value, in mS

// Watchdog items
volatile int Watchdog_Timout = 1200;              // Time in seconds before watchdog times out=20 minutes!

// Heatbeat timer
int Heart_Value = 0;                         
long LastMsg = 0;               

// Custom default values
String WiFi_SSID = "None";                        // SSID string
String My_MAC = "";                               // MAC address, tobe Read from ESP8266
char MAC_array[13] = "000000000000";              // Better MAC definition
//String Mode = "Off";                            // Default mode
volatile int Report_Request = 0;                  // Set to 1 if report required
String Event = "Boot";                            // Default

// I/O
#define StatusLED 2                              // D4
#define StatusLED_On   digitalWrite(StatusLED, HIGH)
#define StatusLED_Off  digitalWrite(StatusLED, LOW)
