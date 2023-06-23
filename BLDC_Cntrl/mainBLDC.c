#include "DSP28x_Project.h"
#include "funkcje.h"
#include "stale.h"
#include "math.h"
#include "modulator.h"
#include "modulator2.h"
#include "dq_abc.h"
#include "abc_dq.h"
#include "filtr.h"
#include "regulator_PI.h"

// Constants
#define DWIE_TRZECIE_PI (M_PI * (2.0 / 3.0))
#define DWA_PI_PRZEZ_DWIESCIE (M_PI * 0.01)
#define AMPLITUDE_SINUS 0.7

// Global variables
struct MODULATOR_PWM_STRUCT modulator;
struct Modulacja modulator2;
struct DQ_ABC_STRUCT DQ_ABC;
struct ABC_DQ_STRUCT ABC_DQ;
struct Dyskretyzacja Tustin;
struct PI_STRUCT PI_d;
struct PI_STRUCT PI_q;
struct PI_STRUCT PI_omega;

unsigned long long int AdcIntCounter = 0;
int praca = 0;  // 0 - STOP NAPED; 1 - ZEZWOLENIE NA PRACE

// Function prototypes
__interrupt void adc_isr(void);

void main(void) {
    // Step 1. Initialize System Control
    InitSysCtrl();

    // Step 2. Initialize GPIO
    InitPWMGpio();
    EPwm_Control123(0);
    InitEncGpio();

    // Step 3. Clear all interrupts and initialize PIE vector table
    DINT;  // Disable CPU interrupts

    InitPieCtrl();  // Initialize the PIE control registers to their default state
    IER = 0x0000;   // Disable CPU interrupts and clear all CPU interrupt flags
    IFR = 0x0000;

    // Initialize the PIE vector table with pointers to the shell Interrupt Service Routines (ISR)
    InitPieVectTable();

    // Interrupts used in this example are re-mapped to ISR functions
    EALLOW;  // Needed to write to EALLOW protected registers
    PieVectTable.ADCINT1 = &adc_isr;
    EDIS;    // Disable write to EALLOW protected registers

    // Step 4. Initialize all the Device Peripherals
    InitAdc();  // Initialize ADC
    AdcOffsetSelfCal();

    // Step 5. User-specific code, enable interrupts
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;  // Enable INT 1.1 in the PIE
    IER |= M_INT1;                      // Enable CPU Interrupt 1
    EINT;                               // Enable Global interrupt INTM
    ERTM;                               // Enable Global realtime interrupt DBGM

    InitADCConv();
    InitPWM();

    // Initialize the PI structures
    IntegratorInit(&PI_d, 35, 1e-4, 0.135, 35, -35, 1.0 / 35);
    IntegratorInit(&PI_q, 35, 1e-4, 0.135, 35, -35, 1.0 / 35);
    IntegratorInit(&PI_omega, 0.4, 1e-4, 100, 2, -2, 1.0 / 0.4);

    // Main loop, wait for ADC interrupt
    while (1) {
        __asm(" NOP");
    }
}

__interrupt void adc_isr(void) {
    // Process the ADC interrupt
    // ... [rest of the interrupt code]
}
