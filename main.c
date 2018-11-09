//Algoritmo para suavização de imagem e redução da mesma utilizando uma máscara 3x3
//Instituto Federal de Ciências e Tecnologia do Ceará - Campus Fortaleza
//Implementado pelos alunos: José Mateus Sales Lima e Celso Ernani de Castro Sales Neto

#pragma config FEXTOSC = OFF    // External Oscillator mode selection bits (Oscillator not enabled)
#pragma config RSTOSC = HFINT32 // Power-up default value for COSC bits (HFINTOSC with OSCFRQ= 32 MHz and CDIV = 1:1)
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; i/o or oscillator function on OSC2)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (FSCM timer enabled)
// CONFIG2
#pragma config MCLRE = ON       // Master Clear Enable bit (MCLR pin is Master Clear function)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config LPBOREN = OFF    // Low-Power BOR enable bit (ULPBOR disabled)
#pragma config BOREN = ON       // Brown-out reset enable bits (Brown-out Reset Enabled, SBOREN bit is ignored)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (VBOR) set to 1.9V on LF, and 2.45V on F Devices)
#pragma config ZCD = OFF        // Zero-cross detect disable (Zero-cross detect circuit is disabled at POR.)
#pragma config PPS1WAY = ON     // Peripheral Pin Select one-way control (The PPSLOCK bit can be cleared and set only once in software)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable bit (Stack Overflow or Underflow will cause a reset)

// CONFIG3
#pragma config WDTCPS = WDTCPS_31// WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF       // WDT operating mode (WDT Disabled, SWDTEN is ignored)
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC      // WDT input clock selector (Software Control)

// CONFIG4
#pragma config WRT = OFF        // UserNVM self-write protection bits (Write protection off)
#pragma config SCANE = available// Scanner Enable bit (Scanner module is available for use)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low Voltage programming enabled. MCLR/Vpp pin function is MCLR.)

// CONFIG5
#pragma config CP = OFF         // UserNVM Program memory code protection bit (Program Memory code protection disabled)
#pragma config CPD = OFF        // DataNVM code protection bit (Data EEPROM code protection disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

#define _XTAL_FREQ 32000000
#define F_CPU 32000000/64//#define Baud_value(baud_rate) (((float)(F_CPU)/(float)baud_rate)-1)
#define Baud_value (((float)(F_CPU)/(float)baud_rate)-1)//calculo do taxa de transmissão serial para Uart

//Constante: Dimensão da matriz de entrada
#define dim 10

double matriz[dim][dim] = {
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,90,90,90,90,90,0,0,
0,0,0,90,0,90,90,90,0,0,
0,0,0,90,90,90,90,90,0,0,
0,0,0,90,90,90,90,90,0,0,
0,0,0,90,90,90,90,90,0,0,
0,90,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,        
};


int main(){

   int q = 0, p = 2, n = 0, k = 2;
   int i, j;
	//Variável para armazenar a soma de cada elemento da máscara 3x3
   int soma = 0;
	//Variável para armazenar a média da máscara 3x3
   int aux = 0;
	//Variáveis temporárias para garantir que a máscara percorrerá toda a matriz
   int temp = dim - 2;
   int temp2 = dim - 3;
   int temp3 = dim - 1;


    while( ((n <= temp2) && (k <= temp3)) && ((q <= temp2) && (p <= temp3)) ) {
		for(i = n; i <= k; i++) {
        		for(j = q; j <= p; j++) {
                 soma += matriz[i][j];
      		}
      }
      q++; p++; //Incrementa as colunas da máscara
      aux = soma/9; //Calcula a média da máscara
		//Reseta as variáveis que armazenam a soma e a média
      aux = 0;
      soma = 0;
		//Verifica se a máscara terminou de percorrer a matriz horizontalmente
		//Reseta as variáveis que faz o controle horizontal e incrementa o controle vertical
      if ((q == temp) && (p == dim)) {
      	p = 2; q = 0;
         n++;
         k++;
      }
    }

		while (1){};
}

