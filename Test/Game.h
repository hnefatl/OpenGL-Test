#ifndef _GAME_H
#define _GAME_H

class Game
{
public:
	Game();
	Game(float RotationSpeed);

	bool Init();
	void Update();
	void Render();
	void Shutdown();

	void OnResize(int Width, int Height);

	void SetRotationSpeed(float Speed);
	const float GetRotationSpeed();

	void SetRotationAngle(float Angle);
	const float GetRotationAngle();

private:
	float m_RotationAngle;
	float m_RotationSpeed;
};

#endif