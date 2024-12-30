#ifndef RLASSETS_H
#define RLASSETS_H

// the goal here is to load assets and organise them by file extension
#include <string>
#include <unordered_map>

#include "rlMemory.h"

#ifndef ASSET_FILES
#define ASSET_FILES std::unordered_map<std::string, const char *>
#endif

class rlAssets {
    public:
        rlAssets() {}
        ~rlAssets() { unload(); } // clean up

        ASSET_FILES assets; // 112 bytes per entry before text
        rlMemory memory;

        void unload() {
            memory.free();
        }

        void load_assets() {
            for (auto it : assets) {
                memory.load(it.first, it.second);
            }
        }

        void *get(std::string name) {
            return memory.get(name);
        }

        ASSET_FILES get_all_by_extension(std::string extension) {
            std::unordered_map<std::string, const char *> out;
            for (auto &it : assets) {
                if (it.first.substr(it.first.find_last_of('.') + 1) == extension) {
                    out[it.first] = it.second;
                }
            }
            return out;
        }
};

#endif