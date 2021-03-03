// Load Wi-Fi library
#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid     = "YAMAC";
const char* password = "123456789ty";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String kirmiziState = "off";
String yesilState = "off";
String maviState = "off";

// Assign output variables to GPIO pins
const int kirmizi = D1;
const int yesil = D2;
const int mavi = D3;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(kirmizi, OUTPUT);
  pinMode(yesil, OUTPUT);
  pinMode(mavi, OUTPUT);
  // Set outputs to LOW
  digitalWrite(kirmizi, LOW);
  digitalWrite(yesil, LOW);
  digitalWrite(mavi, LOW);

  //Static IP address configuration
IPAddress staticIP(192, 168, 1, 50); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS


const char* deviceName = "Cruiser RGB Mouse";

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);



WiFi.hostname(deviceName);      // DHCP Hostname (useful for finding device for static lease)
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(ssid, password);




  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /kirmizi/on") >= 0) {
              Serial.println("kirmizi on");                     
              kirmiziState = "on";
              digitalWrite(kirmizi, HIGH);
  
            } else if (header.indexOf("GET /kirmizi/off") >= 0) {
              Serial.println("kirmizi off");
              kirmiziState = "off";
              digitalWrite(kirmizi, LOW);
            } else if (header.indexOf("GET /yesil/on") >= 0) {
              Serial.println("yesil on");
              yesilState = "on";
              digitalWrite(yesil, HIGH);
            } else if (header.indexOf("GET /yesil/off") >= 0) {
              Serial.println("yesil off");
              yesilState = "off";
              digitalWrite(yesil, LOW);
            }
            else if (header.indexOf("GET /mavi/on") >= 0) {
              Serial.println("mavi on");
              maviState = "on";
              digitalWrite(mavi, HIGH);
            } else if (header.indexOf("GET /mavi/off") >= 0) {
              Serial.println("mavi off");
              maviState = "off";
              digitalWrite(mavi, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Cruiser RGB Mouse</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 5  
            client.println("<p>KIRMIZI Renk " + kirmiziState + "</p>");
            // If the kirmiziState is off, it displays the ON button       
            if (kirmiziState=="off") {
              client.println("<p><a href=\"/kirmizi/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/kirmizi/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 4  
            client.println("<p>YESIL Renk " + yesilState + "</p>");
            // If the yesilState is off, it displays the ON button       
            if (yesilState=="off") {
              client.println("<p><a href=\"/yesil/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/yesil/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
              // Display current state, and ON/OFF buttons for GPIO 4  
            client.println("<p>MAVI Renk " + maviState + "</p>");
            // If the maviState is off, it displays the ON button       
            if (maviState=="off") {
              client.println("<p><a href=\"/mavi/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/mavi/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
