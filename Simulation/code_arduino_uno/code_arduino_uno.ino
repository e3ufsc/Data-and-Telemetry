int a_th = A0;                                //pino de leitura do acelerador 
int leds[11]={3,4,5,6,7,8,9,10,11,12,13};     //declaração dos leds da interface
int leds_arrow[2]={A3,A4};                    //declaração dos leds indicadores acelerar ou desacelerar
boolean hall_sensor = 2;                      //declaração do pino do sensor hall para medida de RPM (deve ser pino 2 para funcionar)
int RPM, rpm_old;                             //Variaveis inteiras para acelerador e rpm
float speed_km_h;                             //variavel velocidade em km/h
float th_ideal, th_atual, th_comp;            //variaveis de aceleração em %            


void setup() {
  pinMode(a_th,INPUT);                      //leitura do acelerador
  
  pinMode(leds[0],OUTPUT);                  //declara cada led como saída
  pinMode(leds[1],OUTPUT);                  //declara cada led como saída
  pinMode(leds[2],OUTPUT);                  //declara cada led como saída
  pinMode(leds[3],OUTPUT);                  //declara cada led como saída
  pinMode(leds[4],OUTPUT);                  //declara cada led como saída
  pinMode(leds[5],OUTPUT);                  //declara cada led como saída
  pinMode(leds[6],OUTPUT);                  //declara cada led como saída
  pinMode(leds[7],OUTPUT);                  //declara cada led como saída
  pinMode(leds[8],OUTPUT);                  //declara cada led como saída
  pinMode(leds[9],OUTPUT);                  //declara cada led como saída
  pinMode(leds[10],OUTPUT);                 //declara cada led como saída
  pinMode(leds_arrow[0],OUTPUT);             //declara cada led como saída
  pinMode(leds_arrow[1],OUTPUT);             //declara cada led como saída
  
  Serial.begin(9600);                       //inicia o serial

}

void loop() {
  acelerador();                             //chama função de leitura do acelerador
  rpm_calculate();                          //chama função de calculo de RPM (tambem insere delay 1segundo)
  speed_calculate();                        //chama função de calculo de velocidade
  led_interface();                          //chama função interface
  th_ideal_calculate();                     //chama função que calcula valor ideal do acelerador
  th_compare();                             //chama função que compara o valor ideal vs atual do acelerador


  //Serial.print("th_atual%:");                     //apenas usado para debug, exibe no serial %acelerador
  //Serial.println(th_atual);
  //Serial.print("th_ideal%:");                     //apenas usado para debug, exibe no serial %acelerador
  //Serial.println(th_ideal);
  Serial.print("th_comp%:");                     //apenas usado para debug, exibe no serial diferença entre %acelerador
  Serial.println(th_comp);
  Serial.print("RPM:");                     //apenas usado para debug, exibe no serial valor de RPM
  Serial.println(RPM);
  Serial.print("speed km/h:");              //apenas usado para debug, exibe no serial velocidade
  Serial.println(speed_km_h);


}

void acelerador(){
  th_atual = map(analogRead(a_th),0,1023,0,100);     //devolve percentual de aceleração
}

void rpm_calculate(){                             //função que calcula rpm usando numero de revoluções dentro de 1segundo
  rpm_old = 0;
  RPM = 0;
  attachInterrupt(0, rpm_cont, RISING);          //pino 0 de interrupção corresponde ao pino 2 da placa
  delay(500);
  detachInterrupt(0);
  RPM = rpm_old*120;
}
void rpm_cont(){                                 //função usada na função anterioir, necessária para realizar interrupção
  rpm_old++;
}

void speed_calculate(){                          //função do calculo de velocidade
  speed_km_h = 3.6*(0.99*RPM*2*(0.4064)*3.141593*0.47*1.02)/60;   //usando rpm e diametro, calcula km/h
}


