#include <linux/hash.h>
#include <linux/hashtable.h>
#include <linux/vmalloc.h>
#include <linux/kdev_t.h>
#include <linux/slab.h>
#include <linux/pagemap.h>
#include <linux/random.h>

#include "dmap.h"
#include "mmap_buffer_hash_table.h"
#include "mmap_buffer_rbtree.h"
#include "shared_defines.h"

#if 0
#if NUM_FREELISTS == 32
static const int __rand[NUM_FREELISTS][NUM_FREELISTS] = {
	{ 28, 1, 18, 6, 29, 0, 16, 5, 8, 23, 20, 2, 3, 21, 4, 13, 10, 9, 27, 15, 14, 30, 7, 11, 22, 24, 31, 25, 19, 26, 17, 12 },
	{ 14, 31, 15, 23, 28, 12, 30, 1, 27, 6, 25, 5, 10, 20, 9, 13, 16, 2, 29, 21, 18, 11, 4, 7, 19, 26, 8, 17, 24, 22, 3, 0 },
	{ 1, 21, 31, 14, 26, 4, 20, 8, 19, 22, 29, 9, 6, 13, 28, 0, 17, 12, 11, 2, 15, 7, 5, 24, 27, 23, 18, 10, 30, 16, 25, 3 },
	{ 29, 30, 14, 24, 20, 15, 5, 27, 26, 6, 1, 8, 2, 21, 10, 19, 16, 13, 18, 17, 23, 0, 25, 22, 3, 9, 11, 7, 31, 4, 28, 12 },
	{ 29, 3, 27, 0, 15, 7, 30, 19, 6, 28, 20, 26, 23, 13, 2, 1, 21, 31, 18, 22, 24, 9, 11, 8, 12, 17, 4, 25, 10, 16, 14, 5 },
	{ 8, 31, 1, 14, 25, 12, 19, 15, 18, 13, 9, 6, 20, 29, 2, 3, 17, 30, 16, 24, 0, 26, 4, 7, 11, 5, 10, 22, 23, 28, 27, 21 },
	{ 20, 24, 2, 5, 23, 8, 25, 7, 6, 29, 31, 1, 12, 30, 3, 10, 4, 15, 18, 16, 28, 27, 0, 13, 21, 22, 19, 9, 14, 11, 26, 17 },
	{ 30, 6, 15, 10, 22, 19, 14, 8, 26, 29, 7, 31, 0, 2, 1, 23, 11, 27, 20, 24, 18, 28, 13, 17, 16, 12, 5, 3, 9, 21, 25, 4 },
	{ 30, 4, 8, 13, 7, 2, 21, 22, 27, 25, 0, 10, 9, 17, 19, 29, 12, 28, 23, 16, 20, 18, 1, 15, 24, 5, 3, 26, 6, 14, 31, 11 },
	{ 2, 1, 19, 27, 14, 11, 5, 20, 31, 16, 13, 26, 24, 23, 18, 25, 28, 21, 12, 9, 10, 15, 8, 0, 30, 4, 6, 22, 7, 17, 3, 29 },
	{ 4, 13, 19, 25, 6, 21, 15, 0, 24, 12, 31, 28, 11, 17, 3, 27, 9, 14, 5, 16, 29, 22, 1, 7, 10, 20, 18, 8, 26, 2, 23, 30 },
	{ 6, 7, 3, 9, 15, 31, 25, 29, 27, 18, 11, 4, 16, 2, 26, 23, 22, 19, 14, 28, 12, 0, 20, 5, 8, 13, 17, 10, 24, 1, 21, 30 },
	{ 18, 30, 27, 17, 11, 5, 28, 0, 20, 13, 3, 15, 12, 23, 8, 25, 29, 1, 14, 22, 16, 19, 10, 9, 26, 6, 4, 31, 7, 2, 21, 24 },
	{ 16, 1, 0, 4, 2, 30, 21, 19, 20, 23, 25, 7, 8, 18, 28, 31, 14, 15, 13, 27, 11, 12, 29, 22, 10, 9, 3, 5, 24, 6, 26, 17 },
	{ 27, 18, 24, 10, 25, 5, 2, 14, 31, 21, 20, 17, 6, 23, 22, 19, 4, 29, 28, 30, 1, 16, 13, 26, 12, 3, 0, 11, 8, 9, 7, 15 },
	{ 21, 22, 23, 1, 5, 12, 17, 20, 24, 30, 10, 31, 11, 2, 18, 7, 13, 3, 0, 29, 26, 15, 8, 28, 25, 4, 14, 6, 9, 19, 27, 16 },
	{ 19, 23, 3, 29, 9, 28, 5, 16, 24, 2, 21, 10, 15, 20, 4, 22, 7, 0, 31, 11, 30, 18, 6, 1, 27, 26, 17, 25, 14, 12, 8, 13 },
	{ 7, 4, 0, 10, 11, 9, 13, 1, 24, 20, 16, 17, 5, 26, 25, 3, 30, 23, 14, 15, 21, 6, 12, 18, 8, 27, 22, 29, 19, 28, 2, 31 },
	{ 31, 6, 3, 23, 21, 22, 4, 8, 10, 28, 12, 7, 19, 17, 24, 14, 29, 9, 27, 11, 1, 5, 13, 2, 25, 30, 0, 26, 18, 20, 15, 16 },
	{ 4, 27, 23, 8, 26, 3, 2, 6, 24, 13, 21, 0, 30, 7, 9, 29, 11, 17, 15, 31, 10, 1, 22, 5, 16, 19, 25, 12, 14, 28, 18, 20 },
	{ 25, 5, 20, 6, 10, 2, 4, 15, 9, 30, 3, 7, 16, 11, 26, 13, 21, 27, 18, 19, 28, 12, 31, 23, 1, 14, 22, 29, 24, 8, 0, 17 },
	{ 11, 17, 26, 27, 10, 2, 13, 22, 30, 23, 14, 8, 16, 7, 9, 3, 4, 19, 25, 28, 18, 0, 21, 29, 6, 12, 5, 31, 15, 1, 24, 20 },
	{ 30, 25, 21, 1, 19, 3, 29, 18, 2, 6, 8, 16, 24, 31, 22, 0, 4, 11, 20, 10, 17, 27, 28, 12, 9, 13, 14, 7, 15, 26, 23, 5 },
	{ 26, 13, 30, 28, 4, 27, 12, 14, 10, 15, 24, 25, 16, 7, 8, 11, 29, 23, 9, 19, 18, 3, 20, 6, 1, 21, 31, 0, 17, 5, 22, 2 },
	{ 6, 30, 22, 28, 31, 9, 4, 12, 8, 27, 18, 19, 23, 11, 10, 17, 0, 1, 3, 14, 29, 15, 13, 20, 2, 25, 7, 24, 16, 21, 5, 26 },
	{ 27, 16, 30, 29, 12, 10, 7, 4, 18, 3, 31, 15, 11, 19, 13, 14, 23, 2, 8, 9, 1, 0, 28, 26, 17, 5, 20, 6, 21, 24, 22, 25 },
	{ 23, 28, 1, 30, 4, 18, 16, 6, 8, 26, 17, 2, 15, 13, 21, 7, 0, 10, 27, 25, 29, 5, 3, 20, 31, 11, 19, 14, 22, 24, 12, 9 },
	{ 17, 6, 7, 8, 16, 12, 30, 25, 1, 9, 4, 28, 27, 29, 18, 5, 0, 24, 23, 20, 3, 2, 26, 11, 31, 13, 15, 14, 19, 10, 22, 21 },
	{ 27, 21, 26, 17, 19, 23, 1, 9, 10, 13, 30, 22, 25, 18, 29, 8, 20, 15, 28, 16, 4, 0, 12, 3, 14, 24, 6, 11, 31, 5, 2, 7 },
	{ 23, 6, 7, 29, 13, 12, 14, 0, 28, 17, 5, 26, 8, 1, 20, 30, 25, 21, 31, 22, 2, 10, 27, 24, 16, 18, 19, 9, 15, 3, 11, 4 },
	{ 30, 28, 13, 0, 17, 24, 3, 9, 6, 20, 29, 18, 27, 15, 10, 26, 22, 2, 19, 16, 31, 21, 12, 5, 8, 7, 4, 25, 11, 23, 1, 14 },
	{ 28, 24, 7, 29, 22, 18, 17, 19, 11, 6, 31, 0, 25, 3, 2, 10, 21, 15, 20, 27, 13, 5, 9, 4, 1, 12, 16, 23, 14, 30, 8, 26 }
};
#elif NUM_FREELISTS == 80
static const int __rand[NUM_FREELISTS][NUM_FREELISTS] = {
{61, 30, 38, 75, 65, 16, 4, 12, 24, 15, 46, 29, 1, 66, 68, 5, 14, 11, 20, 77, 57, 50, 37, 78, 0, 54, 74, 55, 47, 42, 53, 33, 60, 44, 49, 73, 9, 19, 6, 3, 43, 56, 32, 25, 17, 41, 67, 26, 45, 28, 76, 35, 52, 40, 34, 62, 36, 48, 23, 13, 27, 21, 39, 31, 71, 58, 59, 79, 63, 22, 70, 69, 7, 18, 64, 51, 2, 8, 10, 72},
{22, 75, 45, 19, 44, 4, 2, 50, 8, 14, 62, 67, 78, 58, 18, 16, 40, 48, 7, 68, 55, 72, 54, 15, 0, 65, 53, 51, 52, 76, 37, 39, 79, 12, 43, 23, 64, 31, 46, 9, 42, 10, 25, 36, 66, 13, 77, 27, 74, 47, 73, 3, 29, 41, 1, 5, 34, 69, 56, 59, 33, 71, 26, 49, 63, 32, 38, 11, 20, 57, 24, 61, 70, 30, 35, 21, 60, 28, 17, 6},
{8, 48, 18, 47, 37, 70, 62, 21, 71, 10, 79, 41, 75, 54, 68, 24, 57, 74, 40, 0, 59, 9, 78, 55, 6, 43, 64, 17, 34, 61, 29, 50, 66, 56, 51, 25, 44, 33, 52, 39, 19, 20, 31, 63, 45, 69, 32, 36, 16, 13, 26, 60, 12, 76, 15, 14, 46, 67, 22, 28, 42, 5, 72, 30, 38, 53, 23, 4, 49, 3, 2, 7, 27, 73, 35, 11, 58, 65, 77, 1},
{31, 40, 74, 77, 51, 27, 63, 50, 68, 76, 39, 0, 72, 32, 36, 49, 71, 22, 58, 20, 70, 9, 18, 73, 38, 25, 55, 66, 17, 2, 65, 62, 7, 4, 5, 16, 11, 23, 6, 3, 37, 29, 8, 67, 56, 47, 12, 43, 30, 44, 34, 61, 60, 19, 24, 46, 21, 79, 59, 28, 48, 35, 41, 14, 13, 78, 54, 53, 42, 1, 64, 75, 33, 45, 52, 10, 15, 57, 26, 69},
{49, 15, 31, 52, 23, 22, 35, 12, 41, 8, 7, 45, 55, 59, 56, 19, 53, 14, 20, 78, 64, 75, 39, 13, 3, 73, 25, 62, 11, 44, 29, 77, 71, 30, 61, 42, 46, 68, 21, 1, 40, 5, 67, 32, 50, 24, 60, 74, 70, 57, 72, 4, 27, 66, 6, 0, 63, 43, 51, 26, 37, 34, 2, 18, 65, 79, 76, 58, 9, 69, 10, 47, 54, 17, 48, 33, 36, 38, 28, 16},
{52, 49, 72, 55, 69, 20, 51, 66, 3, 30, 27, 34, 37, 45, 25, 64, 47, 19, 32, 65, 22, 74, 68, 42, 18, 53, 41, 71, 17, 12, 9, 46, 33, 16, 70, 57, 23, 58, 36, 13, 44, 35, 21, 77, 15, 24, 6, 59, 5, 60, 76, 2, 10, 56, 50, 78, 11, 73, 29, 61, 79, 7, 4, 1, 14, 75, 67, 63, 26, 39, 40, 31, 38, 28, 48, 8, 62, 54, 0, 43},
{18, 78, 48, 23, 33, 4, 57, 20, 77, 34, 38, 73, 62, 66, 56, 59, 8, 79, 53, 13, 52, 1, 21, 60, 9, 5, 70, 12, 76, 44, 17, 40, 19, 58, 0, 42, 37, 69, 55, 61, 39, 43, 75, 2, 50, 35, 47, 36, 22, 3, 15, 32, 41, 46, 30, 10, 26, 63, 7, 65, 72, 16, 24, 6, 45, 67, 28, 31, 74, 64, 29, 54, 14, 71, 25, 11, 68, 51, 27, 49},
{37, 0, 74, 78, 26, 17, 72, 65, 1, 77, 4, 52, 64, 34, 70, 15, 22, 25, 30, 53, 29, 8, 9, 19, 3, 7, 38, 24, 27, 21, 31, 46, 55, 71, 5, 10, 75, 20, 73, 43, 2, 6, 23, 40, 62, 14, 69, 39, 41, 47, 56, 68, 61, 51, 58, 42, 57, 48, 12, 33, 28, 49, 16, 76, 60, 11, 13, 63, 35, 36, 79, 50, 59, 67, 44, 66, 32, 45, 54, 18},
{45, 16, 53, 69, 74, 65, 32, 36, 49, 59, 64, 77, 5, 3, 39, 25, 43, 6, 4, 40, 28, 55, 0, 46, 48, 2, 62, 52, 78, 24, 10, 29, 47, 67, 73, 27, 9, 30, 31, 41, 34, 14, 66, 19, 8, 76, 15, 54, 11, 20, 72, 58, 12, 79, 21, 37, 57, 17, 51, 18, 26, 71, 44, 63, 68, 1, 38, 13, 75, 50, 33, 42, 70, 61, 7, 60, 35, 56, 23, 22},
{53, 32, 79, 59, 21, 49, 65, 20, 35, 68, 11, 25, 67, 60, 18, 70, 69, 42, 77, 71, 50, 54, 43, 48, 23, 45, 56, 63, 66, 36, 15, 64, 12, 13, 8, 4, 57, 74, 24, 10, 62, 72, 5, 1, 29, 6, 33, 40, 38, 17, 26, 46, 75, 3, 58, 73, 28, 61, 51, 78, 39, 34, 16, 44, 47, 2, 0, 41, 22, 30, 31, 52, 19, 7, 9, 14, 55, 76, 27, 37},
{26, 71, 53, 18, 54, 15, 30, 42, 23, 44, 22, 57, 62, 29, 78, 4, 38, 66, 20, 35, 48, 21, 37, 60, 49, 3, 25, 73, 50, 28, 27, 76, 13, 43, 45, 52, 72, 24, 1, 10, 77, 7, 12, 55, 31, 0, 16, 51, 17, 36, 33, 9, 68, 2, 65, 39, 34, 5, 47, 19, 61, 6, 56, 63, 67, 8, 79, 64, 69, 32, 11, 40, 14, 75, 46, 58, 70, 41, 74, 59},
{3, 9, 23, 22, 77, 68, 36, 42, 75, 7, 4, 59, 62, 11, 38, 32, 2, 41, 30, 20, 24, 33, 35, 53, 21, 28, 60, 47, 69, 0, 70, 16, 10, 43, 73, 72, 71, 39, 14, 66, 48, 65, 27, 51, 46, 74, 34, 58, 31, 55, 44, 50, 40, 25, 8, 45, 29, 17, 64, 26, 79, 15, 6, 78, 56, 54, 12, 37, 13, 49, 18, 57, 19, 1, 52, 63, 5, 76, 61, 67},
{61, 6, 53, 72, 62, 41, 73, 54, 29, 40, 7, 50, 0, 33, 19, 75, 44, 58, 76, 42, 78, 59, 9, 11, 2, 34, 5, 57, 47, 68, 18, 49, 10, 13, 31, 32, 4, 22, 35, 25, 3, 70, 46, 28, 37, 51, 66, 16, 56, 71, 74, 77, 1, 27, 23, 39, 17, 14, 8, 55, 38, 43, 15, 63, 69, 26, 45, 79, 48, 20, 67, 12, 64, 36, 52, 65, 60, 21, 30, 24},
{31, 63, 79, 61, 78, 40, 54, 23, 29, 58, 21, 42, 7, 18, 5, 37, 30, 3, 19, 47, 75, 69, 35, 52, 43, 45, 2, 32, 10, 62, 0, 14, 74, 65, 17, 38, 39, 4, 76, 51, 26, 59, 25, 50, 1, 13, 11, 46, 72, 49, 6, 55, 66, 15, 77, 20, 53, 73, 33, 56, 64, 36, 27, 12, 68, 41, 22, 34, 44, 67, 28, 70, 24, 9, 60, 8, 16, 57, 48, 71},
{66, 30, 48, 73, 72, 41, 17, 8, 64, 1, 24, 10, 33, 23, 54, 0, 13, 29, 62, 18, 39, 69, 2, 47, 74, 14, 35, 42, 46, 58, 21, 4, 31, 11, 56, 28, 60, 20, 44, 32, 55, 67, 53, 45, 5, 76, 26, 38, 16, 25, 3, 49, 65, 52, 22, 71, 15, 51, 61, 27, 43, 78, 63, 9, 68, 79, 57, 34, 19, 59, 37, 77, 7, 70, 75, 36, 40, 6, 50, 12},
{14, 15, 17, 74, 75, 62, 72, 55, 63, 9, 35, 45, 28, 10, 68, 41, 54, 24, 60, 64, 66, 34, 40, 44, 71, 7, 43, 22, 13, 58, 20, 79, 5, 8, 18, 65, 27, 1, 4, 76, 25, 0, 2, 78, 11, 52, 50, 19, 73, 53, 51, 46, 59, 32, 42, 30, 21, 69, 77, 6, 48, 3, 33, 38, 37, 26, 56, 29, 61, 67, 47, 12, 39, 23, 57, 49, 31, 16, 36, 70},
{8, 70, 47, 41, 40, 44, 58, 43, 69, 77, 53, 2, 24, 55, 45, 14, 56, 18, 52, 28, 42, 37, 61, 21, 3, 59, 50, 73, 31, 16, 65, 26, 34, 76, 13, 7, 63, 46, 9, 12, 79, 75, 74, 66, 36, 10, 35, 68, 71, 62, 0, 60, 30, 33, 39, 32, 51, 48, 64, 78, 1, 27, 49, 20, 38, 54, 5, 67, 15, 4, 11, 29, 17, 57, 72, 22, 19, 25, 23, 6},
{9, 72, 32, 62, 19, 16, 71, 67, 23, 37, 6, 15, 35, 52, 43, 68, 39, 30, 70, 38, 73, 77, 11, 51, 53, 3, 56, 49, 64, 45, 22, 8, 61, 5, 24, 65, 50, 42, 76, 48, 63, 47, 0, 58, 27, 57, 59, 46, 66, 78, 79, 33, 36, 7, 21, 12, 74, 18, 31, 75, 44, 13, 10, 69, 41, 26, 34, 29, 55, 28, 2, 17, 20, 60, 54, 40, 1, 14, 25, 4},
{48, 67, 52, 17, 55, 26, 66, 10, 42, 2, 46, 45, 31, 1, 61, 20, 35, 62, 49, 15, 29, 22, 24, 58, 7, 8, 28, 73, 40, 63, 13, 4, 54, 25, 33, 41, 6, 65, 64, 59, 32, 5, 30, 37, 38, 43, 21, 47, 16, 39, 77, 34, 51, 60, 70, 74, 72, 27, 71, 78, 23, 75, 57, 69, 79, 53, 76, 36, 12, 50, 14, 18, 44, 68, 3, 0, 9, 19, 56, 11},
{43, 18, 38, 64, 34, 21, 46, 31, 17, 55, 0, 14, 45, 71, 36, 35, 41, 32, 29, 28, 10, 11, 12, 16, 7, 79, 1, 13, 15, 63, 8, 4, 2, 54, 58, 39, 23, 75, 60, 72, 70, 44, 65, 57, 25, 77, 24, 47, 50, 52, 61, 20, 51, 53, 27, 68, 59, 26, 76, 9, 69, 78, 67, 19, 33, 74, 73, 66, 22, 5, 37, 3, 49, 42, 56, 40, 30, 6, 48, 62},
{38, 32, 1, 57, 67, 61, 42, 59, 4, 9, 16, 3, 73, 12, 18, 79, 76, 25, 14, 8, 23, 13, 7, 36, 49, 39, 5, 70, 41, 31, 55, 46, 24, 71, 62, 21, 44, 75, 66, 33, 72, 26, 11, 15, 43, 77, 48, 20, 78, 56, 51, 47, 27, 53, 63, 34, 37, 22, 30, 2, 10, 35, 6, 29, 74, 68, 40, 54, 45, 0, 64, 50, 60, 58, 19, 17, 69, 65, 52, 28},
{50, 78, 56, 69, 45, 66, 5, 2, 53, 38, 31, 67, 58, 22, 15, 79, 37, 42, 73, 9, 12, 77, 27, 61, 55, 76, 43, 47, 68, 64, 60, 16, 4, 8, 32, 30, 24, 13, 57, 19, 36, 51, 3, 65, 29, 23, 1, 34, 40, 52, 70, 49, 21, 25, 44, 72, 39, 75, 35, 63, 0, 62, 14, 71, 41, 11, 6, 18, 54, 74, 33, 17, 20, 59, 28, 46, 10, 48, 7, 26},
{11, 54, 46, 1, 14, 7, 44, 62, 9, 79, 6, 31, 43, 22, 13, 20, 26, 75, 3, 41, 61, 78, 69, 53, 56, 39, 58, 29, 19, 5, 74, 57, 16, 33, 66, 70, 42, 4, 35, 36, 21, 24, 67, 18, 37, 76, 2, 34, 65, 45, 47, 10, 49, 15, 23, 8, 52, 68, 30, 51, 0, 48, 25, 60, 63, 32, 72, 71, 50, 77, 40, 59, 27, 64, 28, 38, 73, 17, 55, 12},
{13, 53, 39, 14, 56, 40, 60, 70, 77, 17, 19, 71, 0, 27, 73, 15, 28, 61, 76, 32, 7, 49, 43, 20, 38, 63, 47, 4, 48, 57, 37, 64, 6, 52, 54, 29, 78, 44, 8, 69, 41, 23, 31, 18, 26, 10, 24, 55, 59, 45, 25, 42, 22, 68, 34, 1, 12, 11, 21, 65, 35, 74, 36, 79, 2, 30, 46, 33, 3, 66, 51, 62, 75, 16, 58, 72, 67, 50, 5, 9},
{31, 72, 24, 6, 28, 60, 27, 77, 51, 41, 26, 75, 3, 48, 55, 59, 36, 32, 45, 65, 15, 9, 63, 54, 57, 52, 35, 18, 46, 22, 62, 11, 17, 58, 76, 16, 37, 25, 12, 38, 66, 61, 64, 8, 7, 2, 4, 49, 53, 56, 34, 13, 0, 44, 43, 14, 39, 74, 33, 70, 68, 73, 19, 78, 30, 50, 5, 21, 67, 47, 79, 10, 69, 42, 20, 40, 29, 1, 23, 71},
{75, 60, 3, 35, 42, 25, 4, 72, 32, 26, 0, 1, 38, 24, 13, 18, 73, 54, 45, 14, 59, 65, 44, 41, 78, 23, 11, 16, 6, 48, 36, 57, 31, 74, 49, 66, 50, 61, 30, 22, 67, 8, 79, 9, 40, 58, 10, 52, 47, 5, 12, 55, 76, 46, 19, 28, 2, 27, 7, 56, 33, 53, 63, 34, 69, 62, 71, 43, 17, 68, 29, 77, 51, 70, 15, 64, 39, 37, 21, 20},
{3, 32, 73, 64, 79, 27, 67, 26, 15, 69, 55, 51, 20, 41, 65, 8, 4, 21, 58, 28, 0, 45, 13, 44, 72, 60, 34, 30, 39, 57, 52, 62, 33, 6, 66, 25, 10, 53, 14, 75, 70, 22, 43, 35, 68, 61, 59, 47, 40, 16, 74, 76, 37, 38, 24, 31, 11, 9, 18, 71, 2, 49, 54, 36, 29, 12, 56, 1, 46, 5, 78, 63, 48, 23, 77, 19, 50, 7, 17, 42},
{29, 30, 15, 28, 5, 59, 66, 18, 60, 52, 74, 41, 57, 37, 26, 39, 12, 51, 45, 77, 16, 22, 35, 0, 3, 14, 42, 6, 13, 21, 38, 64, 24, 62, 65, 78, 61, 11, 20, 71, 67, 2, 56, 33, 44, 50, 23, 68, 48, 10, 8, 76, 4, 43, 36, 79, 27, 75, 72, 58, 9, 1, 69, 17, 46, 31, 73, 55, 70, 47, 49, 53, 34, 7, 54, 40, 25, 19, 63, 32},
{14, 41, 63, 8, 72, 16, 32, 70, 29, 0, 60, 30, 37, 61, 58, 50, 3, 13, 45, 78, 54, 64, 19, 69, 40, 23, 73, 12, 76, 24, 7, 4, 11, 59, 36, 65, 38, 18, 53, 2, 57, 10, 20, 68, 51, 31, 34, 44, 27, 43, 79, 6, 17, 5, 42, 66, 9, 35, 55, 21, 22, 47, 49, 75, 15, 48, 46, 26, 33, 74, 67, 62, 71, 77, 1, 25, 56, 39, 52, 28},
{8, 13, 2, 15, 44, 49, 55, 43, 45, 39, 4, 66, 22, 0, 12, 17, 36, 67, 5, 3, 53, 51, 23, 76, 70, 16, 40, 75, 9, 29, 74, 24, 57, 64, 62, 26, 33, 50, 35, 27, 32, 31, 56, 59, 54, 52, 73, 60, 65, 19, 42, 58, 71, 61, 78, 28, 38, 18, 46, 6, 47, 21, 20, 14, 34, 37, 41, 77, 48, 10, 68, 69, 1, 72, 7, 79, 25, 30, 11, 63},
{41, 71, 54, 14, 76, 28, 67, 16, 26, 39, 64, 22, 4, 36, 69, 66, 79, 30, 19, 8, 68, 20, 73, 61, 33, 65, 24, 60, 34, 38, 9, 43, 78, 72, 63, 51, 0, 49, 35, 27, 59, 15, 32, 58, 46, 37, 2, 57, 10, 18, 25, 17, 48, 52, 23, 75, 74, 45, 31, 44, 11, 42, 29, 3, 50, 40, 5, 55, 70, 12, 47, 56, 7, 21, 77, 53, 62, 6, 1, 13},
{68, 45, 77, 18, 16, 25, 40, 67, 69, 29, 19, 66, 54, 2, 34, 60, 48, 79, 72, 63, 59, 74, 73, 10, 30, 31, 32, 62, 27, 36, 15, 3, 7, 55, 46, 12, 65, 28, 75, 26, 64, 41, 53, 78, 50, 24, 71, 58, 23, 13, 37, 49, 21, 5, 22, 76, 44, 52, 8, 42, 0, 51, 6, 70, 17, 56, 14, 11, 61, 33, 20, 35, 38, 4, 1, 47, 57, 39, 9, 43},
{34, 41, 59, 38, 63, 23, 7, 31, 71, 28, 32, 14, 56, 10, 37, 66, 48, 74, 16, 47, 60, 19, 40, 61, 43, 62, 5, 15, 25, 36, 49, 76, 58, 64, 67, 3, 35, 21, 77, 12, 18, 20, 69, 4, 1, 70, 0, 65, 72, 6, 13, 45, 27, 78, 75, 8, 22, 52, 57, 50, 30, 29, 42, 79, 68, 51, 39, 9, 73, 53, 2, 46, 24, 17, 44, 11, 55, 54, 33, 26},
{43, 16, 68, 41, 79, 40, 5, 14, 42, 58, 23, 8, 26, 17, 3, 29, 18, 44, 7, 67, 49, 12, 20, 64, 65, 60, 24, 46, 35, 45, 53, 0, 52, 54, 72, 61, 32, 11, 63, 22, 66, 13, 36, 33, 39, 51, 10, 47, 6, 69, 27, 2, 50, 75, 59, 28, 70, 1, 78, 9, 62, 71, 30, 74, 38, 55, 31, 48, 19, 77, 56, 15, 76, 34, 25, 4, 73, 57, 21, 37},
{62, 65, 29, 48, 17, 72, 40, 53, 49, 28, 37, 23, 78, 77, 27, 11, 13, 68, 63, 24, 38, 10, 2, 3, 4, 45, 60, 7, 57, 73, 19, 34, 22, 39, 35, 50, 51, 15, 66, 26, 52, 71, 54, 67, 56, 44, 74, 21, 14, 0, 18, 30, 43, 33, 25, 31, 9, 46, 79, 32, 75, 41, 5, 8, 12, 59, 47, 76, 1, 42, 6, 20, 61, 16, 36, 58, 64, 69, 70, 55},
{41, 61, 43, 69, 18, 57, 17, 11, 10, 24, 7, 77, 12, 55, 66, 60, 38, 4, 50, 73, 46, 28, 58, 76, 63, 64, 37, 56, 59, 68, 45, 2, 15, 65, 40, 31, 35, 20, 52, 6, 51, 49, 54, 72, 34, 32, 42, 22, 30, 44, 14, 19, 48, 39, 70, 67, 27, 26, 21, 29, 3, 75, 79, 78, 33, 5, 0, 62, 47, 25, 16, 74, 13, 36, 71, 23, 53, 1, 8, 9},
{23, 78, 2, 62, 40, 43, 16, 44, 15, 61, 70, 53, 36, 42, 46, 34, 0, 33, 47, 6, 31, 63, 50, 35, 79, 66, 3, 38, 72, 60, 45, 57, 30, 7, 29, 51, 11, 75, 25, 27, 77, 4, 18, 26, 19, 54, 73, 20, 59, 69, 39, 41, 17, 5, 58, 71, 74, 64, 10, 49, 28, 21, 22, 13, 67, 55, 52, 8, 65, 48, 68, 56, 24, 1, 12, 14, 76, 37, 32, 9},
{37, 70, 34, 73, 1, 5, 2, 66, 24, 33, 60, 43, 17, 57, 22, 76, 44, 32, 9, 59, 62, 7, 54, 46, 68, 65, 0, 12, 23, 78, 18, 27, 6, 41, 40, 20, 64, 16, 77, 3, 53, 35, 15, 38, 74, 28, 69, 4, 42, 10, 49, 13, 36, 39, 11, 71, 56, 26, 61, 19, 14, 55, 72, 67, 52, 21, 45, 47, 30, 58, 29, 50, 51, 48, 79, 25, 63, 31, 8, 75},
{46, 62, 4, 25, 73, 20, 60, 67, 74, 12, 0, 52, 37, 40, 32, 18, 27, 58, 9, 69, 65, 54, 64, 49, 16, 21, 72, 34, 29, 8, 39, 5, 78, 28, 77, 55, 44, 1, 57, 66, 38, 14, 33, 10, 19, 43, 79, 51, 26, 70, 56, 53, 76, 75, 23, 31, 71, 7, 68, 45, 63, 30, 6, 15, 13, 36, 24, 61, 50, 42, 17, 41, 2, 11, 59, 47, 35, 22, 48, 3},
{28, 26, 38, 47, 52, 74, 64, 65, 3, 69, 49, 39, 70, 21, 68, 2, 56, 36, 46, 9, 48, 1, 45, 60, 10, 8, 32, 43, 42, 40, 53, 30, 34, 14, 24, 57, 33, 4, 16, 20, 58, 35, 17, 27, 6, 63, 51, 11, 54, 61, 7, 78, 29, 37, 22, 5, 71, 77, 0, 73, 18, 19, 31, 72, 79, 15, 13, 25, 50, 44, 75, 62, 12, 55, 41, 76, 66, 59, 67, 23},
{59, 62, 12, 20, 11, 6, 41, 44, 13, 74, 54, 31, 73, 79, 10, 8, 0, 16, 52, 68, 48, 14, 43, 30, 3, 9, 33, 39, 58, 65, 66, 76, 49, 60, 56, 1, 70, 72, 27, 78, 34, 4, 24, 36, 61, 29, 7, 55, 77, 2, 21, 69, 23, 42, 25, 47, 50, 40, 35, 22, 37, 15, 28, 19, 71, 75, 18, 46, 53, 63, 5, 26, 32, 67, 57, 38, 51, 45, 17, 64},
{43, 15, 48, 20, 9, 30, 8, 23, 70, 36, 76, 35, 50, 58, 39, 7, 73, 55, 56, 3, 62, 32, 5, 59, 21, 0, 45, 57, 61, 16, 79, 65, 77, 13, 67, 12, 17, 4, 10, 31, 40, 2, 14, 47, 51, 18, 26, 64, 71, 41, 25, 53, 19, 44, 72, 49, 22, 69, 37, 52, 54, 34, 66, 75, 24, 78, 63, 11, 42, 74, 46, 38, 6, 29, 28, 1, 33, 60, 68, 27},
{41, 43, 53, 75, 3, 40, 61, 51, 23, 20, 52, 54, 10, 18, 37, 30, 35, 74, 21, 59, 69, 12, 11, 32, 64, 72, 36, 57, 68, 56, 7, 71, 4, 25, 0, 66, 39, 1, 63, 48, 45, 49, 67, 78, 79, 28, 70, 24, 9, 14, 42, 16, 44, 6, 2, 31, 13, 15, 38, 33, 76, 58, 62, 77, 27, 55, 17, 50, 47, 46, 65, 26, 8, 29, 5, 73, 60, 19, 34, 22},
{25, 56, 26, 35, 49, 17, 32, 19, 6, 8, 7, 34, 10, 13, 69, 75, 38, 64, 29, 37, 28, 27, 5, 78, 65, 57, 72, 3, 16, 63, 67, 62, 77, 11, 44, 40, 53, 76, 15, 2, 58, 36, 12, 71, 41, 31, 18, 1, 70, 54, 20, 45, 51, 23, 61, 30, 14, 9, 66, 48, 55, 24, 43, 4, 50, 79, 74, 22, 42, 73, 21, 47, 46, 33, 52, 60, 59, 68, 39, 0},
{5, 77, 31, 3, 65, 61, 21, 52, 78, 19, 18, 45, 35, 34, 46, 33, 54, 13, 17, 41, 38, 37, 2, 55, 50, 79, 26, 6, 16, 40, 44, 4, 64, 12, 51, 58, 69, 15, 0, 66, 73, 1, 43, 8, 49, 47, 20, 32, 29, 72, 71, 59, 30, 39, 28, 74, 7, 23, 56, 57, 67, 62, 42, 60, 22, 10, 75, 25, 76, 9, 70, 24, 36, 68, 53, 27, 48, 63, 11, 14},
{40, 74, 58, 43, 16, 73, 67, 54, 21, 27, 0, 39, 77, 69, 9, 2, 25, 56, 44, 65, 66, 37, 34, 13, 64, 78, 22, 14, 36, 24, 3, 35, 51, 76, 28, 4, 42, 1, 18, 33, 8, 59, 53, 63, 60, 61, 45, 31, 26, 48, 41, 70, 15, 49, 32, 68, 75, 12, 38, 55, 29, 5, 11, 7, 62, 46, 79, 71, 50, 57, 6, 10, 30, 72, 52, 23, 20, 17, 19, 47},
{20, 77, 49, 52, 38, 17, 5, 31, 45, 61, 72, 9, 36, 66, 48, 10, 56, 32, 28, 63, 0, 60, 62, 75, 51, 35, 19, 76, 14, 6, 55, 65, 34, 71, 30, 78, 27, 50, 70, 43, 79, 46, 53, 24, 11, 59, 67, 3, 44, 23, 58, 69, 40, 1, 15, 16, 18, 22, 33, 41, 13, 54, 37, 68, 2, 12, 21, 8, 25, 73, 39, 26, 7, 29, 47, 64, 4, 42, 74, 57},
{26, 60, 22, 36, 10, 39, 78, 29, 43, 8, 55, 2, 74, 31, 5, 59, 65, 32, 12, 37, 4, 28, 69, 45, 48, 75, 7, 17, 21, 44, 16, 79, 18, 1, 56, 77, 47, 61, 64, 35, 34, 66, 6, 62, 51, 19, 40, 38, 11, 23, 53, 67, 50, 30, 3, 49, 68, 20, 54, 0, 24, 73, 14, 13, 42, 41, 15, 33, 71, 57, 52, 76, 72, 46, 9, 58, 25, 27, 70, 63},
{29, 68, 67, 1, 23, 36, 37, 5, 77, 18, 13, 61, 26, 66, 42, 9, 79, 0, 15, 30, 62, 25, 14, 16, 57, 35, 31, 17, 43, 73, 76, 44, 72, 56, 58, 10, 78, 20, 49, 40, 39, 7, 2, 12, 6, 46, 47, 54, 34, 41, 38, 22, 24, 45, 65, 74, 60, 51, 21, 11, 48, 32, 59, 53, 8, 70, 71, 3, 27, 64, 69, 28, 19, 50, 55, 63, 4, 33, 52, 75},
{36, 68, 25, 66, 46, 64, 19, 54, 5, 56, 76, 21, 65, 44, 33, 62, 69, 73, 79, 10, 35, 1, 34, 52, 53, 63, 6, 67, 43, 45, 4, 15, 8, 71, 3, 14, 48, 59, 47, 23, 13, 49, 7, 31, 0, 72, 30, 78, 9, 57, 27, 29, 58, 16, 22, 24, 74, 42, 75, 11, 2, 39, 55, 32, 12, 70, 41, 40, 51, 20, 26, 77, 17, 38, 61, 37, 60, 28, 18, 50},
{44, 54, 65, 46, 18, 53, 61, 72, 14, 71, 55, 64, 77, 32, 22, 2, 6, 73, 40, 34, 50, 69, 17, 19, 13, 33, 66, 7, 0, 68, 63, 23, 47, 8, 41, 57, 58, 9, 30, 36, 48, 39, 45, 25, 60, 31, 10, 4, 37, 75, 42, 52, 11, 12, 1, 15, 3, 70, 67, 38, 29, 27, 20, 5, 43, 24, 74, 26, 62, 28, 59, 49, 51, 78, 79, 21, 56, 35, 16, 76},
{17, 40, 19, 72, 49, 31, 62, 51, 5, 28, 11, 16, 44, 75, 57, 46, 70, 18, 71, 74, 69, 24, 61, 77, 21, 23, 76, 8, 59, 3, 33, 43, 67, 65, 58, 60, 37, 13, 25, 48, 29, 64, 9, 47, 7, 79, 10, 53, 1, 15, 54, 26, 14, 4, 32, 36, 0, 41, 52, 73, 2, 27, 22, 12, 45, 30, 63, 6, 34, 39, 42, 20, 68, 50, 55, 78, 66, 38, 35, 56},
{56, 55, 74, 71, 27, 18, 11, 0, 30, 76, 8, 6, 23, 50, 61, 5, 17, 54, 4, 46, 25, 67, 42, 7, 63, 22, 59, 3, 47, 60, 21, 72, 75, 79, 28, 1, 68, 69, 14, 36, 10, 20, 43, 45, 26, 32, 49, 78, 64, 15, 52, 37, 77, 35, 62, 29, 70, 24, 53, 16, 51, 33, 48, 19, 58, 2, 44, 38, 40, 65, 13, 41, 66, 9, 12, 73, 39, 31, 34, 57},
{75, 39, 16, 66, 57, 59, 52, 10, 37, 11, 78, 36, 43, 68, 62, 70, 58, 72, 74, 31, 49, 21, 9, 63, 22, 18, 15, 50, 45, 26, 79, 55, 6, 0, 29, 54, 2, 17, 40, 23, 71, 24, 1, 69, 28, 56, 53, 44, 13, 67, 46, 35, 33, 20, 77, 7, 3, 14, 61, 27, 34, 5, 42, 4, 51, 65, 32, 19, 41, 64, 38, 30, 73, 47, 12, 48, 25, 76, 60, 8},
{62, 1, 65, 73, 29, 41, 32, 35, 69, 58, 11, 53, 74, 75, 63, 44, 68, 77, 60, 42, 50, 25, 61, 47, 14, 10, 27, 24, 0, 57, 20, 18, 51, 64, 22, 67, 40, 3, 79, 59, 8, 19, 23, 17, 37, 12, 43, 5, 33, 16, 39, 31, 13, 4, 6, 15, 76, 55, 71, 72, 7, 49, 34, 38, 52, 66, 46, 9, 56, 30, 70, 54, 45, 28, 78, 36, 48, 2, 21, 26},
{67, 2, 63, 49, 8, 78, 20, 9, 30, 28, 53, 7, 21, 34, 6, 12, 26, 40, 42, 3, 27, 47, 50, 38, 23, 32, 59, 29, 46, 60, 37, 51, 13, 75, 22, 69, 43, 54, 11, 68, 74, 5, 65, 10, 48, 14, 61, 36, 64, 77, 1, 31, 44, 16, 0, 58, 24, 41, 55, 19, 71, 33, 18, 25, 72, 45, 57, 73, 76, 62, 70, 17, 52, 35, 79, 39, 56, 15, 66, 4},
{56, 2, 32, 69, 75, 77, 58, 64, 27, 5, 7, 28, 65, 22, 42, 62, 15, 71, 53, 50, 44, 54, 40, 20, 37, 34, 72, 14, 79, 30, 25, 67, 66, 51, 78, 6, 52, 38, 43, 21, 1, 3, 45, 46, 48, 63, 8, 59, 19, 10, 4, 49, 33, 61, 39, 70, 11, 57, 24, 18, 29, 9, 23, 47, 76, 12, 17, 13, 36, 41, 35, 55, 0, 31, 68, 73, 16, 60, 74, 26},
{27, 14, 47, 21, 35, 78, 40, 34, 16, 29, 8, 12, 13, 59, 25, 50, 66, 52, 43, 58, 32, 65, 63, 57, 55, 79, 41, 54, 49, 9, 3, 68, 62, 74, 61, 48, 7, 4, 22, 19, 15, 28, 24, 23, 73, 11, 44, 64, 67, 46, 71, 37, 77, 10, 30, 51, 72, 1, 31, 38, 70, 17, 33, 56, 75, 5, 18, 39, 69, 42, 6, 0, 53, 45, 2, 36, 60, 76, 26, 20},
{46, 29, 67, 10, 66, 41, 68, 12, 40, 24, 69, 50, 56, 38, 57, 6, 25, 14, 18, 39, 9, 52, 49, 61, 20, 51, 36, 77, 7, 26, 43, 60, 37, 35, 30, 74, 16, 59, 32, 4, 3, 5, 42, 0, 34, 71, 27, 55, 48, 54, 76, 78, 73, 44, 58, 31, 62, 65, 72, 2, 23, 28, 21, 8, 19, 17, 53, 79, 33, 47, 64, 11, 22, 70, 45, 13, 1, 63, 75, 15},
{60, 57, 48, 70, 59, 15, 25, 67, 35, 77, 0, 2, 20, 30, 6, 3, 64, 69, 76, 78, 14, 66, 32, 75, 49, 46, 29, 5, 22, 26, 73, 18, 63, 62, 13, 47, 21, 40, 51, 54, 9, 72, 24, 17, 28, 10, 8, 74, 11, 44, 33, 43, 58, 56, 39, 34, 68, 41, 16, 31, 50, 79, 45, 27, 55, 71, 37, 61, 42, 12, 65, 4, 38, 1, 23, 7, 19, 36, 53, 52},
{29, 25, 38, 52, 46, 19, 49, 16, 77, 45, 34, 20, 65, 26, 11, 17, 39, 18, 62, 72, 42, 4, 13, 48, 63, 32, 68, 40, 8, 35, 24, 14, 75, 51, 5, 12, 37, 7, 50, 66, 44, 47, 61, 79, 55, 41, 74, 22, 64, 69, 10, 9, 73, 23, 33, 21, 67, 2, 57, 28, 36, 30, 43, 53, 1, 58, 31, 27, 59, 56, 3, 76, 0, 71, 15, 60, 6, 78, 54, 70},
{60, 15, 32, 37, 27, 59, 68, 76, 72, 50, 63, 3, 77, 11, 24, 73, 58, 26, 61, 6, 70, 52, 4, 2, 79, 47, 42, 31, 14, 66, 49, 57, 19, 40, 78, 25, 45, 67, 9, 69, 21, 29, 39, 30, 12, 33, 75, 1, 62, 54, 16, 28, 55, 8, 0, 17, 43, 44, 36, 48, 53, 56, 5, 71, 22, 20, 10, 41, 65, 38, 51, 64, 23, 74, 13, 35, 34, 46, 18, 7},
{71, 45, 54, 37, 73, 63, 60, 57, 46, 7, 50, 16, 24, 13, 49, 72, 75, 55, 58, 74, 32, 67, 5, 70, 33, 22, 79, 2, 43, 23, 6, 53, 26, 66, 41, 20, 9, 4, 8, 56, 34, 12, 3, 48, 17, 11, 14, 18, 31, 69, 0, 44, 59, 61, 29, 40, 25, 68, 15, 62, 76, 36, 35, 52, 27, 64, 77, 21, 39, 30, 47, 42, 65, 51, 1, 38, 10, 28, 19, 78},
{27, 2, 25, 51, 34, 54, 17, 4, 1, 48, 59, 22, 14, 9, 18, 31, 13, 68, 66, 69, 74, 61, 76, 0, 28, 60, 32, 44, 67, 43, 57, 5, 36, 21, 47, 16, 37, 71, 24, 8, 7, 52, 53, 75, 29, 42, 46, 73, 19, 38, 3, 65, 12, 58, 45, 78, 77, 70, 64, 55, 33, 20, 79, 50, 30, 35, 6, 23, 40, 49, 10, 72, 63, 62, 26, 15, 41, 56, 11, 39},
{24, 36, 12, 3, 74, 42, 60, 14, 22, 2, 23, 71, 19, 79, 4, 45, 41, 63, 40, 56, 20, 0, 15, 54, 43, 29, 57, 18, 21, 51, 77, 33, 27, 6, 38, 73, 65, 70, 5, 55, 78, 8, 35, 69, 25, 7, 28, 76, 44, 11, 53, 39, 75, 48, 66, 10, 47, 62, 37, 17, 1, 46, 31, 52, 34, 61, 30, 49, 32, 58, 67, 26, 68, 13, 9, 72, 50, 64, 16, 59},
{34, 26, 54, 44, 46, 7, 8, 75, 2, 78, 70, 29, 11, 35, 10, 39, 32, 24, 20, 43, 15, 49, 65, 17, 31, 0, 45, 22, 3, 27, 18, 53, 55, 30, 42, 50, 16, 48, 4, 61, 40, 63, 47, 69, 33, 79, 66, 14, 73, 77, 37, 38, 28, 58, 57, 36, 51, 52, 59, 71, 6, 9, 41, 72, 56, 12, 23, 1, 25, 13, 19, 68, 60, 21, 74, 64, 67, 76, 5, 62},
{16, 51, 74, 12, 36, 2, 11, 56, 67, 76, 77, 13, 46, 69, 0, 68, 41, 32, 22, 26, 70, 24, 25, 52, 4, 28, 61, 78, 10, 72, 66, 33, 65, 31, 62, 37, 40, 39, 47, 75, 14, 44, 9, 79, 48, 57, 17, 53, 20, 73, 60, 19, 58, 8, 42, 27, 6, 5, 50, 23, 59, 45, 15, 3, 55, 35, 1, 71, 34, 64, 30, 21, 18, 63, 43, 54, 29, 7, 49, 38},
{22, 18, 78, 47, 14, 61, 55, 38, 54, 74, 24, 71, 67, 29, 52, 44, 7, 30, 35, 8, 13, 72, 17, 1, 49, 16, 15, 79, 50, 12, 25, 64, 73, 51, 59, 9, 76, 19, 46, 70, 39, 62, 53, 65, 68, 66, 56, 23, 36, 60, 63, 40, 27, 11, 33, 45, 43, 20, 34, 75, 37, 26, 41, 77, 5, 21, 48, 6, 3, 2, 58, 32, 4, 42, 28, 10, 31, 0, 57, 69},
{46, 78, 22, 0, 41, 26, 33, 20, 48, 28, 47, 11, 17, 53, 25, 69, 71, 24, 15, 55, 23, 67, 74, 10, 65, 79, 77, 72, 6, 75, 49, 64, 31, 5, 61, 13, 7, 3, 51, 16, 4, 44, 68, 1, 19, 30, 21, 70, 60, 18, 35, 54, 27, 56, 32, 50, 34, 62, 38, 12, 37, 52, 66, 63, 59, 39, 9, 8, 73, 40, 58, 42, 14, 29, 2, 36, 45, 76, 57, 43},
{51, 57, 39, 77, 74, 24, 37, 19, 52, 54, 5, 79, 64, 66, 65, 46, 73, 48, 58, 49, 47, 2, 12, 9, 14, 43, 59, 27, 36, 11, 22, 0, 55, 40, 26, 1, 75, 30, 42, 67, 63, 23, 25, 29, 21, 8, 61, 33, 72, 18, 20, 7, 44, 68, 16, 41, 13, 10, 3, 76, 71, 56, 32, 17, 78, 60, 28, 53, 50, 70, 45, 34, 6, 38, 35, 31, 15, 69, 62, 4},
{64, 71, 26, 51, 6, 28, 52, 38, 55, 35, 15, 53, 11, 69, 5, 68, 12, 46, 72, 30, 40, 49, 60, 77, 7, 8, 31, 25, 78, 29, 56, 65, 47, 75, 10, 22, 67, 66, 36, 1, 4, 70, 13, 17, 32, 39, 59, 3, 42, 63, 0, 43, 44, 61, 18, 62, 48, 79, 76, 9, 58, 73, 23, 20, 33, 54, 21, 14, 24, 34, 41, 19, 45, 74, 27, 37, 2, 16, 57, 50},
{17, 53, 2, 30, 66, 43, 56, 9, 15, 39, 68, 23, 24, 77, 38, 75, 78, 74, 79, 31, 35, 61, 3, 13, 33, 11, 59, 76, 21, 50, 4, 36, 16, 37, 58, 42, 14, 64, 6, 22, 18, 60, 27, 26, 40, 5, 65, 34, 70, 19, 29, 71, 44, 48, 10, 72, 0, 46, 41, 47, 69, 51, 1, 8, 62, 54, 20, 12, 7, 45, 49, 52, 67, 63, 28, 32, 55, 57, 73, 25},
{75, 43, 48, 1, 11, 46, 7, 53, 31, 71, 45, 37, 9, 14, 63, 17, 41, 44, 19, 15, 69, 38, 55, 33, 26, 10, 29, 25, 49, 42, 24, 23, 40, 27, 36, 60, 0, 58, 28, 72, 65, 35, 18, 34, 12, 30, 47, 62, 57, 39, 73, 50, 51, 3, 4, 56, 68, 66, 8, 79, 54, 59, 20, 5, 64, 74, 13, 61, 77, 6, 2, 67, 78, 16, 70, 32, 52, 76, 21, 22},
{13, 32, 45, 18, 57, 53, 63, 36, 69, 33, 2, 46, 0, 66, 25, 59, 73, 55, 44, 40, 56, 72, 74, 60, 62, 26, 6, 4, 16, 34, 14, 64, 50, 47, 24, 42, 70, 15, 28, 9, 37, 41, 52, 7, 30, 11, 39, 48, 79, 67, 43, 23, 10, 71, 76, 22, 61, 29, 58, 68, 65, 17, 1, 78, 51, 20, 12, 21, 77, 35, 38, 31, 27, 54, 49, 75, 8, 3, 5, 19},
{19, 37, 55, 11, 35, 48, 79, 57, 13, 66, 15, 41, 69, 29, 26, 2, 4, 33, 46, 38, 25, 56, 12, 21, 42, 74, 18, 77, 10, 16, 73, 53, 1, 43, 45, 67, 22, 63, 5, 62, 6, 50, 7, 8, 44, 65, 9, 71, 68, 47, 51, 14, 20, 28, 31, 72, 3, 60, 32, 61, 40, 30, 36, 39, 58, 49, 70, 78, 52, 24, 76, 64, 23, 59, 75, 34, 27, 54, 0, 17},
{69, 79, 22, 39, 37, 2, 12, 14, 23, 36, 70, 1, 76, 77, 46, 20, 54, 45, 16, 0, 58, 44, 8, 10, 65, 51, 3, 75, 35, 7, 30, 60, 32, 53, 49, 57, 56, 41, 52, 17, 74, 25, 24, 11, 50, 34, 15, 4, 5, 61, 18, 48, 66, 38, 71, 72, 28, 59, 6, 33, 13, 63, 55, 21, 62, 47, 26, 9, 40, 64, 78, 42, 27, 68, 73, 19, 29, 31, 67, 43},
{58, 3, 24, 68, 44, 66, 43, 76, 6, 64, 30, 31, 56, 13, 23, 35, 67, 1, 28, 16, 74, 37, 0, 33, 29, 53, 41, 54, 40, 63, 11, 50, 59, 25, 46, 79, 78, 55, 38, 42, 15, 72, 73, 14, 21, 4, 32, 12, 22, 60, 2, 52, 47, 69, 19, 61, 70, 71, 5, 65, 7, 10, 57, 39, 34, 9, 49, 45, 48, 75, 17, 51, 8, 62, 77, 36, 18, 26, 27, 20},
{34, 61, 15, 41, 51, 48, 42, 10, 30, 9, 39, 14, 76, 45, 20, 44, 25, 11, 6, 38, 36, 75, 57, 27, 55, 17, 12, 2, 16, 70, 40, 43, 46, 21, 50, 67, 78, 73, 32, 65, 1, 71, 13, 24, 5, 72, 68, 0, 7, 28, 66, 79, 74, 26, 69, 58, 52, 29, 8, 47, 18, 62, 22, 4, 59, 3, 63, 23, 64, 31, 37, 33, 35, 77, 49, 19, 56, 60, 53, 54},
{71, 61, 76, 21, 59, 35, 68, 53, 54, 52, 74, 38, 32, 66, 10, 55, 24, 50, 11, 40, 45, 17, 73, 44, 48, 0, 12, 79, 6, 27, 78, 1, 58, 9, 39, 42, 2, 75, 47, 19, 36, 46, 77, 37, 49, 14, 62, 67, 56, 28, 69, 70, 15, 3, 30, 5, 8, 22, 26, 7, 13, 51, 43, 65, 16, 33, 72, 25, 60, 57, 4, 63, 18, 20, 23, 31, 41, 34, 64, 29},
{30, 43, 56, 64, 73, 29, 50, 70, 66, 9, 24, 67, 25, 35, 46, 76, 14, 16, 65, 31, 47, 45, 15, 57, 5, 69, 44, 63, 19, 72, 34, 78, 6, 1, 33, 52, 68, 39, 11, 55, 48, 62, 53, 3, 2, 74, 22, 12, 21, 61, 7, 36, 20, 37, 8, 28, 27, 59, 49, 42, 10, 13, 38, 32, 75, 0, 18, 40, 17, 51, 54, 58, 23, 4, 79, 26, 77, 60, 71, 41},	
};
#elif NUM_FREELISTS == 1

