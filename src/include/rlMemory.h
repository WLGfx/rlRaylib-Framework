#ifndef RLMEMORY_H
#define RLMEMORY_H

#include "stdio.h"
#include <unordered_map>
#include <string>

#ifndef ASSET_FILES
#define ASSET_FILES std::unordered_map<std::string, const char *>
#endif

// A simple memory manager

class rlMemory {
    public:
        rlMemory() {}
        ~rlMemory() {}

        bool alloc(std::string name, size_t size) {
            memory[name] = malloc(size);
            return memory[name] != NULL;
        }

        bool alloc(std::string name, size_t block_size, size_t block_count) {
            memory[name] = malloc(block_size * block_count);
            return memory[name] != NULL;
        }

        void free(std::string name) {
            void *ptr = memory[name];
            if (ptr != NULL) {
                ::free(ptr);
                memory.erase(name);
            }
        }

        void free() {
            for (auto &it : memory) {
                ::free(it.second);
            }
            memory.clear();
        }

        void *get(std::string name) {
            return memory[name];
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
            memory[name] = data;
            return size;
        }

        void load_assets(ASSET_FILES files) {
            for (auto it : files) {
                load(it.first, it.second);
            }
        }
    
    std::unordered_map<std::string, void *> memory;
};

#endif