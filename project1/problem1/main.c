#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	//printf("%d\n",argc);
	//check arguements
	if(argc <3){
		perror("Not enough input args");
		exit(1);
	}
	int numInputs = argc>=3 ? argc-1:argc;

	//check if input files exits aand are readable
	for(int i=1; i< numInputs ; i++){
		printf("%s\n",argv[i]);
		//open the file
		if (access(argv[i], R_OK)){
			perror("Reading error");
			exit(1);
		}
	}

	//get output file name
	const char *outputFile = argc>3 ? argv[argc-1]:"myfile.out";

	//set up file descriptors
	int fd[numInputs+1];

	//All input fd set to read only
	for(int i =0; i < numInputs-1; i++){
		fd[i] = open(argv[i+1], O_RDONLY);
		if(fd[i] == -1){
			printf("Failed to open %s", argv[i+1]);
			exit(1);
		}
	}

	//output fd set to write only
	fd[numInputs-1] = open(outputFile, O_WRONLY | O_CREAT | O_APPEND);

	return 0;
}


// void WriteInFile (int fd, const char *buff, int len){
	
// }

// void CopyFile (int fd, const char *file_in){
	
// }
