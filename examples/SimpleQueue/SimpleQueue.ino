/*
  Simple Queue
  Simple queue demonstration
  
  LIFO / FIFO implementations can be tested by changing IMPLEMENTATION

  This example code is in the public domain.

  created 14 July 2017
  by SMFSW
 */

#include <cQueue.h>

#define	IMPLEMENTATION	LIFO


typedef struct strRec {
	uint16_t	entry1;
	uint16_t	entry2;
} Rec;

Rec tab[6] = {
	{ 0x1234, 0x3456 },
	{ 0x5678, 0x7890 },
	{ 0x90AB, 0xABCD },
	{ 0xCDEF, 0xEFDC },
	{ 0xDCBA, 0xBA09 },
	{ 0x0987, 0x8765 }
};

Queue_t		q;	// Queue declaration


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	
	q_init(&q, sizeof(Rec), 10, IMPLEMENTATION, false);
}

// the loop function runs over and over again forever
void loop() {
	unsigned int i;
	
	for (i = 0 ; i < sizeof(tab)/sizeof(Rec) ; i++)
	{
		Rec rec = tab[i];
		q_push(&q, &rec);
	}
	
	for (i = 0 ; i < sizeof(tab)/sizeof(Rec) ; i++)
	{
		Rec rec;
		q_pop(&q, &rec);
		Serial.print(rec.entry1, HEX);
		Serial.print(" ");
		Serial.println(rec.entry2, HEX);
	}
	
	while(1);
}
