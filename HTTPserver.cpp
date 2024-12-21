#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <random>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "FuncA.h"
#define PORT 8081

void handleClientRequest(int clientSocket) {
    char buffer[30000] = {0};
    read(clientSocket, buffer, 30000);
    std::cout << "\nRequest received:\n" << buffer << std::endl;

    // Extract the request line (e.g., "GET /compute HTTP/1.1")
    std::string request(buffer);
    size_t pathStart = request.find(' ') + 1; // Position of the first space after the method
    size_t pathEnd = request.find(' ', pathStart); // Position of the second space
    std::string path = request.substr(pathStart, pathEnd - pathStart);

    std::cout << "Request path: " << path << std::endl;

    if (path == "/compute") {
        Func func;

        // Simulate heavy computation with trigonometric function
        std::vector<double> values;
        std::mt19937 gen(123); // Random number generator
        std::uniform_real_distribution<double> dist(0.0, M_PI);

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 275000; ++i) {
            values.push_back(func.FuncA(dist(gen), 10));
        }

        for (int i = 0; i < 500; ++i) {
            std::sort(values.begin(), values.end());
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        // Create HTTP response
        std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
        response += "Elapsed time: " + std::to_string(elapsed.count()) + " seconds\n";

        send(clientSocket, response.c_str(), response.size(), 0);
        std::cout << "Response sent, connection closed." << std::endl;
    } else {
        // Respond with 404 Not Found for other paths
        std::string response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n";
        response += "Path not found\n";
        send(clientSocket, response.c_str(), response.size(), 0);
    }

    close(clientSocket);
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Socket binding failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 10) < 0) {
        perror("Listening failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is running on port " << PORT << ". Waiting for connections..." << std::endl;

    while (true) {
        if ((clientSocket = accept(serverSocket, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Connection accept failed");
            close(serverSocket);
            exit(EXIT_FAILURE);
        }

        std::cout << "\nAccepted a new connection." << std::endl;

        handleClientRequest(clientSocket);
    }

    close(serverSocket);
    return 0;
}

