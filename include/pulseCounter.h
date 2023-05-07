#include <esp32_pcnt.h>

/*
ESP32 PulseCounter Hardware Interrupt
*/

//bind pulse counter input to pwm output
const int input_pin0 = CON_PUL_1;// GPIO pin for counter signal input
const int input_pin1 = CON_PUL_2; 
const int input_pin2 = CON_PUL_3;
const int input_pin3 = CON_PUL_4; 

int16_t threshold_0 = 1000;
int16_t threshold_1 = 2000;
int16_t threshold_2 = 1000;
int16_t threshold_3 = 2000;

int16_t high_limit = 3000;

volatile bool pc0_int_flag = false; // interrupt flag
volatile bool pc1_int_flag = false; // interrupt flag
volatile bool pc2_int_flag = false; // interrupt flag
volatile bool pc3_int_flag = false; // interrupt flag

volatile uint8_t pc0_event;
volatile uint8_t pc1_event;
volatile uint8_t pc2_event;
volatile uint8_t pc3_event;

//create counter object
PulseCounter pc0,pc1,pc2,pc3;

//mutex for hardware pulse counters
portMUX_TYPE pcntMux0 = portMUX_INITIALIZER_UNLOCKED;
portMUX_TYPE pcntMux1 = portMUX_INITIALIZER_UNLOCKED;
portMUX_TYPE pcntMux2 = portMUX_INITIALIZER_UNLOCKED;
portMUX_TYPE pcntMux3 = portMUX_INITIALIZER_UNLOCKED;

bool pcntDone[] = { false, false, false, false };

//pulse counter ISR only evt_thres0 enabled
void IRAM_ATTR pc0_isr(uint8_t event) {
    // stop this pwm and counter if event == evt_thres0
    stopPWM(0);
    pc0.pause();
    pc0.clear();
  // Prevent context switching during the interrupt service routine with an ISR spinlock
  portENTER_CRITICAL_ISR(&pcntMux0); 
    // set interrupt flag
    pc0_int_flag = true;
    // get events
    pc0_event = event;

    pcntDone[0] = true;

  portEXIT_CRITICAL_ISR(&pcntMux0);

  
}
//pulse counter ISR
void IRAM_ATTR pc1_isr(uint8_t event) {
    // stop this pwm and counter if event == evt_thres0
    stopPWM(1);
    pc1.pause();
    pc1.clear();
  // Prevent context switching during the interrupt service routine with an ISR spinlock
  portENTER_CRITICAL_ISR(&pcntMux1);
    // set interrupt flag
    pc1_int_flag = true;
    // get events
    pc1_event = event; 
    
    pcntDone[1] = true;
    
  portEXIT_CRITICAL_ISR(&pcntMux1);

}
void IRAM_ATTR pc2_isr(uint8_t event) {
    // stop this pwm and counter
    stopPWM(2);
    pc2.pause();
    pc2.clear();
  // Prevent context switching during the interrupt service routine with an ISR spinlock
  portENTER_CRITICAL_ISR(&pcntMux2);
    // set interrupt flag
    pc2_int_flag = true;
    // get events
    pc2_event = event; 

    pcntDone[2] = true;
    
  portEXIT_CRITICAL_ISR(&pcntMux2);
}
void IRAM_ATTR pc3_isr(uint8_t event) {
    // stop this pwm and counter
    stopPWM(3);
    pc3.pause();
    pc3.clear();
  // Prevent context switching during the interrupt service routine with an ISR spinlock
  portENTER_CRITICAL_ISR(&pcntMux3);
    // set interrupt flag
    pc3_int_flag = true;
    // get events
    pc3_event = event;

    pcntDone[3] = true; 
    
  portEXIT_CRITICAL_ISR(&pcntMux3);
}
void clearPC_0(){
  pc0.pause();
  pc0.clear();
}
//clear and restart the counter
void restartPC_0(){  
  clearPC_0();
  pc0.resume();
}
/***/
void clearPC_1(){
  pc1.pause();
  pc1.clear();
}
//clear and restart the counter
void restartPC_1(){  
  clearPC_1();
  pc1.resume();
}
/***/
void clearPC_2(){
  pc2.pause();
  pc2.clear();
}
//clear and restart the counter
void restartPC_2(){  
  clearPC_2();
  pc2.resume();
}
/***/
void clearPC_3(){
  pc3.pause();
  pc3.clear();
}
//clear and restart the counter
void restartPC_3(){  
  clearPC_3();
  pc3.resume();
}

void initPCNT(bool val){
  pcntDone[0] = val;
  pcntDone[1] = val;
  pcntDone[2] = val;
  pcntDone[3] = val;
}
xQueueHandle pcnt_evt_queue; 
/* A sample structure to pass events from the PCNT
 * interrupt handler to the main program.
 */
typedef struct {
    int unit;  // the PCNT unit that originated an interrupt
    uint32_t status; // information on the event type that caused the interrupt
    unsigned long timeStamp; // The time the event occured
} pcnt_evt_t;

