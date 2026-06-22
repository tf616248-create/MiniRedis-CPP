#include "DataStore.h"

void DataStore::set(const std::string& key,
    const std::string& value)
{
    std::lock_guard<std::mutex> lock(mutex);
    Entry entry;
    entry.value = value;
    entry.expirationTime = 0;

    data[key] = entry;
}
void DataStore::set(
    const std::string& key,
    const std::string& value,
    int ttlSeconds)
{
    std::lock_guard<std::mutex> lock(mutex);

    Entry entry;

    entry.value = value;

    entry.expirationTime =
        std::time(nullptr) + ttlSeconds;

    data[key] = entry;
}

std::string DataStore::get(const std::string& key)
{
    std::lock_guard<std::mutex> lock(mutex);
    auto it = data.find(key);

    if (it == data.end())
    {
        return "NOT FOUND";
    }

    if (it->second.expirationTime != 0 &&
        std::time(nullptr) > it->second.expirationTime)
    {
        data.erase(it);

        return "NOT FOUND";
    }

    return it->second.value;
}

bool DataStore::del(const std::string& key)
{
    std::lock_guard<std::mutex> lock(mutex);
    return data.erase(key) > 0;
}