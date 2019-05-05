#include "utils.h"

using namespace std;
using namespace overground;


mutex sout::mx{};


string overground::operator << (ostream & lhs, ss::endtoken rhs)
{
  ostringstream oss;
  oss << lhs.rdbuf();
  return oss.str();
}
