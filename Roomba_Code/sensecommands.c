#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/resource.h>

//void print_err(char *msg)
//{
//  fprintf(stderr, "%s: %d, %s\n", msg, errno,
//          strerror(errno));
//  exit(1);
//}

int main(int argc, char* argv[]){
pid_t Child;
printf("Number of arguments: %d\n", (argc-1));
Child = fork();

switch(Child){
	case -1:
		printf("Can't fork the parent process");
		exit(1);
		break;
	case 0:
		execlp("/usr/bin/python", "/home/pi/examples/python-sense-hat/commands.py", "/home/pi/examples/python-sense-hat/commands.py","drive", NULL);
		printf("test\n");
		exit(1);
		break;
	default:
		break;
}
//if(Child == 0){
//	printf("Ensured child exits\n");
//	exit(1);
//}
for(int iChild=0; iChild<(argc-1); iChild++){
wait(NULL);
}
printf("All children have finished\n\n");

return 0;
}
//pid_t pid = fork();

  /* Fork the parent to create a child that can execute our python script */
  /* This way the parent can continue, because `exec()` functions cause */
  /* the origin process to terminate. We sacrifice the child. */
//  if (!pid) {
    /* child active */
//    if (execlp("usr/bin/python", "usr/bin/python",
//        "home/pi/examples/python-sense-hat/commands.py",(char*) NULL) == -1) {
//      print_err("Can't run python program");
//    }
//  } else if (pid == -1) {
    /* error */
//    print_err("Can't fork the parent process");
//  } else {
    /* parent active */
//  }

  //return 0;
