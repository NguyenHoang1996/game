#include "Global.h"
#include "Sprite.h"
#include <stdlib.h>
#include <string>
class UI : public Sprite
{
public:
	UI();
	UI(LPWSTR filePath, int totalFrames = 1, int cols = 1) :Sprite(filePath, totalFrames, cols) {
	};
public:
	ID3DXFont *font;
	std::string messageFront;
	char* time;
	RECT fRectangle1;
	void CreateFontUI();
	void WriteFont(int);
};