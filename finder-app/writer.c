#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h> 
#include <string.h>
#include <syslog.h>


int main(int argc, char *argv[])
{
  int fd; 
  ssize_t nr;
  
  openlog(NULL,0,LOG_USER);
  if (argc != 3) {
    syslog(LOG_ERR,"Invalid number of arguments: %d", argc);
    return 1;
  }   
  fd = open (argv[1], O_WRONLY | O_CREAT | O_TRUNC,
             S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP | S_IROTH);
  if (fd == -1){
    /* error */
    syslog(LOG_ERR,"%s:: file not open", argv[1]);
    return 1;
  }
  syslog(LOG_DEBUG,"Writing %s to %s",argv[2],argv[1]);
  
  /* write the string in 'buf' to 'fd' */
  nr = write (fd, argv[2], strlen (argv[2]));
  if (nr == -1){
    /* error */
    syslog(LOG_ERR,"%s:: Unable to write to file", argv[2]);
    return 1;
  }
  if (close (fd) == -1){
    /* error */
    syslog(LOG_ERR,"%s:: file not closed", argv[1]);
    return 1;
  }
  return 0;
}

