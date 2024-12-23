#ifndef RLMEMORY_H
#define RLMEMORY_H

#include "stdio.h"
#include <unordered_map>
#include <string>
#include <utility>

#ifndef ASSET_FILES
#define ASSET_FILES std::unordered_map<std::string, const char *>
#endif

#define MEM_PAIR std::pair<void *, size_t>

enum MEM_ID {
    MEM_ID_UNKNOWN = 0,
    MEM_ID_TTF,
    MEM_ID_OTF,
    MEM_ID_PNG,
    MEM_ID_JPG,
    MEM_ID_SOUND,
    MEM_ID_MUSIC,
    
};

// A simple memory manager
// now using std::pair to store size of allocated blocks
// NOTE: This is a simple memory manager and should not be used for large allocations

class rlMemory {
    public:
        rlMemory() {}
        ~rlMemory() { free(); } // clean up on destructor

        bool alloc(std::string name, size_t size) {
            memory[name] = MEM_PAIR(malloc(size), size);
            return memory[name].first != NULL;
        }

        bool alloc(std::string name, size_t block_size, size_t block_count) {
            size_t total = block_size * block_count;
            memory[name] = MEM_PAIR(malloc(total), total);
            return memory[name].first != NULL;
        }

        void free(std::string name) {
            void *ptr = memory[name].first;
            if (ptr != NULL) {
                ::free(ptr);
                memory.erase(name);
            }
        }

        void free() {
            for (auto &it : memory) {
                ::free(it.second.first);
            }
            memory.clear();
        }

        void *get(std::string name) {
            return memory[name].first;
        }

        size_t size(std::string name) {
            return memory[name].second;
        }

        // should really go in a cpp file but keeping it header only for now
        size_t load(std::string name, const char *filepath) {
            size_t size = 0;
            FILE *file = fopen(filepath, "rb");
            if (file == NULL) {
                return size;
            }
            // file size
            fseek(file, 0, SEEK_END);
            size = ftell(file);
            fseek(file, 0, SEEK_SET);
            // alloc memory
            void *data = malloc(size);
            if (data == NULL) {
                fclose(file);
                return size;
            }
            // load data
            fread(data, 1, size, file);
            fclose(file);
            memory[name] = MEM_PAIR(data, size);
            return size;
        }

        void load_assets(ASSET_FILES files) {
            for (auto it : files) {
                load(it.first, it.second);
            }
        }
    
    std::unordered_map<std::string, MEM_PAIR> memory;
};

#endif