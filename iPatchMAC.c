//README
/*iPatcher by iHacker and malontop with the help of c_axis ;)
http://twitter.com/iHacker
http://twitter.com/malontop
http://twitter.com/c_axis

Run as root
*/

#include <stdio.h>
#include <string.h>

//#define HOSTFILE "/etc/hosts"
//#define BACKUPFILE "/etc/hosts.backup"

#define HOSTFILE "./text"
#define BACKUPFILE "./text.backup"

#define NEWHOST "74.208.105.171 gs.apple.com"

int checkifPatched(FILE *fp){
	char buffer[BUFSIZ];
	int retVal = -1;
	if(fp != NULL){
		fseek(fp, 0, SEEK_SET);
		while(fgets(buffer, BUFSIZ, fp) != NULL && retVal != 0){
			retVal = (strstr(buffer, NEWHOST) == NULL);
		}
	}
	return(retVal);
}

int patchFile(FILE *fp, const char *newhost){
	if((fprintf(fp, newhost) > 0) && (fprintf(fp, "\n") > 0)){
		return(0);
	}
	return(-1);
}

int backupFile(FILE *orig){
	FILE *backup = fopen(BACKUPFILE, "wb");
	int retVal = -1;
	if(backup != NULL){
		fseek(orig, 0, SEEK_SET);
		int ch;
		while( retVal = ((ch = fgetc(orig)) != EOF) && (fputc(ch, backup) != EOF)){
		}
	
	}
	fclose(backup);
	return(retVal);
}

int main()
{
	printf("\nWelcome to iPatcher.\n");
	printf("Patch the host file, located at \"%s\"? Y or N: ", HOSTFILE);
	int retVal = 0;
	char choice;
	scanf("%c", &choice);

	if(choice == 'Y' || choice == 'y')
	{
		FILE *hosts = fopen(HOSTFILE, "ab+");
		puts("Opening hostfile...");
		if(retVal = (hosts != NULL)){
			puts("Check if file is already patched...");
			if (retVal = (checkifPatched(hosts) != 0)){
				puts("Backing up...");
				if (retVal = (backupFile(hosts) == 0)){
					puts("Patching hostfile...");
					retVal = !(patchFile(hosts, NEWHOST));
				}
			}
		}
		fclose(hosts);
	}
	puts( (retVal) ? "Okay" : "Failed" ); //i know, could be better
	return(retVal);
}
