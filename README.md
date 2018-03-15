# cQueue

Queue handling library (written in plain c)

This library is designed for a c implementation on embedded devices, yet may be compiled without change with gcc for other purporses/targets.
Designed as a library to be compatbile with Arduino LibManager specifications (yet rather use Queue instead - https://github.com/SMFSW/Queue).
Port of Queue has been made to work with STM32 code written in plain c.

## Usage

- Initialize a Queue using _q_init(Queue_t * q, uint16_t size_rec, uint16_t nb_recs=20, QueueType type=FIFO, overwrite=false):
  - q - pointer to the queue struct
  - size_rec - size of a record in the queue
  - nb_recs - number of records in the queue
  - type - Queue implementation type: _FIFO_, _LIFO_
  - overwrite - Overwrite previous records when queue is full if set to _true_
- Push stuff to the queue using q_push(Queue_t * q, void * rec)
  - returns _true_ if successfully pushed into queue
  - returns _false_ is queue is full
- Pop stuff from the queue using q_pop(Queue_t * q, void * rec) or q_pull(Queue_t * q, void * rec)
  - returns _true_ if successfully popped from queue
  - returns _false_ if queue is empty
- Peek stuff from the queue using q_peek(Queue_t * q, void * rec)
  - returns _true_ if successfully peeked from queue
  - returns _false_ if queue is empty
- Drop stuff from the queue using q_drop(Queue_t * q)
  - returns _true_ if successfully dropped from queue
  - returns _false_ if queue is empty
- Other methods:
  - q_IsInitialized(Queue_t * q): _true_ if initialized properly, _false_ otherwise
  - q_isEmpty(Queue_t * q): _true_ if full, _false_ otherwise
  - q_isFull(Queue_t * q): _true_ if empty, _false_ otherwise
  - q_getCount(Queue_t * q) or q_nbRecs(Queue_t * q): number of records in the queue
  - q_clean(Queue_t * q) or q_flush(Queue_t * q): remove all items in the queue

## Examples included

- SimpleQueue.ino: Simple queue example (both LIFO FIFO implementations can be tested)
- RolloverTest.ino: Simple test to test queue rollover (for lib testing purposes mainly)
- LibTst.ino: flexible test (for lib testing purposes mainly)

## Documentation

Doxygen generated documentation can be found in "cQueue_vXXX.pdf"

## Release Notes

See [release notes](https://github.com/SMFSW/cQueue/ReleaseNotes.md)

## License

BSD 3-Clause License

Copyright (c) 2017-2018, SMFSW
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
