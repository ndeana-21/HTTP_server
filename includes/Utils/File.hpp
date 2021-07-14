#ifndef FILE_HPP
# define FILE_HPP

#include "Define.hpp"

extern Logger Log;
extern MimeTypes g_mimes;

bool sort_auto_listing(auto_listing i, auto_listing j);

class File {
 public:
	File();
	File(std::string path);
	~File();

	bool opens(bool create = false);
	void close_fd();
	void create(std::string &body);
	void append(std::string &body);
	void unlink();
	void set_path(std::string path, bool negociation = false);
	bool is_directory();
	std::string last_modified();
	bool exists();
	bool exists(std::string &path);

	std::string find_index(std::vector<std::string> &indexes);
	void parse_match();

	std::string autoIndex(std::string &target);
	std::string &getMimeExtension();
	void parseExtensions();
	void parseExtensionsNegociation();
	std::string getContent();
	std::string &getPath();
	std::vector<std::string> &getMatches();
	int &getFd();

 private:
	int fd_;
	std::string file_name_;
	std::string file_name_full_;
	std::string mime_ext_;
	std::vector<std::string> matches_;
	std::string path_;
};

#endif