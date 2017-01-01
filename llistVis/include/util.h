//#ifndef UTIL_H
//#define UTIL_H
static int SCREEN_WIDTH = 1280;
static int SCREEN_HEIGHT = 430;
namespace
{
	template<typename T>
	const T Lerp(const T a, const T b, const T frac)
	{
		return a + ((b - a) * frac);
	}
	float length(float x, float y)
	{
		return sqrt(x*x + y*y);
	}
	float length(sf::Vector2f v1, sf::Vector2f v2)
	{
		float x = v1.x - v2.x;
		float y = v1.y - v2.y;
		return sqrt((abs(x*x)) + (abs(y*y)));
	}
}

//#endif