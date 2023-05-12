#include "Button.h"

//Slider::Slider() {
//}
//
//Slider::Slider(const std::string& iconImagePath, const std::string& trackerImagePath, const std::string& buttonImagePath, const SDL_Rect& trackerRect) {
//}
//
//Slider::~Slider() {
//}
//
//SDL_Texture* Slider::loadImage(const std::string& imagePath) const {
//    return nullptr;
//}
//
//void Slider::initIconRect(const SDL_Rect& rect) {
//}
//
//void Slider::initButtonRect(const SDL_Rect& rect) {
//}
//
//void Slider::setButtonRectX(int x) {
//}
//
//SDL_Rect Slider::getButtonRect() const {
//    return SDL_Rect();
//}
//
//int Slider::getValueFromSlider() const {
//    return 0;
//}
//
//Slider& Slider::operator=(const Slider& slider) {
//    // TODO: insert return statement here
//    return *this;
//}
//
//TextObject::TextObject() {
//}
//
//TextObject::TextObject(const std::string& value, const std::vector<int>& rgb, int size, const std::string& font, const SDL_Rect& rect) {
//}
//
//TextObject::~TextObject() {
//}
//
//void TextObject::setValue(const std::string& value) {
//}
//
//void TextObject::setRGB(const std::vector<int>& rgb) {
//}
//
//void TextObject::setSize(int size) {
//}
//
//void TextObject::setFont(const std::string& font) {
//}
//
//void TextObject::setRectangle(const SDL_Rect& rect) {
//}
//
//std::string TextObject::getValue() const {
//    return std::string();
//}
//
//std::vector<int> TextObject::getRGB() const {
//    return std::vector<int>();
//}
//
//int TextObject::getSize() const {
//    return 0;
//}
//
//std::string TextObject::getFont() const {
//    return std::string();
//}
//
//SDL_Rect TextObject::getRectangle() {
//    return SDL_Rect();
//}
//
//TextObject& TextObject::operator=(const TextObject& text) {
//    // TODO: insert return statement here
//    return *this;
//}
//Button::Button() {
//	this->pathImage = "";
//	this->rect = SDL_Rect();
//}
//Button::Button(const SDL_Rect& rect, const std::string& pathImage) {
//	this->rect = rect;
//	this->pathImage = pathImage;
//}
//Button::~Button() {
//	this->pathImage.clear();
//}
//void Button::setRectangle(const SDL_Rect& rect) {
//	this->rect = rect;
//}
//void Button::setPathImage(const std::string& pathImage) {
//	this->pathImage = pathImage;
//}
//std::string Button::getPathImage() {
//	return this->pathImage;
//}
//SDL_Rect Button::getRectangle() {
//	return this->rect;
//}
//void Button::render(SDL_Renderer* renderer) {
//	SDL_Surface* image = IMG_Load(this->pathImage.c_str());
//	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
//	SDL_FreeSurface(image);
//	SDL_RenderCopy(renderer, texture, &this->rect, nullptr);
//}
//Button& Button::operator=(const Button& button) {
//	this->pathImage = button.pathImage;
//	this->rect = button.rect;
//	return *this;
//}
//
Image::Image() {
	this->pathImage = "";
	this->rect = { 0,0,0,0 };
}
Image::Image(const SDL_Rect& rect, const std::string& pathImage) {
	this->rect = rect;
	this->pathImage = pathImage;
}
Image::~Image() {
	this->pathImage.clear();
}
SDL_Rect Image::getRectangle() {
	return this->rect;
}
void Image::renderImage(SDL_Renderer* renderer) {
	SDL_Surface* img = IMG_Load(this->pathImage.c_str());
	if (!img) {
		std::cout << "can't load\n";
		return;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img);
	SDL_FreeSurface(img);
	SDL_RenderCopy(renderer, texture, nullptr, &this->rect);
	SDL_RenderPresent(renderer);
}
Image& Image::operator=(const Image& img) {
	this->pathImage = img.pathImage;
	this->rect = img.rect;
	return *this;
}