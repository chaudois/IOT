#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "chaudois_phone"
#define STAPSK  "12345678"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;

ESP8266WebServer server(80);

void handleRoot() {
  
  char temp[2500];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  String upTime = "";
         upTime += hr;
         upTime += " hrs ";
         upTime += (min % 60);
         upTime += " min ";
         upTime += (sec % 60);
         upTime += " sec";

  String start =        "<html>";
         start +=         "<head>";
         start +=           "<meta http-equiv='refresh' content='10'/>" ;
         start +=           "<title>Memory LightCube Score</title>" ;
         start +=           "<link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\">" ;
         start +=           "<script src=\"https://code.jquery.com/jquery-3.3.1.min.js\"></script>" ;
         start +=           "<script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js\"></script>" ;
         start +=           "<script src=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js\"></script>" ;
         start +=         "</head>" ;
         start +=         "<body style=\"background: url('http://getwallpapers.com/wallpaper/full/9/6/4/21509.jpg') no-repeat center center fixed\">" ;
         start +=           "<div class=\"container-fluid h-100\">" ;
         start +=              "<div class=\"row align-items-center h-100\">" ;
         start +=                "<div class=\"col-6 mx-auto\">" ;
         start +=                 "<div class=\"card text-white bg-dark text-center\">" ;
         start +=                   "<div class=\"card-header\"><strong>Memory LightCube Score</strong></div>" ;
         start +=                   "<div class=\"card-body\">";

  String stringScoreTable = makeScoreTable();

  String end =                   "</div>"; 
         end +=                  "<div class=\"card-footer text-muted\">LightCube Uptime : ";
         end +=                     upTime;
         end +=                  "</div>" ;
         end +=                 "</div>" ;
         end +=               "</div>" ;
         end +=             "</div>" ;
         end +=           "</div>" ;
         end +=         "</body>" ;
         end +=       "</html>";

  String stringHtmlPage = start + stringScoreTable + end;

  const char* charHtmlPage = stringHtmlPage.c_str();
    
  snprintf(temp, 2500, charHtmlPage);
  
  server.send(200, "text/html", temp);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}

String makeScoreTable() {
  
  int bestScore[7];

  bestScore[0] = 117;
  bestScore[1] = 217;
  bestScore[2] = 317;
  bestScore[3] = 417;
  bestScore[4] = 517;
  bestScore[5] = 617;
  bestScore[6] = 717;

  String out = "";
  
  char temp[2000];

  out += "<table class=\"table table-striped table-hover table-dark\">";
    out += "<thead>";
      out += "<tr>";
        out += "<th scope=\"col\">#</th>";
        out += "<th scope=\"col\">Time</th>";
      out += "</tr>";
    out += "</thead>";
    out += "<tbody>";

      for (int i = 0; i < 7; i++) {
        
        out += "<tr>";
          out += "<th scope=\"row\">";
          out += (i+1);
          out += "</th><td>";
          out += bestScore[i];
          out += " s</td>";
        out += "</tr>";
      }
  
    out += "</tbody>";
  out += "</table>";

  return out;
}
