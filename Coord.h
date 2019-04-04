#ifndef COORD_H
#define COORD_H
#include <iostream>

namespace wag
{
class Coord
{
	public:
	    enum AXIS{
            XY,XZ,YZ
	    };

		/** Default constructor */
		double x = 0, y = 0, z =  0;
		Coord() = default;
		Coord ( double x, double y,double z=0 );
		/** Default destructor */
		virtual ~Coord();
		void move ( double angle, double speed, AXIS = XY);
		void rotate(Coord origin, double angle, AXIS=XY);
		double distance ( Coord ) const;
		double cross(const Coord&, AXIS =XY ) const;

		void operator+= ( Coord );
		void operator-= ( Coord );
		void operator*= ( Coord );
		void operator/= ( Coord );

		Coord operator+ ( Coord )const;
		Coord operator- ( Coord )const;
		Coord operator* ( Coord )const;
		Coord operator/ ( Coord )const;

		void operator*= ( double k );
		void operator/= ( double k );
		Coord operator* ( double k )const;
		Coord operator/ ( double k )const;


		friend std::ostream& operator<< ( std::ostream& os, const Coord& p )
		{
			os << "X:" << p.x << "  Y:" << p.y<<" Z:"<<p.z;
			return os;

		}

		bool operator== ( Coord );
		bool operator!= ( Coord );
		double modulo();
	protected:
	private:
};
}
#endif // COORD_H