void th_ideal_calculate(){
  if(speed_km_h<=26.0){
    if (RPM<330.1){
      th_ideal = 3.64 + 0.264*(RPM) + (0.0000786)*RPM*RPM; //devolve o valor ideal do acelerador em %
    }
    if(RPM>=330.1) th_ideal = 100.0;
    }
   else th_ideal = 95.2;
}

void th_compare(){
  //th_atual-th_ideal < 0 significa que precisa acelerar mais, acende leds da esquerda
  //th_atual-th_ideal > 0 significa que precisa diminuir acelerador, acende leds da direita
  th_comp = (int)((th_atual - th_ideal));         //compara e resulta em valor de diferença em %
}




void led_interface(){
  //função que varia cor e quantidade de leds de acordo com energia perdida
  arrow_led();
  switch ((int)(th_comp)) {                        
    case -5: 
      digitalWrite(leds[0], HIGH);
      digitalWrite(leds[1], LOW);
      digitalWrite(leds[2], LOW);
      digitalWrite(leds[3], LOW);
      digitalWrite(leds[4], LOW);
      digitalWrite(leds[5], LOW);
      digitalWrite(leds[6], LOW);
      digitalWrite(leds[7], LOW);
      digitalWrite(leds[8], LOW);
      digitalWrite(leds[9], LOW);
      digitalWrite(leds[10],LOW);
      break;
    case -4: 
      digitalWrite(leds[0], LOW);
      digitalWrite(leds[1], HIGH);
      digitalWrite(leds[2], LOW);
      digitalWrite(leds[3], LOW);
      digitalWrite(leds[4], LOW);
      digitalWrite(leds[5], LOW);
      digitalWrite(leds[6], LOW);
      digitalWrite(leds[7], LOW);
      digitalWrite(leds[8], LOW);
      digitalWrite(leds[9], LOW);
      digitalWrite(leds[10],LOW);
      break;
    case -3: 
      digitalWrite(leds[0], LOW);
      digitalWrite(leds[1], LOW);
      digitalWrite(leds[2], HIGH);
      digitalWrite(leds[3], LOW);
      digitalWrite(leds[4], LOW);
      digitalWrite(leds[5], LOW);
      digitalWrite(leds[6], LOW);
      digitalWrite(leds[7], LOW);
      digitalWrite(leds[8], LOW);
      digitalWrite(leds[9], LOW);
      digitalWrite(leds[10],LOW);
      break;
     case -2: 
      digitalWrite(leds[0], LOW);
      digitalWrite(leds[1], LOW);
      digitalWrite(leds[2], LOW);
      digitalWrite(leds[3], HIGH);
      digitalWrite(leds[4], LOW);
      digitalWrite(leds[5], LOW);
      digitalWrite(leds[6], LOW);
      digitalWrite(leds[7], LOW);
      digitalWrite(leds[8], LOW);
      digitalWrite(leds[9], LOW);
      digitalWrite(leds[10],LOW);
      break;
     case -1: 
      digitalWrite(leds[0], LOW);
      digitalWrite(leds[1], LOW);
      digitalWrite(leds[2], LOW);
      digitalWrite(leds[3], LOW);
      digitalWrite(leds[4], HIGH);
      digitalWrite(leds[5], LOW);
      digitalWrite(leds[6], LOW);
      digitalWrite(leds[7], LOW);
      digitalWrite(leds[8], LOW);
      digitalWrite(leds[9], LOW);
      digitalWrite(leds[10],LOW);
      break;
     case 0: 
      digitalWrite(leds[0], LOW);
      digitalWrite(leds[1], LOW);
      digitalWrite(leds[2], LOW);
      digitalWrite(leds[3], LOW);
      digitalWrite(leds[4], LOW);
      digitalWrite(leds[5], HIGH);
      digitalWrite(leds[6], LOW);
      digitalWrite(leds[7], LOW);
      digitalWrite(leds[8], LOW);
      digitalWrite(leds[9], LOW);
      digitalWrite(leds[10],LOW);
      break;
     case 1: 
      digitalWrite(leds[0], LOW);
      digitalWrite(leds[1], LOW);
      digitalWrite(leds[2], LOW);
      digitalWrite(leds[3], LOW);
      digitalWrite(leds[4], LOW);
      digitalWrite(leds[5], LOW);
      digitalWrite(leds[6], HIGH);
      digitalWrite(leds[7], LOW);
      digitalWrite(leds[8], LOW);
      digitalWrite(leds[9], LOW);
      digitalWrite(leds[10],LOW);
      break;
     case 2: 
      digitalWrite(leds[0], LOW);
      digitalWrite(leds[1], LOW);
      digitalWrite(leds[2], LOW);
      digitalWrite(leds[3], LOW);
      digitalWrite(leds[4], LOW);
      digitalWrite(leds[5], LOW);
      digitalWrite(leds[6], LOW);
      digitalWrite(leds[7], HIGH);
      digitalWrite(leds[8], LOW);
      digitalWrite(leds[9], LOW);
      digitalWrite(leds[10],LOW);
      break;
     case 3: 
      digitalWrite(leds[0], LOW);
      digitalWrite(leds[1], LOW);
      digitalWrite(leds[2], LOW);
      digitalWrite(leds[3], LOW);
      digitalWrite(leds[4], LOW);
      digitalWrite(leds[5], LOW);
      digitalWrite(leds[6], LOW);
      digitalWrite(leds[7], LOW);
      digitalWrite(leds[8], HIGH);
      digitalWrite(leds[9], LOW);
      digitalWrite(leds[10],LOW);
      break;
     case 4: 
      digitalWrite(leds[0], LOW);
      digitalWrite(leds[1], LOW);
      digitalWrite(leds[2], LOW);
      digitalWrite(leds[3], LOW);
      digitalWrite(leds[4], LOW);
      digitalWrite(leds[5], LOW);
      digitalWrite(leds[6], LOW);
      digitalWrite(leds[7], LOW);
      digitalWrite(leds[8], LOW);
      digitalWrite(leds[9], HIGH);
      digitalWrite(leds[10],LOW);
      break;
     case 5: 
      digitalWrite(leds[0], LOW);
      digitalWrite(leds[1], LOW);
      digitalWrite(leds[2], LOW);
      digitalWrite(leds[3], LOW);
      digitalWrite(leds[4], LOW);
      digitalWrite(leds[5], LOW);
      digitalWrite(leds[6], LOW);
      digitalWrite(leds[7], LOW);
      digitalWrite(leds[8], LOW);
      digitalWrite(leds[9], LOW);
      digitalWrite(leds[10],HIGH);
      break;
     default: 
      digitalWrite(leds[0], LOW);
      digitalWrite(leds[1], LOW);
      digitalWrite(leds[2], LOW);
      digitalWrite(leds[3], LOW);
      digitalWrite(leds[4], LOW);
      digitalWrite(leds[5], LOW);
      digitalWrite(leds[6], LOW);
      digitalWrite(leds[7], LOW);
      digitalWrite(leds[8], LOW);
      digitalWrite(leds[9], LOW);
      digitalWrite(leds[10],LOW);
      break;
      
  }// fim do switch case
  if (th_comp>5) digitalWrite(leds[10],HIGH);
  if (th_comp<-5) digitalWrite(leds[0],HIGH);
  
} //fim da função led_interface

void arrow_led(){
  if ((int)(th_comp)<0){ //indica acelerar
    digitalWrite(leds_arrow[0],HIGH);
    digitalWrite(leds_arrow[1],LOW);
  }
  if ((int)(th_comp)>0){ //indica desacelerar
    digitalWrite(leds_arrow[0],LOW);
    digitalWrite(leds_arrow[1],HIGH);
    
  }
  if (((int)(th_comp))==0){ //indica ideal
    digitalWrite(leds_arrow[0],LOW);
    digitalWrite(leds_arrow[1],LOW);    
    
  }
  
}
