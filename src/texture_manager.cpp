#include "texture_manager.h"

void TMan::SetTexture(std::string key, const char *path) {
    texture_map[key] = LoadTexture(path);
}

void TMan::Walk() {
    for (const auto &entry : fs::recursive_directory_iterator(resources_path)) {
        if (!entry.is_directory()) {
        std::string key = entry.path().parent_path().filename().string() + "-" +
                            entry.path().stem().string();
        // filename() gives the last component of fs::path so we use stem()
        // instead .parent_path() gives full path resources\images\player so we
        //need to call .filename() on it to get "the last component"

        std::string path = fs::absolute(entry.path()).string();

        TMan::SetTexture(key, path.c_str());
        }
    }
}

void TMan::UnloadAll() {
    for (auto &pair : texture_map) {
        UnloadTexture(pair.second);
    }
}
