#include <iostream>
#include <SFML/Network.hpp>

const unsigned short PORT = ;
const std::string IPADDRESS(" ");

std::string msgSend;

sf::TcpSocket socket;
sf::Mutex globalMutex;
bool quit = false;

void DoStuff(void)
{
	static std::string oldMsg;
	while(!quit)
	{
		sf::Packet packetSend;
		globalMutex.lock();
		packetSend << msgSend;
		globalMutex.unlock();

		socket.send(packetSend);

		std::string msg;
		sf::Packet packetReceive;

		socket.receive(packetReceive);
		if ((packetReceive >> msg) && oldMsg != msg && !msg.empty())
		{
			std::cout << msg << std::endl;
			oldMsg = msg;
		}
	}
}

void Server(void)
{
    sf::SelectorTCP Selector;
	sf::TcpListener listener;

	if(!listener.listen(PORT)){
        printf("no Listner!");
	}

	Selector.Add(Listener);

    while (true)
    {
        unsigned int NbSockets = Selector.Wait();
        
        for (unsigned int i = 0; i < NbSockets; ++i)
        {
            sf::SocketTCP Socket = Selector.GetSocketReady(i);
        }
    }

	//listener.accept(socket);
	std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
}

void GetInput(void)
{
	std::string s;
	std::cout << "\nEnter \"exit\" to quit or message to send: ";
	getline(std::cin,s);
	if(s == "exit")
		quit = true;
	globalMutex.lock();
	msgSend = s;
	globalMutex.unlock();
}


int main(int argc, char* argv[])
{
	Server();


	while(!quit)
	{
		GetInput();
	}

	return 0;
}
