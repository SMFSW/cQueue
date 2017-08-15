/*!\file cQueue.h
** \author SMFSW
** \version 1.0
** \date 2017/07/14
** \copyright BSD 3-Clause License (c) 2017, SMFSW
** \brief Queue handling library (designed in c on STM32)
** \details Queue handling library (designed in c on STM32)
**/

#ifndef __CQUEUE_H__
#define __CQUEUE_H__


#ifdef __cplusplus
extern "C"{
#endif

#include <inttypes.h>
#include <stdbool.h>


typedef enum enumQueueType {
	FIFO = 0,
	LIFO = 1
} QueueType;


typedef struct Queue_t {
	QueueType	impl;		//!< Queue implementation: FIFO LIFO
	bool		ovw;		//!< Overwrite previous records when queue is full allowed
	uint16_t	rec_nb;		//!< number of records in the queue
	uint16_t	rec_sz;		//!< Size of a record
	uint8_t *	queue;		//!< Queue start pointer (when allocated)
	
	uint16_t	in;			//!< number of records pushed into the queue
	uint16_t	out;		//!< number of records pulled from the queue (only for FIFO)
	uint16_t	cnt;		//!< number of records not retrieved from the queue
	uint16_t	init;		//!< sets to 0x5A5A after a first init of the queue
} Queue_t;


/*!	\brief Queue constructor
**	\param [in] q - pointer of queue to handle
**	\param [in] size_rec - size of a record in the queue
**	\param [in] nb_recs - number of records in the queue
**	\param [in] type - Queue implementation type: FIFO, LIFO
**	\param [in] overwrite - Overwrite previous records when queue is full
**	\return nothing
**/
void q_init(Queue_t * q, uint16_t size_rec, uint16_t nb_recs, QueueType type, bool overwrite);

#define q_init_def(q, sz)	q_init(q, sz, 20, FIFO, false)

/*!	\brief Queue desructor: release dynamically allocated queue
**	\param [in] q - pointer of queue to handle
**/
void q_kill(Queue_t * q);

/*!	\brief Clean queue, restarting from empty queue
**/
void q_clean(Queue_t * q);

/*!	\brief get emptiness state of the queue
**	\param [in] q - pointer of queue to handle
**	\return Queue emptiness status
**	\retval true if queue is empty
**	\retval false is not empty
**/
inline bool __attribute__((always_inline)) q_isEmpty(Queue_t * q) {
	return (!q->cnt) ? true : false;
}

/*!	\brief get fullness state of the queue
**	\param [in] q - pointer of queue to handle
**	\return Queue fullness status
**	\retval true if queue is full
**	\retval false is not full
**/
inline bool __attribute__((always_inline)) q_isFull(Queue_t * q) {
	return (q->cnt == q->rec_nb) ? true : false;
}

/*!	\brief get number of records in the queue
**	\param [in] q - pointer of queue to handle
**	\return Number of records left in the queue
**/
inline uint16_t __attribute__((always_inline)) q_nbRecs(Queue_t * q) {
	return q->cnt;
}

/*!	\brief Push record to queue
**	\param [in] q - pointer of queue to handle
**	\param [in] record - pointer to record to be pushed into queue
**	\return Push status
**	\retval true if succefully pushed into queue
**	\retval false if queue is full
**/
bool q_push(Queue_t * q, void * record);

/*!	\brief Pop record from queue
**	\param [in] q - pointer of queue to handle
**	\param [in,out] record - pointer to record to be popped from queue
**	\return Pop status
**	\retval true if succefully pulled from queue
**	\retval false if queue is empty
**/
bool q_pop(Queue_t * q, void * record);

/*!	\brief Peek record from queue
**	\param [in] q - pointer of queue to handle
**	\param [in,out] record - pointer to record to be peeked from queue
**	\return Peek status
**	\retval true if succefully pulled from queue
**	\retval false if queue is empty
**/
bool q_peek(Queue_t * q, void * record);

	/*!	\brief Drop current record from queue
	**	\param [in] q - pointer of queue to handle
	**	\return drop status
	**	\retval true if succefully dropped from queue
	**	\retval false if queue is empty
	**/
bool q_drop(Queue_t * q);

#ifdef __cplusplus
}
#endif

#endif /* __CQUEUE_H__ */
