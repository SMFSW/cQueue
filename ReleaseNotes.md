cQueue: Queue handling library (written in plain c)
2017-2019 SMFSW

Feel free to share your thoughts @ xgarmanboziax@gmail.com about:
	- issues encountered
	- optimizations
	- improvements & new functionalities

------------

** Actual:

v1.7:	2 Dec 2019:
- Fix wrong github tag leading to no update by Arduino Library Manager (v1.5 is tagged as v1.6 in library.properties)

v1.6:	3 Nov 2019:
- const qualifiers added where missing
- Added q_peekIdx and q_peekPrevious functions
- Added related examples

v1.5:	2 Jun 2019:
- Fixed README.md thanks to @reydelleon
- INC_IDX & DEC_IDX macros changed to inlines
- Added nonnull attribute to check for null pointers (will report warnings at compile time)

v1.4	26 May 2018:
- Added q_sizeOf inline to check full queue size in byte (may also be used to check if queue has been allocated properly)
- Added q_getRemainingCount inline returning how much records are left in the queue
- Adding support for unit tests and doxygen documentation generation with Travis CI
- Updated README.md
- Added more example sketches & updated LibTst example using latest inlines additions

v1.3	14 March 2018:
- Init control value set back to 0 when queue is killed (prevents failure if killing twice the same queue)
- Added q_sizeof inline to check full queue size in byte (may also be used to check if queue has been allocated properly)
- Added q_isInitialized inline to be able to check after init if queue has been properly allocated
- Changed q_nbRecs to q_getCount, but kept q_nbRecs as macro for compatibility with earlier versions
- Changed q_clean to q_flush, but kept q_clean as macro for compatibility with earlier versions
- Comments fixes

v1.2	12 November 2017:
- Use of const qualifier in some function parameters

v1.1	16 August 2017:
- Queue init function now returns queue address (enabling check for queue allocation success)
- q_pull & q_flush alias created for earlier versions and purists respectively

v1.0	14 July 2017:
- First release
