#include <iostream>
#include <thread>
using namespace std;
void umm_thread(){
    for(int i=0;i>-100;i--){
        cout<<"From t1: "<<i<<endl;
    }
}
int main(){
    thread t (umm_thread);
    for(int i =-;i<100;i++){
        cout<<"FROM MAIN : "<<i<<endl;
    }
    t.join();
    return 0;
}