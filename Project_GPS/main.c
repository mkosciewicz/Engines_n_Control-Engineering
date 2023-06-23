#include "io430.h"
#include "string.h"
#include "stdint.h"
#include "stdio.h"
#include "lcd.h"

#define MAX_BUFFER_SIZE 256
#define DB4 0x10
#define DB5 0x20
#define E 0x08
#define DDRAMSet 0x80

volatile unsigned int i;
//char test[MAX_BUFFER_SIZE]={288,31,03,00,232,,08,63,214,33*70
//$GPGSV,3,2,12,10,50,061,19,@4,16,319,27,21,60,288,32,22,28,145,26*74
//$GPGSV,3,3,12,23,14,057,13,24,07,038,08,27,39,168,25,32,42,122,37*79
//$GPGLL,5213.30026,N,02100.36327,E,130515.00,A,A*68
//$OPRMC,130516.00184,33,02,48.515.00,A,5213.30026,N,02100.36327,E,0.516,,120623,,,A*77
//$GPVTG.,T,,M,0.516,N,0.956,K,A*2B
//$GPGGA,1305q5.00,5213.30026,N,02100.36327,E,1,09,1.09,120.9,M,34.3,M,,*52
//$GPGSA,A,3,27,21,23,01,02,32,10,08,14,,,,2.13,1.09,1.84*0E
//$GPGSV,3,1,12,011
//$GPRMC,13};
volatile char rxbuf1[MAX_BUFFER_SIZE];
volatile char xtract[MAX_BUFFER_SIZE];

volatile int rxbuf1_length;
volatile int xtract_length;

float latitude_list[MAX_BUFFER_SIZE];
float longitude_list[MAX_BUFFER_SIZE];
char latitude[15], longitude[15];

int main(void) {
    WDTCTL = WDTPW + WDTHOLD; // Stop WDT P2DIR = 0xFF;
    P3SEL |= 0xC0; // P3.6,7 = USART1
    P3DIR |= 0x01; // P3.0 wyjscie do MUXa
    P3OUT_bit.P0 = 0x00;
    P4DIR |= 0x80;
    P4OUT &= ~0x80; // P4.0 wyjscie do MUXa
    //BCSCTL1 &= ~XT2OFF; // uruchomienie
    //XTAL = 8MHz;
//    IFG1 &= ~OFIFG;
//    for (i = 0xFF; i > 0; i--);
//        while ((IFG1 & OFIFG));
//    BCSCTL2 |= SELM_2 + SELS; // MCLK= SMCLK=XTAL
////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ME2 |= UTXE1 + URXE1; // wlaczenie TXD/RXD
    UCTL1 |= CHAR; // 8-bit
//    
    UTCTL1 |= SSEL1; // UCLK = SMCLK
    UBR01 = 0x50;
    UBR11 = 0x00;
    UCTL1 &= ~SWRST;
    IE2 |= URXIE1; // przerwania od uart
    __bis_SR_register(GIE); // ustawienie GIE
  //  printf ("Hello");
    //TXBUF1 = 0x55;
    lcd_init();
    lcd_go_line(1);
    lcd_writeln("Ltd");
    lcd_go_line(2);
    lcd_writeln("Lng");
    while(1){
      
//        while (!(IFG2 & UTXIFG1)); // wait until buffer is empty
//       // TXBUF1 = P4IN & 0x0F;
    //TXBUF1 = 0x55;
      
      
      
    }
}

//void send4bit(uint8_t data) {
//    uint8_t temp = data;
//    P2OUT |= E;
//    uint8_t portState = P2OUT;
//    portState &= 0xC3;
//    temp = (temp >> 2) & 0x0F;
//    portState |= temp;
//    P2OUT = portState;
//    P2OUT &= ~E;
//    delay40us();
//
//    temp = data;
//    P2OUT |= E;
//    portState = P2OUT;
//    portState &= 0xC3;
//    temp = (temp << 2) & 0x0F;
//    portState |= temp;
//    P2OUT = portState;
//    P2OUT &= ~E;
//    delay40us();
//}
//
//void delay40ms() {
//    uint16_t R15 = 10000;
//    while (R15 != 0) {
//        R15--;
//    }
//}
//
//void delay40us() {
//    uint8_t R15 = 5;
//    while (R15 != 0) {
//        R15--;
//    }
//}



void transferData() {
    for(int i = 0; i < MAX_BUFFER_SIZE; i++) {
        xtract[i] = rxbuf1[i];
    }
}

void parseGGA() {
    // Find the GGA sentence in the buffer
    char* ggaStart = strstr((const char*)xtract, "$GPGGA");

    if (ggaStart != NULL) {
        char term[MAX_BUFFER_SIZE];
        
//        float latitude, longitude, altitude;
        char NS[1], EW[1];


        sscanf(ggaStart, "$GPGGA,%9[^,],%14[^,],%1[^,],%14[^,],%1[^,]", &term, &latitude, &NS, &longitude, &EW);
//        sscanf(ggaStart, "$GPGGA,%*[^,],%f,%c,%f,%c,%*d,%*d,%*f,%f", &latitude, &NS, &longitude, &EW, &altitude);


        //printf("Latitude: %s\n", latitude);
        //printf("Longitude: %s\n", longitude);
        lcd_go(1,4);
        lcd_write(latitude);
        lcd_go(1,15);
        lcd_write(NS);
        lcd_go(2,4);
        lcd_write(longitude);
        lcd_go(2,15);
        lcd_write(EW);
//        printf("Altitude: %f\n", altitude);
    }
}

void processReceivedData() {
    // Null-terminate the received data for string functions
    rxbuf1[rxbuf1_length] = '\0';
  
    // Parse the GPS data
    parseGGA();
}


#pragma vector=USART1RX_VECTOR
__interrupt void usart1_rx (void)
{
    char data = RXBUF1; // get received data
    static int t=0;
    rxbuf1[t]=data;
    t++;
    if(t>=256) t=0;
    //lista_danych(&data); // add received data to buffer
    rxbuf1_length++; // increment length
   // printf("%d \n", rxbuf1_length);
    //printf("%c ", data);
    while (!(IFG2 & UTXIFG1)); // wait until buffer is empty
    TXBUF1 = 0x55;
    if(rxbuf1_length == MAX_BUFFER_SIZE - 1) { // if buffer is full, process data
        processReceivedData();
        transferData(); // Copy data to new_array
        rxbuf1_length = 0; // reset buffer length
    }
}