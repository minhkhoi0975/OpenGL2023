#pragma once

class GLFWwindow;

class Application
{
private:
	GLFWwindow* window;

private:
	/// <summary>
	/// The time, in seconds, of the latest frame.
	/// </summary>
	float latestFrameTime = 0.0f;

	/// <summary>
	/// Time between consecutive frames, in seconds.
	/// </summary>
	float deltaTime = 0.0f;

private:
	float cursorX;
	float cursorY;
	float cursorDeltaX;
	float cursorDeltaY;

public:
	Application(const char* title, int windowWidth, int windowHeight);
	~Application();

	void RunLoop();
	virtual void OnUpdate();

	/// <summary>
	/// Tells GLFW to close the window.
	/// </summary>
	void CloseWindow();

	/// <summary>
	/// Called before GLFW is terminated.
	/// </summary>
	virtual void OnShutdown();

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
	virtual void OnWindowResized(int newWidth, int newHeight);

	virtual void OnKeyPressed(int key);
	virtual void OnKeyReleased(int key);
	virtual void OnKeyHeld(int key);

	virtual void OnMousePressed(int button);
	virtual void OnMouseReleased(int button);
	virtual void OnCursorMove(double newPositionX, double newPositionY);
};