#else
#error "NUM_FREELISTS number is not supported!"
#endif

#endif /* #if 0 */

#if 0
static int __r[NUM_FREELISTS][NUM_FREELISTS] __read_mostly;

static void generate_rand(void)
{
	int x, y, tmp;
	unsigned int i1, i2;

	for(x = 0; x < NUM_FREELISTS; x++){
		for(y = 0; y < NUM_FREELISTS; y++)
			__r[x][y] = y;

		for(y = 0; y < NUM_FREELISTS; y++){
			i1 = get_random_int() % NUM_FREELISTS;
			i2 = get_random_int() % NUM_FREELISTS;

      if(i1 != i2){
      	tmp =  __r[[x]i1];
        __r[x][i1] = __r[x][i2];
        __[x]r[i2] = tmp;
      }
		}
	}
}
#endif

/* 
 * NUMA node distance vector
 * 2D array of size NUMA nodes * NUMA nodes
 * (implemented as single dimension )
 * Each "row" corresponds to one node,
 * and the "columns" are node numbers sorted by
 * increasing distance to the row node
 */
static int *__NUMA_DV__;

/* Initialization function called once from reset_device_parameters (main.c) */
void init_numa_distance_vector(void)
{
	int nodes = num_online_nodes(), j, k, l;

	/* Create NUMA distance map per node */
	__NUMA_DV__ = (int *)vmalloc(nodes * nodes * sizeof(int));
	DMAP_BGON(__NUMA_DV__ == NULL);

	/* Initialize NUMA distance array based on increasing distance */
	for(j=0;j<nodes;j++){
		int temp;
		/* Initialize row with distances to sort */
		for(k=0;k<nodes;k++)
			__NUMA_DV__[j * nodes + k] = k;

		/* 
		 * Now sort based on increasing distance 
		 * Insertion sort is used because it is
		 * good with small arrays
		 */
		k = 1;
		while(k < nodes){
			l = k;
			while(l > 0 && 
				node_distance(j, __NUMA_DV__[j * nodes + l -1]) > 
				node_distance(j, __NUMA_DV__[j * nodes + l]))
			{
				temp = __NUMA_DV__[j * nodes + l - 1];
				__NUMA_DV__[j * nodes + l - 1] = __NUMA_DV__[j * nodes + l];
				__NUMA_DV__[j * nodes + l] = temp;
				l--;
			}
			k++;
		}
	}
}

