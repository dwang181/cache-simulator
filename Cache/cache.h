#ifndef CACHE_H_
#define CACHE_H_

#define L1 0
#define L2 1

#define LRU 0
#define FIFO 1
#define PLRU 2
#define OPTIMIZATION 3

#define NON_INCLUSIVE 0
#define INCLUSIVE 1
#define EXCLUSIVE 2

#define READ 'r'
#define WRITE 'w'
#define HIT 0
#define MISS 1

#define DIRTY 1
#define CLEAN 0
#define VALID 1
#define INVALID 0

#define LEFT 0
#define RIGHT 1


typedef char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef struct block
{
	/* uint8_t* BLOCK_content; */
	uint64_t TAG;
	uint8_t DIRTY_BIT;
	uint8_t VALID_BIT;
}block;

typedef struct set
{
	block *BLOCK;
	uint64_t *RANK;
}set;

typedef struct cache_stat
{
	uint64_t num_reads;
	uint64_t num_writes;
	uint64_t num_read_hit;
	uint64_t num_read_miss;
	uint64_t num_write_hit;
	uint64_t num_write_miss;
	uint64_t num_write_back;
	uint64_t num_blocks_transferred;
}cache_stat;

typedef struct cache
{
	set *CACHE_IC;

	uint32_t SIZE;
	uint32_t ASSOC;
	uint32_t REPL_POLICY;
	uint32_t INCLUSION;

	uint32_t SET_NUM;
	uint32_t TAG_WIDTH;
	uint32_t INDEX_WIDTH;

	cache_stat CACHE_STAT;
}cache;

extern cache* CACHE;

extern uint32_t NUM_LEVEL;
extern uint32_t BLOCKSIZE, BLOCK_OFFSET_WIDTH;

extern char* TRACE_FILE;
extern uint64_t trace_count;
extern uint64_t *OPTIMIZATION_TRACE;

void Cache_Initial();

void Interpret_Address(uint32_t level, uint64_t ADDR, uint64_t *tag, uint64_t *index);

uint64_t Rebuild_Address(uint8_t level, uint64_t tag, uint64_t index);

uint8_t Cache_Search(uint8_t level, uint64_t tag, uint64_t index, uint32_t *way_num);

void Rank_Maintain(uint8_t level, uint64_t *rank, uint32_t way_num, uint64_t value, uint8_t result);

uint32_t Rank_Top(uint8_t level, const uint64_t *rank);

uint32_t Cache_Replacement(uint8_t level, uint64_t index, uint64_t tag);

void Write_Back(uint8_t level, uint64_t ADDR);

uint8_t Read(uint64_t ADDR, uint64_t *tag, uint64_t *index, uint32_t *way_num);

void Write(uint8_t level, uint64_t ADDR, uint64_t *tag, uint64_t *index, uint32_t *way_num);
#endif