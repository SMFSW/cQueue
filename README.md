# cQueue [![Build Status](https://travis-ci.org/SMFSW/cQueue.svg?branch=master)](https://travis-ci.org/SMFSW/cQueue)

Queue handling library (written in plain c)

This library is designed for a c implementation on embedded devices, yet may be compiled without change with gcc for other purposes/targets.
Designed as a library to be compatible with Arduino LibManager specifications (yet rather use Queue instead - https://github.com/SMFSW/Queue).
Port of Queue has been made to work with STM32 code written in plain c.

## Usage

- Initialize a Queue using `q_init(Queue_t * q, uint16_t size_rec, uint16_t nb_recs=20, QueueType type=FIFO, overwrite=false)`:
  - `q` - pointer to the queue struct
  - `size_rec` - size of a record in the queue
  - `nb_recs` - number of records in the queue
  - `type` - Queue implementation type: `FIFO`, `LIFO`
  - `overwrite` - Overwrite previous records when queue is full if set to `true`
- Push stuff to the queue using `q_push(Queue_t * q, void * rec)`
  - returns `true` if successfully pushed into queue
  - returns `false` is queue is full
- Pop stuff from the queue using `q_pop(Queue_t * q, void * rec)` or `q_pull(Queue_t * q, void * rec)`
  - returns `true` if successfully popped from queue
  - returns `false` if queue is empty
- Peek stuff from the queue using `q_peek(Queue_t * q, void * rec)`
  - returns `true` if successfully peeked from queue
  - returns `false` if queue is empty
- Drop stuff from the queue using `q_drop(Queue_t * q)`
  - returns `true` if successfully dropped from queue
  - returns `false` if queue is empty
- Other methods:
  - `q_IsInitialized(Queue_t * q)`: `true` if initialized properly, `false` otherwise
  - `q_isEmpty(Queue_t * q)`: `true` if full, `false` otherwise
  - `q_isFull(Queue_t * q)`: `true` if empty, `false` otherwise
  - `q_sizeof(Queue_t * q)`: queue size in bytes (returns 0 in case queue allocation failed)
  - `q_getCount(Queue_t * q)` or `q_nbRecs(Queue_t * q)`: number of records in the queue
  - `q_clean(Queue_t * q)` or `q_flush(Queue_t * q)`: remove all items in the queue

## Examples included

- [SimpleQueue.ino](examples/SimpleQueue/SimpleQueue.ino): Simple queue example (both LIFO FIFO implementations can be tested)
- [RolloverTest.ino](examples/RolloverTest/RolloverTest.ino): Simple test to test queue rollover (for lib testing purposes mainly)
- [LibTst.ino](examples/LibTst/LibTst.ino): flexible test (for lib testing purposes mainly)

## Documentation

Doxygen doc can be generated using "Doxyfile".

See [generated documentation](https://smfsw.github.io/cQueue/)

## Release Notes

See [release notes](ReleaseNotes.md)

## See also

[Queue](https://github.com/SMFSW/Queue) - Cpp implementation of this library
