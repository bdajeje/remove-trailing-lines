#include "utils.hpp"

#include <dirent.h>
#include <fstream>

#include <boost/algorithm/string.hpp>

namespace utils {

std::vector<std::string> listFiles(std::string dir_path, const std::string& start_with, const std::string& end_with)
{
  std::vector<std::string> results;

  DIR* dir;
  if((dir = opendir(dir_path.c_str())) != nullptr)
  {
    if(dir_path.back() != '/')
      dir_path += '/';

    struct dirent* ent;
    while((ent = readdir(dir)) != nullptr)
    {
      std::string filename {ent->d_name};

      if(filename == "." || filename == "..")
        continue;

      if( boost::algorithm::starts_with(filename, start_with) &&
          boost::algorithm::ends_with(filename, end_with))
        results.push_back( dir_path + filename );
    }
    closedir(dir);
  }

  return results;
}

bool removeTrailingLines(const std::string& file_path)
{
  // Read file
  std::string content;
  if(!files::read(file_path, content))
    return false;

  // Split file content line by line
  std::vector<std::string> lines;
  boost::algorithm::split(lines, content, boost::is_any_of("\n"));

  // Find how many empty lines at the end of file
  size_t nbr_empty_lines {0};
  for( size_t i = lines.size(); i > 0; --i )
  {
    if(lines[i - 1].length() <= 1)
      nbr_empty_lines++;
    else
      break;
  }

  // Some extra lines? Update file
  if( nbr_empty_lines > 1 )
  {
    std::string new_content;
    for( size_t i = 0; i < lines.size() - nbr_empty_lines; ++i )
      new_content += lines[i] + '\n';
    files::create(file_path, new_content);
  }

  return true;
}

namespace files {

bool read( const std::string& filepath, std::string& result )
{
  std::ifstream file(filepath.c_str());
  if( !file.is_open() )
    return false;

  // Get length of file
  file.seekg(0, file.end);
  const int length = file.tellg();
  file.seekg(0, file.beg);

  // If file content is empty, exit
  if( length < 1 )
    return true;

  // Read the file
  result.resize( length );
  file.read(&result[0], length);

  // Close the file and return good read
  file.close();
  return true;
}

bool create( const std::string& filepath, const std::string& content )
{
  // Try to open the file
  std::ofstream new_file(filepath, std::ios::trunc);
  if( !new_file.is_open() )
    return false;

  // Write content into
  new_file << content;

  // Closing file
  new_file.close();

  return true;
}

} // namespace files

} // namespace utils
