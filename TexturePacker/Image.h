#pragma once

#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include <thread>

class Image {

public:
	Image(std::string file);
	~Image();
	bool load();
	void crop();
	void scale(float amount);
	void scale2(float amount);
	void scale3(float amount);
	


	sf::Image * getImage() const;

	void setPixelArray();
private:
	std::string file;
	sf::Image * image;

	void findTop(unsigned int * top);
	void findBottom(unsigned int * bottom);
	void findLeft(unsigned int * left);
	void findRight(unsigned int * right);

	std::vector<sf::Vector2u> getNeighbourPixels(sf::Image * img, unsigned int x, unsigned int y, float step);
	bool pixelFits(sf::Image * img, unsigned int x, unsigned int y);
	bool hasPixel(unsigned int x, unsigned int y);
	void scale3placePixels(sf::Image * tempImage, unsigned int y1, unsigned int y2, float amount);

	
	sf::Uint8 * pixelArray;
	int pixelsCount = 0;
	
};