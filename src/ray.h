#ifndef RAY_H
#define RAY_H

#include "vec3.h"

// a ray is a starting point plus a direction: P(t) = origin + t*dir
class ray {
  public:
    ray() {}
    ray(const point3& origin, const vec3& dir) : origin_(origin), dir_(dir) {}

    const point3& origin() const { return origin_; }
    const vec3& direction() const { return dir_; }

    // walk t units along the ray (dir isn't normalized, so t is in units of |dir|)
    point3 at(double t) const {
        return origin_ + t * dir_;
    }

  private:
    point3 origin_;
    vec3 dir_;
};

#endif
