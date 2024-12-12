#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <curl/curl.h>

size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Function to test HTTP GET request
void testGetComputeEndpoint() {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize curl\n";
        return;
    }

    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8081");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    auto start = std::chrono::high_resolution_clock::now();
    CURLcode res = curl_easy_perform(curl);
    auto end = std::chrono::high_resolution_clock::now();

    if (res != CURLE_OK) {
        std::cerr << "GET request failed: " << curl_easy_strerror(res) << "\n";
    } else {
        std::cout << "Response: " << response << "\n";
    }

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";

    // Validate the response and elapsed time
    int elapsedMs = static_cast<int>(elapsed.count() * 1000);
    if (response.empty()) {
        std::cerr << "Test failed: No response from server\n";
    } else if (elapsedMs < 5000 || elapsedMs > 20000) {
        std::cerr << "Test failed: Elapsed time is not within the expected range\n";
    } else {
        std::cout << "Test passed\n";
    }

    curl_easy_cleanup(curl);
}

int main() {
    std::cout << "Starting HTTP server tests...\n";

    std::this_thread::sleep_for(std::chrono::seconds(2));

    testGetComputeEndpoint();

    return 0;
}

