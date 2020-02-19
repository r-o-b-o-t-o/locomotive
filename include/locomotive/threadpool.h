#ifndef LOCOMOTIVE_THREADPOOL_H
#define LOCOMOTIVE_THREADPOOL_H

#include "locomotive/locomotive.h"
#include <mutex>
#include <vector>
#include <future>
#include <deque>
#include <type_traits>

namespace Locomotive {

    class LOCOMOTIVE_API Threadpool {

        std::mutex m;
        std::condition_variable v;

        // Une queue qui contient toute les tache que vont executer les thread
        std::deque<std::packaged_task<void()> > work;

        // future qui represente les thread qui ont fini
        std::vector<std::future<void> > finished;


        // Boucle principale du thread, prend une task dans `work` et l'execute
        void threadTask() {
            while(true){
                std::packaged_task<void()> f;
                {
                    std::unique_lock<std::mutex> l(m);
                    if (work.empty()) {
                        v.wait(l,[&]{return !work.empty();});
                    }
                    f = std::move(work.front());
                    work.pop_front();
                }
                // si la task n'est pas valide on abort
                if (!f.valid()) return;
                // execution de la task
                f();
            }
        }

        public:

        // prend en parametre une lambda et retourne une future du type de retour de la lambda
        // les thread sont detacher donc pour attendre  execution d'une tache en mode bloquant
        // il suffit de faire un wait() sur la future retouner pour attendre la fin de la tache.
        // ex: auto f = Threadpool.queue( []{ return 1+1; } );
        // f.wait()
        template<class F, class R = std::result_of_t<F&()> >
        std::future<R> queue(F&& f) {
            // package la lambda dans une packaged_task avec le type de sortis de la lambda
            std::packaged_task<R()> p(std::forward<F>(f));

            auto r = p.get_future(); // on recupere la future avant de lui assigner la tache
            {
                std::unique_lock<std::mutex> l(m);
                work.emplace_back(std::move(p)); // on stock la task dans un tableau de task<void> pour qu elle soit executer par un thread
            }
            v.notify_one(); // reveil un thread pour effectuer la tache

            return r; // retourne la future (qui n'a pas forcement tout de suite le resultat de la tache)
        }

        // lance la threadpool avec 1 thread par defaut, ou le nombre passer en parametre
        void start(std::size_t N = 1) {
            for (std::size_t i = 0; i < N; ++i)
            {
                finished.push_back(
                    std::async(
                        std::launch::async,
                        [this]{ threadTask(); }
                    )
                );
            }
        }

        // stop tous les threads qui ne travaillent pas et notfie les threads qui travail d'arreter
        void abort() {
            cancelPending();
            finish();
        }

        // stop juste les threads qui ne travaillent pas.
        void cancelPending() {
            std::unique_lock<std::mutex> l(m);
            work.clear();
        }
        // empile une tache qui se resume a abort pour tous les thread pour les arreter.
        void finish() {
            {
                std::unique_lock<std::mutex> l(m);
                for(auto&& unused : finished){
                    work.push_back({});
                }
            }
            v.notify_all();
            finished.clear();
        }

        ~Threadpool() {
            finish();
        }
        
    };
}

#endif