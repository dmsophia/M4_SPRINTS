//Adição das bibliotecas que serão usadas para conectar a página web e o ESP
#define led_vermelho 8
#define led_azul 15
#include <WiFi.h>
#include <WebServer.h>
const char* ssid = "Inteli-COLLEGE";
const char* password = "QazWsx@123";

WebServer server(80);
//Funções que farão o led ligar caso o vencedor for X(led vermelho) ou O(led azul)
void handle_x(){
  digitalWrite(led_vermelho, HIGH);
  server.send(200, "foi");
  delay(1000);
  digitalWrite(led_vermelho, LOW);
}

void handle_o(){
  digitalWrite(led_azul, HIGH);
  server.send(200, "foi");
    delay(1000);
  digitalWrite(led_azul, LOW);
}


/*Conexão do ESP ao mesmo WiFi do computador, em que o endereço IP será usado para acender os leds 
e definição da rota que fará ligar de acordo com o ganhador*/
void setup() {
  Serial.begin(115200);
  pinMode(led_vermelho, OUTPUT);
  pinMode(led_azul, OUTPUT);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/x", handle_x);
  server.on("/o", handle_o);
  server.begin();

}


void loop() {
server.handleClient();


}
