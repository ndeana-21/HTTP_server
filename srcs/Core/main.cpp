# include "Server.hpp"
# include "Client.hpp"
# include "Struct.hpp"

int		main(int argc, char **argv){
	//Webserver	webserver;
	if (argc != 2){
		std::cout << "ERROR: Wrong Program Arguments" << std::endl;
		exit(1);
	}
	try{

	}
	catch (std::exception &e){
		std::cout << e.what() << std::endl;
	}
	return 0;
}