#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<string>
using namespace std;
using namespace sf;


float const ground = 450;
float const RightWall = 945;
float const LeftWall = -50;
RectangleShape door1(Vector2f(70, 100));
int cntr = 0;
Sprite powerUps[3];
Texture powerupsTexture[3];

bool runNow = true;
bool ghost2killed = false;

RenderWindow window(VideoMode(1000, 600), "HAUNTED ZAAAFRAN");
void setBackground_Animation(RenderWindow& window);
void setPowerUps();

struct enemy
{
	Sprite shape;
	int speed;
	float animation = 0;
	int health = 100;

} ghost2;
void game(enemy ghost[]);
void game2(enemy& ghost2);
void fighting1(enemy[], Texture[]);
void fighting2(Texture[]);

struct Player
{
	//variables 
	Sprite player;
	float currentframe;
	float moveX, moveY;
	FloatRect rect;
	bool is_grounded;
	int lastKeyPressed, powerupType = -1;
	float speed = 1, timeofspeed = 0.0;
	int lives = 14;
	int ghost1Killed = 0;
	//set & intialize 
	void setPlayer_intialization(Texture& playertexture)

	{
		player.setTexture(playertexture);
		player.setScale(1.45, 1.45);
		moveX = 0;
		moveY = 0;
		currentframe = 0;
		lastKeyPressed = 1;
	}
	void update(float time, Texture playertexture[])
	{
		rect.left += moveX * time;
		rect.top += moveY * time;
		//movement and gravity
		if (!is_grounded)
		{
			moveY += (0.001 * time);
		}
		is_grounded = false;    //to make gravity applied all the time except when on ground
		if (rect.left > RightWall)
			rect.left = RightWall;
		if (rect.left < LeftWall)
			rect.left = LeftWall;
		if (rect.top > ground)
		{
			rect.top = ground;
			moveY = 0;
			is_grounded = true;
		}
		//ANIMATION
		currentframe += 0.15 * time;
		if (currentframe > 8)
			currentframe -= 8;
		if (player1.player.getTexture() == &playertexture[0])
		{
			if (moveX > 0)
				player.setTextureRect(IntRect(int(currentframe) * 65, 0, 64, 60));
			if (moveX < 0)
				player.setTextureRect(IntRect(int(currentframe) * 65 + 64, 0, -64, 60));
		}
		if (runNow) {
			player.setTexture(playertexture[0]);
		}
		else {
			player.setTexture(playertexture[1]);
		}


		player.setPosition(rect.left, rect.top);
		moveX = 0; //??
	}
} player1;
void powerupCollision();
void checkPowerup();
void resetspeedTime();
void respawn(Clock&, Clock&);

struct help {
	Sprite powerUp;
	Vector2f R_positions;
	int x;

};
vector<help> powerupBag;

//puzzle variables
struct RectangleInfo {
	sf::RectangleShape shape;
	sf::Text tex;
	char letter;
	bool isClicked;
	bool isclickable;
	bool isspecific1;
	bool isspecific2;
	bool isspecific3;
};

RectangleInfo r[15];
Text tex[15];
// Set the position of the rectangle to be the same as the mouse position
RectangleShape mou(Vector2f(13, 13));

int puzzle();

int pageNum = 0;
//lives variables
Font livefont;
Text live("lives: ", livefont, 40);
Text lives;
string health2 = to_string(player1.lives);

