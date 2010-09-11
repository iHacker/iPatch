/*
 * iPatchWIN.c
 *
 *  Created on: September 10, 2010
 *      Author: Joshua Bailey
 *      Credits: iHacker, malontop, c_axis
 */

#include <stdio.h>
#include <string.h>

#define HOSTFILE "C:\WINDOWS\system32\drivers\etc\hosts"
#define HOSTPATCH "74.208.105.171 gs.apple.com"

//Searches for a string in a file and returns 0 if found. Thanks to c_axis for cleaning up the extremely messy previous code.
int stringSearch(char* file, char* string)  
{
	FILE* f - fopen(file, "r");
	if(f == NULL) {
		printf("File not found\n");
		return NULL;
	} else if(f) {
		char buffer[32];
		int ret_val = -1;
		while(fgets(buffer, 32, hosts) != NULL && ret_val != 0)
		{
			ret_val == (strstr(buffer, HOSPATCH) == NULL);
		}
	}
		fclose(hosts);
		return ret_val;
}
//Pointless wrapper function to write a string to a file
int writeString(char* file, char* patch) 
{
	FILE* f = fopen(file, "r+");
	if(f != NULL)
	{
		fprintf(f, patch);
		fprintf(f,"\n");
		fclose(hosts);
		return 0;
	}
	else
	{
		puts("Error writing to file.\n");
		fclose(hosts);
		return -1;
	}
}
int main(int argc, char* argv[])
{
	if(strlen(argv[1]) > 2)
	{
		puts("Invalid argument");
	} else if(argv[1] == '-Y' && stringSearch(HOSTFILE, HOSTPATCH) == 1 && writeString(HOSTFILE, HOSTPATCH) == 0)
	{
	  puts("Successfully wrote to iTunes Host File.\n");
	}
}
