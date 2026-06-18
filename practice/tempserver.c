#include <stdio.h>    // fprintf
#include <stdlib.h>   // exit
#include <string.h>   // memset

#include <signal.h>    //signals for reaping dead child processes
#include <errno.h>     //errno in sigchld_handler
#include <sys/wait.h>   //waitpid in sigchld_handler

#include <unistd.h>    //close(sockfd)
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MYPORT "3490"
#define BACKLOG 10

void sigchld_handler(int s)
{
    (void)s; // quiet unused variable warning

    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(){
    struct sigaction sa;
    int status,sockfd,new_fd;
    struct addrinfo hints, *servinfo;
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    char s[INET6_ADDRSTRLEN];
    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
    hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

    //getting address info
    if ((status = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "gai error: %s\n", gai_strerror(status));
        exit(1);
    }
    // servinfo now points to a linked list of 1 or more struct addrinfos

    // make a socket:
    if ((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1){
        perror("Socket Creation Failed");
        exit(1);
    }

    //making port reusable without timeout on exit
    int yes=1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);

    // bind it to the port we passed in to getaddrinfo():
    if (bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
        perror("Binding Failed");
        exit(1);
    }

    // ... do everything until you don't need servinfo anymore ....
    freeaddrinfo(servinfo); // free the linked-list

    //listening
    if (listen(sockfd, BACKLOG) == -1) {
        perror("Listening Failed");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");


    while(1) {  // main accept() loop
        addr_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
        printf("server: got connection from %s\n", s);

        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork Failed");
            printf("Ignored a request from %s\n", s);
            close(new_fd);
            continue;
        }
        else if (pid == 0) { // this is the child process
            close(sockfd); // child doesn't need the listener
            char buffer[1000],message[1000],body[]="Hello friend.\nThis is a server made for learning\n";
            
            //receiving
            if (recv(new_fd, buffer, sizeof(buffer)-1, 0) == -1) {
                perror("recv");
                close(new_fd);
                exit(0);
            }

            //parsing and checking method,path and protocol
            char method[5],path[20],protocol[9];
            char method1[]="GET",method2[]="POST",protocol1[]="HTTP/1.1";
            char path1[]="/",path2[]="/file.txt";
            if(sscanf(buffer, "%4s %19s %8s", method, path, protocol) != 3){
                printf("Malformed Request.Closing Connection.\n");
                exit(0);
            }

            if(strcmp(protocol,protocol1)!=0){
                printf("Malformed Request:Use protocol HTTP/1.1\nClosing Connection.\n");
                exit(0);
            }
            if(strcmp(method,method1)==0){
                //dothis
            }else if(strcmp(method,method2)==0){
                //dothis
            }else{
                printf("Malformed Request:Method not supported.Closing Connection.\n");
                exit(0);
            }

            //showing parsed data on terminal where server is running
            printf("Method: %s\nPath: %s\nProtocol: %s\n", method, path, protocol);

            //sending
            sprintf(message,"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %ld\r\n\r\n%s",strlen(body),body);
            if (send(new_fd, message, strlen(message), 0) == -1) {
                perror("send");
            }
            close(new_fd);
            exit(0);
        }
        close(new_fd);  // parent doesn't need this
    }

    close(sockfd);
    return 0;
}