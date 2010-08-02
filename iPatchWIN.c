// iPatchWIN.c
// Credits - iHacker, malontop, c_axis
#include <stdio.h>
#include <string.h>

#define HOSTFILE "C:\WINDOWS\system32\drivers\etc\hosts.txt"
#define NHOSTPATCH "74.208.105.171 gs.apple.com"

int checkIfPatched() // NOTE: Props to c_axis for his help on this
{
	
	FILE *hosts = fopen(HOSTFILE, "rb");
	char buffer[32];
	int ret_val = -1; // default return value indicates problematic fopen() call; if the file can be read, ret_val will be changed to 0 or 1;
	
	if(hosts != NULL) {
		
		// loop UNTIL the string is found, not until every line is read
		// it may not make a difference in some cases; other times, it will be significantly faster
		while(fgets(buffer, 32, hosts) != NULL && ret_val != 0) {
			
			// branch eliminated; faster, unconditional code
			// ret_val will be 0 if the string was found; otherwise 1
			ret_val = (strstr(buffer, NHOSTPATCH) == NULL);
			
		}
		
	}
	
	fclose(hosts);
	return ret_val;
}

int patchFile()
{
	FILE * hosts = fopen(HOSTFILE, "r+");
	if(hosts != NULL)
	{
		fprintf(hosts, NHOSTPATCH);
		fprintf(hosts,"\n");
		fclose(hosts);
		return 0;
	}
	else
	{
		fclose(hosts);
		return -1;
	}
}

int main(int argc, char * argv[])
{
	char choice;
	printf("Patch iTunes Host File? Y or N: ");
	scanf("%s", choice);

	if(choice == 'Y' || choice == 'Y')
	{
		printf("Checking if file is already patched...");
		checkIfPatched();

		if(checkIfPatched != 0)
		{
			printf("Patching iTunes Host File...");
		    patchFile();
		}
		else
		{
			perror("ERROR: FILE ALREADY PATCHED");
		}
		if(patchFile() == 0)
		{
			printf("iTunes Host File succesfully patched!\n");
		}
		else 
		{
			perror("ERROR: COULD NOT PATCH FILE");
		}
	}
	else
	{
		return -1;
	}

	return 0;
}