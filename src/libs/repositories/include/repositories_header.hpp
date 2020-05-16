#ifndef REPOSITORY_HEADER_HPP
#define REPOSITORY_HEADER_HPP

#include <memory>
#include <vector>
#include <string>
#include <boost/format.hpp>

#include "../../data_base/include/DBController.hpp"
#include "../../data_base/include/DBConnection.hpp"

enum err_code { OK, NO_CTRL, NOT_EXIST, DELETED, ALREADY_EXIST };

#endif // REPOSITORY_HEADER_HPP
