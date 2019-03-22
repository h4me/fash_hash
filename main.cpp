#include <iostream>
#include <vector>
#include "fmt/format.h"


const char DIGITS[] =
    "0001020304050607080910111213141516171819"
    "2021222324252627282930313233343536373839"
    "4041424344454647484950515253545556575859"
    "6061626364656667686970717273747576777879"
    "8081828384858687888990919293949596979899";


namespace my {
/** Fast integer formatter. */
class format_int {
 private:
  
  // Buffer should be large enough to hold all digits (digits10 + 1),
  // a sign and a null character.
  enum { BUFFER_SIZE = std::numeric_limits<unsigned long long>::digits10 + 3 };
  mutable char buffer_[BUFFER_SIZE];
  char* str_;

  // Formats value in reverse and returns a pointer to the beginning.
  char* format_decimal(unsigned long long value) {
    char* ptr = buffer_ + (BUFFER_SIZE - 1);  // Parens to workaround MSVC bug.
    while (value >= 100) {
      // Integer division is slow so do it for a group of two digits instead
      // of for every digit. The idea comes from the talk by Alexandrescu
      // "Three Optimization Tips for C++". See speed-test for a comparison.
      unsigned index = static_cast<unsigned>((value % 100) * 2);
      value /= 100;
      *--ptr = DIGITS[index + 1];
      *--ptr = DIGITS[index];
    }
    if (value < 10) {
      *--ptr = static_cast<char>('0' + value);
      return ptr;
    }
    unsigned index = static_cast<unsigned>(value * 2);
    *--ptr = DIGITS[index + 1];
    *--ptr = DIGITS[index];
    return ptr;
  }

  void format_signed(long long value) {
    unsigned long long abs_value = static_cast<unsigned long long>(value);
    bool negative = value < 0;
    if (negative) abs_value = 0 - abs_value;
    str_ = format_decimal(abs_value);
    if (negative) *--str_ = '-';
  }

 public:
  explicit format_int(int value) { format_signed(value); }
  explicit format_int(long value) { format_signed(value); }
  explicit format_int(long long value) { format_signed(value); }
  explicit format_int(unsigned value) : str_(format_decimal(value)) {}
  explicit format_int(unsigned long value) : str_(format_decimal(value)) {}
  explicit format_int(unsigned long long value) : str_(format_decimal(value)) {}

  /** Returns the number of characters written to the output buffer. */
  std::size_t size() const {
    // return internal::to_unsigned(buffer_ - str_ + BUFFER_SIZE - 1);
    return buffer_ - str_ + BUFFER_SIZE - 1;
  }

  /**
    Returns a pointer to the output buffer content. No terminating null
    character is appended.
   */
  const char* data() const { return str_; }

  /**
    Returns a pointer to the output buffer content with terminating null
    character appended.
   */
  const char* c_str() const {
    buffer_[BUFFER_SIZE - 1] = '\0';
    return str_;
  }

  /**
    \rst
    Returns the content of the output buffer as an ``std::string``.
    \endrst
   */
  std::string str() const { return std::string(str_, size()); }
};

}


namespace mkldnn {
  namespace memory{
    typedef std::vector<int> dims;
  }
}



 static std::string dims2str(const mkldnn::memory::dims& operand_dims) {
    std::string dstr = "";
    for (size_t i = 0; i < operand_dims.size(); ++i) {
      dstr += std::to_string(operand_dims[i]) + "-";
    //  auto k = fmt::format_int(operand_dims[i]).c_str();
   //   dstr += my::format_int(operand_dims[i]).c_str() ;
    //  dstr += "-";
    }
    return dstr;
  }

 static std::string GetHash(std::vector<int>& shape,  // NOLINT
                             std::vector<int>& axis,   // NOLINT
                             const std::string& suffix) {
    return dims2str(shape) + dims2str(axis) + suffix;
  }






 







int main(int argc, char **argv) {

mkldnn::memory::dims nchw_tz = {3,4,5,2,3};
mkldnn::memory::dims axis = {3,4,4222,45};

std::string simple_output = "jaksjkasjsdl";
for(int i=0;i<1000;i++) {
    const  std::string key = GetHash( nchw_tz, axis, simple_output); 

//  std::cout << key << std::endl;
}

   return 0;
}
