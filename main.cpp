#include <iostream>
#include <vector>



namespace mkldnn {
  namespace memory{
    typedef std::vector<int> dims;
  }
}



 static std::string dims2str(const mkldnn::memory::dims& operand_dims) {
    std::string dstr = "";
    for (size_t i = 0; i < operand_dims.size(); ++i) {
      dstr += std::to_string(operand_dims[i]) + "-";
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

const  std::string key = GetHash( nchw_tz, axis, simple_output); 

/*
std::cout << key << std::endl;
*/

   return 0;
}
