bool isAuthorized(AsyncWebServerRequest *  request) {
  if (request->arg("api_key") != secretKey) {
    request->send(401, "text/plain", "Unauthorized");
    return false;
  }
  return true;
}

void startListening() {
  wifiConnect();

  server.on("/sensors", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (isAuthorized(request)) {
      String response = "{\"sensors\":[";
      response += "{\"name\":\"temperature\",\"value\":" + String(analogRead(TEMP)) + ",\"celsius_value\":" + String(getTemperature()) + "},";
      response += "{\"name\":\"light\",\"value\":" + String(getLDR()) + "}";
      response += "]}";

      request->send(200, "text/plain", response);
    }
  });

  server.on("/led", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (isAuthorized(request)) {
      String response = "{\"status\":\"" + String(isLedOn() == true ? "on" : "off")  + "\"}";

      request->send(200, "text/plain", response);
    }
  });

  server.on("/led", HTTP_POST, [](AsyncWebServerRequest * request) {
    if (isAuthorized(request)) {
      if (request->hasParam("state") == true) {
        String state = request->getParam("state")->value();
        if (state == "on") {
          isOn = true;
          request->send(200, "text/plain", "LED on");
        } else if (state == "off") {
          turnLedOff();
          isOn = false;
          request->send(200, "text/plain", "LED off");
        } else {
          request->send(400, "text/plain", "Invalid state");
        }
      } else {
        request->send(400, "text/plain", "Missing state parameter");
      }
    }
  });

  server.on("/threshold", HTTP_POST, [](AsyncWebServerRequest * request) {
    if (isAuthorized(request) == true) {
      if (request->hasParam("value") == true) {
        String stringValue = request->getParam("value")->value();
        int value = atoi(stringValue.c_str());
        if (value != 0 || stringValue == "0") {
          seuil = value;
          request->send(200, "text/plain", "Threshold modified");
        } else {
          request->send(400, "text/plain", "Invalid value");
        }
      } else {
        request->send(400, "text/plain", "Missing value parameter");
      }
    }
  });







  /*  // Route for GET request to root URL
    server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
      request->send(200, "text/plain", "Hello from ESP32!");
    });


    // Route for GET request to /sensor
    server.on("/sensor", HTTP_GET, [](AsyncWebServerRequest * request) {
      Serial.print("GET SENSOR WORKED");
      float sensorValue = getTemperature();
      String response = "Sensor value: " + String(sensorValue);
      request->send(200, "text/plain", response);
    });
    server.on("/sensorauth", HTTP_GET, [](AsyncWebServerRequest * request) {
      // Récupération de la clé de sécurité
      String api_key = request->arg("api_key");
      // vérification de la clé de sécurité
      if (api_key == secretKey) {
        float sensorValue = getTemperature();
        String response = "Sensor value: " + String(sensorValue);
        request->send(200, "text/plain", response);
      }
      else {
        request->send(401, "text/plain", "Unauthorized");
      }
    });
  */

  // Start server
  server.begin();
  Serial.println("Server started");
}
