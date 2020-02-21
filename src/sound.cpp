#include "locomotive/sound.h"
#include "glm/vec3.hpp"
#include <iostream>

namespace Locomotive {
    Sound* Sound::instance = nullptr;

    Sound::Sound() :
            Sound(2) {
    }

    Sound::Sound(int nb_thread) {
        instance = this;
        this->engine = irrklang::createIrrKlangDevice();
        threadpool.start(nb_thread);
    }

    Sound::~Sound() {
        threadpool.finish();

        this->engine->stopAllSounds();
        
        this->engine->drop();
    }

    void Sound::playSound(const std::string& filename) {
        this->threadpool.queue([&engine = engine, filename] { engine->play2D(filename.c_str()); });
    }

    void Sound::playSound(const std::string& filename, bool repeat) {
        this->threadpool.queue([&engine = engine, filename, repeat]{engine->play2D(filename.c_str(), repeat);});
    }

    void Sound::playSound(const std::string& filename, glm::vec3 position) {
        irrklang::vec3df pos(position.x, position.y, position.z);
        this->threadpool.queue([&engine = engine, filename, &pos]{engine->play3D(filename.c_str(), pos);});
    }

    void Sound::playSound(const std::string& filename, glm::vec3 position, bool repeat) {
        irrklang::vec3df pos(position.x, position.y, position.z);
        this->threadpool.queue([&engine = engine, filename, &pos, repeat]{engine->play3D(filename.c_str(), pos, repeat);});
    }

    void Sound::updateListener(glm::vec3 position, glm::vec3 lookDirection) {
        this->engine->setListenerPosition(irrklang::vec3df(position.x, position.y, position.z),
                                  irrklang::vec3df(lookDirection.x, lookDirection.y, lookDirection.z));
 
    }
}