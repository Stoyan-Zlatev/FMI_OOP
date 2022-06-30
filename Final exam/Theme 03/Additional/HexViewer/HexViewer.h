#pragma once

class HexViewer
{
	unsigned char* data;
	size_t size;
public:
	HexViewer(const char* fileName);
	
	HexViewer(const HexViewer& other) = delete;
	HexViewer& operator=(const HexViewer& other) = delete;

	void addByte(const char* byteStr);
	void removeLastByte();
	void change(size_t index, const char* byteStr);

	void saveAs(const char* fileName) const;
	
	void print() const;
	~HexViewer();
};