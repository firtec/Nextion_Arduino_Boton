
/**********************************************************************
** Descripción  : Ejemplo simple para una pantalla NEXUS NX4024K032        
**                400 x 240 pixeles
**                
**  Target       : Arduino Nano
**  ToolChain    : Arduino IDE 1.8.10 bajo Linux Debian
**  www.firtec.com.ar 
**********************************************************************/
int val =0; //variable para mandar por el puerto serial
#define led 2
bool bandera = false;  // Bandera para saber si hay que apagar o encender el LED
   
void setup() {
 Serial.begin(9600); 
  pinMode(led, OUTPUT);
}
void loop() {

byte array[16];                             // Arreglo para recibir datos desde la UART
     while (Serial.available() > 0) {       
     for (int i = 1 ; i < 16; i++) {        // Solo son necesarios en este ejemplo los datos del 1 al 7
          array[i] =  Serial.read();        // La pantalla enviará 7 bytes donde los bytes 2,3 y 4 son los que interesan
        delay(20);                            
    }
/*-----------------------------------------------------------------------------------------------
Estructura del mensaje enviado por NEXUS:
	65 00 05 01 FF FF FF
	 |  |  |  |  |__|__| > Fin de TX
	 |  |  |  Evento
	 |  |  Componente
	 | Página
Todo OK
	 
-------------------------------------------------------------------------------------------------*/
    array[16] = '\0';       
    byte error = array[1];     
    byte pagina = array[2];    	// Página desde donde llega la información desde la pantalla
    byte componente = array[3];	// Identificación del componente que ha enviado la información desde la pantalla
    byte eventopres = array[4];	// Evento del componente que se ha enviado
    byte dato1 = array[5];     	// Comando de fin de envío
    byte dato2 = array[6];     	// Comando de fin de envío
    byte dato3 = array[7];     	// Comando de fin de envío
    delay(5);
    if (pagina == 0 && componente == 5 && bandera == false ) {   // Evento de la pagina 0 y el componente 5(el unico boton de esa pagina)
      digitalWrite(led, HIGH);                    // LED encendido
      bandera = true;                             // Bandera pasa a true para saber si en proximo evento enciede o apaga
      componente = 0;                             // Componente es puesto a cero 
      delay(5);                                       
    }
    if (pagina == 0 && componente == 5 && bandera == true) {   // Nuevo evento del boton y relación con bandera.
      digitalWrite(led, LOW);                    // LED apagado
      bandera = false;                          
      delay(5);                                 
    }
  }
  
 Valor = analogRead(0); // Lee el canal 0
  val= (Valor/4)/2.55;  // Escala los valores analogicos para ajustarlos de 0 a255
 
 Serial.print("j0.val="); // Se apunta a la variable que se modifica
 Serial.print(val);       // Se envía el valor del potenciometro para modificar la variable en la pantalla
 Serial.write(0xff);
 Serial.write(0xff);
 Serial.write(0xff);
 
 Serial.print("n0.val="); // Variable de pantalla que se va a modificar
 Serial.print(val);       // Envía el dato
 Serial.write(0xff);
 Serial.write(0xff);
 Serial.write(0xff);
}
