#pragma once

class GLFWwindow;

class Application
{
private:
	GLFWwindow* window;

private:
	float latestFrameTime = 0.0f;
	float deltaTime = 0.0f;

private:
	float cursorX = 0.0f;
	float cursorY = 0.0f;
	float cursorDeltaX = 0.0f;
	float cursorDeltaY = 0.0f;

public:
	Application(const char* title, int windowWidth, int windowHeight);
	~Application();

	void RunLoop();
	virtual void OnUpdate(const float& deltaTime) {}

	void CloseWindow();
	virtual void OnShutdown() {}

public:
	inline float GetLatestFrameTime() const { return latestFrameTime; };
	inline float GetDeltaTime() const { return deltaTime; }

public:
	inline float GetCursorX() const { return cursorX; }
	inline float GetCursorY() const { return cursorY; }
	void GetCursor(float& cursorX, float& cursorY) const;

	inline float GetCursorDeltaX() const { return cursorDeltaX; }
	inline float GetCursorDeltaY() const { return cursorDeltaY; }
	void GetCursorDelta(float& deltaX, float& deltaY) const;

public:
	// Events.
	virtual void OnWindowResized(int newWidth, int newHeight) {}

	virtual void OnKeyPressed(int key) {}
	virtual void OnKeyReleased(int key) {}
	virtual void OnKeyHeld(int key) {}

	virtual void OnMousePressed(int button) {}
	virtual void OnMouseReleased(int button) {}
	virtual void OnCursorMove(double newPositionX, double newPositionY) {}
};