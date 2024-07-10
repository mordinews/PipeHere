// PipeHere.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <windows.h>
using namespace std;

#define PIPE_NAME L"\\\\.\\pipe\\MyPipe"

int main(void)
{
    HANDLE hPipe;
    OVERLAPPED overlap = { 0 };
    char buffer[128];
    DWORD read;

    // Connect to the named pipe
    hPipe = CreateFile(
        PIPE_NAME,
        GENERIC_READ,
        0, NULL, OPEN_EXISTING,
        FILE_FLAG_OVERLAPPED, NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to connect to pipe." << std::endl;
        return 1;
    }

    // Read from the pipe
    if (ReadFile(hPipe, buffer, sizeof(buffer), &read, &overlap)) {
        WaitForSingleObject(overlap.hEvent, INFINITE);
        std::cout << "Received message: " << buffer << std::endl;
    }
    else {
        std::cerr << "Failed to read from pipe." << std::endl;
    }


    // Exit
    CloseHandle(hPipe);

    return 0;
}