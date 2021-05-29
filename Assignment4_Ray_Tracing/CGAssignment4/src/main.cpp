/*The MIT License (MIT)

Copyright (c) 2021-Present, Wencong Yang (yangwc3@mail2.sysu.edu.cn).

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.*/

#include <array>
#include <vector>
#include <thread>
#include <iostream>

#include "WindowsApp.h"
#include "vec3.h"
#include "ray.h"

typedef std::array<float, 3> Pixel;					//RGB pixel
static std::vector<std::vector<Pixel>> gCanvas;		//Canvas

// The width and height of the screen
constexpr int gHeight = 400;
constexpr int gWidth  = 800;

void rendering();

int main(int argc, char* args[])
{
	// Create window app handle
	WindowsApp::ptr winApp = WindowsApp::getInstance(gWidth, gHeight, "CGAssignment4: Ray Tracing");
	if (winApp == nullptr)
	{
		std::cerr << "Error: failed to create a window handler" << std::endl;
		return -1;
	}

	// Memory allocation for canvas
	gCanvas.resize(gHeight, std::vector<Pixel>(gWidth));

	// Launch the rendering thread
	// Note: we run the rendering task in another thread to avoid GUI blocking
	std::thread renderingThread(rendering);

	// Window app loop
	while (!winApp->shouldWindowClose())
	{
		// Process event
		winApp->processEvent();

		// Display to the screen
		winApp->updateScreenSurface(gCanvas);

	}

	renderingThread.join();

	return 0;
}

void writeRGBToCanvas(const float &r, const float &g, const float &b, int x, int y)
{
	// Out-of-range detection
	if (x < 0 || x >= gWidth)
	{
		std::cerr << "Warnning: try to write the pixel out of range: (x,y) -> (" << x << "," << y << ")" << std::endl;
		return;
	}

	if (y < 0 || y >= gHeight)
	{
		std::cerr << "Warnning: try to write the pixel out of range: (x,y) -> (" << x << "," << y << ")" << std::endl;
		return;
	}

	// Note: x -> the column number, y -> the row number
	gCanvas[y][x] = Pixel({ r,g,b });

}

vec3 color(const ray& r) {
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}

void rendering()
{

	printf("CGAssignment4 (built %s at %s) \n", __DATE__, __TIME__);
	std::cout << "Ray-tracing based rendering launched..." << std::endl;
	int nx = gWidth;
	int ny = gHeight;

	double startFrame = clock();

	vec3 lower_left_corner(-2.0f, -1.0f, -1.0f), 
		horizontal(4.0f, 0.0f, 0.0f), 
		vertical(0.0f, 2.0f, 0.0f), 
		origin(0.0f, 0.0f, 0.0f);

	// The main ray-tracing based rendering loop
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3 col = color(r);
			int ir = 256 - int(255.99 * col[0]);
			int ig = 256 - int(255.99 * col[1]);
			int ib = 256 - int(255.99 * col[2]);

			writeRGBToCanvas(ir, ig, ib, i, j);
		}
	}
	double endFrame = clock();
	double timeConsuming = static_cast<double>(endFrame - startFrame) / CLOCKS_PER_SEC;

	std::cout << "Ray-tracing based rendering over..." << std::endl;
	std::cout << "The rendering task takes " << timeConsuming << " seconds" << std::endl;
}