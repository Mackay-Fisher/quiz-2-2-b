#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
//Basic helper file to hlep breakup teh code and make it look cleaner and easier to read
int checkfile( struct stat fileinfo){//take in a stat which hodls teh file info and returns an int based on the type of file by using all of the statreader gucntions from the stat.h library
    if (S_ISDIR(fileinfo.st_mode)){return 1;} //Relies on the stat function to return a struct with the file information and uses the S_ISDIR fucntion which checks the stat to see if it is a directory
    else if (S_ISREG(fileinfo.st_mode)){return 2;}//Uses the in built S_ISREG function to check if the file is a regular file
    else if (S_ISLNK(fileinfo.st_mode)){return 3;}//Uses the in built S_ISLNK function to check if the file is a symbolic link
    else if (S_ISCHR(fileinfo.st_mode)){return 4;}//Uses the in built S_ISCHR function to check if the file is a character special file
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2)//Checks to see if we only call tehf ucntion name if we do this will return the proper usage case for this type of function
    {
        printf("usage: path1 [path2 ...]\n");//print stament to math the given example file
        exit(1);//this calls a system exist whwihc is then used in order to exit the program
    }
    struct stat fileinfo;
    for(int i=1; argc > i; i++){//This itterates through all of the arguments that are passed into the function
        int check = stat(argv[i], &fileinfo); //first calls stat on the argument of a file to get information about the file
        if (check == -1)//if the file does not exist, stat returns -1 menaing that there is a path error
        {
            printf("%s: path error\n", argv[i]);//This is a print stament to just match the output of the test
        }
        check = checkfile(fileinfo);//This calls the checkfile function which returns an int based on the type of file
        switch (check)//This then create a switch stament that in my opinion looks way cleaner than a bunch of if else staments
        {
            case 1:
                printf("%s: directory\n", argv[i]);//prints the file name and then the type of file that it is to mathc the example output corresponds to S_ISDIR call
                break;
            case 2:
                printf("%s: regular file\n", argv[i]);//prints the file name and then the type of file that it is to mathc the example output corresponds to S_ISREG call
                break;
            case 3: 
                printf("%s: symbolic link\n", argv[i]);// prints the file name and then the type of file that it is to mathc the example output corresponds to S_ISLNK call
                break;
            case 4:
                printf("%s: character special file\n", argv[i]);//prints the file name and then the type of file that it is to mathc the example output corresponds to S_ISCHR call
                break;
            default:
                break;
        }
    }
    
}