void init_hash_table_free_pages(buffer_map_t *page_map, long num_free_pages)
{
	long i;
	struct tagged_page *tmp;
#if NUM_FREELISTS > 1
	int cpu, ncpus = NUM_FREELISTS;
	long num_pages_percpu;
#endif

	DMAP_BGON(page_map->pages != NULL);

	/* Allocate the array of struct tagged_page data structures. Use vmalloc to get a large, virtually contiguous array */
	page_map->pages = (struct tagged_page *)vmalloc(sizeof(struct tagged_page) * num_free_pages); 
	page_map->fl = (struct list_head *)vmalloc(ncpus * sizeof(struct list_head));
	page_map->fl_lock = (spinlock_t *)vmalloc(ncpus * sizeof(spinlock_t));

	DMAP_BGON(page_map->pages == NULL);
	DMAP_BGON(page_map->fl == NULL);
	DMAP_BGON(page_map->fl_lock == NULL);
	printk(KERN_ERR "Done with vmalloc...");

#if NUM_FREELISTS == 1
	INIT_LIST_HEAD(&page_map->fl);
	spin_lock_init(&page_map->fl_lock);
#else
	for(cpu = 0; cpu < ncpus; ++cpu){
		INIT_LIST_HEAD(&page_map->fl[cpu]);
		spin_lock_init(&page_map->fl_lock[cpu]);
	}
#endif

	printk(KERN_ERR "Done with INIT_LIST_HEAD...");

	page_map->total_num_pages = num_free_pages;

#if NUM_FREELISTS == 1
	for(i = 0; i < num_free_pages; ++i){
		tmp = &page_map->pages[i];
		init_tagged_page_meta_data(tmp);
		alloc_tagged_page_data(tmp);

		spin_lock(&page_map->fl_lock);
		list_add_tail(&tmp->free, &page_map->fl);
		spin_unlock(&page_map->fl_lock);
	}
#else
	DMAP_BGON(num_free_pages % ncpus != 0);
	num_pages_percpu = num_free_pages / ncpus;

	for(cpu = 0; cpu < NUM_FREELISTS; ++cpu){
		for(i = cpu * num_pages_percpu; i < ((cpu + 1) * num_pages_percpu); i++){
			tmp = &page_map->pages[i];
			init_tagged_page_meta_data(tmp);
			alloc_tagged_page_data(tmp, cpu);

			spin_lock(&page_map->fl_lock[cpu]);
			list_add_tail(&tmp->free, &page_map->fl[cpu]);
			spin_unlock(&page_map->fl_lock[cpu]);
		}
	}
#endif
}

