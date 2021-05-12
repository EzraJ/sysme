#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <vector>
#include <pwd.h>


int main(){
	struct passwd *pw = getpwuid(getuid());
	std::string homedir = pw->pw_dir;
	std::string config = homedir + "/.sysme/";
	const char* user = std::getenv("USER");
	
	std::cout << "Running as " << user;

	mkdir((homedir + "/.sysme/").c_str(), S_IRWXU | S_IRWXG | S_IRWXO); // Allows all groups, users, and owners, to read, write, and execute this directory.

	std::ofstream buf(homedir+"/.sysme/files.cfg", std::ios_base::app | std::ios_base::ate);
	buf.close();
	std::ifstream conf(homedir+"/.sysme/files.cfg");

	std::vector<std::string> files;
	std::string tmp;
	if(!conf.good()){
		std::cout << "\nsysme could not read config file, exiting sysme\n";
		conf.close();
		std::exit(1);
	}
	while(std::getline(conf, tmp)){
		files.push_back(tmp);
	}

	std::cout << "\nWelcome to sysme, printing out possible readmes!\n";

	std::ifstream currentFile;
	for(auto& e : files){
		std::cout << "# " << e << std::endl;
		std::ifstream currentFile(config + e, std::ios_base::app);
		if(!currentFile.good()){
			std::cout << "Couldn\'t read file: " << e << std::endl;
		}
		while(std::getline(currentFile, tmp)){
			std::cout << tmp << std::endl; 
		}
		currentFile.close();
		std::cout << std::endl;
	}

	conf.close();
	
	return 0;
}