#ifndef LOCOMOTIVE_SOUND_H
#define LOCOMOTIVE_SOUND_H

#include "locomotive/locomotive.h"
#include "locomotive/threadpool.h"
#include "irrKlang/irrKlang.h"

#include "glm/vec3.hpp"

namespace Locomotive {

    class LOCOMOTIVE_API Sound {
        public:
            Sound();
            Sound(int nb_thread);
            ~Sound();

            void playSound(const std::string& filename);
            void playSound(const std::string& filename, bool repeat);
            void playSound(const std::string& filename, glm::vec3 position);
            void playSound(const std::string& filename, glm::vec3 position, bool repeat);
            void updateListener(glm::vec3 position, glm::vec3 lookDirection);

        private:
            irrklang::ISoundEngine* engine;
            Threadpool threadpool;
            //std::vector<std::future<irrklang::ISound*> > sounds;
    };

}

#endif