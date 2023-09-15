// pixy brightness = 46

#include <Pixy2.h>

Pixy2 pixy;

void setup() {
  Serial.begin(115200);
  Serial.print("Starting...\n");

  pixy.init();
  // change to the line_tracking program.  Note, changeProg can use partial strings, so for example,
  // you can change to the line_tracking program by calling changeProg("line") instead of the whole
  // string changeProg("line_tracking")
  Serial.println(pixy.changeProg("line"));
}

void loop() {
  int8_t i;
  // char buf[128];
  // for (int i = 0; i < 255; i++) {
  //   pixy.setCameraBrightness(i);
  //   delay(50);
  // }

  pixy.line.getMainFeatures();
  // pixy.line.getAllFeatures();

  Serial.print("Vector Count: ");
  Serial.println(pixy.line.numVectors);


  if (pixy.line.numVectors == 0) {
    return;
  }
  float xmid = 0;
  float ymid = 0;
  Vector* curr_vector_ptr = pixy.line.vectors;
  for (int i = 0; i < pixy.line.numVectors; i++) {
    //go to next vector
    curr_vector_ptr += i;

    xmid += curr_vector_ptr->m_x0;
    xmid += curr_vector_ptr->m_x1;
    ymid += curr_vector_ptr->m_y0;
    ymid += curr_vector_ptr->m_y1;
  }
  xmid /= pixy.line.numVectors * 2;
  ymid /= pixy.line.numVectors * 2;
  // pixy.setLamp(0, 0);
  int8_t res = pixy.getResolution();
  Serial.print("Resolution: ");
  Serial.println((String)pixy.frameWidth + " : " + (String)pixy.frameHeight);
  Serial.println((String)xmid + " : " + (String)ymid);
}