int main() {

	//lives variables details
	lives.setString(health2);
	livefont.loadFromFile("Retosta.otf");
	lives.setFont(livefont);
	lives.setPosition(live.getPosition().x + 90, live.getPosition().y + 9);
	lives.setString(health2);

	//while (window.isOpen())
	{
		//Event event;
		//while (window.pollEvent(event))
		{
			//if (event.type == Event::Closed)
			{
				//window.close();
			}
		}
		// solution for multiple textures(sprie sheets)



			//players.setTextureRect(IntRect(0, 7*50, 50, 60));
			//players.setScale(1.8, 1.8);
			//players.setPosition(100, 100);
			//fighting(window);
		if (pageNum == 0)
			setBackground_Animation(window);
		if (pageNum == 1)
		{
			cout << "infinteee///////////////////" << endl;
			//puzzle();
			cout << "yarbbbbbbbbbb";
		}

		//window.display();
	}
}
void setBackground_Animation(RenderWindow& window)
{
	Clock timerADD, timerDELETE;
	Texture backgoundtexture1, backgoundtexture2;

	Sprite Backgrounds[2];
	backgoundtexture1.loadFromFile("Zaafran background level [1].JPG");
	Backgrounds[0].setTexture(backgoundtexture1);
	Backgrounds[0].setScale(2.3, 2);

	backgoundtexture2.loadFromFile("Zaafran background level (2).JPG");
	Backgrounds[1].setTexture(backgoundtexture2);
	Backgrounds[1].setScale(2.3, 2);

	door1.setPosition(1030, 380);

	RectangleShape blocks1[7], blocks2[5];
	blocks1[0].setSize(Vector2f(70, 70));
	blocks1[0].setPosition(150, 180);

	blocks1[1].setSize(Vector2f(40, 40));
	blocks1[1].setPosition(290, 145);

	blocks1[2].setSize(Vector2f(40, 40));
	blocks1[2].setPosition(260, 275);

	blocks1[3].setSize(Vector2f(110, 40));
	blocks1[3].setPosition(332, 370);

	blocks1[4].setSize(Vector2f(410, 43));
	blocks1[4].setPosition(592, 470);

	blocks1[5].setSize(Vector2f(410, 43));
	blocks1[5].setPosition(592, 290);

	blocks1[6].setSize(Vector2f(587, 60));
	blocks1[6].setPosition(0, 535);


	blocks2[0].setSize(Vector2f(325, 45));
	blocks2[0].setPosition(0, 167);

	blocks2[1].setSize(Vector2f(260, 40));
	blocks2[1].setPosition(212, 404);

	blocks2[2].setSize(Vector2f(290, 68));
	blocks2[2].setPosition(0, 530);

	blocks2[3].setSize(Vector2f(245, 60));
	blocks2[3].setPosition(433, 530);

	//blocks2[4].setSize(Vector2f(90, 40));
	//blocks2[4].setPosition(850, 450);




	Texture princessCoffinTex;
	princessCoffinTex.loadFromFile("princess_coffin.PNG");
	Sprite princessCoffin;
	princessCoffin.setTexture(princessCoffinTex);
	princessCoffin.setPosition(550, 350);
	princessCoffin.setScale(0.7, 0.7);


	/*Texture r[15];
		r[0].loadFromFile("jdfd");
		Sprite s;
		int i = 0;
			s.setTexture(r[i]);
			i++;
			i %= 15;*/

	SoundBuffer bufffer;
	bufffer.loadFromFile("yt5s.io_-_Scary_Ghost_Laugh_Sound_Effect_Free_No_Copyright_128_kbps.mp3");
	Sound sound;
	sound.setBuffer(bufffer);

	enemy ghost[4];

	Texture ghost_texture;
	ghost_texture.loadFromFile("enemy.png");

	for (int i = 0; i < 4; i++) // input  
	{
		ghost[i].shape.setTexture(ghost_texture);
		ghost[i].speed = rand() % (8 - 5 + 1) + 5;
		ghost[i].shape.setScale(0.8, 0.8);

		//int y = rand() % (500 - 10 + 1) + 10;

		if (i < 2)
		{
			ghost[0].shape.setPosition(0, 60);
			ghost[1].shape.setPosition(0, 300);

			ghost[i].shape.setTextureRect(IntRect(0, 0, 90.2, 99));
		} //first 2 ghost

		else
		{
			ghost[2].shape.setPosition(920, 242);
			ghost[3].shape.setPosition(920, 480);
			ghost[i].shape.setTextureRect(IntRect(90.2, 0, -90.2, 99));
		}//the other 2 ghost
	}

	Texture playertexture[2];
	playertexture[0].loadFromFile("mini.png");
	playertexture[1].loadFromFile("atackk sprite.png");

	Clock gameclock;

	if (player1.player.getTexture() == &playertexture[0])
		player1.player.setTextureRect(IntRect(0, 0, 65, 60));


	player1.setPlayer_intialization(playertexture[0]);
	player1.rect.left = 20;
	player1.rect.top = 350;

	Texture ghost2_texture;
	ghost2_texture.loadFromFile("enemy22.PNG");


	ghost2.shape.setTexture(ghost2_texture);
	ghost2.shape.setTextureRect(IntRect(0, 0, 96.17, 102));
	ghost2.shape.setPosition(405, 320);
	ghost2.shape.setScale(0.8, 0.8);

	ghost2.animation = 1.0;

	setPowerUps();

	while (window.isOpen())
	{
		//lives update
		health2 = to_string(player1.lives);
		lives.setString(health2);
		float time = gameclock.getElapsedTime().asMicroseconds();
		gameclock.restart();
		time /= 650;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
		// (Keyboard::isKeyPressed(Keyboard::K)) //take care !!!!!!!!
		{
			//eep(milliseconds(100));
			//k += 1;
			//ut << ghk;
		}
		if (player1.player.getGlobalBounds().intersects(door1.getGlobalBounds()) && player1.ghost1Killed >= 4)
		{
			cntr = 1;
		}

		for (int i = 2; i < 6; i++)
		{
			if (player1.player.getGlobalBounds().intersects(blocks1[i].getGlobalBounds()) && cntr == 0)
			{
				if ((player1.rect.left + 50 <= blocks1[i].getPosition().x + 20) || (player1.rect.left + 50.5 <= blocks1[i].getPosition().x + 20))
				{
					player1.rect.left = blocks1[i].getPosition().x - 50;
				}
				else if ((player1.rect.left >= blocks1[i].getPosition().x + blocks1[i].getSize().x - 20) || (player1.rect.left >= blocks1[i].getPosition().x + blocks1[i].getSize().x + 0.5 - 20))
					player1.rect.left = blocks1[i].getPosition().x + blocks1[i].getSize().x + 0;
				else
				{
					player1.moveY = 0.1;
					player1.is_grounded = true;
					if (player1.rect.top >= (blocks1[i].getPosition().y + blocks1[i].getSize().y - 0.7))
					{
						//player1.rect.top = (blocks[i].getPosition().y + blocks[i].getSize().y-0.72);
						//player1.moveY =1 ;
						player1.is_grounded = false;
						//player1.moveY += (0.001 * time);

					}
					else
					{
						player1.rect.top = blocks1[i].getPosition().y - 70;
						//player1.moveY += (0.001 * time);
						player1.is_grounded = true;


					}

				}
			}
		}

		for (int i = 0; i < 5; i++)
		{
			if (player1.player.getGlobalBounds().intersects(blocks2[i].getGlobalBounds()) && cntr == 1)
			{
				if (i != 2)
				{
					if ((player1.rect.left + 50 <= blocks2[i].getPosition().x + 20) || (player1.rect.left + 50.5 <= blocks2[i].getPosition().x + 20))
					{
						player1.rect.left = blocks2[i].getPosition().x - 50;
					}
					else if ((player1.rect.left >= blocks2[i].getPosition().x + blocks2[i].getSize().x - 20) || (player1.rect.left >= blocks2[i].getPosition().x + blocks2[i].getSize().x + 0.5 - 20))
						player1.rect.left = blocks2[i].getPosition().x + blocks2[i].getSize().x + 0;
					else
					{
						player1.moveY = 0;
						player1.is_grounded = true;
						if (player1.rect.top > (blocks2[i].getPosition().y + blocks2[i].getSize().y - 0.7))
						{
							//player1.rect.top = (blocks[i].getPosition().y + blocks[i].getSize().y-0.72);
							//player1.moveY = 1;
							player1.is_grounded = false;
							//player1.moveY += (0.001 * time);

						}
						else
						{
							player1.rect.top = blocks2[i].getPosition().y - 70;
							//player1.moveY += (0.001 * time);
							player1.is_grounded = true;


						}

					}
				}
			}
		}


		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			player1.moveX = 0.2;
			player1.lastKeyPressed = 1;

		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			player1.moveX = -0.2;
			player1.lastKeyPressed = 2;
		}
		if (player1.lastKeyPressed == 1)
		{
			player1.player.setTextureRect(IntRect(6 * 65, 0, 64, 60));
		}
		if (player1.lastKeyPressed == 2)
		{
			player1.player.setTextureRect(IntRect(6 * 65 + 64, 0, -64, 60));
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (player1.is_grounded)
			{
				player1.moveY = -0.6;

				player1.is_grounded = false;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::C))
		{
			//if (player1.player.getTexture() == &playertexture[1]);
			runNow = false;
			player1.rect.left += player1.moveX * time;
			player1.rect.top += player1.moveY * time;
			player1.currentframe += 0.015 * time;
			if (player1.currentframe > 8)
				player1.currentframe -= 8;

			{
				if (player1.moveX > 0)
				{
					player1.player.setTexture(playertexture[1]);
					player1.player.setTextureRect(IntRect(0 * 64, 0, 30, 60));
					player1.player.setTextureRect(IntRect(int(player1.currentframe) * 65, 0, 64, 60));

				}
				//player1.player.setTexture(playertexture[0]);
				if (player1.moveX < 0)
				{
					//player1.player.setTexture(playertexture[1]);
					//player1.player.setTextureRect(IntRect(0 * 64, 0, 30, 60));
					player1.player.setTextureRect(IntRect(int(player1.currentframe) * 65 + 64, 0, -64, 60));
				}
			}

			//player1.lastKeyPressed = 3;
		}


		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::C) {
				// Code to handle "C" key release
				runNow = true;
			}
		}

		//if (runNow)
		{
			//player1.player.setTexture(playertexture[0]);
		}

		if (player1.player.getGlobalBounds().intersects(princessCoffin.getGlobalBounds()) && ghost2killed)
		{
			princessCoffin.setScale(0, 0);
			cout << " ya mosahell" << pageNum << endl;
			pageNum = 1;
			cout << " ya mosahell" << pageNum << endl;
			cntr = 2;


		}

		game(ghost);
		game2(ghost2);
		fighting1(ghost, playertexture);
		fighting2(playertexture);

		respawn(timerADD, timerDELETE);
		powerupCollision();
		checkPowerup();
		resetspeedTime();






		player1.update(time, playertexture);
		window.clear();
		if (cntr == 0)
		{
			sound.play();
			window.draw(Backgrounds[0]);
			window.draw(live);
			window.draw(lives);
			//window.draw(door1);
			for (int i = 0; i < 4; i++) //drawing chracter
			{
				window.draw(ghost[i].shape);
			}


			for (int i = 0; i < powerupBag.size(); i++)
			{
				window.draw(powerupBag[i].powerUp);

			}
		}
		if (cntr == 1)
		{

			window.draw(Backgrounds[1]);
			window.draw(live);
			window.draw(lives);
			window.draw(princessCoffin);
			//for (int i = 0; i < 5; i++)
			{
				//window.draw(blocks2[i]);

			}
			window.draw(ghost2.shape); //big ghost

			for (int i = 0; i < powerupBag.size(); i++)
			{
				window.draw(powerupBag[i].powerUp);

			}
			//sleep(milliseconds(10));

			if (player1.rect.left >= RightWall)
			{
				player1.rect.left = 20;
				player1.rect.top = 0;
			}


		}


		window.draw(player1.player);

		if (cntr == 2)
		{
			puzzle();
			break;
		}

		window.display();

	}

}

