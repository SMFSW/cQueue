/*
  Pointers Queue
  Pointers queue demonstration

  This example code is in the public domain.

  created 26 May 2018
  by SMFSW
 */

#include <cQueue.h>

typedef void (* f_act)(int *);	//!< Function pointer typedef for easier use


Queue_t		q;	// Queue declaration

void action1(int * v)	{ *v+=2; Serial.print("Action 1 Called (+2), val="); Serial.println(*v); }
void action2(int * v)	{ *v*=2; Serial.print("Action 2 Called (*2), val="); Serial.println(*v); }
void action3(int * v)	{ *v-=1; Serial.print("Action 3 Called (-1), val="); Serial.println(*v); }

int val = 8;	// Value passed to function pointer for processing


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);

	q_init(&q, sizeof(f_act), 5, FIFO, false);

	for (unsigned int i = 0 ; i < 5 ; i++)
	{
		f_act Act = 0;

		switch (i)
		{
			case 0:
				Act = action1;
				break;
			case 1:
				Act = action2;
				break;
			case 2:
				Act = action3;
				break;
			case 3:
				Act = action2;
				break;
			case 4:
				Act = action1;
				break;
		}

		q_push(&q, &Act);
	}
}

// the loop function runs over and over again forever
void loop() {
	Serial.print("Value before processing = ");
	Serial.println(val);
	for (unsigned int i = 0 ; i < 5 ; i++)
	{
		f_act Act = 0;
		q_pop(&q, &Act);
		Act(&val);
	}
	
	while(1);
}
