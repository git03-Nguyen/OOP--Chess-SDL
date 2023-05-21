#include "Button.h"

//Slider::Slider() {
//}
//
//Slider::Slider(const std::string& iconimagePath, const std::string& trackerimagePath, const std::string& buttonimagePath, const SDL_Rect& trackerRect) {
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
//	this->imagePath = "";
//	this->rect = SDL_Rect();
//}
//Button::Button(const SDL_Rect& rect, const std::string& imagePath) {
//	this->rect = rect;
//	this->imagePath = imagePath;
//}
//Button::~Button() {
//	this->imagePath.clear();
//}
//void Button::setRectangle(const SDL_Rect& rect) {
//	this->rect = rect;
//}
//void Button::setimagePath(const std::string& imagePath) {
//	this->imagePath = imagePath;
//}
//std::string Button::getimagePath() {
//	return this->imagePath;
//}
//SDL_Rect Button::getRectangle() {
//	return this->rect;
//}
//void Button::render(SDL_Renderer* renderer) {
//	SDL_Surface* image = IMG_Load(this->imagePath.c_str());
//	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
//	SDL_FreeSurface(image);
//	SDL_RenderCopy(renderer, texture, &this->rect, nullptr);
//}
//Button& Button::operator=(const Button& button) {
//	this->imagePath = button.imagePath;
//	this->rect = button.rect;
//	return *this;
//}
//
Image::Image() {
	this->rect = { 0,0,0,0 };
	this->texture = nullptr;
	//this->img = nullptr;
}
Image::Image(SDL_Rect rect, const std::string& imagePath) {
	this->rect = rect;
	this->texture = nullptr;
	//
	SDL_Surface* img = IMG_Load(imagePath.c_str());
	if (!img) {
		std::cout << "can't load\n";
		return;
	}
	this->texture = SDL_CreateTextureFromSurface(Window::renderer, img);
	SDL_FreeSurface(img);
}
Image::~Image() {
	//SDL_FreeSurface(this->img);
	//this->img = nullptr;
	SDL_DestroyTexture(this->texture);
	this->texture = nullptr;
}
SDL_Rect Image::getRectangle() {
	return this->rect;
}
void Image::setRectangle(SDL_Rect rect) {
	this->rect = rect;
}
void Image::renderImage() {
	if (!texture || !(&rect) || !Window::renderer) std::cout << "ERROR\n";
	SDL_RenderCopy(Window::renderer, this->texture, nullptr, &this->rect);
}
void Image::makeBlend(int opacity) {
	SDL_SetTextureAlphaMod(this->texture, opacity);
}
void Image::destroy() {
	//SDL_FreeSurface(this->img);
	//this->img = nullptr;
	SDL_DestroyTexture(this->texture);
	this->texture = nullptr;
}
