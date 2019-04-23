#include <Adafruit_SSD1331.h>
#include <Adafruit_GFX.h>
#include <SPI.h>

#define WIDTH 96
#define HEIGHT 64

#define SPRITE_SIZE 16
#define SPRITE_RES 256

#define sclk 18 // 18
#define mosi 23 // 23
#define cs   17
#define rst  4
#define dc   16

//SPRITES

//PLAYER

bool player_alpha_map[SPRITE_RES] =
{
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0,
0,0,1,1,1,1,1,1,1,1,1,0,1,1,0,0,
0,0,1,1,1,1,1,1,1,1,1,0,1,1,0,0,
0,0,1,1,1,1,1,0,0,1,1,0,1,1,0,0,
0,0,1,1,1,1,1,1,1,1,1,0,1,1,0,0,
0,0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,
0,0,1,1,0,0,1,1,1,1,1,1,1,1,0,0,
0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

uint16_t player_texture[SPRITE_RES] =
{
0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0xF800,0xF800,0x0000,0x0000,0x0000,0x0000,0xF800,0xF800,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xF800,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xF800,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0x0000,0x0000,0x0000,0xF800,0xF800,0x0000,0x0000,0xF800,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xF800,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xF800,0xF800,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0xF800,0xF800,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,
0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF,0x5AFF
};

// END PLAYER

//MAIN VARIABLES

Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, mosi, sclk, rst);
//Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, rst);

//Create a empty buffer frame for the display
uint16_t bufferTexture[WIDTH * HEIGHT];

//Gets the position of a pixel in 2D coordinates inside the buffer frame
uint16_t posBuffer(uint16_t x, uint16_t y) {
	return x + WIDTH * y;
}

//Gets the position of a pixel in 2D coordinated inside a single dimension array with a certain x(Width) size
uint16_t posBuffer(uint16_t x, uint16_t y, uint16_t xSize) {
	return x + xSize * y;
}

void copyTexture(uint16_t texOrigin[], uint16_t texDestiny[]) {
	for (uint16_t index = 0; index < SPRITE_RES; index++)
	{
		texDestiny[index] = texOrigin[index];
	}
}

void copyAlphaMap(bool alphaTexOrigin[], bool alphaTexDestiny[]) {
	for (uint16_t index = 0; index < SPRITE_RES; index++)
	{
		alphaTexOrigin[index] = alphaTexDestiny[index];
	}
}

class Object {

public:

	int8_t posX, posY;

};

class Renderer : public Object {

public:

	//Dedicate space for a single texture on this renderer
	uint16_t texture[SPRITE_RES];

	bool alphaMap[SPRITE_RES];

	virtual void draw() {
		//Determine the starting position of this texture to draw considering it's central pivot
		int16_t bufferStartX = posX - (SPRITE_SIZE / 2);
		int16_t bufferStartY = posY + (SPRITE_SIZE / 2);

		for (uint16_t x = 0; x < SPRITE_SIZE; x++)
		{
			for (uint16_t y = 0; y < SPRITE_SIZE; y++)
			{
				int16_t renderPosX = bufferStartX + x;
				int16_t renderPosY = bufferStartX + y;
				//If these pixels are out of bounds then skip them
				if (renderPosX < 0 || renderPosX > WIDTH || renderPosY < 0 || renderPosY > HEIGHT) continue;
				//Draws on the buffer texture the texture given to this object
				bufferTexture[posBuffer(renderPosX, renderPosY)] = texture[posBuffer(x, y, SPRITE_SIZE)];
			}
		}
	}
};

class GameObject : public Renderer {
	
public:

	virtual void start() {

	}


	virtual void update() {

	}

};

class Player : public GameObject {

public:
	
	uint8_t movementSpeed = 2;
	int8_t xSpeed, ySpeed;

	void start() {
		
		posX = 0;
		posY = 0;

		copyTexture(player_texture, texture);
		//copyAlphaMap(player_alpha_map, alphaMap);
		
		for (uint16_t i = 0; i < SPRITE_RES; i++)
		{
			Serial.println(texture[i], HEX);
		}
	}

	void update() {
		
		if (posX - xSpeed <= 0) {
			xSpeed = movementSpeed;
		}

		if (posX + xSpeed >= WIDTH) {
			xSpeed = -movementSpeed;
		}

		if (posY - ySpeed <= 0) {
			ySpeed = movementSpeed;
		}

		if (posY + ySpeed >= HEIGHT) {
			ySpeed = -movementSpeed;
		}

		posX += xSpeed;
		posY += ySpeed;
		
	}

} player;

void setup() {
	Serial.begin(115200);

	display.begin();

	player.start();

	//display.fillScreen(0xFFFF);
}

// the loop function runs over and over again until power down or reset
void loop() {
	//Clear bufferframe
	for (uint16_t i = 0; i < WIDTH * HEIGHT; i++)
	{
		bufferTexture[i] = 0x0000;
	}
	//Game code...
	//display.fillScreen(random(0, 65535));

	player.update();

	player.draw();

	//Draw texture to display
	display.drawRGBBitmap(0, 0, bufferTexture, WIDTH, HEIGHT);
}
