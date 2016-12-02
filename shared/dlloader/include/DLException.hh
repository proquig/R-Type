#ifndef R_TYPE_DLEXCEPTION_HH_
#define R_TYPE_DLEXCEPTION_HH_

#include <exception>
#include <string>

class DLException : public std::exception
{
protected:
  std::string _message;
public:
  explicit DLException(std::string name, std::string error);
  virtual ~DLException() throw() = default;
  virtual const char *what() const throw();
};

#endif //R_TYPE_DLEXCEPTION_HH_