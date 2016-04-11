#pragma once

class GameState {
public:
	GameState();
	~GameState();
private:
	virtual bool update() = 0;
};