void free_hash_table(buffer_map_t *page_map)
{
	struct tagged_page *tmp;
#if NUM_FREELISTS > 1
	int cpu;
#endif

	if(page_map == NULL){
		printk(KERN_ERR "Why is this hash table pointer NULL\n");
		return;
	}

#if NUM_FREELISTS == 1
	while(!list_empty_careful(&page_map->fl)){
		spin_lock(&page_map->fl_lock);
		tmp = container_of(page_map->fl.next, struct tagged_page, free);
		list_del_init(&tmp->free);
		spin_unlock(&page_map->fl_lock);

		free_tagged_page_data(tmp);
	}
#else
	for(cpu = 0; cpu < NUM_FREELISTS; ++cpu){
		while(!list_empty_careful(&page_map->fl[cpu])){
			spin_lock(&page_map->fl_lock[cpu]);
			tmp = container_of(page_map->fl[cpu].next, struct tagged_page, free);
			list_del_init(&tmp->free);
			spin_unlock(&page_map->fl_lock[cpu]);

			free_tagged_page_data(tmp);
		}
	}
	if(__NUMA_DV__ != NULL){
		vfree(__NUMA_DV__);
		__NUMA_DV__ = NULL;
	}
#endif
	vfree(page_map->pages);
}

struct tagged_page *alloc_page_lock(buffer_map_t *page_map, pgoff_t page_offset, struct pr_vma_data *pvd)
{
  struct tagged_page *tagged_page = NULL;
#if NUM_FREELISTS > 1
  int nodeid = numa_node_id();
  int nodes = num_online_nodes();
#endif
	int i;

