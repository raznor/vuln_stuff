#include <iostream>
#include <string>
#include "hw_access.h"

class DRV_Manager
{
public:
	DRV_Manager();
	~DRV_Manager();
	virtual void load();	
	virtual void unload();
};

class Fs_DRV_Manager : public DRV_Manager
{
	std::string fs_name {""};
	struct driver fs_driver;
public:
	Fs_DRV_Manager();
	Fs_DRV_Manager(std::string,int,int,int);
	~Fs_DRV_Manager();
	void load();
	void unload();
};

//DRV_Manager

DRV_Manager::DRV_Manager(){
}

DRV_Manager::~DRV_Manager(){
	unload();
}

void DRV_Manager::load(){
}

void DRV_Manager::unload(){
}

//Fs_DRV_Manager

Fs_DRV_Manager::Fs_DRV_Manager(){
}

Fs_DRV_Manager::~Fs_DRV_Manager(){
	unload();
}

Fs_DRV_Manager::Fs_DRV_Manager(std::string str, int size_name, int serialn, int hw_mac):fs_name(str)
{
	fs_driver.size = size_name;
	fs_driver.serialn = serialn;
	fs_driver.hw_mac = hw_mac;
	fs_driver.name = fs_name.c_str();
	fs_driver.is_loaded = false;

}

void Fs_DRV_Manager::load(){
	if(!fs_driver.is_loaded) {
		fs_driver.is_loaded = driver_init(fs_driver);	
	}
}

void Fs_DRV_Manager::unload(){		
	driver_unload(fs_driver.name);
}


int main(int argc, char* argv[])
{	
	Fs_DRV_Manager* ext4 = new Fs_DRV_Manager("ext4", 20, 6354, 7777);
	DRV_Manager* bad = new Fs_DRV_Manager(argv[1], 10, 3177, 3434);

	ext4->load();
	bad->unload();	
	ext4->unload();

	return 0;
}