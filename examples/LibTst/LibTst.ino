/*
  Lib Test

  LIFO / FIFO implementations can be tested by changing IMPLEMENTATION

  This example code is in the public domain.

  created 14 July 2017
  modified 26 May 2018
  by SMFSW
 */

#include <cQueue.h>

#define	IMPLEMENTATION	FIFO
#define OVERWRITE		true

#define NB_PUSH			14
#define NB_PULL			11


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
	
	q_init(&q, sizeof(Rec), 10, IMPLEMENTATION, OVERWRITE);

	Serial.print("Queue is ");
	Serial.print(q_sizeof(&q));
	Serial.println(" bytes long.");
}

// the loop function runs over and over again forever
void loop() {
	unsigned int i;
	
	for (i = 0 ; i < NB_PUSH ; i++)
	{
		Rec rec = tab[i % (sizeof(tab)/sizeof(Rec))];
		q_push(&q, &rec);
		Serial.print(rec.entry1, HEX);
		Serial.print(" ");
		Serial.print(rec.entry2, HEX);
		Serial.print(" Count ");
		Serial.print(q_getCount(&q));
		Serial.print(" Remaining ");
		Serial.print(q_getRemainingCount(&q));
		Serial.print(" Full? ");
		Serial.println(q_isFull(&q));
	}
	
	Serial.print("Full?: ");
	Serial.print(q_isFull(&q));
	Serial.print("  Nb left: ");
	Serial.println(q_getCount(&q));
	for (i = 0 ; i < NB_PULL+1 ; i++)
	{
		Rec rec = {0xffff,0xffff};
		if (i != NB_PULL / 2)	{ Serial.print(q_pop(&q, &rec)); }
		else					{ Serial.print("Test Peek: "); Serial.print(q_peek(&q, &rec)); }
		Serial.print(" ");
		Serial.print(rec.entry1, HEX);
		Serial.print(" ");
		Serial.println(rec.entry2, HEX);
	}
	Serial.print("Empty?: ");
	Serial.print(q_isEmpty(&q));
	Serial.print("  Nb left: ");
	Serial.println(q_getCount(&q));
	
	while(1);
}