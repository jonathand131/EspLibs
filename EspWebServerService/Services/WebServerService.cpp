#include <Arduino.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include "Common/SystemManager.h"
#include "Services/WebServerService.h"

// The server instance
static AsyncWebServer _server(WEB_SRV_PORT);

// Prototypes
void onRequest(AsyncWebServerRequest *request);
void onBody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total);
void onUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final);


const std::string WebServerServiceClass::name = "WebServerService";

WebServerServiceClass::WebServerServiceClass() {
}

void WebServerServiceClass::init() {
  SystemManager.registerService(this);

  // Catch-All Handlers
  // Any request that can not find a Handler that canHandle it
  // ends in the callbacks below.
  _server.onNotFound(onRequest);
  _server.onFileUpload(onUpload);
  _server.onRequestBody(onBody);

  // Start serving
  _server.begin();
  Serial.println("Webserver is ready.");
}

void WebServerServiceClass::run() {
  /* Nothing to do */
}

void WebServerServiceClass::prepareForOta() {
  // Disable client connections
  // ws.enable(false);

  // Close clients
  // ws.closeAll();

  // Serial.println("WebServer client disconnected.");
}

const std::string& WebServerServiceClass::getName() {
    return WebServerServiceClass::name;
}

AsyncWebServer* WebServerServiceClass::getAsyncWebServer() {
  return &_server;
}


// WebServerService instance
WebServerServiceClass WebServerService;


// Handlers
void onRequest(AsyncWebServerRequest *request) {
  // Handle Unknown Request
  String response = String();
  response += "<html><head><title>Page not found!</title></head>\n";
  response += "<body>\n";
  response += "<h1>HTTP 404</h1>";
  response += "<h2>Page not found</h2>";
  response += "<p>The requested page could not be found.</p>";
  response += "</body></html>\n";
  request->send(404, "text/html", response);
}

void onBody(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
  // Handle body
}

void onUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
  // Handle upload
}
