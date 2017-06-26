// #include <interruptions.h>
// #include <driverVideo.h>

// static int mouse_cycle = 0; // unsigned char
// static int mouse_byte[3];   // signed char
// static int mouse_x = 0;     // signed char
// static int mouse_y = 0;     // signed char

// void mouse_wait(unsigned char type){
//   unsigned int _time_out=100000;
//   if(type==0)
//   {
//     while(_time_out--) //Data
//     {
//       if((read_port(0x64) & 1)==1)
//       {
//         return;
//       }
//     }
//     return;
//   }
//   else
//   {
//     while(_time_out--) //Signal
//     {
//       if((read_port(0x64) & 2)==0)
//       {
//         return;
//       }
//     }
//     return;
//   }
// }

// void mouse_write(unsigned char a_write) {
// 	//Wait to be able to send a command
// 	mouse_wait(1);
// 	//Tell the mouse we are sending a command
// 	write_port(0x64, 0xD4);
// 	//Wait for the final part
// 	mouse_wait(1);
// 	//Finally write
// 	write_port(0x60, a_write);
// }

// unsigned char mouse_read() {
// 	//Get response from mouse
// 	mouse_wait(0);
// 	return read_port(0x60);
// }

// void initialize_Mouse() {
// 	//cuando prendo la computadora, el mouse esta desactivado
// 	//y la informacion que proviene de el no va a generar interrupciones
// 	//entonces debo activarlo
// 	printOnScreen("Inicializando el mouse...");
// 	char status;

// 	mouse_wait(1); //espera hasta que el mouse pueda enviar/recibir comandos/data
// 	write_port(0x64,0xA8); //activo el mouse

// 	mouse_wait(1);
// 	write_port(0x64,0x20); //modifico el byte del compaq status para habilitar las interrupciones

// 	mouse_wait(0);
// 	status=(read_port(0x60) | 2); //sets bit number 1 (value=2) que es responsable de activar la IRQ12

// 	mouse_wait(1);
// 	write_port(0x64, 0x60);

// 	mouse_wait(1);
// 	write_port(0x60, status); ////mando el byte modificado al port 0x60

// 	//hago el setup del mouse
// 	mouse_write(0xF6); //le digo al mouse que use los default settings
// 	mouse_read();

// 	mouse_write(0xF4); //habilito el mouse
// 	mouse_read();
// }


// void mouse_handler(){
// 	printOnScreen("Mouse handler...");
//   static unsigned char cycle = 0;
//   static char mouse_bytes[3];
//   mouse_bytes[cycle++] = read_port(0x60);
 
//   if (cycle == 3) { // if we have all the 3 bytes...
//     cycle = 0; // reset the counter
//     // do what you wish with the bytes, this is just a sample
//     if ((mouse_bytes[0] & 0x80) || (mouse_bytes[0] & 0x40))
//       return; // the mouse only sends information about overflowing, do not care about it and return
//     // if (!(mouse_bytes[0] & 0x20))
//     //   y |= 0xFFFFFF00; //delta-y is a negative value
//     // if (!(mouse_bytes[0] & 0x10))
//     //   x |= 0xFFFFFF00; //delta-x is a negative value
//     if (mouse_bytes[0] & 0x4)
//       printOnScreen("Middle button is pressed!");
//     if (mouse_bytes[0] & 0x2)
//       printOnScreen("Right button is pressed!");
//     if (mouse_bytes[0] & 0x1)
//       printOnScreen("Left button is pressed!");
//     // do what you want here, just replace the puts's to execute an action for each button
//     // to use the coordinate data, use mouse_bytes[1] for delta-x, and mouse_bytes[2] for delta-y
//   }
//   printOnScreen("Leaving mouse handler...");
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <interruptions.h>
#include <driverVideo.h>
#include <driverMouse.h>

static int cycle = 0; // unsigned char
static char mouse_bytes[3];   // signed char
static int mouse_x = 0;     // signed char
static int mouse_y = 0;     // signed char

void mouse_wait(unsigned char type){
  unsigned int _time_out = 100000;
  if(type == 0) {
    while(_time_out--) { //Data
      if((read_port(0x64) & 1) == 1) {
      // if((read_port(0x64) & 0x0b1) == 1) {
        return;
      }
    }
    return;
  } else {
    while(_time_out--) { //Signal
      if((read_port(0x64) & 2) == 0) {
      // if((read_port(0x64) & 0x0b10) == 1) {
        return;
      }
    }
    return;
  }
}

void mouse_write(unsigned char a_write) {
  //Wait to be able to send a command
  mouse_wait(1);
  //Tell the mouse we are sending a command
  write_port(0x64, 0xD4);
  //Wait for the final part
  mouse_wait(1);
  //Finally write
  write_port(0x60, a_write);
}

unsigned char mouse_read() {
  //Get response from mouse
  mouse_wait(0);
  return read_port(0x60);
}

void initialize_Mouse() {
  //cuando prendo la computadora, el mouse esta desactivado
  //y la informacion que proviene de el no va a generar interrupciones
  //entonces debo activarlo
  unsigned char status;

  mouse_wait(1); //espera hasta que el mouse pueda enviar/recibir comandos/data
  write_port(0x64,0xA8); //activo el mouse

  mouse_wait(1);
  write_port(0x64,0x20); //modifico el byte del compaq status para habilitar las interrupciones

  mouse_wait(0);
  status=(read_port(0x60) | 0b10); //sets bit number 1 (value=2) que es responsable de activar la IRQ12

  mouse_wait(1);
  write_port(0x64, 0x60);

  mouse_wait(1);
  write_port(0x60, status); ////mando el byte modificado al port 0x60

  //hago el setup del mouse
  mouse_write(0xF6); //le digo al mouse que use los default settings
  mouse_read();

  mouse_write(0xF4); //habilito el mouse
  mouse_read();
}


void mouse_handler() {
  printOnScreen("In-");
  mouse_bytes[cycle] = read_port(0x60);
  if(cycle == 0){
    printOnScreen("cycle es cero@");
    if((mouse_bytes[0] & 0x80) || (mouse_bytes[0] & 0x40)) {
      cycle = -1;
      printOnScreen("cycle es -1");
    }
  } else if (cycle == 2) {
    printOnScreen("YYYYYYYY");
    char leftClickPressed = 0;
    char rightClickPressed = 0;
    char wheelClickPressed = 0;
    cycle = -1;
    if (mouse_bytes[0] & 0x4) {
      printOnScreen("Middle button is pressed!");
      wheelClickPressed = 1;
    }
    if (mouse_bytes[0] & 0x2) {
      printOnScreen("Right button is pressed!");
      rightClickPressed = 1;
    }
    if (mouse_bytes[0] & 0x1) {
      printOnScreen("Left button is pressed!");
      leftClickPressed = 1;
    }
    // do what you want here, just replace the puts's to execute an action for each button
    // to use the coordinate data, use mouse_bytes[1] for delta-x, and mouse_bytes[2] for delta-y
  }
  cycle++;
  printOnScreen("Out;");
}

// void printCursor (uint8_t mouse_x, uint8_t mouse_y, char mouseLeftClickPressed){
//   uint8_t aux_x = mouse_x + mouse_y;
//   uint8_t aux_y = mouse_x - mouse_y;

//   if(aux_x >= 0 && aux_y)

// }
