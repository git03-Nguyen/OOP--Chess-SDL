#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "Window.h"
#include "Pieces.h"

//class TextObject {
//private:
//	std::string value;
//	std::vector<int> rgb;
//	int size;
//	std::string font;
//	SDL_Rect rect;
//public:
//	TextObject();
//	TextObject(const std::string& value, const std::vector<int>& rgb, int size, const std::string& font, const SDL_Rect& rect);
//	virtual ~TextObject();
//
//	void setValue(const std::string& value);
//	void setRGB(const std::vector<int>& rgb);
//	void setSize(int size);
//	void setFont(const std::string& font);
//	void setRectangle(const SDL_Rect& rect);
//
//	std::string getValue() const;
//	std::vector<int> getRGB() const;
//	int getSize() const;
//	std::string getFont() const;
//	SDL_Rect getRectangle();
//
//	TextObject& operator = (const TextObject& text);
//};

//class Button {
//private:
//	std::string imagePath;
//	SDL_Rect rect;
//public:
//	Button();
//	Button(const SDL_Rect& rect, const std::string& imagePath);
//	virtual ~Button();
//
//	void setRectangle(const SDL_Rect& rect);
//	void setimagePath(const std::string& imagePath);
//	SDL_Rect getRectangle();
//	std::string getimagePath();
//	void render(SDL_Renderer* renderer);
//	Button& operator = (const Button& button);
//};
class Image {
private:
	SDL_Rect rect;
	SDL_Texture* texture;
	//SDL_Surface* img;
public:
	Image();
	Image(SDL_Rect rect, const std::string& imagePath);
	~Image();
	SDL_Rect getRectangle();
	void setRectangle(SDL_Rect rect);
	void makeBlend(int opacity);
	void renderImage();
	void destroy();
};

//class Slider {
//private:
//	SDL_Texture* icon;
//	SDL_Rect iconRect;
//	SDL_Texture* trackerTexture;
//	SDL_Rect trackerRect;
//	SDL_Texture* buttonTexture;
//	SDL_Rect buttonRect;
//
//public:
//	Slider();
//	Slider(const std::string& iconImagePath, const std::string& trackerImagePath, const std::string& buttonImagePath, const SDL_Rect& trackerRect);
//	virtual ~Slider();
//
//	SDL_Texture* loadImage(const std::string& imagePath) const;
//	void initIconRect(const SDL_Rect& rect);
//	void initButtonRect(const SDL_Rect& rect);
//	void setButtonRectX(int x);
//	SDL_Rect getButtonRect() const;
//	int getValueFromSlider() const;
//
//	Slider& operator = (const Slider& slider);
//};
