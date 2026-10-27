#ifndef SLINKY_SHARE_F0B2F81EEFF1CE571A04
#define SLINKY_SHARE_F0B2F81EEFF1CE571A04
#include "PathTessellation.hpp"
#include "DecodedNumericService.hpp"
namespace reconstruction::drawing {
// Caller-owned frame. Allocator calls retain their original user context;
// each numeric call independently reloads its proved borrowed encoded cell.
struct BoundPathDependencies {
    const PathDependencies &original;
    numeric_service::Context unary,direction;
    PathDependencies value;
    BoundPathDependencies(const PathDependencies &source,
        numeric_service::Context angle,numeric_service::Context bearing)
        :original(source),unary(angle),direction(bearing),value(source) {
        value.context=this;
        value.resize_13cf90=[](void *c,void *p,std::uint64_t n) {
            auto &frame=*static_cast<BoundPathDependencies *>(c);
            return frame.original.resize_13cf90(frame.original.context,p,n);
        };
        value.angle_13d190=[](void *c,float x) {
            return numeric_service::floatUnary_13d190(static_cast<BoundPathDependencies *>(c)->unary,x);
        };
        value.direction_13cfc0=[](void *c,float x,float y) {
            return numeric_service::floatDirection_13cfc0(static_cast<BoundPathDependencies *>(c)->direction,x,y);
        };
    }
};
}
#endif // SLINKY_SHARE_F0B2F81EEFF1CE571A04
