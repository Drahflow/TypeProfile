#include <time.h>
#include <sys/time.h>
#include <iostream>

using namespace std;

int main(void) {
  timeval t;
  while(true) {
    gettimeofday(&t, NULL);
    cout << t.tv_sec << "." << t.tv_usec << endl;
  }
}
