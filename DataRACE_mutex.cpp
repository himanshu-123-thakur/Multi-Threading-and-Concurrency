#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

//THIS CAUSES unstable shit as same resource for two thread 

// void umm_thread(){
//     for(int i=0;i>-100;i--){
//         cout<<"From t1: "<<i<<endl;
//     }
// }
// int main(){
//     thread t (umm_thread);
//     for(int i =1;i<100;i++){
//         cout<<"FROM MAIN : "<<i<<endl;
//     }
//     t.join();
//     return 0;
// }

//MUTEXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX ---> synchronise the access of the common resource --> inn this case cout

mutex mu;
void shared_print(string msg,int id){

    //mu.lock(); 


    ///LOCKING mutex wjhile printing --> other thread wont be able to print messaage
    //if exception then mutex is locked forever that is very very bad 
    //TO HANDLE THAT we dont directly use mutex lock

    lock_guard<mutex> guardd(mu);//HANDLE excpetion and forever locked USES RAII
    cout<< msg << id <<endl;
    //mu.unlock();

}

void umm_thread(){
    for(int i=0;i>-100;i--){
        // cout<<"From t1: "<<i<<endl;
        shared_print(string("FROM t1 : "),i);
    }
}
int main(){
    thread t (umm_thread);
    for(int i =0;i<100;i++){
        // cout<<"FROM MAIN : "<<i<<endl;
        shared_print(string("From MAIN : "),i);
    }
    t.join();
    return 0;
}