#ifndef DBCONTROLLER_HPP
#define DBCONTROLLER_HPP

#include <memory>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <postgresql/libpq-fe.h>

#include "DBConnection.hpp"

using namespace std;

class DBController
{
public:
    static DBController& instance();
    shared_ptr<DBConnection> get_free_connection();
    void reset_connection(shared_ptr<DBConnection>);

    bool run_query(string query, PGresult *res);

private:
    DBController(int count);
    DBController(const DBController&) = delete;
    DBController& operator= (const DBController&) = delete;
    
    void create_pool(int size);

    queue<shared_ptr<DBConnection>> connection_pool;
    mutex mtx;
    condition_variable cond;
};

#endif