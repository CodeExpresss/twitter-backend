#include <controller_header.hpp>

class TagsController {
public:
    explicit TagsController(std::shared_ptr<UnitOfWork> _worker): worker(_worker) {};
    ~TagsController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;
};