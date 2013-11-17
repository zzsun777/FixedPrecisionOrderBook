#ifndef __FIXED__
#define __FIXED__

#include <math.h>

#include "Utilities.h"

namespace FixedPriceOrderBook {

//-----------------------------------------------------------------------------
class Fixed {
public:
   //------------------------------------------------------------
   Fixed(double input, uint32_t precision = 5) {
      precision_ = pow(10, precision);
      whole_part_ = static_cast<int64_t>(input);
      fract_part_ = static_cast<int64_t>(round((input - whole_part_) * precision_));
      // fprintf(stderr, "DOUBLE CTOR: Whole part int: %ld.  Fract part int: %ld\n", whole_part_, fract_part_);
   }

   Fixed(int32_t input, uint32_t precision = 5) {
      precision_ = pow(10, precision);
      whole_part_ = input;
      fract_part_ = 0;
      // fprintf(stderr, "INT CTOR: Whole part int: %ld.  Fract part int: %ld\n", whole_part_, fract_part_);
   }

   //------------------------------------------------------------
   Fixed(const Fixed &rhs)
   : whole_part_(rhs.whole_part_)
   , fract_part_(rhs.fract_part_)
   , precision_(rhs.precision_) { }

   //------------------------------------------------------------
   double getDouble() const {
      double price = 0.0;
      price += whole_part_;
      price += static_cast<double>(fract_part_ / static_cast<double>(precision_));
      // DB("getDouble returning double: %.5f\n", price);
      return price;
   }

   //------------------------------------------------------------
   bool operator==(const Fixed &rhs) const {
      return whole_part_ != rhs.whole_part_ ? false :
         fract_part_ != rhs.fract_part_ ? false :
            true;
   }

   //------------------------------------------------------------
   bool operator !=(const Fixed &rhs) const {
      return !operator==(rhs);
   }

   //------------------------------------------------------------
   bool operator <(const Fixed &rhs) const {
      if (whole_part_ < rhs.whole_part_) {
         return true;
      }
      if (whole_part_ == rhs.whole_part_) {
         if (fract_part_ < rhs.fract_part_)  {
            return true;
         }
      }
      return false;
   }

   //------------------------------------------------------------
   bool operator >(const Fixed &rhs) const {
      return !operator<(rhs);
   }

   //------------------------------------------------------------
   bool operator <=(const Fixed &rhs) const {
      return operator<(rhs) ? true : operator==(rhs);
   }

   //------------------------------------------------------------
   bool operator >=(const Fixed &rhs) const {
      return operator>(rhs) ? true : operator==(rhs);
   }

   //------------------------------------------------------------
   Fixed &operator =(const Fixed &rhs) {
      if (this == &rhs) {
         return *this;
      }
      whole_part_ = rhs.whole_part_;
      fract_part_ = rhs.fract_part_;
      precision_ = rhs.precision_;
      return *this;
   }

   //------------------------------------------------------------
   Fixed &operator +=(const Fixed &rhs) {
      whole_part_ += rhs.whole_part_;
      fract_part_ += rhs.fract_part_;
      return *this;
   }

   //------------------------------------------------------------
   // Duplicating to avoid temporary on stack for negation of const rhs
   Fixed &operator -=(const Fixed &rhs) {
      whole_part_ -= rhs.whole_part_;
      fract_part_ -= rhs.fract_part_;
      return *this;
   }

   //------------------------------------------------------------
   void operator *=(const Fixed &rhs) {
      double t = rhs.getDouble();
      whole_part_ *= t;
      fract_part_ *= t;
      while (fract_part_ > (int64_t)precision_) {
         whole_part_ += 1;
         fract_part_ -= precision_;
      }
   }

private:
   int64_t whole_part_;
   int64_t fract_part_;
   uint64_t precision_;
};

//------------------------------------------------------------
Fixed operator+(const Fixed &lhs, const Fixed &rhs) {
   Fixed r(lhs);
   r += rhs;
   return r;
}
Fixed operator-(const Fixed &lhs, const Fixed &rhs) {
   Fixed r(lhs);
   r -= rhs;
   return r;
}

class FixedComparer {
public:
   bool operator()(const Fixed &lhs, const Fixed &rhs) {
      if (lhs < rhs)
         return true;
      return false;
   }
};

}

#endif
