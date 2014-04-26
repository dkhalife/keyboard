#line 1 "C:/Users/Dan/Documents/PIC Projects/Keyboard/Keyboard.c"
unsigned short keydata = 0, special = 0, down = 0;
sbit PS2_Data at RD0_bit;
sbit PS2_Clock at RD1_bit;
sbit PS2_Data_Direction at TRISD0_bit;
sbit PS2_Clock_Direction at TRISD1_bit;
int note;
int counter;
int counting;

void main() {





 Ps2_Config();
 Delay_ms(100);




 note = 0;
 Sound_Init(&PORTD, 2);

 do {
 if (Ps2_Key_Read(&keydata, &special, &down)) {
 if(special) continue;

 if(down){
 counter = 0;
 counting = 1;
 }
 else{
 counting = 0;

 switch(keydata){
 case 'a':
 note = 1000;
 break;

 default:
 note = 300;
 break;
 }
 }










 }

 if(counting == 1){
 ++counter;
 Delay_ms(100);
 }

 if(note != 0){
 Sound_Play(note, counter*100);
 note = 0;
 }
 Delay_ms(1);
 }while(1);
}
