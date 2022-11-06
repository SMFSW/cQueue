/*!\file cQueue.c
** \author SMFSW
** \copyright BSD 3-Clause License (c) 2017-2022, SMFSW
** \brief Queue handling library (written in plain c)
** \details Queue handling library (written in plain c)
**/
/****************************************************************/
#include <string.h>
#include <stdlib.h>

#include "cQueue.h"
/****************************************************************/


/*!	\brief Increment index
**	\details Increment buffer index \b pIdx rolling back to \b start when limit \b end is reached
**	\param [in,out] pIdx - pointer to index value
**	\param [in] end - counter upper limit value
**	\param [in] start - counter lower limit value
**/
static inline void __attribute__((nonnull, always_inline)) inc_idx(uint16_t * const pIdx, const uint16_t end, const uint16_t start)
{
	if (*pIdx < end - 1)	{ (*pIdx)++; }
	else					{ *pIdx = start; }
}

/*!	\brief Decrement index
**	\details Decrement buffer index \b pIdx rolling back to \b end when limit \b start is reached
**	\param [in,out] pIdx - pointer to index value
**	\param [in] end - counter upper limit value
**	\param [in] start - counter lower limit value
**/
static inline void __attribute__((nonnull, always_inline)) dec_idx(uint16_t * const pIdx, const uint16_t end, const uint16_t start)
{
	if (*pIdx > start)		{ (*pIdx)--; }
	else					{ *pIdx = end - 1; }
}


void * __attribute__((nonnull)) q_init(	Queue_t * const pQ,
										const size_t size_rec, const uint16_t nb_recs,
										const QueueType type, const bool overwrite)
{
	q_kill(pQ);	// De-Init queue (if previously initialized) and set structure to 0 to ensure proper functions behavior when queue is not allocated

	const uint32_t size = nb_recs * size_rec;

	pQ->queue = (uint8_t *) malloc(size);

	if (pQ->queue != NULL)
	{
		pQ->dynamic = true;

		pQ->queue_sz = size;
		pQ->rec_sz = size_rec;
		pQ->rec_nb = nb_recs;
		pQ->impl = type;
		pQ->ovw = overwrite;

		pQ->init = QUEUE_INITIALIZED;
	}

	return pQ->queue;	// return NULL when queue not properly allocated, Queue data address otherwise
}

void * __attribute__((nonnull)) q_init_static(	Queue_t * const pQ,
												const size_t size_rec, const uint16_t nb_recs,
												const QueueType type, const bool overwrite,
												void * const pQDat, const size_t lenQDat)
{
	q_kill(pQ);	// De-Init queue (if previously initialized) and set structure to 0 to ensure proper functions behavior when queue is not allocated

	const uint32_t size = nb_recs * size_rec;

	if (lenQDat < size)	{ return NULL; }	// Check static Queue data size

	pQ->queue = (uint8_t *) pQDat;

	if (pQ->queue != NULL)
	{
		pQ->queue_sz = size;
		pQ->rec_sz = size_rec;
		pQ->rec_nb = nb_recs;
		pQ->impl = type;
		pQ->ovw = overwrite;

		pQ->init = QUEUE_INITIALIZED;
	}

	return pQ->queue;	// return NULL when queue not properly allocated, Queue data address otherwise
}

void __attribute__((nonnull)) q_kill(Queue_t * const pQ)
{
	if ((pQ->init == QUEUE_INITIALIZED) && pQ->dynamic && (pQ->queue != NULL))	{ free(pQ->queue); }	// Free existing data (if already dynamically initialized)
	memset(pQ, 0, sizeof(Queue_t));
}


void __attribute__((nonnull)) q_flush(Queue_t * const pQ)
{
	pQ->in = 0;
	pQ->out = 0;
	pQ->cnt = 0;
}


bool __attribute__((nonnull)) q_push(Queue_t * const pQ, const void * const record)
{
	if ((!pQ->ovw) && q_isFull(pQ))	{ return false; }

	uint8_t * const pStart = pQ->queue + (pQ->rec_sz * pQ->in);
	memcpy(pStart, record, pQ->rec_sz);

	inc_idx(&pQ->in, pQ->rec_nb, 0);

	if (!q_isFull(pQ))	{ pQ->cnt++; }	// Increase records count
	else if (pQ->ovw)					// Queue is full and overwrite is allowed
	{
		if (pQ->impl == FIFO)			{ inc_idx(&pQ->out, pQ->rec_nb, 0); }	// as oldest record is overwritten, increment out
		//else if (pQ->impl == LIFO)	{}										// Nothing to do in this case
	}

	return true;
}

bool __attribute__((nonnull)) q_pop(Queue_t * const pQ, void * const record)
{
	const uint8_t * pStart;

	if (q_isEmpty(pQ))	{ return false; }	// No more records

	if (pQ->impl == FIFO)
	{
		pStart = pQ->queue + (pQ->rec_sz * pQ->out);
		inc_idx(&pQ->out, pQ->rec_nb, 0);
	}
	else if (pQ->impl == LIFO)
	{
		dec_idx(&pQ->in, pQ->rec_nb, 0);
		pStart = pQ->queue + (pQ->rec_sz * pQ->in);
	}
	else	{ return false; }

	memcpy(record, pStart, pQ->rec_sz);
	pQ->cnt--;	// Decrease records count
	return true;
}

bool __attribute__((nonnull)) q_peek(const Queue_t * const pQ, void * const record)
{
	const uint8_t * pStart;

	if (q_isEmpty(pQ))	{ return false; }	// No more records

	if (pQ->impl == FIFO)
	{
		pStart = pQ->queue + (pQ->rec_sz * pQ->out);
		// No change on out var as it's just a peek
	}
	else if (pQ->impl == LIFO)
	{
		uint16_t rec = pQ->in;	// Temporary var for peek (no change on pQ->in with dec_idx)
		dec_idx(&rec, pQ->rec_nb, 0);
		pStart = pQ->queue + (pQ->rec_sz * rec);
	}
	else	{ return false; }

	memcpy(record, pStart, pQ->rec_sz);
	return true;
}

bool __attribute__((nonnull)) q_drop(Queue_t * const pQ)
{
	if (q_isEmpty(pQ))			{ return false; }	// No more records

	if (pQ->impl == FIFO)		{ inc_idx(&pQ->out, pQ->rec_nb, 0); }
	else if (pQ->impl == LIFO)	{ dec_idx(&pQ->in, pQ->rec_nb, 0); }
	else						{ return false; }

	pQ->cnt--;	// Decrease records count
	return true;
}

bool __attribute__((nonnull)) q_peekIdx(const Queue_t * const pQ, void * const record, const uint16_t idx)
{
	const uint8_t * pStart;

	if (idx + 1 > q_getCount(pQ))	{ return false; }	// Index out of range

	if (pQ->impl == FIFO)
	{
		pStart = pQ->queue + (pQ->rec_sz * ((pQ->out + idx) % pQ->rec_nb));
	}
	else if (pQ->impl == LIFO)
	{
		pStart = pQ->queue + (pQ->rec_sz * idx);
	}
	else	{ return false; }

	memcpy(record, pStart, pQ->rec_sz);
	return true;
}

