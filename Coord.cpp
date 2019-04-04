#include "Coord.h"
#include <math.h>
using namespace wag;

namespace wag
{
Coord::Coord ( double x, double y , double z ) : x ( x ), y ( y ), z ( z )
{
}

Coord::~Coord()
{
	//dto
}
double Coord::distance ( Coord b ) const
{
	double t = b.x - this->x;
	double u = b.y - this->y;
	double v = b.z - this->z;
	t *= t;
	u *= u;
	v *= v;
	return pow ( t + u + v, 0.5 );

}
double Coord::cross ( const Coord& b, AXIS a ) const
{
	switch ( a ) {
		case XY:
			return this->x * b.y - this->y * b.x;
		case XZ:
			return this->x * b.z - this->z * b.x;
		case YZ:
			return this->y * b.z - this->z * b.y;


		default:
			return 0;

	}



}
bool Coord::operator== ( Coord b )
{
	if ( this->x != b.x ) { return 0; }
	if ( this->y != b.y ) { return 0; }
	if ( this->z != b.z ) { return 0; }
	return 1;

}
void Coord::operator*= ( double b )
{
	this->x *= b;
	this->y *= b;
	this->z *= b;

}
void Coord::operator/= ( double b )
{
	this->x /= b;
	this->y /= b;
	this->z /= b;

}
bool Coord::operator!= ( Coord b )
{
	if ( this->x != b.x ) { return 1; }
	if ( this->y != b.y ) { return 1; }
	if ( this->z != b.z ) { return 1; }
	return 0;

}
void Coord::move ( double angle, double speed, AXIS ax )
{
	switch ( ax ) {
		case XY: {
				x = x + speed * cos ( angle );
				y = y + speed * sin ( angle );
				break;
			}
		case YZ: {
				y = y + speed * cos ( angle );
				z = z + speed * sin ( angle );
				break;
			}
		case XZ: {
				x = x + speed * cos ( angle );
				z = z + speed * sin ( angle );
				break;
			}
		default:
			break;
	}
}
void Coord::operator+= ( Coord c )
{
	this->x += c.x;
	this->y += c.y;
	this->z += c.z;
}
void Coord::operator-= ( Coord c )
{
	this->x -= c.x;
	this->y -= c.y;
	this->z -= c.z;
}
void Coord::operator*= ( Coord c )
{
	this->x *= c.x;
	this->y *= c.y;
	this->z *= c.z;
}
void Coord::operator/= ( Coord c )
{
	this->x /= c.x;
	this->y /= c.y;
	this->z /= c.z;
}
Coord Coord::operator* ( double k ) const
{
	return Coord ( x * k, y * k, z * k );

}

Coord Coord::operator/ ( double k ) const
{
	return   Coord ( x / k, y / k, z / k );
}

Coord Coord::operator+ ( Coord b ) const
{
	return Coord ( this->x + b.x, this->y + b.y, this->z + b.z );
}
Coord Coord::operator- ( Coord b ) const
{
	return Coord ( this->x - b.x, this->y - b.y , this->z - b.z );
}
Coord Coord::operator* ( Coord b ) const
{
	return Coord ( this->x * b.x, this->y * b.y, this->z * b.z );
}
Coord Coord::operator/ ( Coord b ) const
{
	return Coord ( this->x / b.x, this->y / b.y , this->z / b.z );
}

void Coord::rotate ( Coord origin, double angle, AXIS ax )
{
	Coord trans = *this - origin;



	Coord rotated;
	switch ( ax ) {
		case XY: {
				rotated =  {
					x = ( trans.x * cos ( angle ) - trans.y * sin ( angle ) ),
					y = ( trans.x * sin ( angle ) + trans.y * cos ( angle ) ),
					z = trans.z
				};
				break;
			}
		case XZ: {
				rotated =  {
					x = ( trans.x * cos ( angle ) - trans.z * sin ( angle ) ),
					y= trans.y,
					z = ( trans.x * sin ( angle ) + trans.z * cos ( angle ) )
				};
				break;
			}
		case YZ: {
				rotated =  {
                          x= trans.x,
                           y = ( trans.y * cos ( angle ) - trans.z * sin ( angle ) ),
                           z = ( trans.y * sin ( angle ) + trans.z * cos ( angle ) )
				           };
				break;
			}

		default:
			break;
	}


	*this = rotated + origin;
}
/*
void Coord::rotate ( Coord origin, Coord deltaangle )
{
	Coord trans = *this - origin;

    Coord rotated= {
	x = (trans.x * cos ( angle ) - trans.y * sin ( angle )),
	y = (trans.x * sin ( angle ) + trans.y * cos ( angle ))
    };
	*this = rotated+origin;
}
*/

double Coord::modulo()
{
	return pow ( x * x + y * y + z * z, 0.5 );
}
namespace pg
{
std::ostream& operator<< ( std::ostream& os , const Coord& p )
{
	os << "X:" << p.x << "  Y:" << p.y << " Z:" << p.z;
	return os;

}
}

}