void setPowerUps() {
	powerupsTexture[0].loadFromFile("elixir.PNG");
	powerupsTexture[1].loadFromFile("grapes.PNG");
	powerupsTexture[2].loadFromFile("jump_doubler_alone.PNG");
	//powerupsTexture[3].loadFromFile("player_protection.PNG");
	for (int i = 0; i < 2; i++)
	{
		powerUps[i].setTexture(powerupsTexture[i]);

	}
	powerUps[0].setScale(0.08, 0.08);
	powerUps[1].setScale(0.2, 0.2);
	powerUps[2].setScale(0.5, 0.5);





}
void respawn(Clock& timer_add, Clock& timer_delete)
{

	if (timer_add.getElapsedTime().asSeconds() >= 3) {
		int myPowerUpIndex = rand() % 3;
		help Help;
		Help.powerUp = powerUps[myPowerUpIndex];
		Help.R_positions.x = rand() % 1000;
		Help.R_positions.y = rand() % 500;
		Help.powerUp.setPosition(Help.R_positions.x, Help.R_positions.y);
		Help.x = myPowerUpIndex;
		powerupBag.push_back(Help);
		timer_add.restart();
	}
	if (timer_delete.getElapsedTime().asSeconds() >= 10)
	{
		if (!powerupBag.empty())
			powerupBag.erase(powerupBag.begin());
		timer_delete.restart();
	}

}
void powerupCollision()
{
	for (int i = 0; i < powerupBag.size(); i++)
	{
		if (player1.player.getGlobalBounds().intersects(powerupBag[i].powerUp.getGlobalBounds()))
		{
			player1.powerupType = powerupBag[i].x;
			powerupBag.erase(powerupBag.begin() + i);
		}
	}
}
void checkPowerup() {
	// 0--> exir 1-->grapes 2-->jump
	switch (player1.powerupType)
	{
	case 0:
		if (player1.lives <= 15)
		{
			player1.lives += 2;
			std::cout << "\n lives=" << player1.lives << "\n";
		}
		break;
	case 1:
		if (player1.lives < 15)
			player1.lives++;
		break;
	case 2:
	{
		player1.timeofspeed = 5;
		player1.speed = 1.8; }
	break;
	}
	player1.powerupType = -1;
}
void resetspeedTime() {
	if (player1.timeofspeed <= 0)
	{
		player1.timeofspeed = 0;
		player1.speed = 1;
		return;
	}
	else
	{
		player1.timeofspeed -= 0.01;
	}

}


