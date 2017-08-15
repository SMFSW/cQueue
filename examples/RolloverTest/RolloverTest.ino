/*
  RolloverTest
  Simple test to test queue rollover (for lib testing purposes mainly)
  
  Queues an incrementing counter & pop a record from queue each cycle

  This example code is in the public domain.

  created 14 July 2017
  by SMFSW
 */

#include <cQueue.h>

uint16_t in = 0;

Queue_t		q;	// Queue declaration


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	
	q_init(&q, sizeof(in), 10, FIFO, false);
	q_push(&q, &in);		// First push into queue
}

// the loop function runs over and over again forever
void loop() {
	uint16_t out;
	
	q_push(&q, &(++in));
	q_pop(&q, &out);
	Serial.println(out);
	delay(200);
}
