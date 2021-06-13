#include "Utils.h"

void BezierCurve::clearAll()
{
	m_controlPoints.clear();
	m_beizerPoints.clear();
	m_auxiliaryLines.clear();
}

void BezierCurve::clearControlPoints()
{
	m_controlPoints.clear();
	m_auxiliaryLines.clear();
}

void BezierCurve::generateAuxiliaryLines(const double &t)
{
	static const std::array<float, 3> gColors[12] =
	{
		{1, 0, 0},
		{0, 1, 0},
		{1, 0.5f, 0},
		{1, 0, 0.5f},
		{0, 0.5f, 0.5f},
		{0, 0.25f, 0.5f},
		{0.25f, 0.5f, 0},
		{0.5f, 0, 1},
		{1, 0.25f, 0.5f},
		{0.5f, 0.5f, 0.5f},
		{0.25f, 0.25f, 0.25f},
		{0.125f, 0.125f, 0.125f}
	};

	m_auxiliaryLines.clear();

	auto points = m_controlPoints;
	int level = 1;
	while (points.size() >= 2)
	{

		std::vector<Point2D> tmp;
		for (int i = 0; i < points.size() - 1; ++i)
		{
			Point2D point = Point2D::lerp(points[i], points[i + 1], t);
			point.color = { Uint8(gColors[level][0] * 255), Uint8(gColors[level][1] * 255), Uint8(gColors[level][2] * 255) };
			tmp.push_back(point);
		}

		for (int i = 0; i < tmp.size() - 1; ++i)
		{
			const auto &p0 = tmp[i];
			const auto &p1 = tmp[i + 1];
			Line2D line(p0.x, p0.y, p1.x, p1.y);
			line.color = p0.color;
			m_auxiliaryLines.push_back(line);
		}

		level = (level + 1) % 12;
		points = std::move(tmp);
	}
}

void BezierCurve::addControlPoints(int x, int y)
{
	Point2D point(x, y);
	m_controlPoints.push_back(point);
}

void BezierCurve::drawControlPointsAndLines(WindowsApp* winApp) const
{
	if (m_controlPoints.empty())
		return;
	for (size_t i = 0; i < m_controlPoints.size() - 1; ++i)
	{
		const auto &p0 = m_controlPoints[i];
		const auto &p1 = m_controlPoints[i + 1];
		winApp->drawLine(255, 0, 0, p0.x + 0.5, p0.y + 0.5, p1.x + 0.5, p1.y + 0.5);
	}

	for (const auto &p : m_controlPoints)
	{
		winApp->drawRectFill(255, 0, 0, p.x + 0.5 - 3, p.y + 0.5 - 3, 6, 6);
	}
}

void BezierCurve::drawBezierCurvePoints(WindowsApp* winApp) const
{
	if (m_beizerPoints.empty())
		return;

	for (const auto &beizerPoints : m_beizerPoints)
	{
		for (size_t i = 0; i < beizerPoints.size(); ++i)
		{
			const auto &p = beizerPoints[i];
			winApp->drawRectFill(255, 255, 255, p.x + 0.5 - 2, p.y + 0.5 - 2, 4, 4);
		}
	}
}

void BezierCurve::drawAuxiliaryLines(WindowsApp *winApp) const
{
	for (size_t i = 0; i < m_auxiliaryLines.size(); ++i)
	{
		const auto &line = m_auxiliaryLines[i];
		winApp->drawLine(line.color[0], line.color[1], line.color[2], line.x0 + 0.5, line.y0 + 0.5, line.x1 + 0.5, line.y1 + 0.5);
		winApp->drawRectFill(line.color[0], line.color[1], line.color[2], line.x0 + 0.5 - 3, line.y0 + 0.5 - 3, 6, 6);
		winApp->drawRectFill(line.color[0], line.color[1], line.color[2], line.x1 + 0.5 - 3, line.y1 + 0.5 - 3, 6, 6);
	}
}

void BezierCurve::evaluate(const double &t)
{
	// Visualization of auxiliary lines
	generateAuxiliaryLines(t);

	// Task1
	Point2D bp = implementTask1(m_controlPoints, t);

	// Task2
	//Point2D bp = implementTask2(m_controlPoints, t);

	m_beizerPoints.back().push_back(bp);
}

long long BezierCurve::getFactorial(int n)
{
	int size = m_factorialValues.size() - 1;
	if (n <= size) return m_factorialValues[n];

	int index = std::max(0, std::min(n, size));
	long long result = m_factorialValues[index];

	for (int i = index + 1; i <= n; i++)
	{
		if (i <= size)
		{
			m_factorialValues[i] = result *= i;
		}
		else
		{
			m_factorialValues.push_back(result *= i);
		}
	}

	return result;
}

double BezierCurve::getBezierValue(int i, int n, double t)
{
	return getFactorial(n) / (getFactorial(i) * getFactorial(n - i)) * std::pow(t, i) * std::pow(1 - t, n - i);
}

Point2D BezierCurve::implementTask1(const std::vector<Point2D> &points, const double &t)
{
	int n = points.size() - 1;
	auto p = Point2D(0, 0);
	for (int i = 0; i <= n; i++)
	{
		p += points[i] * getBezierValue(i, n, t);
	}

	return p;
}

Point2D BezierCurve::implementTask2(const std::vector<Point2D> &points, const double &t) const
{
	std::vector<Point2D>* iter_points = new std::vector<Point2D>(points);

	do 
	{
		std::vector<Point2D>* temp = new std::vector<Point2D>({});
		int size = (*iter_points).size();
		for (int i = 0; i < size - 1; i++)
		{
			(*temp).push_back(Point2D::lerp((*iter_points)[i], (*iter_points)[i + 1], t));
		}

		delete iter_points;
		iter_points = temp;
	}
	while ((*iter_points).size() > 1);

	Point2D result = (*iter_points)[0];
	delete iter_points;

	return result;
	
}