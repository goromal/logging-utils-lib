#pragma once

#include <string>
#include <experimental/filesystem>
#include <sys/stat.h>

namespace filesys
{

inline bool file_exists (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}


inline bool createDirIfNotExist(const std::string& dir)
{
  if(!std::experimental::filesystem::exists(dir))
      return std::experimental::filesystem::create_directory(dir);
  else
      return false;
}

inline std::vector<std::string> split(const std::string& s, const char* delimeter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimeter[0]))
   {
      tokens.push_back(token);
   }
   return tokens;
}

template <typename Iter>
inline std::string join(Iter begin, Iter end, std::string const& separator)
{
  std::ostringstream result;
  if (begin != end)
    result << *begin++;
  while (begin != end)
    result << separator << *begin++;
  return result.str();
}

inline std::string baseName(const std::string& path)
{
  std::string filename = split(path, "/").back();
  return split(filename, ".")[0];
}

inline std::string dirName(const std::string& path)
{
    std::vector<std::string> split_path = split(path, "/");
    split_path.pop_back();
    return join(split_path.begin(), split_path.end(), "/");
}

} // end namespace filesys