  DMAP_BGON(pvd == NULL);
  DMAP_BGON((pvd->magic1 != PVD_MAGIC_1) || (pvd->magic2 != PVD_MAGIC_2));

#if NUM_FREELISTS == 1
	spin_lock(&page_map->fl_lock);
	tagged_page = list_first_entry_or_null(&page_map->fl, struct tagged_page, free);
	if(tagged_page != NULL){ /* we found a free page */
		list_del_init(&tagged_page->free);
		tagged_page->cpuid = 0;
	}
	spin_unlock(&page_map->fl_lock);
#else
	for(i = 0; i < nodes;i++){
		/* Start checking NUMA node CPUs based on increasing distance */
		const int node = __NUMA_DV__[nodeid * nodes + i];
		int cpu;
		for_each_cpu(cpu, cpumask_of_node(node)){
			spin_lock(&page_map->fl_lock[cpu]);
			tagged_page = list_first_entry_or_null(&page_map->fl[cpu], struct tagged_page, free);
			if(tagged_page != NULL){ /* free page found */
				list_del_init(&tagged_page->free);
				tagged_page->cpuid = cpu;
			}
			spin_unlock(&page_map->fl_lock[cpu]);

			if(tagged_page != NULL)
				break;
		}
	}
#endif

	if(tagged_page == NULL) /* failed here */
		return NULL;

