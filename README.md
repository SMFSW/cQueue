# cQueue

Queue handling library (written in plain c)

This library is designed for a c implementation on embedded devices, yet may be compiled without change with gcc for other purporses/targets.
Designed as a library to be compatbile with Arduino LibManager specifications (yet rather use Queue instead - https://github.com/SMFSW/Queue).
Port of Queue has been made to work with STM32 code written in plain c.

## Usage

- Initialize a Queue using _q_init(Queue_t * q, uint16_t size_rec, uint16_t nb_recs=20, QueueType type=FIFO, overwrite=false)_:
  - q - pointer to the queue struct
  - size_rec - size of a record in the queue
  - nb_recs - number of records in the queue
  - type - Queue implementation type: _FIFO_, _LIFO_
  - overwrite - Overwrite previous records when queue is full if set to _true_
- Push stuff to the queue using q_push(Queue_t * q, void * rec)
  - returns _true_ if succefully pushed into queue
  - returns _false_ is queue is full
- Pop stuff from the queue using q_pop(Queue_t * q, void * rec)
  - returns _true_ if succefully popped from queue
  - returns _false_ if queue is empty
- Peek stuff from the queue using q_peek(Queue_t * q, void * rec)
  - returns _true_ if succefully peeked from queue
  - returns _false_ if queue is empty
- Drop stuff from the queue using q_drop(Queue_t * q)
  - returns _true_ if succefully dropped from queue
  - returns _false_ if queue is empty
- Other methods:
  - q_isEmpty(Queue_t * q): _true_ if full, _false_ otherwise
  - q_isFull(Queue_t * q): _true_ if empty, _false_ otherwise
  - q_nbRecs(Queue_t * q): number of records in the queue
  - q_clean(Queue_t * q): resets the queue

## Examples included

- SimpleQueue.ino: Simple queue example (both LIFO FIFO implementations can be tested)
- RolloverTest.ino: Simple test to test queue rollover (for lib testing purposes mainly)
- LibTst.ino: flexible test (for lib testing purposes mainly)

## Misc

Doxygen doc can be generated for the class using doxyfile.

Feel free to share your thoughts @ xgarmanboziax@gmail.com about:

- issues encountered
- optimisations
- improvements & new functionalities
