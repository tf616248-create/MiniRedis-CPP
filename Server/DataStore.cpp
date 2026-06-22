#include "DataStore.h"

void DataStore::set(const std::string& key,
    const std::string& value)
{
    std::lock_guard<std::mutex> lock(mutex);
    data[key] = value;
}

std::string DataStore::get(const std::string& key)
{
    std::lock_guard<std::mutex> lock(mutex);
    auto it = data.find(key);

    if (it == data.end())
    {
        return "NOT FOUND";
    }

    return it->second;
}

bool DataStore::del(const std::string& key)
{
    std::lock_guard<std::mutex> lock(mutex);
    return data.erase(key) > 0;
}