#include <iostream>
#include <string>
#include <string.h>
#include <iomanip>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include<list>
#include<vector>
#include<SFML/Graphics.hpp>
using namespace std;

sf::RenderWindow W;
list<sf::RectangleShape> pale[3];
string hanoi(int n, char a, char b, char c)
{
	if (n != 0)
	{
		stringstream ss;
		ss << hanoi(n - 1, a, c, b);
		ss << a << c;
		ss <<hanoi(n - 1, b, a, c);
		return ss.str();
	}
	return "";
}


int main()
{
	W.create(sf::VideoMode(1080, 720, 32), "Hanoi");
	W.setActive(true);
	W.setKeyRepeatEnabled(false);
	W.setVerticalSyncEnabled(true);
	W.setPosition(sf::Vector2i(280, 280));
	  

	sf::RectangleShape A(sf::Vector2f(40, 500));
	A.setFillColor(sf::Color(255, 0, 0));
	A.setOrigin(0, 0);
	A.setPosition(250-80, 220);

	sf::RectangleShape B(sf::Vector2f(40, 500));
	B.setFillColor(sf::Color(0, 255, 0));
	B.setOrigin(0, 0);
	B.setPosition(600-80, 220);

	sf::RectangleShape C(sf::Vector2f(40, 500));
	C.setFillColor(sf::Color(0, 0, 255));
	C.setOrigin(0, 0);
	C.setPosition(950-80, 220);

	int licznik = 0;
	
	

	sf::Font ttf;
	ttf.loadFromFile("fonts/OpenSans-Bold.ttf");
	string s("Licznik przesuniec: ");
	sf::Text txt(s, ttf);
	txt.setCharacterSize(30);
	txt.setFillColor(sf::Color(69, 120, 189));
	txt.setPosition(10, 40);

	ostringstream ss;
	ss << licznik;
	sf::Text atext;
	atext.setFont(ttf);
	atext.setCharacterSize(30);
	atext.setFillColor(sf::Color(69, 120, 189));
	atext.setPosition(300, 40);
	
	atext.setString(ss.str());

	sf::Event event;

	//switching number of the disks
	int n = 6;
	string steps = hanoi(n, 'A', 'B', 'C');
	cout << steps << endl;

	for (int i = 1; i <= n; i++)
	{
		pale[0].push_back(sf::RectangleShape(sf::Vector2f(50 + 40 * i, 20)));
		pale[0].back().setFillColor(sf::Color(255, 255, 255));
		pale[0].back().setOrigin((50 + 40 * i) / 2 - 20, 0);
	}
	



	while (W.isOpen())
	{
		while (W.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))W.close();
		}
			W.clear(sf::Color(0,0,0));
			W.draw(A);
			W.draw(B);
			W.draw(C);
			

			for (int i = 0; i < 3; i++)
			{
				int pos = 700;
				for (auto x = pale[i].rbegin(); x != pale[i].rend(); x++)
				{
					x->setFillColor(sf::Color(255, 255, 255));
					x->setOutlineColor(sf::Color(123, 123, 123));
					int X = 170 + i * 350;
					int Y = (pos -= 30);
					x->setPosition(X, Y);
					W.draw(*x);
				}
			}

			if (steps != "") {
				string two = steps.substr(0, 2);
				if (two == "AB") {
					pale[1].push_front(pale[0].front()); pale[0].pop_front();
				}
				if (two == "AC") {
					pale[2].push_front(pale[0].front()); pale[0].pop_front();
				}
				if (two == "BA") {
					pale[0].push_front(pale[1].front()); pale[1].pop_front();
				}
				if (two == "BC") {
					pale[2].push_front(pale[1].front()); pale[1].pop_front();
				}
				if (two == "CA") {
					pale[0].push_front(pale[2].front()); pale[2].pop_front();
				}
				if (two == "CB") {
					pale[1].push_front(pale[2].front()); pale[2].pop_front();
				}
				steps = steps.substr(2);
				licznik++;
				ss.str("");
				ss << licznik;
				atext.setString(ss.str());

			}
			
			

			
			W.draw(txt);
			W.draw(atext);
			W.display();
			sf::sleep(sf::milliseconds(550));

		
	}
	return 0;
}