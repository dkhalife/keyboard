unsigned short keydata = 0, special = 0, down = 0;
sbit PS2_Data            at RD0_bit;
sbit PS2_Clock           at RD1_bit;
sbit PS2_Data_Direction  at TRISD0_bit;
sbit PS2_Clock_Direction at TRISD1_bit;
int note;
int counter;
int counting;

void main() {
//  ANSEL  = 0;                                         // Configure AN pins as digital I/O
//  ANSELH = 0;
//  C1ON_bit = 0;                                       // Disable comparators
//  C2ON_bit = 0;
//  UART1_Init(19200);                                  // Initialize UART module at 19200 bps
  Ps2_Config();                                       // Init PS/2 Keyboard
  Delay_ms(100);                                      // Wait for keyboard to finish
//  UART1_Write_Text("Ready");
//  UART1_Write(10);                                    // Line Feed
//  UART1_Write(13);                                    // Carriage return

        note = 0;
        Sound_Init(&PORTD, 2);
        
  do {
    if (Ps2_Key_Read(&keydata, &special, &down)) {
				if(special) continue; // Skip ctrl, shift ...
				
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
// if (down && (keydata == 16)) {                  // Backspace
// UART1_Write(0x08);      
// }
// else if (down && (keydata == 13)) {             // Enter
// UART1_Write( 'r');                            // send carriage return to usart terminal
// UART1_Write('n');                          // uncomment this line if usart terminal also expects line feed                                                // for new line transition
// }
// else if (down && !special && keydata) {
// UART1_Write(keydata);
// }
    }
        
		if(counting == 1){
			++counter;
			Delay_ms(100);
		}
		
        if(note != 0){
                Sound_Play(note, counter*100);
                note = 0;
        }
		Delay_ms(1);                                      // debounce
  }while(1);
}