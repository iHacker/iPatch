/*hostfilepatcher by iHacker and malontop with the help of c_axis ;)
http://twitter.com/iHacker
http://twitter.com/malontop
http://twitter.com/c_axis*/

#include <stdio.h>
#include <string.h>

#define HOSTFILE "/etc/hosts"
#define BACKUPFILE "/etc/hosts.backup"
#define NEWHOST "74.208.105.171 gs.apple.com "

// NOTE: Thanks c_axis!
int checkifPatched(){

	FILE *hosts = fopen(HOSTFILE, "rb");
	char buffer[32];
	int ret_val = -1; // default return value indicates problematic fopen() call; if the file can be read, ret_val will be changed to 0 or 1;

	if(hosts != NULL) {

		// loop UNTIL the string is found, not until every line is read
		// it may not make a difference in some cases; other times, it will be significantly faster
		while(fgets(buffer, 32, hosts) != NULL && ret_val != 0) {

			// branch eliminated; faster, unconditional code
			// ret_val will be 0 if the string was found; otherwise 1
			ret_val = (strstr(buffer, NEWHOST) == NULL);

		}

	}

	fclose(hosts);
	return ret_val;
}

int patchFile(){
	FILE *hosts = fopen(HOSTFILE, "ab");
	if(hosts != NULL)
	{
		fprintf(hosts, NEWHOST);
		fprintf(hosts, "\n");
		fclose(hosts);
		return(0);
	}else
	{
		fclose(hosts);
		return(-1);
	}
}

int backupFile(){
	FILE *orig = fopen(HOSTFILE, "rb");
	FILE *backup = fopen(BACKUPFILE, "wb");
	char ch;
	if(orig != NULL && backup != NULL){
		while(!feof(orig)){
			ch = fgetc(orig);
			if(ferror(orig)){
				fclose(orig);
				fclose(backup);
				return(-1);
			}
			if(!feof(backup)){
				fputc(ch, backup);
			}
			if(ferror(backup)){
				fclose(orig);
				fclose(backup);
				return(-1);
			}
		}
	}else{
		fclose(orig);
		fclose(backup);
		return(-1);
	}
	fclose(orig);
	fclose(backup);
	return(0);
}

int main(int argc, char* argv[])
{
	printf("Patch the host file? Y or N: ");
	char choice;
	scanf("%c", &choice);

	if(choice == 'Y' || choice == 'y')
	{
		puts("Check if file is already patched...");
		if(checkifPatched() != 0){
			puts("File not patched yet.\n");
			puts("Backing up...");
			if(backupFile() == 0){
				puts("Backup was successful.\n");
				puts("Patching hostfile...");
				if(patchFile() == 0)
					puts("Succesfully patched host file.\n");	
				else
					perror("ERROR: FILE NOT FOUND");
			}else
				perror("Unable to backup hostfile");
		}else{
			puts("Host file is already patched\n");
			return(0);
		}
	}else
		return(1);

	return(0);
}
