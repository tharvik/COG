#pragma once

/// Render the univers
class Renderer {
private:
	void setUpOpenGL();
	
public:
	/// Default constructor
	Renderer();

	/// Render the whole universe to screen
	void render() const;
};
