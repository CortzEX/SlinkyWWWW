#include "ProfileManager.hpp"
#include "ByteStrings.hpp"
#include <algorithm>
#include <cstring>
#include <intrin.h>

// RVAs below are absolute captured addresses minus base0x7ffbfb3b0000.
// Protected encodings in 4C800 are represented by the named provider contracts;
// the surrounding row, timestamp, error and cleanup algorithms are concrete.
namespace reconstruction::configuration {
namespace {
template<class T>T read(const void*p,std::ptrdiff_t at=0){T v;std::memcpy(&v,static_cast<const std::uint8_t*>(p)+at,sizeof v);return v;}
template<class T>void write(void*p,std::ptrdiff_t at,T v){std::memcpy(static_cast<std::uint8_t*>(p)+at,&v,sizeof v);}
void*ptr(Word w){return reinterpret_cast<void*>(std::uintptr_t(w));}
Word word(const void*p){return reinterpret_cast<Word>(p);}
std::int32_t compareName(void*context,const void*a,const void*b){return compareProfileName_eca0(a,b,*static_cast<const ProfileManagerDependencies*>(context));}
std::int32_t compareAge(void*context,const void*a,const void*b){return compareProfileAge_ee70(a,b,*static_cast<const ProfileManagerDependencies*>(context));}
std::uint32_t collect(void*context,const FileProfile*record,void*user){return collectProfile_ecb0(record,user,*static_cast<const ProfileManagerDependencies*>(context));}
// A count/capacity/rows triple has the same native layout as the profile list.
struct Retained {Word count=0,capacity=0;std::uint8_t*rows=nullptr;};
void freeRetained(Retained&r,const ProfileManagerDependencies&d){
    for(Word i=0,offset=0;i<r.count;++i,offset+=16)d.paths.release(d.paths.context,ptr(read<Word>(r.rows,offset)));
    r.count=0;r.capacity=0;d.paths.release(d.paths.context,r.rows);
}
}
std::int32_t compareProfileName_eca0(const void*a,const void*b,const ProfileManagerDependencies&d){
    return d.compareString_13d0a0(d.context,static_cast<const char*>(ptr(read<Word>(a))),static_cast<const char*>(ptr(read<Word>(b))));
}
std::int32_t compareProfileAge_ee70(const void*a,const void*b,const ProfileManagerDependencies&d){
    const auto right=read<std::int64_t>(b,0x30),left=read<std::int64_t>(a,0x30);
    if(left<right)return -1;
    if(left>right)return 1;
    return compareProfileName_eca0(a,b,d);
}
std::uint32_t collectProfile_ecb0(const FileProfile*file,void*collection,const ProfileManagerDependencies&d){
    const auto name=file->name;
    const auto length=recovered_string_length_ab840(reinterpret_cast<const std::uint8_t*>(name));
    auto*copy=static_cast<char*>(d.paths.allocateZeroed(d.paths.context,length+1,1));
    if(!copy)return 1005;
    d.copyString_13d0b0(d.context,copy,name,length);
    std::uint8_t record[64]{};
    write(record,0,word(copy));write(record,8,word(copy)+std::min(length,Word(15)));
    write(record,0x30,file->modificationAgeSeconds);
    const Word key[2]{word(copy),0};
    auto*retained=static_cast<Retained*>(ptr(read<Word>(collection,8)));
    if(retained->rows){
        const auto match=d.find_13d0e0(d.context,key,retained->rows,retained->count,16,compareName,const_cast<ProfileManagerDependencies*>(&d));
        if(match)write(record,0x38,read<std::uint32_t>(match,8));
    }
    auto*date=reinterpret_cast<char*>(record+0x10);
    const auto age=file->modificationAgeSeconds;
    if(age==~Word(0)){
        std::memcpy(date,d.paths.image+0x13ff7e,16);write(date,16,Word(0x746164206e6f6974));
    }else{
        const auto high=__mulh(std::int64_t(age),std::int64_t(0x1845c8a0ce512957));
        const auto days=std::int64_t(Word(high>>13)+(Word(high)>>63));
        if(days==1){std::memcpy(date,d.paths.image+0x13ffb1,16);write(date,16,Word(0x2e6f67));}
        else if(days==0){std::memcpy(date,d.paths.image+0x13ffc9,16);write(date,16,Word(0));}
        else recovered_format(&d.format,date,25,reinterpret_cast<const char*>(d.paths.image+0x13ff99),days);
    }
    auto*profiles=static_cast<std::uint8_t*>(ptr(read<Word>(collection)));
    if((recovered_list_growth(profiles+16,64,read<Word>(profiles),profiles+8,std::uint32_t(word(copy)),&d.memory)&0xff)==0){
        d.paths.release(d.paths.context,copy);return 1005;
    }
    auto*destination=static_cast<std::uint8_t*>(ptr(read<Word>(profiles,16)))+read<Word>(profiles)*64;
    // Native copy stores the highest 16-byte chunk first.
    for(int offset=48;offset>=0;offset-=16)std::memcpy(destination+offset,record+offset,16);
    write(profiles,0,read<Word>(profiles)+1);return 0;
}
std::uint32_t refreshProfiles_ead0(std::uint8_t*profiles,const ProfileManagerDependencies&d){
    Retained retained;
    auto count=read<Word>(profiles);
    if(count){
        for(Word offset=0x38;count;--count,offset+=64){
            auto*rows=static_cast<std::uint8_t*>(ptr(read<Word>(profiles,16)));
            if(read<std::uint32_t>(rows,offset)==0)continue;
            const auto*name=static_cast<const char*>(ptr(read<Word>(rows,std::ptrdiff_t(offset)-0x38)));
            const auto length=recovered_string_length_ab840(reinterpret_cast<const std::uint8_t*>(name));
            auto*copy=static_cast<char*>(d.paths.allocateZeroed(d.paths.context,length+1,1));
            if(!copy){freeRetained(retained,d);return 1005;}
            d.copyString_13d0b0(d.context,copy,name,length);
            const auto flag=read<std::uint32_t>(rows,offset);
            if(recovered_list_growth(&retained.rows,16,retained.count,&retained.capacity,std::uint32_t(word(profiles)),&d.memory)&0xff){
                auto*entry=retained.rows+retained.count*16;write(entry,0,word(copy));write(entry,8,flag);write(entry,12,std::uint32_t(0));++retained.count;
            }
            // A failed growth preserves the native untracked copied allocation.
        }
        if(retained.rows)d.sort_13d0f0(d.context,retained.rows,retained.count,16,compareName,const_cast<ProfileManagerDependencies*>(&d));
        for(Word i=0,offset=0;i<read<Word>(profiles);++i,offset+=64){
            auto*rows=static_cast<std::uint8_t*>(ptr(read<Word>(profiles,16)));d.paths.release(d.paths.context,ptr(read<Word>(rows,offset)));
        }
        write(profiles,0,Word(0));write(profiles,8,Word(0));
        d.paths.release(d.paths.context,ptr(read<Word>(profiles,16)));write(profiles,16,Word(0));
    }
    const Word collection[2]{word(profiles),word(&retained)};
    const auto error=enumerateProfiles_c320(const_cast<Word*>(collection),collect,const_cast<ProfileManagerDependencies*>(&d),d);
    const auto total=read<Word>(profiles);auto*rows=ptr(read<Word>(profiles,16));
    if(total&&rows)d.sort_13d0f0(d.context,rows,total,64,compareAge,const_cast<ProfileManagerDependencies*>(&d));
    freeRetained(retained,d);return error;
}
std::int32_t formatFilename_4c9d0(char*out,const std::uint16_t*filename,const ProfileManagerDependencies&d){
    const Word arguments[]{word(filename)};
    const auto options=d.files.formatOptions(d.files.context);
    return d.files.formatNarrow(d.files.context,options,out,260,260,reinterpret_cast<const char*>(d.paths.image+0x157000),0,arguments);
}
std::uint32_t enumerateFiles_4c800(std::uint16_t**path,void*user,FileProfileCallback callback,void*callbackContext,const ProfileManagerDependencies&d){
    auto*pattern=static_cast<std::uint16_t*>(d.paths.allocateZeroed(d.paths.context,261,2));
    if(!pattern)return 1005;
    const Word args[]{word(*path)};
    if(formatPath_4c6a0(pattern,262,reinterpret_cast<const std::uint16_t*>(d.paths.image+0x157004),args,d.paths)==~std::uint32_t(0)){
        d.paths.release(d.paths.context,pattern);return 1006;
    }
    std::uint8_t findData[0x250]; // Native stack record is populated by the provider.
    const auto handle=d.files.findFirst(d.files.context,pattern,findData);
    if(std::uint32_t(handle)==~std::uint32_t(0)){
        const auto error=d.paths.lastError(d.paths.context)==2?0u:1013u;
        d.paths.release(d.paths.context,pattern);return error;
    }
    std::uint64_t now;d.files.systemTime(d.files.context,&now);
    auto*filename=d.files.threadFilename(d.files.context);
    std::uint32_t error;
    for(;;){
        if(!(findData[0]&0x10)){
            if(formatFilename_4c9d0(filename,reinterpret_cast<const std::uint16_t*>(findData+0x2c),d)==-1){error=1006;break;}
            FileProfile record{filename,~Word(0)};
            const auto modified=read<Word>(findData,0x14);
            if(modified-1<now){Word high;(void)_umul128(now-modified,Word(0xd6bf94d5e57a42bd),&high);record.modificationAgeSeconds=high>>23;}
            error=callback(callbackContext,&record,user);if(error)break;
        }
        if(!d.files.findNext(d.files.context,handle,findData)){error=d.paths.lastError(d.paths.context)==18?0u:1015u;break;}
    }
    d.files.findClose(d.files.context,handle);d.paths.release(d.paths.context,pattern);return error;
}
std::uint32_t enumerateProfiles_c320(void*user,FileProfileCallback callback,void*callbackContext,const ProfileManagerDependencies&d){
    std::uint16_t*path;
    auto error=initializePath_4c590(&path,d.paths);if(error)return error;
    error=appendPath_4c610(&path,d.paths.image+0x13ec08,d.paths);
    if(!error)error=ensureDirectory_4c740(&path,d.paths);
    if(!error)error=appendPath_4c610(&path,d.paths.image+0x13ec30,d.paths);
    if(!error)error=ensureDirectory_4c740(&path,d.paths);
    if(!error)error=enumerateFiles_4c800(&path,user,callback,callbackContext,d);
    releasePath_4cd20(&path,d.paths);return error;
}
}
