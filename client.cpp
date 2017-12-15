#include <iostream>
#include <SFML/Network.hpp>



const unsigned short PORT = ;
const std::string IPADDRESS(" ");

string msgSend;

using namespace std;
usinig namespace sf;

TcpSocket socket;
Mutex globalMutex;

bool quit = false;

void DoStuff(void)
{
	static string oldMsg;

	while(!quit)
	{
		Packet packetSend;
		globalMutex.lock();
		packetSend << msgSend;
		globalMutex.unlock();

		socket.send(packetSend);

		string msg;
		Packet packetReceive;

		socket.receive(packetReceive);
		if ((packetReceive >> msg) && oldMsg != msg && !msg.empty())
		{
			cout << msg << endl;
			oldMsg = msg;
		}
	}
}

void Server(void)
{
	TcpListener listener;
	listener.listen(PORT);
	listener.accept(socket);
	cout << "New client connected: " << socket.getRemoteAddress() << endl;
}

bool Client(void)
{
	if(socket.connect(IPADDRESS, PORT) == Socket::Done)
	{

	}
}

void GetInput(void)
{
	cout << "\nEnter \"exit\" to quit or message to send: ";
	cin >> string text;

	if(text == "exit")	quit = true;

	globalMutex.lock();
	msgSend = text;
	globalMutex.unlock();
}


int main(int argc, char* argv[])
{

}
