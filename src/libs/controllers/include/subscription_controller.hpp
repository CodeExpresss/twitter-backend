#include <controller_header.hpp>

class SubscriptionController {
public:
    explicit SubscriptionController(std::shared_ptr<UnitOfWork> _worker): worker(_worker) {};
    ~SubscriptionController() = default;

    boost::property_tree::ptree get_queryset();

private:
    std::shared_ptr<UnitOfWork> worker;
};