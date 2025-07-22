#ifndef _FLAGS
#define _FLAGS

/**
 * What does each bit do?
 * bit 0: set output name
 * bit 1: only output assembly
 * bit 2: set array size
 * bit 3: set cell size
 * bit 4: enable some optimizations 
 * bit 5: help 
 * bit 6: unused
 * bit 7: unrecognized flag 
 */
#define SET_OUTPUT 0x01
#define COMPILE_ONLY 0x02
#define SET_ARRAY_SIZE 0x04
#define SET_CELL_SIZE 0x08
#define ENABLE_OPTIMIZATIONS 0x10
#define PRINT_HELP 0x20
#define SET_OFFSET 0x40
#define FLAG_UNKNOWN 0x80

#endif