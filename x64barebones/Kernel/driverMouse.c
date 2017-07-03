#include <interruptions.h>
#include <driverVideo.h>
#include <driverMouse.h>
#include <driverKeyboard.h>

char * vidStartM = (char *) VIDSTART;
static int cycle = 0; // unsigned char
static char mouse_bytes[3];   // signed char
static int mouse_x = 0;     // signed char
static int mouse_y = 0;     // signed char
static char leftClickPressed = 0;
static char rightClickPressed = 0;
static char wheelClickPressed = 0;
//static char * position = 0;
//static int start = 0;
static int leftStart_x = 0;     // signed char
static int leftStart_y = 0;     // signed char

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
  // printOnScreen("In-");
  mouse_bytes[cycle] = read_port(0x60);
  if(cycle == 0){
    // printOnScreen("cycle es cero@");
    if((mouse_bytes[0] & 0x80) || (mouse_bytes[0] & 0x40)) {
      cycle = -1;
      // printOnScreen("cycle es -1");
    }
  } else if (cycle == 2) {
    // printOnScreen("YYYYYYYY");
    char leftClick = 0;
    char rightClick = 0;
    char wheelClick = 0;

    cycle = -1;
    if (mouse_bytes[0] & 0x4) {
      // printOnScreen("Middle button is pressed!");
      wheelClick = 1;
    }
    if (mouse_bytes[0] & 0x2) {
      // printOnScreen("Right button is pressed!");
      rightClick = 1;
    }
    if (mouse_bytes[0] & 0x1) {
      // printOnScreen("Left button is pressed!");
      leftClick = 1;
    }
    printCursor(mouse_bytes[1]/3, mouse_bytes[2]/3, 1);
  }
  cycle++;
  // printOnScreen("Out;");
}

void printCursor(uint8_t mouseCoord_x, uint8_t mouseCoord_y, char leftClick) {

  uint8_t aux_x = mouse_x + mouseCoord_x;
  uint8_t aux_y = mouse_y - mouseCoord_y;

  if( aux_x >= 0 && aux_x < COLS && aux_y >= 0 && aux_y < ROWS ) {

    draw_pixel(aux_x, aux_y, 0x87);

 //   char * position = vidStartM + COLS*aux_y*PIXEL + aux_x*PIXEL;

    if(!leftClick) {
      if(leftClickPressed) {
//        int i;
//        for( i=0; i< ROWS*COLS*PIXEL; i++){
//          i++;
//          video[i] = MOUSE;
      cleanSelect(leftStart_x, leftStart_y, aux_x, aux_y, DEFAULTC);
      leftStart_x = 0;
      leftStart_y = 0;
      leftClickPressed = 0;
      }
    } else {
      if(!leftClickPressed) {
        leftClickPressed = 1;
        leftStart_x = aux_x;
        leftStart_y = aux_y;
      }
//      position[1] = MOUSE;
      cpyToBuffer(vidStartM + ((aux_x*COLS + aux_y)*2));
      draw_pixel(aux_x, aux_y, 0x90);
    }
    mouse_x = aux_x;
    mouse_y = aux_y;
//    position[1] = 0x81;
    draw_pixel(mouse_x, mouse_y, DEFAULTC);
  }
}
