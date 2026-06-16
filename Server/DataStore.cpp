#include "DataStore.h"

void DataStore::set(const std::string& key,
    const std::string& value)
{
    data[key] = value;
}

std::string DataStore::get(const std::string& key)
{
    auto it = data.find(key);

    if (it == data.end())
    {
        return "NOT FOUND";
    }

    return it->second;
}

bool DataStore::del(const std::string& key)
{
    return data.erase(key) > 0;
}