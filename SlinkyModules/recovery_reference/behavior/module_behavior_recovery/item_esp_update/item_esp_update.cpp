#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <emmintrin.h>

typedef uint64_t (*item_endpoint)(uint64_t target,uint64_t a,uint64_t b,
    uint64_t c,uint64_t d,uint64_t e,uint64_t f,uint64_t g);
double recovered_vector_distance_squared(const double *,const double *);

static uint64_t read64(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t read32(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static double readf64(const void *p){double v;memcpy(&v,p,8);return v;}
static float readf32(const void *p){float v;memcpy(&v,p,4);return v;}
static void write64(void *p,uint64_t v){memcpy(p,&v,8);}
static void write32(void *p,uint32_t v){memcpy(p,&v,4);}
static void write8(void *p,uint8_t v){memcpy(p,&v,1);}
static uint64_t method_target(uint64_t object,uint32_t offset){
    uint64_t table=read64((const void *)(uintptr_t)object);
    return read64((const void *)(uintptr_t)(table+offset));
}
static uint64_t invoke(item_endpoint call,uint64_t target,uint64_t a,uint64_t b,
    uint64_t c,uint64_t d,uint64_t e,uint64_t f,uint64_t g){
    return call(target,a,b,c,d,e,f,g);
}
static uint64_t game_at(uint64_t bridge){return read64((const void *)(uintptr_t)bridge);}
static uint64_t game_call(item_endpoint call,uint64_t bridge,uint32_t rva,
    uint64_t a,uint64_t b,uint64_t c,uint64_t d,uint64_t e,uint64_t f,uint64_t g){
    return invoke(call,rva,a,b,c,d,e,f,g);
}

/* Original callback target passed to the UTF-16 label lookup at 0x13d0e0. */
__declspec(dllexport) int32_t recovered_item_esp_compare_41830(const int32_t *left,
    const uint8_t *right){
    uint32_t a,b,result;int32_t signed_result;
    memcpy(&a,left,4);b=read32(right+0x14);result=a-b;
    memcpy(&signed_result,&result,4);return signed_result;
}

__declspec(dllexport) void recovered_item_esp_update_41250(uint8_t *event,
    uint8_t *image,item_endpoint call){
    const uint64_t bridge=read64(event+8);
    uint64_t count=read64(image+0x302130);

    /* Drop cached label objects before rebuilding the 88-byte record table. */
    if(count){
        uint64_t client=read64((const void *)(uintptr_t)(game_at(bridge)+8));
        for(uint64_t i=0;i<count;i++){
            uint8_t *row=image+0x302180+i*0x58;
            if(read64(row)){
                invoke(call,method_target(client,0xb0),client,read64(row),0,0,0,0,0);
                write64(row,0);
                count=read64(image+0x302130);
            }
        }
    }
    write64(image+0x302130,0);
    if(!read64((const void *)(uintptr_t)(bridge+0x20)))return;

    uint8_t query[0x30],origin[0x30],current[0x30];
    memset(query,0,0x30);memset(origin,0,0x30);
    game_call(call,bridge,0x23030,(uint64_t)(uintptr_t)query,game_at(bridge),
        read64((const void *)(uintptr_t)(bridge+0x28)),0,0,0,0);
    uint64_t list=game_call(call,bridge,0x24620,game_at(bridge),
        read64((const void *)(uintptr_t)(bridge+0x20)),0,0,0,0,0);
    int32_t reported=(int32_t)game_call(call,bridge,0x24e50,game_at(bridge),list,
        0,0,0,0,0);
    for(int32_t index=0;index<reported;index++){
        do{
            uint64_t item=game_call(call,bridge,0x24e80,game_at(bridge),list,
                (uint32_t)index,0,0,0,0);
            uint64_t entity=game_call(call,bridge,0x27cf0,game_at(bridge),item,
                0,0,0,0,0);
            if(!entity)break;
            if((uint8_t)game_call(call,bridge,0x237b0,game_at(bridge),entity,
                0,0,0,0,0))break;

            memset(origin,0,0x30);
            game_call(call,bridge,0x23030,(uint64_t)(uintptr_t)origin,game_at(bridge),
                entity,0,0,0,0);
            double distance=recovered_vector_distance_squared((const double *)origin,
                (const double *)query);
            float radius=readf32(image+0x2f1ce0);
            __m128 r=_mm_set_ss(radius);r=_mm_mul_ss(r,r);
            double radius2=(double)_mm_cvtss_f32(r);
            /* UCOMISD followed by JA rejects only ordered values above radius;
               unordered NaN distances fall through into record creation. */
            if(distance>radius2)break;

            /* Destination row is captured before any item/game helper can mutate count. */
            uint64_t captured_count=read64(image+0x302130);
            uint8_t *row=image+0x302140+captured_count*0x58;
            uint64_t base_game=game_at(bridge);
            uint64_t stack=game_call(call,bridge,0x27d30,base_game,entity,0,0,0,0,0);
            if(!stack)break;
            int32_t quantity=(int32_t)game_call(call,bridge,0x25d70,base_game,stack,
                0,0,0,0,0);
            if(quantity<=0)break;
            uint64_t item_object=game_call(call,bridge,0x25d10,base_game,stack,
                0,0,0,0,0);
            if(!item_object)break;
            uint32_t item_id=(uint32_t)game_call(call,bridge,0x25c50,base_game,
                item_object,0,0,0,0,0);

            uint64_t string_data=0;
            if(read64(image+0x3043b0)){
                string_data=invoke(call,0x13d0e0,(uint64_t)(uintptr_t)&item_id,
                    read64(image+0x3043b0),read64(image+0x3043a0),
                    0x18,0x180041830,0,0);
            }
            if(!string_data){
                if(!image[0x2f1d20])break;
                string_data=(uint64_t)(uintptr_t)(image+0x2f1ce8);
            }

            /* Record fields through +0x50 follow the original individual stores. */
            write64(row+0x30,read64((const void *)(uintptr_t)(string_data+8)));
            write32(row+0x38,read32((const void *)(uintptr_t)(string_data+0x10)));
            write32(row+0x4c,item_id);
            write8(row+0x50,(uint8_t)quantity);
            write64(row+0x28,read64((const void *)(uintptr_t)(origin+0x10)));
            memcpy(row+0x18,origin,16);

            memset(current,0,0x30);
            game_call(call,bridge,0x230d0,(uint64_t)(uintptr_t)current,game_at(bridge),
                entity,0,0,0,0);
            write64(row+0x10,read64(current+0x10));
            memcpy(row,current,16);
            uint64_t now=read64(image+0x302130)+1;
            write64(image+0x302130,now);
            if(now==100)goto collection_done;
        }while(0);
        reported=(int32_t)game_call(call,bridge,0x24e50,game_at(bridge),list,
            0,0,0,0,0);
    }

collection_done:
    if(image[0x2f1ca8]!=1||!read64(image+0x302130))return;
    uint64_t world=game_call(call,bridge,0x22d40,game_at(bridge),
        read64((const void *)(uintptr_t)(bridge+0x18)),0,0,0,0,0);
    uint64_t camera=game_call(call,bridge,0x272a0,game_at(bridge),world,
        0,0,0,0,0);
    if(!camera||!read64(image+0x302130))return;
    double merge_radius=readf64(image+0x154360);
    for(uint64_t i=0;i<read64(image+0x302130);i++){
        uint8_t *row=image+0x302140+i*0x58;
        uint64_t quantity=row[0x50];
        if(!quantity)continue;
        uint64_t total=quantity;
        for(uint64_t j=0;j<read64(image+0x302130);j++){
            if(i==j)continue;
            uint8_t *other=image+0x302140+j*0x58;
            if(read32(row+0x4c)!=read32(other+0x4c))continue;
            double d2=recovered_vector_distance_squared((const double *)(row+0x18),
                (const double *)(other+0x18));
            if(d2<merge_radius){total+=(uint64_t)other[0x50];write8(other+0x50,0);}
        }
        uint8_t clamped=(uint8_t)(total<99?total:99);
        write8(row+0x50,clamped);
        if(total>1){
            uint64_t row_game=game_at(bridge);
            invoke(call,0xab710,(uint64_t)(uintptr_t)(image+0x3043b8),5,
                (uint64_t)(uintptr_t)(image+0x1543cb),clamped,0,0,0);
            uint64_t client=read64((const void *)(uintptr_t)(row_game+8));
            uint64_t label=invoke(call,method_target(client,0x538),client,
                (uint64_t)(uintptr_t)(image+0x3043b8),0,0,0,0,0);
            if(label){
                label=invoke(call,method_target(client,0xa8),client,label,0,0,0,0,0);
                write64(row+0x40,label);
                if(label){
                    uint32_t color=(uint32_t)game_call(call,bridge,0x27560,
                        row_game,camera,label,0,0,0,0);
                    write32(row+0x48,color);
                }
            }else write64(row+0x40,0);
        }else write64(row+0x40,0);
    }
}
