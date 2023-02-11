/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project, 
in order to read and write information from and to the Backend
*/

//includes.
#include "Pipe.h"
#include <iostream>
#include <thread>
#include "Board.h"


void main()
{
	Pipe p;
	bool isConnect = p.connect();
	
	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else 
		{
			p.close();
			return;
		}
	}
	

	char msgToGraphics[1024];
	strcpy_s(msgToGraphics, "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR1"); // just example...
	

	//start the game.
	Board b(msgToGraphics);
	p.sendMessageToGraphics(msgToGraphics);   // send the board string


	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();
	int number = 1;

	while (msgFromGraphics != "quit")
	{
		
		strcpy_s(msgToGraphics, "YOUR CODE"); // msgToGraphics should contain the result of the operation

		//Answer of the turn.
		number = b.goodMove(msgFromGraphics.substr(0, 2), msgFromGraphics.substr(2, 4), true);
		msgToGraphics[0] = (char)(number + '0');
		msgToGraphics[1] = 0;
		
		//Change the board(if its legal turn).
		if (number == 0 || number == 1)
		{
			b.make_turn(msgFromGraphics.substr(0, 2), msgFromGraphics.substr(2, 4));
		}
		if (number == 8)
		{
			msgToGraphics[0] = '0';
			msgToGraphics[1] = 0;
			p.sendMessageToGraphics(msgToGraphics);
			msgFromGraphics = p.getMessageFromGraphics();
			msgToGraphics[0] = '8';
			msgToGraphics[1] = 0;
		}
		
		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);   

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}

	p.close();
}