
String pageHtml = "<!DOCTYPE html>\n"
"<html lang=\"en\">\n"
"<head>\n"
"<meta charset=\"UTF-8\">\n"
"<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
"<title>Led Blink </title>\n"
"</head>\n"
"<body>\n"
"<main class=\"main-container\">\n"
"<header class=\"main-header\">\n"
"<span class=\"header-content\">LED CONTROLLER</span>\n"
"</header>\n"
"<div class=\"content-conatiner\">\n"
"<div class=\"content\">\n"
"<div class=\"content-heading\">LED ONE CONTROLS</div>\n"
"<button onclick=\"onLedOne()\"  >ON</button>\n"
"<button onclick=\"offLedOne()\"  >OFF</button>\n"
"</div>\n"
"<div class=\"content\">\n"
"<div class=\"content-heading\">LED TWO CONTROLS</div>\n"
"<button onclick=\"onLedTwo()\" >ON</button>\n"
"<button onclick=\"offLedTwo()\" >OFF</button>\n"
"</div>\n"
"<div class=\"content\">\n"
"<div class=\"content-heading\">LED THREE CONTROLS</div>\n"
"<button onclick=\"onLedThree()\" >ON</button>\n"
"<button onclick=\"offLedThree()\">OFF</button>\n"
"</div>\n"
"</div>\n"
"</main>\n"
"<script>\n"
"// turn on led one action\n"
"function onLedOne(){\n"
"console.log(\"turn on led one...\");\n"
"const xhr = new XMLHttpRequest();\n"
"xhr.open(\"GET\", \"/onledone\");\n"
"xhr.send();\n"
"}\n"
"// trun off led one action\n"
"function offLedOne(){\n"
"console.log(\"turn off led one...\");\n"
"const xhr = new XMLHttpRequest();\n"
"xhr.open(\"GET\", \"/offledone\");\n"
"xhr.send();\n"
"}\n"
"// turn on led two action\n"
"function onLedTwo(){\n"
"console.log(\"turn on led two...\");\n"
"const xhr = new XMLHttpRequest();\n"
"xhr.open(\"GET\", \"/onledtwo\");\n"
"xhr.send();\n"
"}\n"
"// trun off led teo action\n"
"function offLedTwo(){\n"
"console.log(\"turn off led two...\");\n"
"const xhr = new XMLHttpRequest();\n"
"xhr.open(\"GET\", \"/offledtwo\");\n"
"xhr.send();\n"
"}\n"
"// trun on led three action\n"
"function onLedThree(){\n"
"console.log(\"turn on led three...\");\n"
"const xhr = new XMLHttpRequest();\n"
"xhr.open(\"GET\", \"/onledthree\");\n"
"xhr.send();\n"
"}\n"
"// turn off led three action\n"
"function offLedThree(){\n"
"console.log(\"turn off led three...\");\n"
"const xhr = new XMLHttpRequest();\n"
"xhr.open(\"GET\",\"/offedthree\");\n"
"xhr.send();\n"
"}\n"
"</script>\n"
"</body>\n"
"</html>\n"

// add libraries to sketch.
#include <ESP8266WiFi.h>
#include<ESP8266WebServer.h>
// setting our ip adress for local,subnet and geteway:
IPAddress local_ip(192, 168, 10, 10);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// instantiating an esp8266webserver object with the value of 80:
ESP8266WebServer server(80);

// setting our wifi name and password:
#define ssid "Led Controller"
#define passcode "123456789"
/*
    declaring pin-out on nodemcu for the ultrasonic sensor and the pump and the pump_pin status:
*/
const int d0 = 16;
const int d1 = 5;
const int d2 = 4;
const int d3 = 0;
const int d4 = 2;
const int d5 = 14;
const int d6 = 12;
const int d7 = 13;
const int d8 = 15;
const int sd2 = 9;
const 
int sd3 = 10;

const int led1 = d1;
const int led2 = d2;
const int led3 = d3;
// const int in4 = d4;


void setup() { // put your code here to run once:
  Serial.begin(115200);
  WiFi.softAP(ssid, passcode);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  // pinMode(in4, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  // digitalWrite(in4, LOW);
//  Serial.println(sendText);
  //show landing page(controller page)...
  server.on("/", onConnect);

  // action call for front motion of the motor
  server.on("/onledone", onLedOne);
  
  // action call for reverse of the motor
  server.on("/offledone", offLedOne);

  // action call for right turn of th motor
  server.on("/onledtwo", onLedTwo);

  // action call for left turn of the motor
  server.on("/offledtwo", offLedTwo);

  // action call to stop motor motion
  server.on("/onledthree", onLedThree);

  // action call to halt all movement of the motor
  server.on("/offledthree", offLedThree);
  
  // handle not found
  server.onNotFound(handle_notfound);

  // start listening to request 
  server.begin();
}

// show lading page (handle on connect)...
void onConnect() {
  server.send(200, "text/html", pageHtml);
}

// turn on led one action...
void onLedOne(){
  digitalWrite(led1, HIGH); // turn led one on...
  server.send(200, "text/plain", "led one on");
}

// turn off led one action...
void offLedOne(){
  digitalWrite(led1, LOW); // turn led one off...
  server.send(200, "text/plain", "led one off");
}

// turn on led two action...
void onLedTwo(){
  digitalWrite(led2, HIGH); // turn on led two...
  server.send(200, "text/plain", "led two on...");
}

// turn off led two action...
void offLedTwo(){
  digitalWrite(led2, LOW); // trun off led two...
  server.send(200, "text/plain", "led two off...");
}

// turn led two on action...
void onLedThree(){
  digitalWrite(led3, HIGH); // turn on led three...
  server.send(200, "text/plain", "led three on...");
}

// turn off led three action...
void offLedThree(){
  Serial.println("led three off...");
  digitalWrite(led3, LOW); // right wheel forward motion...
  server.send(200, "text/plain", "led three off...");
}


// not found page.
void handle_notfound() {
  server.send(404, "text/html", "<h1 style=\"color:red; text-align:center; \">\nweb page not available\n <br/> <a href=\"/\">go back home </a> </h1>\n");
  Serial.println("not found");
}
void loop() { // put your code here to run repeatedly:
  server.handleClient();
}
