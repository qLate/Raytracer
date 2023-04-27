#include "Triangle.h"

#include "Ray.h"
#include "BoundingBoxes.h"

void Triangle::recalculateValues()
{
	auto p1 = points[0], p2 = points[1], p3 = points[2];
	auto e1 = p2 - p1;
	auto e2 = p3 - p1;
	auto normal = obj->getRot() * cross(localPoints[1].vertice - localPoints[0].vertice, localPoints[2].vertice - localPoints[1].vertice);

	// Depending on which component of the normal is largest, calculate
	// coefficients:
	if (fabs(normal.x) > fabs(normal.y) && fabs(normal.x) > fabs(normal.z))
	{
		row1 = {0.0f, e2.z / normal.x, -e2.y / normal.x};
		valRow1 = cross(p3, p1).x / normal.x;
		row2 = {0.0f, -e1.z / normal.x, e1.y / normal.x};
		valRow2 = -cross(p2, p1).x / normal.x;
		row3 = {1.0f, normal.y / normal.x, normal.z / normal.x};
		valRow3 = -dot(p1, normal) / normal.x;
	}
	else if (fabs(normal.y) > fabs(normal.z))
	{
		row1 = {-e2.z / normal.y, 0.0f, e2.x / normal.y};
		valRow1 = cross(p3, p1).y / normal.y;
		row2 = {e1.z / normal.y, 0.0f, -e1.x / normal.y};
		valRow2 = -cross(p2, p1).y / normal.y;
		row3 = {normal.x / normal.y, 1.0f, normal.z / normal.y};
		valRow3 = -dot(p1, normal) / normal.y;
	}
	else if (fabs(normal.z) > 0.0f)
	{
		row1 = {e2.y / normal.z, -e2.x / normal.z, 0.0f};
		valRow1 = cross(p3, p1).z / normal.z;
		row2 = {-e1.y / normal.z, e1.x / normal.z, 0.0f};
		valRow2 = -glm::cross(p2, p1).z / normal.z;
		row3 = {normal.x / normal.z, normal.y / normal.z, 1.0f};
		valRow3 = -dot(p1, normal) / normal.z;
	}
	else
	{
		// This triangle is degenerate. Set the transformation matrix to
		// the 0 matrix, which in turn will yield 0 values in places that
		// intersection calculations will detect and treat as a miss.
		row1 = {};
		valRow1 = 0.0f;
		row2 = {};
		valRow2 = 0.0f;
		row3 = {};
		valRow3 = 0.0f;
	}
}

Triangle::Triangle(GraphicalObject* obj, ExtendedVertice p1, ExtendedVertice p2, ExtendedVertice p3, bool isTwoSided) : localPoints({p1, p2, p3}),
                                                                                                                        localNormal(normalize(cross(localPoints[1].vertice - localPoints[0].vertice, localPoints[2].vertice - localPoints[1].vertice))),
                                                                                                                        isTwoSided(isTwoSided)
{
	if (obj != nullptr)
		attachTo(obj);
}
void Triangle::attachTo(GraphicalObject* obj)
{
	this->obj = obj;

	updateGeometry();
	recalculateValues();
}

