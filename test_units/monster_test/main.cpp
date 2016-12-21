#ifdef RT_UNIX
#include <unistd.h>

#elif RT_WIN
#include <Windows.h>
#endif

#include <iostream>
#include <thread>

#include "IThreadPool.hh"
#include "ADLibrary.hh"

void sleep_and_end(IThreadPool *pool)
{
#ifdef RT_UNIX
    sleep(2);
#elif RT_WIN
    Sleep(2000);
#endif
    if (pool)
        pool->stop();
}

void splash(void)
{
    std::cout << "Splash" << std::endl;
}

int main(int ac, char **av)
{
    Dictionary dic;
    IThreadPool *pool;
#ifdef RT_UNIX
    IDLibrary *lib = ADLibrary::createLibrary(0, "monster", "./monster.so");
#elif RT_WIN
    IDLibrary *lib = ADLibrary::createLibrary(0, "monster", "monster.dll");
#endif
    if (lib->load())
    {
        std::cout << "Library load success" << std::endl;
        if ((dic = lib->getDictionary()) != NULL)
        {
            if (!dic->empty())
            {
                for (std::map<std::string, void *>::iterator sit = dic->begin(); sit != dic->end(); sit++)
                    std::cout << "key=" << sit->first.c_str() << std::endl;
                if ((pool = reinterpret_cast<IThreadPool *(*)(int)>(dic->at("instantiate"))(4)) != nullptr)
                {
                    std::cout << "Init=" << pool->init() << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    pool->addTask(pool->createTask(std::bind(splash)));
                    pool->addTask(pool->createTask(std::bind(sleep_and_end, pool)));
                    reinterpret_cast<void *(*)(IThreadPool *)>(dic->at("destroy"))(pool);
                }
            } else
                std::cout << "dic empty" << std::endl;
            delete dic;
        }
        lib->close();
    } else
        std::cout << "Library load failed" << std::endl;
    ADLibrary::deleteLibrary(lib);
}