void setupPulseCounter() {

  //Serial.begin(115200,SERIAL_8N1);

  // setup hardware pulse counter
  pcnt_evt_queue = xQueueCreate(10, sizeof(pcnt_evt_t));

  // initialise counter unit 0, channel 0 with signal input GPIO pin and control signal input pin (0 = no control signal input)
  pc0.initialise(input_pin0,PCNT_PIN_NOT_USED);
  pc1.initialise(input_pin1,PCNT_PIN_NOT_USED);
  pc2.initialise(input_pin2,PCNT_PIN_NOT_USED);
  pc3.initialise(input_pin3,PCNT_PIN_NOT_USED);
  // count up on negative edges, don't count on positive edges 
  pc0.set_mode(PCNT_COUNT_DIS,PCNT_COUNT_INC,PCNT_MODE_KEEP,PCNT_MODE_KEEP);
  pc1.set_mode(PCNT_COUNT_DIS,PCNT_COUNT_INC,PCNT_MODE_KEEP,PCNT_MODE_KEEP);
  pc2.set_mode(PCNT_COUNT_DIS,PCNT_COUNT_INC,PCNT_MODE_KEEP,PCNT_MODE_KEEP);
  pc3.set_mode(PCNT_COUNT_DIS,PCNT_COUNT_INC,PCNT_MODE_KEEP,PCNT_MODE_KEEP);
  // set glich filter to ignore pulses less than 100 x 2.5ns
  pc0.set_filter_value(100);
  pc1.set_filter_value(100); 
  pc2.set_filter_value(100);
  pc3.set_filter_value(100); 
  // set and enable threshold 0 and 1 watch points - these will trigger an interrupt.
  // the event can be disabled and enabled using pc0.event_disable(PCNT_EVT_THRES_0) or pc0.event_enable(PCNT_EVT_THRES_0)
  // thereshold 0 & 1 events do not stop the counter
  pc0.set_event_value(PCNT_EVT_THRES_0,threshold_0);
  pc1.set_event_value(PCNT_EVT_THRES_0,threshold_0);
  pc2.set_event_value(PCNT_EVT_THRES_0,threshold_0);
  pc3.set_event_value(PCNT_EVT_THRES_0,threshold_0);

  /*
  pc0.set_event_value(PCNT_EVT_THRES_1,threshold_1);
  pc1.set_event_value(PCNT_EVT_THRES_1,threshold_1);
  pc2.set_event_value(PCNT_EVT_THRES_1,threshold_1);
  pc3.set_event_value(PCNT_EVT_THRES_1,threshold_1);
  */
  pc0.event_disable(PCNT_EVT_THRES_1);
  pc1.event_disable(PCNT_EVT_THRES_1);
  pc2.event_disable(PCNT_EVT_THRES_1);
  pc3.event_disable(PCNT_EVT_THRES_1);
  
  /*
  pc0.set_event_value(PCNT_EVT_H_LIM,high_limit);
  pc1.set_event_value(PCNT_EVT_H_LIM,high_limit);
  pc2.set_event_value(PCNT_EVT_H_LIM,high_limit);
  pc3.set_event_value(PCNT_EVT_H_LIM,high_limit);
  */
  pc0.event_disable(PCNT_EVT_H_LIM);
  pc1.event_disable(PCNT_EVT_H_LIM);
  pc2.event_disable(PCNT_EVT_H_LIM);
  pc3.event_disable(PCNT_EVT_H_LIM);

  // register interrupt service routine for all counter units, and pass an optional argument (NULL in this case)
  // pc0.isr_register(pcnt_intr_handler, NULL);
  pc0.attach_interrupt(pc0_isr);
  pc0.interrupt_enable(); //
  pc1.attach_interrupt(pc1_isr);
  pc1.interrupt_enable(); //
  pc2.attach_interrupt(pc0_isr);
  pc3.interrupt_enable(); //
  pc3.attach_interrupt(pc1_isr);
  pc3.interrupt_enable(); //

  // clear and restart the counter
  clearPC_0();

  clearPC_1();

  clearPC_2();

  clearPC_3();

  
}

void loopPulseCounter() {
  
  if (pc0_int_flag) {
    pc0_int_flag = false;
    Serial.print("pc0 : ");
    switch (pc0_event)
    {
      case evt_thres0:
        Serial.println("Threshold 0");
        break;
      case evt_thres1:
        Serial.println("Threshold 1");;
        break;
      case evt_high_lim:
        Serial.println("High Limit");;
        break;
    }
  }
  if (pc1_int_flag) {
    pc1_int_flag = false;
    Serial.print("pc1 : ");
    switch (pc1_event)
    {
      case evt_thres0:
        Serial.println("Threshold 0");
        break;
      case evt_thres1:
        Serial.println("Threshold 1");;
        break;
      case evt_high_lim:
        Serial.println("High Limit");;
        break;
    }
  }
}