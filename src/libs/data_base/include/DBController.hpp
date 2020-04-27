#ifndef DBCONTROLLER_HPP
#define DBCONTROLLER_HPP

#include <memory>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <string>
#include <postgresql/libpq-fe.h>

#include "DBConnection.hpp"

using namespace std;

template <class Connection>
class DBController
{
public:
    static DBController<Connection>& instance() {}

    shared_ptr<Connection> get_free_connection();
    void reset_connection(shared_ptr<Connection>);

    bool run_query(string query, vector<string>& result);

private:
    explicit DBController<Connection>(int count);
    DBController(const DBController<Connection>&) = delete;
    DBController<Connection>& operator= (const DBController<Connection>&) = delete;
    
    void create_pool(int size);

    queue<shared_ptr<Connection>> connection_pool;
    mutex mtx;
    condition_variable cond;
};

#endif