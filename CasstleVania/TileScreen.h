#include "Sprite.h"
#include "d3d9.h"
#include "d3dx9.h"
#include "Scene.h"
#include "Global.h"
#include "Input.h"
class TileScreen : public Scene
{
public:

	TileScreen();
	~TileScreen();
	bool isDisplay = false;
	bool isPressS = false;
	float timeToViewStageDelay = 1.0f;
	float startTimeDelay = 0.0f;

	bool viewEnd;
	Sprite* blackBoard;
	// override parent methods
	int init() override;
	void updateInput(float dt) override;
	void update(float dt) override;
	void draw() override;
	void release() override;

};