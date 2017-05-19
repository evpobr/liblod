#include <stdlib.h>
#include <stdio.h>

typedef struct lod_private
{
	struct lod_vio *vio;
	int is_opened;
	int close_vio;
	FILE *fp;
} lod_ctx;
