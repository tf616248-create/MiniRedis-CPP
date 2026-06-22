#pragma once

#include <unordered_map>
#include <string>
#include <mutex>
#include <ctime>

struct Entry
{
	std::string value;
	std::time_t expirationTime;
};

class DataStore
{
private:
	std::unordered_map<std::string, Entry> data;
	std::mutex mutex;

public:
	void set(const std::string& key, const std::string& value);
	std::string get(const std::string& key);
	bool del(const std::string& key);
	void set(const std::string& key,
		const std::string& value,
		int ttlSeconds);
};