#include "Profile.h"

#include <iostream>
#include <termios.h>
#include <iostream>
#include <sys/time.h>
#include <time.h>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h>

using namespace std;

ostream &operator << (ostream &s, const Profile &profile) {
  s << "Delays: ";
  for(Profile::DelayList::const_iterator i = profile.delays.begin();
      i != profile.delays.end(); ++i) {
    s << *i << " ";
  }
  s << endl;
  return s;
}

Profile::Profile(const string &str) {
  istringstream numbers(str);
  string header;
  numbers >> header;
  if(header != "Delays:") {
    cerr << "header: " << header << endl;
    cerr << "line: " << str << endl;
    throw "Invalid format";
  }

  while(numbers.good()) {
    size_t usecs;
    numbers >> usecs;
    delays.push_back(usecs);
  }
}

static char TEXT[] = "Fritz jagt im komplett verwahrlosten Taxi quer durch Bayern.\n";

static void initterm(void) {
  struct termios term;
  if(tcgetattr(0, &term))
    throw "could not get terminal attributes";
  term.c_lflag &= ~ICANON;
  term.c_lflag &= ~ECHO;
  if(tcsetattr(fileno(stdin), TCSANOW, &term))
    throw "could not set terminal attributes";
}

static void resetterm(void) {
  struct termios term;
  if(tcgetattr(0, &term))
    throw "could not get terminal attributes";
  term.c_lflag |= ICANON;
  term.c_lflag |= ECHO;
  if(tcsetattr(fileno(stdin), TCSANOW, &term))
    throw "could not set terminal attributes";
}

void optainProfile(Profile &profile) {
  initterm();
  cout << "Please type (and press enter):" << endl;
  cout << TEXT << endl;

  timeval s, t;

  size_t pos = 0;
  while(pos < strlen(TEXT)) {
    char c;
    gettimeofday(&s, NULL);
    cin.get(c);
    gettimeofday(&t, NULL);

    if(c == TEXT[pos]) {
      ++pos;
      profile.addDelay(s, t);
      cout << c << flush;
    }
  }
  resetterm();
}
