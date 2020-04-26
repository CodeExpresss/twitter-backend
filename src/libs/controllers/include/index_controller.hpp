#include <controller_header.hpp>

class IndexController {
public:
    IndexController() = default;
    ~IndexController() = default;

    boost::property_tree::ptree get_queryset();
};