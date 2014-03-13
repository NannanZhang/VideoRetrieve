#pragma once

class RGB2HSV
{
public:
	RGB2HSV();
	~RGB2HSV();

public:
	void ApplyFilter(int red, int green, int blue, int* Result);


};

template<class T, class Compare>
inline const T& max(const T& a, const T& b, Compare comp) 
{
	return comp(a, b) ? b : a;
}

template<class T, class Compare>
inline const T& min(const T& a, const T& b, Compare comp)
{
	return comp(b, a) ? b : a;
}

bool int_less(int a, int b);

bool double_less(double a, double b);
