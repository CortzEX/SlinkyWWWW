#include "ListRuntime.hpp"
#include <bit>
#include <cstring>
#include <cstdlib>
namespace {
template<class T>T get(const void *p){T v;std::memcpy(&v,p,sizeof v);return v;}
template<class T>void put(void *p,T v){std::memcpy(p,&v,sizeof v);}
void *at(std::uint64_t base,std::uint32_t index,std::uint32_t stride){return reinterpret_cast<void *>(std::uintptr_t(base+std::uint32_t(index*stride)));}
void *insert(void *slot,std::uint32_t stride,void *metadata,const void *record,std::uint64_t comparator,RecoveredFrameInvoker invoke,const ListMemoryDependencies &memory,bool unique){
    auto *bytes=static_cast<std::uint8_t *>(metadata);
    auto last=get<std::uint32_t>(bytes+4);std::uint32_t first=0,index=last;
    if(last){
        const auto cached=get<std::uint64_t>(slot);
        while(first<last){
            const auto middle=first+((last-first)>>1);
            const auto order=std::bit_cast<std::int32_t>(std::uint32_t(invoke(comparator,0,std::uintptr_t(record),std::uintptr_t(at(cached,middle,stride)))));
            if(order==0){if(unique)return at(get<std::uint64_t>(slot),middle,stride);index=middle;break;}
            if(order<0)last=middle;else first=middle+1;
            index=last;
        }
    }
    auto count=get<std::uint32_t>(bytes+4);const auto capacity=get<std::uint32_t>(bytes);
    auto base=get<std::uint64_t>(slot);
    if(count>=capacity){
        const std::uint32_t grown=capacity?capacity*2:8;
        put(bytes,grown);
        auto *replacement=memory.reallocate(reinterpret_cast<void *>(std::uintptr_t(base)),std::uint32_t(grown*stride));
        if(!replacement){memory.allocation_failure();std::abort();}
        base=std::uintptr_t(replacement);put(slot,base);count=get<std::uint32_t>(bytes+4);
    }
    auto *out=at(base,index,stride);
    memory.move(at(base,index+1,stride),out,std::uint32_t((count-index)*stride));
    memory.copy(out,record,stride);
    put(bytes+4,get<std::uint32_t>(bytes+4)+1);return out;
}
}
// DF90 always inserts an equal comparator record; E0B0 returns the existing one.
void *recovered_sorted_insert_df90(void *slot,std::uint32_t stride,void *metadata,const void *record,std::uint64_t comparator,RecoveredFrameInvoker invoke,const ListMemoryDependencies &memory){return insert(slot,stride,metadata,record,comparator,invoke,memory,false);}
void *recovered_unique_insert_e0b0(void *slot,std::uint32_t stride,void *metadata,const void *record,std::uint64_t comparator,RecoveredFrameInvoker invoke,const ListMemoryDependencies &memory){return insert(slot,stride,metadata,record,comparator,invoke,memory,true);}
void *recovered_remove_index_e1d0(void *data,std::uint32_t stride,void *metadata,std::uint32_t index,const ListMemoryDependencies &memory){
    auto *bytes=static_cast<std::uint8_t *>(metadata);const auto remaining=get<std::uint32_t>(bytes+4)-1;
    put(bytes+4,remaining);const auto base=std::uintptr_t(data);
    return memory.move(at(base,index,stride),at(base,index+1,stride),std::uint32_t((remaining-index)*stride));
}
void *recovered_remove_pointer_e210(void *data,std::uint32_t stride,void *metadata,const void *found,const ListMemoryDependencies &memory){
    const auto distance=std::uintptr_t(found)-std::uintptr_t(data);
    const auto quotient=distance/stride;
    return recovered_remove_index_e1d0(data,stride,metadata,std::uint32_t(quotient),memory);
}