void game(enemy ghost[])
{


	window.setFramerateLimit(60);


	for (int i = 0; i < 4; i++)
	{
		ghost[i].animation += 0.1;//??

		if (i < 2) {
			ghost[i].shape.move(ghost[i].speed, 0);
			if (ghost[i].shape.getPosition().x > 920)
			{
				//int y = rand() % (500) + 10;
				ghost[0].shape.setPosition(0, 60);
				ghost[1].shape.setPosition(0, 300);
				ghost[i].speed = rand() % (8 - 5 + 1) + 5;

			}//to return the character again to zero position

			/*if (player1.sprite.getGloableBounds().intersects(gh[i].shape.getGlobalBounds()))
			{
			  int y = rand() % (720) + 80;
				gh[i].shape.setPosition(0, y);
				gh[i].speed = rand() % (15 - 8 + 1) + 8;
			}*/

			ghost[i].shape.setTextureRect(IntRect(90.2 * int(ghost[i].animation), 0, 90.2, 99));
			if (ghost[i].animation > 4)
			{
				ghost[i].animation = 0;
			}//animating right-left character
		}
		else {
			ghost[i].shape.move(-ghost[i].speed, 0);
			if (ghost[i].shape.getPosition().x < 0)
			{
				//int y = rand() % (500) + 10;
				ghost[2].shape.setPosition(920, 242);
				ghost[3].shape.setPosition(920, 480);

				ghost[i].speed = rand() % (8 - 5 + 1) + 5;

			}//to return the character again to 920 position

		   /* if (player1.sprite.getGloableBounds().intersects(gh[i].shape.getGlobalBounds()))
			{
				int y = rand() % (720) + 80;
				gh[i].shape.setPosition(1200, y);
				gh[i].speed = rand() % (15 - 8 + 1) + 8;
			}*/

			ghost[i].shape.setTextureRect(IntRect(90.2 * int(ghost[i].animation) + 90.2, 0, -90.2, 99));
			if (ghost[i].animation > 4)
			{
				ghost[i].animation = 0;
			}//animating left-Right character

		}
	}
}

