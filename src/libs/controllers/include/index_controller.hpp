#include <controller_header.hpp>

template<class UnitOfWork>
class IndexController {
public:
    explicit IndexController(std::shared_ptr<UnitOfWork> _worker): worker(_worker) {};
    ~IndexController() = default;

    boost::property_tree::ptree get_queryset() {
        worker->get_index_tweet();
    };

private:
    std::shared_ptr<UnitOfWork> worker;
};
