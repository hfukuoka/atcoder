#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/rational.hpp>

namespace mp = boost::multiprecision;
// 任意長整数型
using Bint = mp::cpp_int;
// 仮数部が32桁(10進数)の浮動小数点数型
using Real32 = mp::number<mp::cpp_dec_float<32>>;
// 仮数部が1024桁(10進数)の浮動小数点数型
using Real1024 = mp::number<mp::cpp_dec_float<1024>>;
// ついでに有理数型
using Rat = boost::rational<Bint>;