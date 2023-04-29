#include "Button.h"

Slider::Slider() {
}

Slider::Slider(const std::string& iconImagePath, const std::string& trackerImagePath, const std::string& buttonImagePath, const SDL_Rect& trackerRect) {
}

Slider::~Slider() {
}

SDL_Texture* Slider::loadImage(const std::string& imagePath) const {
    return nullptr;
}

void Slider::initIconRect(const SDL_Rect& rect) {
}

void Slider::initButtonRect(const SDL_Rect& rect) {
}

void Slider::setButtonRectX(int x) {
}

SDL_Rect Slider::getButtonRect() const {
    return SDL_Rect();
}

int Slider::getValueFromSlider() const {
    return 0;
}

Slider& Slider::operator=(const Slider& slider) {
    // TODO: insert return statement here
    return *this;
}

TextObject::TextObject() {
}

TextObject::TextObject(const std::string& value, const std::vector<int>& rgb, int size, const std::string& font, const SDL_Rect& rect) {
}

TextObject::~TextObject() {
}

void TextObject::setValue(const std::string& value) {
}

void TextObject::setRGB(const std::vector<int>& rgb) {
}

void TextObject::setSize(int size) {
}

void TextObject::setFont(const std::string& font) {
}

void TextObject::setRectangle(const SDL_Rect& rect) {
}

std::string TextObject::getValue() const {
    return std::string();
}

std::vector<int> TextObject::getRGB() const {
    return std::vector<int>();
}

int TextObject::getSize() const {
    return 0;
}

std::string TextObject::getFont() const {
    return std::string();
}

SDL_Rect TextObject::getRectangle() {
    return SDL_Rect();
}

TextObject& TextObject::operator=(const TextObject& text) {
    // TODO: insert return statement here
    return *this;
}
