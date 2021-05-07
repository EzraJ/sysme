#include <iostream>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <vector>
#include <pwd.h>

// https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c

inline bool fileExist(const std::string& fName){
	struct stat buffer;
	return (stat (fName.c_str(), &buffer) == 0);
}

inline bool dirExists(const std::string& dName){
	struct stat buffer;
	stat(dName.c_str(), &buffer);
	return buffer.st_mode & S_IFDIR;
}


int main(){
	struct passwd *pw = getpwuid(getuid());
	std::string homedir = pw->pw_dir;
	std::string config = homedir + "/.sysme/";
	unsigned int usr = getuid();
	unsigned int usre = geteuid();
	const char* user = std::getenv("USER");
	
	if(usr == usre){
		std::cout << "Running as " << user << "\n";
	}else{
		std::cout << "Running as root\n";
	}

	mkdir((homedir + "/.sysme/").c_str(), 0777);

	std::ofstream buf(homedir+"/.sysme/files.cfg", std::ios_base::app | std::ios_base::ate);
	buf.close();
	std::ifstream conf(homedir+"/.sysme/files.cfg");

	std::vector<std::string> files;
	std::string tmp;
	while(std::getline(conf, tmp)){
		files.push_back(tmp);
	}

	std::cout << "Welcome to sysme, printing out possible readmes!\n";

	std::ifstream currentFile;
	for(auto& e : files){
		std::cout << "# " << e << std::endl;
		std::ifstream currentFile(config + e, std::ios_base::app);
		while(std::getline(currentFile, tmp)){
			std::cout << tmp << std::endl; 
		}
		currentFile.close();
		std::cout << std::endl;
	}
	
	return 0;
}