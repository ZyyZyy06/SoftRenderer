#pragma once
#include "Global.h"
#include "Config.h"
#include<cstdlib>
#include<iostream>
#include <cassert>
#include <gdiplus.h>
#include "Math.h"

using namespace Gdiplus;


class Buffer {

protected:
	const long BUFFER_SIZE;

public:
	unsigned int channel;
	unsigned int width;
	unsigned int height;
	unsigned char* buffer;

	Buffer(unsigned int channel) :width(GL_WINDOW_WIDTH), height(GL_WINDOW_HEIGHT), BUFFER_SIZE(CONF_MAX_BUFFER_HEIGHT* CONF_MAX_BUFFER_WIDTH* channel) {
		buffer = new unsigned char[BUFFER_SIZE];
	}
	~Buffer() {
		delete[] buffer;
	}

	void updateBufferSize() {
		width = GL_WINDOW_WIDTH;
		height = GL_WINDOW_HEIGHT;
	}
};

class RGBABuffer : public Buffer {
public:
	RGBABuffer() :Buffer(4) {}


	void initWithTargetColor(const Vector4f targetColor) {
		unsigned char r = static_cast<unsigned char>(targetColor.x * 255);
		unsigned char g = static_cast<unsigned char>(targetColor.y * 255);
		unsigned char b = static_cast<unsigned char>(targetColor.z * 255);
		unsigned char a = static_cast<unsigned char>(targetColor.w * 255);

		for (unsigned int i = 0; i < CONF_MAX_BUFFER_HEIGHT; i++) {
			for (unsigned int j = 0; j < CONF_MAX_BUFFER_WIDTH; j++) {
				int stIndex = (i * CONF_MAX_BUFFER_WIDTH + j) * 4;
				buffer[stIndex] = r;
				buffer[stIndex + 1] = g;
				buffer[stIndex + 2] = b;
				buffer[stIndex + 3] = a;
			}
		}
		return;
	}

	void setValue(const unsigned int x, const unsigned int y, const Vector4f value) {
		unsigned int stIndex = (y * width + x) * 4;

		if (stIndex + 3 <= BUFFER_SIZE - 1) {
			unsigned char r = static_cast<unsigned char>(value.x * 255);
			unsigned char g = static_cast<unsigned char>(value.y * 255);
			unsigned char b = static_cast<unsigned char>(value.z * 255);
			unsigned char a = static_cast<unsigned char>(value.w * 255);


			if (stIndex + 3 < BUFFER_SIZE) {
				buffer[stIndex] = r;
				buffer[stIndex + 1] = g;
				buffer[stIndex + 2] = b;
				buffer[stIndex + 3] = a;
			}
		}
		return;
	}

	Vector4f getValue(const unsigned int x, const unsigned int y) {
		unsigned int index = (y * width + x) * 4;
		assert(index + 3 <= BUFFER_SIZE - 1);
		return Vector4f(buffer[index], buffer[index + 1], buffer[index + 2], buffer[index + 3]);
	}

	unsigned char getByteValue(const unsigned int x, const unsigned int y, const unsigned int index) {
		unsigned int stIndex = (y * width + x) * 4;
		assert(stIndex + 3 <= BUFFER_SIZE - 1);
		return buffer[stIndex + index];
	}
};

class ByteBuffer : public Buffer {
public:
	ByteBuffer() : Buffer(1) {}


	void initWithTargetValue(const float targetValue) {
		assert(targetValue <= 1.0 && targetValue >= 0.0);
		unsigned char value = static_cast<unsigned char>(targetValue * 255);

		for (unsigned int i = 0; i < CONF_MAX_BUFFER_HEIGHT; i++) {
			for (unsigned int j = 0; j < CONF_MAX_BUFFER_WIDTH; j++) {
				int stIndex = (i * CONF_MAX_BUFFER_WIDTH + j);
				buffer[stIndex] = value;
			}
		}
		return;
	}

	void setValue(const unsigned int x, const unsigned int y, const double value) {
		unsigned int index = y * width + x;
		if (index < BUFFER_SIZE) {
			buffer[index] = value;
		}
	}

	float getValue(const unsigned int x, const unsigned int y) {
		unsigned int index = y * width + x;
		assert(index <= BUFFER_SIZE - 1);
		if (index < BUFFER_SIZE) {
			return buffer[index];
		}
		return 1.0f;
	}
};

class DepthBuffer {
protected:
	const long BUFFER_SIZE;

public:
	unsigned int width;
	unsigned int height;
	float* buffer;

	DepthBuffer() :width(GL_WINDOW_WIDTH), height(GL_WINDOW_HEIGHT), BUFFER_SIZE(CONF_MAX_BUFFER_HEIGHT* CONF_MAX_BUFFER_WIDTH) {
		buffer = new float[BUFFER_SIZE];
	}
	~DepthBuffer() {
		delete[] buffer;
	}

