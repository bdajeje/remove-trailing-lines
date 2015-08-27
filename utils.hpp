#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

namespace utils {

/*! List files recursively under direcotry
 *  \param dir_path - directory path to scan
 *  \param regexes  - filter files by regexes. If not given, do not filter at all.
 *  \returns a list of filepath
 */
std::vector<std::string> listFiles(std::string dir_path, const std::string& start_with, const std::string& end_with);

/*! Remove trailing lines from file
 *  \param file_path - file path to update
 *  \return true on success, false otherwise
 *  \note leave maximum one empty lines at the end of the file
 */
bool removeTrailingLines(const std::string& file_path);

namespace files {

/*! Create file
 *  \warning override existing file
 */
bool create( const std::string& filepath, const std::string& content );

/*! Read file */
bool read( const std::string& filepath, std::string& result );

} // namespace files

} // namespace utils

#endif // UTILS_HPP
