# cQueue

[![author](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/SMFSW/a9a2b2a02fda1b33461d53ddfe69d649/raw/auth_SMFSW.json)](https://github.com/SMFSW)
![badge](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/SMFSW/a9a2b2a02fda1b33461d53ddfe69d649/raw/cQueue_status_badge.json)
[![license](https://img.shields.io/badge/License-BSD3-darkred.svg)](LICENSE)
[![CodeFactor](https://www.codefactor.io/repository/github/smfsw/cqueue/badge)](https://www.codefactor.io/repository/github/smfsw/cqueue)

![platform](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/SMFSW/a9a2b2a02fda1b33461d53ddfe69d649/raw/ANY_platform.json)

[![doxy](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/SMFSW/a9a2b2a02fda1b33461d53ddfe69d649/raw/tool_DOXY.json)](https://smfsw.github.io/cQueue)
[![re_note](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/SMFSW/a9a2b2a02fda1b33461d53ddfe69d649/raw/tool_RN.json)](ReleaseNotes.md)

![badge](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/SMFSW/a9a2b2a02fda1b33461d53ddfe69d649/raw/cQueue_custom_repo_badge.json)

Queue handling library (written in plain c)

This library is designed for a c implementation on embedded devices, yet may be compiled without change with gcc for other purposes/targets.
Designed as a library to be compatible with Arduino LibManager specifications (yet rather use Queue instead - https://github.com/SMFSW/Queue).

## Usage

- Initialize a Queue using `q_init(Queue_t * pQ, size_t size_rec, uint16_t nb_recs, QueueType type, bool overwrite)`:
  - `pQ` - pointer to the queue struct
  - `size_rec` - size of a record in the queue
  - `nb_recs` - number of records in the queue
  - `type` - queue implementation type: `FIFO`, `LIFO`
  - `overwrite` - overwrite previous records when queue is full if set to `true`
- OR a statically allocated Queue using `q_init_static(Queue_t * pQ, size_t size_rec, uint16_t nb_recs, QueueType type, bool overwrite, void * pQDat, size_t lenQDat)`:
  - `pQ` - pointer to the queue struct
  - `size_rec` - size of a record in the queue
  - `nb_recs` - number of records in the queue
  - `type` - queue implementation type: `FIFO`, `LIFO`
  - `overwrite` - overwrite previous records when queue is full if set to `true`
  - `pQDat` - pointer to static data queue
  - `lenQDat` - length of static data queue (in bytes)
- Push stuff to the queue using `q_push(Queue_t * pQ, void * rec)`
  - returns `true` if successfully pushed into queue
  - returns `false` is queue is full
- Pop stuff from the queue using `q_pop(Queue_t * pQ, void * rec)` or `q_pull(Queue_t * pQ, void * rec)`
  - returns `true` if successfully popped from queue
  - returns `false` if queue is empty
- Peek stuff from the queue using `q_peek(Queue_t * pQ, void * rec)`
  - returns `true` if successfully peeked from queue
  - returns `false` if queue is empty
- Drop stuff from the queue using `q_drop(Queue_t * pQ)`
  - returns `true` if successfully dropped from queue
  - returns `false` if queue is empty
- Peek stuff at index from the queue using `q_peekIdx(Queue_t * pQ, void * rec, uint16_t idx)`
  - returns `true` if successfully peeked from queue
  - returns `false` if index is out of range
  - warning: no associated drop function, not to use with `q_drop`
- Peek latest stored from the queue using `q_peekPrevious(Queue_t * pQ, void * rec)`
  - returns `true` if successfully peeked from queue
  - returns `false` if queue is empty
  - warning: no associated drop function, not to use with `q_drop`
  - note: only useful with FIFO implementation, use `q_peek` instead with a LIFO
- Other methods:
  - `q_isInitialized(Queue_t * pQ)`: `true` if initialized properly, `false` otherwise
  - `q_isEmpty(Queue_t * pQ)`: `true` if empty, `false` otherwise
  - `q_isFull(Queue_t * pQ)`: `true` if full, `false` otherwise
  - `q_sizeof(Queue_t * pQ)`: queue size in bytes (returns 0 in case queue allocation failed)
  - `q_getCount(Queue_t * pQ)` or `q_nbRecs(Queue_t * pQ)`: number of records stored in the queue
  - `q_getRemainingCount(Queue_t * pQ)`: number of records left in the queue
  - `q_clean(Queue_t * pQ)` or `q_flush(Queue_t * pQ)`: remove all items in the queue

## Notes

- Interrupt safe automation is not implemented in the library. You have to manually disable/enable interrupts where required.
No implementation will be made as it would be an issue when using `peek`/`drop` methods with LIFO implementation:
if an item is put to the queue through interrupt between `peek` and `drop` calls, the `drop` call would drop the wrong (newer) item.
In this particular case, dropping decision must be made before re-enabling interrupts.

## Examples included

- [SimpleQueue.ino](examples/SimpleQueue/SimpleQueue.ino): Simple queue example (both LIFO FIFO implementations can be tested)
- [SimpleQueueStatic.ino](examples/SimpleQueueStatic/SimpleQueueStatic.ino): Simple queue example using static queue data array (both LIFO FIFO implementations can be tested)
- [PointersQueue.ino](examples/PointersQueue/PointersQueue.ino): Queue of function pointers performing queued actions
- [QueueDuplicates.ino](examples/QueueDuplicates/QueueDuplicates.ino): Simple test to test queue duplicates before pushing to queue
- [QueueIdxPeeking.ino](examples/QueueIdxPeeking/QueueIdxPeeking.ino): Simple test to test queue index picking
- [RolloverTest.ino](examples/RolloverTest/RolloverTest.ino): Simple test to test queue rollover (for lib testing purposes mainly)
- [LibTst.ino](examples/LibTst/LibTst.ino): flexible test (for lib testing purposes mainly)

## See also

[Queue](https://github.com/SMFSW/Queue) - Cpp implementation of this library
