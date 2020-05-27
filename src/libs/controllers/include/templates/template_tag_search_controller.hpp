#include "tag_search_controller.hpp"

template <class Serialize>
boost::property_tree::ptree TagSearchController<Serialize>::get_queryset(const std::string& tag) {
    err_code rc;
    return serialize(worker->find_by_tag(tag, rc));
}