	//DMAP_BGON(PageLocked(tagged_page->page));
	DMAP_BGON(locked_tp(tagged_page));

	atomic_set(&tagged_page->page_valid, 0);
  atomic_set(&tagged_page->buffer_id, BI_NONE);
	INIT_LIST_HEAD(&tagged_page->qlist);
  tagged_page->page->index = page_offset;
  tagged_page->pvd = pvd;
  atomic_set(&tagged_page->is_dirty, 0);
  tagged_page->priority = 0;

	//DMAP_BGON(PageLocked(tagged_page->page));
	DMAP_BGON(locked_tp(tagged_page));

	for(i = 0; i < MAX_RMAPS_PER_PAGE; i++){
		pvr_mk_invalid(&tagged_page->rmap[i]);
		pvr_set_vaddr(&tagged_page->rmap[i], 0);
		pvr_set_vma(&tagged_page->rmap[i], NULL);
		INIT_LIST_HEAD(&tagged_page->rmap[i].vma_mapped);
		pvr_set_cpu(&tagged_page->rmap[i], 0);
		pvr_set_idx(&tagged_page->rmap[i], i);
	}

	//DMAP_BGON(PageLocked(tagged_page->page));
	DMAP_BGON(locked_tp(tagged_page));

#ifdef USE_WAITQUEUE_FOR_COLLISIONS
	init_waitqueue_head(&tagged_page->waiters);
#endif

