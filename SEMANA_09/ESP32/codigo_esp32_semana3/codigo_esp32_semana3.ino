#define led_azul 21
#define led_vermelho 47
#define led_verde 40
#define led_branco 41
#define ldr 14
#define buzzer 13
#define botao1 17
#define botao2 18

int binario[4];
int led_armazenamento[100][4];
int contagem_armazenamento = 0;
int led[4] = {led_branco, led_verde, led_vermelho, led_azul};
void setup() {
  // put your setup code here, to run once:
  pinMode(led_azul, OUTPUT);
  pinMode(led_vermelho, OUTPUT);
  pinMode(led_verde, OUTPUT);
  pinMode(led_branco, OUTPUT);
  pinMode(ldr, INPUT);
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
}

void converte_binario(int num) {
  for (int i = 0; i < 4; i++) {
    Serial.print(num);
    binario[i] = num % 2;
    led_armazenamento[contagem_armazenamento][i] = num % 2;
    num = num / 2;
    // Serial.print(binario[i]);
  }
  contagem_armazenamento += 1;

  Serial.print("\n");

}

void liga_led(int liga, int led) {
  if (liga == 1) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }
}

void toca_buzzer(int *vetor) {
  int toca = 0;
  for (int i = 0; i < 4; i++) {
    toca += vetor[i] * i * 600;
  }
  tone(buzzer, toca, 500);
}


void loop() {
  // put your main code here, to run repeatedly:


  if (digitalRead(botao1) == LOW) {
    
    int n = analogRead(ldr);
    Serial.println(n);
    int new_value = n / 273;
    Serial.println(new_value);
    Serial.println("clicado");
    converte_binario(new_value);
    liga_led(binario[0], led_branco);
    liga_led(binario[1], led_verde);
    liga_led(binario[2], led_vermelho);
    liga_led(binario[3], led_azul);
    toca_buzzer(binario);
    delay(500);
    liga_led(0, led_branco);
    liga_led(0, led_verde);
    liga_led(0, led_vermelho);
    liga_led(0, led_azul);
  while (digitalRead(botao1) == LOW) {}
  } 
  
  if (digitalRead(botao2) == LOW) {
   
    for (int i = 0; i < contagem_armazenamento; i++) {
      liga_led(led_armazenamento[i][0], led_branco);
      liga_led(led_armazenamento[i][1], led_verde);
      liga_led(led_armazenamento[i][2], led_vermelho);
      liga_led(led_armazenamento[i][3], led_azul);
      toca_buzzer(led_armazenamento[i]);
      delay(500);
      liga_led(0, led_branco);
      liga_led(0, led_verde);
      liga_led(0, led_vermelho);
      liga_led(0, led_azul);
      delay(500);
    }
    contagem_armazenamento = 0;

     while (digitalRead(botao2) == LOW) {}
  }
  delay(10);
  // this speeds up the simulation
}


