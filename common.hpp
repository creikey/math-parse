#ifndef HPP_COMMON
#define HPP_COMMON

namespace cmn {

class pos {
public:
  int column;
  int line;
  pos() : column(0), line(0){};
  pos(int c, int l) : column(c), line(l){};
};
}

#endif
