#ifndef _MATHHELPER_H
#define _MATHHELPER_H
#include <math.h>
#include <SDL.h>

#define PI 3.14159265
#define DEG_TO_RAD PI / 180.0f
#define RAD_TO_DEG 180.0f / PI

struct Vector2 {

	float x;
	float y;

	Vector2(float _x = 0.0f, float _y = 0.0f) {
		x = _x;
		y = _y;
	}

	float MagnitudeSqr() {
		return x*x + y*y;
	}

	float Magnitude() {

		return (float)sqrt(x*x + y*y);
	}

	Vector2 Normalized() {

		float mag = Magnitude();

		return Vector2(x / mag, y / mag);
	}

	Vector2& operator +=(const Vector2& rhs) {

		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	Vector2& operator -=(const Vector2& rhs) {

		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	Vector2 operator -() const {

		return Vector2(-x, -y);
	}
};

const Vector2 VEC2_ZERO = { 0.0f, 0.0f };
const Vector2 VEC2_ONE = { 1.0f, 1.0f };
const Vector2 VEC2_UP = { 0.0f, 1.0f };
const Vector2 VEC2_RIGHT = { 1.0f, 0.0f };

struct SegLine{
	Vector2 point1,point2;

	SegLine(Vector2 p1 = VEC2_ZERO,Vector2 p2 = VEC2_ZERO){
		point1 = p1;
		point2 = p2;
	}

};

inline Vector2 operator +(const Vector2& lhs, const Vector2& rhs) {

	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline Vector2 operator -(const Vector2& lhs, const Vector2& rhs) {

	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline Vector2 operator *(const Vector2& lhs, const float& rhs) {

	return Vector2(lhs.x * rhs, lhs.y * rhs);
}

inline Vector2 operator *(const float& lhs, const Vector2& rhs) {

	return Vector2(lhs * rhs.x, lhs * rhs.y);
}

inline Vector2 operator *(const Vector2& lhs, const Vector2& rhs) {

	return Vector2(lhs.x * rhs.x, lhs.y * rhs.y);
}

inline Vector2 operator /(const Vector2& lhs, const float& rhs) {

	return Vector2(lhs.x / rhs, lhs.y / rhs);
}

inline Vector2 operator /(const float& lhs, const Vector2& rhs) {

	return Vector2(lhs / rhs.x, lhs / rhs.y);
}

inline int myCruzProduct(Vector2 p1,Vector2 p2){///Regresa el valor que retorna el producto
	int64_t res = (int64_t)(p1.x*p2.y) - (int64_t)(p1.y*p2.x); ///cruz de dos punto , 0 si estan sobre la
	if(res >0){                          ///la misma linea , 1 si p2 esta a la derecha
		res = 1;                         /// de p1 , -1 si p2 esta a la izquierda de p1
	}
	if(res < 0){
		res = -1;
	}
	return res;

}

inline int dirAP(SegLine A,Vector2 p){ ///Regresa la direccion a la que esta un punto de una arista
	Vector2 p2;                /// 0 si el punto esta en la arista
	p2.x = A.point2.x - A.point1.x;  /// 1 si esta a un lado de la arista
	p2.y = A.point2.y - A.point1.y;  /// -1 si esta al otro lado de la arista
	p.x = p.x - A.point1.x;
	p.y = p.y - A.point1.y;
	int dir = myCruzProduct(p2,p);
	return dir;
}

inline int LinesIntersect(SegLine A,SegLine B){///Regresa 1 si las aristas se intersectan
	int dirAB1 = dirAP(A,B.point1);   ///-1 si no se intersectan
	int dirAB2 = dirAP(A,B.point2);   /// 0 si un punto deuna arista esta sobre la otra arista
	int dirBA1 = dirAP(B,A.point1);
	int dirBA2 = dirAP(B,A.point2);

	if((dirAB1==0 || dirAB2==0) && (dirBA1!=dirBA2)){
		return 0;
	}
	if((dirBA1==0 || dirBA2==0) && (dirAB1!=dirAB2)){
		return 0;
	}
	if(dirAB1!=dirAB2 && dirBA1!=dirBA2){
		return 1;
	}
	return -1;
}

inline Vector2 intearVector(Vector2 vec){
	int aux = vec.x;
	vec.x = aux;
	aux = vec.y;
	vec.y = aux;
	return vec;
}

inline Vector2 RotateVector(Vector2& vec, float angle) {
	
	float radAngle = (float)(angle*DEG_TO_RAD);

	return Vector2((float)(vec.x * cos(radAngle) - vec.y * sin(radAngle)), (float)(vec.x * sin(radAngle) + vec.y * cos(radAngle)));
}

inline float GetAngleFromYAxisToVector(Vector2 vec){
	float degrees = RAD_TO_DEG * atan2(vec.y, vec.x);
	if (vec.y < 0) degrees + 180;
	degrees -= 90;
	return degrees;
}

inline bool	PointInRect(Vector2 point,SDL_Rect rect){
	point = intearVector(point);
	if(point.x >= rect.x && point.x <= rect.x + rect.w && point.y >= rect.y && point.y <= rect.y + rect.h){
		return true;
	}
	return false;
}

inline float getDistanceToPoint(Vector2 p1,Vector2 p2){
	float distance = (float) pow((p1.x - p2.x),2) + (float)pow((p1.y - p2.y),2);
	distance = sqrt(distance);
	return distance;
}

inline Vector2 obtainFixedPoint(Vector2 center,Vector2 touch,float radio){
	//abreviacion C = center , T = touch
	float disCT= getDistanceToPoint(touch,center);
	if(disCT > radio){
		float ratio = radio / disCT;
		touch.x = center.x + (touch.x - center.x) * ratio;
		touch.y = center.y + (touch.y - center.y) * ratio;
	}
	//Log.d("touch x",Float.toString(touch.x));
	//Log.d("touch y",Float.toString(touch.y));
	return touch;
}

inline float Dot(const Vector2& vec1, const Vector2& vec2) {

	return vec1.x * vec2.x + vec1.y * vec2.y;
}

inline float Clamp(const float& value, const float& min, const float& max) {

	if (value > max) {
		return max;
	}
	if (value < min) {
		return min;
	}

	return value;
}

inline Vector2 Lerp(Vector2& start, Vector2& end, float time) {

	if (time <= 0.0f) {
		return start;
	}

	if (time >= 1.0f) {
		return end;
	}

	Vector2 dir = (end - start).Normalized();
	float mag = (end - start).Magnitude();

	return start + dir * mag * time;
}

#endif
