#include <functional>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>

class ThreadPool {
private:
    std::atomic<bool> destruct;
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> queue;
    std::mutex queue_mutex;
    std::condition_variable condition;
public:
    explicit ThreadPool(size_t poolSize) : destruct(false) {
        for (size_t i = 0; i < poolSize; ++i) { // Создаем ppolSize потоков, каждый поток либо выполняет задачу, либо спит
            threads.emplace_back([this]() {
                        while (!destruct) {
                            std::unique_lock<std::mutex> lock(queue_mutex);
                            //Проснувшись поток проверяет, что в очереди есть задача
                            if (!queue.empty()) {
                                auto current_task = queue.front();
                                //извлекает ее из очереди и выполняет
                                queue.pop();
                                lock.unlock();
                                current_task();
                            } else { //Если задачи нет, поток засыпает ожидая оповещения
                                condition.wait(lock);
                            }
                        }
                    });
        }
    }

    ~ThreadPool() {
        destruct = true;
        condition.notify_all();
        for (auto &thread : threads) {
            thread.join();
        }
    }

    template <class Func, class... Args>
    auto exec(Func &&func, Args&&... args) -> std::future<typename std::result_of<Func(Args...)>::type> {
        using return_type = decltype(func(args...));
        auto current_task = std::make_shared<std::packaged_task<return_type()>>
            (std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            //Новая задача добавляется в очередь
            queue.emplace([current_task]() { (*current_task)(); });
        }
        //происходит оповещение спящих потоков
        condition.notify_one();
        return current_task->get_future();
    }
};
