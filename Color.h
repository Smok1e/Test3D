#pragma once

#pragma pack (push, 1)

struct Color 

{

	char r, g, b;

	Color (char r_, char g_, char b_) :

		r (r_),
		g (g_),
		b (b_)

	{}

	Color (Color & that)

	{
	
		r = that.r;
		g = that.g;
		b = that.b;

	}

	Color (COLORREF color)

	{

		r = GetRValue (color);
		g = GetGValue (color);
		b = GetBValue (color);
	
	}

	Color & operator += (const Color & that)

	{
	
		r += that.r;
		g += that.g;
		b += that.b;

		return *this;

	}

	Color & operator -= (const Color & that)

	{
	
		r -= that.r;
		g -= that.g;
		b -= that.b;

		return *this;

	}

	operator COLORREF ()

	{
	
		return RGB (r, g, b);

	}

};
#pragma pack (pop)