	void updateBufferSize() {
		width = GL_WINDOW_WIDTH;
		height = GL_WINDOW_HEIGHT;
	}

	void initWithTargetValue(const float targetValue) {
		assert(targetValue <= 1.0 && targetValue >= 0.0);

		for (unsigned int i = 0; i < CONF_MAX_BUFFER_HEIGHT; i++) {
			for (unsigned int j = 0; j < CONF_MAX_BUFFER_WIDTH; j++) {
				int stIndex = (i * CONF_MAX_BUFFER_WIDTH + j);
				buffer[stIndex] = targetValue;
			}
		}
		return;
	}

	void setValue(const unsigned int x, const unsigned int y, const double value) {
		unsigned int index = y * width + x;
		if (index < BUFFER_SIZE) {
			buffer[index] = value;
		}
	}

	float getValue(const unsigned int x, const unsigned int y) {
		unsigned int index = y * width + x;
		assert(index <= BUFFER_SIZE - 1);
		if (index < BUFFER_SIZE) {
			return buffer[index];
		}
		return 1.0f;
	}
};

class FrameBuffer {
public:
	RGBABuffer rgbaBuffer;
	DepthBuffer depthBuffer;
	FrameBuffer() {}
	~FrameBuffer() {
		rgbaBuffer.~RGBABuffer();
		depthBuffer.~DepthBuffer();
	}

	void updateBufferSize() {
		rgbaBuffer.updateBufferSize();
		depthBuffer.updateBufferSize();
	}
};



class WindowBuffer {

private:
	static WindowBuffer* singleInstance;
private:
	FrameBuffer buffer_1;
	FrameBuffer buffer_2;
	Vector4f backgroundColor;

	WindowBuffer() {
		currentBuffer = &buffer_1;
		buffer_1.rgbaBuffer.updateBufferSize();
		buffer_2.rgbaBuffer.updateBufferSize();
		buffer_1.rgbaBuffer.initWithTargetColor(Vector4f(0.0, 0.0, 0.0, 1.0));
		buffer_2.rgbaBuffer.initWithTargetColor(Vector4f(0.0, 0.0, 0.0, 1.0));

		buffer_1.depthBuffer.updateBufferSize();
		buffer_2.depthBuffer.updateBufferSize();

		buffer_1.depthBuffer.initWithTargetValue(1.0);
		buffer_2.depthBuffer.initWithTargetValue(1.0);

		backgroundColor = Vector4f(0.0, 0.0, 0.0, 1.0);
	}
	~WindowBuffer() {
	}

public:
	FrameBuffer* currentBuffer;

	void updateWindowBuffer() {
		buffer_1.updateBufferSize();
		buffer_2.updateBufferSize();
	}

	FrameBuffer* getDrawBuffer() {
		if (currentBuffer == NULL) {
			currentBuffer = &buffer_1;
		}

		if (currentBuffer == &buffer_1) {
			buffer_2.rgbaBuffer.initWithTargetColor(backgroundColor);
			buffer_2.depthBuffer.initWithTargetValue(1.0);
			return &buffer_2;
		}
		else {
			buffer_1.rgbaBuffer.initWithTargetColor(backgroundColor);
			buffer_1.depthBuffer.initWithTargetValue(1.0);
			return &buffer_1;
		}
	}

	void SwapWindowBuffer() {
		if (currentBuffer == NULL) {
			currentBuffer = &buffer_1;
		}
		else {
			if (currentBuffer == &buffer_1)
				currentBuffer = &buffer_2;
			else
				currentBuffer = &buffer_1;
		}
	}

	void loadCurrentFrameBufferToBitmap(Bitmap& bitmap) {

		currentBuffer->rgbaBuffer.updateBufferSize();
		unsigned int height = currentBuffer->rgbaBuffer.height;
		unsigned int width = currentBuffer->rgbaBuffer.width;
		RGBABuffer* rgbabuffer = &(currentBuffer->rgbaBuffer);

		for (unsigned int i = 0; i < height; i++) {
			for (unsigned int j = 0; j < width; j++) {
				unsigned char a = rgbabuffer->getByteValue(j, i, 3);
				unsigned char r = rgbabuffer->getByteValue(j, i, 0);
				unsigned char g = rgbabuffer->getByteValue(j, i, 1);
				unsigned char b = rgbabuffer->getByteValue(j, i, 2);

				Color color = Color(a, r, g, b);
				bitmap.SetPixel(j, i, color);
			}
		}
	}

	static WindowBuffer* getInstance() {
		if (singleInstance == NULL)
			singleInstance = new WindowBuffer();
		return singleInstance;
	}
	static void deleteInstance() {
		delete singleInstance;
		singleInstance = NULL;
	}
};

