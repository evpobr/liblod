#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

struct lod_entry
{
	char name[16];
	uint32_t offset;
	uint32_t size_original;
	uint32_t format;
	uint32_t size_compressed;
};

struct lod_header
{
	uint32_t magic;
	uint32_t type;
	uint32_t entries_count;
	uint8_t  unknown[80];
};

typedef struct lod_private
{
	struct lod_vio *vio;
	int is_opened;
	int close_vio;
	void *user_data;
	int  status;

	struct lod_header header;
	struct lod_entry *entries;
} lod_ctx;
