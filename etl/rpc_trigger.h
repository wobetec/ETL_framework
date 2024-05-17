#include "../src/framework.h"

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int BUFFER_SIZE = 1024 * 1024;


class RCPTrigger : public Trigger {
    public:
        RCPTrigger(Queue<std::string, std::string> &outQueue, std::string first, std::string second) : Trigger(outQueue, first, second) {}
        
        void run() override {
            int server_fd, new_socket;
            struct sockaddr_in address;
            int opt = 1;
            int addrlen = sizeof(address);
            char buffer[BUFFER_SIZE] = {0};

            server_fd = socket(AF_INET, SOCK_STREAM, 0);
            setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

            address.sin_family = AF_INET;
            address.sin_addr.s_addr = INADDR_ANY;
            address.sin_port = htons(8080);

            bind(server_fd, (struct sockaddr *)&address, sizeof(address));
            listen(server_fd, 3);

            while(running){
                new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
                read(new_socket, buffer, BUFFER_SIZE);
                // create a hard copy of the buffer to var second
                std::string second = buffer;
                outQueue.enQueue(std::make_pair("cade", second));
                //addToQueue();
            }

            close(new_socket);
            close(server_fd);
        }
};