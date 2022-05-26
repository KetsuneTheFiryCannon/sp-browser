#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

int val = 0;                         // По умолчанию диод не горит
const char *ssid = "Yakunchev";      // Название сети WiFi
const char *password = "Archie2358"; // Пароль для подключения
ESP8266WebServer server(80);         // Создаем веб сервер на 80 порту

// Метод формирует стартовую страницу 192.168.4.1
// Выводит в браузер текущее состояние диода и две кнопки
void handleRoot()
{ // 8 7 6 5
  String s = (!val) ? "<h1>LED On</h1>" : "<h1>LED Off</h1>";
  String a = (!digitalRead(D8)) ? "<h1>D8 On</h1>" : "<h1>D8 Off</h1>";
  String aa = (!digitalRead(D6)) ? "<h1>D6 On</h1>" : "<h1>D6 Off</h1>";
  String aaa = (!digitalRead(D5)) ? "<h1>D5 On</h1>" : "<h1>D5 Off</h1>";
  s += a;
  s += aa;
  s += aaa;
  s += "<!DOCTYPE html> <html> <head>  <meta charset='utf-8'>  <title>Кнопка</title>  <style>   .btn {  display: inline-block; /* Строчно-блочный элемент */    background: #8C959D; /* Серый цвет фона */    color: #fff; /* Белый цвет текста */    padding: 1rem 1.5rem; /* Поля вокруг текста */    text-decoration: none; /* Убираем подчёркивание */    border-radius: 3px; /* Скругляем уголки */   }  </style>";
  s += "</head> <body>   <a href='/led/on8' class='btn'>ON</a> </body></html>";
  s += "</head> <body>   <a href='/led/off8' class='btn'>OFF</a> </body></html>";
   s += "</head> <body>   <a href='/led/on6' class='btn'>ON</a> </body></html>";
  s += "</head> <body>   <a href='/led/off6' class='btn'>OFF</a> </body></html>";
   s += "</head> <body>   <a href='/led/on5' class='btn'>ON</a> </body></html>";
  s += "</head> <body>   <a href='/led/off5' class='btn'>OFF</a> </body></html>";
  // s+= "<script> function isEmail() {   }  </script>";
  // s += "<h2>LED On ";
  // s += "<input type = 'button' value = 'Turn on/off' onClick='isEmail'>";
  // s += "LED Off</h2>";
  server.send(200, "text/html", s);
}

void ledOnD8()
{
  digitalWrite(D8, LOW);
  server.sendHeader("Location", String("/"), true);
  server.send(302, "text/plain", "");
}

void ledOnD6()
{
  digitalWrite(D6, LOW);
  server.sendHeader("Location", String("/"), true);
  server.send(302, "text/plain", "");
}

void ledOnD5()
{
  digitalWrite(D5, LOW);
  server.sendHeader("Location", String("/"), true);
  server.send(302, "text/plain", "");
}

void ledOn()
{
  val = 1;
  digitalWrite(BUILTIN_LED, !val);
  server.sendHeader("Location", String("/"), true);
  server.send(302, "text/plain", "");
}

void ledOff8()
{
  digitalWrite(D8, HIGH);
  server.sendHeader("Location", String("/"), true);
  server.send(302, "text/plain", "");
}

void ledOff6()
{
  digitalWrite(D6, HIGH);
  server.sendHeader("Location", String("/"), true);
  server.send(302, "text/plain", "");
}

void ledOff5()
{
  digitalWrite(D5, HIGH);
  server.sendHeader("Location", String("/"), true);
  server.send(302, "text/plain", "");
}

void ledOff()
{
  val = 0; // Выключаем диод
  digitalWrite(BUILTIN_LED, !val);
  server.sendHeader("Location", String("/"), true);
  server.send(302, "text/plain", "");
}
// Функция настройки. Выполняется один раз при запуске
void setup()
{
  delay(1000);                 // Ждём секунду
  WiFi.softAP(ssid, password); // Создаём точку WiFi
  // Указываем по каким роутам какие методы запускать
  server.on("/", handleRoot);
  server.on("/led/on8", ledOnD8);
  server.on("/led/on6", ledOnD6);
  server.on("/led/on5", ledOnD5);
  server.on("/led/off8", ledOff8);
  server.on("/led/off6", ledOff6);
  server.on("/led/off5", ledOff5);
  server.begin();
  // Диод по умолчанию выключен
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(D8, OUTPUT);
  // pinMode(D7, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D5, OUTPUT);
  digitalWrite(BUILTIN_LED, val);
}

// Основной цикл программы
void loop()
{
  // Ждём подключения
  server.handleClient();
}