	spin_lock(&tagged_page->tp_lock_guard);
	atomic_set(&tagged_page->in_use, 1);
	spin_unlock(&tagged_page->tp_lock_guard);
	
	//DMAP_BGON(PageLocked(tagged_page->page));
	DMAP_BGON(locked_tp(tagged_page));

	return tagged_page;
}

void free_page_lock(buffer_map_t *page_map, struct tagged_page *tagged_page)
{
	int i;
#if NUM_FREELISTS > 1
	const unsigned int cpu = tagged_page->cpuid;
#endif

	DMAP_BGON(atomic_read(&tagged_page->in_use) == 0);
	DMAP_BGON(atomic_read(&tagged_page->buffer_id) != BI_NONE);
	DMAP_BGON(!locked_tp(tagged_page));
	//DMAP_BGON(PageLocked(tagged_page->page));
	
	spin_lock(&tagged_page->tp_lock_guard);
	atomic_set(&tagged_page->in_use, 0);
	spin_unlock(&tagged_page->tp_lock_guard);

  tagged_page->page->index = 0;
  tagged_page->pvd = NULL;
	atomic_set(&tagged_page->page_valid, 0);
  atomic_set(&tagged_page->buffer_id, BI_NONE);
	INIT_LIST_HEAD(&tagged_page->qlist);
  atomic_set(&tagged_page->is_dirty, 0);

  tagged_page->priority = 0;
	tagged_page->cpuid = 0;
	
	for(i = 0; i < MAX_RMAPS_PER_PAGE; i++){
		pvr_mk_invalid(&tagged_page->rmap[i]);
		pvr_set_vaddr(&tagged_page->rmap[i], 0);
		pvr_set_vma(&tagged_page->rmap[i], NULL);
		INIT_LIST_HEAD(&tagged_page->rmap[i].vma_mapped);
		pvr_set_cpu(&tagged_page->rmap[i], 0);
		pvr_set_idx(&tagged_page->rmap[i], i);
	}

	unlock_tp(tagged_page);

#if NUM_FREELISTS == 1
	spin_lock(&page_map->fl_lock);
	list_add_tail(&tagged_page->free, &page_map->fl);
	spin_unlock(&page_map->fl_lock);
#else
	spin_lock(&page_map->fl_lock[cpu]);
	list_add_tail(&tagged_page->free, &page_map->fl[cpu]);
	spin_unlock(&page_map->fl_lock[cpu]);
#endif
}
