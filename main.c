#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

int main(int ac, char **av)
{
    struct sockaddr_in sockinfo;
    int sockfd = 0;
    int new_socket = 0;
    int opt = 1;
    int addrlen = sizeof(sockinfo);

    sockinfo.sin_family = AF_INET;
    sockinfo.sin_addr.s_addr = INADDR_ANY;
    sockinfo.sin_port = htons(21);

    //define le socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket Failed");
        exit(1);
    }
    // force use du port sans erreur "port utilisé"
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(1);
    }
    if (bind(sockfd, (struct sockaddr *)&sockinfo, sizeof(sockinfo)) < 0)
    {
        perror("bind failed");
        exit(1);
    }
    if (listen(sockfd, 10) < 0)
    {
        perror("listen");
        exit(1);
    }
    if ((new_socket = accept(sockfd, (struct sockaddr *)&sockinfo, (socklen_t*)&addrlen)) < 0)
    {
        perror("accept");
        exit(1);
    }
    dprintf(new_socket, "IP Address : %d\n", ntohl(sockinfo.sin_addr.s_addr));
    return 0;
}   