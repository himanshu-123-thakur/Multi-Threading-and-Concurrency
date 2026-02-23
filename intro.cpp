//CODE
//Introduction to threads and concurrency

#include <iostream>
#include <thread>
using namespace std;
void intro (){ //THREAD (2)
    cout<<"Hello to the world of threading and concurrency"<<endl;
}
int main(){ //THREAD (1)
    thread t (intro);
    t.join(); //asks main to wait until intro thread is executed
}