#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

#include <QString>

namespace utils {

/*! List files recursively under direcotry
 *  \param dir_path   - directory path to scan
 *  \param start_with - filter file by start with
 *  \param end_with   - filter file by end with
 *  \param recursive  - enter folder?
 *  \param results    - (out) found filepaths
 */
void listFiles(const QString& dir_path, const QString& name_filter, bool recursive, QStringList& results);

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