void game2(enemy& ghost2)
{
	for (int i = 0; i < 3; i++)
	{
		ghost2.animation += 0.01;
		ghost2.shape.setTextureRect(IntRect(96.17 * int(ghost2.animation), 0, 96.17, 102));
		if (ghost2.animation > 3)
		{
			ghost2.animation = 0;
		}//animating left-Right character
	}
}


void fighting1(enemy ghosts1[], Texture playertexture[])
{
	for (int i = 0; i < 4; i++)
	{
		if (player1.player.getTexture() == &playertexture[0])
		{
			if (player1.player.getGlobalBounds().intersects(ghosts1[i].shape.getGlobalBounds()))
			{
				// sleep(milliseconds(200));
				int y = rand() % (620) + 80;
				ghosts1[i].shape.setPosition(0, y);
				ghosts1[i].speed = rand() % (15 - 8 + 1) + 8;

				player1.lives -= 1;
				std::cout << "\n lives after colliding with the ghost" << (int)player1.lives << "\n";
				//if (player1.lives == 0)
					//window.close();
			}
		}
		else if ((player1.player.getTexture() == &playertexture[1]))
		{
			if (player1.player.getGlobalBounds().intersects(ghosts1[i].shape.getGlobalBounds())) {
				ghosts1[i].shape.setScale(0, 0);
				player1.ghost1Killed += 1; // TO OPEN THE DOOR 
				std::cout << "ghk1=" << player1.ghost1Killed;
			}

		}



	}


}
void fighting2(Texture playertexture[])
{
	float x = 0.8, y = 0.8;
	int collisionCounter = 0;
	if (cntr == 1)
	{
		if (player1.player.getTexture() == &playertexture[0])
		{
			if (player1.player.getGlobalBounds().intersects(ghost2.shape.getGlobalBounds()))
			{
				int y = rand() % (380) + 80;
				int x = rand() % (550) + 80;
				ghost2.shape.setPosition(x, y);
				//ghost2.shape.setPosition(500, 320);
				//sleep(milliseconds(200));
				//ghost2.shape.setPosition(405, 320);
				player1.lives -= 1;
				std::cout << "\n lives after colliding with the ghost" << player1.lives << "\n";
				if (player1.lives <= 0)
					std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
				//window.close();
			}
		}
		else if ((player1.player.getTexture() == &playertexture[1]))
		{
			if (player1.player.getGlobalBounds().intersects(ghost2.shape.getGlobalBounds()))
				/*x -= 0.2;
				y -= 0.2;
				ghost2.shape.setScale(x, y);
				cout << "<<<<" << x << y;*/
			{


				//collisionCounter++;
			//cout << "///////counterrrrr//////" <<  collisionCounter;
				int y = rand() % (380) + 80;
				int x = rand() % (550) + 80;
				ghost2.shape.setPosition(x, y);
				ghost2.health -= 5;
				std::cout << "///////ghost2 lives====//////" << ghost2.health << "//////////\n";

			}

		}
		if (ghost2.health <= 0)
		{
			ghost2.shape.setScale(0, 0);
			ghost2killed = true;
			//OPEN THE TOMB 
		}

	}
}
int puzzle()
{
	RenderWindow Puzzlewindow(sf::VideoMode(1185, 720), "WORD SEARCH GAME!");
	float rw = 230.f, rh = 225.0f, t = 5.0f;
	//Text tex[15];
	bool issel[15] = { 0 };

	sf::SoundBuffer sound1;
	if (!sound1.loadFromFile("success-fanfare-trumpets-6185.mp3"))
	{

	}

	Sound sound11;
	sound11.setBuffer(sound1);

	std::vector<RectangleInfo> r(15);


	sf::Vector2f positions[15] = {
	   {0, 0} , {236, 0} , {472, 0} , {708,0}, {944,0},
	   { 0, 240 } , {236, 240} , {472, 240} , {708,240}, {944,240},
	 { 0, 480 } , {236, 480} , {472, 480} , {708,480}, {944,480}
	};

	Font f;
	if (!f.loadFromFile("Twelny.ttf")) {
		return 1;
	}

	for (int i = 0; i < 15; i++) {
		r[i].shape.setSize(sf::Vector2f(rw, rh));
		r[i].shape.setFillColor(sf::Color::Black);
		r[i].shape.setPosition(positions[i]);
		r[i].shape.setOutlineThickness(t);
		r[i].shape.setOutlineColor(Color::White);
		tex[i].setFont(f);
		tex[i].setFillColor(Color(155, 195, 146));
		tex[i].setCharacterSize(100);

		r[i].isClicked = 0;
		r[i].isclickable = 1;   // initially, all frectangles are clickable
		r[i].isspecific1 = 0;   // initially, no rectangles are specific
		r[i].isspecific2 = 0;   // initially, no rectangles are specific
		r[i].isspecific3 = 0;   // initially, no rectangles are specific
	}


	tex[0].setString("E");
	tex[0].setPosition(100, 50);
	//
	tex[1].setString("M");
	tex[1].setPosition(320, 50);
	//
	tex[2].setPosition(575, 50);
	tex[2].setString("I");
	//
	tex[3].setPosition(805, 50);
	tex[3].setString("R");
	//
	tex[4].setPosition(1035, 50);
	tex[4].setString("C");
	//
	tex[5].setPosition(100, 295);
	tex[5].setString("D");
	//
	tex[6].setPosition(330, 295);
	tex[6].setString("H");
	//
	tex[7].setPosition(560, 293);
	tex[7].setString("J");
	//
	tex[8].setPosition(805, 290);
	tex[8].setString("L");
	//
	tex[9].setPosition(1035, 290);
	tex[9].setString("T");
	//
	tex[10].setPosition(100, 520);
	tex[10].setString("E");
	//
	tex[11].setPosition(335, 520);
	tex[11].setString("A");
	//
	tex[12].setPosition(565, 520);
	tex[12].setString("D");
	//
	tex[13].setPosition(800, 520);
	tex[13].setString("O");
	//
	tex[14].setPosition(1035, 520);
	tex[14].setString("S");

	// clicking on rectangles
	vector<char> input;
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(Puzzlewindow);

		{
			for (int i = 0; i < 15; i++) {
				if (!r[i].isClicked)
					r[i].isClicked = 1;

			}
		}
	}
	//
	//RectangleShape mou(Vector2f(13, 13));
	mou.setFillColor(sf::Color(246, 244, 245));
	int currentRectIndex = 0;

	//Define the indices of the specific rectangles for word 1
	vector<int> specificrectindices1 = { 8, 13 , 14 , 9 };
	int numspecificclicked1 = 0;  //track the num of specific rect clicked
	bool clickedonword1letters = 0;
	bool finish1 = 0;
	bool soundplayed = 0;
	r[8].isspecific1 = 1;
	r[9].isspecific1 = 1;
	r[13].isspecific1 = 1;
	r[14].isspecific1 = 1;

	//Define the indices of the specific rectangles word 2
	vector<int> specificrectindices2 = { 1, 2 , 3 , 4 , 0 };
	int numspecificclicked2 = 0;  //track the num of specific rect clicked
	bool clickedonword2letters = 0;
	bool finish2 = 0;
	r[1].isspecific2 = 1;
	r[2].isspecific2 = 1;
	r[3].isspecific2 = 1;
	r[4].isspecific2 = 1;
	r[0].isspecific2 = 1;

	//Define the indices of the specific rectangles word 3
	vector<int> specificrectindices3 = { 11, 12 , 5 , 10 };
	int numspecificclicked3 = 0;  //track the num of specific rect clicked
	bool clickedonword3letters = 0;
	bool finish3 = 0;
	r[11].isspecific3 = 1;
	r[12].isspecific3 = 1;
	r[5].isspecific3 = 1;
	r[10].isspecific3 = 1;

	vector<int> clickedspecificrects1; //keep track of clicked specific rectangles
	vector<int> clickedspecificrects2; //keep track of clicked specific rectangles
	vector<int> clickedspecificrects3; //keep track of clicked specific rectangles
	while (Puzzlewindow.isOpen())
	{
		//Get the mouse position relative to the window
		sf::Vector2i mousePos = sf::Mouse::getPosition(Puzzlewindow);


		sf::Event event;
		while (Puzzlewindow.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				Puzzlewindow.close();

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					// Get the mouse position relative to the window
				   // sf::Vector2i mousePos = sf::Mouse::getPosition(window);


					for (int i = 0; i < 15; i++) {
						if (r[i].shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
							issel[i] = !issel[i];
							if (issel[i] && r[i].isspecific1) {
								clickedspecificrects1.push_back(i);
								std::cout << " pushhh11111";
							}
							if (issel[i] && r[i].isspecific2) {
								clickedspecificrects2.push_back(i);
								std::cout << " pushhh22222" << endl;
							}
							if (issel[i] && r[i].isspecific3) {
								clickedspecificrects3.push_back(i);
								std::cout << " pushhh33333333" << endl;
							}
						}
					}
				}
				// Iterate through the rectangles
				for (int i = 0; i < 15; i++) {
					if (r[i].shape.getGlobalBounds().contains(mousePos.x, mousePos.y) && r[i].isclickable) {
						if (r[i].isclickable) {
							r[i].isClicked = 1;
							std::cout << "found";

							//check if the clicked rect contain the 1st word letter or not
				  //1
							if (find(specificrectindices1.begin(), specificrectindices1.end(), i) != specificrectindices1.end()) {
								numspecificclicked1++;
								std::cout << numspecificclicked1;
								clickedonword1letters = 1;

							}
							else if (find(specificrectindices1.begin(), specificrectindices1.end(), i) == specificrectindices1.end() && clickedonword1letters && !finish1) {
								//user clicked on a rectangle from another word before finishing all word 1 letters
								numspecificclicked1 = 0;

								//revert the color of clicked rect to black
								for (int j : clickedspecificrects1) {
									issel[j] = 0;
									r[j].shape.setFillColor(Color::Black);
									std::cout << " uuuuuuuuuu" << endl;

								}

								std::cout << " kkkkkkkkkkkk";
							}

							// check if the user has clicked on all specific rectangles
							if (numspecificclicked1 == specificrectindices1.size()) {
								// change the color of the specific rectangles to green
								for (int j : specificrectindices1) {
									r[j].isclickable = 0; // disable further clicks on specific rectangles
									r[j].shape.setFillColor(Color(26, 76, 28));
									std::cout << "XXXXXXXXXX";
								}
								finish1 = 1;
							}

							//2  
									   //check if the clicked rect  contain the 2nd word letters or not
							if (find(specificrectindices2.begin(), specificrectindices2.end(), i) != specificrectindices2.end()) {
								numspecificclicked2++;
								std::cout << numspecificclicked2;
								clickedonword2letters = 1;
							}
							else if (find(specificrectindices2.begin(), specificrectindices2.end(), i) == specificrectindices2.end() && clickedonword2letters && !finish2) {
								//user clicked on a rectangle from another word before finishing all word 1 letters
								numspecificclicked2 = 0;
								//revert the color of clicked rect to black
								for (int j : clickedspecificrects2) {
									issel[j] = 0;
									r[j].shape.setFillColor(Color::Black);
									std::cout << " uuuuuuuuuu" << endl;
								}
								std::cout << " kkkkkkkkkkkk";
							}

							// check if the user has clicked on all specific rectangles
							if (numspecificclicked2 == specificrectindices2.size()) {

								// change the color of the specific rectangles to green
								for (int j : specificrectindices2) {
									r[j].isclickable = 0; // disable further clicks on specific rectangles
									r[j].shape.setFillColor(Color(26, 76, 28));
									std::cout << "XXXXXXXXXX";
								}
								finish2 = 1;
							}
							//3   
										//check if the clicked rect contain the 3rd word letter or not
							if (find(specificrectindices3.begin(), specificrectindices3.end(), i) != specificrectindices3.end()) {
								numspecificclicked3++;
								r[i].isspecific3 = 1;
								std::cout << numspecificclicked3;
								clickedonword3letters = 1;
							}
							else if (find(specificrectindices3.begin(), specificrectindices3.end(), i) == specificrectindices3.end() && clickedonword3letters && !finish3) {
								//user clicked on a rectangle from another word before finishing all word 1 letters
								numspecificclicked3 = 0;
								//revert the color of clicked rect to black
								for (int j : (clickedspecificrects3)) {
									issel[j] = 0;
									r[j].shape.setFillColor(Color::Black);
									std::cout << " uuuuuuuuuu" << endl;
								}
								std::cout << " kkkkkkkkkkkk";
							}
							// check if the user has clicked on all specific rectangles
							if (numspecificclicked3 == specificrectindices3.size()) {
								//  sound11.play();
								  // change the color of the specific rectangles to green
								for (int j : specificrectindices3) {
									r[j].isclickable = 0; // disable further clicks on specific rectangles
									r[j].shape.setFillColor(Color(26, 76, 28));
									std::cout << "XXXXXXXXXX";
								}
								finish3 = 1;

							}

						}
					}
				}
				// play the sound when the user find all the words 
				if (finish1 && finish2 && finish3 && !soundplayed) {
					sound11.play();
					soundplayed = 1;
				}
			}
		}
		// Set the position of the rectangle to be the same as the mouse position
		mou.setPosition(static_cast<sf::Vector2f>(mousePos));

		// Change color back to original
		////////////////////////////clicking on rectangles code is below
		Puzzlewindow.clear();
		for (int i = 0; i < 15; i++) {
			if ((issel[i]) && (r[i].isclickable == 1)) {
				r[i].shape.setFillColor(sf::Color(50, 50, 50));
			}
			else if ((!issel[i]) && (r[i].isclickable == 1)) {
				r[i].shape.setFillColor(sf::Color::Black);
			}
		}
		for (int i = 0; i < 15; ++i) {
			Puzzlewindow.draw(r[i].shape);

			Puzzlewindow.draw(tex[i]);
		}
		Puzzlewindow.draw(mou);
		Puzzlewindow.display();

	}
	return 0;
}