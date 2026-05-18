// #include <iostream>
// #include <thread>
// #include <queue>
// #include <mutex>
// #include <condition_variable>
// #include <chrono>

// using namespace std;

// queue<int> buffer;

// const int MAX_SIZE = 5;

// mutex mtx;

// condition_variable cv_producer;
// condition_variable cv_consumer;

// void producer()
// {
//     int item = 1;

//     while (true)
//     {
//         unique_lock<mutex> lock(mtx);

//         // Wait if buffer is full
//         cv_producer.wait(lock, [] {
//             return buffer.size() < MAX_SIZE;
//         });

//         buffer.push(item);

//         cout << "Produced: " << item << endl;

//         item++;

//         // Notify consumer
//         cv_consumer.notify_one();

//         lock.unlock();

//         this_thread::sleep_for(chrono::milliseconds(500));
//     }
// }

// void consumer()
// {
//     while (true)
//     {
//         unique_lock<mutex> lock(mtx);

//         // Wait if buffer empty
//         cv_consumer.wait(lock, [] {
//             return !buffer.empty();
//         });

//         int item = buffer.front();
//         buffer.pop();

//         cout << "Consumed: " << item << endl;

//         // Notify producer
//         cv_producer.notify_one();

//         lock.unlock();

//         this_thread::sleep_for(chrono::milliseconds(1000));
//     }
// }

// int main()
// {
//     thread t1(producer);
//     thread t2(consumer);

//     t1.join();
//     t2.join();

//     return 0;
// }


#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex m1;
mutex m2;

void thread1()
{
    cout << "Thread1 trying to lock m1" << endl;

    m1.lock();

    cout << "Thread1 locked m1" << endl;

    this_thread::sleep_for(chrono::seconds(1));

    cout << "Thread1 trying to lock m2" << endl;

    m2.lock();

    cout << "Thread1 locked m2" << endl;

    m2.unlock();
    m1.unlock();
}

void thread2()
{
    cout << "Thread2 trying to lock m2" << endl;

    m2.lock();

    cout << "Thread2 locked m2" << endl;

    this_thread::sleep_for(chrono::seconds(1));

    cout << "Thread2 trying to lock m1" << endl;

    m1.lock();

    cout << "Thread2 locked m1" << endl;

    m1.unlock();
    m2.unlock();
}

int main()
{
    thread t1(thread1);
    thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}







//script --> read from json IP from both cient and server //iperf