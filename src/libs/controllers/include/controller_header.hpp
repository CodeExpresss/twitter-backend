#ifndef CONTROLLER_HEADER_HPP
#define CONTROLLER_HEADER_HPP

#include <utility>

#include "unit_of_work.hpp"
#include "serialize.hpp"

class AbstractController {
public:
    virtual boost::property_tree::ptree get_queryset() = 0;

protected:
    AbstractController(std::shared_ptr<UnitOfWork> _worker): worker(std::move(_worker)) {};
    std::shared_ptr<UnitOfWork> worker;
};

#endif