bool Triangle::intersect(Ray& ray, bool intersectAll)
{
	const float dz = dot(row3, ray.dir);
	if (dz == 0.0f)
		return false;

	const float oz = dot(row3, ray.pos) + valRow3;
	const float t = -oz / dz;
	if (t < 0 || ray.closestT < t || t >= ray.maxDist)
		return false;

	const auto hit = ray.pos + ray.dir * t;
	const float b1 = dot(row1, hit) + valRow1;
	if (b1 < 0.0f || b1 > 1.0f)
		return false;

	const float b2 = dot(row2, hit) + valRow2;
	if (b2 < 0.0f || b1 + b2 > 1.0f)
		return false;

	ray.closestT = t;
	ray.closestObj = obj;
	ray.surfaceNormal = normal;
	ray.interPoint = hit;
    ray.closestT = t;
    float b3 = 1 - b1 - b2;
//    auto P =
//    localPoints.at(0).verticeUV
//    auto a  = dot(localPoints.at(0).verticeUV, {b1,b2});
//    auto b  = dot(localPoints.at(1).verticeUV, {b1,b2});
//    auto c  = dot(localPoints.at(2).verticeUV, {b1,b2});

//    ray.color = obj->material.texture->getColor(b1, b2);
//p1.verti
    auto a = b1*localPoints.at(0).verticeUV;
    auto b = b2*localPoints.at(1).verticeUV;
    auto c = b3*localPoints.at(2).verticeUV;
    auto P = a + b + c;
//    auto duv1 =  localPoints.at(0).verticeUV - localPoints.at(2).verticeUV;
//    auto duv2 =  localPoints.at(1).verticeUV - localPoints.at(2).verticeUV;


//    auto dp1 = localPoints.at(0).vertice - localPoints.at(2).vertice, dp2 = localPoints.at(1).vertice - localPoints.at(2).vertice;
//    float determinant = duv1.x * duv1.y - duv1.y * duv2.x;
////    if (determinant == 0.f) {
////        // Handle zero determinant for triangle partial derivative matrix
//////        CoordinateSystem(Normalize(Cross(e2, e1)), &dpdu, &dpdv);
////    }
////    else {
//        float invdet = 1.f / determinant;
//        auto dpdu = ( duv2.y * dp1 - duv1.y * dp2) * invdet;
//        auto dpdv = (-duv2.x * dp1 + duv1.x * dp2) * invdet;
////    }
//
//    // Interpolate $(u,v)$ triangle parametric coordinates
//    float b0 = 1 - b1 - b2;
//    float tu = b0*uvs[0][0] + b1*uvs[1][0] + b2*uvs[2][0];
//    float tv = b0*uvs[0][1] + b1*uvs[1][1] + b2*uvs[2][1];x
//    ray.color = P.x*Color::green() + P.y*Color::red() + (1-P.x - P.y)*Color::blue();
//    ray.color = a*Color::green() + b*Color::red() + c*Color::blue();
//
//    P(u,v) = a*(1-u)*(1-v) + b*(1-u)*v + P2*u*v + P3*u*(1-v)
    ray.color = obj->material.texture->getColor(P.x, P.y);

//    ray.color = b1*Color::green() + b2*Color::red() + b3*Color::blue();

	return true;
}

AABB Triangle::getBoundingBox() const
{
	float x_min = FLT_MAX, x_max = -FLT_MAX;
	float y_min = FLT_MAX, y_max = -FLT_MAX;
	float z_min = FLT_MAX, z_max = -FLT_MAX;

	for (const auto& p : points)
	{
		x_min = std::min(x_min, p.x);
		x_max = std::max(x_max, p.x);

		y_min = std::min(y_min, p.y);
		y_max = std::max(y_max, p.y);

		z_min = std::min(z_min, p.z);
		z_max = std::max(z_max, p.z);
	}
	return {{x_min - 0.05f, y_min - 0.05f, z_min - 0.05f}, {x_max + 0.05f, y_max + 0.05f, z_max + 0.05f}};
}

glm::vec3 Triangle::getCenter() const
{
	return (points[0] + points[1] + points[2]) * 0.333f;
}

void Triangle::updateGeometry()
{
    points = {obj->getRot() * localPoints[0].vertice + obj->getPos(),
              obj->getRot() * localPoints[1].vertice + obj->getPos(),
              obj->getRot() * localPoints[2].vertice + obj->getPos()};

//    points = {
//		obj->getRot() * localPoints[0]. + obj->getPos(),
//		obj->getRot() * localPoints[1] + obj->getPos(),
//		obj->getRot() * localPoints[2] + obj->getPos()
//	};
	normal = obj->getRot() * localNormal;
}