#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

class LibraryException : public std::runtime_error {
public:
  explicit LibraryException(const std::string &msg) : std::runtime_error(msg) {}
};

class InvalidMemberIDException : public LibraryException {
public:
  explicit InvalidMemberIDException(const std::string &id)
      : LibraryException(" Invalid member-ID: " + id) {}
};

class BookNotAvailableException : public LibraryException {
public:
  explicit BookNotAvailableException(const std::string &id)
      : LibraryException(" Book not available (ID: " + id + ")") {}
};

class IssueLimitExceededException : public LibraryException {
public:
  explicit IssueLimitExceededException(size_t max)
      : LibraryException(" Maximum issue limit reached (" +
                         std::to_string(max) + " books)") {}
};

#endif
