/*
 * ================================
 * eli960@163.com
 * http://www.mailhonor.com/
 * 2016-09-05
 * ================================
 */

#include "zcc.h"

namespace zcc
{

class cdb_finder: public basic_finder
{
public:
    cdb_finder();
    ~cdb_finder();
    bool open(const char *_url);
    ssize_t find(const char *query, std::string &result, long timeout);
    void disconnect();
private:
    const char *___url;
    const char *___destination;
    const char *___prefix;
    const char *___suffix;
    cdb db;
};

cdb_finder::cdb_finder()
{
    ___url = 0;
}

cdb_finder::~cdb_finder()
{
    free(___url);
}

bool cdb_finder::open(const char *url)
{
    std::string dest;
    dict dt;
    if (!parse_url(url, dest, dt)) {
        return false;
    }
    if (dest.empty()) {
        return false;
    }

    if (!db.open(dest.c_str())) {
        return false;
    }

    stringsdup sdup;
    sdup.push_back(url);
    sdup.push_back(dest.c_str());
    sdup.push_back(dt.get_str("prefix", ""));
    sdup.push_back(dt.get_str("suffix", ""));

    ___url = sdup.dup();
    std::vector<size_t> &offsets = sdup.offsets();
    ___destination = ___url + offsets[1];
    ___prefix = ___url + offsets[2];
    ___suffix = ___url + offsets[3];
    return true;
}

ssize_t cdb_finder::find(const char *query, std::string &result, long timeout)
{
    char buf[1024 + 1];
    snprintf(buf, 1024, "%s%s%s", ___prefix, query, ___suffix);
    return db.find(buf, strlen(query), result);
}

void cdb_finder::disconnect()
{
}

basic_finder *cdb_finder_create()
{
    return new cdb_finder();
}

}
