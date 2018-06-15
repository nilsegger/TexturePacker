#include "Spritesheetmaker.h"

SpriteSheet::SpriteSheet(sf::Vector2u size, std::vector<Image*> images)
	:size(size), images(images)
{
	spritesheet = new sf::Image;
	spritesheet->create(size.x, size.y, sf::Color::Transparent);
	placeImages();
}

sf::Image * SpriteSheet::getSpritesheet()
{
	return spritesheet;
}

void SpriteSheet::placeImages()
{
	unsigned int x = 0, y = 0;
	unsigned int rowHeight = 0;
	for (int i = 0; i < int(images.size()); i++) {
		sf::Image * image = images[i]->getImage();

		if (!imageFits(image,x,y)) {
			y += rowHeight + padding;
			rowHeight = 0;
			x = 0;
			if (imageFits(image, x, y)) {
				placeImage(image, x, y);
				rowHeight = image->getSize().y;
				x += padding + image->getSize().x;
				rowHeight = image->getSize().y;
			}
			else {
				std::cout << "Images dont fit... At image " << i + 1 << "of" << int(images.size()) << std::endl;
				saveSpritesheet();
				return;
			}
		}
		else if (imageFits(image,x,y)) {
			placeImage(image, x, y);
			x += padding + image->getSize().x;
			if (image->getSize().y > rowHeight) rowHeight = image->getSize().y;
		}
		/*
			Place pixels
			set offset
			check whetever everything fits
			padding?

		*/
		delete image;
	}
	//saveSpritesheet();
}

void SpriteSheet::placeImage(sf::Image * image, unsigned int x, unsigned int y)
{
	for (unsigned int ix = 0; ix < image->getSize().x; ix++) {
		for (unsigned int iy = 0; iy < image->getSize().y; iy++) {
			spritesheet->setPixel(x + ix, y + iy, image->getPixel(ix, iy));
		}
	}
}

bool SpriteSheet::imageFits(sf::Image * image, unsigned int x, unsigned int y)
{
	return (x + image->getSize().x < spritesheet->getSize().x && y + image->getSize().y < spritesheet->getSize().y);
}

void SpriteSheet::saveSpritesheet(std::string path)
{
	std::cout << "Saving..." << std::endl;
	if(spritesheet->saveToFile(path)) std::cout << "Saved spritesheet to " << path << std::endl;
	else std::cout << "Failed to save spritesheet." << std::endl;
	delete spritesheet;
}
