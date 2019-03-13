#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "errormsg.h"


void housekeeping();

struct driver {
	int size;
	int serialn;
	int hw_mac;
	const char* name;
	bool is_loaded;
};

struct driver_list {
	struct driver_list* next = NULL;
	struct driver running;
};

struct driver_list* drv_lst = NULL;

bool driver_init(struct driver drv){

	struct driver_list* new_drv_l = (struct driver_list*)malloc(sizeof(struct driver_list));		
	memcpy(&(new_drv_l->running), &drv, drv.size);
	new_drv_l->running.name = drv.name;
	new_drv_l->next = NULL;
	new_drv_l->running.is_loaded = true;
	
	if(drv_lst == NULL)
	{
		drv_lst = new_drv_l;
	} else {
		struct driver_list* first = drv_lst;
		while (drv_lst->next != NULL) {
			drv_lst = drv_lst->next;
		}	
		drv_lst->next = new_drv_l;
		drv_lst = first;
	}

	return new_drv_l->running.is_loaded;
}

bool driver_unload(const char* name)
{
	if(drv_lst == NULL)
		return false;

	struct driver_list* first = drv_lst;
	while (drv_lst->next != NULL) {	
		drv_lst = drv_lst->next;
	}
	
	if (strcmp(drv_lst->running.name, name) == 0) {
		drv_lst->running.is_loaded = false;
	}
	else {		
		char error_msg [256];
		sprintf(error_msg, could_not_unload, name);
		printf("%s\n", error_msg);

		return false;
	}

	drv_lst = first;
	housekeeping();
	return true;
}

void housekeeping() {

	if (drv_lst->next == NULL) {
		if(drv_lst->running.is_loaded == false) {
			free(drv_lst);
			drv_lst = NULL;
		}
	} else {
		struct driver_list* first = drv_lst;
		while (drv_lst->next != NULL) {	
			if(drv_lst->next->running.is_loaded == false) {
				free(drv_lst->next);
				drv_lst->next = NULL;
			} else
				drv_lst = drv_lst->next;
		}	
	}
}