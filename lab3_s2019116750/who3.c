#include<stdio.h>
#include<unistd.h>
#include<utmp.h>
#include<fcntl.h>
#include<stdlib.h>
#include<time.h>

#define SHOWHOST

int utmp_open( char *);
void utmp_close();
void show_info(struct utmp *);
void showtime(long);

int main(){
    struct utmp *utbufp, *utmp_next();

    if ((utmp_open(UTMP_FILE) == -1)){
        perror(UTMP_FILE);
        exit(1);
    }

    while( ( utbufp = utmp_next()) != ((struct utmp *) NULL))
        show_info(utbufp);
    
    utmp_close();
    return 0;
}

void show_info(struct utmp *utbufp){
    if(utbufp->ut_type != USER_PROCESS)
        return;

    printf("%-10.11s", utbufp->ut_name);
    printf(" ");
    printf("%-10.8s", utbufp->ut_line);
    printf(" ");
    showtime(utbufp->ut_time);

    if(utbufp->ut_host[0] != '\0')
        printf(" (%s)", utbufp->ut_host);
    
    printf("\n");
}

void showtime( long timeval){
    char *cp;

    cp = ctime(&timeval);
    printf("%12.12s", cp+4);
}


