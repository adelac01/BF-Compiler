#ifndef _METADATA
#define _METADATA

#define DEFAULT_ARRAY_SIZE 30000
#define DEFAULT_CELL_SIZE 1
#define DEFAULT_OFFSET 0 
#define DEFAULT_OUTFILENAME "a.out"

struct metadata {
    unsigned int array_size;
    unsigned int cell_size;
    unsigned int starting_offset;
    unsigned int arch;
    std::string output_file;
    std::string input_file; 
};

#endif