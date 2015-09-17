#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define _RING_ARENA_MAX_ALIGN 16

struct RingArena {
	size_t size;
	size_t last;
	void** ring;
};

struct RingArena *RingArena_create(size_t size)
{
	assert(size > 0);
	struct RingArena *ret = malloc(sizeof(*ret));
	if (ret == NULL) goto nomem_arena;
	ret->size = size;
	ret->ring = malloc(size * sizeof(*ret->ring));
	if (ret->ring == NULL) goto nomem_ring;
	for (size_t i = 0; i < size; i++) {
		ret->ring[i] = NULL;
	}
	ret->last = 0;
	return ret;
nomem_ring:
	free(ret);
nomem_arena:
	return NULL;
}

void RingArena_destroy(struct RingArena *arena)
{
	for (size_t i = 0; i < arena->size; i++) {
		if (arena->ring[i] != NULL) {
			free(arena->ring[i]);
		}
	}
	free(arena->ring);
	free(arena);
}

// RingArena has no free, it does it automatically.
void *RingArena_malloc(struct RingArena *arena, size_t size)
{
	assert(size > 0);
	arena->last = (arena->last + 1) % arena->size;
	void *p = realloc(arena->ring[arena->last], _RING_ARENA_MAX_ALIGN + size);
	if (p == NULL) {
		return NULL;
	} else {
		arena->ring[arena->last] = p;
		return ((char *)p) + _RING_ARENA_MAX_ALIGN;
	}
}

int main(int argc, char const *argv[])
{
	struct RingArena *arena = RingArena_create(3);
	for (int i = 0; i < 100; i++) {
		char *temp = RingArena_malloc(arena, 100);
		sprintf(temp, "%d", i);
		printf("%s\n", temp);
	}
	RingArena_destroy(arena);
	return 0;
}