#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

namespace std
{
	static void createFileWithContent(const std::string& content, const std::string& name, const std::string& path)
	{
		std::string pathAndName = path + "\\" + name;
		std::ofstream file(pathAndName);

		file << content;

		file.close();
	}

	static void createFileWithContent(const std::string& content, const std::string& name, const std::string& path, const std::string extension)
	{
		std::string newName = std::string(name) += extension;
		std::createFileWithContent(content, newName, path);
	}


	static bool isTherAnotherFilter(const std::string& word, const std::string& filter, int idx)
	{
		int filterCnt = 0;
		for (int i = idx; i < word.size(); i++)
		{
			if (word[i] == filter[filterCnt])
			{
				filterCnt++;
			}
			else
			{
				filterCnt = 0;
			}
			if (filterCnt == filter.size())
			{
				return true;
			}
		}
		return false;
	}

	static std::string splitStringTillLastWord(const std::string& word, const std::string& filter)
	{
		std::string str;
		int filterCnt = 0;
		for (int i = 0; i < word.size(); i++)
		{
			if (word[i] == filter[filterCnt])
			{
				filterCnt++;
			}
			else
			{
				filterCnt = 0;
			}
			if (filterCnt == filter.size() && !isTherAnotherFilter(word, filter, i))
			{

				for (int j = i + 2; j < word.size(); j++)
				{
					str += word[j];
				}

			}
		}
		return str;
	}

	static bool isFolder(std::string name)
	{
		for (const char c : name)
		{
			if (c == '.')
			{
				return false;
			}
		}
		return true;
	}

	static bool isStringValid(std::string str)
	{
		int cnt = 0;
		for (const char c : str)
		{
			if (c == '.' || c == '/' || c == '$')
			{
				cnt++;
			}
		}
		return !(cnt == str.size());
	}

	static vector<std::string> splitString(std::string s, std::string delimiter)
	{
		size_t pos_start = 0, pos_end, delim_len = delimiter.length();
		string token;
		vector<string> res;

		while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
			token = s.substr(pos_start, pos_end - pos_start);
			pos_start = pos_end + delim_len;
			res.push_back(token);
		}

		res.push_back(s.substr(pos_start));
		return res;
	}

	static std::string getFileExtension(const std::string& file)
	{
		for (int i = 0; i < file.size(); i++)
		{
			if (file[i] == '.')
			{
				bool isValid = true;
				std::string extension = "";
				for (int j = i + 1; j < file.size(); j++)
				{
					extension += file[j];
					if (file[j] == '.')
					{
						isValid = false;
						break;
					}
				}
				if (isValid)
				{
					return extension;
				}
			}
		}
		return "folder";
	}

	template<class T>
	static void removeAt(std::vector<T>& vec, int pos)
	{
		if (pos >= vec.size())
		{
			return;
		}
		vec.erase(vec.begin() + pos);
	}

	static void getFilePathWithExtensionInFolder(const std::filesystem::path& path, const std::string& extension, std::vector<std::string>& to)
	{
		for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path))
		{
			if (std::filesystem::is_directory(entry))
			{
				getFilePathWithExtensionInFolder(entry.path(), extension, to);
			}
			else
			{
				std::string file_extension = "." + getFileExtension(entry.path().filename().string());
				if (file_extension == extension)
				{
					to.push_back(entry.path().string());
				}
			}
		}
	}
}

