#pragma once
#include "kmint/math/vector2d.hpp"

namespace kmint {
namespace pigisland {

	class Wall2D {
		public:
			Wall2D() {}

			Wall2D(kmint::math::vector2d A, kmint::math::vector2d B) : vA(A), vB(B)
			{
				calculateNormal();
			}

			Wall2D(kmint::math::vector2d A, kmint::math::vector2d B, kmint::math::vector2d N) :vA(A), vB(B), vN(N)
			{ }

			kmint::math::vector2d From() const { return vA; }
			void SetFrom(kmint::math::vector2d  v) { vA = v; calculateNormal(); }

			kmint::math::vector2d To() const { return vB; }
			void SetTo(kmint::math::vector2d  v) { vB = v; calculateNormal(); }

			kmint::math::vector2d Center() const { return (vA + vB) / 2.0; }

			kmint::math::vector2d Normal() const { return vN; }
			void SetNormal(kmint::math::vector2d  n) { vN = n; }
		private:	
			kmint::math::vector2d vA, vB, vN;

			void calculateNormal()
			{
				kmint::math::vector2d  temp = normalize(vB - vA);

				vN.x(-temp.y());
				vN.y(temp.x());
			}
	};
} // namespace pigisland
} // namespace kmint
